#!/bin/bash

echo "BEGIN AUTO TESTS."

num_proc=8
timeout=10

# test function
function test_func(){
	#mpirun --timeout $1 -np $2 ./prog $3 $4
	env MPIEXEC_TIMEOUT=$1 /home/jayyee/temp/mpich/build/_inst/bin/mpiexec -np $2 ./prog $3 $4
}

echo -e	
echo "**************Perform Bcast error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 0 $i
done
echo "**************END Bcast error tests*******************"

echo -e	
echo "**************Perform Exscan error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 1 $i
done
echo "**************END Exscan error tests*******************"

echo -e	
echo "**************Perform Gather error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 2 $i
done
echo "**************END Gather error tests*******************"

echo -e	
echo "**************Perform Gatherv error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 3 $i
done
echo "**************END Gatherv error tests*******************"

echo -e	
echo "**************Perform Reduce error tests*******************"

for ((i=0 ; i<8 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 4 $i
done
echo "**************END Reduce error tests*******************"

echo -e	
echo "**************Perform Scan error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 5 $i
done
echo "**************END Scan error tests*******************"

echo -e	
echo "**************Perform Scatter error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 6 $i
done
echo "**************END Scatter error tests*******************"

echo -e	
echo "**************Perform Scatterv error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 7 $i
done
echo "**************END Scatterv error tests*******************"

echo -e	
echo "**************Perform Allgather error tests*******************"

for ((i=0 ; i<6 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 8 $i
done
echo "**************END Allgather error tests*******************"

echo -e	
echo "**************Perform Allgatherv error tests*******************"

for ((i=0 ; i<6 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 9 $i
done
echo "**************END Allgatherv error tests*******************"

echo -e	
echo "**************Perform Allreduce error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 10 $i
done
echo "**************END Allreduce error tests*******************"

echo -e	
echo "**************Perform Alltoall error tests*******************"

for ((i=0 ; i<6 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 11 $i
done
echo "**************END Alltoall error tests*******************"

echo -e	
echo "**************Perform Alltoallv error tests*******************"

for ((i=0 ; i<6 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 12 $i
done
echo "**************END Alltoallv error tests*******************"

echo -e	
echo "**************Perform Alltoallw error tests*******************"

for ((i=0 ; i<6 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 13 $i
done
echo "**************END Alltoallw error tests*******************"


echo -e	
echo "**************Perform Ibcast error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 14 $i
done
echo "**************END IBcast error tests*******************"

echo -e	
echo "**************Perform IExscan error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 15 $i
done
echo "**************END IExscan error tests*******************"

echo -e	
echo "**************Perform IGather error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 16 $i
done
echo "**************END IGather error tests*******************"

echo -e	
echo "**************Perform IGatherv error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 17 $i
done
echo "**************END IGatherv error tests*******************"

echo -e	
echo "**************Perform IReduce error tests*******************"

for ((i=0 ; i<8 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 18 $i
done
echo "**************END IReduce error tests*******************"

echo -e	
echo "**************Perform IScan error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 19 $i
done
echo "**************END IScan error tests*******************"

echo -e	
echo "**************Perform IScatter error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 20 $i
done
echo "**************END IScatter error tests*******************"

echo -e	
echo "**************Perform IScatterv error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 21 $i
done
echo "**************END IScatterv error tests*******************"

echo -e	
echo "**************Perform IAllgather error tests*******************"

for ((i=0 ; i<6 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 22 $i
done
echo "**************END IAllgather error tests*******************"

echo -e	
echo "**************Perform IAllgatherv error tests*******************"

for ((i=0 ; i<6 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 23 $i
done
echo "**************END IAllgatherv error tests*******************"

echo -e	
echo "**************Perform IAllreduce error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 24 $i
done
echo "**************END IAllreduce error tests*******************"

echo -e	
echo "**************Perform IAlltoall error tests*******************"

for ((i=0 ; i<6 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 25 $i
done
echo "**************END IAlltoall error tests*******************"

echo -e	
echo "**************Perform IAlltoallv error tests*******************"

for ((i=0 ; i<6 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 26 $i
done
echo "**************END IAlltoallv error tests*******************"

echo -e	
echo "**************Perform IAlltoallw error tests*******************"

for ((i=0 ; i<6 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 27 $i
done
echo "**************END IAlltoallw error tests*******************"

echo "END AUTO TESTS."
