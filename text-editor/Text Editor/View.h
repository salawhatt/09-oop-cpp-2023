#ifndef _VIEW_H_
#define _VIEW_H_

#define _CRT_SECURE_NO_WARNINGS
#include "TUIAdapter.h"
#include "Model.h"
#include "mystring.h"

using namespace std;
class View
{
public:
	View();
	~View();
	int getSymbol();
	void putChar(chtype ch);
	void enableKeypadFeatures(bool mode);
	void enableEcho(bool mode);
	void renderStatusBar(int coords_line, int coords_column, int rows_total, int mode, size_t first_line, MyString cmd_buffer, MyString path);
	void moveCursor(int coords_line, int coords_column);
	void renderText(Model* text, size_t first_line);
	void Refresh();
	pair<int, int>getWindowSize();

private:
	TUIAdapter curses_;
	enum statusBarMode {
		INPUT_MODE = 2,
		FIND_MODE = 3,
		COMMAND_MODE = 4
	};
};


#endif