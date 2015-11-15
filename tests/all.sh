#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# $(dirname "$BASEDIR")/tests/single_command.sh TEST
# $(dirname "$BASEDIR")/tests/multi_command.sh TEST
# $(dirname "$BASEDIR")/tests/commented_command.sh TEST
# $(dirname "$BASEDIR")/tests/exit.sh TEST
$(dirname "$BASEDIR")/tests/precedence_test.sh TEST


