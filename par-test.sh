TIMEFORMAT=%R

#unsat
for file in unsat/*
do
  time ./main "$file"
done

# sat
for file in sat/*
do
  time ./main "$file"
done
