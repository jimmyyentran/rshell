#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"

echo "TEST COMMAND"
echo "------------------"
{
    echo "test -e /bin"
    echo "test -f /bin"
    echo "test -d /bin"
    echo "test -e "
    echo "test"
    echo "test blah /bin"
    echo "test -? /bin"
    echo "test -de /bin"
    echo "test -d -e /bin"
    echo "test /bin && ls"
    echo "test - /bin && ls"
    echo "test /bin || test -d src && ls"
    echo "exit"
} | $EXECUTABLE $1
