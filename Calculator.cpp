#include "Calculator.h"

int main ()
{
	char* equation = nullptr;
	ReadTxt (&equation, "Calc/eq1.txt");
	char* eq = equation;
	int result = GetG (&eq);
	printf ("%d", result);

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

int GetG (char** eq)
{
	ass;

	int result = GetE (eq);
	Require (eq, '\0');

	*eq = nullptr;
	return result;
}

int GetE (char** eq)
{
	ass;

	int result = GetT (eq);

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

int GetT (char** eq)
{
	ass;

	int result = GetP (eq);

	while (**eq == '*' || **eq == '/')
	{
		bool operat = (**eq == '*') ? 1 : 0;
		*eq += 1;

		if (operat)
			result *= GetP (eq);
		else
			result /= GetP (eq);
	}

	return result;
}

int GetP (char** eq)
{
	ass;

	int result = 0;
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

int GetN (char** eq)
{
	assert (eq);
	assert (*eq);

	int result = 0;
	bool OK = 0;
	while ('0' <= **eq && **eq <= '9')
	{
		OK = 1;
		result = result * 10 + (**eq) - '0';
		*eq += 1;
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
