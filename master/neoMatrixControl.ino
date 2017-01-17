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

void UpdateLeds() {
  int masterIndex = 0;
  for (int i = 0; i < 8; i++) {
    for (int x = 0; x < 8; x ++) {
      SetLedColor(i, x, masterIndex);
      masterIndex++;
    }
  }
  for (int i = 0; i < 8; i++) {
    for (int x = 8; x < 16; x ++) {
      SetLedColor(i, x, masterIndex);
      masterIndex++;
    }
  }
  matrix.show();
}

void SetLedColor(int i, int x, int masterIndex) {
  if (sequence[i][x].on) {
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
      if (instrumentSoloed[i]) {
        matrix.setPixelColor(masterIndex, soloColor.r, soloColor.g, soloColor.b);
      }
      if (instrumentMuted[i]) {
        matrix.setPixelColor(masterIndex, muteColor.r, muteColor.g, muteColor.b);
      }
    }
  }
  if (sequence[i][x].noteID == selectedNote.noteID && !sequence[i][x].hidden) {
    matrix.setPixelColor(masterIndex, selectedNoteColor.r, selectedNoteColor.g, selectedNoteColor.b);
  }

}
