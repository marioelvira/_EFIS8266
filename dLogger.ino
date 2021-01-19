///////////////////
// DLogger setup //
///////////////////
void _DLoggerSetup(void)
{
  dLoggerStatus = DLOGGER_START;
}

///////////////////////////
// DLogger state machine //
///////////////////////////
void _DLoggerLoop(void)
{ 
  int isec = 0;
  int imin = 0;

  switch (dLoggerStatus)
  {
    case DLOGGER_START:
      dLoggerResetSample();
      dLoggerStatus = DLOGGER_RECORD;

      dLoggerCurrentTime = millis();
      dLoggerPreviousTime = dLoggerCurrentTime;
      break;

    case DLOGGER_RECORD:

      dLoggerCurrentTime = millis();
      if (dLoggerCurrentTime - dLoggerPreviousTime >= DLOGGER_TICK)
      {
        // Add sample...
        dLoggerSecTick++;
        if (dLoggerSecTick >= dLoggerSampleRateSec)
        {
          #if (_DLOGGER_SERIAL_DEBUG_ == 1)
          Serial.println("Datalogger add Sample...");
          #endif
          dLoggerAddSample();
          dLoggerSecTick = 0;
        }

        // If sample to record...
        isec = timeSec;
        imin = timeMin;

        // Only in minute multiple and sec 0...
        if (((imin % dLoggerRecordRateMin) == 0) && (isec == 0))
        {
          #if (_DLOGGER_SERIAL_DEBUG_ == 1)
          Serial.println("Datalogger save record...");
          #endif
          dLoggerFileRecordSample();
          dLoggerStatus = DLOGGER_START;
        }
        
        dLoggerPreviousTime = dLoggerCurrentTime;
      }
      break;
  }
}

void dLoggerResetSample (void)
{
  dLAltimeter = 0;
  dLAirSpeed = 0;
  dLVario = 0;
  dLgMag = 0;
  dLgRoll = 0;
  dLgPitch = 0;
  dLiGforce = 0;
  dLiBall = 0;
}

void dLoggerAddSample (void)
{
  dLAltimeter += Altimeter;
  dLAirSpeed += AirSpeed;
  dLVario += Vario;
  dLgMag += gMag;
  dLgRoll += gRoll;
  dLgPitch += gPitch;
  dLiGforce += iGforce;
  dLiBall += iBall;
  
  dLoggerNumberOfSamples++;
}

void dLoggerFileRecordSample (void)
{ 
  dLAltimeter = dLAltimeter/dLoggerNumberOfSamples;
  dLAirSpeed = dLAirSpeed/dLoggerNumberOfSamples;
  dLVario = dLVario/dLoggerNumberOfSamples;
  dLgMag = dLgMag/dLoggerNumberOfSamples;
  dLgRoll = dLgRoll/dLoggerNumberOfSamples;
  dLgPitch = dLgPitch/dLoggerNumberOfSamples;
  dLiGforce = dLiGforce/dLoggerNumberOfSamples;
  dLiBall = dLiBall/dLoggerNumberOfSamples;

  dLoggerString = "";
  dLoggerString += timeHour;
  dLoggerString += ":";
  dLoggerString += timeMin;
  dLoggerString += ":";
  dLoggerString += timeSec;
  dLoggerString += ",";
  dLoggerString += dLAltimeter;
  dLoggerString += ",";
  dLoggerString += dLAirSpeed;
  dLoggerString += ",";
  dLoggerString += dLVario;
  dLoggerString += ",";  
  dLoggerString += dLgMag;
  dLoggerString += ",";
  dLoggerString += dLgRoll;
  dLoggerString += ",";
  dLoggerString += dLgPitch;
  dLoggerString += ",";
  dLoggerString += dLiGforce;
  dLoggerString += ",";
  dLoggerString += dLiBall;

  #if (_DLOGGER_SERIAL_DEBUG_ == 1)
  Serial.println(dLoggerString);
  #endif
  
  dLoggerNumberOfSamples = 0;

  if (sdStatus == SDCARD_DETECTED)
    sdStatus = SDCARD_SAVERECORD;
}
