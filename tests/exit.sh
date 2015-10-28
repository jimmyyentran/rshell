#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"

ARG1="$1"

echo "EXIT_TEST"
echo "------------------"
input () {
    $EXECUTABLE $ARG1 << EOF
$1
exit
EOF
echo
}
input "exit"
input "exit||"
input "ls || exit"
input "ls && exit"
input "exit || ls"
input "exit && ls"
input "ls exit"
input "lsexit"
input "exit || ls"
input "ls || ls || exit"
input "ls && ls && exit"
