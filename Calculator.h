#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#pragma warning (disable : 4996)

#define ass assert (eq);    \
            assert (*eq)

void Require (char** eq, char symb);

double GetG (char* equation);

double GetE (char** eq);

double GetT (char** eq);

double GetD (char** eq);

double GetU (char** eq);

double GetP (char** eq);

double GetN (char** eq);

int CountSize (FILE* file);

size_t ReadTxt (char** text, const char* file_name);
