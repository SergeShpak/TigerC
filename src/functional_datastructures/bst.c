#include <stdlib.h>
#include <string.h>

#include "functional_datastructures/bst.h"

static void transplant(bst *node_to_remove, bst *node_to_transplant);

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

void bst_insert(bst *node, bst *bst_dest_tree) {
  bst *current_node = bst_dest_tree;
  bst *previous_node = NULL;
  while (NULL != current_node) {
    previous_node = current_node;
    current_node = current_node->right;
    int compare_indic = bst_compare_nodes(node, bst_dest_tree);
    if (compare_indic < 0) {
      current_node = current_node->left;
    }
  }
  // Root is null
  if (NULL == previous_node) {
    bst_dest_tree = node;
    node->parent = NULL;
    return;
  }
  node->parent = previous_node;
  if (bst_compare_nodes(node, previous_node) < 0) {
    previous_node->left = node;
    return;
  }
  previous_node->right = node;
}

void bst_delete(bst *bst_tree, char *bst_id) {
  bst *target = bst_search(bst_id, bst_tree);
  if (NULL == target) {
    return;
  }  
  // Target has no children
  if (NULL == target->right && NULL == target->left) {
    bst_free(target);
    target = NULL; 
    return;
  }
  // Target has two children
  if (NULL != target->right && NULL != target->left) {
    bst *target_successor = bst_successor(target);
    // Successor is a younger child of a descendant of the target.
    // Successor does not have a left child by definition
    if (target_successor->parent != target) {
      transplant(target_successor, target_successor->right); 
      target_successor->right = target->right;
      target_successor->right->parent = target_successor;
    }
    transplant(target, target_successor);
    target_successor->left = target->left;
    target_successor->left->parent = target_successor; 
    bst_free(target);
    target = NULL;
    return;
  }
  // Target has one child
  if (NULL != target->right) {
    transplant(target, target->right);
  }
  if (NULL != target->left) {
    transplant(target, target->left); 
  }
  bst_free(target);
  target = NULL;
}

int bst_compare_nodes(bst *first, bst *second) {
  return strcmp(first->id, second->id);
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

// ****************************************************************************
// Static functions section
// ****************************************************************************

void transplant(bst *node_to_remove, bst *node_to_transplant) {
  bst *parent_node = node_to_remove->parent;
  node_to_remove->parent = NULL;
  if (NULL == node_to_transplant) {
    return;
  }
  if (NULL == parent_node) {
    node_to_transplant->parent = NULL;
    return;
  }
  node_to_transplant->parent = parent_node;
  if (node_to_remove == parent_node->left) {
    parent_node->left = node_to_transplant;
    return;
  }
  parent_node->right = node_to_transplant;
}

// ****************************************************************************
// End of static functions section
// ****************************************************************************
