#unsat
for file in unsat/*
do
  cmake-build-debug/par_DPLL < "$file"
done

# sat
for file in sat/*
do
  cmake-build-debug/par_DPLL < "$file"
done
