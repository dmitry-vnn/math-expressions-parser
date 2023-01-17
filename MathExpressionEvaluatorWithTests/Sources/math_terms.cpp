#include "../Headers/math_terms.h"

//========================= BINARY OPERATORS =========================


double OperatorAdd::Evaluate(double arg1, double arg2) const
{
	return arg1 + arg2;
}

double OperatorSubtract::Evaluate(double arg1, double arg2) const
{
	return arg1 - arg2;
}

double OperatorMultiply::Evaluate(double arg1, double arg2) const
{
	return arg1 * arg2;
}

double OperatorDivide::Evaluate(double arg1, double arg2) const
{
	if (arg2 == 0) {
		throw "division by zero";
	}
	return arg1 / arg2;
}

double OperatorPow::Evaluate(double arg1, double arg2) const
{

	if (arg1 == 0 && arg2 < 0) {
		throw EvaluationException("pow for zero exponent argument must be non-negative");
	}

	return pow(arg1, arg2);
}

double OperatorModulus::Evaluate(double arg1, double arg2) const
{
	if (arg2 == 0) {
		throw EvaluationException("modulus division by zero");
	}
	return (long)arg1 % (long)arg2;
}


//========================= FUNCTIONS =========================



double FunctionSin::Evaluate(double arg) const
{
	return sin(arg);
}

double FunctionCos::Evaluate(double arg) const
{
	return cos(arg);
}

double FunctionTan::Evaluate(double arg) const
{
	return tan(arg);
}

double FunctionCot::Evaluate(double arg) const
{
	return 1 / tan(arg);
}

double FunctionLn::Evaluate(double arg) const
{
	return log(arg);
}

double FunctionAbs::Evaluate(double arg) const
{
	return abs(arg);
}

double FunctionSqrt::Evaluate(double arg) const
{
	if (arg < 0) {
		throw EvaluationException("sqrt argument must be non-negative");
	}

	return sqrt(arg);
}

double FunctionCbrt::Evaluate(double arg) const
{
	return cbrt(arg);
}
