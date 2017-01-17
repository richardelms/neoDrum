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
  //  if (midiClockCount % 4 == 0) {
  CheckForNotes();
  //  }
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
  if (midiClockCount == (patternScale * numSteps)) {
    midiClockCount = 0;
  }
}



void CheckForNotes() {
  for (int i = 0; i < 8; i ++) {
    for (int x = 0; x < numSteps; x ++) {
      if (sequence[i][x].ShouldPlay(midiClockCount)) {
        MIDI.sendNoteOff(instrumentNotes[sequence[i][x].instrument] + (octive * 8), 100, midiChanel);
        MIDI.sendNoteOn(instrumentNotes[sequence[i][x].instrument] + (octive * 8), sequence[i][x].velocity, midiChanel);
        notesOn[sequence[i][x].instrument] = true;
      }
    }
  }
}


void HandleStop() {
  firstMidiStep = true;
  midiClockCount = 0;
  currentStep = 0;
  UpdateLeds();
}
