#include <stdio.h>
#include "BSTs_1008148648.c"
#define MAX_OPS 128

double freq = 0;

BST_Node* insertByKey(BST_Node* root, double key) {
  freq += 25.0;
  return BST_insert(root, newBST_Node(freq, 0, key));
}

BST_Node* insert(BST_Node* root, double freq, int bar, double index) {
  return BST_insert(root, newBST_Node(freq, bar, index));
}

void pArr(int steps[MAX_OPS], int index) {
  int i = 0;
  printf("Traverse path: ");
  while (steps[i] != 0 && i <= index) {
    if (i == -1) {
      printf("Left ");
    } else {
      printf("Right ");
    }
    ++i;
  }
  printf("\n");
}

int comp(int steps[MAX_OPS], BST_Node* root, double exp) {
  int i = 0;

  while (steps[i] != 0) {
    if (steps[i] == -1) {
      root = root->left;

      if (root == NULL) {
        printf("ERROR:========================\n");
        printf("Reached end of BST before reaching expected node | Expected: %g Got: NULL\n", exp);
        pArr(steps, i);
        printf("==============================\n");
        return 0;
      }
    } else {
      root = root->right;

      if (root == NULL) {
        printf("ERROR:========================\n");
        printf("Reached end of BST before reaching expected node | Expected: %g Got: NULL\n", exp);
        pArr(steps, i);
        printf("==============================\n");
        return 0;
      }
    }
    ++i;
  }

  if (root->key != exp) {
    printf("ERROR:========================\n");
    printf("Incorrect node key in BST | Expected: %g Got: %g\n", exp, root->key);
    pArr(steps, i);
    printf("==============================\n");
  }
  return root->key == exp;
}

int count(BST_Node* n, int c) {
  if (n == NULL) return c;

  c += 1;
  c = count(n->left, c);
  c = count(n->right, c);
  return c;
}

int eq(BST_Node* a, BST_Node* b) {
  if (a == NULL && b == NULL) {
    return 1;
  }

  if (a == NULL) return 0;

  if (b == NULL) return 0;

  if (a->key == b->key && a->bar == b->bar) {
    return 1;
  } else {
    return 0;
  }
}

int req(BST_Node* r1, BST_Node* r2) {
  if (!eq(r1, r2)) {
    return 0;
  }

  if (!req(r1->left, r2->left)) {
    return 0;
  }

  if (!req(r1->right, r2->right)) {
    return 0;
  }

  return 1;
}

void cpy(BST_Node* a, BST_Node* b) {
  if (b == NULL) return;

  if (b->left != NULL) {
    a->left = newBST_Node(b->freq, b->bar, b->index);
  }

  if (b->right != NULL) {
    a->right = newBST_Node(b->freq, b->bar, b->index);
  }
}

int approx(double in, double exp, double delta) {
  double diff = in - exp;
  double abs;

  if (diff < 0) {
    abs = diff * -1;
  } else {
    abs = diff;
  }

  return abs <= delta;
}

int main() {
  int tests = 1;
  read_note_table();
  printf("\n\n\nTests:\n\n");

  BST_Node* r = insertByKey(NULL, 100);
  insertByKey(r, 50);
  insertByKey(r, 25);
  insertByKey(r, 75);
  insertByKey(r, 12.5);
  insertByKey(r, 37.5);
  insertByKey(r, 125);
  insertByKey(r, 150);
  insertByKey(r, 112.5);
  insertByKey(r, 3000);
  insertByKey(r, 20);

  int s[MAX_OPS];

  int succ = 0;

  s[0] = 0;
  succ += comp(s, r, 100);
  int checks = 1;

  {
    int s[MAX_OPS] = {-1, 0};
    succ += comp(s, r, 50);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {-1, -1, -1, 0};
    succ += comp(s, r, 12.5);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {-1, -1, -1, 1, 0};
    succ += comp(s, r, 20);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {-1, 1, 0};
    succ += comp(s, r, 75);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {1, -1, 0};
    succ += comp(s, r, 112.5);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {1, 1, 1, 0};
    succ += comp(s, r, 3000);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {1, 1, 0};
    succ += comp(s, r, 150);
    checks++; tests++;;
  }

  if (succ != checks) {
    printf("\n** %d ** Errors encountered from inserting nodes.\n\n", checks - succ);
    checks = succ;
  } else {
    printf("OWO Test passed for inserting nodes.\n\n");
  }

  insertByKey(r, 140);
  insertByKey(r, 135);
  insertByKey(r, 130);
  insertByKey(r, 131);

  r = BST_delete(r, 0, 125);

  {
    int s[MAX_OPS] = {1, 0};
    succ += comp(s, r, 130);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {1, 1, -1, -1, -1, 0};
    succ += comp(s, r, 131);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {1, -1, 0};
    succ += comp(s, r, 112.5);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {1, 1, 1, 0};
    succ += comp(s, r, 3000);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {-1, 1, 0};
    succ += comp(s, r, 75);
    checks++; tests++;;
  }

  if (succ != checks) {
    printf("\n** %d ** Errors encountered from deleting node with 2 children.\n\n", checks - succ);
    checks = succ;
  } else {
    printf("OWO Test passed for deleting node with 2 children.\n\n");
  }

  r = BST_delete(r, 0, 100);

  {
    int s[MAX_OPS] = {0};
    succ += comp(s, r, 112.5);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {1, 0};
    succ += comp(s, r, 130);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {1, 1, -1, -1, 0};
    succ += comp(s, r, 135);
    checks++; tests++;;
  }

  {
    int s[MAX_OPS] = {-1, -1, -1, 1, 0};
    succ += comp(s, r, 20);
    checks++; tests++;;
  }

  if (succ != checks) {
    printf("\n** %d ** Errors encountered from deleting root node\n\n", checks - succ);
    checks = succ;
  } else {
    printf("OWO Test passed for deleting root node.\n\n");
  }

  delete_BST(r);
  printf("UWU? Deleting BST, check for memory leaks using valgrind or something uwu!\n\n");


  r = NULL;
  r = insert(r, 21.83, 30, 0.1); // 300.1
  insert(r, 16.35, 84, 0.2); // 840.2
  insert(r, 49.00, 5, 0.5); // 50.5
  insert(r, 51.91, 4, 0.4); // 40.4
  insert(r, 98.00, 12, 0.3); // 120.3
  insert(r, 1864.66, 10, 0.7); // 100.7
  insert(r, 698.46, 43, 0.8); // 430.8
  insert(r, 103.83, 22, 0.9); // 220.9
  insert(r, 58.27, 100, 1.0); // 1000.96
  insert(r, 82.41, 3, 0.5);
  insert(r, 77.78, 3, 1.0);
  insert(r, 32.70, 3, 0.7);

  BST_Node* cp = newBST_Node(r->freq, r->bar, r->index);
  cpy(cp, r);

  reverseSong(r);

  BST_Node* a = BST_search(r, 100, 0);
  BST_Node* b = BST_search(r, 3, 0);
  BST_Node* c = BST_search(r, 19, 1 - 0.2);

  if (a != NULL && b != NULL && c != NULL) {
    checks++; tests++;;
    succ++;
  } else {
    checks++; tests++;;
    printf("ERROR: Reverse Song breaks BST structure; No longer able to search the tree.\n");
    printf("Make sure you've updated every variable, including the key, when you reverse it!\n");
  }

  if (succ != checks) {
    printf("\n** %d ** Errors encountered from reverseSong\n\n", checks - succ);
    checks = succ;
  } else {
    printf("OWO Test passed for reverseSong.\n\n");
  }

  reverseSong(r);

  if (eq(cp, r)) {
    checks++; tests++;;
    succ++;
  } else {
    checks++; tests++;;
  }

  if (succ != checks) {
    printf("\n** %d ** Small issues encountered from calling reverseSong twice:\n", checks - succ);
    printf("By calling reverseSong(reverseSong(root)), your function returns a different BST from the original root.\n");
    printf("Note: Not really an issue though as long as everything is working.\n");
    checks = succ;
  }


  insert(r, 4434.92, 12, 0.2);

  r = BST_harmonize(r, 5, 0.01);
  
  if (count(r, 0) == 23) {
    succ++;
    checks++; tests++;;
  } else {
    checks++; tests++;;
  }

  if (succ != checks) {
    printf("\n** %d ** Errors encountered from harmonize\n", checks - succ);
    printf("BST with 12 elements passed into function, expected 23 elements to be returned (some elements had invalid indices), got %d\n\n", count(r, 0));
    checks = succ;
  } else {
    printf("OWO Test 1 passed for harmonize.\n\n");
  }

  a = BST_search(r, 30, .1 + .01);
  {
    if (a == NULL) {
      printf("Expected to find note with Bar 30, Index 0.11, Frequency 29.14: Got NULL\n");
      checks++; tests++;;
    } else {
      succ += approx(a->freq, 29.14, 0.01) ? 1 : 0;
      checks++; tests++;;
      if (succ != checks)
        printf("Expected to find note with Bar 30, Index 0.11, Frequency 29.14: Got Frequency %g\n", a->freq);
    }
  }


  a = BST_search(r, 10, .7 + .01);
  {
    if (a == NULL) {
      printf("Expected to find note with Bar 10, Index 0.71, Frequency 2489.02: Got NULL\n");
      checks++; tests++;;
    } else {
      succ += approx(a->freq, 2489.02, 0.01) ? 1 : 0;
      checks++; tests++;;
      if (succ != checks)
        printf("Expected to find note with Bar 10, Index 0.71, Frequency 2489.02: Got Frequency %g\n", a->freq);
    }
  }

   a = BST_search(r, 12, 0.2 + 0.01);
  {
    if (a == NULL) {
      succ++;
      checks++; tests++;;
    } else {
      checks++; tests++;;
      printf("Expected to NOT find note with Bar 12, Index 0.21, Frequency 4979+: Got Frequency %g\n", a->freq);
    }
  }

  if (succ != checks) {
    printf("\n** %d ** Errors encountered from harmonize\n", checks - succ);
    checks = succ;
  } else {
    printf("OWO Test 2 passed for harmonize.\n\n");
  }
  
  delete_BST(cp);
  delete_BST(r);

  printf("===============================\n");
  if (checks != tests) {
    printf("\n** %d ** Errors encountered from all tests\n", tests - succ);
    printf("Amodeth\n");
  } else {
    printf("\nAll tests passed! Yay maybe?\n");
  }
  
  return 0;
}