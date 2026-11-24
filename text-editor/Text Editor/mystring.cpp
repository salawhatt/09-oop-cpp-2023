#include "mystring.h"

//############################# CONSTRUCTORS ################################

MyString::MyString()
{
	str = new char[15];
	str[0] = 0;
	length_str = 0;
	volume = 15;
}

MyString::MyString(const char* string) :MyString(string, strlen(string)) { }

MyString::MyString(const char* string, int count) : MyString()
{
	if (count > volume - 1) {
		delete[] str;
		volume = count + 1;
		str = new char[volume];
	}
	strncpy(str, string, count);
	str[count] = 0;
	length_str = count;
}

MyString::MyString(int count, char symbol) : MyString()
{
	if (count > volume - 1) {
		delete[] str;
		volume = count + 1;
		str = new char[volume];
	}
	for (int i = 0; i < count; i++) {
		str[i] = symbol;
	}
	str[count] = 0;
	length_str = count;
}

MyString::MyString(const MyString& other) :MyString(other.str, other.length_str) {}

MyString::MyString(string& string) : MyString(string.c_str(), string.length()) {}

MyString::MyString(initializer_list<char> list) : MyString()
{
	length_str = list.size();
	if (length_str > volume - 1)
	{
		delete[] str;
		volume = length_str + 1;
		str = new char[volume];
	}
	const char* pList = list.begin();
	strcpy(str, pList);
	str[length_str] = 0;
}

MyString::~MyString()
{
	delete[] this->str;
}

//############################# OPERATORS ###################################

MyString MyString::operator+(string& string)
{
	return *this + (char*)string.c_str();
}

MyString MyString::operator+(const char* string)
{
	if (!string)return *this;
	MyString new_string = MyString(*this);
	new_string.length_str = new_string.length_str + strlen(string);
	char* bmp;
	if (new_string.length_str > volume - 1) {
		bmp = new char[new_string.length_str + 1];
		volume = new_string.length_str + 1;
	}
	else {
		bmp = new char[volume];
	}
	strcpy(bmp, new_string.str);
	delete[] new_string.str;
	new_string.str = bmp;
	strcat(new_string.str, string);
	return new_string;
}

MyString MyString::operator+(const MyString& other)
{
	return *this + other.str;
}

void MyString::operator+=(const char* string)
{
	if (!string)return;
	char* bmp;
	length_str = length_str + strlen(string);
	if (length_str > volume - 1) {
		bmp = new char[length_str + 1];
		volume = length_str + 1;
	}
	else {
		bmp = new char[volume];
	}
	strcpy(bmp, str);
	delete[] str;
	str = bmp;
	strcat(this->str, string);
	return;
}

void MyString::operator+=(string& string)
{
	*this += (char*)string.c_str();
}

void MyString::operator=(string& string)
{
	*this = (char*)string.c_str();
}

void MyString::operator=(const char* string)
{
	if (string == NULL) {
		this->str[0] = 0;
		this->length_str = 0;
		return;
	}
	if (strlen(string) > this->volume - 1) {
		delete[] this->str;
		this->volume = strlen(string) + 1;
		this->str = new char[volume];
	}
	this->length_str = strlen(string);
	strcpy(this->str, string);
}

void MyString::operator=(char symbol)
{
	this->length_str = 1;
	this->str[0] = symbol;
	this->str[1] = 0;
}

void MyString::operator=(MyString other)
{
	*this = other.str;
}

char MyString::operator[](size_t index)
{
	if (index >= this->length_str) return 0;
	return this->str[index];
}

bool MyString::operator>(const MyString& other)
{
	if (strcmp(this->str, other.str) > 0)return true;
	return false;
}

bool MyString::operator<(const MyString& other)
{
	if (strcmp(this->str, other.str) < 0)return true;
	return false;
}

bool MyString::operator<=(const MyString& other)
{
	return !(*this > other);
}

bool MyString::operator>=(const MyString& other)
{
	return !(*this < other);
}

bool MyString::operator==(const MyString& other)
{
	if (strcmp(this->str, other.str) == 0)return true;
	return false;
}

bool MyString::operator!=(const MyString& other)
{
	return !(*this == other);
}

ostream& operator<<(ostream& output, MyString& string) {
	if (!string.str) output << "";
	else output << string.str;
	return output;
}

istream& operator>>(istream& input, MyString& string)
{
	char* tmp = new char[100000];
	input.getline(tmp, 100000);
	if (strlen(tmp) != 0) {
		if (strlen(tmp) > string.volume - 1) {
			delete[] string.str;
			string.volume = strlen(tmp) + 1;
			string.str = new char[string.volume];
		}
		string.length_str = strlen(tmp);
		strcpy(string.str, tmp);
	}
	else {
		string.str[0] = 0;
		string.length_str = 0;
	}
	delete[] tmp;
	return input;
}
//############################# OTHER FUNCTIONS #############################

char* MyString::c_str()
{
	return this->str;
}

char* MyString::data() 
{
	return this->str;
}

size_t MyString::length()
{
	return this->length_str;
}

size_t MyString::size()
{
	return this->length_str;
}

bool MyString::empty() 
{
	return this->length_str == 0;
}

size_t MyString::capacity()
{
	return this->volume;
}

void MyString::shrink_to_fit() 
{
	if (volume == 15 || length_str + 1 == volume) return;
	char* tmp = str;
	if (length_str < 15) {
		str = new char[15];
		volume = 15;
	}
	else {
		volume = length_str + 1;
		str = new char[volume];
	}
	strcpy(str, tmp);
	delete[] tmp;
}

void MyString::clear() 
{
	this->str[0] = 0;
	this->length_str = 0;
}

//############################# INSERT ######################################

void MyString::insert(size_t index, size_t count, char symbol)
{
	if (index > length_str) return;
	char* bmp = str;
	length_str = length_str + count;
	if (length_str >= volume) {
		volume = length_str + 1;
	}
	str = new char[volume];
	strcpy(str, bmp);
	str[index] = 0;
	char* insert_string = new char[count + 1];
	for (size_t i = 0; i < count; i++)
		insert_string[i] = symbol;
	insert_string[count] = 0;
	strcat(str, insert_string);
	strcat(str, bmp + index);
	delete[] bmp;
	delete[] insert_string;
}

void MyString::insert(size_t index, const char* string, size_t count)
{
	if (index > length_str) return;
	if (count > strlen(string)) return;
	char* bmp = this->str;
	length_str = length_str + count;
	if (length_str >= volume) {
		volume = length_str + 1;
	}
	str = new char[volume];
	strcpy(str, bmp);
	str[index] = 0;
	char* insert_string = new char[strlen(string) + 1];
	strcpy(insert_string, string);
	insert_string[count] = 0;
	strcat(this->str, insert_string);
	strcat(this->str, bmp + index);
	delete[] bmp;
	delete[] insert_string;
}

void MyString::insert(size_t index, const char* string)
{
	this->insert(index, string, strlen(string));
}

void MyString::insert(size_t index, string string, size_t count)
{
	this->insert(index, (char*)string.c_str(), count);
}

void MyString::insert(size_t index, string string)
{
	this->insert(index, (char*)string.c_str(), string.length());
}


//############################# ERASE #######################################

void MyString::erase(size_t index, size_t count)
{
	if (index >= this->length_str || count < 1)return;
	if (count + index >= this->length_str) {
		this->str[index] = 0;
	}
	else {
		char* tmp = this->str + (index + count);
		this->str[index] = 0;
		strcat(this->str, tmp);
	}
	this->length_str = strlen(this->str);
}

//############################# APPEND ######################################

void MyString::append(size_t count, char symbol)
{
	char* new_string = new char[count + 1];
	for (size_t i = 0; i < count; i++)
		new_string[i] = symbol;
	new_string[count] = 0;
	this->append(new_string, 0, strlen(new_string));
}

void MyString::append(const char* string)
{
	this->append(string, 0, strlen(string));
}

void MyString::append(const char* string, size_t index, size_t count)
{
	if (index > length_str) return;
	if (count > strlen(string)) return;

	length_str = length_str + count;
	if (length_str >= volume) {
		char* bmp = this->str;
		volume = length_str + 1;
		str = new char[volume];
		strcpy(str, bmp);
		delete[] bmp;
	}
	strcat(str, string);
}

void MyString::append(string string)
{
	this->append((char*)string.c_str(), 0, string.size());
}

void MyString::append(string string, size_t index, size_t count)
{
	this->append((char*)string.c_str(), index, count);
}

//############################# REPLACE #########################################

void MyString::replace(size_t index, size_t count, const char* string)
{
	this->erase(index, count);
	this->insert(index, string);
}

void MyString::replace(size_t index, size_t count, string string)
{
	this->replace(index, count, (char*)string.c_str());
}

//############################# SUBSTR ######################################

MyString MyString::substr(size_t index)
{
	return MyString(this->str + index);
}

MyString MyString::substr(size_t index, size_t count)
{
	char* tmp = new char[count + 1];
	strncpy(tmp, this->str + index, count);
	tmp[count] = 0;
	return MyString(tmp);
}

//############################# FIND ########################################

int MyString::find(const char* string)
{
	return this->find(string, 0);
}

int MyString::find(const char* string, size_t index)
{
	char* pChar = strstr(this->str + index, string);
	if (pChar == NULL) return -1;
	return pChar - this->str;
}

int MyString::find(string string)
{
	return this->find((char*)string.c_str(), 0);
}

int MyString::find(string string, size_t index)
{
	return this->find((char*)string.c_str(), index);
}