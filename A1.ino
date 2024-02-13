#include <MIDI.h>
#include <CapacitiveSensor.h>

#define THRESHOLD 120
#define DEADZONE 80

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

void setup()                    
{
   pinMode(13, OUTPUT);
   digitalWrite(13, HIGH);
   MIDI.begin();
   Serial.begin(115200);
}

void playNote(CapacitiveSensor& pad, int note, bool& key){
  if(abs(analogRead(A0)+analogRead(A1)-1024)>DEADZONE){
    if(pad.capacitiveSensor(30)>THRESHOLD){
      if(!key){
        key = true;
        MIDI.sendNoteOn(note,abs(analogRead(A0)+analogRead(A1)-1024)/8,1);
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

void loop()                    
{
    playNote(cs_3_4,72,C);
    playNote(cs_3_5,74,D);
    playNote(cs_3_6,76,E);
    playNote(cs_3_7,77,F);
    playNote(cs_3_8,79,G);
    playNote(cs_3_9,81,A);
    playNote(cs_3_10,83,B);
}
