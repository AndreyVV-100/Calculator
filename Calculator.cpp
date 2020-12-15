#include "Calculator.h"

int main ()
{
	GetG ("Calc/eq2.txt");
	return 0;
}

bool Require_F (char** eq, char symb)
{
	assert (eq);
	assert (*eq);

	if (**eq == symb)
	{
		*eq += 1;
		return 0;
	}

	printf ("Require \'%c\' (%d) error: %s", symb, symb, *eq);
	return 1;
}

double GetG (const char* file_path)
{
	char* equation = nullptr;
	ReadTxt (&equation, file_path);
	if (!equation)
		return NAN;
	
	char* eq = equation;
	double vars['z' - 'a' + 1] = {};

	for (size_t i_var = 0; i_var <= 'z' - 'a'; i_var++)
		vars[i_var] = NAN;

	while (strchr (eq, '='))
		if (GetVarDefine (&eq, vars))
			return NAN;

	double result = GetE (&eq, vars);
	Require (&eq, '\0');

	printf ("\n" "Result = %lf", result);
	free (equation);
	return result;
}

bool GetVarDefine (char** eq, double* vars)
{
	ass;
	
	if (!islower (**eq))
	{
		printf ("Variable error: %s", *eq);
		return 1;
	}

	SkSp;
	size_t position = **eq - 'a';
	*eq += 1;

	SkSp;
	Require_F (eq, '=');
	SkSp;

	vars[position] = GetN (eq, vars);
	if (isnan (vars[position]))
		return 1;

	SkSp;
	Require_F (eq, '\n');
	return 0;
}

double GetE (char** eq, double* vars)
{
	ass;

	double result = GetT (eq, vars);
	SkSp;

	while ((**eq == '+' || **eq == '-') && !isnan (result))
	{
		bool operat = (**eq == '+') ? 1:0;
		*eq += 1;

		if (operat)
			result += GetT (eq, vars);
		else
			result -= GetT (eq, vars);
		SkSp;
	}

	return result;
}

double GetT (char** eq, double* vars)
{
	ass;

	double result = GetDegree (eq, vars);
	SkSp;

	while ((**eq == '*' || **eq == '/') && !isnan (result))
	{
		bool operat = (**eq == '*') ? 1 : 0;
		*eq += 1;

		if (operat)
			result *= GetDegree (eq, vars);
		else
			result /= GetDegree (eq, vars);
		SkSp;
	}

	return result;
}

double GetDegree (char** eq, double* vars)
{
	ass;

	double result = GetUnary (eq, vars);
	SkSp;

	if (**eq == '^' && !isnan (result))
	{
		*eq += 1;
		double exponent = GetDegree (eq, vars);
		result = pow (result, exponent);
	}

	return result;
}

double GetUnary (char** eq, double* vars)
{
	ass;
	SkSp;

	if (islower (**eq))
	{
		switch (**eq)
		{
			#define check_and_get(cmd, len) if (strncmp (#cmd, *eq, len) == 0)	\
											{									\
												*eq += len;						\
												return cmd (GetP (eq, vars));	\
											}
			#include "FunctionsList.h"
			#undef check_and_get
		}
	}

	return GetP (eq, vars);
}

double GetP (char** eq, double* vars)
{
	ass;
	SkSp;

	double result = 0;
	if (**eq == '(')
	{
		*eq += 1;
		result = GetE (eq, vars);
		Require (eq, ')');
	}
	else if (islower (**eq))
		result = GetVar (eq, vars);
	else
		result = GetN (eq, vars);

	return result;
}

double GetVar (char** eq, double* vars)
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
		return NAN;
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
	if (file == nullptr)
	{
		printf ("[Input error] Unable to open file \"%s\"\n", file_name);
		return 0;
	}

	size_t num_symbols = CountSize (file);

	*text = (char*)calloc (num_symbols + 2, sizeof (**text));

	if (*text == nullptr)
	{
		printf ("[Error] Unable to allocate memory\n");
		return 0;
	}

	fread (*text, sizeof (**text), num_symbols, file);
	fclose (file);

	(*text)[num_symbols] = '\0';

	return num_symbols;
}

void  SkipSpaces (char** eq)
{
	assert (eq);
	assert (*eq);

	while (**eq == ' ' || **eq == '\t' || **eq == '\r')
		*eq += 1;

	return;
}

double arcsin(double num){ return NAN; }
double arccos (double num) { return NAN; }
double arctg (double num) { return NAN; }
double arcctg (double num) { return NAN; }
double arcsh (double num) { return NAN; }
double arcch (double num) { return NAN; }
double arcth (double num) { return NAN; }
double arccth (double num) { return NAN; }
double tg (double num) { return NAN; }
double ctg (double num) { return NAN; }
double sh (double num) { return NAN; }
double ch (double num) { return NAN; }
double th (double num) { return NAN; }
double cth (double num) { return NAN; }
double ln (double num) { return NAN; }
