#include <stdlib.h>
#include <string.h>

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
  bst *current_node = bst_tree;
  while (NULL != current_node) {
    int compare_result = strcmp(bst_id, current_node->id);
    if (0 == compare_result) {
      return current_node; 
    }
    if (compare_result > 0) {
      current_node = current_node->right; 
    }
    if (compare_result < 0) {
      current_node = current_node->left; 
    }
  }
  return current_node;
}

bst *bst_minimum(bst *bst_tree) {
  if (NULL == bst_tree) {
    return NULL; 
  }
  bst *current_node = bst_tree;
  while (NULL != current_node->left) {
    current_node = current_node->left;
  }
  return current_node;
}

bst *bst_maximum(bst *bst_tree) {
  if (NULL == bst_tree) {
    return NULL;
  }
  bst *current_node = bst_tree;
  while(NULL != current_node->right) {
    current_node = current_node->right;
  }
  return current_node;
}

bst *bst_predecessor(bst *bst_tree) {
  if (NULL == bst_tree) {
    return NULL; 
  }
  if (NULL != bst_tree->left) {
    return bst_maximum(bst_tree->left);
  }
  bst *current_node = bst_tree;
  bst *parent = bst_tree->parent;
  while(NULL != parent && current_node == parent->left) {
    current_node = parent;
    parent = parent->parent;
  }
  return parent;
}

bst *bst_successor(bst *bst_tree) {
  if (NULL == bst_tree) {
    return NULL;
  }
  if (NULL != bst_tree->right) {
    return bst_minimum(bst_tree->right);
  }
  bst *current_node = bst_tree;
  bst *parent = bst_tree->parent;
  while (NULL !=  parent && current_node == parent->right) {
    current_node = parent;
    parent = parent->parent;
  }
  return parent;
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
