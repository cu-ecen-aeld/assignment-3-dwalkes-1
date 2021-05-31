#!/bin/sh

set -e
set -u


if [ $# -ne 2 ]
then
	echo "ERROR: Invalid Number of Arguments."
       	echo "Total number of arguments should be 2."
	echo "The order of the arguments should be:"
	echo "  1) Path to the file."
	echo "  2)String to be written in the specified file"
	exit 1
fi


WRITEFILE=$1
WRITESTR=$2

echo $WRITESTR > "$WRITEFILE"
