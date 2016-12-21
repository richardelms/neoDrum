#include <Potentiometer.h>
#include <MIDI.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Pushbutton.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>

//input definitions
//controlls
Potentiometer brightnessPot = Potentiometer(15);
Pushbutton startStopButton(22);
Pushbutton functionButton(23);
int encoder0 = 24;
int encoder1 = 25;
Pushbutton resetPatternButton(26);
int lastEncoderPosition = 0;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

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
Pushbutton hitButtons[] = {
  hitButton_0, hitButton_1, hitButton_2,
  hitButton_3, hitButton_4, hitButton_5,
  hitButton_6, hitButton_7
};

//neoPixel definitions
#define neoOutput 2
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, neoOutput,
                            NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
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

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(255, 255, 0), matrix.Color(0, 255, 0), matrix.Color(0, 255, 255), matrix.Color(0, 0, 255), matrix.Color(255, 0, 255)
};

//midi definitions
MIDI_CREATE_DEFAULT_INSTANCE();
int instrumentNotes[] = {43, 42, 41, 40, 39, 38, 37, 36};
bool notesOn[] = {false, false, false, false, false, false, false, false};
int octive = 0;
int instrumentVelocities[] = {100, 100, 100, 100, 100, 100, 100, 100};


//config values
int numSteps = 8;
int bpm = 119;
bool firstStep = true;
int matrixBrightness = 20;

//util vars
int functionMode = 0; //0 = bpm/ 1 = octive/2 = velocity  /3 = brightness
int currentStep = 0;
int selectedInstrument = 7;
unsigned long lastStep = 0;
bool sequence[8][8];
bool started = false;

// initialisation
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("ginTronics 101");
  InitMatrix();
  MIDI.begin(MIDI_CHANNEL_OMNI);
  SetupEncoder();
}

void SetupEncoder() {
  pinMode (encoder0, INPUT);
  pinMode (encoder1, INPUT);
}

void InitAnimation() {
  int x = matrix.width();
  int pass = 0;
  matrix.setTextWrap(false);
  matrix.setTextColor(colors[0]);
  for (int i = 0; i < 80; i++) {
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(F("ginTronics"));
    --x;
    pass ++;
    if (pass == 6) {
      pass = 0;
    }
    matrix.setTextColor(colors[pass]);
    matrix.show();
    delay(60);
  }
  UpdateLcd();
}

void InitMatrix() {
  matrix.begin();
  matrix.setBrightness(matrixBrightness);
  matrix.show();
  InitAnimation();
  UpdateLeds();
}

// program loop
void loop() {
  CheckForStep();
  CheckForInputs();
}

void CheckForInputs() {
  //controlls
  if (startStopButton.getSingleDebouncedRelease()) {
    started = !started;
  }

  if (resetPatternButton.getSingleDebouncedRelease()) {
    ResetPattern();
  }

  if (functionButton.getSingleDebouncedRelease()) {
    functionMode ++;
    if (functionMode == 4) {
      functionMode = 0;
    }
    UpdateLcd();
  }

  //matrix input

  if (instrumentSelectButtons[0].getSingleDebouncedRelease()) {
    SetInstrument(0);
  }
  if (instrumentSelectButtons[1].getSingleDebouncedRelease()) {
    SetInstrument(1);
  }
  if (instrumentSelectButtons[2].getSingleDebouncedRelease()) {
    SetInstrument(2);
  }
  if (instrumentSelectButtons[3].getSingleDebouncedRelease()) {
    SetInstrument(3);
  }
  if (instrumentSelectButtons[4].getSingleDebouncedRelease()) {
    SetInstrument(4);
  }
  if (instrumentSelectButtons[5].getSingleDebouncedRelease()) {
    SetInstrument(5);
  }
  if (instrumentSelectButtons[6].getSingleDebouncedRelease()) {
    SetInstrument(6);
  }
  if (instrumentSelectButtons[7].getSingleDebouncedRelease()) {
    SetInstrument(7);
  }

  if (hitButtons[0].getSingleDebouncedRelease()) {
    SetHit(0);
  }
  if (hitButtons[1].getSingleDebouncedRelease()) {
    SetHit(1);
  }
  if (hitButtons[2].getSingleDebouncedRelease()) {
    SetHit(2);
  }
  if (hitButtons[3].getSingleDebouncedRelease()) {
    SetHit(3);
  }
  if (hitButtons[4].getSingleDebouncedRelease()) {
    SetHit(4);
  }
  if (hitButtons[5].getSingleDebouncedRelease()) {
    SetHit(5);
  }
  if (hitButtons[6].getSingleDebouncedRelease()) {
    SetHit(6);
  }
  if (hitButtons[7].getSingleDebouncedRelease()) {
    SetHit(7);
  }
  CheckForEncoderInput();
}


void CheckForEncoderInput() {
  n = digitalRead(encoder0);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder1) == LOW) {
      encoder0Pos--;
      DownInput();
    } else {
      encoder0Pos++;
      UpInput();
    }
  }
  encoder0PinALast = n;
}

void UpInput() {
  if (functionMode == 0) {
    bpm ++;
  }
  if (functionMode == 1) {
    octive ++;
    if (octive > 5) {
      octive = 5;
    }
  }
  if (functionMode == 2) {
    instrumentVelocities[selectedInstrument] ++;
    if (instrumentVelocities[selectedInstrument] > 127) {
      instrumentVelocities[selectedInstrument] = 127;
    }
  }
  if (functionMode == 3) {
    matrixBrightness += 10;
    if (matrixBrightness > 200) {
      matrixBrightness = 200;
    }
    matrix.setBrightness(matrixBrightness);
    matrix.show();
  }
  UpdateLcd();
}

void DownInput() {
  if (functionMode == 0) {
    bpm --;
    if (bpm < 1) {
      bpm = 1;
    }
  }
  if (functionMode == 1) {
    octive --;
    if (octive < -5) {
      octive = -5;
    }
  }

  if (functionMode == 2) {
    instrumentVelocities[selectedInstrument] --;
    if (instrumentVelocities[selectedInstrument] < 0) {
      instrumentVelocities[selectedInstrument] = 0;
    }
  }

  if (functionMode == 3) {
    matrixBrightness -= 10;
    if (matrixBrightness < 10) {
      matrixBrightness = 10;
    }
    matrix.setBrightness(matrixBrightness);
    matrix.show();
  }
  UpdateLcd();
}




void ResetPattern() {
  for (int i = 0; i < 8; i++) {
    for (int x = 0; x < 8; x ++) {
      sequence[i][x] = false;
    }
  }
  UpdateLeds();
}

void SetInstrument(int instrument) {
  selectedInstrument = instrument;
  UpdateLeds();
  UpdateLcd();
  MIDI.sendNoteOn(instrumentNotes[instrument] + (octive * 8), instrumentVelocities[instrument], 1);
  MIDI.sendNoteOff(instrumentNotes[instrument] + (octive * 8), 100, 1);
}

void SetHit(int x) {
  sequence[selectedInstrument][x] = !sequence[selectedInstrument][x];
  UpdateLeds();
}

void CheckForStep() {
  if (!started) {
    return;
  }
  unsigned long currentMillis = millis();
  if (!firstStep) {
    if (currentMillis - lastStep >= 60000 / (bpm * 2)) {
      lastStep = currentMillis;
      currentStep ++;
      if (currentStep == numSteps) {
        currentStep = 0;
      }
      MakeStep();
    }
  } else {
    lastStep = currentMillis;
    firstStep = false;
    MakeStep();
  }
}

void MakeStep() {
  CheckForNoteOff();
  PlayNotes();
  UpdateLeds();
}

void PlayNotes() {
  for (int i = 0; i < 8; i++) {
    if (sequence[i][currentStep] == true) {
      MIDI.sendNoteOn(instrumentNotes[i] + (octive * 8), instrumentVelocities[i], 1);
      notesOn[i] = true;
    }
  }
}

void CheckForNoteOff() {
  for (int i = 0; i < sizeof(notesOn); i++) {
    if (notesOn[i]) {
      MIDI.sendNoteOff(instrumentNotes[i] + (octive * 8), 127, 1);
    }
  }
}

void UpdateLeds() {
  int masterIndex = 0;
  for (int i = 0; i < 8; i++) {
    for (int x = 0; x < 8; x ++) {
      if (sequence[i][x] == true) {
        if (currentStep == x) {
          matrix.setPixelColor(masterIndex, selectedAndStepColor.r, selectedAndStepColor.g, selectedAndStepColor.b);
        } else {
          matrix.setPixelColor(masterIndex, selectedColor.r, selectedColor.g, selectedColor.b);
        }
      } else {
        if (currentStep == x) {
          matrix.setPixelColor(masterIndex, normalStepColor.r, normalStepColor.g, normalStepColor.b);
        } else {
          if (selectedInstrument == i) {
            matrix.setPixelColor(masterIndex, selectedInstrumentColor.r, selectedInstrumentColor.g, selectedInstrumentColor.b);
          } else {
            matrix.setPixelColor(masterIndex, baseUnselectedValue.r, baseUnselectedValue.g, baseUnselectedValue.b);
          }
        }
      }
      masterIndex++;
    }
  }
  matrix.show();
}

void UpdateLcd() {
  lcd.clear();
  if (functionMode == 0) {
    lcd.setCursor(0, 0);
    // print the number of seconds since reset:
    lcd.print("BPM");
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(bpm);
  }
  if (functionMode == 1) {
    lcd.setCursor(0, 0);
    // print the number of seconds since reset:
    lcd.print("OCTAVE");
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(octive);
  }
  if (functionMode == 2) {
    lcd.setCursor(0, 0);
    // print the number of seconds since reset:
    lcd.print("VELOCITY");
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(instrumentVelocities[selectedInstrument]);
  }
  if (functionMode == 3) {
    lcd.setCursor(0, 0);
    // print the number of seconds since reset:
    lcd.print("Brightness");
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(matrixBrightness);
  }
}




