#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"

echo "BRACKET COMMAND"
echo "------------------"
{
    echo "[ -e /bin ] && echo 1"
    echo "[ -f /bin ] && echo 1"
    echo "[ -d /bin ] && echo 1"
    echo "[ -e Makefile ] && echo 1"
    echo "[ -f Makefile ] && echo 1"
    echo "[ -d Makefile ] && echo 1"
    echo "[ -e /bin ; ] && echo 1"
    echo "[ -e /bin # ] && echo 1"
    echo "[ -e /bin /blah # ] && echo 1"
    echo "[ -e /bin || ] && echo 1"
    echo "[ -e /bin ]] && echo 1"
    echo "[[ -e /bin ]] && echo 1"
    echo "[ -e /bin  && ;echo 1"
    echo "[ -e /bin  && echo 1"
    echo "[[ -e /bin ; echo 1"
    echo "[] && echo 1"
    echo "exit"
} | $EXECUTABLE $1
