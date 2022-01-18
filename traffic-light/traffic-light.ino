#include "StateMachine.h";
const int RED_PIN = 2;
const int YELLOW_PIN = 1;
const int GREEN_PIN = 4;
const int BUTTON_PIN = 3;

const int STATE_RED = 0;
const int STATE_GREEN = 1;
const int STATE_REDYELLOW = 2;
const int STATE_YELLOW = 3;
const int STATE_YELLOW2 = 5;
const int STATE_NOLIGHT = 4;

const int MODE_FLASH_YELLOW = 0;
const int MODE_AUTOMATIC = 1;
const int MODE_MANUAL = 2;

const int YELLOW_FLASH_INTERVAL = 2000;

int mode = MODE_AUTOMATIC;
int automaticStateDurations[4];

StateMachine sm(STATE_RED);

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);

  sm.addTransition(STATE_RED, STATE_REDYELLOW);
  sm.addTransition(STATE_REDYELLOW, STATE_GREEN);
  sm.addTransition(STATE_GREEN, STATE_YELLOW);
  sm.addTransition(STATE_YELLOW, STATE_RED);
  sm.addTransition(STATE_YELLOW2, STATE_NOLIGHT);
  sm.addTransition(STATE_NOLIGHT, STATE_YELLOW2);

  automaticStateDurations[STATE_RED] = 5000;
  automaticStateDurations[STATE_REDYELLOW] = 1500;
  automaticStateDurations[STATE_GREEN] = 5000;
  automaticStateDurations[STATE_YELLOW] = 1500;
}

void setYellow() {
  digitalWrite(YELLOW_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
}

void setRed() {
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
}

void setRedYellow() {
  digitalWrite(YELLOW_PIN, HIGH);
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
}

void setGreen() {
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
}

void setOff() {
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
}

long currentTimingMillis = 0;

void automaticStateHandler() {
  if (millis() - currentTimingMillis >= automaticStateDurations[sm.getState()]) {
    sm.transition();
    currentTimingMillis = millis();
  }
}

void flashYellowStateHandler() {
  if (millis() - currentTimingMillis >= YELLOW_FLASH_INTERVAL) {
    sm.transition();
    currentTimingMillis = millis();
  }
}

void manualState() {
  sm.transition();
}


long buttonNotPressedMS = 0;

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  long currentMillis = millis();

  if (buttonState == HIGH) {
    if (currentMillis - buttonNotPressedMS >= 4000) {
      mode = MODE_FLASH_YELLOW;
      sm.setState(STATE_YELLOW2);
    } else if (currentMillis - buttonNotPressedMS >= 2000) {
      mode = MODE_AUTOMATIC;
      sm.setState(STATE_RED);
    } else if (currentMillis - buttonNotPressedMS > 100) {
      if (mode != MODE_MANUAL) {
        sm.setState(STATE_RED);
        mode = MODE_MANUAL;
      } else {
        manualState();
      }

    }
  }

  if (buttonState == HIGH)
  {
    buttonNotPressedMS = currentMillis;
  }

  switch (mode) {
    case MODE_AUTOMATIC:
      automaticStateHandler();
      break;
    case MODE_FLASH_YELLOW:
      flashYellowStateHandler();
      break;
  }

  switch (sm.getState()) {
    case STATE_RED:
      setRed();
      break;
    case STATE_YELLOW:
    case STATE_YELLOW2:
      setYellow();
      break;
    case STATE_REDYELLOW:
      setRedYellow();
      break;
    case STATE_GREEN:
      setGreen();
      break;
    case STATE_NOLIGHT:
      setOff();
      break;
  }





}
