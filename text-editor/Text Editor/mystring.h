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

	MyString();						            // default constructor

	MyString(const char* string);               // char array constructor

	MyString(const char* string, int count);    // init class with count characters of  “char string”

	MyString(int count, char symbol);           // init class with count of characters

	MyString(const MyString& other);            // init class with count of characters

	MyString(string& string);				    // std::string constructor

	MyString(const initializer_list<char> list);// initializer list constructor

	~MyString();							    // destructor

	//############################# OPERATORS ###################################

	MyString operator+(string& string);         // concatenate with std::string

	MyString operator+(const char* string);     // concatenate with char array

	MyString operator+(const MyString& other);  // concatenate with Mystring

	
	void operator+=(const char* string);	    // assignment concatenate with char array

	void operator+=(string& string);		    // assignment concatenate with std::string
	
	void operator=(string& string);		        // std::string assignment
	
	void operator=(const char* string);         // char string assignment

	void operator=(const char symbol);          // char assignment

	void operator=(const MyString other);       // assigning class object !

	char operator[](size_t index);			    // index operator

	bool operator>(const MyString& other);      // lexicographically comparing1

	bool operator<(const MyString& other);      // lexicographically comparing2

	bool operator<=(const MyString& other);     // lexicographically comparing3

	bool operator>=(const MyString& other);     // lexicographically comparing4
	 
	bool operator==(const MyString& other);     // lexicographically comparing5

	bool operator!=(const MyString& other);     // lexicographically comparing6

	friend ostream& operator<<(ostream& output, MyString& string);

	friend istream& operator>>(istream& input, MyString& string);

	//############################# OTHER FUNCTIONS #############################

	char* c_str();						      // return a pointer to null-terminated character array

	char* data();							  // return a pointer to array data that not required to be null-terminated

	size_t length();						  // same as size

	size_t size();							  // return the number of char elements in string

	bool empty();							  // true if string is empty

	size_t capacity();						  // return the current amount of allocated memory for array

	void shrink_to_fit();					  // reduce the capacity to size

	void clear();							  // remove all char element in string

	//############################# INSERT ######################################

	void insert(size_t index, size_t count, char symbol);		// insert count of char in index position

	void insert(size_t index, const char* string, size_t count);// insert count of null-terminated char string at index position 

	void insert(size_t index, const char* string);              // insert null-terminated char string at index position 

	void insert(size_t index, string string, size_t count);     // insert count of std::string at index position

	void insert(size_t index, string string);                   // insert std::string at index position

	//############################# ERASE #######################################

	void erase(size_t index, size_t count);						// erase count of char at index position	

	//############################# APPEND ######################################

	void append(size_t count, char symbol);					      // append count of char

	void append(const char* string) ;						      // append null-terminated char string

	void append(const char* string, size_t index, size_t count) ; // append a count of null-terminated char string by index position

	void append(string string) ;					              // append std:: string

	void append(string string, size_t index, size_t count) ;      // append a count of std:: string by index position 

	//############################# REPLACE #########################################

	void replace(size_t index, size_t count, const char* string); // replace a count of char at index by “string”

	void replace(size_t index, size_t count, string string);      // replace a count of char at index by std::string

	//############################# SUBSTR ######################################

	MyString substr(size_t index);                                // return a substring starts with index position

	MyString substr(size_t index, size_t count);                  // return a count of substring’s char starts with index position

	//############################# FIND ########################################

	int find(const char* string);                                 // if founded return the index of substring  

	int find(const char* string, size_t index);                   // same as find(“string”) but search starts from index position

	int find(string string);								      // if founded return the index of substring

	int find(string string, size_t index);                        // same as find(“string”) but search starts from index position


private:
	char* str;								   // pointer to string
	int length_str;							   // string length
	int volume;								   // memory occupied by the string
}; 


#endif 

