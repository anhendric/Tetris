
#include "peg.hpp"
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

ROMDATA UCHAR uc21Bitmap[32] = {
0xff,0x89,0xa3,0x81,0xc9,0x83,0xa9,0x81,0x93,0xc1,0x8b,0xa1,0x83,0xd1,0x85,0xa1,
0x93,0xc1,0x8b,0xa1,0x83,0xd1,0x85,0xa1,0x83,0x91,0xc5,0x91,0xc3,0x89,0xa1,0xff,
};
PegBitmap gb21Bitmap = { 0x00, 1, 8, 32, 0x000000ff, (UCHAR *) uc21Bitmap};
