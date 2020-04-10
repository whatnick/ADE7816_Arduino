
#include <SPI.h>
#include "ADE7816.h"

ADE7816_SPI eic = ADE7816_SPI();

void setup()
{
  /* Initialize the serial port to host */
  Serial.begin(115200);
  eic.init();
}

void loop()
{

}