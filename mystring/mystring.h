#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std; 

#ifndef MYSTRING_H // header protection
#define MYSTRING_H

class MyString
{
public: 
	//############################# CONSTRUCTORS ################################

	MyString();						           // default constructor

	MyString(const char* string);              // char array constructor

	MyString(initializer_list<char> list);     // initializer list constructor

	MyString(const string string);             // std::string constructor

	MyString(const char* string, int count);   // init class with count characters of  “char string”

	MyString(int count, char symbol);          // init class with count of characters

	MyString(const MyString& other);           // init class with count of characters
	//____________________________ðàçíèöû ìåæäó ññûëêàìè è óêàçàòåëÿìè__________ 

	~MyString();							   // destructor

	//############################# OPERATORS ###################################

	MyString operator+(const MyString& other); // concatenate with Mystring

	MyString operator+(const char* string);    // concatenate with char array

	MyString operator+(const string& string);  // concatenate with std::string
	
	MyString operator=(const char* string);    // char string assignment

	MyString operator=(const string& string);  // std::string assignment

	MyString operator=(const char symbol);     // char assignment

	MyString operator=(const MyString& other); // assigning class object !

	MyString operator+=(const char* string);   // assignment concatenate with char array

	MyString operator+=(const string& string); // assignment concatenate with std::string

	MyString operator+=(const MyString& other);// assignment concatenate with class object !

	char operator[](int index);				   // index operator

	bool operator==(const MyString& other);    // lexicographically comparing1

	bool operator!=(const MyString& other);    // lexicographically comparing2

	bool operator>(const MyString& other);     // lexicographically comparing3

	bool operator<=(const MyString& other);    // lexicographically comparing4

	bool operator<(const MyString& other);     // lexicographically comparing5

	bool operator>=(const MyString& other);    // lexicographically comparing6

	friend ostream& operator<<(ostream& output, const MyString& string); // 

	friend istream& operator>>(istream& input, MyString& string);

	//############################# OTHER FUNCTIONS #############################

	char* c_str() const;						 // return a pointer to null-terminated character array

	char* data() const;							 // return a pointer to array data that not required to be null-terminated

	int length() const;							 // same as size

	int size() const;							 // return the number of char elements in string

	bool empty() const;							 // true if string is empty

	int capacity() const;						 // return the current amount of allocated memory for array

	void shrink_to_fit();					     // reduce the capacity to size

	void clear();							     // remove all char element in string

	//############################# INSERT ######################################

	void insert(int index, int count, char symbol);		           // insert count of char in index position

	void insert(int index, const char* string);                    // insert null-terminated char string at index position 

	void insert(int index, const char* string, int count);         // insert count of null-terminated char string at index position 

	void insert(int index, const string& string);                  // insert std::string at index position

	void insert(int index, const string& string, int count) ;      // insert count of std::string at index position

	//############################# ERASE #######################################

	void erase(int index, int count);						       // erase count of char at index position	

	//############################# APPEND ######################################

	void append(int count, char symbol);					       // append count of char

	void append(const char* string) ;						       // append null-terminated char string

	void append(const char* string, int index, int count) ;        // append a count of null-terminated char string by index position

	void append(const string& string) ;					           // append std:: string

	void append(const string& string, int index, int count) ;      // append a count of std:: string by index position 

	//############################# REPLACE #########################################

	void replace(int index, int count, const char* string);       // replace a count of char at index by “string”

	void replace(int index, int count, const string& string);     // replace a count of char at index by std::string

	//############################# SUBSTR ######################################

	MyString substr(int index);                                   // return a substring starts with index position

	MyString substr(int index, int count);                        // return a count of substring’s char starts with index position

	//############################# FIND ########################################

	int find(const char* string);                                 // if founded return the index of substring  

	int find(const char* string, int index);                      // same as find(“string”) but search starts from index position

	int find(const string& string);								  // if founded return the index of substring

	int find(const string& string, int index);                    // same as find(“string”) but search starts from index position


private:
	char* str;								   // pointer to string
	int length_str;							   // string length
	int volume;								   // memory occupied by the string
}; 


#endif 

