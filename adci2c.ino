//////////////////
// ADCI2C setup //
//////////////////
void _ADCI2CSetup(void)
{
  adsStatus = ADS_DETECTION;
  adsInfo = "";
}

//////////////////////////
// ADCI2C state machine //
//////////////////////////
void _ADCI2CLoop(void)
{ 
  int16_t adc0, adc1, adc2, adc3;

  switch (adsStatus)
  {
    case ADS_DETECTION:
    
      // Initialise the sensor...
      ads1015.begin(ADS_I2C_ADDRESS);

      // The ADC input range (or gain) can be changed via the following
      // functions, but be careful never to exceed VDD +0.3V max, or to
      // exceed the upper and lower limits if you adjust the input range!
      // Setting these values incorrectly may destroy your ADC!
      //                                                                ADS1015  ADS1115
      //                                                                -------  -------
      // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
      // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
      // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
      // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
      // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
      // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
      
      #if (_ADCI2C_SERIAL_DEBUG_ == 1)
      Serial.println("ADC ADS1015 detected...");
      #endif

      adsTickReconnect = millis();

      adsStatus = ADS_WORKING;
      adsNConnec++;
      
      break;

    case ADS_WORKING:

      delay(50); // 50 ms ??

      if (millis() - adsTickReconnect >= 1000)
      {
        adc0 = ads1015.readADC_SingleEnded(0);
        adc1 = ads1015.readADC_SingleEnded(1);
        adc2 = ads1015.readADC_SingleEnded(2);
        adc3 = ads1015.readADC_SingleEnded(3);

        #if (_ADCI2C_SERIAL_DEBUG_ == 1)
        Serial.print("ADC I2C AIN0: "); Serial.println(adc0);
        Serial.print("ADC I2C AIN1: "); Serial.println(adc1);
        Serial.print("ADC I2C AIN2: "); Serial.println(adc2);
        Serial.print("ADC I2C AIN3: "); Serial.println(adc3);
        Serial.println(" ");
        #endif
        
        adsTickReconnect = millis();
      }
    
      break;
      
      
  }
}
