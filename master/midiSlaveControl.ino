void DebugMidi() {
  if (MIDI.read())
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(MIDI.getType());
    lcd.setCursor(0, 1);
    lcd.print(MIDI.getData1());
  }
}

void HandleClockTick() {
  //  if (midiClockCount % 12 == 0) {
  //    if (!firstMidiStep) {
  //      currentStep ++;
  //      if (currentStep == numSteps) {
  //        currentStep = 0;
  //      }
  //    }
  //    firstMidiStep = false;
  //    MakeStep();
  //  }
  //  midiClockCount ++;
}

void HandleStop() {
  //  firstMidiStep = true;
  //  midiClockCount = 0;
  //  currentStep = 0;
  //  UpdateLeds();
}
