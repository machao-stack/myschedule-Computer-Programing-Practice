#!/bin/bash
# Test Script - Automated Testing of Schedule Management Software
echo "=== compiling ==="
g++ main.cpp src/Task.cpp -I include -o myshedule
if [ $? -eq 0 ]; then
	echo "successfully compiled"
else
	echo "compiling failed"
	exit 1
fi

echo ""
echo "=== clean up old data ==="
rm -f task.txt

echo ""
echo "=== sign up testing(correct passwords) ==="
echo -e "admin\n123456" | ./myschedule showtask

echo ""
echo "=== implement add task test= ==="
echo -e "admin\n123456" | ./myschedule addtask "test task1" "14:00"
echo -e "admin\n123456" | ./myschedule addtask "test task2" "15:00"

echo ""
echo " ===show task test=== "
echo -e "admin\n123456" | ./myschedule showtask

echo ""
echo " === delete task test ==="
echo -e "admin\n123456" | ./myschedule deltask 1
echo ""
echo "=== test displaying tasks after deletion ==="
echo -e "admin\n123456" | ./myschedule showtask
echo ""
echo "=== interactive mode test (auto exit after running for 5 seconds) ==="
echo -e "admin\n123456\nshowtask\nexit" | ./myschedule run
echo ""
echo "=== all tests finished ==="
