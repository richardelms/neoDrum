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

  if (!functionButton.isPressed())
  {
    functionMode ++;
    if (functionMode == numFunctions) {
      functionMode = 0;
    }
    UpdateLcd();
    return;
  }

  switch (functionMode) {
    case 0:
      bpm ++;
      break;
    case 1:
      sequence[selectedNote.instrument][selectedNote.sequencePosition].velocity ++;
      if (sequence[selectedNote.instrument][selectedNote.sequencePosition].velocity > 127) {
        sequence[selectedNote.instrument][selectedNote.sequencePosition].velocity = 127;
      }
      break;
    case 2:
      sequence[selectedNote.instrument][selectedNote.sequencePosition].SwingAmount ++;
      if (sequence[selectedNote.instrument][selectedNote.sequencePosition].SwingAmount > patternScale) {
        sequence[selectedNote.instrument][selectedNote.sequencePosition].SwingAmount = patternScale;
      }
      break;
    case 3:
      octive ++;
      if (octive > 5) {
        octive = 5;
      }
      break;
    case 4:
      patternScale /= 2;
      if (patternScale < 6) {
        patternScale = 6;
      }
      break;
    case 5:
      master = !master;
      break;
    case 6:
      matrixBrightness += 10;
      if (matrixBrightness > 250) {
        matrixBrightness = 250;
      }
      matrix.setBrightness(matrixBrightness);
      matrix.show();
      break;
  }
  UpdateLcd();
}

void DownInput() {

  if (!functionButton.isPressed())
  {
    functionMode --;
    if (functionMode < 0) {
      functionMode = numFunctions - 1;
    }
    UpdateLcd();
    return;
  }

  switch (functionMode) {
    case 0:
      bpm ++;
      break;
    case 1:
      sequence[selectedNote.instrument][selectedNote.sequencePosition].velocity --;
      if (sequence[selectedNote.instrument][selectedNote.sequencePosition].velocity < 0) {
        sequence[selectedNote.instrument][selectedNote.sequencePosition].velocity = 0;
      }
      break;
    case 2:
      sequence[selectedNote.instrument][selectedNote.sequencePosition].SwingAmount --;
      if (sequence[selectedNote.instrument][selectedNote.sequencePosition].SwingAmount < (0 - patternScale)) {
        sequence[selectedNote.instrument][selectedNote.sequencePosition].SwingAmount = (0 - patternScale);
      }
      break;
    case 3:
      octive --;
      if (octive < -5) {
        octive = -5;
      }
      break;
    case 4:
      patternScale *= 2;
      if (patternScale > 192) {
        patternScale = 192;
      }
      break;
    case 5:
      master = !master;
      break;
    case 6:
      matrixBrightness -= 10;
      if (matrixBrightness < 10) {
        matrixBrightness = 10;
      }
      matrix.setBrightness(matrixBrightness);
      matrix.show();
      break;
  }
  UpdateLcd();
}
