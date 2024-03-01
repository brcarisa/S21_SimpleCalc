#include "divide_tokens.h"

void replace_x_to_value(char *str, long double value) {
  if (str != NULL) {
    int len_str_before = strlen(str);
    int how_much_left = MAX_LEN - len_str_before;
    char ins_value[MAX_LEN + 1] = {'\0'};
    memset(ins_value, '\0', MAX_LEN + 1);
    ins_value[0] = '(';
    ins_value[1] = ' ';
    snprintf(ins_value + 2, MAX_LEN - 4, "%Lf", value);
    if (ins_value[2] == '-') {
      ins_value[2] = '~';
      memmove(ins_value + 4, ins_value + 3, strlen(ins_value));
      ins_value[3] = ' ';
    }
    ins_value[strlen(ins_value)] = ' ';
    ins_value[strlen(ins_value)] = ')';
    int value_len = strlen(ins_value);
    for (char *ptr = str; *ptr != '\0' && (how_much_left - value_len) > 0;
         ptr++) {
      if (*ptr == 'x') {
        if (how_much_left) {
          memmove(ptr + value_len - 1, ptr, strlen(ptr));
          memmove(ptr, ins_value, value_len);
          how_much_left -= value_len;
        }
      }
    }
  }
}

void add_end_line(char *str) {
  if (str != NULL) {
    *(str + strlen(str)) = '<';
    *(str + strlen(str) + 1) = '\0';
  }
}

void unary_plus_or_minus_pars(char *str) {
  if (*str == '+') {
    *str = 'p';
  } else if (*str == '-') {
    *str = '~';
  }
  char previous_lexeme[MAX_LEN + 1] = {'\0'};
  memset(previous_lexeme, '\0', MAX_LEN + 1);
  int curr_word = 0;
  for (char *ptr = str; *ptr != '\0'; ptr++) {
    if (curr_word) {
      if (*ptr == '+' || *ptr == '-') {
        if (strchr(previous_lexeme, '(')) {
          if (*ptr == '+')
            *ptr = 'p';
          else if (*ptr == '-')
            *ptr = '~';
        }
      }
    }
    for (char *cpylex = ptr; *cpylex != ' '; cpylex++) {
      strncpy(previous_lexeme, cpylex, 1);
    }
    while (*ptr != ' ') {
      ptr++;
    }
    curr_word++;
  }
}

int func_processing(char *str) {
  if (str == NULL) return 0;
  int size_of_func = 0;
  char curr_str[6] = {'\0'};
  strncat(curr_str, str, 5);
  if (*str == 'a') {
    if (strstr(curr_str, "asin") || strstr(curr_str, "acos") ||
        strstr(curr_str, "atan")) {
      size_of_func = 4;
    }
  } else if (*str == 'c') {
    if (strstr(curr_str, "cos")) {
      size_of_func = 3;
    }
  } else if (*str == 's') {
    if (strstr(curr_str, "sin")) {
      size_of_func = 3;
    } else if (strstr(curr_str, "sqrt")) {
      size_of_func = 4;
    }
  } else if (*str == 't') {
    if (strstr(curr_str, "tan")) {
      size_of_func = 3;
    }
  } else if (*str == 'l') {
    if (strstr(curr_str, "ln")) {
      size_of_func = 2;
    } else if (strstr(curr_str, "log")) {
      size_of_func = 3;
    }
  }
  return size_of_func;
}

char *token_separator(char *str) {
  if (str == NULL) {
    return NULL;
  }
  char *separeted_tokens = (char *)calloc(MAX_LEN * 2 + 1, sizeof(char));
  if (separeted_tokens != NULL) {
    memset(separeted_tokens, '\0', MAX_LEN * 2 + 1);
  }
  for (char *ptr = str; *ptr != '\0'; ptr++) {
    char current_char = *ptr;
    char current_token[MAX_LEN] = {'\0'};
    int step = 0;
    if (current_char == '.' || strchr(NUMBERS, (int)current_char)) {
      step = strspn(ptr, NUMBERS_AND_DOT) - 1;
      strncpy(current_token, ptr, step + 1);
    } else if (strchr(OPERATORS, (int)current_char) ||
               strchr(BRACKETS, (int)current_char) || current_char == 'x') {
      strncpy(current_token, ptr, 1);
    } else if (strchr(FUNCTIONS, (int)current_char)) {
      step = func_processing(ptr) - 1;
      strncpy(current_token, ptr, step + 1);
    }
    ptr += step;
    strcat(separeted_tokens, current_token);
    strcat(separeted_tokens, " ");
  }
  return separeted_tokens;
}
