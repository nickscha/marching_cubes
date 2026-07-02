# marching_cubes
C89, single header, nostdlib marching cubes algorithm

This is currently a 'naive' implementation focussing only on the marching cubes triangulation part and does not cover sophisticated LOD stiching and transition like transvoxel yet.

For more information please look at the "marching_cubes.h" file or take a look at the "examples" or "tests" folder.

> [!WARNING]
> THIS PROJECT IS A WORK IN PROGRESS! ANYTHING CAN CHANGE AT ANY MOMENT WITHOUT ANY NOTICE! USE THIS PROJECT AT YOUR OWN RISK!

<p align="center">
  <a href="https://github.com/nickscha/marching_cubes/releases">
    <img src="https://img.shields.io/github/v/release/nickscha/marching_cubes?style=flat-square&color=blue" alt="Latest Release">
  </a>
  <a href="https://github.com/nickscha/marching_cubes/releases">
    <img src="https://img.shields.io/github/downloads/nickscha/marching_cubes/total?style=flat-square&color=brightgreen" alt="Downloads">
  </a>
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square" alt="License">
  </a>
  <img src="https://img.shields.io/badge/Standard-C89-orange?style=flat-square" alt="C Standard">
  <img src="https://img.shields.io/badge/nolib-nostdlib-lightgrey?style=flat-square" alt="nostdlib">
</p>

## **Features**
- **C89 compliant** — portable and legacy-friendly  
- **Single-header API** — just include `marching_cubes.h`  
- **nostdlib** — no dependency on the C Standard Library  
- **Minimal binary size** — optimized for small executables  
- **Cross-platform** — Windows, Linux, MacOs 
- **Strict compilation** — built with aggressive warnings & safety checks  

## Quick Start

Download or clone marching_cubes.h and include it in your project.

```C
#include "marching_cubes.h" /* Marching Cubes */

/* Simple flat plane density grid */
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

#define DIM 129
#define MAX_TRIANGLES (DIM * DIM * DIM * 5)

int main() {
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

    if (triangle_count < 1) {
      return 1;
    }    

    return 0;
}
```

## "nostdlib" Motivation & Purpose

nostdlib is a lightweight, minimalistic approach to C development that removes dependencies on the standard library. The motivation behind this project is to provide developers with greater control over their code by eliminating unnecessary overhead, reducing binary size, and enabling deployment in resource-constrained environments.

Many modern development environments rely heavily on the standard library, which, while convenient, introduces unnecessary bloat, security risks, and unpredictable dependencies. nostdlib aims to give developers fine-grained control over memory management, execution flow, and system calls by working directly with the underlying platform.

### Benefits

#### Minimal overhead
By removing the standard library, nostdlib significantly reduces runtime overhead, allowing for faster execution and smaller binary sizes.

#### Increased security
Standard libraries often include unnecessary functions that increase the attack surface of an application. nostdlib mitigates security risks by removing unused and potentially vulnerable components.

#### Reduced binary size
Without linking to the standard library, binaries are smaller, making them ideal for embedded systems, bootloaders, and operating systems where storage is limited.

#### Enhanced performance
Direct control over system calls and memory management leads to performance gains by eliminating abstraction layers imposed by standard libraries.

#### Better portability
By relying only on fundamental system interfaces, nostdlib allows for easier porting across different platforms without worrying about standard library availability.
