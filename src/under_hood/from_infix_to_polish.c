#include "from_infix_to_polish.h"

//в функции определения приоритета можно + и - закинуть в одно условие

void handle_closure_brackets(stack_operands_t *op_stack, char *buff,
                             bool *is_success) {
  if (op_stack != NULL && buff != NULL && is_success != NULL) {
    bool is_end = false;
    bool has_open_couple = false;
    while (!is_end && *is_success) {
      if (peek(op_stack) != NULL) {
        if (*(peek(op_stack)) != '(') {
          strcat(buff, pop(op_stack));
          strcat(buff, " ");
        } else {
          has_open_couple = true;
          pop(op_stack);
          is_end = true;
        }
      } else {
        is_end = true;
      }
    }
    if (!has_open_couple) {
      *is_success = false;
    }
  }
}

int priority_check(int operator_code) {
  int operator_priority = 0;

  if (operator_code == '(') {
    operator_priority = OPEN_BRACKET;
  } else if (operator_code == '+') {
    operator_priority = PLUS;
  } else if (operator_code == '-') {
    operator_priority = MINUS;
  } else if (operator_code == '/') {
    operator_priority = DIV;
  } else if (operator_code == '%') {
    operator_priority = MOD;
  } else if (operator_code == '*') {
    operator_priority = MULT;
  } else if (operator_code == '^') {
    operator_priority = POW;
  }
  return operator_priority;
}

int get_operator_int(char *token) {
  if (token == NULL) {
    return 0;
  }
  return (int)*token;
}

void operators_priority(stack_operands_t *op_stack, char *token, char *buff) {
  if (op_stack != NULL && token != NULL && buff != NULL) {
    int current_operator = get_operator_int(token);
    int operator_from_stack = get_operator_int(peek(op_stack));
    int current_priority = priority_check(current_operator);
    if (current_priority > priority_check(operator_from_stack) ||
        (current_priority == 3 && priority_check(operator_from_stack) == 3)) {
      push(op_stack, token);
    } else {
      bool is_priority_stack_higher_current = false;
      while (!is_priority_stack_higher_current) {
        operator_from_stack = get_operator_int(peek(op_stack));
        if (current_priority <= priority_check(operator_from_stack) &&
            operator_from_stack) {
          strcat(buff, pop(op_stack));
          strcat(buff, " ");
        } else {
          push(op_stack, token);
          is_priority_stack_higher_current = true;
        }
      }
    }
  }
}

bool end_of_line_processing(stack_operands_t *op_stack, char *buff) {
  if (op_stack == NULL || buff == NULL) {
    return false;
  }
  bool res = true;
  bool we_have_unclosed_brcacket = false;
  while (peek(op_stack) != NULL && !we_have_unclosed_brcacket) {
    if (*(peek(op_stack)) == '(') {
      we_have_unclosed_brcacket = true;
    } else {
      strcat(buff, pop(op_stack));
      strcat(buff, " ");
    }
  }
  if (we_have_unclosed_brcacket) {
      res = false;
  }
  return res;
}

bool logic_of_algorithm_dijkstra(stack_operands_t *op_stack, char *buff,
                                 char *token) {
  if (op_stack == NULL || buff == NULL || token == NULL) {
    return false;
  }
  bool is_success = true;
  if (strchr(NUMBERS_AND_DOT_AND_X, (int)*token)) {
    strcat(buff, token);
    strcat(buff, " ");
  } else if (strchr(OPERATORS, (int)*token)) {
    if (peek(op_stack) != NULL) {
      operators_priority(op_stack, token, buff);
    } else {
      push(op_stack, token);
    }
  } else if (strchr(FUNCTIONS, (int)*token) || strchr("~p", (int)*token)) {
    push(op_stack, token);
  } else if (*token == '(') {
    push(op_stack, token);
  } else if (*token == ')') {
    handle_closure_brackets(op_stack, buff, &is_success);
  } else if (*token == '<') {
    is_success = end_of_line_processing(op_stack, buff);
  }
  return is_success;
}

bool run_dijkstra_algorithm(char *str) {
  if (str == NULL) {
    return false;
  }
  bool is_success = true;
  char buff[MAX_LEN * 2 + 1] = {'\0'};
  stack_operands_t *op_stack = init_stack();
  if (op_stack != NULL) {
    char *token = strtok(str, " ");
    int allowed_len = MAX_LEN * 2;
    while (token != NULL && is_success &&
           allowed_len - (int)strlen(token) > 0) {
      is_success = logic_of_algorithm_dijkstra(op_stack, buff, token);
      token = strtok(NULL, " ");
      if (token != NULL) {
        allowed_len -= (int)strlen(token) + 1;
      }
    }
    remove_stack(op_stack);
    free(op_stack);
    op_stack = NULL;
    strncpy(str, buff, MAX_LEN * 2);
  } else {
    is_success = false;
  }
  return is_success;
}
