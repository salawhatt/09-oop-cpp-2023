#pragma once
using namespace std;
#include "mystring.h"
#include <fstream> 
#include <iostream>
#include <vector>
#include <string>
#pragma comment(lib, "pdcurses.lib")

class Model
{
public:
	Model(size_t window_width);
	~Model();
	int getLineLength(size_t line_number);
	void insertLine(size_t line_number, MyString& string);
	void insertStringInLine(size_t line_number, size_t index, char* string);
	void appEndString(MyString string);
	void insertCh(size_t line_number, size_t ch_pos, char sym);
	void appEndCh(size_t line_number, char sym);
	void Clear();
	void eraseInLine(size_t line_number, size_t index, size_t count);
	void eraseInLine(size_t line_number, size_t index);
	void eraseLine(size_t index);
	char* getLine(size_t line_number);
	char getChar(size_t line_number, size_t index);
	size_t rFind(size_t line_number, size_t index, char* str);
	size_t lFind(size_t line_number, size_t index, char* str);
	size_t getLinesCount();
	bool findDown(size_t* line_number, size_t* index, char* str);
	bool findUp(size_t* line_number, size_t* index, char* str);
	bool writeToFile(MyString path);
	bool readFromFile(MyString path);
	MyString getString(size_t line_number, size_t index, size_t count);
private:
	vector<MyString> text_;
	size_t max_line_size;
};

