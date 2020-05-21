/*************************************************************************************/
/* Base implementation around .js prior art here                                     */
/* https://github.com/tadakado/smart-meter/blob/master/Soft/OLD_spi/02_initialize.js */
/*************************************************************************************/
#include "ADE7816.h"
#include "SPI.h"

SPIClass spi;
ADE7816_SPI::ADE7816_SPI(uint8_t spi_bus)
{
spi = SPIClass(spi_bus);
 
}

void ADE7816_SPI::begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss)
{
    spi.begin(sck, miso, mosi, ss);
    Serial.println(_clock);
    _ss = ss;
    pinMode(_ss, OUTPUT);
    digitalWrite(_ss, HIGH);
    delay(1);
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(_ss, LOW);
        delayMicroseconds(10);
        digitalWrite(_ss, HIGH);
        delayMicroseconds(10);
    }
}

void ADE7816_SPI::settings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode){
    _clock=clock;
    _bitOrder=bitOrder;
    _dataMode=dataMode;
}

void ADE7816_SPI::writeRegister(uint16_t reg, uint16_t val)
{
    uint8_t fba=0x0;
    uint8_t hba=reg>>8;
    uint8_t lba=reg&0xff;
    uint8_t hbv=val>>8;
    uint8_t lbv=val&0xff;
    digitalWrite(_ss,LOW);
    spi.beginTransaction(SPISettings(_clock, _bitOrder, _dataMode));
    spi.transfer(fba);
    spi.transfer(hba);
    spi.transfer(lba);   
    spi.transfer(hbv);
    spi.transfer(lbv);   
    spi.endTransaction();
    digitalWrite(_ss,HIGH);

}

uint32_t ADE7816_SPI::readRegister(uint16_t reg)
{
    uint8_t fba=0x1;
    uint8_t hba=reg>>8;
    uint8_t lba=reg&0xff;
    uint32_t res=0;
    digitalWrite(_ss,LOW);
    spi.beginTransaction(SPISettings(_clock, _bitOrder, _dataMode));
    spi.transfer(fba);
    spi.transfer(hba);
    spi.transfer(lba);   
    uint8_t rb0=spi.transfer(0x0);
    uint8_t rb1=spi.transfer(0x0);
    uint8_t rb2=spi.transfer(0x0);
    uint8_t rb3=spi.transfer(0x0);
    res|=rb0;
    res=(res<<8)|rb1;
    res=(res<<8)|rb2;
    res=(res<<8)|rb3;
    spi.endTransaction();
    digitalWrite(_ss,HIGH);
    return res;
}

void ADE7816_SPI::runDsp()
{
    ADE7816_SPI::writeRegister(Run,1);
}
void ADE7816_SPI::stopDsp()
{
    writeRegister(Run,0);
}
