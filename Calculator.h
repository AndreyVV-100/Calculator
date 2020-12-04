#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#pragma warning (disable : 4996)

#define ass assert (eq);    \
            assert (*eq);   \
            assert (vars)

void Require (char** eq, char symb);

/* ToDo: Dictionary*/

double GetG (char* equation);

void   GetM (char** eq, double* vars);

double GetE (char** eq, double* vars);

double GetT (char** eq, double* vars);

double GetD (char** eq, double* vars);

double GetU (char** eq, double* vars);

double GetP (char** eq, double* vars);

double GetV (char** eq, double* vars);

double GetN (char** eq, double* vars);

int CountSize (FILE* file);

size_t ReadTxt (char** text, const char* file_name);
