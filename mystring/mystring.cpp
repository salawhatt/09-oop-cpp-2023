#include "mystring.h"

//############################# CONSTRUCTORS ################################

MyString::MyString()
{
	str = nullptr;
	length_str = 0;
	volume = 0;
}

MyString::MyString(const char* string) :MyString(string, strlen(string))
{

}

MyString::MyString(initializer_list<char> list) 
{
	length_str = list.size();
	volume = length_str + 1;
	this->str = new char[volume];

	int i = 0;
	for (auto elem : list) { 
		this->str[i] = elem;
		++i;
	}
	this->str[length_str] = '\0';
}

MyString::MyString(const string string) :MyString(string.c_str(), strlen(string.c_str()))  //c_str: string=>char*
{

}

MyString::MyString(const char* string, int count) 
{
	length_str = count;
	volume = length_str + 1;

	this->str = new char[volume];

	for (int i = 0; i < count; i++)
		this->str[i] = string[i];

	this->str[count] = '\0';
}

MyString::MyString(int count, char symbol) 
{
	length_str = count;
	volume = length_str + 1;

	this->str = new char[volume];

	for (int i = 0; i < count; i++)
		this->str[i] = symbol;

	this->str[length_str] = '\0';
}

MyString::MyString(const MyString& other) :MyString(other.str, other.length_str)
{

}

MyString::~MyString()
{
	delete[] this->str;
}

//############################# OPERATORS ###################################

MyString MyString::operator+(const MyString& other)
{
	return *this + other.str;
}

MyString MyString::operator+(const char* string)
{
	MyString tmp;
	tmp.length_str = this->length_str + strlen(string);
	tmp.volume = tmp.length_str + 1;

	tmp.str = new char[tmp.volume];

	strcpy(tmp.str, this->str);

	for (int i = this->length_str; i < tmp.length_str; i++)
		tmp.str[i] = string[i - this->length_str];

	tmp.str[tmp.length_str] = '\0';
	return tmp;
}

MyString MyString::operator+(const string& string)
{
	return *this + string.c_str();
}


MyString MyString::operator=(const char* string)
{
	this->length_str = strlen(string);

	if (this->volume < this->length_str + 1)
	{
		this->volume = this->length_str + 1;
	}

	// free перед присв.
	delete[] this->str;
	this->str = new char[this->volume];

	strcpy(this->str, string);

	return *this;
}

MyString MyString::operator=(const string& string)
{
	return *this = string.c_str();
}

MyString MyString::operator=(const char symbol)
{
	this->length_str = 1;
	this->volume = 2;

	this->str = new char[this->volume];

	this->str[0] = symbol;
	this->str[1] = '\0';

	return *this;
}

MyString MyString::operator=(const MyString& other)
{
	return *this = other.str;
}

MyString MyString::operator+=(const char* string)
{

	this->insert(this->length_str, string, strlen(string));
	return *this;
}

MyString MyString::operator+=(const string& string)
{
	return *this += string.c_str();
}

MyString MyString::operator+=(const MyString& other)
{
	return *this += other.str;
}

char MyString::operator[](int index)
{
	return this->str[index];
}

bool MyString::operator==(const MyString& other)
{
	if (strcmp(this->str, other.str))
		return false;

	return true;
}

bool MyString::operator!=(const MyString& other)
{
	return !(*this == other);
}

bool MyString::operator>(const MyString& other)
{
	if (string(this->str).compare(other.str) > 0)
		return true;

	return false;
}

bool MyString::operator<=(const MyString& other)
{
	return !(*this > other);
}

bool MyString::operator<(const MyString& other)
{
	if (string(this->str).compare(other.str) < 0)
		return true;

	return false;
}

bool MyString::operator>=(const MyString& other)
{
	return !(*this < other);
}

ostream& operator<<(ostream& output, const MyString& string)
{
	if (!string.str) output << "";
	else output << string.str;
	return output;
}

istream& operator>>(istream& input, MyString& string)
{
	char* buff = new char[256];
	int i = 0;
	for (buff[i] = input.get(); buff[i] != '\n'; ++i, buff[i] = input.get()) {
		if (i == 255) {
			buff[255] = '\0';
			string.append(buff);
			i = 0;
		}
	}
	buff[i] = '\0';
	string.append(buff);
	return input;
}

//############################# OTHER FUNCTIONS #############################

char* MyString::c_str() const
{
	return this->str;
}

char* MyString::data() const
{
	return this->str;
}

int MyString::length() const
{
	return this->length_str;
}

int MyString::size() const
{
	return this->length_str;
}

bool MyString::empty() const
{
	return this->length_str == 0;
}

int MyString::capacity() const
{
	return this->volume;
}

void MyString::shrink_to_fit() 
{
	if ((this->length_str + 1) == this->volume) return;
	else {
		this->volume = this->length_str + 1;
		char* buff = this->str;
		this->str = new char[this->volume];
		strcpy(this->str, buff);
		delete[] buff;
	}
}

void MyString::clear() 
{
	if (this->length_str != 0) {
		this->str[0] = '\0';
		this->length_str = 0;
	}
}

//############################# INSERT ######################################

void MyString::insert(int index, int count, char symbol) 
{
	char* tmp_str = new char[count + 1];
	for (int i = 0; i < count; ++i)
		tmp_str[i] = symbol;
	tmp_str[count] = '\0';
	this->insert(index, tmp_str, count);
	delete[] tmp_str;
}

void MyString::insert(int index, const char* string) 
{
	this->insert(index, string, strlen(string));
}

void MyString::insert(int index, const char* string, int count) 
{
	if (index < 0 || index > this->length_str || !count || count > strlen(string)) return;

	
	if (this->volume < this->length_str + count + 1)	
	{
		this->volume = this->length_str + count + 1;
	}

	//this->volume = this->length_str + count + 1;

	if (this->str == nullptr) 
	{
		this->str = new char[this->volume];
		strncpy(this->str, string, count);
		this->length_str += count;
		this->str[this->length_str] = '\0';
		return;
	}

	char* buf = this->str;
	this->str = new char[this->volume];
	strncpy(this->str, buf, index);
	strncpy(this->str + index, string, count);
	strncpy(this->str + index + count, buf + index, this->length_str - index);
	delete[] buf;
	this->length_str += count;
	this->str[this->length_str] = '\0';
}

void MyString::insert(int index, const string& string) 
{
	this->insert(index, string.c_str(), strlen(string.c_str()));
}

void MyString::insert(int index, const string& string, int count) 
{
	this->insert(index, string.c_str(), count);
}

//############################# ERASE #######################################

void MyString::erase(int index, int count) 
{
	if (index < 0 || index > this->length_str) return;

	if (index + count >= this->length_str) 
	{
		this->str[index] = '\0';
		this->length_str = index;
	}
	else 
	{
		for (int i = (index + count); i <= length_str; ++i)
			this->str[i - count] = this->str[i];
		this->length_str -= count;
	}
}

//############################# APPEND ######################################

void MyString::append(int count, char symbol) 
{
	this->insert(this->length_str, count, symbol);
}

void MyString::append(const char* string) 
{
	this->insert(this->length_str, string, strlen(string));
}

void MyString::append(const char* string, int index, int count) 
{
	this->insert(this->length_str, string + index, count);
}

void MyString::append(const string& string) 
{
	this->insert(this->length_str, string.c_str(), strlen(string.c_str()));
}

void MyString::append(const string& string, int index, int count) 
{
	this->insert(this->length_str, string.c_str() + index, count);
}

//############################# REPLACE #########################################

void MyString::replace(int index, int count, const char* string)
{
	this->erase(index, count);
	this->insert(index, string, strlen(string));
}

void MyString::replace(int index, int count, const string& string)
{
	this->erase(index, count);
	this->insert(index, string.c_str(), strlen(string.c_str()));
}

//############################# SUBSTR ######################################

MyString MyString::substr(int index)
{
	MyString tmp_str = this->str + index;
	return tmp_str;
}

MyString MyString::substr(int index, int count)
{
	MyString tmp_str;
	tmp_str.append(this->c_str(), index, count);
	return tmp_str;
}

//############################# FIND ########################################

int MyString::find(const char* string)
{
	return this->find(string, 0);
}

int MyString::find(const char* string, int index)
{
	int str_size = strlen(string);
	int i, j, k;
	for (int i = index; i < this->length_str; i++)
	{
		if (this->str[i] == string[0])
		{
			k = i;
			for (j = 0; j < str_size && k < this->volume; j++, k++)
			{
				if (string[j] != this->str[k])
					break;
			}
			if (j == str_size)
				return i;
		}
	}
	return -1;
}

int MyString::find(const string& string)
{
	return this->find(string.c_str(), 0);
}

int MyString::find(const string& string, int index)
{
	return this->find(string.c_str(), index);
}