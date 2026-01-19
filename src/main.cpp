#include <Arduino.h>
#include "FastAccelStepper.h"

#define dirPinStepper    14
#define enablePinStepper 23
#define stepPinStepper   27

FastAccelStepperEngine engine;
FastAccelStepper* stepper = nullptr;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== FastAccelStepper ESP32 test ===");

  engine.init();
  Serial.println("Engine init done");

  stepper = engine.stepperConnectToPin(stepPinStepper);
  if (!stepper) {
    Serial.println("ERROR: stepper is NULL! Check stepPinStepper and wiring.");
    while (true) {
      delay(1000);  // halt so we don't crash dereferencing a null pointer
    }
  }
  Serial.println("Stepper connected OK");

  stepper->setDirectionPin(dirPinStepper);
  stepper->setEnablePin(enablePinStepper);
  stepper->setAutoEnable(true);

  stepper->setSpeedInHz(1000);    // try a bit faster to clearly see motion
  stepper->setAcceleration(500);

  Serial.println("Stepper configured");
}

void loop() {
  if (stepper && !stepper->isRunning()) {
    Serial.println(stepper->getCurrentPosition());
    stepper->move(2000);
  }
  delay(10);
}
