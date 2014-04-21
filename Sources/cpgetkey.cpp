//    This file is part of Tetris (C)2006-2007 ClassPad.fr

//    Tetris is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.

//    Tetris is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with Foobar; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef WIN32

#include "cpgetkey.h"

#define   IO_BASE         0xA4000100
#define   IO_PBCR         0x00000002
#define   IO_PORTBASE      0xA4000120
#define   IO_PADR         0x00000000
#define   IO_PBDR         0x00000002

/*
 Check the status of a single key

 NOTE: code is a HEX encoded byte where the upper nibble is a
 row-scan and the lower nibble is a col-scan.
*/


int GetKey(KEY_CODE code)
{
   int i;
   int flag = 0;
   int ret = 1;
   unsigned char reg , ki , ko , kiMask , koMask;
   const unsigned short state[] = {
        0xAAA9u , 0xAAA6u , 0xAA9Au , 0xAA6Au ,
      0xA9AAu , 0xA6AAu , 0x9AAAu , 0x6AAAu
   };

    ki = (code) >> 4;
    ko = (code) & 0x0f;
   if (ki > 7 || ko >> 7)
    {
        return 0;
    }   

    kiMask = 0x01;
   kiMask <<= ki;
   koMask = 0x01;
   koMask <<= ko;

   set_gbr((VP)IO_BASE);
   gbr_write_word(IO_PBCR , state[ko]);
   set_gbr((VP)IO_PORTBASE);
   gbr_write_byte(IO_PBDR , ~koMask);

   for(i = 0 ; i < 5 ; i++)
    {
      reg = ~gbr_read_byte(IO_PADR);
      if(!(reg & kiMask))
         flag++;
   }
   if(flag)
   {
      ret = 0;
   }

   set_gbr((VP)IO_BASE);
   gbr_write_word(IO_PBCR , 0xAAAAu);
   gbr_write_word(IO_PBCR , 0x5555u);
   set_gbr((VP)IO_PORTBASE);
   gbr_write_byte(IO_PBDR , 0x00);
   return ret;
}

/*
 Check the status of the keyboard using a 8*8 (64) byte array
*/

int GetKeyboard(char* keybuffer)
{
   int i , j;
   KEY_CODE code;
   int ret = 0;
   for(i = 0 ; i < 8 ; i++)
    {
        code = i << 4;
       for(j = 0 ; j < 8 ; j++)
        {
            if (*keybuffer = GetKey(code)) ret = 1;
         code++;
         keybuffer++;
      }
   }   
   return ret;
} 
