//////////////////
// Vario set up //
//////////////////
void _VarioSetup(void)
{
  VarioPreviousAtlitude = 0;
  Vario_mps = 0;
}

/////////////////////////
// Vario state machine //
/////////////////////////
void _VarioLoop(void)
{
  VarioCurrentTime = millis();
  if (VarioCurrentTime - VarioPreviousTime >= VARIO_TICK)
  {
    Vario_mps = (VarioPreviousAtlitude - Altitude_m)*1000/(VarioPreviousTime - VarioCurrentTime); // m/s   
      
    if (units.vario == VARIO_FEETpM)
      Vario = 60*CONV_METERS_TO_FEET*Vario_mps;
    else if (units.vario == VARIO_MpM)
      Vario = 60*Vario_mps;
    /*
    else if (units.vario == VARIO_FEETpS)
      Vario = CONV_METERS_TO_FEET*Vario_mps;
    else if (units.vario == VARIO_MpS)
      Vario = Vario_mps;
    */
    
    #if (_VARIO_SERIAL_DEBUG_ == 1)
    Serial.print("---> Vario" );
    Serial.print(VarioValue);
    Serial.println(" m/s");
    #endif
    
    VarioPreviousAtlitude = Altitude_m;
    VarioPreviousTime = VarioCurrentTime;
  }
}
