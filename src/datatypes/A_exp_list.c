#include <stdlib.h>

#include "datatypes/A_exp_list.h"

static A_exp_list *allocate(A_exp_list_type type, A_exp_list_payload *payload);

A_exp_list *A_LastExpList(A_exp *exp) {
  A_exp_list_payload *payload 
                    = (A_exp_list_payload*) malloc(sizeof(A_exp_payload));
  if (NULL == payload) {
    return NULL;
  }
  payload->exp = exp;
  return allocate(LAST_EXP_LIST, payload);
}

A_exp_list *A_PairExpList(A_exp *exp, A_exp_list *exp_list) {
  A_exp_list_payload *payload 
                    = (A_exp_list_payload*) malloc(sizeof(A_exp_payload));
  if (NULL == payload) {
    return NULL;
  } 
  payload->pair_exp_list.exp = exp;
  payload->pair_exp_list.exp_list = exp_list;
  return allocate(PAIR_EXP_LIST, payload);
}

A_exp_list *allocate(A_exp_list_type type, A_exp_list_payload *payload) {
  A_exp_list *exp_list = (A_exp_list*) malloc(sizeof(A_exp_list));
  if (NULL == exp_list) {
    return NULL;
  }
  exp_list->type = type;
  exp_list->payload = payload;
  return exp_list;
}

void free_exp_list(A_exp_list *exp_list) {
  // TODO
}
