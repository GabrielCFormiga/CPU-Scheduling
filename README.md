### C++ Implementation of CPU Scheduling Algorithms

In this repository, I implemented three CPU scheduling algorithms in C++: First-Come, First-Served (FCFS), Shortest Job Next (SJN), and Round Robin (RR time quantum = 2).

It is also important to note that these implementations are non-preemptive.

The focus was not on optimizing the code's asymptotic complexity, but the implementation of SJN uses a priority queue to select the next process to execute, and the FCFS implementation iterates over the process list in O(n) time. The implementations still maintain a reasonable performance.

### How to Run

1. Compile the C++ files with `g++ ./src/*.cpp -I ./include/ -o main`.
2. Run the compiled executable with `./main ./data/instance.txt`.