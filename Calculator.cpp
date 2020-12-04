#include "Calculator.h"

int main ()
{
	char* equation = nullptr;
	ReadTxt (&equation, "Calc/eq1.txt");

	double result = GetG (equation);
	printf ("%lf", result);

	free (equation);
	return 0;
}

void Require (char** eq, char symb)
{
	ass;

	if (**eq == symb)
	{
		*eq += 1;
		return;
	}

	printf ("Require error: %s", *eq);
	exit (1);
}

double GetG (char* equation)
{
	assert (equation);

	char* eq = equation;
	double result = GetE (&eq);
	Require (&eq, '\0');

	return result;
}

double GetE (char** eq)
{
	ass;

	double result = GetT (eq);

	while (**eq == '+' || **eq == '-')
	{
		bool operat = (**eq == '+') ? 1:0;
		*eq += 1;

		if (operat)
			result += GetT (eq);
		else
			result -= GetT (eq);
	}

	return result;
}

double GetT (char** eq)
{
	ass;

	double result = GetD (eq);

	while (**eq == '*' || **eq == '/')
	{
		bool operat = (**eq == '*') ? 1 : 0;
		*eq += 1;

		if (operat)
			result *= GetD (eq);
		else
			result /= GetD (eq);
	}

	return result;
}

double GetD (char** eq)
{
	ass;

	double result = GetP (eq);

	if (**eq == '^')
	{
		*eq += 1;
		double exponent = GetD (eq);
		result = pow (result, exponent);
	}

	return result;
}

double GetP (char** eq)
{
	ass;

	double result = 0;
	if (**eq == '(')
	{
		*eq += 1;
		result = GetE (eq);
		Require (eq, ')');
	}
	else
		result = GetN (eq);

	return result;
}

double GetN (char** eq)
{
	assert (eq);
	assert (*eq);

	double result = 0;
	int OK = 0;

	while ('0' <= **eq && **eq <= '9')
	{
		OK = 1;
		result = result * 10 + (**eq) - '0';
		*eq += 1;
	}

	if (OK && **eq == '.')
	{
		// OK - shift
		OK = 0;
		*eq += 1;
	
		while ('0' <= **eq && **eq <= '9')
		{
			OK++;
			result = result * 10 + (**eq) - '0';
			*eq += 1;
		}

		result *= pow (0.1, OK);
	}

	if (!OK)
	{
		printf ("Number error: %s", *eq);
		exit (1);
	}

	return result;
}

int CountSize (FILE* file)
{
	fseek (file, 0, SEEK_END);
	size_t num_symbols = ftell (file);
	fseek (file, 0, SEEK_SET);

	return num_symbols;
}

size_t ReadTxt (char** text, const char* file_name)
{
	assert (text);
	assert (file_name);

	FILE* file = fopen (file_name, "r");
	if (file == NULL)
	{
		printf ("[Input error] Unable to open file \"%s\"\n", file_name);
		exit (EXIT_FAILURE);
	}

	size_t num_symbols = CountSize (file);

	*text = (char*) calloc (num_symbols + 2, sizeof (**text));
	if (*text == nullptr)
	{
		printf ("[Error] Unable to allocate memory\n");
		exit (EXIT_FAILURE);
	}

	fread (*text, sizeof (**text), num_symbols, file);
	fclose (file);

	return num_symbols;
}
