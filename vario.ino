//////////////////
// Vario set up //
//////////////////
void _VarioSetup(void)
{
  VarioCurrentAtlitude = 0;
  VarioPreviousAtlitude = 0;
  VarioValue = 0;
}

/////////////////////////
// Vario state machine //
/////////////////////////
void _VarioLoop(void)
{
  VarioCurrentAtlitude = altitude;
  VarioCurrentTime = millis();
  if (VarioCurrentTime - VarioPreviousTime >= VARIO_TICK)
  {
    VarioValue = (VarioPreviousAtlitude - VarioCurrentAtlitude)*1000/(VarioPreviousTime - VarioCurrentTime); // m/s 

    #if (_VARIO_SERIAL_DEBUG_ == 1)
    Serial.print("---> Vario" );
    Serial.print(VarioValue);
    Serial.println(" m/s");
    #endif
    
    VarioPreviousAtlitude = VarioCurrentAtlitude;
    VarioPreviousTime = VarioCurrentTime;
  }
}
