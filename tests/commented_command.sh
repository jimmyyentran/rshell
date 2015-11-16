#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"

echo "COMMENTED_TEST"
echo "------------------"
{
    echo "#"
    echo "#ls"
    echo ";#ls"
    echo "ls # random command"
    echo "ls# random command"
    echo "ls#"
    echo "ls -a#"
    echo "exit"
} | $EXECUTABLE $1
