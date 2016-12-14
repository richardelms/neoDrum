#include <Potentiometer.h>
#include <MIDI.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Pushbutton.h>
#include <Adafruit_NeoPixel.h>


//input definitions
//pots
Potentiometer brightnessPot = Potentiometer(15);

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
  instrumentSelect_0,instrumentSelect_1,instrumentSelect_2,
  instrumentSelect_3,instrumentSelect_4,instrumentSelect_5,
  instrumentSelect_6,instrumentSelect_7
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
  hitButton_0,hitButton_1,hitButton_2,
  hitButton_3,hitButton_4,hitButton_5,
  hitButton_6,hitButton_7
};

//neoPixel definitions
#define neoOutput 3
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, neoOutput,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
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

NeoColor selectedAndStepColor = NeoColor(255,0,0);

NeoColor selectedInstrumentColor = NeoColor(0,0,255);

//midi definitions
MIDI_CREATE_DEFAULT_INSTANCE();
int instrumentNotes[] = {43,42,41,40,39,38,37,36};

//config values
int numSteps = 8;
int bpm = 200;
bool firstStep = true;
int matrixStartingBrightness = 10;
int lastBrightnessLevel = 0;

//util vars
int currentStep = 0;
int selectedInstrument = 7;
unsigned long lastStep = 0;
bool sequence[8][8];

// initialisation
void setup() {
//  Serial.begin(9600);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  InitMatrix();
}

void InitMatrix(){
//  brightnessPot.setSectors(255);
  matrix.begin();
  matrix.setBrightness(matrixStartingBrightness);
  matrix.show();
}

// program loop
void loop() {
  CheckForStep();
    CheckForInputs();

//  CheckForBrightnessAdjustment();
}

void CheckForInputs(){  
          if(instrumentSelectButtons[0].getSingleDebouncedRelease()){
              SetInstrument(0);
          }
          if(instrumentSelectButtons[1].getSingleDebouncedRelease()){
              SetInstrument(1);
          }
          if(instrumentSelectButtons[2].getSingleDebouncedRelease()){
              SetInstrument(2);
          }
          if(instrumentSelectButtons[3].getSingleDebouncedRelease()){
              SetInstrument(3);
          }
          if(instrumentSelectButtons[4].getSingleDebouncedRelease()){
              SetInstrument(4);
          }
          if(instrumentSelectButtons[5].getSingleDebouncedRelease()){
              SetInstrument(5);
          }
          if(instrumentSelectButtons[6].getSingleDebouncedRelease()){
              SetInstrument(6);
          }
          if(instrumentSelectButtons[7].getSingleDebouncedRelease()){
              SetInstrument(7);
          }



         if(hitButtons[0].getSingleDebouncedRelease()){
              SetHit(0);
          }
           if(hitButtons[1].getSingleDebouncedRelease()){
              SetHit(1);
          }
           if(hitButtons[2].getSingleDebouncedRelease()){
              SetHit(2);
          }
           if(hitButtons[3].getSingleDebouncedRelease()){
              SetHit(3);
          }
           if(hitButtons[4].getSingleDebouncedRelease()){
              SetHit(4);
          }
           if(hitButtons[5].getSingleDebouncedRelease()){
              SetHit(5);
          }
           if(hitButtons[6].getSingleDebouncedRelease()){
              SetHit(6);
          }
           if(hitButtons[7].getSingleDebouncedRelease()){
              SetHit(7);
          }
}

void SetInstrument(int instrument){
    selectedInstrument = instrument;
    UpdateLeds();
    MIDI.sendNoteOn(instrumentNotes[instrument], 100, 1);  
  }

  void SetHit(int x){
    sequence[selectedInstrument][x] = !sequence[selectedInstrument][x];
    UpdateLeds();
  }

void CheckForBrightnessAdjustment(){
    int brightnessPotValue = brightnessPot.getSector();
  if(brightnessPotValue != lastBrightnessLevel){
      lastBrightnessLevel = brightnessPotValue;
      matrix.setBrightness(brightnessPotValue);
      matrix.show();
    }
  }

void CheckForStep(){
  unsigned long currentMillis = millis();
  if(!firstStep){
    if (currentMillis - lastStep >= 60000/(bpm * 2)) {
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






