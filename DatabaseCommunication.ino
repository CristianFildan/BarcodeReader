/*
	searchDB looks through the database to check if the barcodeNumer is there.
  returnts the corresponding bin if the item is there or 0 otherwise
    @param String -> the barCode detected on the barcode scanner
    @return -> the bin corresponding to the item / 0 if there is database problem or item is not in database 
    */
int searchDB(String barCode) {
  
  // Open file for reading starting from the start of the file 
  database = SD.open("database.txt", FILE_READ);

  if (database) {
    Serial.println("Reading:");
    // Reading the whole file
    
    
    int dataFound = 0;

    label:
    while (database.available())
    {
      String s = database.readStringUntil('\r');
      database.read();
      
      Serial.println(s);
      int i,j;
      int dataSize = 13;

      for(i=0,j=0; i<dataSize; i++,j++)
      { 
        if(s[i] != barCode[j])
          goto label;
      }
      dataFound = s[i+1]-'0'; 
      //dataFound = 1; // uncomment for testing
      break;
    }
    Serial.println(dataFound);
    database.close();
    return dataFound != 0;
  }
  else {
    Serial.println("Error opening test.txt");
    return 0;
  }
}


void addDB(String barCode, int bin) {

  database = SD.open("database.txt", FILE_WRITE);

  if (database) {
    Serial.print("Adding ");
    Serial.print(barCode);
    Serial.println(" to database:");
    
    // Write to file
    String data = barCode + ' ' + char(bin+'0');

    database.println(data);
    database.close(); // close the file

    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("Error opening test.txt");
  }
}