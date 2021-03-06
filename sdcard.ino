//////////////
// SD setup //
//////////////
void _SDSetup(void)
{
  sdStatus = SDCARD_DETECTION;
}

//////////////////////
// SD state machine //
//////////////////////
void _SDLoop(void)
{
  switch (sdStatus)
  {
    case SDCARD_DETECTION:
      if (!SD.begin(sdCs))
      {
        sdStatus = SDCARD_NOT_DETECTED;
        sdTickReconnect = millis();
        
        #if (_SDCARD_SERIAL_DEBUG_ == 1)
        Serial.println("SD Card Not detected...");
        #endif
      }
      else
      {
        sdStatus = SDCARD_DIRECTORY;

        #if (_SDCARD_SERIAL_DEBUG_ == 1)
        Serial.println("SD Card detected...");
        #endif
      }
      break;

    case SDCARD_DETECTED:
      break;

    case SDCARD_DIRECTORY:
    
      sdFile = SD.open("/");

      #if (_SDCARD_SERIAL_DEBUG_ == 1)
      printDirectory(sdFile, 0);
      Serial.println("SD Directory detected...");
      #endif
      
      sdStatus = SDCARD_DETECTED;
      break;

    case SDCARD_SAVERECORD:
      if ((sdFile, dLoggerString, sdFileName) == 0)
      {
        sdCounter ++;
        sdStatus = SDCARD_DETECTED;
        #if (_SDCARD_SERIAL_DEBUG_ == 1)
        Serial.println("SD Card Save reccord...");
        #endif
      }
      else
      {
        sdStatus = SDCARD_DETECTION;
        #if (_SDCARD_SERIAL_DEBUG_ == 1)
        Serial.println("SD Card Save reccord ERROR...");
        #endif
      }

      //sdTickSaveRecord = millis();
      break;

    case SDCARD_NOT_DETECTED:
      if (millis() - sdTickReconnect >= 1000)
        sdStatus = SDCARD_DETECTION;
      break;
  }
}

int sdSaveRecord(File dataFile, String dataString, String fileName)
{

  if (!SD.begin(sdCs))
   return -1;
  
  dataFile = SD.open(fileName, FILE_WRITE);

  if (dataFile)
  {
    dataFile.println(dataString);
    dataFile.close();
    return 0;
  }
  else
    return -1;
}

#if (_SDCARD_SERIAL_DEBUG_ == 1)
void printDirectory(File dir, int numTabs)
{
  // TODO
  while (true)
  {
    File entry =  dir.openNextFile();
    if (! entry) {
      Serial.println("Empty");
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory())
    {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
#endif
