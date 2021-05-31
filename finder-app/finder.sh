#!/bin/sh

set -e
set -u

if [ $# -ne 2 ]
then
	echo "ERROR: Invalid Number of Arguments."
       	echo "Total number of arguments should be 2."
       	echo "The order of the arguments should be:"
	echo "   1)File Directory Path."
       	echo "   2)String to be searched in the specified directory path."
	exit 1
fi

FILESDIR=$1
SEARCHSTR=$2


#The filesdir is in quotes because if the directory path consists of spaces, then variable substitution will consider it as multiple argument.
#The quotes signify that the entire string in filesdir is a single string.
#This issue can also be resolved by using double square brackets i.e [[ ]] instead of using quotes.
if [ ! -d "$FILESDIR" ]
then
	echo -e "ERROR: The specified path is not a directory. \n"
	exit 1
fi

FILE_COUNT=$(find "$FILESDIR" -type f | wc -l)
STRING_COUNT=$(grep -ro "$SEARCHSTR" "$FILESDIR" | wc -l)

echo File Directory Path: $FILESDIR
echo String to be searched in the specified directory path: $SEARCHSTR
echo The number of files are $FILE_COUNT and the number of matching lines are $STRING_COUNT including all the subdirectories in the specified directory.
