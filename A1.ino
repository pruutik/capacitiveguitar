// #include <MIDI.h>
// #include <serialMIDI.h>

#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_3_4 = CapacitiveSensor(3,4);        // 1M resistor between pins 3 & 4, pin 4 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_3_5 = CapacitiveSensor(3,5);        // 1M resistor between pins 3 & 4, pin 4 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_3_6 = CapacitiveSensor(3,6);
CapacitiveSensor   cs_3_7 = CapacitiveSensor(3,7);
CapacitiveSensor   cs_3_8 = CapacitiveSensor(3,8);
CapacitiveSensor   cs_3_9 = CapacitiveSensor(3,9);
CapacitiveSensor   cs_3_10 = CapacitiveSensor(3,10);

void setup()                    
{
  //  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  //  MIDI.begin();
   pinMode(13, OUTPUT);
   digitalWrite(13, HIGH);
   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_3_4.capacitiveSensor(30);
    long total2 =  cs_3_5.capacitiveSensor(30);
    long total3 =  cs_3_6.capacitiveSensor(30);
    long total4 =  cs_3_7.capacitiveSensor(30);
    long total5 =  cs_3_8.capacitiveSensor(30);
    long total6 =  cs_3_9.capacitiveSensor(30);
    long total7 =  cs_3_10.capacitiveSensor(30);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(analogRead(A0));
    Serial.print("\t");
    Serial.print(analogRead(A1));
    Serial.print("\t");
    Serial.print(digitalRead(13));
    Serial.print("\t");

    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.print(total2);                  // print sensor output 1
    Serial.print("\t");
    Serial.print(total3);
    Serial.print("\t");
    Serial.print(total4);
    Serial.print("\t");
    Serial.print(total5);
    Serial.print("\t");
    Serial.print(total6);
    Serial.print("\t");
    Serial.println(total7);

    delay(100);                             // arbitrary delay to limit data to serial port 
}
