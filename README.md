Cache Simulator

Overview

This Cache Simulator is a C++ program designed to simulate the behavior of a cache memory. It takes a sequence of memory addresses requested by the CPU and simulates hits and misses in the cache based on the provided configuration parameters.

Features

Simulates cache behavior with configurable memory and cache sizes.
Processes memory addresses and determines cache hits or misses.
Outputs detailed statistics about cache performance.
Requirements

C++ Compiler (e.g., GCC, Clang)
Standard C++ Libraries
Compilation

To compile the Cache Simulator, use the following command:

g++ -o cache_sim cache_sim.cpp

Usage

Run the simulator with the following command:

./cache_sim <mem_size> <cache_size> <access_filename>

mem_size: Size of the memory in blocks (must be a power of 2).
cache_size: Size of the cache in blocks (must be a power of 2 and a factor of mem_size).
access_filename: Filename containing a list of memory block addresses to access.
Input File Format

The input file (access_filename) should contain a list of memory addresses (block addresses), each separated by a space.

Example:

1 3 4 1 3 1

Output

The simulator generates an output file named hitmiss-out.txt, containing the address and whether there was a hit or a miss for each memory access. It also reports the overall hit and miss percentage.

Example

Command:

./cache_sim 4 2 accesslist.txt

Output (hitmiss-out.txt):

1 Miss
3 Miss
4 Miss
1 Miss
3 Miss
1 Hit
Out of 6 memory accesses, there was a 16% cache hit rate and an 83% miss rate.

Two-Level Cache Simulator

Overview

This C++ application simulates a two-tier cache system, encompassing both L1 and L2 caches, and handles multi-word blocks in each cache line. It processes a series of memory address requests, emulating the behavior of these caches and categorizing the types of cache misses encountered.

Compilation Guide

To compile this simulator, ensure you have a C++ compiler like g++ available.

Compile Command:
In the directory with cache_sim.cpp, execute:

g++ -o cache_simBonus cache_simBonus.cpp

Executable Creation:
This command will create an executable named cache_sim.
Execution Guide

Run the simulator with the command in the following structure:

./cache_simBonus mem_size cache_size_L1 cache_size_L2

<memory_size>: Total size of memory in blocks.
<L1_cache_size>: Size of the L1 cache in blocks.
<L2_cache_size>: Size of the L2 cache in blocks.

Example Usage:

./cache_simBonus 1024 64 256

Input Expectations

The simulator expects an input file named accesslist.txt in the same directory. This file should list the memory addresses that the simulator will access.

Output Details

The simulator outputs its results to hitmiss-out.txt, detailing each memory access as a hit or miss. Additionally, it prints a summary of access statistics, including the number of hits, misses, and classifications of misses, to the standard output.

Current Limitations and Bugs

Block Size: The block size is preset to 4 words. Adjustments for dynamic block sizes are not currently supported.
Cache Design: The cache is implemented in a straightforward direct-mapped manner. More intricate designs like set-associative are not included.
Eviction Strategy: There is no implementation of specific strategies like LRU or FIFO for cache eviction.
Input Flexibility: The simulator is hardcoded to read from accesslist.txt and does not support variable input files.
Handling Large Data Sets: The program may not be optimized for extremely large memory sizes and could become less efficient.
Notes

Ensure accesslist.txt is properly placed and formatted in the executable's directory.
The parameters provided when running the program should adhere to the stated constraints (e.g., the size of the caches should be proportional to the size of the memory).