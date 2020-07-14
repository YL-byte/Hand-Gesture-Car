
//RF TRANS declaration part
#include <Wire.h>
#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

RH_ASK driver(2000, 2, 2, 0);

//Gyro A4 (SDA), A5 (SCL)

//Variables for Gyroscope
int gyro_x, gyro_y, gyro_z;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
boolean set_gyro_angles;

long acc_x, acc_y, acc_z, acc_total_vector;
int angle_roll_acc, angle_pitch_acc;
 
float angle_pitch, angle_roll;
int angle_pitch_buffer, angle_roll_buffer;
float angle_pitch_output, angle_roll_output;

int max_angle_pitch_acc = 50, max_angle_roll_acc = 50;
//Variables for RF Transsmitor
int sensorData = 0;
char sensorCharMsg[4];
uint8_t glove_encoded;

void setup() {

  //Start I2C Connection
  Wire.begin();
  trans_setup();
  //Setup MPU
  setup_mpu_6050();
  Serial.begin(115200);
  
}

void loop() {
  glove_encoded = 0b00000000;
  mpu_6050_loop();
  Serial.print("Pitch "); Serial.print((int)angle_pitch_acc);Serial.print(" | Roll "); Serial.print((int)angle_roll_acc);
  Serial.println();
  
  /*
   Create message => 0b1234
    1 is positive if roll is bigger then 0;
    2 is positive if roll abs valute is bigger then threshold;
    3 is positive if pitch is bigger then 0;
    4 is positive if pitch abs value is bigger then threshold;
  */
  
  if (angle_pitch_acc > max_angle_pitch_acc || angle_pitch_acc < (-1 * max_angle_pitch_acc)){
    glove_encoded = glove_encoded|0b00000001;    
  }

  if (angle_pitch_acc > 0){
    glove_encoded = glove_encoded|0b00000010;    
  }

  if (angle_roll_acc > max_angle_roll_acc || angle_roll_acc < (-1 * max_angle_roll_acc)){
    glove_encoded = glove_encoded|0b00000100;    
  }

  if (angle_roll_acc > 0){
    glove_encoded = glove_encoded|0b00001000;    
  }
  
  sensorData = (int)glove_encoded;
  itoa(sensorData, sensorCharMsg, 10);
  Serial.println(sensorCharMsg);
  Serial.println(strlen(sensorCharMsg));
  
  driver.send((uint8_t *) sensorCharMsg, 2);
  driver.waitPacketSent();
  delay(200);
 }
