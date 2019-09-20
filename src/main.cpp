#include <Arduino.h>
#include <NewPing.h>
#include <Adafruit_NeoPixel.h>


#define TRIGGER_PIN 8
#define ECHO_PIN 9
#define LED_PIN 7
#define LED_COUNT 27
#define MAX_DISTANCE 15
#define DELAY 200
#define SENSOR_COUNT 4

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
// NewPing sensors[4];
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

NewPing sensors[4] = {
  NewPing(2, 10, MAX_DISTANCE),
  NewPing(3, 11, MAX_DISTANCE),
  NewPing(4, 12, MAX_DISTANCE),
  NewPing(5, 13, MAX_DISTANCE)
};

int SET_GROUP[] = {0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  // for (int i = 0; i < 4; ++i) {
  //   sensors[i] = NewPing(TRIGGER_PINS[i], ECHO_PINS[i], MAX_DISTANCE);
  // }
  strip.begin();
  strip.show();
}

void ledBlink() {
  digitalWrite(LED_PIN, HIGH);
  // delayMicroseconds(500000);
  digitalWrite(LED_PIN, LOW);
  // delayMicroseconds(500000);
}

void disco() {
  for (int i = 0; i < LED_COUNT; ++i) {
    if (i > 0)
      strip.setPixelColor(i - 1, 0, 0, 0);
    strip.setPixelColor(i, 255, 0, 0);
    strip.show();
    delayMicroseconds(5000);
  }

  strip.setPixelColor(26, 0, 0, 0);
  strip.show();
}

void updateLeds() {
  for (int i = 0; i < LED_COUNT; ++i) {
    if (i < 9)
      strip.setPixelColor(i, SET_GROUP[0], 0, 0);
    else if (i < 18)
      strip.setPixelColor(i, SET_GROUP[1], 0, 0);
    else
    {
      strip.setPixelColor(i, SET_GROUP[2], 0, 0);
    }
    
    strip.show();
  }
}

void activateStrips() {
  SET_GROUP[0] = 0;
  SET_GROUP[2] = 255;
  updateLeds();
  delay(DELAY);
  SET_GROUP[1] = 255;
  SET_GROUP[2] = 0;
  updateLeds();
  delay(DELAY);
  SET_GROUP[0] = 255;
  SET_GROUP[1] = 0;
  updateLeds();
  delay(DELAY);
}

void closeStrips() {
  SET_GROUP[0] = 0;
  SET_GROUP[1] = 0;
  SET_GROUP[2] = 0;
  updateLeds();
}

void loop() {
  long distance;
  int j = 0;
  delayMicroseconds(20);
  
  // activateStrips();
  
  for (int i = 0; i < SENSOR_COUNT; ++i) {
    // Serial.print("Distance ");
    // Serial.print(i);
    // Serial.print(": ");
    // Serial.print(sensors[i].ping_cm());
    // Serial.print("\n");
    if (sensors[i].ping_cm() > 0) {
      activateStrips();
      j = 1;
    }
  }

  if (!j) closeStrips();
}

