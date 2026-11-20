# Memory and Matrix Multiply

For my topic I choose to focus on how we can use our knowledge of computer
systems to design and reason about faster algorithms.
In particular, matrix multiply.
The two optimizations I am focusing on are changing the loop order and tiling.
Importantly, none of these change how many arithemetic operations
are performed, only the order of operations and the memory access patterns.
In the end, I only included the differences in loop order in the presentation due to timing constraints (also it had a much smaller effect in my local experiments). 

## 1. Loop order

The change in performace in going from loop order ijk to ikj is about
7-8x on my machine.
The main reason for this is that we store matrices in row-major order,
so each iteration of the innermost loop of the ijk algorithm increments
it jumps to a new row of B which likely causes a read from slow memory 
every time.
On the other hand, with ikj, the innermost loop goes through B one row
at a time, and so takes advantage of 
those elements being stored contiguously

## 2. Tiling

In effect, tiling is just block matrix multiply and the idea is to reuse
those elements while they are in the fast memory instead of reading
and writing back and forth as many times.
I looked it up and my laptop has 128KB of cache and so I focused on
using tiles of size 64 (since that allows for all 3 matrices to fit).
In my experiements this was usually the fastest tile, but not always.
Tiling also had a much smaller effect on the runtime at most making
the algorithms about 25% faster (above the ikj algorithm).

# Building and running

### Requirements
- A C compiler (for example, GCC or Clang)
- `make`

Build the executable:

```sh
make
```

This creates `./matmul`. To run all three algorithms use:

```sh
make run N=1024 T=64
```

This runs them with 1024 × 1024 matrices, using a tile size of 64 for the tiled version.
To run multiple tests at once, use

```sh
make test SIZES="512 768 960 1024" TILES="16 32 64 128"
```

You can also modify the Makefile instead of passing the arguements
through the command line.
Finally, to test a single algorithm do the following:

```sh
make test-ijk SIZES="512 1024"
make test-ikj SIZES="512 1024 2048"
make test-tiled SIZES="512 1024" TILES="32 64 128"
```

Or

```sh
./matmul ijk 512
./matmul ikj 512
./matmul tiled 512 64
```

As a warning, the ijk algorithm is quite slow for large sized matrices,
so I don't recommend testing it on anything larger than 1024 sized
matrices.