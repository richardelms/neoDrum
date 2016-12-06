#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_NeoPixel.h>

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
NeoColor normalStepColor = NeoColor(255,255,255);
NeoColor selectedColor = NeoColor(0,255,0);
NeoColor selectedAndStepColor = NeoColor(0,0,255);
NeoColor baseUnselectedValue = NeoColor(0,0,0);

//config values
int numSteps = 8;
int bpm = 120;
bool firstStep = true;

//util vars
int currentStep = 0;
int selectedInstrument = 4;
unsigned long lastStep = 0;

bool sequence[8][8] = {{true,true,false,false,true,false,false,false},
            {false,true,false,false,true,false,false,false},
            {false,true,false,true,false,true,false,true},
            {false,false,false,false,false,false,false,false},
            {false,false,true,false,false,false,false,true},
            {true,false,false,false,true,true,true,false},
            {false,false,true,true,false,false,false,false},
            {true,true,false,false,false,false,false,true}};


// initialisation
void setup() {
  InitMatrix();
}

void InitMatrix(){
  matrix.begin();
  matrix.setBrightness(matrixBrightness);
  matrix.show();
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
  UpdateLeds();
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
          matrix.setPixelColor(masterIndex, baseUnselectedValue.r, baseUnselectedValue.g, baseUnselectedValue.b);
        }
      } 
      masterIndex++;
    } 
  }
  matrix.show();
}



