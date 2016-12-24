#ifndef FUNCTIONAL_DATASTRUCTURES_BST_H
#define FUNCTIONAL_DATASTRUCTURES_BST_H

typedef struct _bst bst;
typedef struct _node node;

/**
 * \struct bst include/functional_datastructures/bst.h
 * \brief Representation of a binary search tree.
 *
 * Represents a binarty search tree. Contains a pointer to the root of the
 * tree.
 */
struct _bst {
  node *root;
};

/**
 * \struct node include/functional_datastructures/bst.h
 * \brief Representation of the node of a binary search tree.
 *
 * Represents a node of a binary search tree. Identified by a string id.
 * Contains a void pointer to its payload. Points to its parent and children.
 */ 
struct _node {
  char *id;
  node *parent;
  node *left, *right;
  void *payload;
};

bst *bst_create(void);

/**
 * \brief Creates a node wit a given id and payload.
 *
 * Allocates a memory for the node, creates a node with the given id and
 * payload and returns the pointer to it. Parent and children of the node are
 * set to NULL.
 *
 * \param[in] id  Id of the node to be created.
 * \param[in] payload Void pointer to the payload that will be associated with
 *                    the node.
 *
 *  \returns On success returns a pointer to the newly created node. In case
 *            of a failure return NULL.
 */
node *bst_node_create(char *id, void *payload);

/**
 * \brief Looks for a node with the given id in the given tree.
 *
 * Tries to find a node with the given id in the provided tree. Returns the
 * first node found. The tree in which the search is performed is represented
 * as a node, so the operation can be easily performed in sub-trees.
 *
 * \param [in]  id  Id of the target node.
 * \param[in]   tree A pointer to the node, that is considered the root of the
 *                  search tree.
 *  \returns Pointer to the first found node. If no node with the given id
 *          exists in the given subtree, returns NULL.
 */
node *bst_search(char *id, bst *tree);

/**
 * \brief Finds a node with the minimal id in the given subtree.
 *
 * Finds a node with the minimal id in the given subtree. Returns the first 
 * node found. The tree in which the search is performed is represented
 * as a node, so the operation can be easily performed in sub-trees.
 *
 * \param [in]  tree  Pointer to the node that is considered the root of the
 *                    search tree.
 *
 *  \returns A pointer to the node with the minimal id in the given tree. If 
 *          the tree is empty, returns NULL.
 */
node *bst_minimum(node *tree);

/**
 * \brief Finds a node with the maximal id in the given subtree.
 *
 * Finds a node with the maximal id in the given subtree. Returns the first 
 * node found. The tree in which the search is performed is represented
 * as a node, so the operation can be easily performed in sub-trees.
 *
 * \param [in]  tree  Pointer to the node that is considered the root of the
 *                    search tree.
 *
 *  \returns A pointer to the node with the maximal id in the given tree. If 
 *          the tree is empty, returns NULL.
 */
node *bst_maximum(node *tree);

// TODO: treating case when there are several nodes with the same id
/**
 * \brief Finds the node's predecessors in the maximal tree.
 *
 * Finds the node with the maximal id amongs the nodes with ids that are
 * smaller or equal to that of the given node. The nodes belong to the
 * maximal tree to which the given node belongs.
 *
 * \param [in]  n Pointer to the node which predecessor is found.
 * 
 *  \returns A pointer to the predecessor node. Returns NULL if the given node
 *          is null, or when the given node has the minimal id in the tree.
 */
node *bst_predecessor(node *n);

// TODO: treating case when there are several nodes with the same id
/**
 * \brief Finds the node's successors in the maximal tree.
 *
 * Finds the node with the minimal id amongs the nodes with ids that are
 * greater or equal to that of the given node. The nodes belong to the
 * maximal tree to which the given node belongs.
 *
 * \param [in]  n Pointer to the node which successor is found.
 * 
 *  \returns A pointer to the successor node. Returns NULL if the given node
 *          is null, or when the given node has the maximal id in the tree.
 */
node *bst_successor(node *n);
void bst_insert(node *n, bst *dest_tree);
void bst_delete(bst *tree, char *id);
int bst_compare_nodes(node *first, node *second);
void bst_free(bst *tree);
void bst_node_free(node*);

#endif
