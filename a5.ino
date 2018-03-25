int buzz = 9;
#include <Adafruit_NeoPixel.h>
#define PIN 6

#include <Wire.h>
#include "Adafruit_SI1145.h"

Adafruit_SI1145 uv = Adafruit_SI1145();
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzz, OUTPUT);
  strip.begin();
  strip.show();

  //Serial.begin(9600);
  Serial.println("Adafruit SI1145 test");
  if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }
  Serial.println("OK!");
  

}

//if UV or temperature > 100, then buzz
//if no UV, or temperature is between 60 and 80, and dark, then lights

void loop() {
  int data = analogRead(A9);;
  Serial.println(data);
  strip.setPixelColor(1, strip.Color(0,150,0));
  strip.show();
  
  // put your main code here, to run repeatedly:
 

  Serial.println("===================");
  Serial.print("Vis: "); Serial.println(uv.readVisible());
  Serial.print("IR: "); Serial.println(uv.readIR());
  
  // Uncomment if you have an IR LED attached to LED pin!
  //Serial.print("Prox: "); Serial.println(uv.readProx());

  float UVindex = uv.readUV();
  // the index is multiplied by 100 so to get the
  // integer index, divide by 100!
  UVindex /= 100.0;  
  Serial.print("UV: ");  Serial.println(UVindex);
  delay(1000);

  if (UVindex >= 2){
    digitalWrite(buzz, HIGH);
  } else {
    digitalWrite(buzz, LOW);
  }
}

