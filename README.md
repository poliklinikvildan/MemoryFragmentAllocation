# Fragment Allocation Simulation

This repository contains a C++ program that simulates memory allocation and job scheduling using different allocation strategies, including Worst-Fit, Best-Fit, and First-Fit. The program reads a list of file fragments and a job table to allocate fragments to memory based on their size and the selected allocation strategy.

## Sorting and Its Effect on Allocation

Sorting the file fragments can significantly impact how different memory allocation strategies perform:

### Ascending Order (Smallest First)

- When fragments are sorted in ascending order based on their size, smaller fragments are allocated first.
- **First-Fit:** Small fragments are likely to find suitable memory blocks early, minimizing fragmentation.
- **Best-Fit:** Small fragments have a better chance of finding the best-fitting memory block, reducing fragmentation.
- **Worst-Fit:** Small fragments may lead to fragmentation issues as they might not fit well into larger available memory blocks.

### Descending Order (Largest First)

- Sorting fragments in descending order allocates larger fragments first.
- **First-Fit:** Larger fragments can consume available memory blocks quickly, leaving less space for smaller fragments.
- **Best-Fit:** Larger fragments may lead to fragmentation as smaller memory blocks won't fit.
- **Worst-Fit:** Larger fragments are more likely to find available memory blocks, potentially reducing fragmentation.

## Code Explanation

- The C++ program reads a list of file fragments and a job table, representing memory fragments and jobs to be executed.
- Memory allocation strategies (Worst-Fit, Best-Fit, and First-Fit) are implemented.
- Fragments are allocated to memory blocks based on the selected strategy and the size of available memory blocks.
- The program simulates job execution and memory allocation over a time period.
- The allocation results are printed, including memory states, job states, and allocation failures.
- The simulator has the capacity to track both successful and unsuccessful allocation scenarios.

## Usage

1. Compile the program using `g++ main.cpp -o main`.
2. Run the program using `./main`.


