#include <iostream>	
#include <fstream>	
#define LMAX 1001

using namespace std;

ifstream fin("bool.in");
ofstream fout("bool.out");

int evaluate(char*& expr);
int operand(char*& expr);
int value(char*& expr);
int NOT(char*& expr);
int AND(char*& expr);
int OR(char*& expr);

char s[LMAX];
bool values[28];

inline void escape_space(char*& expr)
{
	while (expr[0] == ' ') expr++;
}

int main()
{
	char* expr, change;
	int n;

	fin.get(s, LMAX - 1);

	fin >> n;
	for (int i = 0; i < n; i++)
	{
		fin >> change;
		expr = s;
		values[change - 'A'] = !values[change - 'A'];
		fout << evaluate(expr);
	}

	return 0;
}

int evaluate(char*& expr)
{
	return OR(expr);
}

int OR(char*& expr)
{
	auto result = AND(expr);

	escape_space(expr);
	while (expr[0] == 'O' && expr[1] == 'R')
	{
		expr += 2;
		result |= AND(expr);
		escape_space(expr);
	}

	return result;
}

int AND(char*& expr)
{
	auto result = NOT(expr);

	escape_space(expr);
	while (expr[0] == 'A' && expr[1] == 'N' && expr[2] == 'D')
	{
		expr += 3;
		result &= NOT(expr);
		escape_space(expr);
	}

	return result;
}

int NOT(char*& expr)
{
	bool result = 0;

	escape_space(expr);
	if (expr[0] == 'N' && expr[1] == 'O' && expr[2] == 'T')
	{
		expr += 3;
		result = !NOT(expr);
		escape_space(expr);
	}
	else result = operand(expr);

	return result;
}

int operand(char*& expr)
{
	escape_space(expr);
	if (expr[0] == '(')
	{
		auto result = evaluate(++expr);
		expr++;
		escape_space(expr);
		return result;
	}
	else
	{
		return value(expr);
		escape_space(expr);
	}
}

int value(char*& expr)
{
	char* initial = expr;
	while (isalpha(expr[0]))
	{
		expr++;
	}
	auto len = expr - initial;
	return len == 1 ? values[*initial - 'A'] : (len == 4);
}