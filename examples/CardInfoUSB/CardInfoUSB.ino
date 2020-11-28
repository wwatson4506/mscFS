/*
  MSC USB Drive test 
   
 This example shows how use the utility libraries on which the'
 SD library is based in order to get info about your USB Drive.
 Very useful for testing a card when you're not sure whether its working or not.
 	
 created  28 Mar 2011
 by Limor Fried 
 modified 9 Apr 2012
 by Tom Igoe
 modified 17 Nov 2020
 by Warren Watson
 */
 // include the SD library:
#include <mscFS.h>

// Setup USBHost_t36 and as many HUB ports as needed.
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
USBHub hub3(myusb);
USBHub hub4(myusb);

// Setup MSC for the number of USB Drives you are using. (Two for this example)
// Mutiple  USB drives can be used. Hot plugging is supported. There is a slight
// delay after a USB MSC device is plugged in. This is waiting for initialization
// but after it is initialized ther should be no delay.
msController msDrive1(myusb);
msController msDrive2(myusb);

// set up variables using the mscFS utility library functions:
MSC2Drive msc1;
MSCVolume volume;
MscFile root;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }
  
  // Start USBHost_t36, HUB(s) and USB devices.
  myusb.begin();

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the USB drive(s) are working!
  Serial.print("\nInitializing USB MSC drive...");
  if (!msc1.init(&msDrive1)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a USB drive connected?");
  } else {
     Serial.println("USB drive is present.");
  }
  
  // print the type of card
  Serial.print("\nCard type: ");
  switch(msc1.usbType()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    case SD_CARD_TYPE_USB:
      Serial.println("USB MSC");
      break;
    default:
      Serial.println("Unknown");
  }

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  if(volume.fatType()) {
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();
  
  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  if (volumesize < 8388608ul) {
    Serial.print("Volume size (bytes): ");
    Serial.println(volumesize * 512);        // SD card blocks are always 512 bytes
  }
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 2;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  }

  //Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  //root.openRoot(volume);
  
  // list all files in the card with date and size
  // root.ls(LS_R | LS_DATE | LS_SIZE);

}


void loop(void) {
  
}
