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

extern "C" void LibGetTime2(byte *hour2, byte *minute2, byte *second2);

void PegAppInitialize(PegPresentationManager *pPresentation)
{
    byte h, m, s;
    LibGetTime2(&h, &m, &s);
    srand(3600*(int)h+60*(int)m+(int)s); // On initialise le générateur de nombres aléatoires avec l'heure courante
    
	PegRect Rect;
	Rect.Set(MAINFRAME_LEFT, MAINFRAME_TOP, MAINFRAME_RIGHT, MAINFRAME_BOTTOM - STATUS_HEIGHT + 1);
    TetrisWindow *mw = new TetrisWindow(Rect);
	//pPresentation->Add(mw);
	// On exécute directement la fenêtre
    mw->Execute();
}

extern "C" char *ExtensionGetLang(ID_MESSAGE MessageNo)
{
	return "";
}
