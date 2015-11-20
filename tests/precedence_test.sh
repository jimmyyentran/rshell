#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$(dirname "$BASEDIR")/bin/rshell"

echo "PRECEDENCE TEST"
echo "------------------"
{
    echo "(echo 1 && echo 2) && (echo 3 && echo 4)"
    # echo "(echo 1 && echo 2) && (echo 3 || echo 4)"
    echo "(echo 1 && echo 2) || (echo 3 && echo 4)"
    # echo "(echo 1 && echo 2) || (echo 3 || echo 4)"
    echo "(echo 1 || echo 2) && (echo 3 && echo 4)"
    # echo "(echo 1 || echo 2) && (echo 3 || echo 4)"
    echo "(echo 1 || echo 2) || (echo 3 && echo 4)"
    echo "(echo 1 || echo 2) || (echo 3 || echo 4)"
    echo "(echo 1 && (echo 2 && echo 2.5)) && (echo 3 && echo 4)"
    echo "(echo 1 && echo 2) && ((echo 3 || echo 4) && echo 5)"
    echo "(echo 1 && echo 2) && ((echo 3 || echo 4) && (echo 5 || echoo 6)"
    echo "(echo 1 && echo 2) && ((echo 3 || echo 4) && (echo 5 || echoo 6))"
    echo "(echo 1 && e 2 || echo 3) && (e 4 && echo 5 || (echo 6 || e 7 && \
(echo 8 || e 9)) && (e 10 || (echo 11 && ( e 12 || echo 13 && \
((echo 14))))))"
    echo "(echo 1 && e 2 || echo 3) && (e 4 && echo 5 || (echo 6 || e 7 && \
(echo 8 || e 9)) && (e 10 || (echo 11 && ( e 12 || echo 13 && \
((echo 14))))))"
    echo "exit"
} | $EXECUTABLE $1
