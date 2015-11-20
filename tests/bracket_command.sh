#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"

echo "BRACKET COMMAND"
echo "------------------"
{
    echo "[ -e /bin ] && echo success"
    echo "[ -f /bin ] && echo success"
    echo "[ -d /bin ] && echo success"
    echo "[ -e Makefile ] && echo success"
    echo "[ -f Makefile ] && echo success"
    echo "[ -d Makefile ] && echo success"
    echo "[ -d Makefile ] && [ -e /bin ] && echo success"
    echo "[ -e /bin ; ] && echo success"
    echo "[ -e /bin # ] && echo success"
    echo "[ -e /bin /blah # ] && echo success"
    echo "[ -e /bin || ] && echo success"
    echo "[ -e /bin ]] && echo success"
    echo "[[ -e /bin ]] && echo success"
    echo "[ -e /bin  && ;echo success"
    echo "[ -e /bin  && echo success"
    echo "[[ -e /bin ; echo success"
    echo "[] && echo success"
    echo "exit"
} | $EXECUTABLE $1
