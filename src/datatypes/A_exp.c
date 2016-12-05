#include <stdlib.h>

#include "datatypes/A_exp.h"

static A_exp *allocate(A_exp_type type, A_exp_payload *payload);

A_exp *A_NumExp(int num) {
  A_exp_payload *payload = (A_exp_payload*) malloc(sizeof(A_exp_payload));
  if (NULL == payload) {
    return NULL;
  }
  payload->num = num;
  return allocate(NUM_EXP, payload);
}

A_exp *A_IdExp(char *id) {
  A_exp_payload *payload = (A_exp_payload*) malloc(sizeof(A_exp_payload));
  if (NULL == payload) {
    return NULL;
  }
  payload->id = id;
  return allocate(ID_EXP, payload);
}

A_exp *A_OpExp(A_exp *exp1, A_binop binop, A_exp *exp2) {
  A_exp_payload *payload = (A_exp_payload*) malloc(sizeof(A_exp_payload));
  if (NULL == payload) {
    return NULL;
  }
  payload->op_exp.exp1 = exp1;
  payload->op_exp.exp2 = exp2;
  payload->op_exp.binop = binop;
  return allocate(OP_EXP, payload);
}

A_exp *A_EseqExp(A_stm *stm, A_exp *exp) {
  A_exp_payload *payload = (A_exp_payload*) malloc(sizeof(A_exp_payload));
  if (NULL == payload) {
    return NULL;
  }
  payload->eseq_exp.stm = stm;
  payload->eseq_exp.exp = exp;
  return allocate(ESEQ_EXP, payload);
}

A_exp *allocate(A_exp_type type, A_exp_payload *payload) {
  A_exp *exp = (A_exp*) malloc(sizeof(A_exp));
  if (NULL == payload) {
    return NULL;
  }
  exp->type = type;
  exp->payload = payload;
  return exp;
}

void free_exp(A_exp *exp) {
  // TODO
}
