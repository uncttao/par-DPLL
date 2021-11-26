#unsat
for file in unsat/*
do
  cmake-build-release/par_DPLL < "$file"
done

# sat
for file in sat/*
do
  cmake-build-release/par_DPLL < "$file"
done
