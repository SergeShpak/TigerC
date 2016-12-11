#ifndef FUNCTIONAL_DATASTRUCTURES_BST_H
#define FUNCTIONAL_DATASTRUCTURES_BST_H

typedef struct _bst bst;
typedef struct _node node;

struct _bst {
  node *root;
};

struct _node {
  char *id;
  node *parent;
  node *left, *right;
  void *payload;
};

bst *bst_create(void);
node *bst_node_create(char *id, void *payload);
node *bst_search(char *id, bst *tree);
node *bst_minimum(node *tree);
node *bst_maximum(node *tree);
node *bst_predecessor(node *n);
node *bst_successor(node *n);
void bst_insert(node *n, bst *dest_tree);
void bst_delete(bst *tree, char *id);
int bst_compare_nodes(node *first, node *second);
void bst_free(bst *tree);
void bst_node_free(node*);

#endif
