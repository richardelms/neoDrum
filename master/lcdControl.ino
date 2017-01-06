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
    lcd.print(sequence[selectedNote.instrument][selectedNote.sequencePosition].velocity);
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
  if (functionMode == 7) {
    lcd.setCursor(0, 0);
    lcd.print("NOTE SCALE");
    String noteScale = "";
    switch (patternScale) {
      case 6:
        noteScale = "4/32";
                    break;
      case 12:
        noteScale = "4/16";
                    break;
      case 24:
        noteScale = "4/8";
                    break;
      case 48:
        noteScale = "4/4";
                    break;
                    case 96:
        noteScale = "4/2";
                    break;
                     case 192:
        noteScale = "4/1";
                    break;

    }
    lcd.setCursor(0, 1);
    lcd.print(noteScale);
  }
}

