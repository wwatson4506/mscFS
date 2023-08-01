# mscFS Library
## THIS LIBRARY IS OUTDATED !!
# Use Teensyduino 1.59 Beta 2 and Arduino 1.8.18 or Arduino IDE 2.1.1

mscFS is a version of SD for use with USB host mass storeage devices and parallels the new Teensy File System Abstracion class.

This library is compatible with SD. It is ment for use with Sdfat and USBHost_t36. It parallels SD and does not use FS.h.
SdFat-parallel had slight modifications to "SdFat.h" and "SdFatConfig.h".

Two libraries must be cloned and installed in the TD1.54B5 "arduino-1.8.13/hardware/teensy/avr/libraries' folder.

You will need to backup these two libraries somewhere to revert back to if needed:

1 - SdFat

2 - USBHost_t36

The two libraries you need to replace them with are available here:

https://github.com/wwatson4506/SdFat-beta/tree/SdFat-parallel

https://github.com/wwatson4506/USBHost_t36

The four MSC library branches here:

https://github.com/wwatson4506/MSC

are not needed now with the modified version of USBHost_t36. "MasStorageDriver.cpp" and "msc.h" are now contained in my version of USBHost_t36. "MassStorageHost.cpp" and "MassStorage.h" are still available in the four different branches of the MSC library.
