# par-DPLL

A (parallel) implementation of the classic DPLL algorithm using Cilk

### Reference

DPLL algorithm:  https://en.wikipedia.org/wiki/dpll_algorithm

Cilk: https://github.com/OpenCilk

Benchmark: https://www.cs.ubc.ca/~hoos/SATLIB/benchm.html

### Usage

1. Build or install Cilk into `../../build` (or any directory, but the path in `compile.sh` needs to be changed).
2. Modify and turn on desired features in `system.h`. Typicall for benchmarks, just use `TIMING`. For solver only, just
   use `SHOW_RESULT`.
3. Run `compile.sh`.
4. To run the benchmarks, download benchmark files and put them in `unsat` and `sat` directories. Then
   run `benchmark.sh`.
5. To run the solver, use `./main [path to the CNF file]`.

### Benchmark

The benchmark focuses only on UNSAT problems (since SAT instances tend to finish very/too fast).

The hardware used for the benchmark is https://its.unc.edu/research-computing/longleaf-cluster/.

The CPU model is `AMD EPYC 7313 16-Core Processor`.

The benchmark only accounts for the DPLL *solving* time (not parsing time and etc.).

#### uuf50-218 (50 variables and 218 clauses)

![uuf50-218](https://github.com/uncttao/par-DPLL/blob/master/assets/SATLIB-Benchmark%20Problems%2C%20uuf50-218%2C%20First%20100.png)

![uuf50-218-avg](https://github.com/uncttao/par-DPLL/blob/master/assets/SATLIB-Benchmark%20Problems%2C%20uuf50-218%2C%20First%20100.avg.png)

#### uuf75-325 (75 variables and 325 clauses)

This is a more difficult set of problems (more variables and clauses) than the previous set of benchmarks.

![uuf75-325](https://github.com/uncttao/par-DPLL/blob/master/assets/SATLIB-Benchmark%20Problems%2C%20uuf75-325%2C%20First%20100.png)

![uuf75-325-avg](https://github.com/uncttao/par-DPLL/blob/master/assets/SATLIB-Benchmark%20Problems%2C%20uuf75-325%2C%20First%20100.avg.png)

We also implemented a cut-off scheme such that the solver would no longer fork new Cilk subroutines if the number of active literals decrease below certain numbers. This can be understood as an explicit grainularity control to amortize the cost of creating new Cilk subroutines.

#### uuf50-218 Cutoff

#### at 10 variables

![uuf50-218-10](https://github.com/uncttao/par-DPLL/blob/master/assets/50-10.png)

#### at 20 variables

![uuf50-218-20](https://github.com/uncttao/par-DPLL/blob/master/assets/50-20.png)

#### uuf75-325 Cutoff

#### at 10 variables

![uuf75-325-10](https://github.com/uncttao/par-DPLL/blob/master/assets/75-10.png)

#### at 20 variables

![uuf75-325-20](https://github.com/uncttao/par-DPLL/blob/master/assets/75-20.png)

### Evaluation

1. The scalability per UNSAT problem varies greatly. From the graph, we see that while some problems scale well, it is not so much for many other instances.

2. As the difficulty of the UNSAT problems increases, the scaling of the solver tends to improve.

3. Per the benchmark tested, the system ceases to provide further scaling beyond 32 degrees of parallelism (not shown). The scalability also starts to fall off near 32.

4. The cutoff scheme has a non-neglible effect on scalability.

### Comments

Due to the irregularity of (UN)SAT problems, it could be difficult for DPLL solvers to offer consistent speedup even using powerful frameworks such as Cilk. This is also due to the fact that the current implementation is suboptimal.

### Todo

Optimize the implementation for both single-thread and multi-thread.

### Pull Request

Welcomed!
