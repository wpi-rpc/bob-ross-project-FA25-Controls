#include <Arduino.h>
#include "FastAccelStepper.h"
#include <Servo.h>
#include "constants.h"

#include "esp_log.h"

#define enablePinStepper 23

#define dirPinStepper1    14
#define stepPinStepper1   27

#define dirPinStepper2    13
#define stepPinStepper2   26


#define servoPin1 25
#define servoPin2 12

struct command {
  unsigned short x,y;
  uint8_t z;
  uint8_t colour;
};

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper1 = NULL;
FastAccelStepper *stepper2 = NULL;
Servo servo1;
Servo servo2;

void setup() {
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  delay(500);
  Serial.println();
  Serial.println("=== FastAccelStepper ESP32 test ===");

  engine.init();
  Serial.println("Engine init done");

  stepper1 = engine.stepperConnectToPin(stepPinStepper1);
  stepper2 = engine.stepperConnectToPin(stepPinStepper2);

  if (!stepper1 || !stepper2) {
    Serial.println("ERROR: stepper is NULL! Check stepPinStepper and wiring.");
    while (true) {
      delay(1000);  // halt so we don't crash dereferencing a null pointer
    }
  }
  Serial.println("Stepper connected OK");

  stepper1->setDirectionPin(dirPinStepper1);
  stepper1->setEnablePin(enablePinStepper);
  stepper1->setAutoEnable(true);

  stepper2->setDirectionPin(dirPinStepper2);
  stepper2->setEnablePin(enablePinStepper);
  stepper2->setAutoEnable(true);

  stepper1->setSpeedInHz(1000);    // try a bit faster to clearly see motion
  stepper1->setAcceleration(800);

  stepper2->setSpeedInHz(500);    // try a bit faster to clearly see motion
  stepper2->setAcceleration(800);

  Serial.println("Stepper configured");

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  Serial.println("Servos configured");

}

void loop() {/*
command uart_in;
void loop() {
  if (stepper1 && !(stepper1->isRunning())) {
    stepper1->runForward();
    // Serial.println(stepper1->getCurrentPosition());
    // stepper1->move(2000);
  }
  if (stepper2 && !(stepper2->isRunning())) {
  stepper2->runBackward();

  // Serial.println(stepper1->getCurrentPosition());
  // stepper1->move(2000);
  }
  if(servo1.read() == 180){
    servo1.write(0);
  } else {
    servo1.write(180);
  }
  if(servo2.read() == 180){
    servo2.write(0);
  } else {
    servo2.write(180);
  }
  delay(1000);*/

  if (Serial2.available()) {
    Serial2.readBytes((char*)&uart_in, sizeof(uart_in));
    ESP_LOGI("uart_in", "(%d,%d,%d,%d)", uart_in.x, uart_in.y, uart_in.z, uart_in.colour);
    Serial2.write(0x06);
    ESP_LOGI("uart_out", "Acknowledged");
  }
  
  delay(1000);
}






// void setup() {
//   engine.init();
//   stepper1 = engine.stepperConnectToPin(stepPinStepper1);
//   Serial.begin(115200);
//   if (stepper1) {
//     stepper1->setDirectionPin(dirPinStepper1);
//     stepper1->setAutoEnable(true);

//     stepper1->setSpeedInHz(500);       // 500 steps/s
//     stepper1->setAcceleration(100);    // 100 steps/s²
//     stepper1->move(1000);
//   }
// }

// void loop() {
//   //Serial.println("Hello");
//   stepper1->runForward();
// }

// // put function declarations here:
// int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
//   int result = myFunction(2, 3);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }



// FastAccelStepperEngine engine;
<<<<<<< HEAD
// FastAccelStepper* stepper = nullptr;


=======
// FastAccelStepper* stepper = nullptr;
>>>>>>> uart-reception-protocol
