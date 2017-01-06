void UpdateLcd() {
  lcd.clear();
  switch (functionMode) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("BPM");
      lcd.setCursor(0, 1);
      lcd.print(bpm);
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("VELOCITY");
      lcd.setCursor(0, 1);
      lcd.print(sequence[selectedNote.instrument][selectedNote.sequencePosition].velocity);
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("SWING");
      lcd.setCursor(0, 1);
      lcd.print(sequence[selectedNote.instrument][selectedNote.sequencePosition].SwingAmount);
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("OCTAVE");
      lcd.setCursor(0, 1);
      lcd.print(octive);
      break;
    case 4:
      lcd.setCursor(0, 0);
      lcd.print("NOTE SCALE");
      lcd.setCursor(0, 1);
      switch (patternScale) {
        case 6:
        lcd.print("4/32");
          break;
        case 12:
        lcd.print("4/16");
          break;
        case 24:
        lcd.print("4/8");
          break;
        case 48:
        lcd.print("4/4");
          break;
        case 96:
        lcd.print("4/2");
          break;
        case 192:
        lcd.print("4/1");
          break;
      }
      break;
    case 5:
      lcd.setCursor(0, 0);
      lcd.print("MIDI CLOCK MODE");
      lcd.setCursor(0, 1);
      if (master) {
        lcd.print("INTERNAL");
      } else {
        lcd.print("EXTERNAL");
      }
      break;
    case 6:
      lcd.setCursor(0, 0);
      lcd.print("Brightness");
      lcd.setCursor(0, 1);
      lcd.print(matrixBrightness);
      break;
  }
}

