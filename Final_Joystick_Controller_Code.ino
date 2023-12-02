
#include "U8glib.h"
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SoftwareSerial.h>
U8GLIB_SH1106_128X64 oled(U8G_I2C_OPT_NONE);

int joystickX1 = A0; // Analog pin for joystick 1 X axis
int joystickY1 = A1; // Analog pin for joystick 1 Y axis
int joystickX2 = A2; // Analog pin for joystick 2 X axis
int joystickY2 = A3; // Analog pin for joystick 2 Y axis

int x1Value, y1Value, x2Value, y2Value;

char state = 0;

int response_time = 2;

MPU6050 mpu6050(Wire);

void setup(void) {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  Wire.begin();

  mpu6050.calcGyroOffsets(true);
  delay(2000);
}

void loop(void) {

  x1Value = analogRead(joystickX1);
  y1Value = analogRead(joystickY1);
  x2Value = analogRead(joystickX2);
  y2Value = analogRead(joystickY2);

  mpu6050.update();
  // For Debugging
  // Serial.print("x1: ");
  // Serial.print(x1Value);
  // Serial.print("\t");
  // Serial.print("y1: ");
  // Serial.print(y1Value);
  // Serial.print("\t");
  // Serial.print("x2: ");
  // Serial.print(x2Value);
  // Serial.print("\t");
  // Serial.print("y2: ");
  // Serial.print(y2Value);
  // Serial.println();

  float xAngle = mpu6050.getAngleX();
  float yAngle = mpu6050.getAngleY();

  // Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
  // Serial.print("	angleY : ");Serial.print(mpu6050.getAngleY());
  // Serial.print("	angleZ : ");Serial.println(mpu6050.getAngleZ());

  // Move Left
  if (yAngle > 25.0) {
    // Serial.print("L");
    state = 'L';
    delay(response_time);
  }

  //Move Right
  if ( yAngle < -25.0) {
    // Serial.print("R");
    state = 'R';
    delay(response_time);
  }

  // //Claw Up
  if (xAngle > 25.0) {
    // Serial.print("G");
    state = 'G';
    delay(response_time);
  }

  //  //Claw Down
  if ( xAngle < -25.0) {
    // Serial.print("U");
    state = 'U';
    delay(response_time);
  }

  // //  //Move right
  if (x1Value > 650) {
    // Serial.print("C");
    state = 'C';
    delay(response_time);
  }

  //  //Move left --- Right Hand
  if ( x1Value < 350) {
    // Serial.print("c");
    state = 'c';
    delay(response_time);
  }

  if (y2Value > 650) {
    // Serial.print("P");
    state = 'P';
    delay(response_time);

  }
  if (y2Value < 350 ) {
    // Serial.print("p");
    state = 'p';
    delay(response_time);
  }
  // // finger 1 - Claw Bend/Open
  if (y1Value < 350) {
    // Serial.print("F");
    state = 'F'; // open gripper
    delay(response_time);
  }

  if (y1Value > 650) {
    // Serial.print("f");
    state = 'f'; // close gripper
    delay(response_time);
  }


  // // thumb 1 - thumb (Base Rotation)
  if (x2Value < 350 ) {
    // Serial.print("T"); 
    state = 'T';// stepper left
    delay(response_time);
  }
  

  if (x2Value > 650) {
    // Serial.print("t");
    state = 't'; // stepper right
    delay(response_time);
  }
  

  Serial.println(state);
  

  
  // page1();
  updateDisplay();
  state = 'X';
   // Update the OLED display with the state
  // delay(50);
}

void updateDisplay() {
  oled.firstPage();
  do {
    oled.setFont(u8g_font_osr29r);
    oled.setPrintPos(50, 50);
    oled.print(state);
  } while (oled.nextPage());
}

