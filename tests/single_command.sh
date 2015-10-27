#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"

input () {
    $EXECUTABLE << EOF
    $1
EOF
echo
}

echo "SINGLE COMMAND TEST"
echo "------------------"

input "ls -alt /bin"

