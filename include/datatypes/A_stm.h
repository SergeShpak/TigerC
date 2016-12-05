#ifndef A_STM_H
#define A_STM_H

typedef enum {
  COMPOUND_STM,
  ASSIGN_STM,
  PRINT_STM 
} A_stm_type;

typedef struct _A_stm A_stm;

#include "A_exp.h"
#include "A_exp_list.h"

typedef union _A_stm_payload { 
  A_exp_list *exp_list;   // PrintStm
  
  // Struct representing CompoundStm
  struct {
    A_stm *stm1;
    A_stm *stm2; 
  } compound_stm;
  
  // Struct representing AssignStm
  struct {
    char *id;
    A_exp *exp; 
  } assign_stm;
} A_stm_payload;

struct _A_stm {
  A_stm_type type;
  A_stm_payload *payload;
};


// Constructors and destructors section

A_stm *A_CompoundStm(A_stm*, A_stm*);
A_stm *A_AssignStm(char*, A_exp*);
A_stm *A_PrintStm(A_exp_list*);

void free_stm(A_stm*);

// End of constructors and destructors section

#endif
