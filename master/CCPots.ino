class Pot
{
  public:
    Pot(byte pin, byte command, byte control, byte channel);
    void newValue(byte command, byte value, byte channel);
    byte getValue();
    byte Pcommand;
    byte Pcontrol;
    byte Pchannel;
  private:
    byte _pin;
    byte _muxpin;
    byte _numMuxPins;
    byte _control;
    int _value;
    int _oldValue;
    bool _changed;
    byte _enablepin;
};

Pot::Pot(byte pin, byte command, byte control, byte channel)
{
  _pin = pin;
  _control = control;
  _value = analogRead(_pin);
  _value = _value >> 3;
  _oldValue = _value << 3;
  _value = _value << 3;
  Pcommand = command;
  Pcontrol = control;
  Pchannel = channel;
}

byte Pot::getValue()
{
  _value = analogRead(_pin);
  int tmp = (_oldValue - _value);
  if (tmp >= 16 || tmp <= -16) {
    _oldValue = _value >> 3;
    _oldValue = _oldValue << 3;
    return _value >> 3;
  }
  return 255;
}

void Pot::newValue(byte command, byte value, byte channel) {
  Pcommand = command;
  Pcontrol = value;
  Pchannel = channel;
}

Pot PO0(0, 0, 52, 1);
Pot PO1(1, 0, 53, 1);
Pot PO2(2, 0, 54, 1);
Pot PO3(3, 0, 55, 1);
Pot PO4(4, 0, 56, 1);
Pot PO5(5, 0, 57, 1);
Pot PO6(6, 0, 58, 1);
Pot PO7(7, 0, 59, 1);

void CheckForCCPotInput() {
  byte potmessage0 = PO0.getValue();
  if (potmessage0 != 255) MIDI.sendControlChange(PO0.Pcontrol, potmessage0, midiChanel);

  byte potmessage1 = PO1.getValue();
  if (potmessage1 != 255) MIDI.sendControlChange(PO1.Pcontrol, potmessage1, midiChanel);

  byte potmessage2 = PO2.getValue();
  if (potmessage2 != 255) MIDI.sendControlChange(PO2.Pcontrol, potmessage2, midiChanel);

  byte potmessage3 = PO3.getValue();
  if (potmessage3 != 255) MIDI.sendControlChange(PO3.Pcontrol, potmessage3, midiChanel);

  byte potmessage4 = PO4.getValue();
  if (potmessage4 != 255) MIDI.sendControlChange(PO4.Pcontrol, potmessage4, midiChanel);

  byte potmessage5 = PO5.getValue();
  if (potmessage5 != 255) MIDI.sendControlChange(PO5.Pcontrol, potmessage5, midiChanel);

  byte potmessage6 = PO6.getValue();
  if (potmessage6 != 255) MIDI.sendControlChange(PO6.Pcontrol, potmessage6, midiChanel);

  byte potmessage7 = PO7.getValue();
  if (potmessage7 != 255) MIDI.sendControlChange(PO7.Pcontrol, potmessage7, midiChanel);
}





