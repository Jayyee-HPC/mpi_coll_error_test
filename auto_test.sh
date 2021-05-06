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
echo "**************Perform Reduce error tests*******************"

for ((i=0 ; i<8 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 3 $i
done
echo "**************END Reduce error tests*******************"

echo -e	
echo "**************Perform Scan error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 4 $i
done
echo "**************END Scan error tests*******************"

echo -e	
echo "**************Perform Scatter error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 5 $i
done
echo "**************END Scatter error tests*******************"

echo -e	
echo "**************Perform Scatterv error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 6 $i
done
echo "**************END Scatterv error tests*******************"

echo -e	
echo "**************Perform Igather error tests*******************"

for ((i=0 ; i<7 ; i++)); do
	echo -e	
	echo -e "\tTESTCASE $i"
	test_func $timeout $num_proc 7 $i
done
echo "**************END Igather error tests*******************"

echo "END AUTO TESTS."
