#include <TinyGPS++.h>
#include <SD.h>
#include <SoftwareSerial.h>

// declaration of objects and variables
File myFile;
TinyGPSPlus gps;
char character;

// setting up connection ports
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;


// connecting arduino to GPS module
SoftwareSerial ss(RXPin, TXPin);


void setup() {
  Serial.begin(9600);
  ss.begin(GPSBaud);

  if (!SD.begin(10)) {
    Serial.println("Initialization failed!");
    delay(100);
    exit(0);
  }

  // creates file if "first_data.csv" does not exist
  if (!SD.exists("data.csv")) {
    myFile = SD.open("data.csv", FILE_WRITE);
    myFile.println("latitude, longitude, rating");
    myFile.println();
  // if "data.csv" exists, goes to end of file to begin writing
  } else {
    myFile = SD.open("data.csv", FILE_WRITE);
    myFile.seek(EOF);
  }

  if (!SD.exists("data.csv")) {
    Serial.println("data.csv does not exist");
    delay(100);
    exit(0);
  }
}


void loop() {
  // always reads gps data
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }
  if (gps.location.isValid() && gps.location.isUpdated() && (gps.location.age() <= 1500) && (gps.satellites.value() > 2)) {
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
        myFile.print(gps.location.lat(), 8);
        myFile.print(",");
        myFile.print(gps.location.lng(), 8);
        myFile.print(",");
        break;

      // if v is entered, write latitude, longitude, and rating
      case 'v':
        myFile.print(gps.location.lat(), 8);
        myFile.print(",");
        myFile.print(gps.location.lng(), 8);
        myFile.print(",");
        // enter rating of sidewalk
        Serial.println("Input rating of sidewalk from 0-5:");
        int rating;
        while (Serial.available() == 0) {
        }
        rating = Serial.read() - 48;
        clearBuffer();
        Serial.print("Rating: ");
        Serial.println(rating);
        myFile.println(rating);
        break;

      // closes file and exits program
      case 'e':
        myFile.close();
        Serial.println("Closing...");
        delay(500);
        exit(0);
        break;

      // all other inputs
      default:
        Serial.println("Invalid Input");
        break;
    }
    clearBuffer();
  }
}


// // stolen from TinyGPSPlus example "Device Example"
// void displayInfo()
// {
//   Serial.print(F("Location: ")); 
//   if (gps.location.isValid())
//   {
//     Serial.print(gps.location.lat(), 6);
//     Serial.print(F(","));
//     Serial.print(gps.location.lng(), 6);
//   }
//   else
//   {
//     Serial.print(F("INVALID"));
//   }

//   Serial.print(F("  Date/Time: "));
//   if (gps.date.isValid())
//   {
//     Serial.print(gps.date.month());
//     Serial.print(F("/"));
//     Serial.print(gps.date.day());
//     Serial.print(F("/"));
//     Serial.print(gps.date.year());
//   }
//   else
//   {
//     Serial.print(F("INVALID"));
//   }

//   Serial.print(F(" "));
//   if (gps.time.isValid())
//   {
//     if (gps.time.hour() < 10) Serial.print(F("0"));
//     Serial.print(gps.time.hour());
//     Serial.print(F(":"));
//     if (gps.time.minute() < 10) Serial.print(F("0"));
//     Serial.print(gps.time.minute());
//     Serial.print(F(":"));
//     if (gps.time.second() < 10) Serial.print(F("0"));
//     Serial.print(gps.time.second());
//     Serial.print(F("."));
//     if (gps.time.centisecond() < 10) Serial.print(F("0"));
//     Serial.print(gps.time.centisecond());
//   }
//   else
//   {
//     Serial.print(F("INVALID"));
//   }

//   Serial.print("  Age: ");
//   Serial.println(gps.location.age());

//   Serial.println();
// }


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