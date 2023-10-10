#ifndef L1_3_H
#define L1_3_H

#include <stdbool.h>

typedef enum {
  OK = 0,
  TOO_FEW_ARGS = 1,
  FLAG_ERROR,
  FLAG_UNKNOWN,
  FLAG_TOO_LONG,
  ARGC_ERROR,
  INVALID_NUMBER
} st_code;

double max(double a, double b);
double min(double a, double b);

//Prints

st_code q_fl_print(int argc, char* argv[]);
st_code m_fl_print(int argc, char* argv[]);
st_code t_fl_print(int argc, char* argv[]);

//Input control functions

st_code flags_handling(char* flag, int argc, char* argv[]);
st_code input(int argc, char* argv[]);

//Actual logic functions

bool multiplicity(long long first, long long second);
int quadratic_eq_all_solves(double ans[6][2], int ans_errs[6], double first, double second, double third, double eps);
int solve_quadr_eq(double ans[2], double a, double b, double c, double eps);
bool triangle(double a, double b, double c, double eps);
#endif