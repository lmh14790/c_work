#!/bin/bash
IFS=''
set foo bar bam
echo \$@ = "$@"
echo \$* = "$*"
unset IFS 
echo \$@ = "$@"
echo \$* = "$*"
unset  foo
echo foo
echo "test param script===="
salutation="HELLO"
echo $salutation
echo "the script $0 is now running"
echo "the second parameter was $2"
echo "the first parameter was $1"
echo "the parameter list was $*"
echo "the user's home directrory is $HOME"
echo "please enter a new greeting"
read salutation

echo $salutation
echo "the script $0 is now complete"
exit 0