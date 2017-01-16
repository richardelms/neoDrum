
class Pot
{
  public:
    Pot(byte pin, byte command, byte control, byte channel);
    void muxUpdate();
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

void Pot::muxUpdate()
{
  byte temp = _muxpin;
  temp = temp << 2;
  if (_numMuxPins > 8) PORTD = PORTD & B11000011;
  else PORTD = PORTD & B11100011;
  //PORTD = PORTD & B11000011;
  PORTD = PORTD | temp;
}


byte Pot::getValue()
{
  _value = analogRead(_pin);
  int tmp = (_oldValue - _value);
  if (tmp >= 8 || tmp <= -8) {
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
//*************************************************************************

Pot PO0(0, 0, 52, 1);
Pot PO1(1, 0, 53, 1);
Pot PO2(2, 0, 54, 1);
Pot PO3(3, 0, 55, 1);
Pot POTS[] = {PO0, PO1, PO2, PO3};

void CheckForCCPotInput() {
  byte potmessage0 = PO0.getValue();
  if (potmessage0 != 255) MIDI.sendControlChange(PO0.Pcontrol, potmessage0, midiChanel);

  byte potmessage1 = PO1.getValue();
  if (potmessage1 != 255) MIDI.sendControlChange(PO1.Pcontrol, potmessage1, midiChanel);

  byte potmessage2 = PO2.getValue();
  if (potmessage2 != 255) MIDI.sendControlChange(PO2.Pcontrol, potmessage2, midiChanel);

  byte potmessage3 = PO3.getValue();
  if (potmessage3 != 255) MIDI.sendControlChange(PO3.Pcontrol, potmessage3, midiChanel);
}





