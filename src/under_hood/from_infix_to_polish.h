#ifndef FROM_INFIX_TO_POLISH_H
#define FROM_INFIX_TO_POLISH_H

#include "../smart_calc.h"
#include "stack_elements.h"

enum operator_precedence {
  OPEN_BRACKET = 0,
  PLUS = 1,
  MINUS = 1,
  MULT = 2,
  DIV = 2,
  MOD = 2,
  POW = 3,
  UNARY_MINUS = 4,
  UNARY_PLUS = 4,
};

bool run_dijkstra_algorithm(char *str);
bool logic_of_algorithm_dijkstra(stack_operands_t *op_stack, char *buff,
                                 char *token);
bool end_of_line_processing(stack_operands_t *op_stack, char *buff);
void operators_priority(stack_operands_t *op_stack, char *token, char *buff);
int get_operator_int(char *token);
int priority_check(int operator_code);
void handle_closure_brackets(stack_operands_t *op_stack, char *buff,
                             bool *is_success);

#endif  // !FROM_INFIX_TO_POLISH_H