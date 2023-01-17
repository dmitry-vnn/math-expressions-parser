#pragma once
#include <string>
#include <iostream>

//======================= TOKEN TYPE =======================

enum class TokenType {

	OPEN_BRACKET,
	CLOSE_BRACKET,
	CONST,
	VARIABLE,
	OPERATOR,
	FUNCTION,

	UNKNOWN //Tokenizer встретил что-то не то (неизвестный символ/ы)

};



//========================= TOKEN =========================

class Token {

private:

	TokenType tokenType;
	std::string value;


public:
	Token(TokenType _tokenType, const std::string& _value) : tokenType(_tokenType), value(_value) { }

	Token(const Token& token);
	Token& operator=(const Token& token);

	bool operator==(const Token& token) const;
	bool operator==(const TokenType& type) const { return this->tokenType == type; }

	TokenType GetTokenType() const { return tokenType; }
	std::string GetValue() const { return value; }

	friend std::ostream& operator<<(std::ostream& out, const Token& token);

};
