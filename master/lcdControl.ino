void UpdateLcd() {
  lcd.clear();
  if (functionMode == 0) {
    lcd.setCursor(0, 0);
    lcd.print("BPM");
    lcd.setCursor(0, 1);
    lcd.print(bpm);
  }
  if (functionMode == 1) {
    lcd.setCursor(0, 0);
    lcd.print("OCTAVE");
    lcd.setCursor(0, 1);
    lcd.print(octive);
  }
  if (functionMode == 2) {
    lcd.setCursor(0, 0);
    lcd.print("VELOCITY");
    lcd.setCursor(0, 1);
    lcd.print(instrumentVelocities[selectedInstrument]);
  }
  if (functionMode == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Brightness");
    lcd.setCursor(0, 1);
    lcd.print(matrixBrightness);
  }
  if (functionMode == 4) {
    lcd.setCursor(0, 0);
    lcd.print("MIDI CLOCK MODE");
    lcd.setCursor(0, 1);
    if (master) {
      lcd.print("INTERNAL");
    } else {
      lcd.print("EXTERNAL");
    }
  }
  if (functionMode == 5) {
    lcd.setCursor(0, 0);
    lcd.print("SAVE PATTERN");
    lcd.setCursor(0, 1);
    lcd.print(currentSavePattern);
  }
  if (functionMode == 6) {
    lcd.setCursor(0, 0);
    lcd.print("LOAD PATTERN");
    lcd.setCursor(0, 1);
    lcd.print(currentLoadPattern);
  }
}

