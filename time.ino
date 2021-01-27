
/////////////////
// Time set up //
/////////////////
void _TimeSetup(void)
{
  timeTick = millis();

  #if (_USE_RTC_ == 1)
  rtcObject.Begin();
  
  //RtcTime = RtcDateTime(21, 01, 27, 17, 59, 0);
  //rtcObject.SetDateTime(RtcTime);
  #else
  timeSec = 0;
  timeMin = 0;
  timeHour = 0;
  #endif
}

////////////////////////
// Time state machine //
////////////////////////
void _TimeLoop(void)
{
  timeMilisec = millis();
  
  if (millis() - timeTick >= 1000)
  {
    #if (_USE_RTC_ == 1)
    _RtcReadDate();
    #else
    timeSec++;
    if (timeSec >= 60)
    {
      timeSec = 0;
      timeMin++;
      if (timeMin >= 60)
      {
        timeMin = 0;
        timeHour++;
      }
    }
    #endif
    
    timeTick = millis();
  }

  #if (_TICK_SERIAL_DEBUG_ == 1)
  Serial.print(timeMilisec);
  Serial.println(" milis");
  #endif
}

#if (_USE_RTC_ == 1)
void _RtcReadDate(void)
{
  RtcTime = rtcObject.GetDateTime();

  RtcTimeStr = String(RtcTime.Year());
  RtcTimeStr = RtcTimeStr + "/" + String(RtcTime.Month());
  RtcTimeStr = RtcTimeStr + "/" + String(RtcTime.Day());
  RtcTimeStr = RtcTimeStr + " " + String(RtcTime.Hour());
  RtcTimeStr = RtcTimeStr + ":" + String(RtcTime.Minute());
  RtcTimeStr = RtcTimeStr + ":" + String(RtcTime.Second());

  /*  
  sprintf(RtcTimeStr, "%d/%d/%d %d:%d:%d",
          RtcTime.Year(),   //get year method
          RtcTime.Month(),  //get month method
          RtcTime.Day(),    //get day method
          RtcTime.Hour(),   //get hour method
          RtcTime.Minute(), //get minute method
          RtcTime.Second()  //get second method
  );
  */
}
#endif
