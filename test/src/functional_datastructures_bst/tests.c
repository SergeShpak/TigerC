#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "unity.h"

#include "functional_datastructures/bst.h"
#include "../../include/functional_datastructures/utils.h"

#define   true  ((1 == 1))
#define   false ((!true))

void setUp() {
  srand(time(NULL));
}

void test_bst_create_CreatesNode(void) {
  char *id = "a";
  struct int_wrap *payload = get_int_wrap_payload(1);
  bst *b = bst_create(id, payload);
  TEST_ASSERT_EQUAL_STRING("a", b->id);
  TEST_ASSERT_EQUAL(1, ((struct int_wrap*) b->payload)->num); 
  free(payload);
  bst_free(b);
}

void test_bst_create_PayloadPointsToOriginalStructure(void) {
  char *id = get_random_id(1, 25);
  struct int_wrap *payload = get_rand_int_wrap_payload(); 
  bst *b = bst_create(id, payload);
  TEST_ASSERT_EQUAL(payload, b->payload);
  purge_bst(b);
}

void test_bst_create_MissingChildIsNULL(void) {
  char *id = get_random_id(1, 25);
  struct int_wrap *payload = get_rand_int_wrap_payload();
  bst *b = bst_create(id, payload);
  TEST_ASSERT_NULL(b->left);
  TEST_ASSERT_NULL(b->right);
  purge_bst(b);
}

void test_bst_create_RootParentIsNULL(void) {
  char *id = get_random_id(1, 25);
  struct int_wrap *payload = get_rand_int_wrap_payload();
  bst *b = bst_create(id, payload);
  TEST_ASSERT_NULL(b->parent);
  purge_bst(b);
}

void test_bst_free_PayloadIsAccessibleAfterNodeIsFreed(void) {
  char *id = get_random_id(1, 25);
  struct int_wrap *payload = get_int_wrap_payload(1);
  bst *b = bst_create(id, payload);
  bst_free(b);
  TEST_ASSERT_NOT_NULL(payload);
  TEST_ASSERT_EQUAL(1, payload->num);
  free(payload);
}

void test_bst_insert_InsertsInCorrectOrder(void) {
  char *id1 = "a", *id2 = "b", *id3 = "c";
  bst *b1 = bst_create(id1, NULL);
  bst *b2 = bst_create(id2, NULL);
  bst *b3 = bst_create(id3, NULL);
  bst_insert(b1, b2);
  bst_insert(b3, b2);
  TEST_ASSERT_EQUAL(b1, b2->left);
  TEST_ASSERT_EQUAL(b3, b2->right);
}

void test_bst_insert_InsertsEqualAsBiggerChild(void) {
  char *id1 = "b", *id2 = "b";
  bst *b1 = bst_create(id1, NULL);
  bst *b2 = bst_create(id2, NULL);
  bst_insert(b1, b2);
  TEST_ASSERT_EQUAL(b1, b2->right);
}

void test_bst_maximum_FindsBiggestKey(void) {
  bst *tree = get_random_tree(3, 20, 5, 25);
  bst *max_node = bst_maximum(tree);
  char **tree_ids = get_ids(tree);
  char *verified_id = max_node->id;
  int i = 0;
  char *current_id = tree_ids[i];
  while (NULL != current_id) {
    int comparison_result = strcmp(verified_id, current_id);
    TEST_ASSERT_TRUE(comparison_result >= 0);
    current_id = tree_ids[i++];
  }
  free(tree_ids);
  purge_bst(tree);
}

void test_bst_maximum_ReturnsNULLIfTreeIsNULL(void) {
  bst *tree = NULL;
  bst *max_node = bst_maximum(tree);
  TEST_ASSERT_NULL(max_node);
}

void test_bst_minimum_FindsSmallestKey(void) {
  bst *tree = get_random_tree(3, 20, 5, 25);
  bst *min_node = bst_minimum(tree);
  char **tree_ids = get_ids(tree);
  char *verified_id = min_node->id;
  int i = 0;
  char *current_id = tree_ids[i];
  while (NULL != current_id) {
    int comparison_result = strcmp(verified_id, current_id);
    TEST_ASSERT_TRUE(comparison_result <= 0);
    current_id = tree_ids[i++];
  }
  free(tree_ids);
  purge_bst(tree); 
}

void test_bst_minimum_ReturnsNULLIfTreeIsNULL(void) {
  bst *tree = NULL;
  bst *min_node = bst_minimum(tree);
  TEST_ASSERT_NULL(min_node);
}

void test_bst_predecessor_ReturnsNodePredecessor(void) {
  char *ids_str = "abcdefg";
  bst *tree = get_tree(ids_str);
  sort_chars_asc(ids_str);
  struct pair **nodes_with_predecessors = get_nodes_predecessors(tree);
  int pair_index = 0;
  struct pair *curr_pair = nodes_with_predecessors[pair_index];
  while (NULL != curr_pair) {
    if (NULL == curr_pair->paired_node) {
      TEST_ASSERT_TRUE(ids_str[0] == curr_pair->node->id[0]); 
    } 
    if (NULL != curr_pair->paired_node) { 
      char *node_id = curr_pair->node->id;
      char *predecessor_id = curr_pair->paired_node->id;
      size_t node_id_index = find_in_sorted_asc(node_id[0], ids_str);
      TEST_ASSERT_TRUE(ids_str[node_id_index - 1] == predecessor_id[0]);
    } 
    pair_index++;
    curr_pair = nodes_with_predecessors[pair_index]; 
  }
  purge_bst(tree);
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_bst_create_CreatesNode);
  RUN_TEST(test_bst_create_RootParentIsNULL);
  RUN_TEST(test_bst_create_MissingChildIsNULL);
  RUN_TEST(test_bst_create_PayloadPointsToOriginalStructure);
  RUN_TEST(test_bst_free_PayloadIsAccessibleAfterNodeIsFreed);
  RUN_TEST(test_bst_insert_InsertsEqualAsBiggerChild);
  RUN_TEST(test_bst_insert_InsertsInCorrectOrder);
  return UNITY_END();
}

void tearDown(void) {
}
