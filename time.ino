
/////////////////
// Time set up //
/////////////////
void _TimeSetup(void)
{
  timeTick = millis();
  timeSec = 0;
  timeMin = 0;
  timeHour = 0;
}

////////////////////////
// Time state machine //
////////////////////////
void _TimeLoop(void)
{
  timeMilisec = millis();
  
  if (millis() - timeTick >= 1000)
  {
    timeSec++;
    if (timeSec >= 60)
    {
      timeSec = 0;
      timeMin++;
      if (timeMin >= 60)
      {
        timeSec = 0;
        timeHour++;
      }
    }
    
    timeTick = millis();
  }

  #if (_TICK_SERIAL_DEBUG_ == 1)
  Serial.print(timeMilisec);
  Serial.println(" milis");
  #endif
}
