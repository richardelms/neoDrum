void SaveSequence(int saveSlot) {

  int address = saveSlot * totalMatrixSize;

  for (int i = 0; i < 8; i++) {
    for (int x = 0; x < numSteps; x ++) {
      if (sequence[i][x] == true) {
        EEPROM.write(address, 1);
      } else {
        EEPROM.write(address, 0);
      }
      address ++;
    }
  }

}


void LoadSequence(int saveSlot) {
  int address = saveSlot * totalMatrixSize;
  for (int i = 0; i < 8; i++) {
    for (int x = 0; x < numSteps; x ++) {
      if (EEPROM.read(address) == 1) {
        sequence[i][x] == true;
      } else {
        sequence[i][x] == false;
      }
      address ++;
    }
  }
}




