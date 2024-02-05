#include "valid_input.h"
//проверить условие выхода из цикла, когда встречается еще одна точка в функции
// dot_validation

bool dot_validation(char *str) {
  if (str == NULL) return false;
  bool check_dot_significant = strchr(NUMBERS, (int)*str - 2) ? true : false;
  str++;
  bool check_dot_alone = true;
  bool check_nums_only = true;
  if (!check_dot_significant && (!strchr(NUMBERS, (int)*str) || *(str) == '\0'))
    check_dot_alone = false;
  for (char *ptr = str; *ptr != '\0' && check_dot_alone && check_nums_only;
       ptr++) {
    char current_char = *ptr;
    if (!strchr(NUMBERS, (int)current_char)) {
      check_nums_only = false;
      if (current_char == '.') {
        check_dot_alone = false;
      }
    }
  }
  return check_dot_alone;
}

int symbols_validation(char *str) {
  if (str == NULL) return 0;
  int valid_symbols = 0;
  char string_for_check[6] = {'\0'};
  strncat(string_for_check, str, 5);
  if (*str == '(') {
    valid_symbols = 1;
  } else if (*str == ')') {
    if (*(str - 1) != '(') {
      valid_symbols = 1;
    }
  } else if (*str == 'c') {
    if (strstr(string_for_check, "cos(")) valid_symbols = 4;
  } else if (*str == 'a') {
    if (strstr(string_for_check, "acos(") ||
        strstr(string_for_check, "asin(") ||
        strstr(string_for_check, "atan(")) {
      valid_symbols = 5;
    }
  } else if (*str == '.') {
    if (dot_validation(str)) {
      valid_symbols = 1;
    }
  } else if (*str == 's') {
    if (strstr(string_for_check, "sin(")) {
      valid_symbols = 4;
    }
    if (strstr(string_for_check, "sqrt(")) {
      valid_symbols = 5;
    }
  } else if (*str == 't') {
    if (strstr(string_for_check, "tan(")) {
      valid_symbols = 4;
    }
  } else if (*str == 'm') {
    if (strstr(string_for_check, "mod(")) {
      valid_symbols = 4;
    }
  } else if (*str == 'l') {
    if (strstr(string_for_check, "ln(")) {
      valid_symbols = 3;
    }
    if (strstr(string_for_check, "log(")) {
      valid_symbols = 4;
    }
  } else if (strchr(OPERATORS, (int)*str)) {
    if (strchr(OPERANDS, (int)*(str + 1)) && (int)*(str + 1) != '\0') {
      valid_symbols = 1;
    }
  }
  return valid_symbols;
}

bool input_validation(char *str) {
  if (str == NULL) {
    return false;
  } else if (*str == ')') {
    return false;
  }
  bool is_valid = true;

  for (char *ptr = str; *ptr != '\0' && is_valid; ptr++) {
    char current_char = *ptr;
    if (strchr(PERMITTED_SYMBOLS, (int)current_char) != NULL) {
      if (strchr(NUMBERS, (int)current_char) || current_char == 'x') {
        //число в порядке
      } else {
        int step = symbols_validation(ptr);
        if (step) {
          ptr += step - 1;
        } else {
          is_valid = false;
        }
      }
    } else {
      is_valid = false;
    }
  }
  return is_valid;
}