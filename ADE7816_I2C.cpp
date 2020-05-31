/***********************************************************************/
/* ADE7816 .c initial file from Linux implementation                   */
/*  https://github.com/andrew-gillan/energon/blob/master/scr/ADE7816.c */
/*  Thr above code implements an I2C variant of the ADE7816 Driver     */
/***********************************************************************/

#include "ADE7816.h"
#include "Wire.h"

ADE7816_I2C::ADE7816_I2C(int addr)
{
    _addr = addr;
    i2c.setClock(400000);
}

void ADE7816_I2C::begin()
{
    i2c.begin();
}

void ADE7816_I2C::writeRegister(uint16_t reg, uint16_t val)
{
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    uint8_t hbv = val >> 8;
    uint8_t lbv = val & 0xff;
    i2c.beginTransmission(_addr);
    i2c.write(hba);
    i2c.write(lba);
    i2c.write(hbv);
    i2c.write(lbv);
    i2c.endTransmission();
}

uint32_t ADE7816_I2C::readRegister(uint16_t reg)
{
    uint8_t rb0 = 0;
    uint8_t rb1 = 0;
    uint8_t rb2 = 0;
    uint8_t rb3 = 0;
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    uint32_t res = 0;
    i2c.beginTransmission(_addr);
    i2c.write(hba);
    i2c.write(lba);
    i2c.endTransmission(false);
    i2c.requestFrom((uint8_t)_addr, (uint8_t)4, (uint8_t) true);
    if (i2c.available() >= 1)
    {
        rb0 = i2c.read();
        rb1 = i2c.read();
        rb2 = i2c.read();
        rb3 = i2c.read();
    }
    res |= rb0;
    res = (res << 8) | rb1;
    res = (res << 8) | rb2;
    res = (res << 8) | rb3;
    return res;
}

void ADE7816_I2C::runDsp()
{
    ADE7816_I2C::writeRegister(Run, 1);
}

void ADE7816_I2C::stopDsp()
{
    writeRegister(Run, 0);
}

int ADE7816_I2C::_writeRegister(const unsigned int reg, const unsigned int val)
{
    return 0;
}
int ADE7816_I2C::_readRegister(const unsigned int reg)
{
    return 0;
}