
#include <SPI.h>
#include "ADE7816.h"


//initialise spi with default pins
//SCLK = 18, MISO = 19, MOSI = 23, SS = 5

const int8_t sck = 5;
const int8_t miso = 19;
const int8_t mosi = 18;
const int8_t ss = 33;
uint32_t vrms = 0;
uint32_t ia_rms = 0;
uint32_t ib_rms = 0;
uint32_t ic_rms = 0;
uint32_t id_rms = 0;
uint32_t ie_rms = 0;
uint32_t if_rms = 0;

ADE7816_SPI eic = ADE7816_SPI(VSPI);

void setup()
{

  /* Initialize the serial port to host */
  Serial.begin(115200);
  eic.settings(200000, MSBFIRST, SPI_MODE3);
  eic.begin(sck, miso, mosi, ss);
  eic.runDsp();
  eic.runDsp();
  eic.runDsp();
  for (int i = 0; i < 10; i++)
  {
    vrms = eic.readRegister(VRMS);
    Serial.print("VRMS=");
    Serial.println(vrms);
  }
  for (int i = 0; i < 10; i++)
  {
    ia_rms = eic.readRegister(IARMS);
    ib_rms = eic.readRegister(IBRMS);
    ic_rms = eic.readRegister(ICRMS);
    id_rms = eic.readRegister(IDRMS);
    ie_rms = eic.readRegister(IERMS);
    if_rms = eic.readRegister(IFRMS);
    Serial.print("IRMS ");
    Serial.print(ia_rms);
    Serial.print(" ");
    Serial.print(ib_rms);
    Serial.print(" ");
    Serial.print(ic_rms);
    Serial.print(" ");
    Serial.print(id_rms);
    Serial.print(" ");
    Serial.print(ie_rms);
    Serial.print(" ");
    Serial.println(if_rms);
  }
  eic.stopDsp();
  eic.stopDsp();
  eic.stopDsp();
  for (int i = 0; i < 10; i++)
  {
    vrms = eic.readRegister(VRMS);
    Serial.print("VRMS=");
    Serial.println(vrms);
  }

}

void loop()
{

}
