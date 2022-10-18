// Global variables
// TODO add more variables (pin and other)
// Remark: Current ToDo's does not include writing to the database (putting new items to the Database);
#include <Servo.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8,9); // RX to 2 TX to 3

const int button1Pin = 5; 	// pins used for buttons 2:5
const int button2Pin = 4;   
const int button3Pin = 3;   
const int button4Pin = 2;

const int barcodePin1 = 8;  //pins used for barcodeScanner
const int barcodePin2 = 9;

const int motionSensor = A0;

File database;
int pinSD = 10; // Pin 10, 11, 12, 13 must be used together to coomunicate Arduino and SD module
                // check Miro board for more info

const int ledPin = 13;	  	// used for testing
const int time = 2000;		// used for testing and servo movement: 2 seconds
							
int currentPos;				// position of Bottom Servo
							/// TODO: Position of the servo not implemented yet

Servo bottomServo; 			// Bottom Servo pin set to 6
Servo topServo;				// Top/Lid Servo pin set to 7
const int bottomServoPin = 6;
const int topServoPin = 7;
const int bottomServoTime = 2000;	// Use in case no extra sensor
const int topServoTime = 2000;		// Time of topServoMovement
const int lidOpenTime = 2000;		// Time lid will stay open
/// Servo movement speed controlled locally in MotorMovement


// This function will run at the start:
void setup() {
  
  /// TODO: get the position of the bottom servo and restore it to the default
  /// Remark: Servos work in a way that we can return it to it's initial position.
  
  bottomServo.attach(bottomServoPin);
  topServo.attach(topServoPin);

  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);

  pinMode(motionSensor, INPUT);

  pinMode(pinSD, OUTPUT);
  SD.begin();
}

//This function will run repeatedly after the start:
void loop() {
  
  // Check for button input
  int button = ButtonReader();
  if(button) {
    Serial.print("Button pressed: ") ;
    Serial.println(button);
    MotorMovement(button);
    return;
  }
  
  // Check for barcode input
  String barcodeSeq = BarcodeReader();
  if(!barcodeSeq.equals("")) {
  	Serial.print("Barcode detected: ");
    Serial.println(barcodeSeq);
    
    // Check Database and call motors if needed.
    int binNumber = BarcodeDetected(barcodeSeq);
    MotorMovement(binNumber);
    
    //delay(time); // delay used for testing purposes;
    Serial.println("Detection Finished!");
    return;
  }
}

/*
	BarcodeDetected check is the sequence is in the Database
  @param seq -> the sequence of digits
	@return int -> the corresponding bin or residual */
int BarcodeDetected(String seq) {
   
  int inDatabase = searchDB(seq);
  
  if(!inDatabase)
    Serial.println("Not found in Database, awaiting button command");

  while(!inDatabase)
  {
    inDatabase = ButtonReader();
    if(inDatabase)
      addDB(seq,inDatabase);
  }
  
  return inDatabase;
}