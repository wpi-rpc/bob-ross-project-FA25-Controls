#include "GantryStepper.h"

GantryStepper :: GantryStepper(FastAccelStepperEngine engine, uint8_t stepPin, uint8_t dirPin, uint8_t enPin) {
    stepper = engine.stepperConnectToPin(stepPin);
    
    if (!stepper) {
        Serial.println("ERROR: stepper is NULL! Check stepPinStepper and wiring.");
        while (true) {
            delay(1000);  // halt so we don't crash dereferencing a null pointer
        }
    }
    
    stepper->setDirectionPin(dirPin);
    stepper->setEnablePin(enPin);
    stepper->setAutoEnable(true);

    stepper->setSpeedInHz(1000);    // try a bit faster to clearly see motion
    stepper->setAcceleration(800);
}

bool GantryStepper :: checkReachDestination(){
    float currentSpot = stepper->getCurrentPosition() * stepsToAnlge * wheelRadius;
    return abs(destinationSpot - currentSpot) <= 0.005;
}