#include <stdlib.h>
#include <assert.h>  // TODO remove after implementing an error mechanism

#include "datatypes/A_stm.h"
#include "datatypes/A_exp.h"
#include "interp_functions/interp_functions.h"

static int count_print_stm(A_stm stm);
static int count_compound_stm(A_stm stm);
static int count_assign_stm(A_stm stm);
static int count_exp(A_exp exp);
static int count_exp_list(A_exp_list list);
// If statement is valid return a non-negative value
static int verify_statement(A_stm stm);

int max_args(A_stm stm) {
  int stm_status = verify_statement(stm);
  if (stm_status < 0) {
    return stm_status;
  }
  int max_args;
  switch(stm.type) {
    case COMPOUND_STM:
      max_args = count_compound_stm(stm);
      break;
    case ASSIGN_STM:
      max_args = count_assign_stm(stm);
      break;
    case PRINT_STM:
      max_args = count_print_stm(stm);
      break;
    default:
      assert(0);  // TODO error mechanism
      break;
  }
  return max_args;
}

int count_print_stm(A_stm stm) {
  assert(PRINT_STM == stm.type);  // TODO error mechanism
  int counter = 1;
  A_exp_list *exp_list = stm.payload->exp_list;
  do {
    counter++;
    if (PAIR_EXP_LIST == exp_list->type) {
      exp_list = exp_list->payload->pair_exp_list.exp_list;
    } 
  } while(LAST_EXP_LIST != exp_list->type);
  return counter;
}

int count_compound_stm(A_stm stm) {
  assert(COMPOUND_STM == stm.type);  // TODO error mechanism
  int stm1_counter, stm2_counter;
  stm1_counter = max_args(*(stm.payload->compound_stm.stm1));
  stm2_counter = max_args(*(stm.payload->compound_stm.stm2));
  return stm1_counter >= stm2_counter ? stm1_counter : stm2_counter;
}

int count_assign_stm(A_stm stm) {
  assert(ASSIGN_STM == stm.type);  // TODO error mechanism
  return count_exp(*(stm.payload->assign_stm.exp));
}

int count_exp(A_exp exp) {
  int max_count, exp1_counter, exp2_counter, stm_counter;
  switch(exp.type) {
    case ID_EXP:
    case NUM_EXP:
      max_count = 0;
      break;
    case OP_EXP:
      exp1_counter = count_exp(*(exp.payload->op_exp.exp1));
      exp2_counter = count_exp(*(exp.payload->op_exp.exp2));
      max_count = exp1_counter >= exp2_counter ? exp1_counter : exp2_counter; 
      break;
    case ESEQ_EXP:
      exp1_counter = count_exp(*(exp.payload->eseq_exp.exp));
      stm_counter = max_args(*(exp.payload->eseq_exp.stm));
      max_count = exp1_counter >= stm_counter ? exp1_counter : stm_counter; 
      break;
    default:
      assert(0);  // TODO error mechanism
  }
  return max_count;
}

int count_exp_list(A_exp_list exp_list) {
  int max_counter, exp_list_counter, exp_counter;
  switch(exp_list.type) {
    case LAST_EXP_LIST:
      max_counter = count_exp(*(exp_list.payload->exp));
      break;
    case PAIR_EXP_LIST:
      exp_list_counter 
                = count_exp_list(*(exp_list.payload->pair_exp_list.exp_list));
      exp_counter = count_exp(*(exp_list.payload->pair_exp_list.exp));
      max_counter 
            = exp_list_counter >= exp_counter ? exp_list_counter : exp_counter;
      break;
    default:
      assert(0);  // TODO error mechanism
      break;
  }
  return max_counter;
}

int verify_statement(A_stm stm) {
  if (NULL == stm.payload) {
    return -1;
  }
  return 0;
}
