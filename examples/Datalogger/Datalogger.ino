/*
  SD-MSC drive datalogger
 
 This example shows how to log data from three analog sensors
 to an MSC drive using the USB MSC library.
 	
 
 created  24 Nov 2010
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
}

void loop()
{
  // make a string for assembling the data to log:
  String dataString = "";

  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ",";
    }
  }

  // open the file.
  File dataFile = MSC.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  } else {
    // if the file isn't open, pop up an error:
    Serial.println("error opening datalog.txt");
  }
  delay(100); // run at a reasonable not-too-fast speed
}





