//using namespace midi;

void CheckForPulse() {
  if (!started || !master) {
    return;
  }
  unsigned long currentMillis = millis();
    if (currentMillis - lastStep >= 60000 / ((bpm * 2) / patternScale)) {
      lastStep = currentMillis;
      SendClockTick();
  } 
}

void SendClockTick(){
  HandleClockTick();
  //SEND CLOCK TICK TO MIDI OUT
//  MIDI.sendRealTime(Clock);
  }
