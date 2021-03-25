if [ $# -ne 1 ]; then
	echo "Missing argument: $0 [command]"
	exit -1
else
	gcc -o ./test/$1_test.out ./source/test_$1.c -lpthread

	echo "Evaluation start"
	echo "Target: $1"

	for (( i=0; i<5; i++ ));
	do
		echo "Loop $i"
		time ./test/$1_test.out
		echo ""
	done

	echo ""
	echo "Evaluation for $1 complete."
fi
