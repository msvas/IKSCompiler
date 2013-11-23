#!/bin/bash

INPUTS_PATH="."
BIN_PATH="../../build"
BIN=$BIN_PATH/main

# test program existence
if [ ! -x $BIN ]
then
	echo -e >&2 "\033[41mExecutable $BIN not found. Aborting.\033[40m"
	exit 1
fi

check_if_command_exists () {
	type $1 >/dev/null 2>&1 || { echo -e >&2 "\033[41mI require $1 but it's not installed. Please install it and try again. Aborting.\033[40m"; exit 1; }
}

# create a log file with a timestamp
logfile=$BIN_PATH/summary_$(date +"%Y%m%d_%H%M%S")

for input in `ls -1 $INPUTS_PATH/e*.iks`
do
	echo "------------------------------------------------------------------------------" >> $logfile
	echo $input >> $logfile
	echo "------------------------------------------------------------------------------" >> $logfile
	# check with valgrind
	valgrind --leak-check=yes --track-origins=yes $BIN < $input &>> $logfile

	#detect segfault
	got_error_code=$?
	if [ $got_error_code -eq 139 ]
	then
		R="$input causes a segfault (exit code is $got_error_code)"
		echo $R
		echo $R >> $logfile
		continue
	fi
done

echo -e "\e[91mExecution logs saved in $logfile\e[0m"

