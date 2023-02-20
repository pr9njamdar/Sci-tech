#include <SoftwareSerial.h>  // TX RX software library for bluetooth

#include <Servo.h>             // servo library
Servo base, arm, pivot, grip;  // servo name




int index = 0;
int servopos0[100] = {};
int servopos1[100] = {};
int servopos2[100] = {};
int servopos3[100] = {};

int Base_curr_pose = 90;
int Arm_curr_pose = 90;
int Pivot_curr_pose = 90;
int Grip_curr_pose = 97;



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
  base.attach(2);
  arm.attach(3);
  pivot.attach(4);
  grip.attach(5);

  base.write(Base_curr_pose);
  arm.write(Arm_curr_pose);
  pivot.write(Pivot_curr_pose);
  grip.write(Grip_curr_pose);
  Serial.begin(9600);


  myservo__base.attach(10);
  myservo__arm.attach(11);
  myservo__base.write(baseposition);
  myservo__arm.write(armposition);
}

void loop() {
  //Read from bluetooth and write to usb serial
  if (Serial.available() > 0)  // receive number from bluetooth
  {
    int data = Serial.read();  // save the received number to servopos
    Serial.println(data);      // serial print servopos current number received from bluetooth
    if (data == 1) {
      Serial.println("up");

      Arm_curr_pose += 5;
      arm.write(Arm_curr_pose);
      Serial.println(Arm_curr_pose);
    }
    if (data == 2) {
      Serial.println("down");

      Arm_curr_pose -= 5;
      arm.write(Arm_curr_pose);
      Serial.println(Arm_curr_pose);
    }
    if (data == 3) {
      Serial.println("left");

      Base_curr_pose += 5;
      base.write(Base_curr_pose);
      Serial.println(Base_curr_pose);
    }
    if (data == 4) {
      Serial.println("right");

      Base_curr_pose -= 5;
      base.write(Base_curr_pose);
      Serial.println(Base_curr_pose);
    }

    if (data == 11) {
      Serial.println("Pivot up");

      Pivot_curr_pose += 5;
      pivot.write(Pivot_curr_pose);
      Serial.println(Pivot_curr_pose);
    }
    if (data == 12) {
      Serial.println("Pivot down");

      Pivot_curr_pose -= 5;
      pivot.write(Pivot_curr_pose);
      Serial.println(Pivot_curr_pose);
    }
    if (data == 13) {
      Serial.println("Hold");

      Grip_curr_pose += 5;
      grip.write(Grip_curr_pose);
      Serial.println(Grip_curr_pose);
    }
    if (data == 14) {
      Serial.println("Relese");

      Grip_curr_pose -= 5;
      grip.write(Grip_curr_pose);
      Serial.println(Grip_curr_pose);
    }


    if (data == 200) {
      Serial.println("Recording...");
      servopos0[index] = Base_curr_pose;
      servopos1[index] = Arm_curr_pose;
      servopos2[index] = Pivot_curr_pose;
      servopos3[index] = Grip_curr_pose;
      index++;
      Serial.println("Done...");
    }
    if (data == 204) {
      while (true) {
        for (int i = 0; i < index; i++) {
          Serial.println("base");
          base.write(servopos0[i]);
          Serial.println(servopos0[i]);
          Serial.println("arm");
          arm.write(servopos1[i]);
          Serial.println(servopos1[i]);
          Serial.println("pivot");
          pivot.write(servopos2[i]);
          Serial.println(servopos2[i]);
          Serial.println("grip");
          grip.write(servopos3[i]);
          Serial.println(servopos3[i]);
          delay(1500);
        }
      }
    }
  }

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
if (armposition < 180 && armposition > 0) {
      armposition--;
    }
    if (armposition == 0) {
      armposition++;
    }
    if (armposition == 180) { armposition--; }     
    
     myservo__arm.write(armposition);
     //  Serial.println(up-down);
     Serial.println(armposition);
     delay(50);
   }

   if (down > up + 25) {
     //  Serial.println("Intenstiy is more in the upper side");
     if (armposition < 180 && armposition > 0) {
      armposition++;
    }
    if (armposition == 0) {
      armposition++;
    }
    if (armposition == 180) { armposition--; }    
     myservo__arm.write(armposition);
     //  Serial.println(down-up);
     Serial.println(armposition);
     delay(50);
   }

  if (left > right + 25) {

    if (baseposition < 180 && baseposition > 0) {
      baseposition++;
    }
    if (baseposition == 0) {
      baseposition++;
    }
    if (baseposition == 180) { baseposition--; }

    myservo__base.write(baseposition);
    //  Serial.println("Intenstiy is more on the left side");
    //  Serial.println(left-right);
    Serial.println(baseposition);
    delay(50);
  }

  if (right > left + 25) {
    if (baseposition < 180 && baseposition > 0) {
      baseposition--;
    }
    if (baseposition == 0) {
      baseposition++;
    }
    if (baseposition == 180) { baseposition--; }
    myservo__base.write(baseposition);
    Serial.println(baseposition);
    //  Serial.println("Intenstiy is more on the right side");
    //  Serial.println(right-left);
    delay(50);
  }
}
