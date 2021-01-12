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
      if (!SD.begin(10))
      {
        sdStatus = SDCARD_NOT_DETECTED;
        sdTickReconnect = millis();
        
        #if (_SDCARD_SERIAL_DEBUG_ == 1)
        Serial.println("SD Card Not detected...");
        #endif
      }
      else
      {
        sdStatus = SDCARD_DETECTED;

        #if (_SDCARD_SERIAL_DEBUG_ == 1)
        Serial.println("SD Card detected...");
        #endif
      }
      break;

    case SDCARD_DETECTED:
      break;

    case SDCARD_SAVERECORD:
      // open the file
      sdFile = SD.open("test.txt", FILE_WRITE);
      if (sdFile)
      {
        // close the file
        sdFile.close();
      }
      break;

    case SDCARD_NOT_DETECTED:
      if (millis() - sdTickReconnect >= 1000)
        sdStatus = SDCARD_DETECTION;
      break;
  }
}
