#ifndef STACK_ELEMENTS_H
#define STACK_ELEMENTS_H

typedef struct stack_struct {
  int lenght;
  char **tokens;
} stack_operands_t;

typedef struct ld_stack_struct {
  int lenght;
  long double *values;
} ld_stack_t;

#include "../smart_calc.h"

// STACK_OPERANDS
stack_operands_t *init_stack();
bool is_stack_empty(stack_operands_t *stack);
bool is_stack_full(stack_operands_t *stack);
void push(stack_operands_t *stack, char *token);
char *peek(stack_operands_t *stack);
char *pop(stack_operands_t *stack);
void remove_stack(stack_operands_t *stack);

// STACK_VALUES
ld_stack_t *init_ld_stack();
bool is_ld_stack_empty(ld_stack_t *stack);
bool is_ld_stack_full(ld_stack_t *stack);
void push_ld(ld_stack_t *stack, long double value);
long double peek_ld(ld_stack_t *stack);
long double pop_ld(ld_stack_t *stack);
void remove_ld_stack(ld_stack_t *stack);

#endif  // !STACK_ELEMENTS_H