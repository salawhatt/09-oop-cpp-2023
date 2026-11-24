#include "mystring.h"
//#include "iostream"

#define CONSTRUCTORS 0
#define OPERATORS 0
#define INSERT_ERASE 0
#define APPEND 0
#define REPLACE_SUBSTR 0
#define FIND 0

using namespace std;

int main()
{
	std::string default_msg { "Test #" }; // результат в отчёте
	int num_test = 1;

	MyString test ("HeLlo world!");
	std::cout << test << " " << test.size() << " " << test.capacity() << std::endl;

	test = "Oh,";
	std::cout << test << " " << test.size() << " " << test.capacity() << std::endl;
	
	test += "my";
	std::cout << test << " " << test.size() << " " << test.capacity() << std::endl; 

	test = "HeLlo HeLlo HeLlo HeLlo HeLlo HeLlo!";
	std::cout << test << " " << test.size() << " " << test.capacity() << std::endl;

		

//#################################################################### CONSTRUCTORS ####################################################################
#if CONSTRUCTORS && !OPERATORS && !INSERT_ERASE && !REPLACE_SUBSTR && !FIND
	std::cout << "\n" <<  default_msg << num_test << " Constructor()" << std::endl; num_test++;
	MyString a1;
	std::cout << a1 << " " << a1.size() << " " << a1.capacity();

	std::cout << "\n" <<  default_msg << num_test << " Constructor(\"char string\")" << std::endl; num_test++;
	MyString a2("Hello world!");
	std::cout << a2 << " " << a2.size() << " " << a2.capacity() << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Constructor({\'s\',\'t\',\'r\',\'i\',\'n\',\'g\'})" << std::endl; num_test++;
	MyString a3({ 'h','e','l','l','o' });
	std::cout << a3 << " " << a3.size() << " " << a3.capacity() << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Constructor(std::string)" << std::endl; num_test++;
	std::string s = "hello";
	MyString a4(s);
	std::cout << a4 << " " << a4.size() << " " << a4.capacity() << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Constructor(\"char string\", count)" << std::endl; num_test++;
	MyString a5("hello", 4);
	std::cout << a5 << " " << a5.size() << " " << a5.capacity() << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Constructor( count, char)" << std::endl; num_test++;
	MyString a6(5, '!');
	std::cout << a6 << " " << a6.size() << " " << a6.capacity() << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Constructor(MyString)" << std::endl; num_test++;
	MyString a7("hello");
	MyString a8(a7);
	std::cout << a8 << " " << a8.size() << " " << a8.capacity() << std::endl;

	//#################################################################### OPERATORS ####################################################################

#elif OPERATORS && !CONSTRUCTORS && !INSERT_ERASE && !REPLACE_SUBSTR && !FIND
	std::cout << "\n" <<  default_msg << num_test << " Operator +(Mystring)" << std::endl; num_test++;
	MyString a1("hel"), a2("lo"), a3;
	a3 = a1 + a2;
	std::cout << a1 << " " << a2 << " " << a3 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Operator +(\"char string\")" << std::endl; num_test++;
	MyString a4("hel"), a5;
	a5 = a4 + "lo";
	std::cout << a4 << " " << a5 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Operator +(std::string)" << std::endl; num_test++;
	MyString a6("hel"), a7;
	std::string s1 = "lo";
	a7 = a6 + s1;
	std::cout << a6 << " " << a7 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Operator +=(\"char string\")" << std::endl; num_test++;
	MyString a8("hel"), a9("lo");
	a8 += a9;
	std::cout << a8 << " " << a9 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Operator +=(std::string)" << std::endl; num_test++;
	MyString a10("hel");
	std::string s2 = "lo";
	a10 += s2;
	std::cout << a10 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Operator=(\"char string\")" << std::endl; num_test++;
	MyString a11;
	a11 = "hello";
	std::cout << a11 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Operator=(std::string)" << std::endl; num_test++;
	MyString a12;
	std::string s3 = "hello";
	a12 = s3;
	std::cout << a12 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Operator=(\'char\')" << std::endl; num_test++;
	MyString a13;
	a13 = '!';
	std::cout << a13 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " Opearator[](int)" << std::endl; num_test++;
	MyString a14;
	a14 = "hello";
	std::cout << a14[2] << std::endl;
 
	std::cout << "\n" <<  default_msg << num_test << " Operator>() Operator<() Operator>=() Operator<=() Operator!=() Operator==()" << std::endl; num_test++;
	MyString a, b;
	a = "abcd";
	b = "abce";
	std::cout << (a == b) << (a != b) << (a > b) << (a >= b) << (a < b) << (a <= b) << std::endl;


	//#################################################################### OTHER FUNCTIONS ####################################################################

	std::cout << "\n" <<  default_msg << num_test << " data()" << std::endl; num_test++;
	MyString a15("Hello world!");
	std::string s4;
	s4 = a15.data();
	std::cout << s4 << std::endl;


	std::cout << "\n" <<  default_msg << num_test << " size()" << std::endl; num_test++;
	MyString a16("Hello world!");
	std::cout << a16.size() << std::endl;


	std::cout << "\n" <<  default_msg << num_test << " empty()" << std::endl; num_test++;
	MyString a17("Hello world!");
	std::cout << a17.empty() << std::endl;


	std::cout << "\n" <<  default_msg << num_test << " capacity()" << std::endl; num_test++;
	MyString a18("Hello world!");
	std::cout << a18.capacity() << std::endl;


	std::cout << "\n" <<  default_msg << num_test << " shrink_to_fit()" << std::endl; num_test++;
	MyString a19("Hello world!");
	a19.erase(5, 6);
	std::cout << a19 << " " << a19.size() << " " << a19.capacity() << std::endl;
	a19.shrink_to_fit();
	std::cout << a19 << " " << a19.size() << " " << a19.capacity() << std::endl;


	std::cout << "\n" <<  default_msg << num_test << " clear()" << std::endl; num_test++;
	MyString a20("Hello world!");
	std::cout << a20 << std::endl;
	a20.clear();
	std::cout << a20 << std::endl;


	std::cout << "\n" <<  default_msg << num_test << " Operator<<(std::basic_ostream)" << std::endl; num_test++;
	MyString a21("Hello world!");
	std::cout << a21 << std::endl;


	//std::cout << "\n" <<  default_msg << num_test << " Operator>>(std::basic_istream)" << std::endl; num_test++;

	//#################################################################### INSERT & ERASE ####################################################################
#elif !OPERATORS && !CONSTRUCTORS && INSERT_ERASE && !APPEND && !REPLACE_SUBSTR && !FIND  

	std::cout << "\n" <<  default_msg << num_test << " insert(index, count, char)" << std::endl; num_test++;
	MyString a1 = "aaaaa";
	a1.insert(0, 1, '!');
	std::cout << a1 << std::endl;
	a1.insert(3, 2, '@');
	std::cout << a1 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " insert(index, \"string\")" << std::endl; num_test++;
	MyString a2 = "aaaaa";
	a2.insert(1, "@@@@@");
	std::cout << a2 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " insert(index, \"string\", count)" << std::endl; num_test++;
	MyString a3 = "aaaaa";
	a3.insert(1, "@@@@@", 2);
	std::cout << a3 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " insert(index, std::string)" << std::endl; num_test++;
	MyString a4 = "aaaaa";
	std::string s1 = "@@@@@";
	a4.insert(1, s1);
	std::cout << a4 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " insert(index, std::string, count)" << std::endl; num_test++;
	MyString a5 = "aaaaa";
	std::string s2 = "@@@@@";
	a5.insert(1, s2, 2);
	std::cout << a5 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " erase(index, count)" << std::endl; num_test++;
	MyString a6("Hello world!");
	a6.erase(5, 6);
	std::cout << a6 << std::endl;


	//#################################################################### APPEND ####################################################################
#elif !OPERATORS && !CONSTRUCTORS && !INSERT_ERASE && APPEND && !REPLACE_SUBSTR && !FIND

	std::cout << "\n" <<  default_msg << num_test << " append(count, char)" << std::endl; num_test++;
	MyString a1;
	a1.clear();
	a1.append(3, '!');
	std::cout << a1 << std::endl;
	a1.append(3, '@');
	std::cout << a1 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " append(\"string\")" << std::endl; num_test++;
	MyString a2;
	a2.clear();
	a2.append("Hello ");
	std::cout << a2 << std::endl;
	a2.append("world");
	std::cout << a2 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " append(\"string\", index, count)" << std::endl; num_test++;
	MyString a3;
	a3.clear();
	a3.append("Hello world", 0, 6);
	std::cout << a3 << std::endl;
	a3.append("Hello world", 6, 5);
	std::cout << a3 << std::endl;


	std::cout << "\n" <<  default_msg << num_test << " append(std::string)" << std::endl; num_test++;
	MyString a4;
	std::string s1 = "Hello ", s2 = "world";
	a4.clear();
	a4.append(s1);
	std::cout << a4 << std::endl;
	a4.append(s2);
	std::cout << a4 << std::endl;

	std::cout << "\n" <<  default_msg << num_test << " append(std::string, index, count) " << std::endl; num_test++;
	MyString a5;
	std::string s3 = "Hello world";
	a5.clear();
	a5.append(s3, 0, 6);
	std::cout << a5 << std::endl;
	a5.append(s3, 6, 5);
	std::cout << a5 << std::endl;
	//#################################################################### REPLACE_SUBSTR ####################################################################
#elif !OPERATORS && !CONSTRUCTORS && !INSERT_ERASE && !APPEND && REPLACE_SUBSTR && !FIND
	std::cout << "\n" << default_msg << num_test << " replace(index, count, \"string\")" << std::endl; num_test++;
	MyString a1 = "hello amazing world";
	a1.replace(6, 7, "wonderful");
	std::cout << a1 << std::endl;

	std::cout << "\n" << default_msg << num_test << " replace(index, count, std::string)" << std::endl; num_test++;
	MyString a2 = "hello amazing world";
	std::string s1 = "wonderful";
	a2.replace(6, 7, s1);
	std::cout << a2 << std::endl;

	std::cout << "\n" << default_msg << num_test << " substr(index)" << std::endl; num_test++;
	MyString a3 = "hello amazing world", a4;
	a4 = a3.substr(6);
	std::cout << a4 << std::endl;

	std::cout << "\n" << default_msg << num_test << " substr(index,count)" << std::endl; num_test++;
	MyString a5 = "hello amazing world", a6;
	a6 = a5.substr(6, 7);
	std::cout << a6 << std::endl;


	//#################################################################### FIND ####################################################################
#elif !OPERATORS && !CONSTRUCTORS && !INSERT_ERASE && !APPEND && !REPLACE_SUBSTR && FIND
	std::cout << "\n" << default_msg << num_test << " find(\"string\")" << std::endl; num_test++;
	int i;
	MyString a1 = "hello amazing world amazing";
	i = a1.find("amazing");
	std::cout << i << std::endl;

	std::cout << "\n" << default_msg << num_test << " find(\"string\", index)" << std::endl; num_test++;
	MyString a2 = "hello amazing world amazing";
	i = a2.find("amazing", 7);
	std::cout << i << std::endl;

	std::cout << "\n" << default_msg << num_test << " find(std::string)" << std::endl; num_test++;
	MyString a3 = "hello amazing world amazing";
	std::string s1 = "amazing";
	i = a3.find(s1);
	std::cout << i << std::endl;

	std::cout << "\n" << default_msg << num_test << " find(std::string, index)" << std::endl; num_test++;
	MyString a4 = "hello amazing world amazing";
	std::string s2 = "amazing";
	i = a4.find(s2, 7);
	std::cout << i << std::endl;


#endif
	return 0;
}


