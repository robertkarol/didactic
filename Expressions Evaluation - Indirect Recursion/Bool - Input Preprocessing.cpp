#include <fstream>
#include <cstring>
#define LMAX 1001

using namespace std;

// Solution 2 of logical expressions evaluation: with input preprocessing

ifstream fin("bool.in");
ofstream cout("bool.out");

char s[LMAX];
bool values[27];

// headers of out functions
int evaluate(char*& expr);
int operand(char*& expr);
int value(char*& expr);
void preprocessing(char*& prel);
int OR(char*& expr);
int AND(char*& expr);
int NOT(char*& expr);


int main()
{
    int n;
    char change;
	fin.get(s, LMAX - 1);
	char* prel = s;
	preprocessing(prel);
	fin >> n;
	while(n)
	{
		fin >> change;
		char* expr = s;
		values[change - 'A'] = !values[change - 'A'];
		cout<<evaluate(expr);
		n--;
	}

    return 0;
}

/* 
Preprocessing means:
- removing all the spaces
- AND becomes &
- OR becomes |
- NOT becomes !
- TRUE becomes 1
- FALSE becomes 0
*/
void preprocessing(char*& prel)
{
	while (prel[0])
	{
		if (prel[0] == ' ') strcpy(prel, prel + 1);
		else if (prel[0] == 'T' && prel[1] == 'R')
		{
			strcpy(prel, prel + 3);
			prel[0] = '1';
			prel++;
		}
		else if (prel[0] == 'F' && prel[1] == 'A')
		{
			strcpy(prel, prel + 4);
			prel[0] = '0';
			prel++;
		}
		else if(prel[0] == 'A' && prel[1] == 'N')
        {
            strcpy(prel, prel + 2);
            prel[0]='&';
            prel++;
        }
        else if(prel[0] == 'O' && prel[1] == 'R')
        {
            strcpy(prel, prel + 1);
            prel[0]='|';
            prel++;
        }
        else if(prel[0] == 'N' && prel[1] == 'O')
        {
            strcpy(prel, prel + 2);
            prel[0]='!';
            prel++;
        }
		else prel++;
	}
}

// Just calling lowest priority function
int evaluate(char *& expr)
{
	return OR(expr);
}

// Priority level 3: we'll get out operands by calling the priority level 2 function
int OR(char *& expr)
{
    int result = AND(expr);
    while(expr[0] == '|')
    {
        result |= AND(++expr);
    }
	return result;
}

// Priority level 2: we'll get out operands by calling the priority level 1 function
int AND(char *& expr)
{
	int result = NOT(expr);
    while(expr[0] == '&')
    {
        result &= NOT(++expr);
    }
	return result;
}

// Priority level 1: we'll get out operands directly or proceed recursion if multiple negations are found (e.g. NOT NOT A)
int NOT(char *& expr)
{
    int result;
	if(expr[0] == '!')
        result = !NOT(++expr);
    else
        result = operand(expr);
    return result;
}

// Making the decision whether we need to evaluate a sub-expression or extract the value of the operand
int operand(char *& expr)
{
    int result;
    if(expr[0] == '(')
    {
        result = evaluate(++expr); //escape (
        ++expr; // escape )
    }
    else result = value(expr);
    return result;
}

// Value function gets way more simple: we can find one of {0, 1, A,...,Z}
int value(char *& expr)
{
    char c = expr[0];
    expr++; // escape the operand
    if(isdigit(c))
        return c - '0';
    else
        return values[c - 'A'];
}
