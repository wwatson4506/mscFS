/*
  SD-MSC drive basic file example
 
 This example shows how to create and destroy an SD card file 	

 created   Nov 2010
 by David A. Mellis
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

File root;

void setup()
{
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }

	myusb.begin();

  Serial.print("Initializing MSC Drive 1...");

  if (!MSC.begin(&msDrive1)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  root = MSC.open("/");
  
  printDirectory(root, 0);
  
  Serial.println("done!");
}

void loop()
{
  // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}



