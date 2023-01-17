#include <gtest/gtest.h>
#include "../Headers/expressions.h"


TEST(Expressor, Expr1) {

	try {
		
		Expressor expressor("(sin(a+b))^2+(cos(a+b))^2", 
			{ 
				{"a", 1},
				{"b", 52} 
			}
		);

		EXPECT_DOUBLE_EQ(expressor.Evaluate(), 1);
	}
	catch (ValidationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}
	catch (EvaluationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}

}

TEST(Expressor, Expr2) {

	try {

		Expressor expressor("sin(2*x)-2*sin(x)*cos(x)",
			{
				{"x", 525}
			}
		);

		EXPECT_DOUBLE_EQ(expressor.Evaluate(), 0);
	}
	catch (ValidationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}
	catch (EvaluationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}

}

TEST(Expressor, Expr3) {

	try {

		Expressor expressor("ln(x^y)-y*ln(x)",
			{
				{"x", 5},
				{"y", 13},
			}
		);

		EXPECT_TRUE(abs(expressor.Evaluate()) < 1);
	}
	catch (ValidationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}
	catch (EvaluationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}

}

TEST(Expressor, Expr4) {

	try {

		double x = 635;
		Expressor expressor("cos(2*sqrt(x))-(cos(sqrt(x)))^2-(sin(sqrt(x)))^2",
			{
				{"x", x}
			}
		);

		EXPECT_DOUBLE_EQ(
			expressor.Evaluate(), 
			cos(2*sqrt(x)) - pow(cos(sqrt(x)), 2) - pow(sin(sqrt(x)), 2) 
		);
	}
	catch (ValidationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}
	catch (EvaluationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}

}

TEST(Expressor, Expr5) {

	try {

		double a = 1;
		double b = 3;
		Expressor expressor("a*a+b*b*b + a/sqrt(2*b)",
			{
				{"a", a},
				{"b", b},
			}
		);

		EXPECT_DOUBLE_EQ(
			expressor.Evaluate(),
			a * a + b * b * b + a / sqrt(2 * b)
		);
	}
	catch (ValidationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}
	catch (EvaluationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}

}

TEST(Expressor, Expr6) {

	try {

		double x = 4;
		double y = 0.3;
		double pi = 3.14159265358979323846;
		double exp = std::exp(1);

		Expressor expressor(

			"cos(4*pi/3+3*x)+exp*y*0.1-3.63",
			{
				{"x", x},
				{"y", y},
				{"pi", pi},
				{"exp", exp}
			}
		);

		EXPECT_DOUBLE_EQ(expressor.Evaluate(), cos(4 * pi / 3 + 3 * x) + exp * y * 0.1 - 3.63);
	}
	catch (ValidationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}
	catch (EvaluationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}

}


TEST(Expressor, Expr7) {

	try {

		double x = 4;
		double y = 0.3;

		Expressor expressor(

			"((((x)+1)))*((((2+(y)))))",
			{
				{"x", x},
				{"y", y},
			}
		);

		EXPECT_DOUBLE_EQ(expressor.Evaluate(), ((((x)+1))) * ((((2 + (y))))));
	} catch (ValidationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	} catch (EvaluationException& ex) {
		std::cerr << ex.GetMessage() << std::endl;
		FAIL();
	}

}