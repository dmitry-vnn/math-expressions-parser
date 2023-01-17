#ifndef MATH_TERMS_H
#define MATH_TERMS_H

#include <string>
#include "token.h"


//========================= PRIORITABLE =========================

class Prioritable {

private:
	size_t priority;

public:

	Prioritable(size_t _priority) : priority(_priority) {}
	Prioritable(const Prioritable& prioritable) : priority(prioritable.priority) {}

	size_t GetPriority() const { return priority; }

	virtual Token ToToken() const = 0;

};

//========================= BINARY OPERATORS =========================

class BinaryOperator : public Prioritable {

private:
	std::string name;

public:

	BinaryOperator(size_t _priority, const std::string& _name) :
		Prioritable(_priority),
		name(_name) {}

	BinaryOperator(const BinaryOperator& binaryOperator) :
		Prioritable(binaryOperator),
		name(binaryOperator.GetName()) {}

	BinaryOperator& operator=(const BinaryOperator& binaryOperator) = delete;

	bool operator==(const std::string& tokenName) const { return this->name == tokenName; }

	virtual double Evaluate(double arg1, double arg2) const = 0;
	std::string GetName() const { return name; }

	Token ToToken() const override { return Token(TokenType::OPERATOR, name); }
};

class OperatorAdd : public BinaryOperator {

public:
	OperatorAdd() :
		BinaryOperator::BinaryOperator(1, "+") {}

	double Evaluate(double arg1, double arg2) const override;
};

class OperatorSubtract : public BinaryOperator {

public:
	OperatorSubtract() :
		BinaryOperator::BinaryOperator(1, "-") {}

	double Evaluate(double arg1, double arg2) const override;
};

class OperatorMultiply : public BinaryOperator {

public:

	OperatorMultiply() :
		BinaryOperator::BinaryOperator(2, "*") {}

	double Evaluate(double arg1, double arg2) const override;
};

class OperatorDivide : public BinaryOperator {

public:

	OperatorDivide() :
		BinaryOperator::BinaryOperator(2, "/") {}

	double Evaluate(double arg1, double arg2) const override;
};

class OperatorPow : public BinaryOperator {

public:

	OperatorPow() :
		BinaryOperator::BinaryOperator(3, "^") {}

	double Evaluate(double arg1, double arg2) const override;
};

class OperatorModulus : public BinaryOperator {

public:

	OperatorModulus() :
		BinaryOperator::BinaryOperator(3, "%") {}

	double Evaluate(double arg1, double arg2) const override;
};


//========================= FUNCTIONS =========================


class UnaryFunction : public Prioritable {

private:
	std::string name;

public:

	UnaryFunction(const std::string& _name) :
		Prioritable(100),
		name(_name) {}

	UnaryFunction(const UnaryFunction& unaryFunction) :
		Prioritable(unaryFunction),
		name(unaryFunction.GetName()) {}

	UnaryFunction& operator=(const UnaryFunction& binaryOperator) = delete;

	bool operator==(const std::string& tokenName) const { return this->name == tokenName; }

	virtual double Evaluate(double arg) const = 0;
	std::string GetName() const { return name; }

	Token ToToken() const override { return Token(TokenType::FUNCTION, name); }
};


class FunctionSin : public UnaryFunction {

public:

	FunctionSin() :
		UnaryFunction::UnaryFunction("sin") {}

	double Evaluate(double arg) const override;
};

class FunctionCos : public UnaryFunction {

public:

	FunctionCos() :
		UnaryFunction::UnaryFunction("cos") {}

	double Evaluate(double arg) const override;
};

class FunctionTan : public UnaryFunction {

public:

	FunctionTan() :
		UnaryFunction::UnaryFunction("tan") {}

	double Evaluate(double arg) const override;
};

class FunctionCot : public UnaryFunction {

public:

	FunctionCot() :
		UnaryFunction::UnaryFunction("cot") {}

	double Evaluate(double arg) const override;
};

class FunctionLn : public UnaryFunction {

public:

	FunctionLn() :
		UnaryFunction::UnaryFunction("ln") {}

	double Evaluate(double arg) const override;
};

class FunctionAbs : public UnaryFunction {

public:

	FunctionAbs() :
		UnaryFunction::UnaryFunction("abs") {}

	double Evaluate(double arg) const override;
};

class FunctionSqrt : public UnaryFunction {

public:

	FunctionSqrt() :
		UnaryFunction::UnaryFunction("sqrt") {}

	double Evaluate(double arg) const override;
};

class FunctionCbrt : public UnaryFunction {

public:

	FunctionCbrt() :
		UnaryFunction::UnaryFunction("cbrt") {}

	double Evaluate(double arg) const override;
};


//========================= BRACKETS =========================

class OpenBracket : public Prioritable {

public:

	OpenBracket() : Prioritable(0) {}

	OpenBracket(const OpenBracket& openBracket) : Prioritable(openBracket) {}

	OpenBracket& operator=(const OpenBracket& bracket) = delete;

	Token ToToken() const override { return Token(TokenType::OPEN_BRACKET, "("); }

};

class CloseBracket : public Prioritable {

public:

	CloseBracket() : Prioritable(0) {}

	CloseBracket(const CloseBracket& closeBracket) : Prioritable(closeBracket) {}

	CloseBracket& operator=(const CloseBracket& bracket) = delete;

	Token ToToken() const override { return Token(TokenType::CLOSE_BRACKET, ")"); }

};

//========================= VARIABLES =========================

class Variable {

private:

	std::string name;
	double value;

public:
	Variable(const std::string& _name, double _value) : name(_name), value(_value) {}

	Variable(const Variable& variable) : name(variable.name), value(variable.value) {}

	Variable& operator=(const Variable& variable) = delete;

	bool operator==(const std::string& tokenName) const { return this->name == tokenName; }

	std::string GetName() const { return name; }

	double GetValue() const { return value; }

};

//========================= EVALUATION_EXCEPTION =========================

class EvaluationException {

private:

	std::string message;

public:

	EvaluationException(const std::string& _message) :
		message(_message) {};

	std::string GetMessage() { return message; }

};

#endif