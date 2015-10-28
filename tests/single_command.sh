#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"

echo "SINGLE COMMAND TEST"
echo "------------------"
{
    echo "ls "
    echo "ls ."
    echo "ls -a"
    echo "ls -a bin/ src/"
    echo "git status"
    echo "lscpu"
    echo "lscpu "
    echo "exit"

} | $EXECUTABLE $1| tee >(cat) >(grep "Parent" | cat)
