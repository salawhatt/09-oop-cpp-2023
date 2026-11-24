#include "TUIAdapter.h"

WINDOW* TUIAdapter::initScr() {
	return initscr();
}

int TUIAdapter::getChar() {
	return getch();
}

int TUIAdapter::disableBuffering() {
	return cbreak();
}

int TUIAdapter::disableEcho() {
	return noecho();
}

int TUIAdapter::enableEcho() {
	return echo();
}
int TUIAdapter::enableKeypadFeatures(bool mode) {
	return keypad(stdscr, mode);
}
int TUIAdapter::refreshWindow() {
	return refresh();
}
int TUIAdapter::Move(int row, int col) {
	return move(row, col);
}

int TUIAdapter::addChar(chtype ch) {
	return addch(ch);
}

int TUIAdapter::moveAndAddChar(int row, int col, chtype ch)
{
	return mvaddch(row, col, ch);
}
int TUIAdapter::print(chtype* mes)
{
	return printw("%s", mes);
}
int TUIAdapter::moveAndPrint(int row, int col, char* mes)
{
	return mvprintw(row, col, "%s", mes);
}
int TUIAdapter::attributesOn(chtype atr)
{
	return attron(atr);
}
int TUIAdapter::attributesOff(chtype atr)
{
	return attroff(atr);
}
int TUIAdapter::Clear()
{
	return clear();
}
int TUIAdapter::endWin()
{
	return endwin();
}
void TUIAdapter::getWindowSize(int* row, int* col)
{
	getmaxyx(stdscr, *col, *row);
}
