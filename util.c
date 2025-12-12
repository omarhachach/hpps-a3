#include "util.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>

double distance(int d, const double *x, const double *y) {
  double sum = 0.0;
  for (int i = 0; i < d; i++) {
    double diff = x[i] - y[i];
    sum += diff * diff;
  }
  return sqrt(sum);
}

int insert_if_closer(int k, int d,
                     const double *points, int *closest, const double *query,
                     int candidate) {
  // Calculate distance from candidate to query
  const double *candidate_point = &points[candidate * d];
  double candidate_dist = distance(d, candidate_point, query);

  // Find where to insert (if at all)
  int insert_pos = -1;

  for (int i = 0; i < k; i++) {
    if (closest[i] == -1) {
      // Empty slot, just insert here
      insert_pos = i;
      break;
    }

    // Get distance of current neighbor
    const double *neighbor_point = &points[closest[i] * d];
    double neighbor_dist = distance(d, neighbor_point, query);

    if (candidate_dist < neighbor_dist) {
      // Found where to insert
      insert_pos = i;
      break;
    }
  }

  // If no position found, candidate is not close enough
  if (insert_pos == -1) {
    return 0;
  }

  // Shift elements down to make room
  for (int i = k - 1; i > insert_pos; i--) {
    closest[i] = closest[i - 1];
  }

  // Insert the candidate
  closest[insert_pos] = candidate;

  return 1;
}
