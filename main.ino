#include <Servo.h>  // include the Servo library

Servo myservo;   // create a servo object
int potpin = 0;  // select the input pin for the potentiometer
int val;
int val1;  // variable to store the value coming from the sensor
int servopos[100] = {};

Servo myservo1;   // create a servo object
int potpin1 = 1;  // select the input pin for the potentiometer
int val01;
int val11;  // variable to store the value coming from the sensor
int servopos1[100] = {};

Servo myservo2;   // create a servo object
int potpin2 = 2;  // select the input pin for the potentiometer
int val02;
int val12;  // variable to store the value coming from the sensor
int servopos2[100] = {};

Servo myservo3;   // create a servo object
int potpin3 = 3;  // select the input pin for the potentiometer
int val03;
int val13;  // variable to store the value coming from the sensor
int servopos3[100] = {};

int prev1 = 0;
int prev2 = 0;
int prev3 = 0;
int prev4 = 0;

int buffer = 20;
int count = 0;



// solar tracker elements initialization
Servo myservo__base, myservo__arm;

int baseposition = 90, armposition = 90;

int up_left = A9;
int up_right = A10;
int down_left = A8;
int down_right = A11;

int up_left_value;
int up_right_value;
int down_left_value;
int down_right_value;

int up;
int down;
int right;
int left;


void setup() {
  Serial.begin(9600);
  myservo.attach(11);
  myservo1.attach(10);
  myservo2.attach(9);
  myservo3.attach(8);
  // solar Tracker

  myservo__base.attach(6);
  myservo__arm.attach(5);
  myservo__base.write(baseposition);
  myservo__arm.write(armposition);
}

void loop() {

  //________Solar Tracker code ____________
  up_right_value = analogRead(up_right);
  up_left_value = analogRead(up_left) + 79;
  down_right_value = analogRead(down_right) + 51;
  down_left_value = analogRead(down_left);
  //    Serial.println("upright :");
  //    Serial.println(up_right_value);
  //    Serial.println("downright :");
  //  Serial.println(down_right_value);
  //    Serial.println("downleft :");
  //    Serial.println(down_left_value);
  //    Serial.println("upleft :");
  //  Serial.println(up_left_value);
  //   delay(5000);
  up = (up_right_value + up_left_value) / 2;
  down = (down_right_value + down_left_value) / 2;
  right = (up_right_value + down_right_value) / 2;
  left = (up_left_value + down_left_value) / 2;
  if (up > down + 25) {
    //  Serial.println("Intenstiy is more in the down side");
    armposition--;
    myservo__arm.write(armposition);
    //  Serial.println(up-down);
    Serial.println(armposition);
    delay(50);
  }
  if (down > up + 25) {
    //  Serial.println("Intenstiy is more in the upper side");
    armposition++;
    myservo__arm.write(armposition);
    //  Serial.println(down-up);
    Serial.println(armposition);
    delay(50);
  }
  if (left > right + 25) {

    baseposition++;
    myservo__base.write(baseposition);
    //  Serial.println("Intenstiy is more on the left side");
    //  Serial.println(left-right);
    Serial.println(baseposition);
    delay(50);
  }
  if (right > left + 25) {
    baseposition--;
    myservo__base.write(baseposition);
    Serial.println(baseposition);
    //  Serial.println("Intenstiy is more on the right side");
    //  Serial.println(right-left);
    delay(50);
  }


  // ____________Robotic Arm ____________Code.


  val = analogRead(potpin);
  val1 = map(val, 188, 1024, 180, 0);
  if (val1 - prev1 > buffer || val1 - prev1 < -buffer) {
    myservo.write(val1);
    delay(25);
    prev1 = val1;
  } else {
    myservo.write(prev1);
    delay(25);
  }


  val01 = analogRead(potpin1);
  val11 = map(val01, 0, 1024, 0, 180);
  if (val11 - prev2 > buffer || val1 - prev2 < -buffer) {
    myservo1.write(val11);
    delay(25);
    prev2 = val11;
  } else {
    myservo1.write(prev2);
    delay(25);
  }


  val02 = analogRead(potpin2);
  val12 = map(val02, 0, 1024, 180, 0);
  if (val12 - prev3 > buffer || val12 - prev3 < -buffer) {
    prev3 = val12;
    myservo2.write(val12);
    delay(25);
  } else {
    myservo2.write(prev3);
    delay(25);
  }


  val03 = analogRead(potpin3);
  val13 = map(val03, 0, 1024, 0, 180);
  if (val13 - prev4 > buffer || val13 - prev4 < -buffer) {
    myservo3.write(val13);
    delay(25);
    prev4 = val13;
  } else {
    myservo3.write(prev4);
    delay(25);
  }


  if (Serial.available()) {
    int state = Serial.parseInt();

    if (state == 1) {

      Serial.println("Servo 0 position");
      Serial.println(val1);

      servopos[count] = val1;
      Serial.println(count);
      Serial.println(servopos[count]);

      Serial.println("Servo 1 position");
      Serial.println(val11);
      Serial.println("Servo 1 analog position");
      Serial.println(val01);
      servopos1[count] = val11;
      Serial.println(count);
      Serial.println(servopos1[count]);

      Serial.println("Servo 2 position");
      Serial.println(val12);
      servopos2[count] = val12;
      Serial.println(count);
      Serial.println(servopos2[count]);

      count = count + 1;
    }
    if (state == 6) {
      while (true) {


        for (int i = 0; i < count; i++) {
          myservo.write(servopos[i]);
          myservo1.write(servopos1[i]);
          myservo2.write(servopos2[i]);
          delay(1000);
        }
      }
    }
  }
}
