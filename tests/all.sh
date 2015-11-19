#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

$(dirname "$BASEDIR")/tests/single_command.sh $1
$(dirname "$BASEDIR")/tests/multi_command.sh $1
$(dirname "$BASEDIR")/tests/commented_command.sh $1
$(dirname "$BASEDIR")/tests/exit.sh $1
$(dirname "$BASEDIR")/tests/precedence_test.sh $1
$(dirname "$BASEDIR")/tests/test_command.sh $1
$(dirname "$BASEDIR")/tests/bracket_command.sh $1



