///////////////////
// DLogger setup //
///////////////////
void _DLoggerSetup(void)
{
  dLoggerStatus = DLOGGER_START;
  dloogerStart = 0;
}

///////////////////////////
// DLogger state machine //
///////////////////////////
void _DLoggerLoop(void)
{ 
  int isec = 0;
  int imin = 0;

  // Only record if flying...
  if (AirSpeed_OnFly == 0)
  {
    dloogerStart = 0;
    dLoggerStatus = DLOGGER_NORECORD;
  }
  else
  {
    if (dloogerStart == 0)
    {
      dloogerStart = 1;
      dLoggerStatus = DLOGGER_START;
    }
  }

  switch (dLoggerStatus)
  {
    case DLOGGER_NORECORD:
      break;
    
    case DLOGGER_START:
      // Read date...
      RtcTime = rtcObject.GetDateTime();

      sdFileName = "Rec_";
      sdFileName = sdFileName + "_" + String(RtcTime.Year());
      sdFileName = sdFileName + "_" + String(RtcTime.Month());
      sdFileName = sdFileName + "_" + String(RtcTime.Day());
      sdFileName = sdFileName + "_" + String(RtcTime.Hour());
      sdFileName = sdFileName + "_" + String(RtcTime.Minute());
      sdFileName = sdFileName + "_" + String(RtcTime.Second());
      sdFileName = sdFileName + ".csv";

      #if (_DLOGGER_SERIAL_DEBUG_ == 1)
      Serial.println(sdFileName);
      #endif
          
      dLoggerFileRecordHearder();
      
      dLoggerResetSample();
      dLoggerCurrentTime = millis();
      dLoggerPreviousTime = dLoggerCurrentTime;

      dLoggerStatus = DLOGGER_ONRECORD;
      break;

    case DLOGGER_ONRECORD:

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
        #if (_USE_RTC_ == 1)
        isec = (int)RtcTime.Second();
        imin = (int)RtcTime.Minute();
        #else
        isec = timeSec;
        imin = timeMin;
        #endif

        // Only in minute multiple and sec 0...
        if (((imin % dLoggerRecordRateMin) == 0) && (isec == 0))
        {
          #if (_DLOGGER_SERIAL_DEBUG_ == 1)
          Serial.println("Datalogger save record...");
          #endif
          dLoggerFileRecordSample();
          dLoggerResetSample();
          #if (_DLOGGER_SERIAL_DEBUG_ == 1)
          Serial.println("Datalogger sample reseted...");
          #endif
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

  dLoggerNumberOfSamples = 0;
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

void dLoggerFileRecordHearder (void)
{ 
  dLoggerString = "";
  
  dLoggerString += "date";
  
  dLoggerString += ",";
  dLoggerString += "alt";
  dLoggerString += ",";
  dLoggerString += "airspeed";
  dLoggerString += ",";
  dLoggerString += "vario";
  dLoggerString += ",";  
  dLoggerString += "magnet";
  dLoggerString += ",";
  dLoggerString += "roll";
  dLoggerString += ",";
  dLoggerString += "pith";
  dLoggerString += ",";
  dLoggerString += "gforce";
  dLoggerString += ",";
  dLoggerString += "ball";

  #if (_DLOGGER_SERIAL_DEBUG_ == 1)
  Serial.println(dLoggerString);
  #endif

  if (sdStatus == SDCARD_DETECTED)
    sdStatus = SDCARD_SAVERECORD;
}

void dLoggerFileRecordSample (void)
{
  if (dLoggerNumberOfSamples == 0)
  {
    #if (_DLOGGER_SERIAL_DEBUG_ == 1)
    Serial.println("Nothing lo LOG...");
    #endif
    return;
  }
    
  dLAltimeter = dLAltimeter/dLoggerNumberOfSamples;
  dLAirSpeed = dLAirSpeed/dLoggerNumberOfSamples;
  dLVario = dLVario/dLoggerNumberOfSamples;
  dLgMag = dLgMag/dLoggerNumberOfSamples;
  dLgRoll = dLgRoll/dLoggerNumberOfSamples;
  dLgPitch = dLgPitch/dLoggerNumberOfSamples;
  dLiGforce = dLiGforce/dLoggerNumberOfSamples;
  dLiBall = dLiBall/dLoggerNumberOfSamples;

  dLoggerString = "";
  
  #if (_USE_RTC_ == 1)
  dLoggerString += RtcTimeStr;
  #else
  dLoggerString += timeHour;
  dLoggerString += ":";
  dLoggerString += timeMin;
  dLoggerString += ":";
  dLoggerString += timeSec;
  #endif
  
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
