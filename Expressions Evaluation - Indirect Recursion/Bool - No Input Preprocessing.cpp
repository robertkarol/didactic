#include <iostream>	
#include <fstream>	
#define LMAX 1001

// Solution 1 of logical expressions evaluation: without input preprocessing

using namespace std;

ifstream fin("bool.in");
ofstream fout("bool.out");

// Declaring headers of our functions
int evaluate(char*& expr);
int operand(char*& expr);
int value(char*& expr);
int NOT(char*& expr);
int AND(char*& expr);
int OR(char*& expr);

char s[LMAX];
bool values[28];

// Escape spaces funtion we'll repeatedly call, so we'll make it inline to optimize calls
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

// Priority level 3: getting out operands from priority level 2
int OR(char*& expr)
{
	auto result = AND(expr);

	escape_space(expr);
	while (expr[0] == 'O' && expr[1] == 'R')
	{
		expr += 2; // escape the operator
		result |= AND(expr);
		escape_space(expr);
	}

	return result;
}

// Priority level 2: getting out operands from priority level 1
int AND(char*& expr)
{
	auto result = NOT(expr);

	escape_space(expr);
	while (expr[0] == 'A' && expr[1] == 'N' && expr[2] == 'D')
	{
		expr += 3; // escape the operator
		result &= NOT(expr);
		escape_space(expr);
	}

	return result;
}

// Priority level 1: top level, so we'll get operands from our operands function
int NOT(char*& expr)
{
	bool result = 0;

	escape_space(expr);
	if (expr[0] == 'N' && expr[1] == 'O' && expr[2] == 'T')
	{
		expr += 3; // escape the operator
		result = !NOT(expr);
		escape_space(expr);
	}
	else result = operand(expr);

	return result;
}

// We can either find a sub-expression or an actual operand, so we'll make the decision here
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

// Extract the actual operand
int value(char*& expr)
{
	char* initial = expr;
	while (isalpha(expr[0]))
	{
		expr++;
	}
	auto len = expr - initial; // len is 1 for variables (e.g. A), 4 for TRUE, 5 for FALSE
	return len == 1 ? values[*initial - 'A'] : (len == 4);
}
