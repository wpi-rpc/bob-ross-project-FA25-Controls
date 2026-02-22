#include <Arduino.h>
#include "FastAccelStepper.h"
#include "constants.h"

/**
 * @brief Represents a stepper motor for the Bob Ross project gantry.
 */
class GantryStepper {
    private: 

    //Odemetry
    float destinationSpot = 0;
    FastAccelStepper *stepper = NULL;

    public: 

    /**
     * @brief Creates a GantryStepper instance
     */
    GantryStepper(FastAccelStepperEngine engine, uint8_t stepPin, uint8_t dirPin, uint8_t enPin);
    
    void setSpot();
    int getSpot();
    bool checkReachDestination();
};

