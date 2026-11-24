#include "View.h"

View::View()
{
	curses_.initScr();
	curses_.disableEcho();
	curses_.disableBuffering();
	curses_.enableKeypadFeatures(true);
}

View::~View()
{
	curses_.endWin();
}

int View::getSymbol()
{
	return curses_.getChar();
}

void View::putChar(chtype ch)
{
	curses_.addChar(ch);
}

void View::enableKeypadFeatures(bool mode)
{
	curses_.enableKeypadFeatures(mode);
}

void View::enableEcho(bool mode)
{
	if (mode) curses_.enableEcho();
	else curses_.disableEcho();
}

void View::renderStatusBar(int coords_line, int coords_column, int rows_total, int mode, size_t first_line, MyString cmd_buffer, MyString path)
{
	MyString status_bar = " Line ";
	status_bar += to_string(coords_line + 1 + first_line).c_str();
	status_bar += ", column ";
	status_bar += to_string(coords_column + 1).c_str();
	status_bar += ".  ";
	switch (mode)
	{
		case INPUT_MODE: {
			status_bar += "WRITE MODE ";
			break;
		}case FIND_MODE: {
			status_bar += "FIND_MODE ";
			break;
		}case COMMAND_MODE: {
			status_bar += "COMMAND_MODE ";
			break;
		}
		default: {
			status_bar += "NAVIGATION_MODE ";
			break;
		}
	}

	curses_.attributesOn(A_REVERSE);
	curses_.moveAndPrint(LINES - 1, 0, status_bar.c_str());
	status_bar = cmd_buffer;
	curses_.moveAndPrint(LINES - 1, 33, status_bar.c_str());
	char fileNameString[] = "FILE NAME: ";
	curses_.moveAndPrint(LINES - 1, 89, fileNameString);
	curses_.moveAndPrint(LINES - 1, 100, path.c_str());
	curses_.attributesOff(A_REVERSE);
	moveCursor(coords_line, coords_column);
}

void View::moveCursor(int coords_line, int coords_column)
{
	curses_.Move(coords_line, coords_column);
}

void View::renderText(Model* text, size_t first_line)
{
	curses_.Clear();
	size_t lines_rendered = 0;
	while ((lines_rendered < LINES - 1) && (lines_rendered + first_line < text->getLinesCount())) {
		curses_.Move(lines_rendered, 0);
		curses_.print((chtype*)text->getLine(first_line + lines_rendered++));
	}
}

void View::Refresh()
{
	curses_.refreshWindow();
}

pair<int, int> View::getWindowSize()
{
	return make_pair(LINES - 1, COLS);
}