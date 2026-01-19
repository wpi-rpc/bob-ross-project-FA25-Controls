#include <Arduino.h>
#include <FastAccelStepper.h>

#include "FastAccelStepper.h"
#include "AVRStepperPins.h" // Only required for AVR controllers

#define dirPinStepper    14
#define enablePinStepper 6
#define stepPinStepper   12

// If using an AVR device use the definitons provided in AVRStepperPins
//    stepPinStepper1A
//
// or even shorter (for 2560 the correct pin on the chosen timer is selected):
//    stepPinStepperA

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper* stepper = NULL;

void setup() {
   engine.init();
   stepper = engine.stepperConnectToPin(stepPinStepper);
   Serial.begin(115200);
   if (stepper) {
      stepper->setDirectionPin(dirPinStepper);
      //stepper->setEnablePin(enablePinStepper);
      stepper->setAutoEnable(true);

      stepper->setSpeedInHz(500);       // 500 steps/s
      stepper->setAcceleration(100);    // 100 steps/s²
      stepper->move(1000);
   }
}

void loop() {
  Serial.println("Hello");
}