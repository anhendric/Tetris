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

#ifndef TETRIS_WINDOW_INCLUDED
#define TETRIS_WINDOW_INCLUDED


#define K_ONOFF	0x10
#define K_EXE 0x21
#define K_EXP 0x22
#define K_DOT 0x24
#define K_0 0x25
#define K_OPPOSIT 0x26
#define K_PLUS 0x31
#define K_3 0x32
#define K_2	0x34
#define K_1 0x35
#define K_COMMA 0x36
#define K_MINUS	0x41
#define K_6 0x42
#define K_5	0x44
#define K_4 0x45
#define K_RPAR 0x46
#define K_TIMES	0x51
#define K_9 0x52
#define K_Z 0x53
#define K_8 0x54
#define K_7 0x55
#define K_LPAR 0x56
#define K_DIV 0x61
#define K_POWER 0x62
#define K_LEFT 0x63
#define K_DOWN 0x64
#define K_Y 0x65
#define K_X 0x66
#define K_BACK 0x71
#define K_CLEAR 0x72
#define K_RIGHT 0x73
#define K_UP 0x74
#define K_KEYBOARD 0x75
#define K_EQUAL 0x76

typedef unsigned char KEY_CODE;

#include "ClassPad.h"
#include <stdlib.h>
#include <machine.h> 
#include "GaumerieLib/GaumerieLib.h"

// Traite les messages dans la fonction Message
#define GetMessage() PegMessage pSend;\
        if (MessageQueue()->PopNoIdle(&pSend))\
        {\
             int iReturn = Presentation()->DispatchMessage(Presentation(), &pSend);\
             if (iReturn) return iReturn;\
        }\
        if (GetSystemMessage(&pSend,IM_RCVTMO_POL))\
        {\
            if (pSend.wType==HM_SYS_CLEAR) pSend.pTarget = this;\
            if (pSend.wType==HM_SYS_CLOSE)\
            {\
                MessageQueue()->Push(pSend);\
                break;\
            }\
            MessageQueue()->Push(pSend);\
        }\
        1

class TetrisWindow : public PegWindow     
{
    public:
        KEY_CODE GB_LEFT;
        KEY_CODE GB_RIGHT;
        KEY_CODE GB_UP;
        KEY_CODE GB_DOWN;
        KEY_CODE GB_A;
        KEY_CODE GB_B;
        KEY_CODE GB_START;
        KEY_CODE GB_OFF;
        KEY_CODE GB_LOAD;
        KEY_CODE GB_SAVE;
        
        KEY_CODE* cpkptr[10];
        
        char highname[2][10][6][3][7];
        int highscore[2][10][6][3];
        
        char piece[4][2][7];
        char piecec[6][6];
        char state[12][19];
        char r[4][6];
        
        bool cheat;
        
        int nbrblock;
        char ch[2];
        char x,y;
        DWORD rot;
        
        DWORD score, level, period, high;
        int lines;
        DWORD scoreB[5];
        bool type;
        bool g_over;
        
        TetrisWindow(PegRect rec);
        virtual SIGNED Message(const PegMessage &Mesg);
        virtual SIGNED Execute();
        void GameOver();        
        bool Rotation();
        bool Lignes();
        void Ran();
        void High();
        void AfficheBlockInit();
        void AfficheBlock(int dg, int b);
        bool Test(int dg, int b);
        void DrawNumber(short x, short y, DWORD n);
        void DrawText(short x, short y, PEGCHAR* text, bool gray=0);
        void DrawText(short x, short y, DWORD num, bool gray=0);
        void DrawBrick(short x, short y, UCHAR z);
        void DrawMenu(int sel, int sel2);
        void DrawSetKMenu(int sel, bool set);
        void SetKeys();
        
        void LoadHighscore();
        void SaveHighscore();
        void AddHighscore(int sc, bool typ, int lvl, int hig);
};

extern "C" void Bevt_Request_LaunchMenu(void); // A utiliser pour quitter le programme

#endif
