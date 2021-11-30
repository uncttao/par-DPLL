TIMEFORMAT=%R

#unsat
for file in unsat/*
do
  ./main "$file"
done

# sat
for file in sat/*
do
  ./main "$file"
done
