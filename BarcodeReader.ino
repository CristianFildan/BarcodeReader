/*
	BarcodeReader looks for the values received through the camera
    @return -> sequece of digits / "Not Detected" */

String BarcodeReader() 
{
  char i = '0';
  char a[15] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
  int k = 0;
  int relay_pin = 5;
  String code = "";
  
  if(mySerial.available())
    delay(1000);

  while (mySerial.available()) 
  {
    i = mySerial.read();
    //Serial.println(i);
    a[k] = i;
    code = code + i;


    k = k + 1;
    //Serial.println(k);

    if (k == 13)
    {
      Serial.println(code);

      while(mySerial.available()) 
      {
        char dummy = mySerial.read();  
      }

      return code;
    }
  }

  return code;
}