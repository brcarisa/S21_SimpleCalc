#include "smart_calc.h"

void mod_to_percent(char *str, const char *old_substring,
                    const char *new_substring) {
  char *position = str;
  int old_length = strlen(old_substring);
  int new_length = strlen(new_substring);

  while ((position = strstr(position, old_substring)) != NULL) {
    memmove(position + new_length, position + old_length,
            strlen(position + old_length) + 1);
    memcpy(position, new_substring, new_length);
    position += new_length;
  }
}

int calculate_str_api_with_x(const char *str, long double x, long double *res) {
  if (str == NULL || res == NULL) {
    return 1;
  }
  *res = 0;
  char buff[MAX_LEN + 1] = {'\0'};
  bool is_error = false;
  strncpy(buff, str, MAX_LEN);
  mod_to_percent(buff, "mod", "%");
  is_error = !input_validation(buff);
  if (!is_error) {
    char *token = token_separator(buff);
    if (token != NULL) {
      unary_plus_or_minus_pars(token);
      add_end_line(token);
      replace_x_to_value(token, x);
      is_error = !run_dijkstra_algorithm(token);
      if (!is_error) {
        *res = result_calculate(token);
      }
      free(token);
      token = NULL;
    }
  }
  return is_error;
}

int calculate_str_api(const char *str, long double *res) {
  if (str == NULL || res == NULL) {
    return 1;
  }
  char buff[MAX_LEN + 1] = {'\0'};
  bool is_error = false;
  strncpy(buff, str, MAX_LEN);
  is_error = false;
  mod_to_percent(buff, "mod", "%");
  is_error = !input_validation(buff);
  if (!is_error) {
    char *token = token_separator(buff);
    if (token != NULL) {
      unary_plus_or_minus_pars(token);
      add_end_line(token);
      is_error = !run_dijkstra_algorithm(token);
      if (!is_error) {
        *res = result_calculate(token);
      }
      free(token);
      token = NULL;
    }
  }
  return is_error;
}