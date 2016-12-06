#include <MIDI.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Pushbutton.h>
#include <Adafruit_NeoPixel.h>


//input definitions
//instrumentbuttons
Pushbutton instrumentSelect_0(31);
Pushbutton instrumentSelect_1(33);
Pushbutton instrumentSelect_2(35);
Pushbutton instrumentSelect_3(37);
Pushbutton instrumentSelect_4(39);
Pushbutton instrumentSelect_5(41);
Pushbutton instrumentSelect_6(43);
Pushbutton instrumentSelect_7(45);
Pushbutton instrumentSelectButtons[] = {
  instrumentSelect_0,instrumentSelect_1,instrumentSelect_2,
  instrumentSelect_3,instrumentSelect_4,instrumentSelect_5,
  instrumentSelect_6,instrumentSelect_7
};

//hitButtons
Pushbutton hitButton_0(30);
Pushbutton hitButton_1(32);
Pushbutton hitButton_2(34);
Pushbutton hitButton_3(36);
Pushbutton hitButton_4(38);
Pushbutton hitButton_5(40);
Pushbutton hitButton_6(42);
Pushbutton hitButton_7(44);
Pushbutton hitButtons[] = {
  hitButton_0,hitButton_1,hitButton_2,
  hitButton_3,hitButton_4,hitButton_5,
  hitButton_6,hitButton_7
};



//neoPixel definitions
#define neoOutput 3
#define matrixBrightness 50
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, neoOutput,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);
class NeoColor
{
  public:
    NeoColor(int,int, int);
    int r;
    int g;
    int b;
};
NeoColor::NeoColor(int red,int green, int blue){
  r = red;
  g = green;
  b = blue;
}

NeoColor baseUnselectedValue = NeoColor(0,0,0);

NeoColor normalStepColor = NeoColor(255,200,200);

NeoColor selectedColor = NeoColor(0,255,0);

NeoColor selectedAndStepColor = NeoColor(0,255,100);

NeoColor selectedInstrumentColor = NeoColor(0,0,255);

//midi definitions
MIDI_CREATE_DEFAULT_INSTANCE();
int instrumentNotes[] = {36,38,39,42,46,43,45,48};

//config values
int numSteps = 8;
int bpm = 120;
bool firstStep = true;

//util vars
int currentStep = 0;
int selectedInstrument = 4;
unsigned long lastStep = 0;

bool sequence[8][8] = {{false,false,false,false,false,false,false,false},
            {false,false,false,false,false,false,false,false},
            {false,false,false,false,false,false,false,false},
            {false,false,false,false,false,false,false,false},
            {false,false,false,false,false,false,false,false},
            {false,false,false,false,false,false,false,false},
            {false,false,false,false,false,false,false,false},
            {false,false,false,false,false,false,false,false}};


// initialisation
void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  InitMatrix();
}

void InitMatrix(){
  matrix.begin();
  matrix.setBrightness(matrixBrightness);
  matrix.show();
}

// program loop
void loop() {
  CheckForInputs();
  CheckForStep();
}

void CheckForInputs(){
  for(int i = 0 ; i < sizeof(instrumentSelectButtons);i++){
        if(instrumentSelectButtons[i].getSingleDebouncedPress()){
              selectedInstrument = i;
              UpdateLeds();
          }
    }
    for(int i = 0 ; i < sizeof(hitButtons);i++){
        if(hitButtons[i].getSingleDebouncedPress()){
              sequence[selectedInstrument][i] = !sequence[selectedInstrument][i];
              UpdateLeds();
          }
    }
}

void CheckForStep(){
  unsigned long currentMillis = millis();
  if(!firstStep){
    if (currentMillis - lastStep >= 60000/bpm) {
      lastStep = currentMillis;
      currentStep ++;
      if(currentStep == numSteps){
        currentStep = 0;
      }
      MakeStep();
    }
  }else{
    lastStep = currentMillis;
    firstStep = false;
    MakeStep();
  }
}

void MakeStep(){
  PlayNotes();
  UpdateLeds();
}

void PlayNotes(){
    for(int i = 0; i < 8; i++){
      if(sequence[i][currentStep] == true){
        MIDI.sendNoteOn(instrumentNotes[i], 100, 1);  
      }
    }
}

void UpdateLeds(){
  int masterIndex = 0;
  for(int i = 0; i < 8; i++){
    for(int x = 0; x < 8; x ++){
      if(sequence[i][x] == true){
        if(currentStep == x){
          matrix.setPixelColor(masterIndex, selectedAndStepColor.r, selectedAndStepColor.g, selectedAndStepColor.b);
        }else{
          matrix.setPixelColor(masterIndex, selectedColor.r, selectedColor.g, selectedColor.b);
        }
      }else{
        if(currentStep == x){
          matrix.setPixelColor(masterIndex, normalStepColor.r, normalStepColor.g, normalStepColor.b);
        }else{
          if(selectedInstrument == i){
            matrix.setPixelColor(masterIndex, selectedInstrumentColor.r, selectedInstrumentColor.g, selectedInstrumentColor.b);
          }else{
            matrix.setPixelColor(masterIndex, baseUnselectedValue.r, baseUnselectedValue.g, baseUnselectedValue.b);
          }
        }
      } 
      masterIndex++;
    } 
  }
  matrix.show();
}






