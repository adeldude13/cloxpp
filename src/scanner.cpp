#include "scanner.hpp" 
#include <string>

#define isNumber(c) (c <= '9'	&& c >= '0')
#define isIden(c) ((c <= 'Z'	&& c >= 'A') || (c <= 'z' && c >= 'a') || (c == '$'))

Token::Token() {
}

Token::Token(TokenType t, int line) {
	this->line = line;
	this->type = t;
}

Token::Token(TokenType t, int line, std::string content) {
	this->content = content;
	this->line = line;
	this->type = t;
}

Scanner::Scanner(std::string str) {
	this->make(str);
}

void Scanner::make(std::string v) {
	source = v;
	i_map["class"] = T_CLASS;
	i_map["if"] = T_IF;
	i_map["else"] = T_ELSE;
	i_map["for"] = T_FOR;
	i_map["while"] = T_WHILE;
	i_map["var"] = T_VAR;
	i_map["return"] = T_RETURN;
	i_map["super"] = T_SUPER;
	i_map["or"] = T_OR;
	i_map["and"] = T_AND;
	i_map["nil"] = T_NIL;
	i_map["true"] = T_TRUE;
	i_map["false"] = T_FALSE;
	i_map["fun"] = T_FUN;
	i_map["print"] = T_PRINT;
	i_map["this"] = T_THIS;
}

Token Scanner::comment() {
	if(isAtEnd()) {
		return makeToken(T_SLASH);
	}
	if(source[curr+1] == '*') {
		curr++;
		return makeToken(T_COMMENT);
	}
	return makeToken(T_SLASH);
}

Token Scanner::bang() {
	if(isAtEnd()) {
		return makeToken(T_BANG);
	}
	if(source[curr+1] == '=') {
		curr++;
		return makeToken(T_BANG_EQUAL);
	}
	return makeToken(T_BANG);
}

Token Scanner::equal() {
	if(isAtEnd()) {
		return makeToken(T_EQUAL);
	}
	if(source[curr+1] == '=') {
		curr++;
		return makeToken(T_EQUAL_EQUAL);
	}
	return makeToken(T_EQUAL);
}

Token Scanner::bigger() {
	if(isAtEnd()) {
		return makeToken(T_GREATER);
	}
	if(source[curr+1] == '=') {
		curr++;
		return makeToken(T_GREATER_EQUAL);
	}
	return makeToken(T_GREATER);
}


Token Scanner::smaller() {
	if(isAtEnd()) {
		return makeToken(T_LESS);
	}
	if(source[curr+1] == '=') {
		curr++;
		return makeToken(T_LESS_EQUAL);
	}
	return makeToken(T_LESS);
}

Token Scanner::strings() {
	std::string ret = "";
	curr++;
	while(1) {
		if(isAtEnd()) {
			if(source[curr-1] != '"') return makeToken(T_ERROR, "Uncomplete String");
			return makeToken(T_STR, ret);
		}
		if(source[curr] == '"') {
			return makeToken(T_STR, ret);
		}
		ret += source[curr++];
	}
	return makeToken(T_STR, ret);
}

Token Scanner::number() {
	bool hadDot = false;
	std::string ret = "";
	while(!isAtEnd() && (isNumber(source[curr]) || (source[curr] == '.' && !hadDot))) {
		if(source[curr] == '.') {
			hadDot = true;
		}
		ret += source[curr++];
	}
	return makeToken(T_NUM, ret);
}

Token Scanner::keyword() {
	std::string v = "";
	while(!isAtEnd() && isIden(source[curr])) {
		v += source[curr++];
	}
	if(i_map.find(v) != i_map.end()) {
		return makeToken(i_map[v]);
	}
	return makeToken(T_IDEN, v);
}

Token Scanner::fetch() {
	
START:
	if(isAtEnd()) {
		return Token(T_EOF, this->line);
	}
	char c = source[curr];
	switch(c) {
		case '(': curr++; return makeToken(T_LEFT_P); break;
		case ')': curr++; return makeToken(T_RIGHT_P); break;
		case '}': curr++; return makeToken(T_LEFT_B); break;
		case '{': curr++; return makeToken(T_RIGHT_B); break;
		case '+': curr++; return makeToken(T_PLUS); break;
		case '-': curr++; return makeToken(T_MINUS); break;
		case '*': curr++; return makeToken(T_STAR); break;
		case '.': curr++; return makeToken(T_DOT); break;
		case ',': curr++; return makeToken(T_COMMA); break;
		case ';': curr++; return makeToken(T_SEMICOLON); break;
		case '\n': this->line++; curr++; goto START;
		case '\r': case '\t': case ' ': curr++; goto START;
		default:
		break;
	}
	if(c == '!') { Token ret = bang(); curr++; return ret; }
	if(c == '=') { Token ret = equal(); curr++; return ret;}
	if(c == '>') { Token ret = bigger(); curr++; return ret;}
	if(c == '<') { Token ret = smaller(); curr++; return ret;}
	if(c == '"') { Token ret = strings(); curr++; return ret; }
	if(isNumber(c)) { Token ret = number(); return ret;}
	if(isIden(c)) { Token ret = keyword(); return ret;}
	if(c == '/') { 
		Token ret = comment(); curr++; 
		if(ret.type == T_COMMENT) {
			while(!isAtEnd() && source[curr++] != '\n');
			goto START;
		}
		return ret;
	}
	curr++;
	return makeToken(T_ERROR, "Invalid Char");
}

#undef isNumebr
#undef isIden 
