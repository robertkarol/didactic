#include <fstream>
#include <cstring>
#define LMAX 1001

using namespace std;

ifstream fin("bool.in");
ofstream cout("bool.out");

char s[LMAX];
bool values[27];

int evaluate(char*& expr);
int operand(char*& expr);
int value(char*& expr);
void prelucrare(char*& prel);
int OR(char*& expr);
int AND(char*& expr);
int NOT(char*& expr);


int main()
{
    int n;
    char change;
	fin.get(s, LMAX - 1);
	char* prel = s;
	prelucrare(prel);
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

void prelucrare(char*& prel)
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

int evaluate(char *& expr)
{
	return OR(expr);
}

int operand(char *& expr)
{
    int result;
    if(expr[0] == '(')
    {
        result = evaluate(++expr);
        ++expr;
    }
    else result = value(expr);
    return result;
}

int value(char *& expr)
{
    char c = expr[0];
    expr++;
    if(isdigit(c))
        return c - '0';
    else
        return values[c - 'A'];
}

int OR(char *& expr)
{
    int result = AND(expr);
    while(expr[0] == '|')
    {
        result |= AND(++expr);
    }
	return result;
}

int AND(char *& expr)
{
	int result = NOT(expr);
    while(expr[0] == '&')
    {
        result &= NOT(++expr);
    }
	return result;
}

int NOT(char *& expr)
{
    int result;
	if(expr[0] == '!')
        result = !NOT(++expr);
    else
        result = operand(expr);
    return result;
}
