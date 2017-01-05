void MakeStep() {
  CheckForNoteOff();
//  PlayNotes();
  UpdateLeds();
}

//void PlayNotes() {
//  for (int i = 0; i < 8; i++) {
//    if (sequence[i][currentStep] == true) {
//      MIDI.sendNoteOn(instrumentNotes[i] + (octive * 8), instrumentVelocities[i], midiChanel);
//      notesOn[i] = true;
//    }
//  }
//}

void CheckForNoteOff() {
  for (int i = 0; i < sizeof(notesOn); i++) {
    if (notesOn[i]) {
      MIDI.sendNoteOff(instrumentNotes[i] + (octive * 8), 127, midiChanel);
    }
  }
}
