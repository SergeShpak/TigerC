#include <stdlib.h>

#include "functional_datastructures/bst.h"

bst *bst_create(char *bst_id, void *bst_payload) {
  bst *tree = (bst*) malloc(sizeof(bst));
  tree->id = bst_id;
  tree->payload = bst_payload;
  tree->parent = NULL;
  tree->left = NULL;
  tree->right = NULL;
  return tree;
}

bst *bst_search(char *bst_id, bst *bst_tree) {
  return NULL;
}

bst *bst_minimum(bst *bst_tree) {
  return NULL;
}

bst *bst_maximum(bst *bst_tree) {
  return NULL;
}

bst *bst_predecessor(bst *bst_tree) {
  return NULL;
}

bst *bst_insert(bst *bst_node, bst *bst_dest_tree) {
  return NULL;
}

bst *bst_delete(bst *bst_tree, char *bst_id) {
  return NULL;
}

void bst_free(bst *tree) {
  if (NULL == tree) {
    return;
  } 
  bst_free(tree->left);
  bst_free(tree->right);
  free(tree);
  tree = NULL;
}
