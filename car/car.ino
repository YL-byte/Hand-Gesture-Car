#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

//RF Receiver Data-------------------------------------------------------------------------------------
RH_ASK driver(2000, 2, 2, 0);
uint8_t buf[2];
bool roll_active = false, roll_positive = false, pitch_active = false, pitch_positive = false;
int data_received = 0; //This var contains the data received by the RF transmittor
int counter_to_stop = 0;//Counts the number of failed attempts to read RF; When successful attempt happens the counter will reset itself
int max_counter_to_stop = 1000;//After 100 failed attempts to read instructions from the RF the car will stop
//L293D-------------------------------------------------------------------------------------

//Motor A
const int enable34 = 8; //Pin 9 of L293 Always HIGH
const int motorPin4  = 6;  // Pin 14 of L293
const int motorPin3  = 7;  // Pin 10 of L293

//Motor B
const int enable12 = 5; //Pin 1 of L293 Always HIGH
const int motorPin2  = 9; // Pin 7 of L293
const int motorPin1  = 10;  // Pin 2 of L293
//-------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);

  //Recevier Setup
  rec_setup();

  //Wheels Setup
  wheels_setup();
}


//---------------------------------------------------------------------------------------------------------------
void loop() {
  recv_loop();
  check_stats();
  motor_output();
  delay(5);
}
