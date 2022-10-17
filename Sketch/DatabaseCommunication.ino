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
    Serial.println("Read:");
    // Reading the whole file
    
    int dataFound = 0;

    label:
    while (database.available())
    {
      String s = database.readStringUntil('\r');

      int i,j;
      int dataSize = 13;

      for(i=0,j=0; i<dataSize; i++,j++)
        if(s[i] != barCode[j])
          goto label;

      dataFound = s[i+1]-'0';
      break;
    }

    database.close();
    return dataFound;
  }
  else {
    Serial.println("Error opening test.txt");
    return 0;
  }
}


/*void loop() {
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file...");
    // Write to file
    myFile.println("Testing text 1, 2 ,3...");
    myFile.close(); // close the file
    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
}*/