#include <TinyGPS++.h>
#include <SD.h>
#include <Wire.h>
#include <SoftwareSerial.h>

int CS = 10;
File data;
TinyGPSPlus gps;
char character;
char empty;

//Setting up connection ports
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;


//Connecting arduino to GPS module
SoftwareSerial ss(RXPin, TXPin);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(GPSBaud);
  ss.begin(GPSBaud);
  SD.begin(10);

  if (!SD.begin(10)) {
    Serial.println("Initialization failed!");
    delay(100);
    while(1);
  }

  if (!SD.exists("data.txt")) {
    data = SD.open("data.txt", FILE_WRITE);
    data.println("latitude, longitude, rating");
    delay(100);
  } else {
    data = SD.open("data.txt", FILE_WRITE);
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  
  while (ss.available() > 0) {
  // //to test location and date/time
  //   if (gps.encode(ss.read())) {
  //     displayInfo();
  //   }
  // }
  // Continuously asks for rating of sidewalks while input is not x
    do {
      Serial.println();
      Serial.println("Input x to record beginning point or e to exit:");
      while (Serial.available() == 0) {
      }
      character = Serial.read();
      Serial.print("Character: ");
      Serial.println(character);
      clearBuffer();
      switch (character) {
        case '\0':
          break;
        case 'x':
          data.print(gps.location.lat(), 8);
          data.print(",");
          data.print(gps.location.lng(), 8);
          data.print(",");
          Serial.println("Input rating of sidewalk from 0-5:");
          int rating;
          while (Serial.available() == 0) {
          }
          rating = Serial.read() - 48;
          clearBuffer();
          Serial.print("Rating: ");
          Serial.println(rating);
          data.println(rating);
          break;
        case 'e':
          Serial.println("Closing...");
          delay(100);
          data.close();
          exit(0);
          break;
        default:
          Serial.println("Invalid Input");
          break;
        }
        clearBuffer();
      } while (character != 'e' || character != 'E');
    }
}


void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}


void clearBuffer() {
  Serial.flush();
  while (Serial.available()) {
    Serial.read();
    Serial.end();
    Serial.begin(9600);
  }
}

