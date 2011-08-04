#ifndef TREE_H
#define TREE_H

/* */
typedef struct node {
  struct node **children;
  struct node *parent;
  void * data;
  unsigned int depth;
  unsigned int count;
  unsigned int maxSize;
} Node;

/* */
typedef struct {
  Node *root;
  unsigned int depth;
  unsigned int count;
} Tree;

/*
 *
 */
Node *addChildNode(Tree *tree, Node *parent, void *data);

/*
 *
 */
Tree *newTree(void *data);

/*
 *
 */
void printTree(const Tree *tree);

#endif
