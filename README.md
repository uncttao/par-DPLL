# par-DPLL
A (parallel) implementation of the classic DPLL algorithm using Cilk

### Reference

DPLL algorithm:  https://en.wikipedia.org/wiki/dpll_algorithm

Cilk: https://github.com/OpenCilk

Benchmark: https://www.cs.ubc.ca/~hoos/SATLIB/benchm.html

### Benchmark

Benchmark focuses only on UNSAT problems (since SAT instances tend to finish very/too fast).

The hardware used for the benchmark is https://its.unc.edu/research-computing/longleaf-cluster/.

The CPU model is `AMD EPYC 7313 16-Core Processor`.

![uuf50-218](https://github.com/uncttao/par-DPLL/blob/master/SATLIB-Benchmark%20Problems%2C%20uuf50-218%2C%20First%20100.png)

![uuf50-218-avg](https://github.com/uncttao/par-DPLL/blob/master/SATLIB-Benchmark%20Problems%2C%20uuf50-218%2C%20First%20100.avg.png)

![uuf75-325](https://github.com/uncttao/par-DPLL/blob/master/SATLIB-Benchmark%20Problems%2C%20uuf75-325%2C%20First%20100.png)

![uuf75-325-avg](https://github.com/uncttao/par-DPLL/blob/master/SATLIB-Benchmark%20Problems%2C%20uuf75-325%2C%20First%20100.avg.png)

### Evaluation

1) As the difficulty of the UNSAT problems increases, the scaling of the solver tends to improve.

2) Per the benchmark tested, the system ceases to provide further scaling beyond 32 degrees of parallelism (now shown in the graphs).

### Comments

Due to the irregularity of (UN)SAT problems, it could be difficult for DPLL solvers to offer consistent speedup even using powerful frameworks such as Cilk. This is also due to the fact that the current implementation is suboptimal.

### Todo

Optimize the implementation for both single-thread and multi-thread.
