#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"

echo "MULTI COMMAND TEST"
echo "------------------"
{
    echo "uname&&ls"
    echo "uname||ls"
    echo "uname;ls"
    echo "uname#ls"
    echo "uname##ls"
    echo "uname&ls"
    echo "uname|ls"
    echo "uname&|ls"
    echo "uname&&"
    echo "uname||"
    echo "git status"
    echo "ls -alt && ls"
    echo "ls -j && ls"
    echo "ls -j || ls"
    echo "ls&&|" #fix
    echo "ls && || ls" #fix
    echo "exit"
} | $EXECUTABLE $1
