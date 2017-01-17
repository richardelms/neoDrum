void DebugMidi() {
  if (master) {
    return;
  }
  if (MIDI.read())
  {
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
  CheckForNotes();
  if (midiClockCount % patternScale == 0) {
    if (!firstMidiStep) {
      currentStep ++;
      if (currentStep == numSteps) {
        currentStep = 0;
      }
    }
    firstMidiStep = false;
    UpdateLeds();
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
