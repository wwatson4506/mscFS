/**
 * Copyright (c) 2011-2019 Bill Greiman
 * Modified for use with MSC Copyright (c) 2017-2020 Warren Watson
 * This file is part of the SdFat library for SD memory cards.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef USBFat_h
#define USBFat_h
/**
 * \file
 * \brief main SdFs include file.
 */
/*
#include "common/SysCall.h"
#include "USBmsController/USBmsc.h"
#include "ExFatLib/ExFatLib.h"
#include "FatLib/FatLib.h"
#include "FsLib/FsLib.h"
#if INCLUDE_SDIOS
#include "sdios.h"
#endif  // INCLUDE_SDIOS
*/
#include "SdFat.h"
//------------------------------------------------------------------------------
/** MSCFat version */
#define MSC_FAT_VERSION "2.0.0"
//==============================================================================
/**
 * \class UsbBase
 * \brief base SD file system template class.
 */
template <class Vol>
class UsbBase : public Vol {
 public:
  //----------------------------------------------------------------------------
  /** Initialize USB drive and file system.
   *
   * \param[in] msController drive.
   * \return true for success or false for failure.
   */
  bool begin(msController *pdrv) {
	return mscBegin(pdrv);
  }
  //----------------------------------------------------------------------------
  /** Initialize USB drive and file system for USB Drive.
   *
   * \param[in] msController drive configuration.
   * \return true for success or false for failure.
   */
  bool mscBegin(msController *pDrive) {
    return cardBegin(pDrive) && Vol::begin(m_USBmscDrive);
  }
  //----------------------------------------------------------------------------
  /** \return Pointer to USB MSC object. */
  mscDevice* usbDrive() {return m_USBmscDrive;}
  //---------------------------------------------------------------------------
  /** Initialize USB MSC drive.
   *
   * \param[in] Pointer to an instance of msc.
   * \return true for success or false for failure.
   */
  bool cardBegin(msController *pDrive) {
    m_USBmscDrive = m_USBmscFactory.newMSCDevice(pDrive);
    return m_USBmscDrive && !m_USBmscDrive->errorCode();
  }
  //----------------------------------------------------------------------------
  /** %Print error info and halt.
   *
   * \param[in] pr Print destination.
   */
  void errorHalt(print_t* pr) {
    if (sdErrorCode()) {
      pr->print(F("SdError: 0X"));
      pr->print(sdErrorCode(), HEX);
      pr->print(F(",0X"));
      pr->println(sdErrorData(), HEX);
    } else if (!Vol::fatType()) {
      pr->println(F("Check SD format."));
    }
    SysCall::halt();
  }
  //----------------------------------------------------------------------------
  /** %Print error info and halt.
   *
   * \param[in] pr Print destination.
   * \param[in] msg Message to print.
   */
  void errorHalt(print_t* pr, const char* msg) {
    pr->print(F("error: "));
    pr->println(msg);
    errorHalt(pr);
  }
  //----------------------------------------------------------------------------
  /** %Print msg and halt.
   *
   * \param[in] pr Print destination.
   * \param[in] msg Message to print.
   */
  void errorHalt(print_t* pr, const __FlashStringHelper* msg) {
    pr->print(F("error: "));
    pr->println(msg);
    errorHalt(pr);
  }
  //----------------------------------------------------------------------------
  /** %Print error info and halt.
   *
   * \param[in] pr Print destination.
   */
  void initErrorHalt(print_t* pr) {
    initErrorPrint(pr);
    SysCall::halt();
  }
  //----------------------------------------------------------------------------
  /** %Print error info and halt.
   *
   * \param[in] pr Print destination.
   * \param[in] msg Message to print.
   */
  void initErrorHalt(print_t* pr, const char* msg) {
    pr->println(msg);
    initErrorHalt(pr);
  }
  //----------------------------------------------------------------------------
  /** %Print error info and halt.
   *
   * \param[in] pr Print destination.
   * \param[in] msg Message to print.
   */
  void initErrorHalt(Print* pr, const __FlashStringHelper* msg) {
    pr->println(msg);
    initErrorHalt(pr);
  }
  //----------------------------------------------------------------------------
  /** Print error details after begin() fails.
   *
   * \param[in] pr Print destination.
   */
  void initErrorPrint(Print* pr) {
    pr->println(F("begin() failed"));
    if (sdErrorCode()) {
      pr->println(F("Do not reformat the SD."));
      if (sdErrorCode() == SD_CARD_ERROR_CMD0) {
        pr->println(F("No card, wrong chip select pin, or wiring error?"));
      }
    }
    errorPrint(pr);
  }
  //----------------------------------------------------------------------------
  /** %Print volume FAT/exFAT type.
   *
   * \param[in] pr Print destination.
   */
  void printFatType(print_t* pr) {
    if (Vol::fatType() == FAT_TYPE_EXFAT) {
      pr->print(F("exFAT"));
    } else {
      pr->print(F("FAT"));
      pr->print(Vol::fatType());
    }
  }
  //----------------------------------------------------------------------------
  /** %Print SD errorCode and errorData.
   *
   * \param[in] pr Print destination.
   */
  void errorPrint(print_t* pr) {
    if (sdErrorCode()) {
      pr->print(F("SdError: 0X"));
      pr->print(sdErrorCode(), HEX);
      pr->print(F(",0X"));
      pr->println(sdErrorData(), HEX);
    } else if (!Vol::fatType()) {
      pr->println(F("Check SD format."));
    }
  }
  //----------------------------------------------------------------------------
  /** %Print msg, any SD error code.
   *
   * \param[in] pr Print destination.
   * \param[in] msg Message to print.
   */
  void errorPrint(print_t* pr, char const* msg) {
    pr->print(F("error: "));
    pr->println(msg);
    errorPrint(pr);
  }

  /** %Print msg, any SD error code.
   *
   * \param[in] pr Print destination.
   * \param[in] msg Message to print.
   */
  void errorPrint(Print* pr, const __FlashStringHelper* msg) {
    pr->print(F("error: "));
    pr->println(msg);
    errorPrint(pr);
  }
  //----------------------------------------------------------------------------
  /** %Print error info and return.
   *
   * \param[in] pr Print destination.
   */
  void printSdError(print_t* pr) {
    if (sdErrorCode()) {
      if (sdErrorCode() == SD_CARD_ERROR_CMD0) {
        pr->println(F("No card, wrong chip select pin, or wiring error?"));
      }
      pr->print(F("SD error: "));
      printSdErrorSymbol(pr, sdErrorCode());
      pr->print(F(" = 0x"));
      pr->print(sdErrorCode(), HEX);
      pr->print(F(",0x"));
      pr->println(sdErrorData(), HEX);
    } else if (!Vol::cwv()) {
      pr->println(F("Check SD format."));
    }
  }
  //----------------------------------------------------------------------------
  /** \return SD card error code. */
  uint8_t sdErrorCode() {
    if (m_USBmscDrive) {
      return m_USBmscDrive->errorCode();
    }
    return SD_CARD_ERROR_INVALID_CARD_CONFIG; //TODO: change this!
  }
  //----------------------------------------------------------------------------
  /** \return SD card error data. */
  uint8_t sdErrorData() {return m_USBmscDrive ? m_USBmscDrive->errorData() : 0;}
  //----------------------------------------------------------------------------
  /** \return pointer to base volume */
  Vol* vol() {return reinterpret_cast<Vol*>(this);}
  //----------------------------------------------------------------------------
  /** Initialize file system after call to cardBegin.
   *
   * \return true for success or false for failure.
   */
  bool volumeBegin() {
     return Vol::begin(m_USBmscDrive);
  }
#if ENABLE_ARDUINO_SERIAL
  /** Print error details after begin() fails. */
  void initErrorPrint() {
    initErrorPrint(&Serial);
  }
  //----------------------------------------------------------------------------
  /** %Print msg to Serial and halt.
   *
   * \param[in] msg Message to print.
   */
  void errorHalt(const __FlashStringHelper* msg) {
    errorHalt(&Serial, msg);
  }
  //----------------------------------------------------------------------------
  /** %Print error info to Serial and halt. */
  void errorHalt() {errorHalt(&Serial);}
  //----------------------------------------------------------------------------
  /** %Print error info and halt.
   *
   * \param[in] msg Message to print.
   */
  void errorHalt(const char* msg) {errorHalt(&Serial, msg);}
  //----------------------------------------------------------------------------
  /** %Print error info and halt. */
  void initErrorHalt() {initErrorHalt(&Serial);}
  //----------------------------------------------------------------------------
  /** %Print msg, any SD error code.
   *
   * \param[in] msg Message to print.
   */
  void errorPrint(const char* msg) {errorPrint(&Serial, msg);}
   /** %Print msg, any SD error code.
   *
   * \param[in] msg Message to print.
   */
  void errorPrint(const __FlashStringHelper* msg) {errorPrint(&Serial, msg);}
  //----------------------------------------------------------------------------
  /** %Print error info and halt.
   *
   * \param[in] msg Message to print.
   */
  void initErrorHalt(const char* msg) {initErrorHalt(&Serial, msg);}
  //----------------------------------------------------------------------------
  /** %Print error info and halt.
   *
   * \param[in] msg Message to print.
   */
  void initErrorHalt(const __FlashStringHelper* msg) {
    initErrorHalt(&Serial, msg);
  }
#endif  // ENABLE_ARDUINO_SERIAL
  //----------------------------------------------------------------------------
 private:
  mscDevice*  m_USBmscDrive;
  USBmscFactory m_USBmscFactory;
};
//------------------------------------------------------------------------------
/**
 * \class UsbFat32
 * \brief MSC file system class for FAT volumes.
 */
class UsbFat32 : public UsbBase<FatVolume> {
 public:
  /** Format a SD card FAT32/FAT16.
   *
   * \param[in] pr Optional Print information.
   * \return true for success or false for failure.
   */
  bool format(print_t* pr = nullptr) {
    FatFormatter fmt;
    uint8_t* cache = reinterpret_cast<uint8_t*>(cacheClear());
    if (!cache) {
      return false;
    }
    return fmt.format(usbDrive(), cache, pr);
  }
};
//------------------------------------------------------------------------------
/**
 * \class UsbExFat
 * \brief MSC file system class for exFAT volumes.
 */
class UsbExFat : public UsbBase<ExFatVolume> {
 public:
  /** Format a SD card exFAT.
   *
   * \param[in] pr Optional Print information.
   * \return true for success or false for failure.
   */
  bool format(print_t* pr = nullptr) {
    ExFatFormatter fmt;
    uint8_t* cache = reinterpret_cast<uint8_t*>(cacheClear());
    if (!cache) {
      return false;
    }
    return fmt.format(usbDrive(), cache, pr);
  }
};
//------------------------------------------------------------------------------
/**
 * \class USBFs
 * \brief SD file system class for FAT16, FAT32, and exFAT volumes.
 */
class UsbFs : public UsbBase<FsVolume> {
};
//------------------------------------------------------------------------------
typedef UsbFs UsbFat;
typedef FsBaseFile UsbBaseFile;
/**
 * \class SdFile
 * \brief FAT16/FAT32 file with Print.
 */
class MscFile : public PrintFile<UsbBaseFile> {
 public:
  MscFile() {}
  /** Create an open SdFile.
   * \param[in] path path for file.
   * \param[in] oflag open flags.
   */
  MscFile(const char* path, oflag_t oflag) {
    open(path, oflag);
  }
};
 #endif  // USBFat_h
