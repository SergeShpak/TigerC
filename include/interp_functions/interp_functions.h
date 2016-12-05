#ifndef INTERP_FUNCTIONS_H
#define INTERP_FUNCTIONS_H

#include "datatypes/A_stm.h"

// Count maximal number of arguments in all Print statements, that occur in
// stm.
int max_args(A_stm stm);

void interp(A_stm);

#endif
