#!/bin/bash

INPUTS_PATH="test/input"
BIN_PATH="build"
BIN=$BIN_PATH/main
REPORT=report
declare -i nota
declare -i quality
((nota = 0))
((quality = 0))

rm -f $REPORT

#test existance
if [ ! -x $BIN ]
then
   echo "# Executable $BIN not found."
   continue
fi

check_if_command_exists () {
	type $1 >/dev/null 2>&1 || { echo -e >&2 "\033[41mI require $1 but it's not installed. Please install it and try again. Aborting.\033[40m"; exit 1; }
}

for INPUT in `ls -1 $INPUTS_PATH/s*.iks`
do
	EXPECTED_ERROR=`head -n1 $INPUT | awk '{ print $2 }'`
	EXPECTED_ERROR_CODE=`grep "$EXPECTED_ERROR " $INPUTS_PATH/errors.h | awk '{ print $3 }'`
	$BIN < $INPUT > /dev/null 2> /dev/null #$REPORT
	GOT_ERROR_CODE=$?
	
	#detect segfault
	if [ $GOT_ERROR_CODE -eq 139 ]
	then
		R="$INPUT causes a segfault (exit code is $GOT_ERROR_CODE)"
		echo $R
		echo $R >> $REPORT
		continue
	fi
	
	#check with valgrind
	check_if_command_exists valgrind
	TEMP_FILE="/tmp/e4-$RANDOM.tmp"
	rm -f $TEMP_FILE
	valgrind $BIN < $INPUT 2>> $TEMP_FILE >> $TEMP_FILE
	INVALID_WRITES=`cat $TEMP_FILE | grep "Invalid write" | wc -l`
	INVALID_READS=`cat $TEMP_FILE | grep "Invalid read" | wc -l`
	CONDITIONAL=`cat $TEMP_FILE | grep "Conditional" | wc -l`
	BYTES_LOST=`cat $TEMP_FILE | grep "definitely lost:" | awk '{ print $4}' | sed "s/,//g"`
	rm $TEMP_FILE
	CODE_CORRECT="(w,r,c,l)=($INVALID_WRITES,$INVALID_READS,$CONDITIONAL,$BYTES_LOST)"
	if [ $INVALID_WRITES -eq 0 ]
	then
		((quality = $quality + 1))
	fi
	if [ $INVALID_READS -eq 0 ]
	then
		((quality = $quality + 1))
	fi
	if [ $CONDITIONAL -eq 0 ]
	then
		((quality = $quality + 1))
	fi
	if [ $BYTES_LOST -eq 0 ]
	then
		((quality = $quality + 1))
	fi
	
	#analyze the result and report
	if [ $GOT_ERROR_CODE -ne $EXPECTED_ERROR_CODE ]
	then
		N=`grep " $GOT_ERROR_CODE " $INPUTS_PATH/errors.h | awk '{ print $2 }'`
		R="$INPUT expects a $EXPECTED_ERROR($EXPECTED_ERROR_CODE), but we got a $N($GOT_ERROR_CODE) $CODE_CORRECT"
		echo $R
		echo $R >> $REPORT
	else
		((nota = $nota + 1))
		R="$INPUT $EXPECTED_ERROR okay $CODE_CORRECT"
		echo $R
		echo $R >> $REPORT
	fi
done
NTESTES=`ls -1 $INPUTS_PATH/s*.iks | wc -l`
NOTA_FINAL=`echo "$nota / $NTESTES * 10" | bc -l`
QUALIDADE_FINAL=`echo "($quality / ($NTESTES * 4)) * 10" | bc -l`
R="$NOTA_FINAL $QUALIDADE_FINAL"
echo $R
echo $R >> $REPORT

