/*
  SD-MSC drive basic file example
 
 This example shows how to create and destroy an MSC drive file 	
 
 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
  modified 8 Nov 2020
 by Warren Watson

 This example code is in the public domain.
 	 
 */

#include <mscFS.h>

USBHost myusb;

USBHub hub1(myusb);
USBHub hub2(myusb);
USBHub hub3(myusb);
USBHub hub4(myusb);

msController msDrive1(myusb);
msController msDrive2(myusb);

File myFile;

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }

	myusb.begin();

  Serial.print("Initializing MSC drive 1...");

  if (!MSC.begin(&msDrive1)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  if (MSC.exists("example.txt")) {
    Serial.println("example.txt exists.");
  }
  else {
    Serial.println("example.txt doesn't exist.");
  }

  // open a new file and immediately close it:
  Serial.println("Creating example.txt...");
  myFile = MSC.open("example.txt", FILE_WRITE);
  myFile.close();

  // Check to see if the file exists: 
  if (MSC.exists("example.txt")) {
    Serial.println("example.txt exists.");
  }
  else {
    Serial.println("example.txt doesn't exist.");  
  }

  // delete the file:
  Serial.println("Removing example.txt...");
  MSC.remove("example.txt");

  if (MSC.exists("example.txt")){ 
    Serial.println("example.txt exists.");
  }
  else {
    Serial.println("example.txt doesn't exist.");  
  }
}

void loop()
{
  // nothing happens after setup finishes.
}



