#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"

input () {
    $EXECUTABLE << EOF
    $1
EOF
echo
}

# TODO: fix the space command
echo "MULTI COMMAND TEST"
echo "------------------"
input "ls&&ls"
input "ls||ls"
input "ls;ls"
input "ls&ls"
input "ls|ls"
input "ls&|ls"
