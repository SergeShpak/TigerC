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

void test_bst_node_create_CreatesNode(void) {
  char *id = "a";
  struct int_wrap *payload = get_int_wrap_payload(1);
  node *b = bst_node_create(id, payload);
  TEST_ASSERT_EQUAL_STRING("a", b->id);
  TEST_ASSERT_EQUAL(1, ((struct int_wrap*) b->payload)->num); 
  free(payload);
  bst_node_free(b);
}

void test_bst_create_PayloadPointsToOriginalStructure(void) {
  char *id = get_random_id(1, 25);
  struct int_wrap *payload = get_rand_int_wrap_payload(); 
  node *b = bst_node_create(id, payload);
  TEST_ASSERT_EQUAL(payload, b->payload);
  purge_bst(b);
}

void test_bst_create_MissingChildIsNULL(void) {
  char *id = get_random_id(1, 25);
  struct int_wrap *payload = get_rand_int_wrap_payload();
  node *b = bst_node_create(id, payload);
  TEST_ASSERT_NULL(b->left);
  TEST_ASSERT_NULL(b->right);
  purge_bst(b);
}

void test_bst_create_RootParentIsNULL(void) {
  char *id = get_random_id(1, 25);
  struct int_wrap *payload = get_rand_int_wrap_payload();
  node *b = bst_node_create(id, payload);
  TEST_ASSERT_NULL(b->parent);
  purge_bst(b);
}

void test_bst_free_PayloadIsAccessibleAfterNodeIsFreed(void) {
  char *id = get_random_id(1, 25);
  struct int_wrap *payload = get_int_wrap_payload(1);
  node *b = bst_node_create(id, payload);
  bst_node_free(b);
  TEST_ASSERT_NOT_NULL(payload);
  TEST_ASSERT_EQUAL(1, payload->num);
  free(payload);
}

void test_bst_insert_InsertsInCorrectOrder(void) {
  char *id1 = "a", *id2 = "b", *id3 = "c";
  bst *tree = bst_create();
  node *b1 = bst_node_create(id1, NULL);
  node *b2 = bst_node_create(id2, NULL);
  node *b3 = bst_node_create(id3, NULL);
  bst_insert(b2, tree);
  bst_insert(b1, tree);
  bst_insert(b3, tree);
  TEST_ASSERT_EQUAL(b1, b2->left);
  TEST_ASSERT_EQUAL(b3, b2->right);
  bst_node_free(b1);
  bst_node_free(b2);
  bst_node_free(b3);
  bst_free(tree);
}

void test_bst_insert_InsertsEqualAsBiggerChild(void) {
  char *id1 = "b", *id2 = "b";
  bst *tree = bst_create();
  node *b1 = bst_node_create(id1, NULL);
  node *b2 = bst_node_create(id2, NULL);
  bst_insert(b1, tree);
  bst_insert(b2, tree);
  TEST_ASSERT_EQUAL(b2, b1->right);
  bst_node_free(b1);
  bst_node_free(b2);
  bst_free(tree);
}

void test_bst_maximum_FindsBiggestKey(void) {
  bst *tree = get_random_tree(3, 20, 5, 25);
  node *max_node = bst_maximum(tree->root);
  char **tree_ids = get_ids(tree->root);
  char *verified_id = max_node->id;
  int i = 0;
  char *current_id = tree_ids[i];
  while (NULL != current_id) {
    int comparison_result = strcmp(verified_id, current_id);
    TEST_ASSERT_TRUE(comparison_result >= 0);
    current_id = tree_ids[i++];
  }
  free(tree_ids);
  purge_bst(tree->root);
  bst_free(tree);
}

void test_bst_maximum_ReturnsNULLIfTreeIsNULL(void) {
  node *root = NULL;
  node *max_node = bst_maximum(root);
  TEST_ASSERT_NULL(max_node);
}

void test_bst_minimum_FindsSmallestKey(void) {
  bst *tree = get_random_tree(3, 20, 5, 25);
  node* root = tree->root;
  node *min_node = bst_minimum(root);
  char **tree_ids = get_ids(root);
  char *verified_id = min_node->id;
  int i = 0;
  char *current_id = tree_ids[i];
  while (NULL != current_id) {
    int comparison_result = strcmp(verified_id, current_id);
    TEST_ASSERT_TRUE(comparison_result <= 0);
    current_id = tree_ids[i++];
  }
  free(tree_ids);
  purge_bst(root);
  bst_free(tree); 
}

void test_bst_minimum_ReturnsNULLIfTreeIsNULL(void) {
  node *root = NULL;
  node *min_node = bst_minimum(root);
  TEST_ASSERT_NULL(min_node);
}

void test_bst_predecessor_ReturnsNodePredecessor(void) {
  char *ids_str = allocate_str("abcdefg");
  bst *tree = create_tree_with_ids(ids_str);
  sort_chars_asc(ids_str);
  struct pair **nodes_with_predecessors = get_nodes_predecessors(tree->root);
  int pair_index = 0;
  struct pair *curr_pair = nodes_with_predecessors[pair_index];
  while (NULL != curr_pair) {
    if (NULL == curr_pair->paired_node) {
      TEST_ASSERT_TRUE(ids_str[0] == curr_pair->leading_node->id[0]);
    } 
    if (NULL != curr_pair->paired_node) { 
      char *node_id = curr_pair->leading_node->id;
      char *predecessor_id = curr_pair->paired_node->id;
      size_t node_id_index = find_in_sorted_asc(node_id[0], ids_str);
      TEST_ASSERT_TRUE(ids_str[node_id_index - 1] == predecessor_id[0]);
    } 
    pair_index++;
    curr_pair = nodes_with_predecessors[pair_index]; 
  }
  purge_bst(tree->root);
  bst_free(tree);
  int i = 0;
  curr_pair = nodes_with_predecessors[i];
  while (NULL != curr_pair) {
    free(curr_pair);
    curr_pair = nodes_with_predecessors[++i];
  }
  free(nodes_with_predecessors);
  free(ids_str);
}

void test_bst_predecessor_ReturnsNULLIfTreeIsNULL(void) {
  node *root = NULL;
  node *predecessor = bst_predecessor(root);
  TEST_ASSERT_NULL(predecessor);
}

void test_bst_successor_ReturnsNodeSuccessor(void) {
  char *ids_str = allocate_str("abcdefg");
  bst *tree = create_tree_with_ids(ids_str);
  sort_chars_asc(ids_str);
  struct pair **nodes_with_successors = get_nodes_successors(tree->root);
  int pair_index = 0;
  struct pair *curr_pair = nodes_with_successors[pair_index];
  while (NULL != curr_pair) {
    if (NULL == curr_pair->paired_node) {
      size_t len_ids_str = strlen(ids_str);
      TEST_ASSERT_TRUE(ids_str[len_ids_str - 1] == curr_pair->leading_node->id[0]);
    } 
    if (NULL != curr_pair->paired_node) { 
      char *node_id = curr_pair->leading_node->id;
      char *successor_id = curr_pair->paired_node->id;
      size_t node_id_index = find_in_sorted_asc(node_id[0], ids_str);
      TEST_ASSERT_TRUE(ids_str[node_id_index + 1] == successor_id[0]);
    } 
    pair_index++;
    curr_pair = nodes_with_successors[pair_index]; 
  }
  purge_bst(tree->root);
  bst_free(tree);
  int i = 0;
  curr_pair = nodes_with_successors[i];
  while (NULL != curr_pair) {
    free(curr_pair);
    curr_pair = nodes_with_successors[++i];
  }
  free(nodes_with_successors);
  free(ids_str);
}

void test_bst_successor_ReturnsNULLIfTreeIsNULL(void) {
  node *root = NULL;
  node *successor = bst_successor(root);
  TEST_ASSERT_NULL(successor);
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_bst_node_create_CreatesNode);
  RUN_TEST(test_bst_create_PayloadPointsToOriginalStructure);
  RUN_TEST(test_bst_create_MissingChildIsNULL);
  RUN_TEST(test_bst_create_RootParentIsNULL);
  RUN_TEST(test_bst_free_PayloadIsAccessibleAfterNodeIsFreed);
  RUN_TEST(test_bst_insert_InsertsInCorrectOrder);
  RUN_TEST(test_bst_insert_InsertsEqualAsBiggerChild);
  RUN_TEST(test_bst_maximum_FindsBiggestKey);
  RUN_TEST(test_bst_maximum_ReturnsNULLIfTreeIsNULL);
  RUN_TEST(test_bst_minimum_FindsSmallestKey);
  RUN_TEST(test_bst_minimum_ReturnsNULLIfTreeIsNULL);
  RUN_TEST(test_bst_predecessor_ReturnsNodePredecessor);
  RUN_TEST(test_bst_predecessor_ReturnsNULLIfTreeIsNULL);
  RUN_TEST(test_bst_successor_ReturnsNodeSuccessor);
  RUN_TEST(test_bst_successor_ReturnsNULLIfTreeIsNULL);
  return UNITY_END();
}

void tearDown(void) {
}
