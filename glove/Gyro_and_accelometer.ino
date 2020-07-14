#include<Wire.h>

#define mpuAddress 0X68;


void setup_mpu_6050(){
   //Setup the registers of the MPU-6050
  setup_mpu_6050_registers();
  int cal_number = 1000;
  //Calibrate the MPU
  for (int cal_int = 0; cal_int < cal_number; cal_int++){
    //Add the gyro values to their appropreate values for later division
    read_mpu_6050_data();
    gyro_x_cal += gyro_x;
    gyro_y_cal += gyro_y;
    gyro_z_cal += gyro_z;
    delay(5);
  }

  //Divide all results by calibration number
  gyro_x_cal /= cal_number;
  gyro_y_cal /= cal_number;
  gyro_z_cal /= cal_number;

}

void mpu_6050_loop(){
  
  read_mpu_6050_data();

  //Subtract the offset values from the raw gyro values
  gyro_x -= gyro_x_cal;                                                
  gyro_y -= gyro_y_cal;                                                
  gyro_z -= gyro_z_cal;                                                

  //Gyro angle calculations . Note 0.0000611 = 1 / (250Hz x 65.5)
  angle_pitch += gyro_x * 0.0000611;  
  angle_roll += gyro_y * 0.0000611; 
  //0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians                                
  //If the IMU has yawed transfer the roll angle to the pitch angle
  angle_pitch += angle_roll * sin(gyro_z * 0.000001066);

  //If the IMU has yawed transfer the pitch angle to the roll angle               
  angle_roll -= angle_pitch * sin(gyro_z * 0.000001066);              

  //Calculate the total accelerometer vector
  acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z)); 
   
  //57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
  //Calculate the pitch angle
  angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296; 
  //Calculate the roll angle      
  angle_roll_acc =  asin((float)acc_x/acc_total_vector)* -57.296;       
  
  //Accelerometer calibration value for pitch
  angle_pitch_acc -= 0;
  //Accelerometer calibration value for roll                                              
  angle_roll_acc -= 0;                                               
}


void setup_mpu_6050_registers(){  
  //Activate the MPU-6050
  
  //Start communicating with the MPU-6050
  Wire.beginTransmission(0x68); 
  //Send the requested starting register                                       
  Wire.write(0x6B);  
  //Set the requested starting register                                                  
  Wire.write(0x00);
  //End the transmission                                                    
  Wire.endTransmission(); 
                                              
  //Configure the accelerometer (+/-8g)
  
  //Start communicating with the MPU-6050
  Wire.beginTransmission(0x68); 
  //Send the requested starting register                                       
  Wire.write(0x1C);   
  //Set the requested starting register                                                 
  Wire.write(0x10); 
  //End the transmission                                                   
  Wire.endTransmission(); 
                                              
  //Configure the gyro (500dps full scale)
  
  //Start communicating with the MPU-6050
  Wire.beginTransmission(0x68);
  //Send the requested starting register                                        
  Wire.write(0x1B);
  //Set the requested starting register                                                    
  Wire.write(0x08); 
  //End the transmission                                                  
  Wire.endTransmission(); 
                                              
}

void read_mpu_6050_data(){ 

  //Read the raw gyro and accelerometer data

  //Start communicating with the MPU-6050                                          
  Wire.beginTransmission(0x68);  
  //Send the requested starting register                                      
  Wire.write(0x3B);
  //End the transmission                                                    
  Wire.endTransmission(); 
  //Request 14 bytes from the MPU-6050                                  
  Wire.requestFrom(0x68,14);    
  //Wait until all the bytes are received                                       
  while(Wire.available() < 14);
  
  //Following statements left shift 8 bits, then bitwise OR.  
  //Turns two 8-bit values into one 16-bit value                                       
  acc_x = Wire.read()<<8|Wire.read() / 4096;                                  
  acc_y = Wire.read()<<8|Wire.read() / 4096;                                  
  acc_z = Wire.read()<<8|Wire.read() / 4096;                                  
  int16_t temp = Wire.read()<<8|Wire.read();                                   
  gyro_x = Wire.read()<<8|Wire.read();                                 
  gyro_y = Wire.read()<<8|Wire.read();                                 
  gyro_z = Wire.read()<<8|Wire.read();                                 
}
