#ifndef FUNCTIONAL_DATASTRUCTURES_BST_H
#define FUNCTIONAL_DATASTRUCTURES_BST_H

typedef struct _bst bst;
enum color;

enum color {
  RED,
  BLACK
};

struct _bst {
  char *id;
  bst *parent;
  bst *left, *right;
  void *payload;
  enum color color;
};

bst *bst_create(char *id, void *payload);
bst *bst_search(char *id, bst *tree);
bst *bst_minimum(bst *tree);
bst *bst_maximum(bst *tree);
bst *bst_predecessor(bst *tree);
bst *bst_successor(bst *tree);
bst *bst_insert(bst *tree, bst *dest_tree);
bst *bst_delete(bst *tree, char *id);
void bst_free(bst *tree);

#endif
