///////////////
// RTC setup //
///////////////
void _RtcSetup(void)
{
  rtcObject.Begin();
 
  RtcTime = RtcDateTime(21, 01, 25, 21, 20, 0);
  rtcObject.SetDateTime(RtcTime);
  
  RtcStatus = RTC_START;
}

///////////////////////
// RTC state machine //
///////////////////////
void _RtcLoop(void)
{
  switch (RtcStatus)
  {
    case RTC_START:
      RtcStatus = DLOGGER_RECORD;

      RtcCurrentTime = millis();
      RtcPreviousTime = RtcCurrentTime;
      break;

    case RTC_READ:
      RtcCurrentTime = millis();
      if (RtcCurrentTime - RtcPreviousTime >= RTC_TICK)
      {
        RtcTime = rtcObject.GetDateTime();
        
        sprintf(RtcTimeStr, "%d/%d/%d %d:%d:%d",
            RtcTime.Year(),   //get year method
            RtcTime.Month(),  //get month method
            RtcTime.Day(),    //get day method
            RtcTime.Hour(),   //get hour method
            RtcTime.Minute(), //get minute method
            RtcTime.Second()  //get second method
        );

        #if (_RTC_SERIAL_DEBUG_ == 1)
        Serial.println("Rtc date...");
        Serial.println(RtcTimeStr);
        #endif
        
        RtcPreviousTime = RtcCurrentTime;
      }
      break;
  }
}
