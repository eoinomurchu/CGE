#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

/*
 *
 */
Node *addChildNode(Tree *tree, Node *parent, void *data) {
  Node *child = malloc(sizeof(Node));
  child->data = data;
  child->parent = parent;
  child->depth = 0;
  child->count = 0;
  child->maxSize = 1;
  child->children = malloc(child->maxSize*sizeof(Node*));

  if (parent) {
    child->depth = parent->depth + 1;
    if (parent->count == parent->maxSize) {
      parent->maxSize *= 2;
      parent->children = realloc(parent->children, parent->maxSize*sizeof(Node*));
    }
    parent->children[parent->count++] = child;
  }
  if (tree) {
    ++tree->count;
    if (child->depth > tree->depth)
      tree->depth = child->depth;
  }

  return child;
}

/*
 *
 */
Tree *newTree(void *data) {
  Tree *t = malloc(sizeof(Tree));
  t->depth = 0;
  t->root = addChildNode(t, NULL, data);
  return t;
}

static void printSubTree(const Node *root) {
  if (root) {
    int i;
    for (i = root->depth; i > 0; i--)
      printf("%s", i==1 ? "|____" : "     ");
    printf("%s\n", ((char *)root->data));
    for (i = 0; i < root->count; i++)
      printSubTree(root->children[i]);
  }
}

/*
 *
 */
void printTree(const Tree *tree) {
  printSubTree(tree->root);
}
