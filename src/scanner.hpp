#ifndef SCANNER_H
#define SCANNER_H
#include <unordered_map>
#include <string>

typedef enum {
	T_NUM, T_STR, T_IDEN,

	T_BANG, T_BANG_EQUAL, T_EQUAL_EQUAL, T_LESS, T_GREATER, T_LESS_EQUAL, T_GREATER_EQUAL,

	T_PLUS, T_MINUS, T_STAR, T_SLASH, T_EQUAL, T_LEFT_P, T_RIGHT_P, T_LEFT_B, T_RIGHT_B, T_DOT, T_COMMA, T_COMMENT, T_SEMICOLON,

	T_CLASS, T_IF, T_ELSE, T_FOR, T_WHILE, T_VAR, T_RETURN, T_SUPER, T_OR, T_AND, T_NIL, T_TRUE, T_FALSE, T_FUN, T_PRINT, T_THIS, 

	T_ERROR, T_EOF,
} TokenType;


class Token {
	public:
		Token();
		Token(TokenType, int);
		Token(TokenType, int, std::string);
		TokenType type;	
		std::string content = "";
		int line;
};


class Scanner {
	public:
		Scanner(std::string);
		void make(std::string);
		int line;
		Token fetch();
		bool isAtEnd() { return curr >= source.size(); }
		Token makeToken(TokenType t, std::string v="") {
			return Token(t, line, v);
		}
		Token comment(), bang(), equal(), bigger(), smaller(), strings(), number(), keyword();
	private:
		std::size_t curr = 0;
		std::string source = "";
		std::unordered_map<std::string, TokenType> i_map;
};


#endif
