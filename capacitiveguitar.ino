#include <MIDI.h>
#include <CapacitiveSensor.h>

#define THRESHOLD 120
#define DEADZONE 80
#define BUTTONPIN 13

MIDI_CREATE_DEFAULT_INSTANCE();

CapacitiveSensor   cs_3_4 = CapacitiveSensor(3,4);        // 1M resistor between pins 3 & 4, pin 4 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_3_5 = CapacitiveSensor(3,5);        // 1M resistor between pins 3 & 4, pin 4 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_3_6 = CapacitiveSensor(3,6);
CapacitiveSensor   cs_3_7 = CapacitiveSensor(3,7);
CapacitiveSensor   cs_3_8 = CapacitiveSensor(3,8);
CapacitiveSensor   cs_3_9 = CapacitiveSensor(3,9);
CapacitiveSensor   cs_3_10 = CapacitiveSensor(3,10);

bool C = false;
bool D = false;
bool E = false;
bool F = false;
bool G = false;
bool A = false;
bool B = false;

bool buttonpressed = false;
int mode = 0;
bool playsound = false;
int velocity = 0;
// int pitchbend = 0;

int offset = 0;
int lastoffset = 0;

void setup()                    
{
   pinMode(BUTTONPIN, OUTPUT);
   digitalWrite(BUTTONPIN, HIGH);
   MIDI.begin();
   Serial.begin(115200);
}

void MIDImessage(byte status, byte data1, byte data2)
{
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}

void playNote(CapacitiveSensor& pad, int note, bool& key){
  if(playsound){
    if(pad.capacitiveSensor(30)>THRESHOLD){
      if(!key){
        key = true;
        MIDI.sendNoteOn(note,velocity,1);
      }
    }else if(key){
      key = false;
      MIDI.sendNoteOff(note,0,1);
    }
  }else if(key){
    key = false;
    MIDI.sendNoteOff(note,0,1);
  }
}

void readjoystick(){
  int X = analogRead(A1);
  int Y = analogRead(A0);

  velocity = abs(X+Y-1024);

  if(abs(X+Y-1024)>DEADZONE){
    playsound = true;
  }else{
    if(playsound){
      // MIDI.sendPitchBend(0,1);
      // MIDI.sendControlChange(0,0,1);
    }
    playsound = false;
    return;
  }

  switch(mode){
    case 1:
      MIDI.sendPitchBend((int)map(X,0,1024,MIDI_PITCHBEND_MIN,MIDI_PITCHBEND_MAX),1);
      break;
    case 2:
      offset = (X - 256)/40;
      break;
    case 3:
      // MIDI.sendControlChange(1,map(X,0,512,0,127),1);
      break;

    default:
      break;
  }
}

void loop()                    
{
  // MIDI.read();

  int buttonstate = digitalRead(BUTTONPIN);
  if(!buttonpressed && !buttonstate){
    buttonpressed = !buttonstate;
    mode++;
    if(mode==0){
      offset=0;
    }
    if(mode==3){
      MIDImessage(177, 0, 1);
      delay(100);
      MIDImessage(177, 0, 100);
      // MIDI.sendControlChange(1,10,1);
      // MIDI.sendControlChange(1,1,1);
    }
    if(mode>2)mode = 0;
  }else if(buttonpressed && buttonstate){
    buttonpressed = !buttonstate;
  }else{
    buttonpressed = !buttonstate;
  }

  readjoystick();

  if(offset!=lastoffset){
    MIDI.sendNoteOff(72+lastoffset,0,1);
    MIDI.sendNoteOff(74+lastoffset,0,1);
    MIDI.sendNoteOff(76+lastoffset,0,1);
    MIDI.sendNoteOff(77+lastoffset,0,1);
    MIDI.sendNoteOff(79+lastoffset,0,1);
    MIDI.sendNoteOff(81+lastoffset,0,1);
    MIDI.sendNoteOff(83+lastoffset,0,1);
  }

  lastoffset=offset;

  playNote(cs_3_4,72+offset,C);
  playNote(cs_3_5,74+offset,D);
  playNote(cs_3_6,76+offset,E);
  playNote(cs_3_7,77+offset,F);
  playNote(cs_3_8,79+offset,G);
  playNote(cs_3_9,81+offset,A);
  playNote(cs_3_10,83+offset,B);
}
