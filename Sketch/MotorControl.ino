
/*
	MotorMovement first moves the bottom servo and then the top servo
    @param bin -> the bin number where the trash should go
    TODO: Timing (time) of servo movement not calculated
    Remark: Problem:
    	Bins will get misalligned
    Possible solution: 
    	Use a sensor (2euro) to detect position
    	Put it under the bins and append a coulourful piece from the bins*/
void MotorMovement(int bin) {
    
  Serial.println("First(bottom) Servo movement start...");
  ///TODO: set the timer or location given the different positions
  //bottomServo.attach(bottomServoPin);
  bottomServo.write(45);
  Serial.println("First(bottom) Servo movement delay!");
  delay(bottomServoTime);	//Instead of delay check for sensorInput
  bottomServo.write(45);
  //bottomServo.detach();
  Serial.println("First(bottom) Servo movement finished!");
  
  
  /// TODO: Store the new position of bottom Servo in SD card
  /// 		Or return the bins to their initial position.
  
  Serial.println("Second(top) Servo movement start..."); 
  //topServo.attach(topServoPin);
  topServo.write(45);
  delay(topServoTime);
  //topServo.detach();
  delay(lidOpenTime);
  //topServo.attach(topServoPin);
  topServo.write(45);
  delay(topServoTime);
  topServo.write(45);
  //topServo.detach();  
  Serial.println("Second(Top) Servo movement finished!");
}