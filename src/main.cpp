#include <Arduino.h>
#include <NewPing.h>
#include <Adafruit_NeoPixel.h>


#define TRIGGER_PIN 8
#define ECHO_PIN 9
#define LED_PIN 7
#define LED_COUNT 36
#define MAX_DISTANCE 7
#define DELAY 200
#define SENSOR_COUNT 4
#define DELAY_LIGHTS 2000

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
// NewPing sensors[4];
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

NewPing sensors[4] = {
  NewPing(2, 10, MAX_DISTANCE),
  NewPing(3, 11, MAX_DISTANCE),
  NewPing(4, 12, MAX_DISTANCE),
  NewPing(5, 13, MAX_DISTANCE)
};

bool SET_GROUP[] = {false, false, false, false};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // for (int i = 0; i < 4; ++i) {
  //   sensors[i] = NewPing(TRIGGER_PINS[i], ECHO_PINS[i], MAX_DISTANCE);
  // }
  strip.begin();
  strip.show();
}



void updateLeds() {
  for (int i = 0; i < LED_COUNT; ++i) {
    if (i < 9)
      strip.setPixelColor(i, SET_GROUP[0]?255:0, 0, 0);
    else if (i < 18)
      strip.setPixelColor(i, SET_GROUP[1]?255:0, 0, 0);
    else if (i < 27)
      strip.setPixelColor(i, SET_GROUP[2]?255:0, 0, 0);
    else {
      strip.setPixelColor(i, SET_GROUP[3]?255:0, 0, 0);
    }
    
    strip.show();
  }
}

void activateStrips() {
  SET_GROUP[0] = false;
  SET_GROUP[3] = true;
  updateLeds();
  delay(DELAY);
  SET_GROUP[3] = false;
  SET_GROUP[2] = true;
  updateLeds();
  delay(DELAY);
  SET_GROUP[1] = true;
  SET_GROUP[2] = false;
  updateLeds();
  delay(DELAY);
  SET_GROUP[0] = true;
  SET_GROUP[1] = false;
  updateLeds();
  delay(DELAY);
}

void closeStrips() {
  SET_GROUP[0] = false;
  SET_GROUP[1] = false;
  SET_GROUP[2] = false;
  updateLeds();
}

void loop() {
  long distance;
  bool j = false;
  delayMicroseconds(20);
  
  // activateStrips();
  
  for (int i = 0; i < SENSOR_COUNT; ++i) {
    distance = sensors[i].ping_cm();
    if (distance > 0) {
      delay(50);
      distance = sensors[i].ping_cm();
      if (distance > 0) {
        activateStrips();
        j = true;
        // delay(DELAY_LIGHTS);
        break;
      }
    //   Serial.print("Distance ");
    // Serial.print(i);
    // Serial.print(": ");
    // Serial.print(distance);
    // Serial.print("\n");
      
    }
  }

  if (!j)  {
    closeStrips();
  }
}

