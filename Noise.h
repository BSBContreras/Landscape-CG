#ifndef NOISE_CLASS_H
#define NOISE_CLASS_H

#include <math.h>

/* Function to linearly interpolate between a0 and a1
 * Weight w should be in the range [0.0, 1.0]
 */
float interpolate(float a0, float a1, float w);

typedef struct {
    float x, y;
} vector2;

// Computes the dot product of the distance and gradient vectors.
float dotGridGradient(int ix, int iy, float x, float y);

// Compute Perlin noise at coordinates x, y
float perlin(float x, float y);

#endif