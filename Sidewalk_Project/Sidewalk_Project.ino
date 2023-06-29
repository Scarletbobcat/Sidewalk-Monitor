#include <TinyGPS++.h>
#include <SD.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Keyboard.h>

int CS = 10;
File data;
TinyGPSPlus gps;

//Setting up connection ports
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

//Connecting arduino to GPS module
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(GPSBaud);
  ss.begin(GPSBaud);
  pinmode(CS, OUTPUT);
  SD.begin();
  data = SD.open("test.csv", FILE_WRITE);
  // checks if opening file works and makes headers
  if (data) {
    data.println("latitude, longitude, rating")
  } else {
    Serial.println("Failed to open file")
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Input x to record beginning point or esc to exit:")
  character = inputChar();
  if (character != '\0') {
    if (character == 'x' || character == 'X') {
      data.print(gps.location.lat(), 8);
      data.print(",");
      data.print(gps.location.lng(), 8);
      data.print(",");
      Serial.println("Input rating of sidewalk from 0-5");
      rating = Serial.read();
      data.println(rating);
    } else if (character == 27) {
      data.close()
    }
  } else {
    Serial.println("Invalid Input");
  }
}

char inputChar() {
  //receives input from keyboard
  if (Serial.available > 0) {
    newChar = Serial.read();
    return newChar;
  }
  return '\0';
}