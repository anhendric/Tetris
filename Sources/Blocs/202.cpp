
#include "peg.hpp"
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

ROMDATA UCHAR uc20Bitmap[32] = {
0xff,0xff,0xff,0xff,0xa4,0xa8,0xa8,0x89,0x80,0x02,0x02,0x21,0xca,0x20,0x20,0x05,
0x80,0x84,0x84,0x51,0xa2,0x11,0x11,0x03,0x88,0x44,0x44,0x29,0xff,0xff,0xff,0xff,
};
PegBitmap gb20Bitmap = { 0x00, 1, 32, 8, 0x000000ff, (UCHAR *) uc20Bitmap};

