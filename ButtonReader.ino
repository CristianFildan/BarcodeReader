/*
	BurronReader awaits value change from the buttons
    @return -> the button pressed / 0 if nothing is pressed 
    Remark: Possible problems:
    	if a button gets stuck we are doomed :) 
        if multiple buttons are pressed at the same time... 
        	... behavior can't be predicted*/
int ButtonReader() {
  int buttonPressed = digitalRead(button1Pin);
  buttonPressed = max(buttonPressed,digitalRead(button2Pin)*2);
  buttonPressed = max(buttonPressed,digitalRead(button3Pin)*3);
  buttonPressed = max(buttonPressed,digitalRead(button4Pin)*4);

  /*Serial.print("ButtonReader");
  Serial.println(buttonPressed);
  delay(300);*/
  return buttonPressed;
}
