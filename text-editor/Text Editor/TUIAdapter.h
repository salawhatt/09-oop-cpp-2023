#ifndef _ADAPT_H_
#define _ADAPT_H_

#include "curses.h"
#pragma comment(lib, "pdcurses.lib")

class TUIAdapter
{
public:
	WINDOW* initScr();
	int getChar();
	int disableBuffering();
	int enableEcho();
	int disableEcho();
	int enableKeypadFeatures(bool mode);
	int refreshWindow();
	int Move(int row, int col);
	int addChar(chtype ch);
	int moveAndAddChar(int row, int col, chtype ch);
	int print(chtype* mes);
	int moveAndPrint(int row, int col, char* mes);
	int attributesOn(chtype atr);
	int attributesOff(chtype atr);
	int Clear();
	int endWin();
	void getWindowSize(int* row, int* col);
};
#endif

