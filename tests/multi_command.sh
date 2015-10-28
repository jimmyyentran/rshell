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
echo "ls -alt && ls"
echo "exit"
} | $EXECUTABLE | cat

# input () {
    # $EXECUTABLE << EOF
# $1
# EOF
# echo
# }

