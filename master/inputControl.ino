void CheckForInputs() {
  //controlls
  if (startStopButton.getSingleDebouncedRelease()) {
    started = !started;
    MIDI.sendControlChange(22, 127, midiChanel);
  }

  if (resetPatternButton.getSingleDebouncedRelease()) {
    ResetPattern();
  }

  if (functionButton.getSingleDebouncedRelease()) {
    functionMode ++;
    if (functionMode == 4) {
      functionMode = 0;
    }
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
  CheckForEncoderInput();
}


void CheckForEncoderInput() {
  n = digitalRead(encoder0);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (firstEncode) {
      firstEncode = false;
      return;
    }
    if (digitalRead(encoder1) == LOW) {
      encoder0Pos--;
      DownInput();
    } else {
      encoder0Pos++;
      UpInput();
    }
  }
  encoder0PinALast = n;
}

void UpInput() {
  if (functionMode == 0) {
    bpm ++;
  }
  if (functionMode == 1) {
    octive ++;
    if (octive > 5) {
      octive = 5;
    }
  }
  if (functionMode == 2) {
    instrumentVelocities[selectedInstrument] ++;
    if (instrumentVelocities[selectedInstrument] > 127) {
      instrumentVelocities[selectedInstrument] = 127;
    }
  }
  if (functionMode == 3) {
    matrixBrightness += 10;
    if (matrixBrightness > 200) {
      matrixBrightness = 200;
    }
    matrix.setBrightness(matrixBrightness);
    matrix.show();
  }
  UpdateLcd();
}

void DownInput() {
  if (functionMode == 0) {
    bpm --;
    if (bpm < 1) {
      bpm = 1;
    }
  }
  if (functionMode == 1) {
    octive --;
    if (octive < -5) {
      octive = -5;
    }
  }

  if (functionMode == 2) {
    instrumentVelocities[selectedInstrument] --;
    if (instrumentVelocities[selectedInstrument] < 0) {
      instrumentVelocities[selectedInstrument] = 0;
    }
  }

  if (functionMode == 3) {
    matrixBrightness -= 10;
    if (matrixBrightness < 10) {
      matrixBrightness = 10;
    }
    matrix.setBrightness(matrixBrightness);
    matrix.show();
  }
  UpdateLcd();
}

void ResetPattern() {
  for (int i = 0; i < 8; i++) {
    for (int x = 0; x < 8; x ++) {
      sequence[i][x] = false;
    }
  }
  UpdateLeds();
}

void SetInstrument(int instrument) {
  selectedInstrument = instrument;
  UpdateLeds();
  UpdateLcd();
  MIDI.sendNoteOn(instrumentNotes[instrument] + (octive * 8), instrumentVelocities[instrument], midiChanel);
  MIDI.sendNoteOff(instrumentNotes[instrument] + (octive * 8), 100, midiChanel);
}

void SetHit(int x) {
  sequence[selectedInstrument][x] = !sequence[selectedInstrument][x];
  UpdateLeds();
}