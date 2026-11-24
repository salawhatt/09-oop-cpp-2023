#include "Controller.h"
#include "View.h"
Controller::Controller(Model* text, View* view):model_(text),view_(view)
{
	coords_column = ZERO_POS;
	coords_line = ZERO_POS;
	working_mode = NAVIGATION_MODE;
	first_visible_line = ZERO_POS;
	insert_mode = true;
	window_size = view->getWindowSize();
}

Controller::~Controller() { }

void Controller::loop()
{
	chtype key = 0;
	view_->renderStatusBar(coords_line, coords_column, model_->getLinesCount(), working_mode, first_visible_line, command_buffer_, current_file_path_);

	while (working_mode) {
		key = view_->getSymbol();
		switch (key)
		{
			case KEY_UP: {
				moveUp();
				key = NEXT_CHAR;
				break;
			}
			case KEY_DOWN: {
				moveDown();
				key = NEXT_CHAR;
				break;
			}
			case KEY_RIGHT: {
				moveRight();
				key = NEXT_CHAR;
				break;
			}
			case KEY_LEFT: {
				moveLeft();
				key = NEXT_CHAR;
				break;
			}
			case KEY_PGUP: {
				pageUp();
				key = NEXT_CHAR;
				break;
			}
			case KEY_PGDN: {
				pageDown();
				key = NEXT_CHAR;
				break;
			}
			default:
				break;
			}
				if (key == NEXT_CHAR) {
					render();
					continue;
				}
				switch (working_mode)
				{
					case NAVIGATION_MODE: {
						navigationModeController(key);
						break;
					}
					case WRITE_MODE: {
						writeModeController(key);
						break;
					}
					case FIND_MODE: {
						findModeController(key);
						break;
					}
					case COMMAND_MODE: {
						commandModeController(key);
						break;
					}
					default:
						break;
					}
				render();
	}
}

void Controller::writeModeController(chtype key)
{
	MyString s;
	switch (key)
	{
		case KEY_INSERT: {
			insert_mode = !insert_mode;
			break;
		}
		case KEY_ESC: {
			working_mode = NAVIGATION_MODE;
			break;
		}
		case KEY_BACK: {
			if (coords_column != ZERO_POS) {
				model_->eraseInLine(coords_line + first_visible_line, --coords_column, 1);
			}
			else {
				if (model_->getLineLength(coords_line + first_visible_line) == ZERO_POS && coords_line + first_visible_line != 0) {
					model_->eraseLine(coords_line + first_visible_line);
				}
				moveUp();
				coords_column = model_->getLineLength(coords_line + first_visible_line);
			}
			break;
		}
		case KEY_DELETE: {
			model_->eraseInLine(coords_line + first_visible_line, coords_column, 1);
			break;
		}
		case KEY_ENTERR: {
			s.clear();
			s.shrink_to_fit();


			if (model_->getLineLength(coords_line + first_visible_line) == coords_column) {
				s = "";
				model_->appEndCh(coords_line + first_visible_line, '\n');
				if (s[s.size() - 1] == '\n')
					model_->insertLine(++coords_line + first_visible_line, s);
				else
					model_->insertStringInLine(++coords_line + first_visible_line, 0, s.c_str());
			}
			else {
				s = (model_->getLine(coords_line) + coords_column);
				model_->eraseInLine(coords_line + first_visible_line, coords_column, model_->getLineLength(coords_line + first_visible_line) - coords_column);
				model_->appEndCh(coords_line + first_visible_line, '\n');
				if (s[s.size() - 1] == '\n')
					model_->insertLine(++coords_line + first_visible_line, s);
				else
					model_->insertStringInLine(++coords_line + first_visible_line, ZERO_POS, s.c_str());
			}
			if (coords_line == window_size.first) {
				coords_line--;
				first_visible_line++;
			}
			coords_column = ZERO_POS;
			break;
		}
		default: {

			if (insert_mode) {
				model_->insertCh(coords_line + first_visible_line, coords_column, key);
				coords_column++;
			}
			else {
				model_->eraseInLine(coords_line + first_visible_line, coords_column, 1);
				model_->insertCh(coords_line + first_visible_line, coords_column, key);
				coords_column++;
			}
			if (coords_column == window_size.second) {
				moveDown();
			}
			break;
		}
		}
}

void Controller::navigationModeController(chtype key)
{
	switch (key)
	{
		case KEY_ESC: {
			working_mode = EXIT_MODE;
			break;
		}
		case 'i': {
			insert_mode = true;
			working_mode = WRITE_MODE;
			break;
		}
		case 'I': {
			insert_mode = true;
			working_mode = WRITE_MODE;
			coords_column = ZERO_POS;
			break;
		}
		case 'A': {
			insert_mode = true;
			model_->eraseInLine(coords_line + first_visible_line, 0);
			coords_column = ZERO_POS;
			working_mode = WRITE_MODE;
			break;
		}
		case 'S': {
			insert_mode = true;
			coords_column = model_->getLineLength(coords_line + first_visible_line);
			working_mode = WRITE_MODE;
			break;
		}
		case 'r': {
			insert_mode = false;
			working_mode = WRITE_MODE;
			break;
		}
		case '/': {

			command_buffer_ = '/';
			working_mode = FIND_MODE;
			break;
		}
		case '?': {

			command_buffer_ = '?';
			working_mode = FIND_MODE;
			break;
		}
		case ':': {

			command_buffer_ = ':';
			working_mode = COMMAND_MODE;
			break;
		}
		case 'g': {
			chtype second_key = view_->getSymbol();
			if (second_key == 'g') {
				firstPage();
			}
			break;
		}
		case 'G': {
			lastPage();
			break;
		}
		case '^': {
			coords_column = ZERO_POS;
			break;
		}
		case '$': {
			coords_column = model_->getLineLength(coords_line + first_visible_line);
			break;
		}
		case 'w': {
			coords_column = model_->rFind(coords_line, coords_column + 1, (char*)" ");
			break;
		}
		case 'b': {
			int index = coords_column - 1;
			if (index < 0) index = 0;
			coords_column = model_->lFind(coords_line, index, (char*)" ");
			break;
		}
		case 'x': {
			model_->eraseInLine(coords_line + first_visible_line, coords_column, 1);
			break;
		}
		case 'd': {
			key = view_->getSymbol();
			if (key == 'i') {
				key = view_->getSymbol();
				if (key == 'w') {
					deleteWord();
				}
			}
			else if (key == 'd') {
				cutLine();
			}
			break;
		}
		case 'y': {
			copyLine();
			key = view_->getSymbol();
			if (key == 'w') {
				copyWord();
			}

			break;
		}
		case 'p': {
			insertString();
			break;
		}
		default: {
			if (key > '0' && key <= '9') {
				size_t rez = 0;
				while (key >= '0' && key <= '9') {
					rez *= 10;
					rez += key - '0';
					key = view_->getSymbol();
				}
				if (key == 'G') {
					moveToLine(rez);
				}
			}
			break;
		}
	}
}

void Controller::findModeController(chtype key)
{
	switch (key)
	{
		case KEY_ESC: {
			working_mode = NAVIGATION_MODE;
			command_buffer_.clear();
			command_buffer_.shrink_to_fit();
			break;
		}
		case KEY_ENTERR: {
			find(command_buffer_);
			break;
		}
		case KEY_BACK: {
			if (!command_buffer_.empty()) {
				command_buffer_.erase(command_buffer_.size() - 1, 1);
			}
			break;
		}
		case 'n': {
			command_buffer_.erase(0, 1);
			command_buffer_.insert(0, 1, '/');
			find(command_buffer_);
			break;
		}
		case 'N': {
			command_buffer_.erase(0, 1);
			command_buffer_.insert(0, 1, '?');
			find(command_buffer_);
			break;
		}
		default:
			char tmp[2] = { (char)key, 0 };
			command_buffer_ += tmp;
			break;
		}
}

void Controller::commandModeController(chtype key)
{
	switch (key)
	{
		case KEY_ESC: {
			working_mode = NAVIGATION_MODE;
			command_buffer_.clear();
			command_buffer_.shrink_to_fit();
			break;
		}
		case KEY_ENTERR: {
			processCommand(command_buffer_);
			command_buffer_ = ':';
			break;
		}
		case KEY_BACK: {
			if (command_buffer_.size() > 1) {
				command_buffer_.erase(command_buffer_.size() - 1, 1);
			}
			break;
		}
		default:
			char tmp[2] = { (char)key, 0 };
			command_buffer_ += tmp;
			break;
		}
}

void Controller::moveUp()
{
	if (coords_line != ZERO_POS) 
	{
		coords_line--;
		ensureCursorPositionWithinLine();
	}
	else if (first_visible_line != ZERO_POS) 
	{
		--first_visible_line;
	}
}

void Controller::moveDown()
{
	if (coords_line < model_->getLinesCount() - 1 && coords_line < window_size.first - 1) {
		coords_line++;
		ensureCursorPositionWithinLine();
	}
	else if (model_->getLinesCount() - first_visible_line > window_size.first) {
		++first_visible_line;
		ensureCursorPositionWithinLine();
	}
}

void Controller::moveLeft()
{
	if (coords_column!= ZERO_POS)
	{
		coords_column--;
	}
	else if (coords_line != ZERO_POS) {
		coords_line--;
		coords_column = model_->getLineLength(coords_line + first_visible_line);
	}
	else if (first_visible_line != ZERO_POS) {
		--first_visible_line;
		coords_column = model_->getLineLength(first_visible_line);
	}
}

void Controller::moveRight()
{
	if (coords_column < model_->getLineLength(coords_line + first_visible_line)) {
		coords_column++;
	}
	else if (coords_line != model_->getLinesCount() - 1 && coords_line < window_size.first - 1) {
		coords_line++;
		coords_column = ZERO_POS;
	}
	else if (model_->getLinesCount() - first_visible_line > window_size.first) {
		++first_visible_line;
		coords_column = ZERO_POS;
	}
}

void Controller::pageUp()
{
	int top_of_page = first_visible_line - window_size.first;
	if (top_of_page < 0) top_of_page = ZERO_POS;
	first_visible_line = top_of_page;
	ensureCursorPositionWithinLine();
}

void Controller::pageDown()
{
	int top_of_page = first_visible_line + window_size.first;
	if (top_of_page > (int)(model_->getLinesCount() - window_size.first)) {
		top_of_page = model_->getLinesCount() - window_size.first;
		if (top_of_page < 0) top_of_page = ZERO_POS;
	}
	first_visible_line = top_of_page;
	ensureCursorPositionWithinLine();
}

void Controller::firstPage()
{
	first_visible_line = ZERO_POS;
	coords_line = ZERO_POS;
	if (coords_column > model_->getLineLength(ZERO_POS)) {
		coords_column = model_->getLineLength(ZERO_POS);
	}
}

void Controller::lastPage()
{
	int top_of_page = model_->getLinesCount() - window_size.first;
	if (top_of_page < 0) top_of_page = ZERO_POS;
	first_visible_line = top_of_page;
	coords_line = ZERO_POS;
	if (coords_column > model_->getLineLength(model_->getLinesCount() - 1)) {
		coords_column = model_->getLineLength(model_->getLinesCount() - 1);
	}
}

void Controller::render()
{
	view_->renderText(model_, first_visible_line);
	view_->renderStatusBar(coords_line, coords_column, model_->getLinesCount(), working_mode, first_visible_line, command_buffer_, current_file_path_);
	view_->Refresh();
}

void Controller::ensureCursorPositionWithinLine()
{
	int currentLineLength = model_->getLineLength(coords_line + first_visible_line);
	if (coords_column > currentLineLength) {
		coords_column = currentLineLength;
	}
}

void Controller::moveToLine(size_t rez)
{
	if (--rez > model_->getLinesCount() - 1)return;
	first_visible_line = rez;
	coords_line = ZERO_POS;
	ensureCursorPositionWithinLine();
}

void Controller::deleteWord()
{
	size_t index = model_->lFind(first_visible_line + coords_line, coords_column, (char*)" ");
	size_t count = model_->rFind(first_visible_line + coords_line, coords_column, (char*)" ") - index + 1;
	model_->eraseInLine(first_visible_line + coords_line, index, count);
	ensureCursorPositionWithinLine();
}

void Controller::copyLine()
{
	clipboard_ = model_->getString(first_visible_line + coords_line, 0, model_->getLineLength(first_visible_line + coords_line));
	if (clipboard_[clipboard_.size() - 1] == '\n')
		clipboard_.erase(clipboard_.size() - 1, 1);
	clipboard_.shrink_to_fit();
}

void Controller::cutLine()
{
	copyLine();
	model_->eraseLine(first_visible_line + coords_line);
	if (first_visible_line + coords_line >= model_->getLinesCount()) moveUp();
	else ensureCursorPositionWithinLine();
}

void Controller::insertString()
{
	if (!clipboard_.empty()) {
		model_->insertStringInLine(first_visible_line + coords_line, coords_column, clipboard_.c_str());
	}
}

void Controller::copyWord()
{
	size_t index = model_->lFind(first_visible_line + coords_line, coords_column, (char*)" ");
	size_t count = model_->rFind(first_visible_line + coords_line, coords_column, (char*)" ") - index;
	clipboard_ = model_->getString(first_visible_line + coords_line, index, count);
	clipboard_.shrink_to_fit();
}

void Controller::find(MyString target)
{
	size_t line_number = first_visible_line + coords_line;
	size_t index;
	bool rez;
	if (target[0] == '/') {
		moveRight();
		index = coords_column;
		rez = model_->findDown(&line_number, &index, target.c_str() + 1);
		if (!rez)
			moveLeft();
	}
	else if (target[0] == '?') {
		index = 0;
		if (coords_column > 0)
			index = coords_column - 1;

		rez = model_->findUp(&line_number, &index, target.c_str() + 1);
	}
	else {
		command_buffer_.insert(1, 0);
		return;
	}
		if (rez) 
		{
			if (target[0] == '/')
			{
				if (line_number > (window_size.first + first_visible_line))
				{
					first_visible_line = line_number;
					coords_line = 0;
				}
				else
				{
					coords_line = line_number - first_visible_line;
				}
				coords_column = index;
			}
			if (target[0] == '?')
			{
				first_visible_line = line_number;
				coords_line = 0;
				coords_column = index;
			}
		}
}

void Controller::writeToFile(MyString path)
{
	if (model_->writeToFile(path))
		current_file_path_ = path;
	else
		current_file_path_ = "Faild to open!";
}

void Controller::readFromFile(MyString path)
{
	model_->Clear();
	if (model_->readFromFile(path))
		current_file_path_ = path;
	else
		current_file_path_ = "Faild to open!";
}

void Controller::processCommand(MyString command)
{
	command.erase(0, 1);
	switch (command[0])
	{
		case 'o': {
			current_file_path_.clear();
			current_file_path_.shrink_to_fit();
			readFromFile(command.c_str() + 2);
			break;
		}
		case 'x': {
			writeToFile(current_file_path_);
			current_file_path_.clear();
			current_file_path_.shrink_to_fit();
			model_->Clear();
			break;
		}
		case 'w': {
				switch (command[1])
				{
					case 0: {
						writeToFile(current_file_path_);
						break;
					}
					case 'q': {
						writeToFile(current_file_path_);
						working_mode = EXIT_MODE;
						break;
					}
					default:
						writeToFile(command.c_str() + 2);
						break;
					}
		break;
	}
		case 'q': {
				switch (command[1])
				{
					case 0: {
						MyString Dialog = "Save file? y/n";
						view_->renderStatusBar(coords_line, coords_column, model_->getLinesCount(), working_mode, first_visible_line, command_buffer_, Dialog);
						view_->Refresh();
						chtype key = view_->getSymbol();
						if (key == 'y') {
							if (current_file_path_.empty()) {
								key = view_->getSymbol();
								current_file_path_.append(1, key);
								while (key != KEY_ENTERR) {
									current_file_path_.append(1, key);
									key = view_->getSymbol();
								}
							}
							writeToFile(current_file_path_);
						}
						working_mode = EXIT_MODE;
						break;
					}
					case '!': {

						working_mode = EXIT_MODE;
						break;
					}
					default:
						break;
					}
			break;
		}
		case 'h': {
			MyString save_path = current_file_path_;
			writeToFile(current_file_path_);
			current_file_path_ = "help.txt";
			readFromFile(current_file_path_);
			render();
			view_->getSymbol();
			writeToFile(current_file_path_);
			current_file_path_.clear();
			current_file_path_.shrink_to_fit();
			current_file_path_ = save_path;
			readFromFile(current_file_path_);
			render();
			break;
		}
		default:
			size_t rez = 0;
			if (command.size())
			{
				for (int i = 0; i < command.size(); i++) {
					rez *= 10;
					rez += command[i] - '0';
				}
			}
			moveToLine(rez);
			break;
		}
}