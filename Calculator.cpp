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
	assert (eq);
	assert (*eq);

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
	double vars['z' - 'a' + 1] = {};

	for (size_t i_var = 0; i_var <= 'z' - 'a'; i_var++)
		vars[i_var] = NAN;

	while (eq[1] == '=')
		GetM (&eq, vars);

	double result = GetE (&eq, vars);
	Require (&eq, '\0');

	return result;
}

void   GetM (char** eq, double* vars)
{
	ass;
	
	if (!islower (**eq))
	{
		printf ("Variable error: %s", *eq);
		exit (1);
	}
	
	size_t position = **eq - 'a';
	*eq += 1;
	Require (eq, '=');

	vars[position] = GetE (eq, vars);
	Require (eq, '\n');
	return;
}

double GetE (char** eq, double* vars)
{
	ass;

	double result = GetT (eq, vars);

	while (**eq == '+' || **eq == '-')
	{
		bool operat = (**eq == '+') ? 1:0;
		*eq += 1;

		if (operat)
			result += GetT (eq, vars);
		else
			result -= GetT (eq, vars);
	}

	return result;
}

double GetT (char** eq, double* vars)
{
	ass;

	double result = GetD (eq, vars);

	while (**eq == '*' || **eq == '/')
	{
		bool operat = (**eq == '*') ? 1 : 0;
		*eq += 1;

		if (operat)
			result *= GetD (eq, vars);
		else
			result /= GetD (eq, vars);
	}

	return result;
}

double GetD (char** eq, double* vars)
{
	ass;

	double result = GetU (eq, vars);

	if (**eq == '^')
	{
		*eq += 1;
		double exponent = GetD (eq, vars);
		result = pow (result, exponent);
	}

	return result;
}

double GetU (char** eq, double* vars)
{
	ass;

	if (islower (**eq))
	{
		switch (**eq)
		{
			case 'c':
			{
				if (strncmp ("cos", *eq, 3) == 0)
				{
					*eq += 3;
					return cos (GetP (eq, vars));
				}
				break;
			}

			case 's':
			{
				if (strncmp ("sin", *eq, 3) == 0)
				{
					*eq += 3;
					return sin (GetP (eq, vars));
				}
				break;
			}
		}
	}

	return GetP (eq, vars);
}

double GetP (char** eq, double* vars)
{
	ass;

	double result = 0;
	if (**eq == '(')
	{
		*eq += 1;
		result = GetE (eq, vars);
		Require (eq, ')');
	}
	else if (islower (**eq))
		result = GetV (eq, vars);
	else
		result = GetN (eq, vars);

	return result;
}

double GetV (char** eq, double* vars)
{
	ass;
	assert (islower (**eq));
	
	double result = vars[**eq - 'a'];
	*eq += 1;
	return result;
}

double GetN (char** eq, double* vars)
{
	assert (eq);
	assert (*eq);

	double result = 0;
	int OK = 0;

	while (isdigit (**eq))
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
	
		while (isdigit (**eq))
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
