/* marching_cubes.h - v0.1 - public domain data structures - nickscha 2026

C89, single header, nostdlib marching cubes algorithm

This Test class defines cases to verify that we don't break the excepted behaviours in the future upon changes.

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/
#include "../marching_cubes.h" /* Marching Cubes Algorithm   */
#include "stdio.h"             /* printf for testing purpose */
#include "stdlib.h"            /* Malloc for testing purpose */

#define DIM 129
#define MAX_TRIANGLES (DIM * DIM * DIM * 5)

static void initialize_density_grid(float *grid, int grid_dimensions, float grid_total_size, marching_cubes_vec3 grid_center)
{
  int x, y, z;

  for (z = 0; z < grid_dimensions; ++z)
  {
    /*
    float wz = (((float)z / ((float)grid_dimensions - 1.0f)) - 0.5f) * grid_total_size + grid_center.z;
    */

    for (y = 0; y < grid_dimensions; ++y)
    {
      float wy = (((float)y / ((float)grid_dimensions - 1.0f)) - 0.5f) * grid_total_size + grid_center.y;

      for (x = 0; x < grid_dimensions; ++x)
      {
        /* Simple Flat plane */
        float final_density = wy + 20.0f;

        grid[z * grid_dimensions * grid_dimensions + y * grid_dimensions + x] = final_density;
      }
    }
  }
}

int main(void)
{
  float *density_grid;

  marching_cubes_context ctx = {0};

  marching_cubes_triangle *triangle_buffer;
  int triangle_count = 0;

  density_grid = malloc(sizeof(float) * DIM * DIM * DIM);

  if (!density_grid)
  {
    return 1;
  }

  ctx.dim_size = DIM;
  ctx.grid_size = 100.0f; /* Total world-space size of the chunk */
  ctx.iso_level = 0.0f;   /* The "surface" is where density is 0 */
  ctx.chunk_coord.x = 0.0f;
  ctx.chunk_coord.y = 0.0f;
  ctx.chunk_coord.z = 0.0f;
  ctx.density_grid = density_grid;
  ctx.transition_mask = 0;
  ctx.lod_level = 0;

  triangle_buffer = malloc(sizeof(marching_cubes_triangle) * MAX_TRIANGLES);

  if (!triangle_buffer)
  {
    return 1;
  }

  /* Fill density grid */
  initialize_density_grid(density_grid, DIM, ctx.grid_size, ctx.chunk_coord);

  /* Calculate Marching Cubes Triangles from density grid */
  marching_cubes_generate(&ctx, triangle_buffer, &triangle_count);

  printf("[marching_cubes] triangle_count: %d\n", triangle_count);

  return 0;
}

/*
   -----------------------------------------------------------------------------
   This software is available under 2 licenses -- choose whichever you prefer.
   ------------------------------------------------------------------------------
   ALTERNATIVE A - MIT License
   Copyright (c) 2026 nickscha
   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   ------------------------------------------------------------------------------
   ALTERNATIVE B - Public Domain (www.unlicense.org)
   This is free and unencumbered software released into the public domain.
   Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
   software, either in source code form or as a compiled binary, for any purpose,
   commercial or non-commercial, and by any means.
   In jurisdictions that recognize copyright laws, the author or authors of this
   software dedicate any and all copyright interest in the software to the public
   domain. We make this dedication for the benefit of the public at large and to
   the detriment of our heirs and successors. We intend this dedication to be an
   overt act of relinquishment in perpetuity of all present and future rights to
   this software under copyright law.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   ------------------------------------------------------------------------------
*/
