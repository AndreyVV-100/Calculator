#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#pragma warning (disable : 4996)

#define ass assert (eq);    \
            assert (*eq)

void Require (char** eq, char symb);

int GetG (char** eq);

int GetE (char** eq);

int GetT (char** eq);

int GetP (char** eq);

int GetN (char** eq);

int CountSize (FILE* file);

size_t ReadTxt (char** text, const char* file_name);
