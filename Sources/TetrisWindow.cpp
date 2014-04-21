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

#include "TetrisWindow.h"
#include "bitmaps.h"
#include "cpgetkey.h"

// Coordonnées des affichages des numéros de level
int XLvl[] = {41 , 57 , 73 , 89 , 105, 41 , 57 , 73 , 89 , 105};
int YLvl[] = {109, 109, 109, 109, 109, 125, 125, 125, 125, 125};
//X-24 pour B-Type

// Coordonnées des affichages des numéros de hauteur en B-Type
int XHig[] = {105, 121, 137, 105, 121, 137};
int YHig[] = {109, 109, 109, 125, 125, 125};

char bindex[]={0,1,2,3,7,10,11,12,13};
int linescore[] = {40, 100, 300, 1200};

PEGCHAR gbkeys[12][10] = {"left", "right", "up", "down", "button a", "button b", "start", "power", "save", "load"};
PEGCHAR* cpkeys(KEY_CODE code)
{
    switch(code){
        case K_ONOFF:   return "on/off";
        case K_KEYBOARD:return "keyboard";
        case K_BACK:    return "<";
        case K_CLEAR:   return "clear";
        case K_LEFT:    return "left";
        case K_RIGHT:   return "right";
        case K_UP:      return "up";
        case K_DOWN:    return "down";
        case K_EQUAL:   return "=";
        case K_X:       return "x";
        case K_Y:       return "y";
        case K_Z:       return "z";
        case K_POWER:   return "^";
        case K_LPAR:    return "(";
        case K_RPAR:    return ")";
        case K_COMMA:   return ",";
        case K_OPPOSIT: return "(-)";
        case K_TIMES:   return "*";
        case K_MINUS:   return "-";
        case K_PLUS:    return "+";
        case K_EXE:     return "exe";
        case K_EXP:     return "exp";
        case K_DOT:     return ".";
        case K_0:       return "0";
        case K_1:       return "1";
        case K_2:       return "2";
        case K_3:       return "3";
        case K_4:       return "4";
        case K_5:       return "5";
        case K_6:       return "6";
        case K_7:       return "7";
        case K_8:       return "8";
        case K_9:       return "9";
    }
    return "";
}

////////////////////////////////////////

TetrisWindow::TetrisWindow(PegRect rect):PegWindow(rect, FF_NONE)
{
    for(int i=0;i<12;i++)
    {
        for(int j=0;j<19;j++)
        {
            state[i][j]=0;
            state[0][j]=1;
            state[11][j]=1;
            state[i][18]=1;
        }
    }

    piece[0][0][0]=0; piece[1][0][0]=1; piece[2][0][0]=1; piece[3][0][0]=0;
    piece[0][1][0]=0; piece[1][1][0]=1; piece[2][1][0]=1; piece[3][1][0]=0;

    piece[0][0][1]=2; piece[1][0][1]=2; piece[2][0][1]=0; piece[3][0][1]=0;
    piece[0][1][1]=0; piece[1][1][1]=2; piece[2][1][1]=2; piece[3][1][1]=0;

    piece[0][0][2]=3; piece[1][0][2]=3; piece[2][0][2]=3; piece[3][0][2]=0;
    piece[0][1][2]=0; piece[1][1][2]=3; piece[2][1][2]=0; piece[3][1][2]=0;
    
    piece[0][0][3]=4; piece[1][0][3]=5; piece[2][0][3]=5; piece[3][0][3]=6; 
    piece[0][1][3]=0; piece[1][1][3]=0; piece[2][1][3]=0; piece[3][1][3]=0; 
     
    piece[0][0][4]=0; piece[1][0][4]=10; piece[2][0][4]=10; piece[3][0][4]=0;
    piece[0][1][4]=10; piece[1][1][4]=10; piece[2][1][4]=0; piece[3][1][4]=0;

    piece[0][0][5]=11; piece[1][0][5]=11; piece[2][0][5]=11; piece[3][0][5]=0;
    piece[0][1][5]=0; piece[1][1][5]=0; piece[2][1][5]=11; piece[3][1][5]=0;

    piece[0][0][6]=0; piece[1][0][6]=0; piece[2][0][6]=12; piece[3][0][6]=0;
    piece[0][1][6]=12; piece[1][1][6]=12; piece[2][1][6]=12; piece[3][1][6]=0;
    
    score=0; lines=0; level=0;
    nbrblock=0;
    x=4; y=-1;
    
    r[0][0]=1;  r[1][0]=2;  r[2][0]=3;  r[3][0]=2;
    r[0][1]=1;  r[1][1]=0;  r[2][1]=-1; r[3][1]=0;
    r[0][2]=0;  r[1][2]=-1; r[2][2]=0;  r[3][2]=1;
    r[0][3]=2;  r[1][3]=1;  r[2][3]=2;  r[3][3]=3;
    r[0][4]=0;  r[1][4]=1;  r[2][4]=0;  r[3][4]=-1;
    r[0][5]=1;  r[1][5]=0;  r[2][5]=-1; r[3][5]=0;

    // Tableau de pointeurs vers les différentes variables de touches
    cpkptr[0]=&GB_LEFT;
    cpkptr[1]=&GB_RIGHT;
    cpkptr[2]=&GB_UP;
    cpkptr[3]=&GB_DOWN;
    cpkptr[4]=&GB_A;
    cpkptr[5]=&GB_B;
    cpkptr[6]=&GB_START;
    cpkptr[7]=&GB_OFF;
    cpkptr[8]=&GB_LOAD;
    cpkptr[9]=&GB_SAVE;
}

////////////////////////////////

void TetrisWindow::LoadHighscore()
{
    CPReadMCSFile r0("tetrisOp", "Tetris", IMU_MCS_TypeMem);
    CPMEMFileHeader h0("Tetris", "Options");
    if(r0.FileExists())
    {
        r0.Open();
        h0.Read(r0);
        if(!r0.IsNotError()) Bevt_Request_LaunchMenu();
        GB_LEFT  = r0.ReadByte();
        GB_RIGHT = r0.ReadByte();
        GB_UP    = r0.ReadByte();
        GB_DOWN  = r0.ReadByte();
        GB_A     = r0.ReadByte();
        GB_B     = r0.ReadByte();
        GB_START = r0.ReadByte();
        GB_OFF   = r0.ReadByte();
        GB_LOAD  = r0.ReadByte();
        GB_SAVE  = r0.ReadByte();
        r0.Close();
    }
    else
    {
        UCHAR temp;
        BMCSCreateFolder("Tetris", &temp);
        CPWriteMCSFile w0("tetrisOp", "Tetris", IMU_MCS_TypeMem);
        GB_LEFT  = K_LEFT;
        GB_RIGHT = K_RIGHT;
        GB_UP    = K_UP;
        GB_DOWN  = K_DOWN;
        GB_A     = K_KEYBOARD;
        GB_B     = K_BACK;
        GB_START = K_EXE;
        GB_OFF   = K_ONOFF;
        GB_LOAD  = K_COMMA;
        GB_SAVE  = K_RPAR;
        h0.Write(w0);
        w0.WriteByte(GB_LEFT);
        w0.WriteByte(GB_RIGHT);
        w0.WriteByte(GB_UP);
        w0.WriteByte(GB_DOWN);
        w0.WriteByte(GB_A);
        w0.WriteByte(GB_B);
        w0.WriteByte(GB_START);
        w0.WriteByte(GB_OFF);
        w0.WriteByte(GB_LOAD);
        w0.WriteByte(GB_SAVE);
        w0.Realize();
        h0.Write(w0);
        w0.WriteByte(GB_LEFT);
        w0.WriteByte(GB_RIGHT);
        w0.WriteByte(GB_UP);
        w0.WriteByte(GB_DOWN);
        w0.WriteByte(GB_A);
        w0.WriteByte(GB_B);
        w0.WriteByte(GB_START);
        w0.WriteByte(GB_OFF);
        w0.WriteByte(GB_LOAD);
        w0.WriteByte(GB_SAVE);
    }
    
    CPReadMCSFile r("tetrisHi", "Tetris", IMU_MCS_TypeMem);
    CPMEMFileHeader h("Tetris", "Hiscore");
    if(r.FileExists())
    {
        r.Open();
        h.Read(r);
        if(!r.IsNotError()) Bevt_Request_LaunchMenu();
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<3;j++)
            {
                r.ReadBytes(highname[0][i][0][j], 7*sizeof(char));
                highscore[0][i][0][j] = r.ReadInt();
            }
        }
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<6;j++)
            {
                for(int k=0;k<3;k++)
                {
                    r.ReadBytes(highname[1][i][j][k], 7*sizeof(char));
                    highscore[1][i][j][k] = r.ReadInt();
                }
            }
        }
        r.Close();
    }
    else
    {
        UCHAR temp;
        BMCSCreateFolder("Tetris", &temp);
        CPWriteMCSFile w("tetrisHi", "Tetris", IMU_MCS_TypeMem);
        h.Write(w);
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<3;j++)
            {
                memset(highname[0][i][0][j], 0, 7*sizeof(char));
                highscore[0][i][0][j] = 0;
                w.WriteBytes(highname[0][i][0][j], 7*sizeof(char));
                w.WriteInt(0);
            }
        }
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<6;j++)
            {
                for(int k=0;k<3;k++)
                {
                    memset(highname[1][i][j][k], 0, 7*sizeof(char));
                    highscore[1][i][j][k] = 0;
                    w.WriteBytes(highname[1][i][j][k], 7*sizeof(char));
                    w.WriteInt(0);
                }
            }
        }
        w.Realize();
        h.Write(w);
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<3;j++)
            {
                memset(highname[0][i][0][j], 0, 7*sizeof(char));
                highscore[0][i][0][j] = 0;
                w.WriteBytes(highname[0][i][0][j], 7*sizeof(char));
                w.WriteInt(0);
            }
        }
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<6;j++)
            {
                for(int k=0;k<3;k++)
                {
                    memset(highname[1][i][j][k], 0, 7*sizeof(char));
                    highscore[1][i][j][k] = 0;
                    w.WriteBytes(highname[1][i][j][k], 7*sizeof(char));
                    w.WriteInt(0);
                }
            }
        }
    }
}

void TetrisWindow::SaveHighscore()
{
    CPMEMFileHeader h0("Tetris", "Options");
    BMCSDeleteVariable((CP_CHAR*)"Tetris", (CP_CHAR*)"tetrisOp");
    CPWriteMCSFile w0("tetrisOp", "Tetris", IMU_MCS_TypeMem);
    h0.Write(w0);
    w0.WriteByte(GB_LEFT);
    w0.WriteByte(GB_RIGHT);
    w0.WriteByte(GB_UP);
    w0.WriteByte(GB_DOWN);
    w0.WriteByte(GB_A);
    w0.WriteByte(GB_B);
    w0.WriteByte(GB_START);
    w0.WriteByte(GB_OFF);
    w0.WriteByte(GB_LOAD);
    w0.WriteByte(GB_SAVE);
    w0.Realize();
    h0.Write(w0);
    w0.WriteByte(GB_LEFT);
    w0.WriteByte(GB_RIGHT);
    w0.WriteByte(GB_UP);
    w0.WriteByte(GB_DOWN);
    w0.WriteByte(GB_A);
    w0.WriteByte(GB_B);
    w0.WriteByte(GB_START);
    w0.WriteByte(GB_OFF);
    w0.WriteByte(GB_LOAD);
    w0.WriteByte(GB_SAVE);
    BMCSDeleteVariable((CP_CHAR*)"Tetris", (CP_CHAR*)"tetrisHi");
    CPWriteMCSFile w("tetrisHi", "Tetris", IMU_MCS_TypeMem);
    CPMEMFileHeader h("Tetris", "Hiscore");
    h.Write(w);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<3;j++)
        {
            w.WriteBytes(highname[0][i][0][j], 7*sizeof(char));
            w.WriteInt(highscore[0][i][0][j]);
        }
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<6;j++)
        {
            for(int k=0;k<3;k++)
            {
                w.WriteBytes(highname[1][i][j][k], 7*sizeof(char));
                w.WriteInt(highscore[1][i][j][k]);
            }
        }
    }
    w.Realize();
    h.Write(w);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<3;j++)
        {
            w.WriteBytes(highname[0][i][0][j], 7*sizeof(char));
            w.WriteInt(highscore[0][i][0][j]);
        }
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<6;j++)
        {
            for(int k=0;k<3;k++)
            {
                w.WriteBytes(highname[1][i][j][k], 7*sizeof(char));
                w.WriteInt(highscore[1][i][j][k]);
            }
        }
    }
}

void TetrisWindow::AddHighscore(int sc, bool typ, int lvl, int hig)
{
    if(!typ) hig=0;
    char _r = 3;
    for(int i=0;i<3;i++)
    {
        if(sc>highscore[typ][lvl][hig][i]) {_r = i;break;}
    }
    if(_r==3) return; // Pas de highscore obtenu
    
    for(int i=1;i>=_r;i--)
    {
        for(int j=0;j<7;j++)
        {
            highname[typ][lvl][hig][i+1][j] = highname[typ][lvl][hig][i][j];
        }
        highscore[typ][lvl][hig][i+1] = highscore[typ][lvl][hig][i];
    }
    for(int j=0;j<7;j++)
    {
        highname[typ][lvl][hig][_r][j] = 0;
    }
    highscore[typ][lvl][hig][_r] = 0;
    
    SH3Timer::SetTimerFreq(SH3Timer::TIMER_2, 20000);
    SH3Timer::SetCount(SH3Timer::TIMER_2, 0);
    
    SH3Timer::Start(SH3Timer::TIMER_2);
    
    DrawMenu((typ ? 2:1), (typ ? hig:lvl));
    DrawNumber(137,165+8*_r, sc);
    bool g = true;
    PEGCHAR hiname[7] = {'\0'};
    int f=0, c=0;
    while(c<6)
    {
        while(1)
        {
            if(GetKey(GB_UP))
            {
                if(f++==29) f=0;
                while(GetKey(GB_UP));
            }
            else if(GetKey(GB_DOWN))
            {
                if(!f--) f=29;
                while(GetKey(GB_DOWN));
            }
            else if(GetKey(GB_A))
            {
                hiname[c++]=tfont[f];
                f=0;
                break;
            }
            else if(GetKey(GB_B) && c>0)
            {
                hiname[c--]='\0';
                f = hiname[c];
                if(f>='a' && f<='z') f-='a';
                else if(f=='.') f=26;
                else if(f=='-') f=27;
                else if(f=='*') f=28;
                else if(f==' ') f=29;
                break;
            }
            else if(GetKey(GB_START))
            {
                hiname[c]=tfont[f];
                c=6;
                break;
            }
            if(SH3Timer::HasUnderflowed(SH3Timer::TIMER_2))
            {
                g = !g;
                if(g) DrawBitmap2(font[f], 32+8*c, 165+8*_r, &screen);
                else  DrawBitmap2(font[29], 32+8*c, 165+8*_r, &screen);
            }
        }
        DrawMenu((typ ? 2:1), (typ ? hig:lvl));
        DrawText(33, 165+8*_r, hiname);
        DrawNumber(137,165+8*_r, sc);
        while(GetKey(GB_A) || GetKey(GB_B) || GetKey(GB_START));
    }
    
    for(int j=0;j<7;j++) {highname[typ][lvl][hig][_r][j] = hiname[j];}
    highscore[typ][lvl][hig][_r] = sc;
    
    SH3Timer::Stop(SH3Timer::TIMER_2);
}

////////////////////////////////

void TetrisWindow::Ran()
{
    //OBCD l = cast_to_OBCD(0), u1 = cast_to_OBCD(6), r1;
    //Cal_Random(1, &l, &u1, &r1);
    ch[(nbrblock+1)%2] = rand()%7; // valeurs de 0 à 7 exclus (de 0 à 6 inclus donc)
}

void TetrisWindow::High()
{
    for(int j=0;j<2*high;j++)
    {
        int d=0;
        for(int i=1;i<11;i++)
        {
            //OBCD l = cast_to_OBCD(0), u1 = cast_to_OBCD(10), r1;
            //Cal_Random(1, &l, &u1, &r1);
            char ran=rand()%14;
            if (ran>8) ran=0;
            if (ran && d!=10)
            {
                d++;
                state[i][17-j]=bindex[ran];
                DrawBrick(i,17-j,bindex[ran]);
            }
        }
    }
}

void TetrisWindow::AfficheBlockInit()
{
    rot=0;

    piecec[0][0]=0; piecec[1][0]=0; piecec[2][0]=0; piecec[3][0]=0; piecec[4][0]=0; piecec[5][0]=0;
    piecec[0][1]=0; piecec[1][1]=0; piecec[2][1]=0; piecec[3][1]=0; piecec[4][1]=0; piecec[5][1]=0;
    piecec[0][2]=0; piecec[1][2]=0; piecec[2][2]=0; piecec[3][2]=0; piecec[4][2]=0; piecec[5][2]=0;
    piecec[0][3]=0; piecec[1][3]=0; piecec[2][3]=0; piecec[3][3]=0; piecec[4][3]=0; piecec[5][3]=0;
    piecec[0][4]=0; piecec[1][4]=0; piecec[2][4]=0; piecec[3][4]=0; piecec[4][4]=0; piecec[5][4]=0;
    piecec[0][5]=0; piecec[1][5]=0; piecec[2][5]=0; piecec[3][5]=0; piecec[4][5]=0; piecec[5][5]=0;

    DrawBrick(14,14,14); // On efface le coin inférieur droit            

    for(int a=0;a<4;a++)
    {
        for(int b=0;b<2;b++)
        {
            piecec[a+1][b+2]=piece[a][b][ch[nbrblock%2]];
            if (piece[a][b][ch[nbrblock%2]]!=0) DrawBrick(a+x,b+y+1,piece[a][b][ch[nbrblock%2]]);
            if (piece[a][b][ch[(nbrblock+1)%2]]!=0) DrawBrick(a+14,b+14,piece[a][b][ch[(nbrblock+1)%2]]);             
                
        }
    }
}


void TetrisWindow::AfficheBlock(int dg, int b)
{
    if (ch[nbrblock%2]==3)
    {
        if (rot%2==0)
        {
             DrawBrick(x-dg,y+1-b,15);
             DrawBrick(x,y+1,20);
        }        
        else
        {
            DrawBrick(x+1-dg,y-b,16);
            DrawBrick(x+1,y,21);
        }    
    }    
    else
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if (piecec[i+1][j+1]!=0)
                {
                    if (piecec[i+1-dg][j+1-b]==0)
                    {
                        DrawBrick(i+x-dg,j+y-b,0);
                    }    
                    if (piecec[i+1+dg][j+1+b]==0)
                    {
                        DrawBrick(i+x,j+y,piecec[i+1][j+1]);
                    }        
                }
            }
        }
    }
}

bool TetrisWindow::Rotation()
{
    int z=3;
    
    if (ch[nbrblock%2]==3) z=4;
    
    for(int i=0;i<z;i++)
    {
        for(int j=0;j<z;j++)
        {
            if (state[x+i][y+j]!=0) return 0;
        }
    }

    rot++;
    
    piecec[0][0]=0; piecec[1][0]=0; piecec[2][0]=0; piecec[3][0]=0; piecec[4][0]=0; piecec[5][0]=0;
    piecec[0][1]=0; piecec[1][1]=0; piecec[2][1]=0; piecec[3][1]=0; piecec[4][1]=0; piecec[5][1]=0;
    piecec[0][2]=0; piecec[1][2]=0; piecec[2][2]=0; piecec[3][2]=0; piecec[4][2]=0; piecec[5][2]=0;
    piecec[0][3]=0; piecec[1][3]=0; piecec[2][3]=0; piecec[3][3]=0; piecec[4][3]=0; piecec[5][3]=0;
    piecec[0][4]=0; piecec[1][4]=0; piecec[2][4]=0; piecec[3][4]=0; piecec[4][4]=0; piecec[5][4]=0;
    piecec[0][5]=0; piecec[1][5]=0; piecec[2][5]=0; piecec[3][5]=0; piecec[4][5]=0; piecec[5][5]=0;   

    if (ch[nbrblock%2]==3)
    {
        if (rot%2==0)
        {        
            DrawBrick(x+1,y,16);
            piecec[1][2]=4; piecec[2][2]=5; piecec[3][2]=5; piecec[4][2]=6;
            DrawBrick(x,y+1,20);
        }
        else
        {
            DrawBrick(x,y+1,15);
            piecec[2][1]=7; piecec[2][2]=8; piecec[2][3]=8; piecec[2][4]=9;
            DrawBrick(x+1,y,21);
        }        
        return 0;
    }    

    DrawBrick(x,y,17);
    char a,b;
        
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<2;j++)
        {
            if (piece[i][j][ch[nbrblock%2]]!=0)
            {
                a=r[rot%4][0] + i * r[rot%4][1] + j* r[rot%4][2];
                b=r[rot%4][3] + i * r[rot%4][4] + j* r[rot%4][5];
                piecec[a][b]=piece[i][j][ch[nbrblock%2]];
                DrawBrick(a-1+x,b-1+y,piecec[a][b]);
            }    
        }
    }
    return 1;
}

bool TetrisWindow::Test(int dg, int b)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if (piecec[i+1][j+1]!=0 && piecec[i+1+dg][j+1+b]==0)
            {
                if (state[i+x+dg][j+y+b]) return 0;
            }
        }
    }
    return 1;
}


bool TetrisWindow::Lignes()
{
    int d; int dec[4]={0,0,0,0};
    int i;
    
    d=0;
    
    for(int j=0;j<4;j++)
    {
        if (y+j<=17)
        {
            i=0; 
            while (i<11 && state[i][y+j])
            {
                i++;
            }
            if (state[i][y+j])
            {          
                //DrawBrick(1,y+j,19);
                dec[d]=y+j;
                d++;
                if(type)
                {
                    --lines;
                }    
                else
                {
                    if(++lines == 10*(level+1))
                    {
                        level++;
                        if(period - 5000 > 0)
                        {
                            period -= 5000;
                            SH3Timer::SetTimerFreq(SH3Timer::TIMER_2, period);
                        }
                    }
                }        
            }
        }
    }

    if(!d) return 0;
    
    score += linescore[d-1]*(level+1);
    scoreB[d-1]++;
    
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<d;j++)
        {
            DrawBrick(1,dec[j],19-(i%2));
        }
        for(int k=0;k<1000000;k++);
    }
    
    for (int b=0;b<d;b++)
    {
        for(int j=dec[b];j>=1;j--)
        {
            for(int i=1;i<11;i++)
            {
                state[i][j]=state[i][j-1];
                DrawBrick(i,j,state[i][j]);
            }    
        }
    }
    return 1;                   
}    

//////////////////////////

// Score:145,86
// Level:142,118
// Lines:142,142

void TetrisWindow::DrawNumber(short x, short y, DWORD n) // Dessine un nombre, où x et y sont les coordonnées du dernier numéro
{
    x--;
    CP_CHAR str[10];
    CP_IntToString(n, str);
    for(int i=0, j=CP_StringLen(str)-1;j>=0;i++,j--)
    {
        DrawBitmap2(number[str[j]-'0'], x-8*i, y, &screen);
    }
}

void TetrisWindow::DrawText(short x, short y, PEGCHAR* text, bool gray)
{
    x--;
    if(gray)
    {
        for(int i=0;i<strlen(text);i++)
        {
            char c = text[i];
            if(c>='a' && c<='z')      DrawBitmap2(gfont[c-'a'], x+8*i, y, &screen);
            else if(c>='0' && c<='9') DrawBitmap2(gnumber[c-'0'], x+8*i, y, &screen);
            else if(c=='.')           DrawBitmap2(gfont[26], x+8*i, y, &screen);
            else if(c=='-')           DrawBitmap2(gfont[27], x+8*i, y, &screen);
            else if(c=='*')           DrawBitmap2(gfont[28], x+8*i, y, &screen);
            else if(c==' ')           DrawBitmap2(gfont[29], x+8*i, y, &screen);
            else if(c=='^')           DrawBitmap2(gspec[0], x+8*i, y, &screen);
            else if(c=='<')           DrawBitmap2(gspec[1], x+8*i, y, &screen);
            else if(c=='+')           DrawBitmap2(gspec[2], x+8*i, y, &screen);
            else if(c==',')           DrawBitmap2(gspec[3], x+8*i, y, &screen);
            else if(c=='/')           DrawBitmap2(gspec[4], x+8*i, y, &screen);
            else if(c==')')           DrawBitmap2(gspec[5], x+8*i, y, &screen);
            else if(c=='(')           DrawBitmap2(gspec[6], x+8*i, y, &screen);
            else if(c=='=')           DrawBitmap2(gspec[7], x+8*i, y, &screen);
        }
    }
    else
    {
        for(int i=0;i<strlen(text);i++)
        {
            char c = text[i];
            if(c>='a' && c<='z')      DrawBitmap2(font[c-'a'], x+8*i, y, &screen);
            else if(c>='0' && c<='9') DrawBitmap2(number[c-'0'], x+8*i, y, &screen);
            else if(c=='.')           DrawBitmap2(font[26], x+8*i, y, &screen);
            else if(c=='-')           DrawBitmap2(font[27], x+8*i, y, &screen);
            else if(c=='*')           DrawBitmap2(font[28], x+8*i, y, &screen);
            else if(c==' ')           DrawBitmap2(font[29], x+8*i, y, &screen);
            else if(c=='^')           DrawBitmap2(spec[0], x+8*i, y, &screen);
            else if(c=='<')           DrawBitmap2(spec[1], x+8*i, y, &screen);
            else if(c=='+')           DrawBitmap2(spec[2], x+8*i, y, &screen);
            else if(c==',')           DrawBitmap2(spec[3], x+8*i, y, &screen);
            else if(c=='/')           DrawBitmap2(spec[4], x+8*i, y, &screen);
            else if(c==')')           DrawBitmap2(spec[5], x+8*i, y, &screen);
            else if(c=='(')           DrawBitmap2(spec[6], x+8*i, y, &screen);
            else if(c=='=')           DrawBitmap2(spec[7], x+8*i, y, &screen);
        }
    }    
}

void TetrisWindow::DrawText(short x, short y, DWORD num, bool gray)
{
    x--;
    CP_CHAR str[10];
    CP_IntToString(num, str);
    if(gray)
    {
        for(int i=0;i<CP_StringLen(str);i++)
        {
            DrawBitmap2(gnumber[str[i]-'0'], x+8*i, y, &screen);
        }
    }
    else    
    {
        for(int i=0;i<CP_StringLen(str);i++)
        {
            DrawBitmap2(number[str[i]-'0'], x+8*i, y, &screen);
        }
    }
}

void TetrisWindow::DrawMenu(int sel, int sel2)
{
    DrawBitmap2(&menuA, 0, 0, &screen);
    DrawText(25,68,"a-type",(sel==0 ? 1:type));
    DrawText(89,68,"b-type",(sel==0 ? 1:!type));
    if(type) // B-Type
    {
        DrawBitmap2(&menuB, 11, 89, &screen);
        for(int i=0;i<10;i++) DrawText(XLvl[i]-24,YLvl[i],i,(sel==1 ? 1:(i!=level)));
        for(int i=0;i<6;i++)  DrawText(XHig[i],YHig[i],i,(sel==2 ? 1:(i!=high)));
        if(sel==2)
        {
            for(int i=0;i<3;i++)
            {
                if(highscore[type][level][sel2][i])
                {
                    DrawText(33, 165+8*i, highname[type][level][sel2][i]);
                    DrawNumber(137,165+8*i, highscore[type][level][sel2][i]);
                }
            }
        }
    }
    else // A-Type
    {
        for(int i=0;i<10;i++) DrawText(XLvl[i],YLvl[i],i,(sel==1 ? 1:(i!=level)));
        if(sel==1)
        {
            for(int i=0;i<3;i++)
            {
                if(highscore[type][sel2][0][i])
                {
                    DrawText(33, 165+8*i, highname[type][sel2][0][i]);
                    DrawNumber(137,165+8*i, highscore[type][sel2][0][i]);
                }
            }
        }
    }
}

void TetrisWindow::DrawBrick(short x, short y, UCHAR z)
{
    DrawBitmap2(bricks[z], 16+8*(x-1), 61+8*y, &screen);
}

void TetrisWindow::DrawSetKMenu(int sel, bool set)
{
    DrawBitmap2(&keymenu, 0, 0, &screen);
    for(int i=0;i<10;i++)
    {
        DrawText(14, 68+12*i, gbkeys[i], 1);
        if(sel==i && set) DrawText(81, 68+12*i, "...", 0);
        else    DrawText(81, 68+12*i, cpkeys(*cpkptr[i]), 0);
    }
}

void TetrisWindow::SetKeys()
{
    SH3Timer::SetTimerFreq(SH3Timer::TIMER_2, 20000);
    SH3Timer::SetCount(SH3Timer::TIMER_2, 0);
    
    SH3Timer::Start(SH3Timer::TIMER_2);
    DrawSetKMenu(0, 0);
    bool g = true;
    char sel = 0;
    while(1)
    {
        if(GetKey(GB_UP) && sel)
        {
            sel--;
            DrawSetKMenu(sel, 0);
            while(GetKey(GB_UP));
        }
        else if(GetKey(GB_DOWN) && sel<9)
        {
            sel++;
            DrawSetKMenu(sel, 0);
            while(GetKey(GB_DOWN));
        }
        else if(GetKey(GB_A))
        {
            DrawSetKMenu(sel, 1);
            while(GetKey(GB_A));
            bool loop = true;
            while(loop)
            {
                for(int i=0x10;i<0x77;i++)
                {
                    if(GetKey(i))
                    {
                        *cpkptr[sel]=i;
                        loop = false;
                        while(GetKey(i));
                        break;
                    }
                }
            }
            DrawSetKMenu(sel, 0);
        }
        else if(GetKey(GB_START))
        {
            while(GetKey(GB_START));
            return;
        }
        if(SH3Timer::HasUnderflowed(SH3Timer::TIMER_2))
        {
            g = !g;
            DrawText(14, 68+12*sel, gbkeys[sel], g);
        }
    }
    SH3Timer::Stop(SH3Timer::TIMER_2);
}

SIGNED TetrisWindow::Message(const PegMessage &Mesg)
{
    switch(Mesg.wType)
    {
        case PM_LBUTTONDOWN: // Je pense que c'est le seul utile pour un menu non? ;)
            // Mesg.Point.x = coordonnées x du stylet
            // Mesg.Point.y = coordonnées y du stylet
            break;
        default:
            return PegWindow::Message(Mesg);
    }
    return 0;
}

SIGNED TetrisWindow::Execute()
{
    cheat = ClibValExistChk((CP_CHAR*)"Tetris", (CP_CHAR*)"cheat");
    LoadHighscore();
    
    SH3Timer::SetClockFreq(SH3Timer::TIMER_2, SH3Timer::FRQ_57KHZ);
    
    GrayScales::Initialize();
    GrayScales::SetBuffers(screen.tuc_Bmp, screen.tuc_Bmp2); // screen est défini dans TetrisWindow.h
    GrayScales::Start();
    
    // Intro
    
    bool opt=0;
    while(!GetKey(GB_START))
    {
        if((opt && GetKey(GB_LEFT)) || (!opt && GetKey(GB_RIGHT)))
        {
            opt=!opt;
        }
        DrawBitmap2(&intro, 0, 47, &buffer);
        if(!opt) DrawBitmap2(&arrow, 9, 47+114, &buffer);
        else    DrawBitmap2(&arrow, 56, 47+114, &buffer);
        DrawBitmap2(&buffer, 0, 0, &screen);
    }
    while(GetKey(GB_START));
    if(opt) SetKeys();
    
    while(1) { // Début de la boucle du jeu
    
    // Initialisation
    
    for(int i=0;i<12;i++)
    {
        for(int j=0;j<19;j++)
        {
            state[i][j]=0;
            state[0][j]=1;
            state[11][j]=1;
            state[i][18]=1;
        }
    }
    score=0; lines=0; level=0; high = 0; type = 0;
    for(int i=0;i<5;i++) scoreB[i]=0;
    nbrblock=0;
    g_over=false;
    x=4; y=-1;
    
    // Menu
    
    SH3Timer::SetTimerFreq(SH3Timer::TIMER_2, 20000);
    SH3Timer::SetCount(SH3Timer::TIMER_2, 0);
    
    SH3Timer::Start(SH3Timer::TIMER_2);
    
    DrawMenu(0, 0);
    bool g = true;
    char sel1 = 0, sel2 = 0;
    while(1)
    {
        if(GetKey(GB_LEFT))
        {
            switch(sel1){
                case 0: if(sel2) sel2=0; break;
                case 1:
                case 2: if(sel2) sel2--;
            }
            DrawMenu(sel1, sel2);
            while(GetKey(GB_LEFT));
        }
        else if(GetKey(GB_RIGHT))
        {
            switch(sel1){
                case 0: if(!sel2) sel2=1; break;
                case 1: if(sel2<9) sel2++; break;
                case 2: if(sel2<5) sel2++;
            }
            DrawMenu(sel1, sel2);
            while(GetKey(GB_RIGHT));
        }
        else if(GetKey(GB_UP) && sel1)
        {
            switch(sel1){
                case 1: if(sel2>4) sel2-=5; break;
                case 2: if(sel2>2) sel2-=3;
            }
            DrawMenu(sel1, sel2);
            while(GetKey(GB_UP));
        }
        else if(GetKey(GB_DOWN) && sel1)
        {
            switch(sel1){
                case 1: if(sel2<5) sel2+=5; break;
                case 2: if(sel2<3) sel2+=3;
            }
            DrawMenu(sel1, sel2);
            while(GetKey(GB_DOWN));
        }
        else if(GetKey(GB_A))
        {
            switch(sel1){
                case 0: type=sel2; sel2=level; break;
                case 1: level=sel2; sel2=high; break;
                case 2: high=sel2;
            }
            if(++sel1 == (type ? 3:2)) break;
            DrawMenu(sel1, sel2);
            while(GetKey(GB_A));
        }
        else if(GetKey(GB_B) && sel1)
        {
            switch(sel1){
                case 1: sel2=type; break;
                case 2: sel2=level;
            }
            sel1--;
            DrawMenu(sel1, sel2);
            while(GetKey(GB_B));
        }
        else if(GetKey(GB_START))
        {
            while(GetKey(GB_START));
            break;
        }
        else if(GetKey(GB_OFF))
        {
            SaveHighscore();
            GrayScales::Stop();
            GrayScales::Restore();
            SH3Timer::Stop(SH3Timer::TIMER_2);
            Bevt_Request_LaunchMenu();
            return 0;
        }
        if(SH3Timer::HasUnderflowed(SH3Timer::TIMER_2))
        {
            g = !g;
            switch(sel1)
            {
                case 0: // Sélection du type
                    if(!sel2) DrawText(25,68,"a-type",g);
                    else      DrawText(89,68,"b-type",g);
                    break;
                case 1: // Sélection du level
                    if(type) DrawText(XLvl[sel2]-24,YLvl[sel2],sel2,g);
                    else     DrawText(XLvl[sel2],YLvl[sel2],sel2,g);
                    break;
                case 2: // Sélection de la hauteur
                    if(type) DrawText(XHig[sel2],YHig[sel2],sel2,g);
                    break;
            }
        }
    }

    SH3Timer::Stop(SH3Timer::TIMER_2);
    
    // Début du jeu
    
    SH3Timer::SetTimerFreq(SH3Timer::TIMER_2, 57538-5000*level);
    SH3Timer::SetCount(SH3Timer::TIMER_2, 0);
    
    DrawBitmap2(&game, 0, 0, &screen); // On dessine l'écran de jeu
    if(type) {lines=25;DrawBitmap2(&gameB, 105, 61, &screen);}
    Ran(); nbrblock++; Ran();
    
    if(type) High();
    AfficheBlockInit();
    if(type)
    {
        DrawNumber(129, 78, level);
        DrawNumber(129, 102, high);
        DrawNumber(137, 142, lines);
    }
    else
    {
        DrawNumber(145, 86, score);
        DrawNumber(142, 118, level);
        DrawNumber(142, 142, lines);
    }
    SH3Timer::Start(SH3Timer::TIMER_2);
    
    period = 57538-5000*level;
    int down_cumul = 0;
    int wait = 0;
    bool up = false;
    int slevel = level;
    while(1)
    {
        if(!GetKey(GB_LEFT) && !GetKey(GB_RIGHT) && !GetKey(GB_DOWN) && !GetKey(GB_UP) && !GetKey(GB_A) && !GetKey(K_1) && !GetKey(K_2)) wait=0;
        //if(!GetKey(K_DOWN)) down_cumul=0;
        if(!GetKey(GB_UP) && !GetKey(GB_A)) up = true;
        if((GetKey(GB_UP) || GetKey(GB_A)) && ch[nbrblock%2]!=0 && up) //On ne cherchera pas à faire faire une rotation au carré
        {
            Rotation();
            up = false;
        }    
            
        if(GetKey(GB_LEFT) && Test(-1,0) && !wait)
        {
            x--;
            AfficheBlock(-1, 0);
            
            wait=2000;
        }    
        if(GetKey(GB_RIGHT) && Test(1,0) && !wait)
        {
            x++;
            AfficheBlock(1, 0);
            
            wait=2000;
        }
        if(GetKey(GB_DOWN) && Test(0,1) && !wait)
        {
            down_cumul++;
            y++;
            AfficheBlock(0, 1);
            
            wait=500;
        }
        if(GetKey(GB_START))
        {
            DrawBitmap2(&screen, 0, 0, &buffer); // On copie l'écran
            DrawBitmap2(&pause, 16, 61, &screen);
            while(GetKey(GB_START));
            while(!GetKey(GB_START));
            while(GetKey(GB_START));
            DrawBitmap2(&buffer, 0, 0, &screen);
        }
        if(GetKey(GB_OFF))
        {
            SaveHighscore();
            GrayScales::Stop();
            GrayScales::Restore();
            SH3Timer::Stop(SH3Timer::TIMER_2);
            Bevt_Request_LaunchMenu();
            return 0;
        }
        
        if(GetKey(K_1) && cheat && !type && !wait)
        {
            score++;
            bool quit = false;
            if(score>=1000000) {score=999999;quit=true;}
            DrawNumber(145, 86, score);
            if(quit) break;
            wait=100;
        }
        if(GetKey(K_2) && cheat && !wait)
        {
            if(type) lines--;
            else lines++;
            score+=40;
            if(type)
            {
                scoreB[0]++;
                DrawText(120, 142, "   ");
                DrawNumber(137, 142, lines);
                if(lines==0) break;
            }
            else
            {
                if(lines == 10*(level+1))
                {
                    level++;
                    if(period - 5000 > 0)
                    {
                        period -= 5000;
                        SH3Timer::SetTimerFreq(SH3Timer::TIMER_2, period);
                    }
                }
                bool quit=false;
                if(level==10) {level=9;quit=true;}
                DrawNumber(145, 86, score);
                DrawNumber(142, 118, level);
                DrawNumber(142, 142, lines);
                if(quit) break;
            }
            wait=2000;
        }
        
        if(SH3Timer::HasUnderflowed(SH3Timer::TIMER_2)) 
        {
            if (Test(0,1))
            {
                if(!GetKey(GB_DOWN)) down_cumul=0;
                y++;
                AfficheBlock(0, 1);
            }
            else
            {
                score+=down_cumul;
                scoreB[4]+=down_cumul;
                down_cumul=0;
                if(score>=1000000) score=999999;
                if(!type) DrawNumber(145, 86, score);
                if (x==4 &&!y) {GameOver(); g_over=true; break;}
                for(int i=0;i<4;i++)  // Transfert de la piece dans le state
                {
                    for(int j=0;j<4;j++)
                    {
                        if (piecec[i+1][j+1]!=0) state[i+x][j+y]=piecec[i+1][j+1];
                    }        
                }    
                Lignes();
                if(lines<0) lines=0;
                bool quit = false;
                if(score>=1000000) {score=999999;quit=true;}
                x=4; y=0; 
                nbrblock++; 
                Ran();
                AfficheBlockInit();
                if(level==10) {level=9;quit=true;}
                if(type)
                {
                    DrawNumber(129, 78, level);
                    DrawNumber(129, 102, high);
                    DrawText(120, 142, "   ");
                    DrawNumber(137, 142, lines);
                    if(lines==0) break;
                }
                else
                {
                    DrawNumber(145, 86, score);
                    DrawNumber(142, 118, level);
                    DrawNumber(142, 142, lines);
                }
                if(quit) break;
            }
        }
        if(wait) wait--;
    }
    SH3Timer::Stop(SH3Timer::TIMER_2);
    
    if(type && !g_over)
    {
        for(int i=1;i<2000000;i++);
        DrawBitmap2(&count, 16, 61, &screen);
        for(int i=0;i<4;i++)
        {
            DrawNumber(16+9, 61+9+24*i, 0);
            DrawText(57, 61+9+24*i, linescore[i]*(level+1));
            DrawNumber(16+65, 61+17+24*i, 0);
        }
        DrawNumber(16+65, 61+105, 0);
        DrawNumber(16+65, 61+137, 0);
        for(int i=1;i<2000000;i++);
        int S=0;
        for(int i=0;i<4;i++)
        {
            for(int c = 1;c<=scoreB[i];c++)
            {
                DrawNumber(16+9, 61+9+24*i, c);
                DrawNumber(16+65, 61+17+24*i, c*linescore[i]*(level+1));
                DrawNumber(16+65, 61+137, S);
                S+=linescore[i]*(level+1);
                for(int i=1;i<100000;i++);
            }
            for(int i=1;i<500000;i++);
        }
        for(int c = 0;c<=scoreB[4];c++)
        {
            DrawNumber(16+65, 61+105, c);
            DrawNumber(16+65, 61+137, S);
            S++;
            for(int i=1;i<80000;i++);
        }
        while(!GetKey(GB_START));
        while(GetKey(GB_START));
    }
    
    if(score == 999999 || (level==9 && type && !g_over) || (lines/10>=10 && !type && !g_over))
    {
        DrawBitmap2(&mask6, 16, 61, &screen);
        DrawBitmap2(&fin, 16, 61, &screen);
        for(int i=0;i<8;i++)
        {
            DrawBitmap2(bonhomme[i%2], 53, 102, &screen);
            for(int i=0;i<1200000;i++);
        }
    }
        
    if(!type || (type && !g_over)) AddHighscore(score, type, slevel, high);
    
    } // Fin de la boucle du jeu    
    GrayScales::Stop();
    GrayScales::Restore();
    SH3Timer::Stop(SH3Timer::TIMER_2);
    SaveHighscore();
    Bevt_Request_LaunchMenu();
    return 0;
}

void TetrisWindow::GameOver()
{
    for(int j=18;j>-1;j--)
    {
        for(int i=1;i<11;i++)
        {
           DrawBrick(i,j,13);
        }
        for(int i=0;i<200000;i++);
    }
    for(int i=0;i<3000000;i++);
    for(int j=18;j>-1;j--)
    {
        for(int i=1;i<11;i++)
        {
           DrawBrick(i,j,0);
        }
        for(int i=0;i<200000;i++);
    }
    DrawBitmap2(&gameover, 16, 61, &screen);
    while(!GetKey(GB_START));
    while(GetKey(GB_START));
}
