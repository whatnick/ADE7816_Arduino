/***********************************************************************/
/* ADE7816 .c initial file from Linux implementation                   */
/*  https://github.com/andrew-gillan/energon/blob/master/scr/ADE7816.c */
/*  Thr above code implements an I2C variant of the ADE7816 Driver     */
/***********************************************************************/

#include "ADE7816.h"

ADE7816_I2C::ADE7816_I2C(int addr)
{
    _addr = addr;
}