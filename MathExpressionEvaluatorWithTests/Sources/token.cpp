#include "../Headers/token.h"

//========================= TOKEN =========================

Token::Token(const Token& token)
{
	this->tokenType = token.tokenType;
	this->value = token.value;
}

Token& Token::operator=(const Token& token)
{
	if (this == &token) {
		return *this;
	}

	this->tokenType = token.tokenType;
	this->value = token.value;

	return *this;
}

bool Token::operator==(const Token& token) const
{
	return
		this->tokenType == token.tokenType && (
			this->tokenType == TokenType::UNKNOWN || this->value == token.value);
}

std::ostream& operator<<(std::ostream& out, const Token& token)
{
	switch (token.GetTokenType())
	{
	case TokenType::OPEN_BRACKET:
		out << "OPEN_BRACKET";
		break;
	case TokenType::CLOSE_BRACKET:
		out << "CLOSE_BRACKET";
		break;
	case TokenType::CONST:
		out << "CONST";
		break;
	case TokenType::VARIABLE:
		out << "VARIABLE";
		break;
	case TokenType::OPERATOR:
		out << "OPERATOR";
		break;
	case TokenType::FUNCTION:
		out << "FUNCTION";
		break;
	case TokenType::UNKNOWN:
		out << "UNKNOWN";
		break;
	}

	out << ": " << token.GetValue();
	return out;
}
