void wheels_setup(){
    //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);

    //Set enablers HIGH
    pinMode(enable12, OUTPUT);
    pinMode(enable34, OUTPUT);
    digitalWrite(enable12, HIGH);
    digitalWrite(enable34, HIGH);
}

void motor_output() {
    
    bool motorPin1_status = LOW; //HIGH -> motor A clockwise
    bool motorPin2_status  = LOW;//HIGH -> motor A counter-clockwise
    bool motorPin3_status  = LOW;//HIGH -> motor B clockwise
    bool motorPin4_status  = LOW;//HIGH -> motor B counter-clockwise

    //Set current Command to wheels
    
    //STOP
    if (roll_active == false && pitch_active == false){
    //Serial.print("STOP");Serial.println();
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    }

    //RIGHT
    else if (roll_active == true && roll_positive == false){
    //Serial.print("Right");Serial.println();
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);//HIGH
    }

    //LEFT
    else if (roll_active == true && roll_positive == true){
    //Serial.print("Left");Serial.println();
    digitalWrite(motorPin1, LOW);//HIGH
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    }    

    //BACKWARD
    else if (pitch_active == true && pitch_positive == false){
    //Serial.print("Forward");Serial.println();
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);

    }
    
    //FOWARD
    else if (pitch_active == true && pitch_positive == true){
    //Serial.print("Backward");Serial.println();
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    }
}
