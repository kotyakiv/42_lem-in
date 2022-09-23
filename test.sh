#!/bin/bash

# This script generates 5 different random maps to test each case for the evaluation
# Generated maps are saved
# The number of lines required is compared with the line number obtained from the lem-in's output

for i in {1..5}; do
	./generator --flow-one > flow_1_$i.txt
	./generator --flow-ten > flow_10_$i.txt
	./generator --flow-thousand > flow_1000_$i.txt
	./generator --big > big_$i.txt
	./generator --big-superposition > big_sup_$i.txt
	sleep 1
done

wait

echo "flow_one results:"
for i in {1..5}; do
	EXP=$(cat flow_1_$i.txt | grep "lines required:" | tail -1 | awk '{print $NF}')
	GOT=$(cat flow_1_$i.txt | ./lem-in | grep "L" -c)
	DIFF=$(expr $GOT - $EXP)
	echo "expected: $EXP got: $GOT	/// diff: $DIFF"
done

echo "--------"
echo "flow_ten results:"
for i in {1..5}; do
	EXP=$(cat flow_10_$i.txt | grep "lines required:" | tail -1 | awk '{print $NF}')
	GOT=$(cat flow_10_$i.txt | ./lem-in | grep "L" -c)
	DIFF=$(expr $GOT - $EXP)
	echo "expected: $EXP got: $GOT	/// diff: $DIFF"
done

echo "--------"
echo "flow_thousand results:"
for i in {1..5}; do
	EXP=$(cat flow_1000_$i.txt | grep "lines required:" | tail -1 | awk '{print $NF}')
	GOT=$(cat flow_1000_$i.txt | ./lem-in | grep "L" -c)
	DIFF=$(expr $GOT - $EXP)
	echo "expected: $EXP got: $GOT	/// diff: $DIFF"
done

echo "--------"
echo "big results:"
for i in {1..5}; do
	EXP=$(cat big_$i.txt | grep "lines required:" | tail -1 | awk '{print $NF}')
	GOT=$(cat big_$i.txt | ./lem-in | grep "L" -c)
	DIFF=$(expr $GOT - $EXP)
	echo "expected: $EXP got: $GOT	/// diff: $DIFF"
done

echo "--------"
echo "big superposition:"
for i in {1..5}; do
	EXP=$(cat big_sup_$i.txt | grep "lines required:" | tail -1 | awk '{print $NF}')
	GOT=$(cat big_sup_$i.txt | ./lem-in | grep "L" -c)
	DIFF=$(expr $GOT - $EXP)
	echo "expected: $EXP got: $GOT	/// diff: $DIFF"
done




