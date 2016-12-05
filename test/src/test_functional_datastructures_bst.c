#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "unity.h"

#include "functional_datastructures/bst.h"

#define   true  ((1 == 1))
#define   false ((!true))

struct int_wrap {
  int num;
};

struct paired_node {
  bst *node;
  bst *pair;
};

static char *get_random_id(int min_id_length, int max_id_length);
static bst *get_random_tree(int min_nodes_count, int max_nodes_count,
                            int min_id_length, int max_id_length);
static struct int_wrap *get_rand_int_wrap_payload(void);
static struct int_wrap *get_int_wrap_payload(int payload);
static void purge_bst(bst *tree);
static void purge_shallow_payload(bst *tree);
static void count_nodes(bst *tree, int *acc);
static char **get_ids(bst *tree);
static void get_ids_internal(bst *tree, char **nodes_ids, int *nodes_ctr); 
static struct paired_node **get_nodes_with_predecessors(bst* tree);
static int check_predecessor(struct paired_node *pair, bst *tree);

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
  bst *tree = get_random_tree(10, 20, 5, 10);
  struct paired_node **nodes_with_predecessor = 
                      get_nodes_with_predecessors(tree);
  char **ids = get_ids(tree);
  int i =  0;
  struct paired_node *current_pair = nodes_with_predecessor[i];
  while(nodes_with_predecessor != NULL) {
    int is_predecessor = check_predecessor(current_pair, tree);
    TEST_ASSERT_TRUE(is_predecessor);
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

int check_predecessor(struct paired_node *pair, bst *tree) {
  char **ids = get_ids(tree);
  int i = 0;
  char *current_id = ids[i];
  if (NULL != pair->pair) {
    // If current node is root
    if (pair->node == tree) {
      return true;
    }
    return false;
  }
  while(NULL != current_id) {
    // If there is an id strictly smaller than the node id and strictly bigger
    // than its paired id, considered to be the node's predecessor, than 
    // the considere id is not the predecessor 
    if (strcmp(pair->node->id, current_id) > 0 
        && strcmp(pair->pair->id, current_id) < 0) {
      return false;
    }
    current_id = ids[i++];
  }
  return true;  
}

struct paired_node **get_nodes_with_predecessors(bst *tree) {
  int *nodes_count = (int *) malloc
  return NULL;
}

char *get_random_id(int min_id_length, int max_id_length) {
  const char *id_chars = "0123456789absdefghijhklmnopqrstuvwxyz";
  assert(min_id_length >= 0);
  assert(max_id_length >= min_id_length);
  int id_length 
            = (rand() % (max_id_length + 1 - min_id_length)) + min_id_length;
  char *id = (char*) malloc(sizeof(char) * (id_length + 1));
  int id_chars_length = strlen(id_chars);
  for (int i = 0; i < id_length; i++) {
    int rand_idx = rand() % id_chars_length;
    id[i] = id_chars[rand_idx]; 
  }
  id[id_length] = '\0';
  return id;
}

bst *get_random_tree(int min_nodes_count, int max_nodes_count,
                            int min_id_length, int max_id_length) {
  assert(min_nodes_count >= 0);
  assert(max_nodes_count >= min_nodes_count);
  int number_of_nodes 
        = (rand() % (max_nodes_count + 1 - min_nodes_count)) + min_nodes_count;
  bst *tree = NULL;
  for (int i = 0; i < number_of_nodes; i++) {
    char *id = get_random_id(min_id_length, max_id_length);
    struct int_wrap *payload = get_rand_int_wrap_payload(); 
    bst *node = bst_create(id, payload);
    bst_insert(node, tree);
  }
  return tree;
}

struct int_wrap *get_rand_int_wrap_payload(void) {
  return get_int_wrap_payload(rand());
}

struct int_wrap *get_int_wrap_payload(int payload) {
  struct int_wrap *wrap =
      (struct int_wrap*) malloc(sizeof(struct int_wrap));
  wrap->num = payload;
  return wrap;
}

void purge_bst(bst *tree) {
  if (NULL == tree) {
    return;
  }
  purge_shallow_payload(tree);
  if (NULL != tree->left) {
    purge_bst(tree->left);
  }
  if (NULL != tree->right) {
    purge_bst(tree->right);
  }
  if (NULL != tree->id) {
    free(tree->id);
  }
  free(tree);
}

void purge_shallow_payload(bst *tree) {
  if (NULL == tree) {
    return;
  }
  if (NULL != tree->left) {
    purge_shallow_payload(tree->left);
  }
  if (NULL != tree->right) {
    purge_shallow_payload(tree->right);
  }
  if (NULL != tree->payload) {
    free(tree->payload);
    tree->payload = NULL;
  }
}

char **get_ids(bst *tree) {
  int *nodes_ctr = (int *) malloc(sizeof(int));
  *nodes_ctr = 0;
  count_nodes(tree, nodes_ctr);
  char **nodes_ids = (char**) malloc(sizeof(char*) * (*nodes_ctr + 1));
  nodes_ids[*nodes_ctr] = NULL;
  *nodes_ctr = 0;
  get_ids_internal(tree, nodes_ids, nodes_ctr);
  free(nodes_ctr);
  return nodes_ids;
}

void count_nodes(bst *tree, int *acc) {
  if (NULL == tree) {
    return;
  } 
  (*acc)++;
  if (NULL != tree->left) {
    count_nodes(tree->left, acc);
  }
  if (NULL != tree->right) {
    count_nodes(tree->right, acc);
  }
}

void get_ids_internal(bst *tree, char **nodes_ids, int *nodes_ctr) {
  if (NULL == tree) {
    return;
  }
  nodes_ids[*nodes_ctr] = tree->id;
  (*nodes_ctr)++;
  if (NULL != tree->left) {
    get_ids_internal(tree->left, nodes_ids, nodes_ctr);
  }
  if (NULL != tree->right) {
    get_ids_internal(tree->right, nodes_ids, nodes_ctr);
  }
}
