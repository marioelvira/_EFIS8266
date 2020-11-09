#if (_USE_WDT_ == 1)

/////////////////////
// Watchdog set up //
/////////////////////
void _WdtSetup(void)
{
  Serial.printf("\n\nSdk version: %s\n",    ESP.getSdkVersion());
  Serial.printf("Core Version: %s\n",       ESP.getCoreVersion().c_str());
  Serial.printf("Boot Version: %u\n",       ESP.getBootVersion());
  Serial.printf("Boot Mode: %u\n",          ESP.getBootMode());
  Serial.printf("CPU Frequency: %u MHz\n",  ESP.getCpuFreqMHz());
  Serial.printf("Reset reason: %s\n",       ESP.getResetReason().c_str());

  ESP.wdtDisable();
  ESP.wdtEnable(1000);
  
  wdtForced = 0;
}

////////////////////////////
// Watchdog state machine //
////////////////////////////
void _WdtLoop(void)
{
  ESP.wdtFeed();

  if (wdtForced == 1)
  {
    while (1);
  }
}

#endif
