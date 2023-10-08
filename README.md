Output is a simulation of memory allocation using different strategies (Worst-Fit, Best-Fit, and First-Fit) over time. 

Section Headers: These headers indicate which memory allocation strategy is currently being simulated.

Time: This shows the simulation time, indicating the step or iteration in the simulation.

Allocation Succeeded for Fragment: These lines indicate that memory fragments have been successfully allocated at the current time step. The program is reporting that it was able to allocate fragments.

Memory State: This line shows the current state of the memory after allocation or deallocation. It represents the memory blocks and their sizes.

Job State: This line indicates the state of the job at the current time step. In this case, it's in the "Sleep" state.

Allocation Failed for Fragment: These lines indicate that memory fragments could not be allocated at the current time step. The program is reporting that it failed to allocate fragments due to insufficient available memory.

## Usage

1. Compile the program using `g++ main.cpp -o main`.
2. Run the program using `./main`.


