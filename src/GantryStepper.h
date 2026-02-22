#include <Arduino.h>
#include "FastAccelStepper.h"
#include "constants.h"

class GantryStepper {
    //Odemetry
    float destinationSpot = 0;

    FastAccelStepper *stepper = NULL;
    
    GantryStepper(FastAccelStepperEngine engine, uint8_t stepPin, uint8_t dirPin, uint8_t enPin);

    void setSpot();
    int getSpot();

    bool checkReachDestination();


};

