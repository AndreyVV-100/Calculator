#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#pragma warning (disable : 4996)
#pragma warning (disable : 26451)

#define ass assert (eq);    \
            assert (*eq);   \
            assert (vars)

#define Require(eq, symb) if (Require_F (eq, symb)) return NAN;

#define SkSp SkipSpaces (eq)

bool Require_F (char** eq, char symb);

double GetG (const char* file_path);

bool GetVarDefine (char** eq, double* vars);

double GetE (char** eq, double* vars);

double GetT (char** eq, double* vars);

double GetDegree (char** eq, double* vars);

double GetUnary (char** eq, double* vars);

double GetP (char** eq, double* vars);

double GetVar (char** eq, double* vars);

double GetN (char** eq, double* vars);

int CountSize (FILE* file);

size_t ReadTxt (char** text, const char* file_name);

void  SkipSpaces (char** eq);

double arcsin (double num);
double arccos (double num);
double arctg (double num);
double arcctg (double num);
double arcsh (double num);
double arcch (double num);
double arcth (double num);
double arccth (double num);
double tg (double num);
double ctg (double num);
double sh (double num);
double ch (double num);
double th (double num);
double cth (double num);
double ln (double num);