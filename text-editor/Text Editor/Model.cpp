#include "Model.h"

Model::Model(size_t window_width)
{
	text_ = vector<MyString>{ MyString() };
	max_line_size = window_width;
}

Model::~Model() 
{
}

void Model::insertLine(size_t line_number, MyString& string)
{
	if (line_number == text_.size())
		appEndString(string);
	else
		text_.insert(text_.begin() + line_number, string);
}

void Model::appEndString(MyString string)
{
	if (string.size() > max_line_size) {
		MyString overflow = (string.c_str() + max_line_size);
		string.erase(max_line_size, overflow.size());
		string.shrink_to_fit();
		text_.push_back(string);
		text_.push_back(overflow);
	}
	else {
		text_.push_back(string);
	}
}

void Model::insertCh(size_t line_number, size_t ch_pos, char sym)
{
	if (text_.size() <= line_number) {
		text_.push_back(MyString(1, sym));
		return;
	}
	if (ch_pos == text_[line_number].size()) {
		text_[line_number].append(1, sym);
	}
	else {
		text_[line_number].insert(ch_pos, 1, sym);
	}
	if (text_[line_number].size() > max_line_size) {
		if (text_[line_number][max_line_size] == '\n') {
			MyString new_line = "\n";
			insertLine(line_number + 1, new_line);
		}
		else {
			insertCh(line_number + 1, 0, text_[line_number][max_line_size]);
		}
		text_[line_number].erase(max_line_size, 1);
		text_[line_number].shrink_to_fit();
	}
}

void Model::appEndCh(size_t line_number, char sym)
{
	text_[line_number].append(1, sym);

	if (text_[line_number].size() > max_line_size) {
		if (text_[line_number][max_line_size] == '\n') {
			MyString new_line = "\n";
			insertLine(line_number + 1, new_line);
		}
		else {
			insertCh(line_number + 1, 0, text_[line_number][max_line_size]);
		}
		text_[line_number].erase(max_line_size, 1);
		text_[line_number].shrink_to_fit();
	}
}

size_t Model::getLinesCount()
{
	return text_.size();
}

int Model::getLineLength(size_t line_number)
{
	size_t size = strlen((text_[line_number].c_str()));
	if (text_[line_number][size] == '\n')return size - 1;
	return size;
}

char* Model::getLine(size_t line_number)
{
	return text_[line_number].c_str();
}

void Model::eraseInLine(size_t line_number, size_t index, size_t count)
{
	text_[line_number].erase(index, count);
	text_[line_number].shrink_to_fit();
}

void Model::eraseInLine(size_t line_number, size_t index)
{
	eraseInLine(line_number, index, text_[line_number].size());
}

void Model::insertStringInLine(size_t line_number, size_t index, char* string)
{
	if (line_number == text_.size()) {
		appEndString(string);
		return;
	}

	text_[line_number].insert(index, string);
	if (text_[line_number].size() > max_line_size) {
		MyString overflow(text_[line_number].c_str() + max_line_size);
		eraseInLine(line_number, max_line_size);
		if (overflow[overflow.size() - 1] == '\n') {
			insertLine(line_number + 1, overflow);
		}
		else {
			insertStringInLine(line_number + 1, 0, overflow.c_str());
		}
	}
}

void Model::eraseLine(size_t index) {
	text_.erase(text_.begin() + index);
	text_.shrink_to_fit();
	if (text_.empty()) text_.push_back(MyString());
}

char Model::getChar(size_t line_number, size_t index)
{
	return text_[line_number][index];
}

size_t Model::rFind(size_t line_number, size_t index, char* str)
{
	int found = text_[line_number].find(str, index);
	if (found == -1) return text_[line_number].size();
	if (found == index) return rFind(line_number, index + 1, str);
	return found;
}

size_t Model::lFind(size_t line_number, size_t index, char* str)
{
	int found = -1;
	int tmp = text_[line_number].find(str);
	while (tmp != -1 && tmp < index) {
		found = tmp;
		tmp = text_[line_number].find(str, tmp + 1);
	}
	if (found == -1)return 0;
	if (found == index) return lFind(line_number, index - 1, str);
	return found + 1;
}

MyString Model::getString(size_t line_number, size_t index, size_t count)
{
	return MyString(text_[line_number].c_str() + index, count);
}

bool Model::findDown(size_t* line_number, size_t* index, char* str)
{
	size_t cur_line = *line_number;
	size_t cur_ind = *index;
	size_t 	found = text_[cur_line].find(str, cur_ind);
	if (found != -1) {
		*index = found;
		return true;
	}
	for (int i = cur_line + 1; i < text_.size(); i++) {
		found = text_[i].find(str);
		if (found != -1) {
			*line_number = i;
			*index = found;
			return true;
		}
	}
	return false;
}

bool Model::findUp(size_t* line_number, size_t* index, char* str)
{
	int found = -1;
	int tmp = text_[*line_number].find(str);
	while (tmp != -1 && tmp <= *index && *index!=0) {
		found = tmp;
		tmp = text_[*line_number].find(str, tmp + 1);
	}
	
	
	if (found != -1) {
		*index = found;
		return true;
	}
	for (int i = *line_number - 1; i >= 0; i--) {
		tmp = text_[i].find(str);
		while (tmp != -1) {
			found = tmp;
			tmp = text_[i].find(str, tmp + 1);
		}
		if (found != -1) {
			*line_number = i;
			*index = found;
			return true;
		}
	}
	return false;
}

bool Model::writeToFile(MyString path)
{
	ofstream fout(path.c_str(), ios::binary);
	if (!fout.is_open()) {

		return false;
	}
	for (auto line : text_) {
		fout << line << '\n';
	}
	fout << endl;
	fout.close();
	return true;
}

bool Model::readFromFile(MyString path)
{
	ifstream fin;
	fin.open(path.c_str());
	if (!fin.is_open()) {
		return false;
	}
	char* tmp = new char[1025];
	MyString str;
	while (!fin.eof()) {
		fin.getline(tmp, 1024);
		str = tmp;
		appEndString(str);
	}
	delete[] tmp;
	fin.close();
	return true;
}

void Model::Clear()
{
	text_.clear();
	text_.shrink_to_fit();
}

