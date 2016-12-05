#include <stdlib.h>

#include "datatypes/A_stm.h"

static A_stm *allocate(A_stm_type type, A_stm_payload *payload);

A_stm *A_CompoundStm(A_stm* stm1, A_stm* stm2) {
  A_stm_payload *payload = (A_stm_payload*) malloc(sizeof(A_stm_payload));
  if (NULL == payload) {
    return NULL;
  }
  payload->compound_stm.stm1 = stm1;
  payload->compound_stm.stm2 = stm2;
  return allocate(COMPOUND_STM, payload);
}

A_stm *A_AssignStm(char *id, A_exp *exp) {
  A_stm_payload *payload = (A_stm_payload*) malloc(sizeof(A_stm_payload));
  if (NULL == payload) {
    return NULL;
  }
  payload->assign_stm.id = id;
  payload->assign_stm.exp = exp;
  return allocate(ASSIGN_STM, payload);
}

A_stm *A_PrintStm(A_exp_list *exp_list) {
  A_stm_payload *payload = (A_stm_payload*) malloc(sizeof(A_stm_payload));
  if (NULL == payload) {
    return NULL;
  }
  payload->exp_list = exp_list;
  return allocate(PRINT_STM, payload); 
}

A_stm *allocate(A_stm_type type, A_stm_payload *payload) {
  A_stm *stm = (A_stm*) malloc(sizeof(A_stm));
  stm->type = type;
  stm->payload = payload;
  return stm;
}

void free_stm(A_stm *stm) {
  // TODO
}
