
void rec_setup(){
  driver.init();
}

void recv_loop(){

    reset_stats();
    
    if (driver.recv(buf, 2)) {
      counter_to_stop = 0;
      Serial.print("Message Received: ");
      Serial.print("buf_0: ");Serial.write((int) buf[0]);Serial.println();
      Serial.print("buf_1: ");Serial.write((int) buf[1]);Serial.println();

      Serial.println();

      set_data_recieved();
      
      Serial.print("data_received: ");Serial.print(data_received);
      Serial.println();
      Serial.print("data_received(bin): ");
      print_byte();
   }

   //Try to read 
   else if (counter_to_stop < max_counter_to_stop){
    counter_to_stop ++;
   }
   
   //If no message received - STOP
   else {
    Serial.print("No Message Received");
    Serial.println();
    data_received = 0;
   }
}


void reset_stats(){
  pitch_active = false;
  pitch_positive = false;
  roll_active = false;
  roll_positive = false;

}

void set_data_recieved(){
      int buf_0 = (int)buf[0];
      int buf_1 = (int)buf[1];
      if (buf_0 == NULL) {
        data_received = 0;
      }
      
      else if (buf_0 == 0 && buf_1 == NULL){
        data_received = 0;
      }
      
      else if (buf_0 == 0 && buf_1 != NULL){
        data_received =  10 * buf_1;
      }
 
      else if (buf_0 > 0 && buf_1 != NULL){
        data_received =  10 * (buf_0 - 48) + (buf_1 - 48);
      } 
      
      else {
        data_received = buf_0 - 48;        
      }
}

void check_stats(){
/*
if binary_data&0b0001 = 0001 => pitch passed threshold; if zero its between thresholds
if binary_data&0b0010 = 0010 => pitch is positive; if 0 it is negitive
if binary_data&0b0100 = 0100 => roll passed threshold; if zero its between thresholds 
if binary_data&0b1000 = 1000 => roll passed threshold ; if 0 it is negitive
*/

if (data_received & 0b00000001){
  pitch_active = true;
}

if (data_received & 0b00000010 ){
  pitch_positive = true;
}

if (data_received & 0b00000100){
  roll_active = true;
}

if (data_received & 0b00001000){
  roll_positive = true;
}

//Serial.print("Pitch Active: ");Serial.println(pitch_active);
//Serial.print("Pitch Positive: ");Serial.println(pitch_positive);
//Serial.print("Roll Active: ");Serial.println(roll_active);
//Serial.print("Roll Positive: ");Serial.println(roll_positive);
}

void print_byte(){
     for (int i = 7; i >= 0; i--) {
        bool b = bitRead(data_received, i);
        Serial.print(b);
    }
    Serial.println();
}
