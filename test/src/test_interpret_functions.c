#include <unity.h>

#include "datatypes/A_stm.h"
#include "interp_functions/interp_functions.h"

void test_max_args_ReturnsCorrectNumber(void) {
  A_stm *stm = A_CompoundStm(A_AssignStm("a",
                A_OpExp(A_NumExp(5), A_PLUS, A_NumExp(3))
                ),
                A_CompoundStm(
                  A_AssignStm("b", 
                    A_EseqExp(
                      A_PrintStm(
                        A_PairExpList(
                          A_IdExp("a"), 
                          A_LastExpList(
                            A_OpExp(
                              A_IdExp("a"), A_MINUS, A_NumExp(1)
                            )
                          )
                        )
                      ),
                      A_OpExp(A_NumExp(10), A_TIMES, A_IdExp("a"))
                    )
                  ),
                  A_PrintStm(
                    A_LastExpList(A_IdExp("b"))
                  )
                )
                );
  int max_args_count = max_args(*stm);  
  TEST_ASSERT_EQUAL(2, max_args_count);
}

void test_max_args_ReturnsNegativeIfPayloadIsNull(void) {
  A_stm *stm = A_AssignStm("B", A_NumExp(12));
  stm->payload = NULL;
  int max_args_count = max_args(*stm);
  TEST_ASSERT_TRUE(max_args_count < 0);
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_max_args_ReturnsCorrectNumber);
  RUN_TEST(test_max_args_ReturnsNegativeIfPayloadIsNull);
  return UNITY_END();
}
