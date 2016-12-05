#ifndef A_EXP_H
#define A_EXP_H

typedef enum {
  ID_EXP,
  NUM_EXP,
  OP_EXP,
  ESEQ_EXP
} A_exp_type;

typedef struct _A_exp A_exp;

#include "A_binop.h" 
#include "A_stm.h"

typedef union _A_exp_payload {
  int num;  // NumExp
  char *id; // IdExp
  
  // Struct representing OpExp
  struct {
    A_exp *exp1;
    A_exp *exp2;
    A_binop binop;
  } op_exp;
  
  // Struct representing EseqExp
  struct {
    A_stm *stm;
    A_exp *exp;
  } eseq_exp;
} A_exp_payload; 


struct _A_exp {
  A_exp_type type;
  A_exp_payload *payload;   
};


// Constructors and destructors section

A_exp *A_NumExp(int);
A_exp *A_IdExp(char*);
A_exp *A_OpExp(A_exp*, A_binop, A_exp*);
A_exp *A_EseqExp(A_stm*, A_exp*);

void free_exp(A_exp*);

// End of constructors and destructors section

#endif
