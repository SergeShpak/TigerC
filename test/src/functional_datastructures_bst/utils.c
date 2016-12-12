#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../include/functional_datastructures/utils.h"

static void purge_shallow_payload(node* tree);
static void get_ids_internal(node *tree, char **nodes_ids, size_t *nodes_ctr); 
static void quicksort(char *str, size_t p, size_t r);
static size_t partition(char *str, size_t p, size_t r);
static struct pair **allocate_pairs(node *n); 
static void fill_pairs(node *, struct pair **nodes_with_successors, 
                      size_t *acc_counter, node* (*pair_choosing_func)(node*));
static struct pair **get_pairs(node *n, node *(pair_choosing_func)(node*));

char *get_random_id(int min_id_length, int max_id_length) {
  const char *id_chars = "0123456789absdefghijhklmnopqrstuvwxyz";
  assert(min_id_length >= 0);
  assert(max_id_length >= min_id_length);
  int id_length 
            = (rand() % (max_id_length + 1 - min_id_length)) + min_id_length;
  char *id = (char*) malloc(sizeof(char) * (id_length + 1));
  size_t id_chars_length = strlen(id_chars);
  for (int i = 0; i < id_length; i++) {
    size_t rand_idx = rand() % id_chars_length;
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
  bst *tree = bst_create();
  for (int i = 0; i < number_of_nodes; i++) {
    char *id = get_random_id(min_id_length, max_id_length);
    struct int_wrap *payload = get_rand_int_wrap_payload(); 
    node *node = bst_node_create(id, payload);
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

void purge_bst(node *n) {
  if (NULL == n) {
    return;
  }
  purge_shallow_payload(n);
  if (NULL != n->left) {
    purge_bst(n->left);
  }
  if (NULL != n->right) {
    purge_bst(n->right);
  }
  if (NULL != n->id) {
    free(n->id);
  }
  free(n);
  return;
}

char **get_ids(node *n) {
  size_t *nodes_ctr = (size_t *) malloc(sizeof(size_t));
  *nodes_ctr = 0;
  count_nodes(n, nodes_ctr);
  char **nodes_ids = (char**) malloc(sizeof(char*) * (*nodes_ctr + 1));
  nodes_ids[*nodes_ctr] = NULL;
  *nodes_ctr = 0;
  get_ids_internal(n, nodes_ids, nodes_ctr);
  free(nodes_ctr);
  return nodes_ids;
}

void count_nodes(node *n, size_t *acc) {
  if (NULL == n) {
    *acc = 0;
    return;
  } 
  (*acc)++;
  if (NULL != n->left) {
    count_nodes(n->left, acc);
  }
  if (NULL != n->right) {
    count_nodes(n->right, acc);
  }
}

bst *create_tree_with_ids(char *ids_string) {
  int len_str = strlen(ids_string);
  if (0 == len_str) {
    return NULL;
  }
  bst *tree = bst_create();
  for (int i = 0; i < len_str; i++) {
    char *current_id = (char*) malloc(sizeof(char) + 1);
    current_id[0] = ids_string[i];
    current_id[1] = '\0';
    node *node = bst_node_create(current_id, NULL);
    bst_insert(node, tree);
  }
  return tree;
}

void sort_chars_asc(char* str) {
  size_t len = strlen(str);
  quicksort(str, 0, len - 1); 
}

size_t find_in_sorted_asc(char target, char *str) {
  size_t len = strlen(str);
  if (1 == len) {
    if (str[0] == target) {
      return 0;
    }
    return -1;
  }
  size_t lower_bound = 0, upper_bound = len;
  while(1 == 1) {
    if (lower_bound == upper_bound) {
      return -1;
    }
    size_t mid = (upper_bound + lower_bound) / 2;
    if (str[mid] == target) {
      return mid;
    } 
    if (str[mid] > target) {
      upper_bound = mid;
      continue;
    }
    if (str[mid] < target) {
      lower_bound = mid;
      continue; 
    }
  }  
}

struct pair **get_nodes_predecessors(node *n) { 
  return get_pairs(n, bst_predecessor);
}

struct pair **get_nodes_successors(node *n) {
  return get_pairs(n, bst_successor);
}

char *allocate_str(char *str_to_duplicate) {
  int len = strlen(str_to_duplicate);
  char *str = (char*) malloc(sizeof(char) * (len + 1));
  strncpy(str, str_to_duplicate, len);
  str[len] = '\0';
  return str;
}

// ****************************************************************************
// Static functions
// ****************************************************************************

void get_ids_internal(node *n, char **nodes_ids, size_t *nodes_ctr) {
  if (NULL == n) {
    return;
  }
  nodes_ids[*nodes_ctr] = n->id;
  (*nodes_ctr)++;
  if (NULL != n->left) {
    get_ids_internal(n->left, nodes_ids, nodes_ctr);
  }
  if (NULL != n->right) {
    get_ids_internal(n->right, nodes_ids, nodes_ctr);
  }
}

void purge_shallow_payload(node *n) {
  if (NULL == n) {
    return;
  }
  if (NULL != n->left) {
    purge_shallow_payload(n->left);
  }
  if (NULL != n->right) {
    purge_shallow_payload(n->right);
  }
  if (NULL != n->payload) {
    free(n->payload);
    n->payload = NULL;
  }
}

void quicksort(char *str, size_t p, size_t r) {
  if (p >= r) {
    return;
  }
  size_t q = partition(str, p, r);
  quicksort(str, p, q - 1);
  quicksort(str, q + 1, r);
}

size_t partition(char *str, size_t p, size_t r) {
  char x = str[r];
  size_t i = p - 1;
  for (size_t j = p; j < r; j++) {
    if (str[j] < x) {
      i++;
      char tmp = str[i];
      str[i] = str[j];
      str[j] = tmp; 
    }
  }
  i++;
  char tmp = str[i];
  str[i] = str[r];
  str[r] = tmp;
  return i;
}

struct pair **get_pairs(node *n, node *(pair_choosing_func)(node*)) {
  struct pair **pairs = allocate_pairs(n); 
  size_t *acc_counter = (size_t*) malloc(sizeof(size_t));
  *acc_counter = 0;
  fill_pairs(n, pairs, acc_counter, pair_choosing_func);
  free(acc_counter);
  return pairs;
}

struct pair **allocate_pairs(node *n) {
  size_t *nodes_count = (size_t*) malloc(sizeof(size_t));
  *nodes_count = 0;
  count_nodes(n, nodes_count);
  struct pair **pairs 
            = (struct pair**) malloc(sizeof(struct pair) * (*nodes_count + 1));
  pairs[*nodes_count] = NULL;
  free(nodes_count);
  return pairs;
}

void fill_pairs(node *n, struct pair **allocated_nodes,
                size_t *acc_counter, node* (*pair_choosing_func)(node*)) {
  if (NULL == n) {
    return;
  }
  struct pair *current_pair = (struct pair *) malloc(sizeof(struct pair));
  current_pair->leading_node = n;
  current_pair->paired_node = pair_choosing_func(n);
  allocated_nodes[*acc_counter] = current_pair;
  (*acc_counter)++;
  fill_pairs(n->left, allocated_nodes, acc_counter, pair_choosing_func);
  fill_pairs(n->right, allocated_nodes, acc_counter, pair_choosing_func);
}

// ****************************************************************************
// End of static functions section
// ****************************************************************************
