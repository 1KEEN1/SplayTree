#include <bits/stdc++.h>
using namespace std;

class node {
public:
  int key;
  node *left, *right;
};

node *newNode(int key) {
  node *Node = new node();
  Node->key = key;
  Node->left = Node->right = NULL;
  return (Node);
}

node *rightRotate(node *x) {
  node *y = x->left;
  x->left = y->right;
  y->right = x;
  return y;
}

node *leftRotate(node *x) {
  node *y = x->right;
  x->right = y->left;
  y->left = x;
  return y;
}

node *splay(node *root, int key) {
  if (root == NULL || root->key == key)
    return root;

  if (root->key > key) {
    if (root->left == NULL)
      return root;

    if (root->left->key > key) {
      root->left->left = splay(root->left->left, key);
      root = rightRotate(root);
    } else if (root->left->key < key) {
      root->left->right = splay(root->left->right, key);
      if (root->left->right != NULL)
        root->left = leftRotate(root->left);
    }
    return (root->left == NULL) ? root : rightRotate(root);
  } else {
    if (root->right == NULL)
      return root;

    if (root->right->key > key) {
      root->right->left = splay(root->right->left, key);
      if (root->right->left != NULL)
        root->right = rightRotate(root->right);
    } else if (root->right->key < key) {
      root->right->right = splay(root->right->right, key);
      root = leftRotate(root);
    }
    return (root->right == NULL) ? root : leftRotate(root);
  }
}

struct node *delete_key(struct node *root, int key) {
  struct node *temp;
  if (!root)
    return NULL;

  root = splay(root, key);

  if (key != root->key)
    return root;

  if (!root->left) {
    temp = root;
    root = root->right;
  } else {
    temp = root;
    root = splay(root->left, key);
    root->right = temp->right;
  }

  free(temp);

  return root;
}

node *search(node *root, int key) { return splay(root, key); }

void preOrder(node *root) {
  if (root != NULL) {
    cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
  }
}

int main() {
  node *root = newNode(100);
  root->left = newNode(50);
  root->right = newNode(200);
  root->left->left = newNode(40);
  root->left->left->left = newNode(30);
  root->left->left->left->left = newNode(20);

  root = delete_key(root, 30);

  root = search(root, 20);

  cout << "Preorder traversal of the modified Splay tree is \n";
  preOrder(root);

  return 0;
}