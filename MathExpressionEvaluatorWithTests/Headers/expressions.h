#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <string>
#include <vector>
#include <set>

#include "math_terms.h"


//========================= TOKENIZER =========================

class Tokenizer {

private:

	std::string infix;
	
	std::vector<std::string> operators;
	std::vector<std::string> functionNames;
	std::vector<std::string> variableNames;


public:

	Tokenizer(
		const std::string& _infix, 
		const std::vector<std::string>& _operators,
		const std::vector<std::string>& _functionNames,
		const std::vector<std::string>& _variableNames
	): 
		infix(_infix), 
		operators(_operators),
		functionNames(_functionNames),
		variableNames(_variableNames)
	{};

	Tokenizer(const Tokenizer& tokenizer) = delete;
	Tokenizer& operator=(const Tokenizer& tokenizer) = delete;

	std::vector<Token> ToTokens() const;

private:

	void FillUniqueOperatorsChars(std::set<char>& s) const;

	size_t FindEndIndexOfNumber(const std::string& str, size_t startIndex) const;
	size_t FindEndIndexOfLatin(const std::string& str, size_t startIndex) const;
	size_t FindEndIndexOfOperator(const std::string& str, size_t startIndex, const std::set<char>& allowedSymbols) const;


};


//========================= VALIDATOR =========================

class Validator {

private:

	std::vector<Token> tokens;

public:

	Validator(const std::vector<Token>& _tokens) : tokens(_tokens) {}
	bool IsValid() const;
	void TryValidOrThrow() const;

	Validator(const Validator& validator) = delete;
	Validator& operator=(const Validator& validator) = delete;

};

enum class ValidationResult {

	SUCCESS,
	WRONG

};

class ValidationException {

private:

	std::string message;

public:

	ValidationException( const std::string& _message) :
		message(_message) {};

	std::string GetMessage() { return message; }

};


//========================= POSTFIX_TRANSLATOR =========================


class PostfixTranslator {

private:

	std::vector<Token> infixTokens;
	std::vector<std::shared_ptr<const BinaryOperator>> operators;
	std::vector<std::shared_ptr<const UnaryFunction>> functions;


public:

	 PostfixTranslator(
		const std::vector<Token>& _infixTokens, 
		const std::vector<std::shared_ptr<const BinaryOperator>>& _operators,
		const std::vector<std::shared_ptr<const UnaryFunction>>& _functions
	):
		infixTokens(_infixTokens),
		operators(_operators),
		functions(_functions) {}

	PostfixTranslator(const PostfixTranslator& validator) = delete;
	PostfixTranslator& operator=(const PostfixTranslator& validator) = delete;

	std::vector<Token> ToPostfixTokens() const;


private:

	//std::shared_ptr<Prioritable> FindOperatorByName(const std::string& name) const;
	//std::shared_ptr<Prioritable> FindFunctionByName(const std::string& name) const;

};


//========================= POSTFIX EVALUATOR =========================


class PostfixEvaluator {

private:

	std::vector<Token> postfixTokens;
	std::vector<std::shared_ptr<const BinaryOperator>> operators;
	std::vector<std::shared_ptr<const UnaryFunction>> functions;
	std::vector<Variable> variables;


public:

	PostfixEvaluator(
		const std::vector<Token>& _postfixTokens,
		const std::vector<std::shared_ptr<const BinaryOperator>>& _operators,
		const std::vector<std::shared_ptr<const UnaryFunction>>& _functions,
		const std::vector<Variable>& _variables
	) :
		postfixTokens(_postfixTokens),
		operators(_operators),
		functions(_functions),
		variables(_variables) {}

	PostfixEvaluator(const PostfixTranslator& validator) = delete;
	PostfixEvaluator& operator=(const PostfixTranslator& validator) = delete;

	double Evaluate() const;


private:

	double ToDouble(const std::string& value) const;

};

//========================= EXPRESSOR =========================

class Expressor {

private:
	
	std::string infix;
	std::vector<Variable> variables;

	std::vector<std::shared_ptr<const BinaryOperator>> operators;
	std::vector<std::shared_ptr<const UnaryFunction>> functions;


	std::vector<Token> infixTokens;

	std::string postfix;
	std::vector<Token> postfixTokens;



public:

	Expressor(
		const std::string& _infix,
		const std::vector<Variable>& _variables
	);

	Expressor(const Expressor&) = delete;
	Expressor& operator=(const Expressor&) = delete;

	double Evaluate() const;
	
	std::string GetInfix() const  { return infix; }
	std::string GetPostfix() const { return postfix; }

	std::vector<Token> GetInfixTokens() const { return infixTokens; }
	std::vector<Token> GetPostfixTokens() const { return postfixTokens; }

};


#endif


