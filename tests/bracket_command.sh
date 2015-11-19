#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"

echo "BRACKET COMMAND"
echo "------------------"
{
    echo "[ -e /bin ] && echo 1"
    echo "[ -e /bin ]] && echo 1"
    echo "[[ -e /bin ]] && echo 1"
    echo "[[ -e /bin ] && echo 1"
    echo "[ -e /bin  && ;echo 1"
    echo "[] && echo 1"
    echo "exit"
} | $EXECUTABLE $1
