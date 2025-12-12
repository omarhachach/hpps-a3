#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

double* read_points(FILE *f, int* n_out, int *d_out) {
  int32_t n, d;

  // Read the dimensions
  if (fread(&n, sizeof(int32_t), 1, f) != 1) {
    return NULL;
  }
  if (fread(&d, sizeof(int32_t), 1, f) != 1) {
    return NULL;
  }

  *n_out = n;
  *d_out = d;

  // Allocate space for all the points
  double *points = malloc(n * d * sizeof(double));
  if (points == NULL) {
    return NULL;
  }

  // Read all the point data
  if (fread(points, sizeof(double), n * d, f) != (size_t)(n * d)) {
    free(points);
    return NULL;
  }

  return points;
}

int* read_indexes(FILE *f, int *n_out, int *k_out) {
  int32_t n, k;

  // Read n and k
  if (fread(&n, sizeof(int32_t), 1, f) != 1) {
    return NULL;
  }
  if (fread(&k, sizeof(int32_t), 1, f) != 1) {
    return NULL;
  }

  *n_out = n;
  *k_out = k;

  // Allocate space for indexes
  int *indexes = malloc(n * k * sizeof(int));
  if (indexes == NULL) {
    return NULL;
  }

  // Read the index data
  if (fread(indexes, sizeof(int), n * k, f) != (size_t)(n * k)) {
    free(indexes);
    return NULL;
  }

  return indexes;
}

int write_points(FILE *f, int32_t n, int32_t d, double *data) {
  // Write n and d first
  if (fwrite(&n, sizeof(int32_t), 1, f) != 1) {
    return 1;
  }
  if (fwrite(&d, sizeof(int32_t), 1, f) != 1) {
    return 1;
  }

  // Write all the point data
  if (fwrite(data, sizeof(double), n * d, f) != (size_t)(n * d)) {
    return 1;
  }

  return 0;
}

int write_indexes(FILE *f, int32_t n, int32_t k, int *data) {
  // Write n and k
  if (fwrite(&n, sizeof(int32_t), 1, f) != 1) {
    return 1;
  }
  if (fwrite(&k, sizeof(int32_t), 1, f) != 1) {
    return 1;
  }

  // Write the indexes
  if (fwrite(data, sizeof(int), n * k, f) != (size_t)(n * k)) {
    return 1;
  }

  return 0;
}
