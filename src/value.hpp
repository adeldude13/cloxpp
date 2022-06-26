#ifndef VALUE_HPP
#define VALUE_HPP
#include <string>

typedef enum {
	V_BOOL,
	V_NIL,
	V_NUM,
} ValueType;

class Value {
	public:
		Value(double);
		Value(bool);
		Value();
		ValueType type;
		union {
			double number;
			bool b;
		};
		
		void print();

		bool isBool();
		bool isNumber();
		bool isNil(); 
		
		double getNumber();
		bool getBool();
		std::string getNil();
};


#endif
