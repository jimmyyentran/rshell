#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"
echo $EXECUTABLE

input () {
    $EXECUTABLE << EOF
    $1
EOF
}

input "ls&&"
