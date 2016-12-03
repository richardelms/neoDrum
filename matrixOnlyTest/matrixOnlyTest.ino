#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_NeoPixel.h>

//neoPixel definitions
#define neoOutput 10
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
NeoColor normalStepColor = NeoColor(255,255,255);
NeoColor selectedColor = NeoColor(0,255,0);
NeoColor selectedAndStepColor = NeoColor(0,0,255);
NeoColor baseUnselectedValue = NeoColor(100,100,100);

//config values
int numSteps = 8;
int bpm = 120;
bool firstStep = true;

//util vars
int step = 0;
int selectedInstrument = 0;
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
  InitMatrix();
  InitAnimation();
}

void InitMatrix(){
  matrix.begin();
  matrix.setBrightness(255);
  matrix.show();
}

void InitAnimation(){
  for(int x = 0; x < 4; x++){
    for(int i = 0 ; i < 64; i++){
      matrix.setPixelColor(i, random(1,255), random(1,255), random(1,255));
      matrix.show();
      delay(100);
    }
  }
}

// program loop
void loop() {
  CheckForStep();
}


void CheckForStep(){
  unsigned long currentMillis = millis();
  if(!firstStep){
    if (currentMillis - lastStep >= 60000/bpm) {
      lastStep = currentMillis;
      step ++;
      if(step == numSteps){
        step = 0;
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
  UpdateLeds();
}

void UpdateLeds(){
  clearAllLeds();   
  ShowCurrentStep();
  setupSelectedLeds();
  matrix.show();
}

void clearAllLeds(){
  for(int i = 0; i < 64; i++){
    matrix.setPixelColor(i, baseUnselectedValue.r, baseUnselectedValue.g, baseUnselectedValue.b);
  }
}

void ShowCurrentStep(){
  int masterIndex = 0;
  for(int i = 0; i < 8; i++){
    for(int x = 0; x < 8; x ++){
      if(step == x){
        if(sequence[i][x] == true){
          matrix.setPixelColor(masterIndex, selectedAndStepColor.r, selectedAndStepColor.g, selectedAndStepColor.b);
        }else{
          matrix.setPixelColor(masterIndex, normalStepColor.r, normalStepColor.g, normalStepColor.b);
        }
      }
      masterIndex++;
    }
  }
}

void setupSelectedLeds(){
  int masterIndex = 0;
  for(int i = 0; i < 8; i++){
    for(int x = 0; x < 8; x ++){
      if(sequence[i][x] == true){
        if(selectedInstrument == i){
          matrix.setPixelColor(masterIndex, baseUnselectedValue.r, baseUnselectedValue.g, baseUnselectedValue.b);
        }
      }
      masterIndex++;
    }
  }
}






