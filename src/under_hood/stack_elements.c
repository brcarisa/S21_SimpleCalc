#include "stack_elements.h"

// STACK_OPERANDS

stack_operands_t *init_stack() {
  bool is_error = false;
  stack_operands_t *stack =
      (stack_operands_t *)calloc(1, sizeof(stack_operands_t));
  if (stack == NULL) {
    is_error = true;
  } else {
    stack->lenght = 0;
    stack->tokens = (char **)calloc(MAX_LEN, sizeof(char **));
    if (stack->tokens == NULL) {
      is_error = true;
    }
  }
  return is_error == 0 ? stack : NULL;
}

bool is_stack_empty(stack_operands_t *stack) {
  if (stack == NULL) {
    return false;
  }
  return stack->lenght == 0;
}

bool is_stack_full(stack_operands_t *stack) {
  if (stack == NULL) {
    return false;
  }
  return stack->lenght == MAX_LEN;
}

void push(stack_operands_t *stack, char *token) {
  if (stack != NULL && !is_stack_full(stack) && token != NULL) {
    stack->tokens[stack->lenght] = token;
    stack->lenght++;
  }
}

char *peek(stack_operands_t *stack) {
  if (stack == NULL || is_stack_empty(stack)) {
    return NULL;
  }
  return stack->tokens[stack->lenght - 1];
}

char *pop(stack_operands_t *stack) {
  if (stack == NULL || is_stack_empty(stack)) {
    return NULL;
  }
  stack->lenght--;
  return stack->tokens[stack->lenght];
}

void remove_stack(stack_operands_t *stack) {
  if (stack != NULL && stack->tokens != NULL) {
    free(stack->tokens);
    stack->tokens = NULL;
    stack->lenght = 0;
  }
}

// STACK_VALUES

ld_stack_t *init_ld_stack() {
  bool is_error = false;
  ld_stack_t *new_stack = (ld_stack_t *)calloc(1, sizeof(ld_stack_t));
  if (new_stack == NULL) {
    is_error = true;
  } else {
    new_stack->lenght = 0;
    new_stack->values = (long double *)calloc(MAX_LEN, sizeof(long double *));
    if (new_stack->values == NULL) {
      is_error = true;
    }
  }
  return is_error == false ? new_stack : NULL;
}

bool is_ld_stack_empty(ld_stack_t *stack) {
  if (stack == NULL) {
    return false;
  }

  return stack->lenght == 0;
}

bool is_ld_stack_full(ld_stack_t *stack) {
  if (stack == NULL) {
    return false;
  }
  return stack->lenght == MAX_LEN;
}

void push_ld(ld_stack_t *stack, long double value) {
  if (stack != NULL && !is_ld_stack_full(stack)) {
    stack->values[stack->lenght] = value;
    stack->lenght++;
  }
}

long double peek_ld(ld_stack_t *stack) {
  if (stack == NULL || is_ld_stack_empty(stack)) {
    return 0;
  }
  return stack->values[stack->lenght - 1];
}

long double pop_ld(ld_stack_t *stack) {
  if (stack == NULL || is_ld_stack_empty(stack)) {
    return 0;
  }
  stack->lenght--;
  return stack->values[stack->lenght];
}

void remove_ld_stack(ld_stack_t *stack) {
  if (stack != NULL && !is_ld_stack_empty(stack)) {
    free(stack->values);
    stack->values = NULL;
    stack->lenght = 0;
  }
}