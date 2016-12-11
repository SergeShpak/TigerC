#ifndef TIGER_TESTS_FD_BST_UTILS_H
#define TIGER_TESTS_FD_BST_UTILS_H

#include <unity.h>
#include <functional_datastructures/bst.h>

#define   true  ((1 == 1))
#define   false ((!true))  

struct int_wrap {
  int num;
};

struct pair {
  node *leading_node;
  node *paired_node;
};

char *get_random_id(int min_id_length, int max_id_length);
bst *get_random_tree(int min_nodes_count, int max_nodes_count,
                           int min_id_length, int max_id_length);
struct int_wrap *get_rand_int_wrap_payload(void);
struct int_wrap *get_int_wrap_payload(int payload);
void purge_bst(node*);
void count_nodes(node*, size_t *acc);
char **get_ids(node*);
int check_predecessors(bst *tree, int *valid_indicator);
bst *create_tree_with_ids(char *ids_string);
void sort_chars_asc(char *str);
struct pair **get_nodes_predecessors(node*);
struct pair **get_nodes_successors(node*);
size_t find_in_sorted_asc(char target, char *str);
char *allocate_str(char *str_to_duplicate);

#endif
