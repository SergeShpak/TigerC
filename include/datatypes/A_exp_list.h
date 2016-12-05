#ifndef A_EXP_LIST_H
#define A_EXP_LIST_H

typedef enum {
  PAIR_EXP_LIST,
  LAST_EXP_LIST
} A_exp_list_type;

typedef struct _A_exp_list A_exp_list;

#include "A_exp.h" 

typedef union _A_exp_list_payload {
  A_exp *exp;   // LastExpList

  // Struct representing PairExpList
  struct {
    A_exp *exp;
    A_exp_list *exp_list;  
  } pair_exp_list;
} A_exp_list_payload;

struct _A_exp_list {
  A_exp_list_type type;
  A_exp_list_payload *payload;
};


// Constructors and destructors section

A_exp_list *A_LastExpList(A_exp*);
A_exp_list *A_PairExpList(A_exp*, A_exp_list*);

void free_exp_list(A_exp_list*);

// End of constructors and destructors section

#endif
