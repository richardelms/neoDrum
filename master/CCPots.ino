void CheckForCCPotInput() {
  int sector0 = CCPot0.getSector();
  if (lastCCPotValues[0] != sector0) {
    lastCCPotValues[0] = sector0;
    MIDI.sendControlChange(CCPotMidiNotes[0], sector0, midiChanel);
  }
  int sector1 = CCPot1.getSector();
  if (lastCCPotValues[1] != sector1) {
    lastCCPotValues[1] = sector1;
    MIDI.sendControlChange(CCPotMidiNotes[1], sector1, midiChanel);
  }
  int sector2 = CCPot2.getSector();
  if (lastCCPotValues[2] != sector2) {
    lastCCPotValues[2] = sector2;
    MIDI.sendControlChange(CCPotMidiNotes[2], sector2, midiChanel);
  }
  int sector3 = CCPot3.getSector();
  if (lastCCPotValues[3] != sector3) {
    lastCCPotValues[3] = sector3;
    MIDI.sendControlChange(CCPotMidiNotes[3], sector3, midiChanel);
  }
}


