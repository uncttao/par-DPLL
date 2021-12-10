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

![uuf50-218](https://github.com/uncttao/par-DPLL/blob/master/assets/uuf50-218.png)

#### uuf75-325 (75 variables and 325 clauses)

This is a more difficult set of problems (more variables and clauses) than the previous set of benchmarks.

![uuf75-325](https://github.com/uncttao/par-DPLL/blob/master/assets/uuf75-325.png)

We also implemented a cutoff scheme such that the solver would no longer fork new Cilk subroutines if the number of active literals decreases below certain numbers. This can be understood as an explicit granularity control to amortize the cost of creating new Cilk subroutines.

#### uuf50-218 Cutoff

#### at 10 variables

![uuf50-218-10](https://github.com/uncttao/par-DPLL/blob/master/assets/uuf50-218-10.png)

#### at 20 variables

![uuf50-218-20](https://github.com/uncttao/par-DPLL/blob/master/assets/uuf50-218-20.png)

#### uuf75-325 Cutoff

#### at 10 variables

![uuf75-325-10](https://github.com/uncttao/par-DPLL/blob/master/assets/uuf75-325-10.png)

#### at 20 variables

![uuf75-325-20](https://github.com/uncttao/par-DPLL/blob/master/assets/uuf75-325-20.png)

#### at 30 variables

![uuf75-325-30](https://github.com/uncttao/par-DPLL/blob/master/assets/uuf75-325-30.png)

### Evaluation

1. The scalability per UNSAT problem varies greatly. From the graph, we see that while some problems scale well, it is not so much for many other instances.

2. As the difficulty of the UNSAT problems increases, the scaling of the solver tends to improve.

3. Per the benchmark tested, the system ceases to provide further scaling beyond 32 degrees of parallelism (not shown). The scalability also starts to fall off near 32.

4. The cutoff scheme yields a slight increase in performance especially at higher parallelism for the uuf50-218 problem sets. There is not obvious difference, however, for the uuf75-325 problems.

### Comments

Due to the irregularity of (UN)SAT problems, it could be difficult for DPLL solvers to offer consistent speedup even using powerful frameworks such as Cilk. For example, a Cilk subroutine may be halted too soon because it encounters unsatisfiability rather quickly; in general, such behavior decreases scalability as the amount of individual subroutine work is too small to amortize the decent cost associated with parallelization (i.e. copying the entire formula for a new subroutine). Another blocker to scaling is due to that the current SAT solver has many sequential (or yet to be parallelized) parts allowing Amdahl's law to dominate.

In any case, it should be obvious that the more difficult the (UN)SAT problem is, the better scaling results we observe. This is because the cost associated with  parallelization is more amortized as individual subroutine work becomes more complex.

The reason that the system fails to scale (or suffer from performance regression) beyond 32 degrees of parallelism has to do with the causes mentioned in the previous discussions as well as the underlying `AMD EPYC 7313` architecture. As the machine has only 16 x 2 = 32 threads per socket, moving beyond 32 cores carries an extra cost of communication.

In addition, we observe that the cutoff scheme is useful and allows for slight increase in performance especially at greater degrees of parallelism. However, increasing cutoff >= 30 has no more effect on performance. The irregularities of (UN)SAT problems make it difficult to ascertain the optimal cutoff parameter. This optimal parameter is also likely different for different subclasses of (UN)SAT problems, but they are currently treated the same in this regard. In the future, a dynamic, runtime-profiling-based cutoff scheme should be a better option.

### Todo

Optimize the implementation for both single-thread and multi-thread.

### Pull Request

Welcomed!
