#include <TinyGPS++.h>
#include <SD.h>
#include <SoftwareSerial.h>

// declaration of objects and variables
int CS = 10;
File data;
TinyGPSPlus gps;
char character;
char empty;

// setting up connection ports
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;


// connecting arduino to GPS module
SoftwareSerial ss(RXPin, TXPin);


void setup() {
  SD.begin(10);

  if (!SD.begin(10)) {
    Serial.println("Initialization failed!");
    delay(100);
    while(1);
  }

  // creates file if "data.csv" does not exist
  if (!SD.exists("data.csv")) {
    data = SD.open("data.csv", FILE_WRITE);
    data.println("latitude, longitude, rating");
    data.println();
    delay(100);
  // if "data.csv" exists, goes to end of file to begin writing
  } else {
    data = SD.open("data.csv", FILE_WRITE);
    data.seek(EOF);
  }

  Serial.begin(9600);
  ss.begin(GPSBaud);
}


void loop() {
  // always reads gps data
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  if (gps.location.isValid() && gps.location.isUpdated() && (gps.location.age() <= 1500)) {
    menu();
    while (Serial.available() == 0) {
    }
    character = Serial.read();
    Serial.print("Character: ");
    Serial.println(character);
    clearBuffer();

    switch (character) {

      // if x is entered, write latitude and longitude
      case 'x':
        displayInfo();
        data.print(gps.location.lat(), 8);
        data.print(",");
        data.print(gps.location.lng(), 8);
        data.print(",");
        ssBuffer();
        break;

      // if v is entered, write latitude, longitude, and rating
      case 'v':
        displayInfo();
        data.print(gps.location.lat(), 8);
        data.print(",");
        data.print(gps.location.lng(), 8);
        data.print(",");
        ssBuffer();
        // enter rating of sidewalk
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

      // closes file and exits program
      case 'e':
        data.close();
        exit(0);
        break;

      // all other inputs
      default:
        Serial.println("Invalid Input");
        ssBuffer();
        break;
    }
    clearBuffer();
  }
}


// stolen from TinyGPSPlus example "Device Example"
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

  Serial.print("  Age: ");
  Serial.println(gps.location.age());

  Serial.println();
}

// clears software serial buffer
void ssBuffer() {
  while (ss.available() > 0) {
    char dummy = ss.read();
  }
}


// clears serial buffer
void clearBuffer() {
  Serial.flush();
  while (Serial.available()) {
    Serial.read();
    Serial.end();
    Serial.begin(9600);
  }
}

// this prints the menu of the program
void menu() {
  Serial.println();
  Serial.println("x - record first point");
  Serial.println("v - record end point");
  Serial.println("e - exit program");
}