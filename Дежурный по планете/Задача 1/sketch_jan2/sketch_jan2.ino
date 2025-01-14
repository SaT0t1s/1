
#include <Arduino.h>

const int led1 = 5; // Пин для первого светодиода
const int led2 = 6; // Пин для второго светодиода

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('#');
    parseCommand(command);
  }
}

void parseCommand(String command) {
  int firstSemicolon = command.indexOf(';');
  int secondSemicolon = command.indexOf(';', firstSemicolon + 1);

  String cmd = command.substring(0, firstSemicolon);
  String arg1 = command.substring(firstSemicolon + 1, secondSemicolon);
  String arg2 = command.substring(secondSemicolon + 1);

  if (cmd == "setBrightINT") {
    int led = arg1.toInt();
    int brightness = arg2.toInt();
    setBrightnessINT(led, brightness);
  } else if (cmd == "setBrightFLOAT") {
    int led = arg1.toInt();
    float brightness = arg2.toFloat();
    setBrightnessFLOAT(led, brightness);
  } else if (cmd == "launchAnimation") {
    String animationType = arg1;
    unsigned long duration = arg2.toInt();
    launchAnimation(animationType, duration);
  }
}

void setBrightnessINT(int led, int brightness) {
  if (led == 1) {
    analogWrite(led1, brightness);
  } else if (led == 2) {
    analogWrite(led2, brightness);
  }
}

void setBrightnessFLOAT(int led, float brightness) {
  int brightnessINT = brightness * 255;
  if (led == 1) {
    analogWrite(led1, brightnessINT);
  } else if (led == 2) {
    analogWrite(led2, brightnessINT);
  }
}

void launchAnimation(String animationType, unsigned long duration) {
  unsigned long startTime = millis();
  while (millis() - startTime < duration) {
    if (animationType == "separately") {
      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);
      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);
    } else if (animationType == "together") {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      delay(500);
    }
  }
}
