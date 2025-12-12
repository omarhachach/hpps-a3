#include "bruteforce.h"
#include "util.h"
#include <stdlib.h>
#include <assert.h>

int* knn(int k, int d, int n, const double *points, const double* query) {
  // Allocate result array
  int* result = malloc(k * sizeof(int));
  if (result == NULL) {
    return NULL;
  }

  // Initialize with -1 (no neighbors yet)
  for (int i = 0; i < k; i++) {
    result[i] = -1;
  }

  // Check every point
  for (int i = 0; i < n; i++) {
    insert_if_closer(k, d, points, result, query, i);
  }

  return result;
}

