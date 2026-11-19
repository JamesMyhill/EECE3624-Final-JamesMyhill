/*
  
*/

#include <SoftwareSerial.h>
#include <Wire.h>
#include <ZumoShield.h>

#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     200

ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int speed_amplifier = 1;

//receiver
unsigned char incomingByte;     
// HC-05
SoftwareSerial bluetooth(2,4);  // RX, TX


void waitForButtonAndCountDown()
{
  button.waitForButton();
  // play audible countdown
  for (int i = 0; i < 3; i++)
  {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }
  delay(1000);
  buzzer.playNote(NOTE_G(4), 500, 15);
  delay(1000);
}

void setup() {
  //Serial.begin(9600);
  //Serial.println("Serial setup complete.");
  // Setup the HC-05 bluetooth device
  // (HC)=(Uno).  VCC=5V, GND=GND, TX=RX(pin2),
  // RX=DNC! (possible damage if 5V Uno TX drives to HC-05)
  bluetooth.begin(9600);
}


void loop() {
  if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }
  //delay(20);
  if (bluetooth.available()) {  
    incomingByte = (unsigned char) bluetooth.read();
    //Serial.write(incomingByte);
    if (incomingByte == 'S'){
    if(speed_amplifier == 1){
      speed_amplifier++;
    }else{
      speed_amplifier = 1;
    }
  }else if (incomingByte == 'U'){
    motors.setSpeeds(FORWARD_SPEED*speed_amplifier, FORWARD_SPEED*speed_amplifier);
  }else if(incomingByte == 'D'){
    motors.setSpeeds(-REVERSE_SPEED*speed_amplifier, -REVERSE_SPEED*speed_amplifier);
  }else if(incomingByte == 'R'){
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
  }else if(incomingByte == 'L'){
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
  }else if(incomingByte == 'X'){
    motors.setSpeeds(0,0);
  }
  }

}









