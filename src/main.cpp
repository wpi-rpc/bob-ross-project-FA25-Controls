#include <Arduino.h>
#include "FastAccelStepper.h"
#include <Servo.h>
#include "constants.h"

#include "esp_log.h"

FastAccelStepperEngine engine = FastAccelStepperEngine();

struct command {
  unsigned short x,y;
  uint8_t z;
  uint8_t colour;
};

class Stepper {
  private:
  
    FastAccelStepper* motor = NULL;
    const int STEPPER_PIN; 
    const int DIR_PIN;
    const int EN_PIN;  

  public: 

  Stepper(const int stepper_pin, int dir_pin, int en_pin) 
    : STEPPER_PIN(stepper_pin), DIR_PIN(dir_pin), EN_PIN(en_pin) {}

  void init() {
    motor = engine.stepperConnectToPin(STEPPER_PIN);
    motor->setSpeedInHz(1000);
    motor->setAcceleration(500);
    motor->setDirectionPin(DIR_PIN);
    motor->setEnablePin(EN_PIN);
    motor->setAutoEnable(true);
  }

  int getSteps(double cm) {
    return (int)(cm * 53.0);
  }

  double getCm(int steps) {
    return (double)steps / 53.0;
  }

  void moveTo(double cm) {
    motor->moveTo(getSteps(cm), false);
  } 

  double getPosition() {
    return getCm(motor->getCurrentPosition());
  }

  void setAcceleration(double accel) { motor->setAcceleration(getSteps(accel)); }
  double getAcceleration() { return getCm(motor->getAcceleration()); }
  bool isRunning() { return motor->isRunning(); }
};

class Gantry {
  private: 
  // motor pins
  const int X_STEP_PIN = 27;
  const int X_DIR_PIN = 14;
  const int Y_STEP_PIN = 26;
  const int Y_DIR_PIN = 13;
  const int EN_PIN = 23;
  // servo pins 
  const int Z_SERVO = 12; 
  const int COLOR_SERVO = 25;
  // limit switch pins 
  const int X_LIMIT_PIN = 19;
  const int Y_LIMIT_PIN = 18;
  // motors 
  Stepper motor_x = Stepper(X_STEP_PIN, X_DIR_PIN, EN_PIN);
  Stepper motor_y = Stepper(Y_STEP_PIN, Y_DIR_PIN, EN_PIN);
  Servo servo_z = Servo();
  Servo servo_color = Servo();

  // other params 
  double max_acceleration = 1; 


  public: 

  void init() {
    motor_x.init();
    motor_y.init();
    pinMode(X_LIMIT_PIN, INPUT_PULLUP);
    pinMode(Y_LIMIT_PIN, INPUT_PULLUP);
    servo_z.attach(Z_SERVO);
    servo_color.attach(COLOR_SERVO);
    servo_color.write(125); // DOING ONE COLOR FOR NOW
  }

  bool isAtXLimit() { return digitalRead(X_LIMIT_PIN); }
  bool isAtYLimit() { return digitalRead(Y_LIMIT_PIN); }
  void setMaxAcceleration(double accel) { 
    max_acceleration = accel;
  }

  void move(double x_cm, double y_cm) {
    double dx = x_cm - motor_x.getPosition();
    double dy = y_cm - motor_y.getPosition();
    if(std::abs(dx) < 0.001 && std::abs(dy) < 0.001) 
      return;
    
    double denom = std::pow(std::pow(dx, 2.0) + std::pow(dy, 2.0), 0.5);
    double accel_dx = (max_acceleration * dx) / denom;
    double accel_dy = (max_acceleration * dy) / denom;

    motor_x.setAcceleration(accel_dx);
    motor_y.setAcceleration(accel_dy);
    motor_x.moveTo(x_cm);
    motor_y.moveTo(y_cm);
  }

  void movePen(int penDown) {
    if(penDown == 1) {
      // move down 
      servo_z.write(42);
    } else if(penDown == 0) {
      // move up
      servo_z.write(75);
    }
  }
};

Servo servo1;
Servo servo2;
Gantry gantry = Gantry();
const int xLimitPin = 19; 
const int yLimitPin = 18;


void setup() {
  Serial2.begin(115200, SERIAL_8N1, 16, 17);    
  Serial.begin(115200, SERIAL_8N1);
  Serial.println("Serial monitor set up");
  delay(500);

  Serial.println("Device initialized");
  engine.init();
  gantry.init();
  
}

command uart_in;
void loop() {
    if (Serial2.available()) {
        Serial2.readBytes((char*)&uart_in, sizeof(uart_in));
        ESP_LOGI("uart_in", "(%d,%d,%d,%d)", uart_in.x, uart_in.y, uart_in.z, uart_in.colour);
        Serial2.write(0x06);
        ESP_LOGI("uart_out", "Acknowledged");
        char buffer[100];
        sprintf(buffer, "<x,y,z,c> = (%d, %d, %d, %d)", uart_in.x, uart_in.y, uart_in.z, uart_in.colour);
        gantry.movePen(uart_in.z);
        double c = 60.0;
        gantry.move(uart_in.x / c, uart_in.y / c);
        // 2. Print the buffer itself
        Serial.println(buffer);
    } else {
        delay(100);
    }

    Serial.println(digitalRead(yLimitPin));
}