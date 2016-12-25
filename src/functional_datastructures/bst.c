#include <stdlib.h>
#include <string.h>

#include "functional_datastructures/bst.h"

static void transplant(node *node_to_remove, node *node_to_transplant);

bst *bst_create(void) {
  bst *tree = (bst *) malloc(sizeof(bst));
  tree->root = NULL;
  return tree;
}

node *bst_node_create(char *id, void *payload) {
  node *n = (node*) malloc(sizeof(node));
  if (NULL == n) {
    return NULL;
  }
  n->id = id;
  n->payload = payload;
  n->parent = NULL;
  n->left = NULL;
  n->right = NULL;
  return n;
}

node *bst_search(char *bst_id, bst *bst_tree) {  
  node *current_node = bst_tree->root;
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

node *bst_minimum(node *n) {
  if (NULL == n) {
    return NULL; 
  }
  node *current_node = n;
  while (NULL != current_node->left) {
    current_node = current_node->left;
  }
  return current_node;
}

node *bst_maximum(node *n) {
  if (NULL == n) {
    return NULL;
  }
  node *current_node = n;
  while(NULL != current_node->right) {
    current_node = current_node->right;
  }
  return current_node;
}

node *bst_predecessor(node *n) {
  if (NULL == n) {
    return NULL; 
  }
  if (NULL != n->left) {
    return bst_maximum(n->left);
  }
  node *current_node = n;
  node *parent = current_node->parent;
  while(NULL != parent && current_node == parent->left) {
    current_node = parent;
    parent = parent->parent;
  }
  return parent;
}

node *bst_successor(node *n) {
  if (NULL == n) {
    return NULL;
  }
  if (NULL != n->right) {
    return bst_minimum(n->right);
  }
  node *current_node = n;
  node *parent = n->parent;
  while (NULL !=  parent && current_node == parent->right) {
    current_node = parent;
    parent = parent->parent;
  }
  return parent;
}

void bst_insert(node *n, bst *bst_dest_tree) {
  node *current_node = bst_dest_tree->root;
  node *previous_node = NULL;
  while (NULL != current_node) {
    previous_node = current_node;
    int compare_indic = bst_compare_nodes(n, current_node);
    if (compare_indic < 0) {
      current_node = current_node->left;
    }
    if (compare_indic >= 0) {
      current_node = current_node->right;
    }
  }
  // Root is null
  if (NULL == previous_node) {
    bst_dest_tree->root = n;
    n->parent = NULL;
    return;
  }
  n->parent = previous_node;
  if (bst_compare_nodes(n, previous_node) < 0) {
    previous_node->left = n;
    return;
  }
  previous_node->right = n;
}

void bst_delete(bst *bst_tree, char *bst_id) {
  node *target = bst_search(bst_id, bst_tree);
  if (NULL == target) {
    return;
  }  
  // Target has no children
  if (NULL == target->right && NULL == target->left) {
    bst_node_free(target);
    target = NULL; 
    return;
  }
  // Target has two children
  if (NULL != target->right && NULL != target->left) {
    node *target_successor = bst_successor(target);
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
    bst_node_free(target);
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
  bst_node_free(target);
  target = NULL;
}

int bst_compare_nodes(node *first, node *second) {
  return strcmp(first->id, second->id);
}

void bst_node_free(node *n) {
  if (NULL == n) {
    return;
  } 
  free(n);
}

void bst_free(bst *tree) {
  if (NULL == n) {
    return;
  }
  free(tree);
}

// ****************************************************************************
// Static functions section
// ****************************************************************************

void transplant(node *node_to_remove, node *node_to_transplant) {
  node *parent_node = node_to_remove->parent;
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
