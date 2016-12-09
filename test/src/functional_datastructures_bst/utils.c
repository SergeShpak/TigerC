#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../include/functional_datastructures/utils.h"

static void purge_shallow_payload(bst* tree);
static void get_ids_internal(bst *tree, char **nodes_ids, int *nodes_ctr); 
static void quicksort(char *str, int p, int r);
static int partition(char *str, int p, int r);

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

bst *get_tree(char *ids_string) {
  int len_str = strlen(ids_string);
  if (0 == len_str) {
    return NULL;
  }
  bst *tree = NULL;
  for (int i = 0; i < len_str; i++) {
    char *current_id = (char*) malloc(sizeof(char) + 1);
    current_id[0] = ids_string[i];
    current_id[1] = '\0';
    bst *node = bst_create(current_id, NULL);
    bst_insert(node, tree);
  }
  return tree;
}

void sort_chars(char* str) {
  int len = strlen(str);
  quicksort(str, 0, len - 1); 
}

void quicksort(char *str, int p, int r) {
  if (p >= r) {
    return;
  }
  int q = partition(str, p, r);
  quicksort(str, p, q - 1);
  quicksort(str, p, q + 1); 
}

int partition(char *str, int p, int r) {
  char x = str[r];
  int i = p - 1;
}

// ****************************************************************************
// Static functions
// ****************************************************************************

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

// ****************************************************************************
// End of static functions section
// ****************************************************************************
