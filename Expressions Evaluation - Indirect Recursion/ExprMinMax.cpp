#include <iostream>	
#include <fstream>	
#include <algorithm>	
#define LMAX 100001

using namespace std;

ifstream fin("emm.in");
ofstream fout("emm.out");

int evaluate(char*& expr);
int operand(char*& expr);
int value(char*& expr);
int MIN_MAX(char*& expr);

char expression[LMAX];

int main()
{
	fin >> expression;
	char* expr;
	expr = expression;
	fout << evaluate(expr);
	return 0;
}

int evaluate(char*& expr)
{
	return MIN_MAX(expr);
}

int MIN_MAX(char*& expr)
{
	auto result = operand(expr);

	while (expr[0] == 'm' || expr[0] == 'M')
	{
		switch (expr[0])
		{
		case 'm':
			result = min(result, operand(++expr));
			break;
		case 'M':
			result = max(result, operand(++expr));
			break;
		default:
			break;
		}
	}

	return result;
}

int operand(char*& expr)
{
	if (expr[0] == '(')
	{
		auto result = evaluate(++expr);
		expr++;
		return result;
	}
	else
	{
		return value(expr);
	}
}
int value(char*& expr)
{
	int nr = 0;

	while (isdigit(expr[0]))
	{
		nr = nr * 10 + (expr[0] - '0');
		expr++;
	}

	return nr;
}