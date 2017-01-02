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

