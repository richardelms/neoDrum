void DebugMidi() {
  if (master) {
    return;
  }
  if (MIDI.read())
  {
//    for debug
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print(MIDI.getType());
//    lcd.setCursor(0, 1);
//    lcd.print(MIDI.getData1());


    switch (MIDI.getType()) {
      case 248:
        HandleClockTick();
        break;
      case 242:
        HandleStop();
        break;
    }
  }
}

void HandleClockTick() {
  if (midiClockCount % patternScale == 0) {
    if (!firstMidiStep) {
      currentStep ++;
      if (currentStep == numSteps) {
        currentStep = 0;
      }
    }
    firstMidiStep = false;
    MakeStep();
  }
  midiClockCount ++;
}

void HandleStop() {
  firstMidiStep = true;
  midiClockCount = 0;
  currentStep = 0;
  UpdateLeds();
}
