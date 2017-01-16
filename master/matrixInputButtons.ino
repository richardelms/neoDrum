void CheckForInputs() {
  //led monitors
  if (!shiftButton.isPressed()) {
    digitalWrite(28, HIGH);
  } else {
    digitalWrite(28, LOW);
  }
  //controlls
  if (startStopButton.getSingleDebouncedRelease()) {
    started = !started;
    MIDI.sendControlChange(22, 127, midiChanel);
  }
  if (resetPatternButton.getSingleDebouncedRelease()) {
    ResetPattern();
    InitSequence();
    UpdateLcd();
  }
  //matrix input
  if (instrumentSelectButtons[0].getSingleDebouncedRelease()) {
    SetInstrument(0);
  }
  if (instrumentSelectButtons[1].getSingleDebouncedRelease()) {
    SetInstrument(1);
  }
  if (instrumentSelectButtons[2].getSingleDebouncedRelease()) {
    SetInstrument(2);
  }
  if (instrumentSelectButtons[3].getSingleDebouncedRelease()) {
    SetInstrument(3);
  }
  if (instrumentSelectButtons[4].getSingleDebouncedRelease()) {
    SetInstrument(4);
  }
  if (instrumentSelectButtons[5].getSingleDebouncedRelease()) {
    SetInstrument(5);
  }
  if (instrumentSelectButtons[6].getSingleDebouncedRelease()) {
    SetInstrument(6);
  }
  if (instrumentSelectButtons[7].getSingleDebouncedRelease()) {
    SetInstrument(7);
  }
  if (hitButtons[0].getSingleDebouncedRelease()) {
    SetHit(0);
  }
  if (hitButtons[1].getSingleDebouncedRelease()) {
    SetHit(1);
  }
  if (hitButtons[2].getSingleDebouncedRelease()) {
    SetHit(2);
  }
  if (hitButtons[3].getSingleDebouncedRelease()) {
    SetHit(3);
  }
  if (hitButtons[4].getSingleDebouncedRelease()) {
    SetHit(4);
  }
  if (hitButtons[5].getSingleDebouncedRelease()) {
    SetHit(5);
  }
  if (hitButtons[6].getSingleDebouncedRelease()) {
    SetHit(6);
  }
  if (hitButtons[7].getSingleDebouncedRelease()) {
    SetHit(7);
  }
  if (hitButtons[8].getSingleDebouncedRelease()) {
    SetHit(8);
  }
  if (hitButtons[9].getSingleDebouncedRelease()) {
    SetHit(9);
  }
  if (hitButtons[10].getSingleDebouncedRelease()) {
    SetHit(10);
  }
  if (hitButtons[11].getSingleDebouncedRelease()) {
    SetHit(11);
  }
  if (hitButtons[12].getSingleDebouncedRelease()) {
    SetHit(12);
  }
  if (hitButtons[13].getSingleDebouncedRelease()) {
    SetHit(13);
  }
  if (hitButtons[14].getSingleDebouncedRelease()) {
    SetHit(14);
  }
  if (hitButtons[15].getSingleDebouncedRelease()) {
    SetHit(15);
  }
}

//void CheckForSaveAndLoadInput() {
//  if (encoderButton.getSingleDebouncedPress()) {
//    if (functionMode == 5) {
//      SaveSequence(currentSavePattern);
//    }
//    if (functionMode == 6) {
//      LoadSequence(currentLoadPattern);
//    }
//  }
//}

void ResetPattern() {
  for (int i = 0; i < 8; i++) {
    for (int x = 0; x < numSteps; x ++) {
      sequence[i][x].on = false;
    }
  }
  UpdateLeds();
}

void SetInstrument(int instrument) {
  selectedInstrument = instrument;
  UpdateLeds();
  UpdateLcd();
  if (!shiftButton.isPressed()) {
    MIDI.sendNoteOn(instrumentNotes[instrument] + (octive * 8), 100, midiChanel);
    MIDI.sendNoteOff(instrumentNotes[instrument] + (octive * 8), 100, midiChanel);
  }
}

void SetHit(int x) {
  if (!shiftButton.isPressed()) {
    selectedNote = sequence[selectedInstrument][x];
    sequence[selectedInstrument][x].hidden = false;
  } else {
    sequence[selectedInstrument][x].on = !sequence[selectedInstrument][x].on;
  }
  UpdateLeds();
  UpdateLcd();
}
