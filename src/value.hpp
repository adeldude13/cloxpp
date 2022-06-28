#ifndef VALUE_HPP
#define VALUE_HPP
#include <string>

typedef enum {
	V_BOOL,
	V_NIL,
	V_NUM,
	V_STR,
} ValueType;

class Value;

class Str {
	public:
		Str(std::string);
		void addObj(Str *);
		std::string content;
		Str *next;
};


class Value {
	public:
		Value(double);
		Value(bool);
		Value(std::string);
		Value();
		ValueType type;
		union {
			double number;
			bool b;
			Str *str;
		};
		
		void print();

		bool isBool();
		bool isNumber();
		bool isNil(); 
		bool isStr();

		double getNumber();
		bool getBool();
		std::string getNil();
		std::string getStr();
};


#endif
