
#include<Wire.h>
#include <MPU6050_tockn.h>

//Create thumb Sensors
int pinkie = 0; //Pinkie thumb
int finger = 0; //finger thumb
int thumb = 0; //Index thumb

int pinkie_Data = A2;
int finger_Data = A1;
int thumb_Data = A0;


MPU6050 mpu6050(Wire);


int thumb_high = 0;
int thumb_low = 0;
int finger_high = 0;
int finger_low = 0;
int pinkie_high = 0;
int pinkie_low = 0;

//Stop Caliberating the Flex Sensor when complete
bool bool_caliberate = false;

//How often to send values to the Robotic Arm
int response_time = 20;

void setup() {
  pinMode(3, OUTPUT);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
 
  Serial.begin(9600);
  delay(2000);

}
void loop() {

  mpu6050.update();

  float xAngle = mpu6050.getAngleX();
  float yAngle = mpu6050.getAngleY();
  float zAngle = mpu6050.getAngleZ();
  // //For Debugging
  // Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
  // Serial.print("	angleY : ");Serial.print(mpu6050.getAngleY());
  // Serial.print("	angleZ : ");Serial.println(mpu6050.getAngleZ());

  
  pinMode(3, HIGH); //Use basic LED as visual indicator if value being sent

  // debug_flex(); //Debug Mode on/off
  

  //Print out a value, based on the change of the XYZ co-ordinates of 1st or 2nd MPU

  // //Base Left
  if ( zAngle > 30.0) {
    Serial.print("R");
    delay(response_time);
  }

  //Base Right
  if (zAngle < -30.0) {
    Serial.print("L");
    delay(response_time);
  }

  //Claw Up
  if ( yAngle > 30.0) {
    Serial.print("U");
    delay(response_time);
  }

  //  //Claw Down
  if ( yAngle < -30.0) {
    Serial.print("G");
    delay(response_time);
  }

  //CCW
  if ( xAngle > 30.0) {
    Serial.print("t");
    delay(response_time);
  }

  //CW
  if ( xAngle < -30.0) {
    Serial.print("T");
    delay(response_time);

  }

  // read the values from Flex Sensors to Arduino
  pinkie = analogRead(pinkie_Data);
  finger = analogRead(finger_Data);
  thumb = analogRead(thumb_Data);


  //Calibrate to find upper and lower limit of the Flex Sensor
  if (bool_caliberate == false ) {
    delay(1000);

    thumb_high = (thumb * 1.15);
    thumb_low = (thumb * 0.8);

    finger_high = (finger * 1.15);
    finger_low = (finger * 0.8);

    pinkie_high = (pinkie * 1.15);
    pinkie_low = (pinkie * 0.8);

    bool_caliberate = true;
  }

  delay(response_time);

  Pinkie - Elbow UP
  if (pinkie >= pinkie_high) {
    Serial.print("P");
    delay(response_time);

  } //Elbow Down
  if (pinkie <= pinkie_low ) {
    Serial.print("p");
    delay(response_time);
  }


  //Wrist Up
  if (thumb >= thumb_high) {
    Serial.print("T");
    delay(response_time);
  }

  //Wrist Down
  if (thumb <= thumb_low) {
    Serial.print("t");
    delay(response_time);
  }

  // finger 1 - Claw Open
  if (finger >= finger_high) {
    Serial.print("F");
    delay(response_time);
  }

  if (finger <= finger_low) {
    Serial.print("f");
    delay(response_time);
  }
  else {
    delay(5);
  }
}


void debug_flex() {
  //Sends value as a serial monitor to port
  //thumb (Claw open / close)
  Serial.print("Thumb: ");
  Serial.print(thumb);
  Serial.print("\t");
  //  //thumb Params
  Serial.print("thumb High: ");
  Serial.print(thumb_high);
  Serial.print("\t");
  Serial.print("T Low: ");
  Serial.print(thumb_low);
  Serial.print("\t");

  //finger (Claw Further)
  Serial.print("finger: ");
  Serial.print(finger);
  Serial.print("\t");

  //  finger Params
  Serial.print("finger High: ");
  Serial.print(finger_high);
  Serial.print("\t");
  Serial.print("finger Low: ");
  Serial.print(finger_low);
  Serial.print("\t");

  //Pinkie (Claw Further)
  Serial.print("Pinkie: ");
  Serial.print(pinkie);
  Serial.print("\t");

  //  //Pinkie Params
  Serial.print("Pinkie High: ");
  Serial.print(pinkie_high);
  Serial.print("\t");
  Serial.print("Pinkie Low: ");
  Serial.print(pinkie_low);
  Serial.print("\t");
  Serial.println();
}