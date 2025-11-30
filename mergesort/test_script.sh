#!/bin/bash
echo "Generate test arrays if not found"

sizes=(5 10 500 2000 5000)

for size in "${sizes[@]}"; do
    if [ ! -f data/array_${size}.txt ]; then
        echo "Generating array of size $size"
        python3 random_array.py $size > data/array_${size}.txt
    fi
done

echo "Compiling..."
make

echo "Running benchmarks..."

for size in "${sizes[@]}"; do
    echo "* * * * * * * ${size} elements"
    cal_t=$((time bin/seq_mergesort data/array_${size}.txt) 2>&1 > /dev/null | grep real | awk '{print $2}')
    echo "Sequential: $cal_t"

    cal_t=$((time bin/omp_mergesort data/array_${size}.txt) 2>&1 > /dev/null | grep real | awk '{print $2}')
    echo "OpenMP: $cal_t"

    cal_t=$((time bin/pthread_mergesort data/array_${size}.txt) 2>&1 > /dev/null | grep real | awk '{print $2}')
    echo "Pthread: $cal_t"

    cal_t=$((time mpirun -np 4 bin/mpi_mergesort data/array_${size}.txt) 2>&1 > /dev/null | grep real | awk '{print $2}')
    echo "MPI (4 processes): $cal_t"
    echo
done

