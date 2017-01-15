#include <Potentiometer.h>
#include <MIDI.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Pushbutton.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

//input definitions
//controlls
Potentiometer brightnessPot = Potentiometer(15);
Pushbutton startStopButton(22);
Pushbutton functionButton(23);
Pushbutton shiftButton(29);
int encoder0 = 24;
int encoder1 = 25;
Pushbutton resetPatternButton(26);
Pushbutton encoderButton(27);
int lastEncoderPosition = 0;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;
bool firstEncode = true;

//LCD Screen
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

//instrumentbuttons
Pushbutton instrumentSelect_0(30);
Pushbutton instrumentSelect_1(32);
Pushbutton instrumentSelect_2(34);
Pushbutton instrumentSelect_3(36);
Pushbutton instrumentSelect_4(38);
Pushbutton instrumentSelect_5(40);
Pushbutton instrumentSelect_6(42);
Pushbutton instrumentSelect_7(44);
Pushbutton instrumentSelectButtons[] = {
  instrumentSelect_0, instrumentSelect_1, instrumentSelect_2,
  instrumentSelect_3, instrumentSelect_4, instrumentSelect_5,
  instrumentSelect_6, instrumentSelect_7
};

//hitButtons
Pushbutton hitButton_0(31);
Pushbutton hitButton_1(33);
Pushbutton hitButton_2(35);
Pushbutton hitButton_3(37);
Pushbutton hitButton_4(39);
Pushbutton hitButton_5(41);
Pushbutton hitButton_6(43);
Pushbutton hitButton_7(45);
Pushbutton hitButton_8(46);
Pushbutton hitButton_9(48);
Pushbutton hitButton_10(50);
Pushbutton hitButton_11(52);
Pushbutton hitButton_12(47);
Pushbutton hitButton_13(49);
Pushbutton hitButton_14(51);
Pushbutton hitButton_15(53);

Pushbutton hitButtons[] = {
  hitButton_0, hitButton_1, hitButton_2,
  hitButton_3, hitButton_4, hitButton_5,
  hitButton_6, hitButton_7, hitButton_8, hitButton_9, hitButton_10,
  hitButton_11, hitButton_12, hitButton_13,
  hitButton_14, hitButton_15
};





//neoPixel definitions
#define neoOutput 2
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 2, 1, neoOutput,
                            NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE +
                            NEO_TILE_TOP + NEO_TILE_LEFT +
                            NEO_TILE_ROWS + NEO_TILE_PROGRESSIVE,
                            NEO_GRB            + NEO_KHZ800);
class NeoColor
{
  public:
    NeoColor(int, int, int);
    int r;
    int g;
    int b;
};
NeoColor::NeoColor(int red, int green, int blue) {
  r = red;
  g = green;
  b = blue;
}

NeoColor baseUnselectedValue = NeoColor(0, 0, 0);

NeoColor normalStepColor = NeoColor(255, 200, 200);

NeoColor selectedColor = NeoColor(0, 255, 0);

NeoColor selectedAndStepColor = NeoColor(255, 0, 0);

NeoColor selectedInstrumentColor = NeoColor(0, 0, 255);

NeoColor selectedNoteColor = NeoColor(255, 255, 0);



const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(255, 255, 0), matrix.Color(0, 255, 0), matrix.Color(0, 255, 255), matrix.Color(0, 0, 255), matrix.Color(255, 0, 255)
};

//midi definitions
MIDI_CREATE_DEFAULT_INSTANCE();
int instrumentNotes[] = {43, 42, 41, 40, 39, 38, 37, 36};
bool notesOn[] = {false, false, false, false, false, false, false, false};
bool instrumentMuted[] = {false, false, false, false, false, false, false, false};
bool instrumentSoloed[] = {false, false, false, false, false, false, false, false};
int octive = 0;
int midiChanel = 1;


//config values
int numSteps = 16;
int totalMatrixSize = 128;
int numFunctions = 7;
int numPatterns = 5;
bool started = false;
int midiClockCount = 0;
bool firstMidiStep = true;
bool master = false;
int currentSavePattern = 0;
int currentLoadPattern = 0;
int matrixBrightness = 30;
int patternScale = 24;
int functionMode = 0;
//0 = bpm
// 1 = velocity
//2 = swing
//3 = Octive
//4 = pattern scale
// 5 = master or slave
// 6 = Brightness




class Note
{
  public:
    int sequencePosition;
    int instrument;
    int velocity = 100;
    int SwingAmount = 0;
    int noteID = 0;
    bool on;
    bool ShouldPlay(int);
};
bool Note::ShouldPlay(int midiClockPosition) {
  if (on == true && midiClockPosition == ((sequencePosition * patternScale) + SwingAmount)) {
    return true;
  } else {
    return false;
  }
}





//util vars
Note sequence[8][16];
int bpm = 120;
bool firstStep = true;
int currentStep = 0;
int selectedInstrument = 7;
Note selectedNote;
unsigned long lastStep = 0;





// initialisation
void setup() {
  //  //organise this yoooooo its for the input monitoring led
  InitSequence();
  pinMode(28, OUTPUT);
  SetupLcd();
  InitMatrix();
  SetupMidi();
  SetupEncoder();
}


void InitSequence() {
  int idIndex = 0;
  for (int i = 0; i < 8; i ++) {
    for (int x = 0; x < numSteps; x ++) {
      sequence[i][x].sequencePosition = x;
      sequence[i][x].instrument = i;
      sequence[i][x].noteID = idIndex;
      sequence[i][x].velocity = 100;
      sequence[i][x].SwingAmount = 0;
      idIndex ++;
    }
  }
  selectedNote = sequence[7][0];
}


void SetupLcd() {
  lcd.begin(16, 2);
  lcd.print("INITALISING");
}

void SetupMidi() {
  MIDI.begin(midiChanel);
  MIDI.setHandleClock(HandleClockTick);
  MIDI.setHandleStop(HandleStop);
}

void SetupEncoder() {
  pinMode (encoder0, INPUT);
  pinMode (encoder1, INPUT);
}

void InitMatrix() {
  matrix.begin();
  matrix.setBrightness(matrixBrightness);
  matrix.show();
  //  InitAnimation();
  UpdateLeds();
}

// program loop
void loop() {
  DebugMidi();
  //  CheckForStep();
  CheckForInputs();
  CheckForEncoderInput();
}

