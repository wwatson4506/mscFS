/*
  SD-MSC drive file dump
 
 This example shows how to read a file from the MSC drive using the
 MSC library and send it over the serial port.
 	
 
 created  22 December 2010
 by Limor Fried
 modified 9 Apr 2012
 by Tom Igoe
 modified 8 Nov 2020
 by Warren Watson
 
 This example code is in the public domain.
 	 
 */

#include <SD-MSC.h>

USBHost myusb;

USBHub hub1(myusb);
USBHub hub2(myusb);
USBHub hub3(myusb);
USBHub hub4(myusb);

msController msDrive1(myusb);
msController msDrive2(myusb);

void setup()
{

 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }

	myusb.begin();

  Serial.print("Initializing USB MSC drive 1...");
  
  // see if the card is present and can be initialized:
  if (!MSC.begin(&msDrive1)) {
    Serial.println("MSC Drive initialization failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("MSC drive initialized.");
  
  // open the file.
  File dataFile = MSC.open("datalog.txt");

  // if the file is available, write to it:
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
}

void loop()
{
}

