#pragma once
using namespace std;
#include "Model.h"
#include "View.h"
#include "mystring.h"
#define ZERO_POS 0
class Controller
{
public:
	Controller(Model* text, View* view);
	~Controller();
	void loop();
	void writeModeController(chtype key);
	void navigationModeController(chtype key);
	void findModeController(chtype key);
	void commandModeController(chtype key);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void pageUp();
	void pageDown();
	void firstPage();
	void lastPage();
	void render();
	void ensureCursorPositionWithinLine();
	void moveToLine(size_t rez);
	void deleteWord();
	void copyLine();
	void cutLine();
	void insertString();
	void copyWord();
	void find(MyString target);
	void writeToFile(MyString path);
	void readFromFile(MyString path);
	void processCommand(MyString command);
	MyString current_file_path_;
private:
	pair<int, int> window_size;
	int coords_line;
	int coords_column;
	int working_mode;
	bool insert_mode;
	size_t first_visible_line;
	Model* model_;
	View* view_;
	MyString clipboard_;
	MyString command_buffer_;
	enum Mode {
		EXIT_MODE = 0,
		NAVIGATION_MODE = 1,
		WRITE_MODE = 2,
		FIND_MODE = 3,
		COMMAND_MODE = 4
	};
	enum Key {
		NEXT_CHAR = 0,
		KEY_ESC = 27,
		KEY_ENTERR = 10,
		KEY_BACK = 8,
		KEY_INSERT = 506,
		KEY_DELETE = 330,
		KEY_PGUP = 339,
		KEY_PGDN = 338
	};
};

