//////////////
// IO setup //
//////////////
void _IOSetup(void)
{
  InPulsacion = NO_PULSACION;
  InCounter = 0;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop(void)
{ 
  if (InStatus_ant == inAux)
    InCounter++; // Incrementamos el contador.
  else
  {   
    // Si detectamos un flanco de bajada...
    if (InStatus_ant == 0)
    {
      if (InCounter > PULSACION_LARGA)
        InPulsacion = PULSACION_LARGA;
      else if (InCounter > PULSACION_CORTA)
        InPulsacion = PULSACION_CORTA;
      else
        InPulsacion = PULSACION_ERROR;

      #if (_IN_SERIAL_DEBUG_ == 1)
      if (InPulsacion == PULSACION_LARGA)
        Serial.println(">> IN -> Pulsacion Larga");
      else if (InPulsacion == PULSACION_CORTA)
        Serial.println(">> IN -> Pulsacion Corta");
      else
        Serial.println(">> IN -> Error Pulsacion");
      #endif
    }

    InCounter = 0;
  }

  InStatus_ant = inAux;
}
