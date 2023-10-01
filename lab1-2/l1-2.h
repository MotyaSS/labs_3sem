#ifndef L1_2_H_
#define L1_2_H_

typedef enum {
  INPUT_OK,
  INVALID_ARGC,
  INVALID_EPS
} st_code;

typedef enum {
  OK,
  LIM_NOT_OK,
} calc_st_code;

st_code input_handle(int argc, char* argv[]);

calc_st_code print_all_e(double eps);
calc_st_code e_lim(double eps, double* result);
calc_st_code e_sum(double eps, double* result);
calc_st_code e_equation(double eps, double* result);

calc_st_code print_all_pi(double eps);
calc_st_code pi_lim(double eps, double* result);
calc_st_code pi_sum(double eps, double* result);
calc_st_code pi_equation(double eps, double* result);

calc_st_code print_all_ln2(double eps);
calc_st_code ln2_lim(double eps, double* result);
calc_st_code ln2_sum(double eps, double* result);
calc_st_code ln2_equation(double eps, double* result);

calc_st_code print_all_sqrt2(double eps);
calc_st_code sqrt2_lim(double eps, double* result);
calc_st_code sqrt2_sum(double eps, double* result);
calc_st_code sqrt2_multiplication(double eps, double* result);

calc_st_code print_all_y(double eps);
calc_st_code y_lim(double eps, double* result);
calc_st_code y_sum(double eps, double* result);
calc_st_code y_equation(double eps, double* result);
#endif