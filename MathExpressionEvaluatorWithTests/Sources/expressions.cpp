#include "../Headers/expressions.h"

#include <set>
#include "../Headers/containers_utils.h"

#include <iostream>
#include "../Headers/dynamic_stack.h"
#include "../Headers/token.h"
#include <sstream>



//========================= TOKENIZER =========================

std::vector<Token> Tokenizer::ToTokens() const
{
	std::vector<Token> tokens;
	
	std::string infix = this->infix;

	Containers::ReplaceAll(infix, " ", "");

	size_t pos = 0;

	std::set<char> uniqueOperatorChars;
	FillUniqueOperatorsChars(uniqueOperatorChars);

	while (pos < infix.length())
	{
		if (infix[pos] == '(' || infix[pos] == ')') {
			
			std::string symbol(1, infix[pos]);

			Token token(
				symbol == "(" ? 
				TokenType::OPEN_BRACKET 
				:
				TokenType::CLOSE_BRACKET,
				symbol
			);

			tokens.push_back(token);

			pos++;
			continue;
		}

		if (infix[pos] >= '0' && infix[pos] <= '9') {

			size_t endPos = FindEndIndexOfNumber(infix, pos);
			
			Token token(TokenType::CONST, infix.substr(pos, (endPos - pos + 1)));
			tokens.push_back(token);

			pos += (endPos - pos + 1);
			continue;
		}

		if ((infix[pos] >= 'a' && infix[pos] <= 'z') || (infix[pos] >= 'A' && infix[pos] <= 'Z')) {
			size_t endPos = FindEndIndexOfLatin(infix, pos);

			std::string sub = infix.substr(pos, (endPos - pos + 1));

			if (Containers::VectorContains(functionNames, sub)) {

				Token token(TokenType::FUNCTION, sub);
				tokens.push_back(token);

				pos += (endPos - pos + 1);
				continue;
			}

			if (Containers::VectorContains(variableNames, sub)) {

				Token token(TokenType::VARIABLE, sub);
				tokens.push_back(token);

				pos += (endPos - pos + 1);
				continue;
			}

			Token token(TokenType::UNKNOWN, sub);
			tokens.push_back(token);

			pos += (endPos - pos + 1);
			continue;

		}

		if (Containers::SetContains(uniqueOperatorChars, infix[pos])) {

			size_t endPos = FindEndIndexOfOperator(infix, pos, uniqueOperatorChars);
			std::string sub = infix.substr(pos, (endPos - pos + 1));

			if (Containers::VectorContains(operators, sub)) {

				Token token(TokenType::OPERATOR, sub);
				tokens.push_back(token);

				pos += (endPos - pos + 1);
				continue;
			}

			Token token(TokenType::UNKNOWN, sub);
			tokens.push_back(token);

			pos += (endPos - pos + 1);
			continue;

		}

		std::string symbol(1, infix[pos]);

		Token token(TokenType::UNKNOWN, symbol);
		tokens.push_back(token);

		pos++;

	}

	return tokens;

}


void Tokenizer::FillUniqueOperatorsChars(std::set<char>& s) const
{
	for (const auto& op : operators)
	{
		for (const char& c : op) {
			s.insert(c);
		}
	}
}

size_t Tokenizer::FindEndIndexOfNumber(const std::string& str, size_t startIndex) const
{
	size_t endIndex = startIndex + 1;

	bool hasDot = false;
	
	while (endIndex < str.length())
	{
		if (str[endIndex] >= '0' && str[endIndex] <= '9') {
			endIndex++;
			continue;
		}

		if (str[endIndex] == '.') {
			if (!hasDot) {
				hasDot = true;
				endIndex++;
				continue;
			}
		}

		break;
	}

	return endIndex - 1;

}

size_t Tokenizer::FindEndIndexOfLatin(const std::string& str, size_t startIndex) const
{
	size_t endIndex = startIndex + 1;

	while (endIndex < str.length())
	{
		if ((str[endIndex] >= 'a' && str[endIndex] <= 'z') ||
			(str[endIndex] >= 'A' && str[endIndex] <= 'Z')) 
		{
			endIndex++;
			continue;
		}

		break;
	}

	return endIndex - 1;
}

size_t Tokenizer::FindEndIndexOfOperator(const std::string& str, size_t startIndex, const std::set<char>& allowedSymbols) const
{
	size_t endIndex = startIndex + 1;

	while (endIndex < str.length())
	{
		if (Containers::SetContains(allowedSymbols, str[endIndex])) {
			endIndex++;
			continue;
		}

		break;
	}

	return endIndex - 1;
}


//========================= VALIDATOR =========================

void Validator::TryValidOrThrow() const
{
	if (Containers::VectorContains(tokens, Token(TokenType::UNKNOWN, ""))) {
		throw ValidationException(
			std::string("Неизвестный элемент '")
			+ Containers::VectorFind(tokens, TokenType::UNKNOWN).GetValue()
			+ "' "
		);
	}

	int countOfOpenBrackets = 0;

	Token previousToken = Token(TokenType::UNKNOWN, "<ничего>");
	size_t tokenIndex = 0;

	while (tokenIndex < tokens.size())
	{
		TokenType previousTokenType = previousToken.GetTokenType();

		const Token& token = tokens[tokenIndex];

		TokenType tokenType = token.GetTokenType();

		if (tokenType == TokenType::OPEN_BRACKET) {
			countOfOpenBrackets++;
		}
		else if (tokenType == TokenType::CLOSE_BRACKET) {
			if (--countOfOpenBrackets < 0) {
				throw ValidationException("Лишняя закрывающаяся скобка");
			}
		}

		switch (tokenType)
		{

		case TokenType::OPEN_BRACKET: {

			if (previousTokenType == TokenType::VARIABLE ||
				previousTokenType == TokenType::CONST ||
				previousTokenType == TokenType::CLOSE_BRACKET)
			{
				throw ValidationException(
					std::string("Перед элементом '")
					+ token.GetValue()
					+ "' Не может стоять элемент '"
					+ previousToken.GetValue()
					+ "'"
				);
			}

			break;
		}

		case TokenType::CLOSE_BRACKET:
		case TokenType::OPERATOR: {

			if (previousTokenType != TokenType::VARIABLE &&
				previousTokenType != TokenType::CONST &&
				previousTokenType != TokenType::CLOSE_BRACKET)
			{
				throw ValidationException(
					std::string("Перед элементом '")
					+ token.GetValue()
					+ "' Не может стоять элемент '"
					+ previousToken.GetValue()
					+ "'"
				);
			}

			break;
		}


		case TokenType::CONST:
		case TokenType::VARIABLE:
		case TokenType::FUNCTION:
		default: {

			if (previousTokenType != TokenType::UNKNOWN &&
				previousTokenType != TokenType::OPERATOR &&
				previousTokenType != TokenType::OPEN_BRACKET)
			{
				throw ValidationException(
					std::string("Перед элементом '")
					+ token.GetValue()
					+ "' Не может стоять элемент '"
					+ previousToken.GetValue()
					+ "'"
				);
			}

			break;
		}
		}

		tokenIndex++;
		previousToken = token;
	}

	if (countOfOpenBrackets != 0) {
		throw ValidationException("Лишняя открывающаяся скобка");
	}

	TokenType previousTokenType = previousToken.GetTokenType();

	if (previousTokenType != TokenType::CLOSE_BRACKET &&
		previousTokenType != TokenType::CONST &&
		previousTokenType != TokenType::VARIABLE
		)
	{
		throw ValidationException(
			std::string("Выражение не может оканчиваться элементом '")
			+ previousToken.GetValue()
			+ "'"
		);
	}

}

bool Validator::IsValid() const
{
	try {
		TryValidOrThrow();
		return true;
	}
	catch (ValidationException) {
		return false;
	}
}



//========================= POSTFIX_TRANSLATOR =========================


std::vector<Token> PostfixTranslator::ToPostfixTokens() const
{
	std::vector<Token> tokens;
	tokens.reserve(infixTokens.size());
	
	TDynamicStack<std::shared_ptr<const Prioritable>> prioritableStack;
	
	for (const Token& token : infixTokens) {
	
		TokenType tokenType = token.GetTokenType();
	
		if (tokenType == TokenType::OPEN_BRACKET) {
			prioritableStack.Push(std::make_shared<const OpenBracket>());

			continue;
		}
	
		if (tokenType == TokenType::VARIABLE || tokenType == TokenType::CONST) {
			tokens.push_back(token);
			continue;
		}
	
		if (tokenType == TokenType::CLOSE_BRACKET) {
	
			if (prioritableStack.IsEmpty()) {
				continue;
			}

			Token topStack = prioritableStack.Pop()->ToToken();
			while (topStack.GetTokenType() != TokenType::OPEN_BRACKET) {
				tokens.push_back(topStack);

				if (prioritableStack.IsEmpty()) {
					break;
				}

				topStack = prioritableStack.Pop()->ToToken();
			}
			continue;
		}
	
		if (tokenType == TokenType::OPERATOR) {
			
			auto tokenAsOperator = Containers::VectorFind(operators, token.GetValue());

			while (!prioritableStack.IsEmpty()) {

				auto topStack = prioritableStack.Pop();

				if (tokenAsOperator->GetPriority() <= topStack->GetPriority()) {
					tokens.push_back(topStack->ToToken());
					continue;
				}
				
				prioritableStack.Push(topStack);
				break;

			}

			prioritableStack.Push(tokenAsOperator);

		}

		if (tokenType == TokenType::FUNCTION) {

			auto tokenAsFunction = Containers::VectorFind(functions, token.GetValue());

			while (!prioritableStack.IsEmpty()) {

				auto topStack = prioritableStack.Pop();

				if (tokenAsFunction->GetPriority() <= topStack->GetPriority()) {
					tokens.push_back(topStack->ToToken());
					continue;
				}

				prioritableStack.Push(topStack);
				break;

			}

			prioritableStack.Push(tokenAsFunction);

		}
	
	}
	
	while (!prioritableStack.IsEmpty()) {
		tokens.push_back(prioritableStack.Pop()->ToToken());
	}

	return tokens;

}

//std::shared_ptr<Prioritable> PostfixTranslator::FindOperatorByName(const std::string& name) const
//{
//	for (auto& opPtr : operators) {
//		if (opPtr.get()->GetName() == name) {
//			return opPtr;
//		}
//	}
//
//	throw "Operator not found";
//}
//
//std::shared_ptr<Prioritable> PostfixTranslator::FindFunctionByName(const std::string& name) const
//{
//	for (auto& funPtr : functions) {
//		if (funPtr.get()->GetName() == name) {
//			return funPtr;
//		}
//	}
//	
//	throw "Function not found";
//}

//========================= POSTFIX EVALUATOR =========================

double PostfixEvaluator::Evaluate() const
{

	TDynamicStack<double> operands;

	for (const auto& token : postfixTokens) {

		switch (token.GetTokenType()) {
			case TokenType::OPERATOR: {
				double arg2 = operands.Pop();
				double arg1 = operands.Pop();

				auto binaryOperator = Containers::VectorFind(operators, token.GetValue());

				double result = binaryOperator->Evaluate(arg1, arg2);

				operands.Push(result);

				continue;
			}
			case TokenType::FUNCTION: {
				double arg = operands.Pop();

				auto unaryFunction = Containers::VectorFind(functions, token.GetValue());

				double result = unaryFunction->Evaluate(arg);

				operands.Push(result);

				continue;
			}
			case TokenType::VARIABLE: {
				operands.Push(Containers::VectorFind(variables, token.GetValue()).GetValue());
				continue;
			}
			case TokenType::CONST: {
				operands.Push(ToDouble(token.GetValue()));
				continue;
			}
		}
	}

	return operands.Pop();
}

double PostfixEvaluator::ToDouble(const std::string& value) const
{
	std::istringstream iss(value);
	double result;
	if (!(iss >> result))
		throw EvaluationException("Not a number");
	return result;
}



//========================= EXPRESSOR =========================


Expressor::Expressor(const std::string& _infix, const std::vector<Variable>& _variables) :
	infix(_infix),
	variables(_variables),
	operators
	{
		std::make_shared<OperatorAdd>(),
		std::make_shared<OperatorSubtract>(),
		std::make_shared<OperatorMultiply>(),
		std::make_shared<OperatorDivide>(),
		std::make_shared<OperatorPow>(),
		std::make_shared<OperatorModulus>()
	},
	functions
	{
		std::make_shared<FunctionSin>(),
		std::make_shared<FunctionCos>(),
		std::make_shared<FunctionTan>(),
		std::make_shared<FunctionCot>(),
		std::make_shared<FunctionLn>(),
		std::make_shared<FunctionAbs>(),
		std::make_shared<FunctionSqrt>(),
		std::make_shared<FunctionCbrt>()
	}

{

	std::vector<std::string> functionNames, operatorNames, variableNames;

	functionNames.reserve(functions.size());
	operatorNames.reserve(operators.size());
	variableNames.reserve(variables.size());

	for (const auto& fun : functions) {
		functionNames.push_back(fun->GetName());
	}

	for (const auto& op : operators) {
		operatorNames.push_back(op->GetName());
	}

	for (const auto& var : variables) {
		variableNames.push_back(var.GetName());
	}

	Tokenizer tokenizer(infix, operatorNames, functionNames, variableNames);

	infixTokens = tokenizer.ToTokens();

	Validator validator(infixTokens);

	validator.TryValidOrThrow();

	PostfixTranslator translator(infixTokens, operators, functions);

	postfixTokens = translator.ToPostfixTokens();
	
	postfix = "";

	for (const auto& token : postfixTokens) {
		postfix.append(token.GetValue());
	}


}

double Expressor::Evaluate() const
{

	PostfixEvaluator evaluator(postfixTokens, operators, functions, variables);

	return evaluator.Evaluate();
}
