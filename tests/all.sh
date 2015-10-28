#!/bin/bash

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# source $(dirname "$BASEDIR")/tests/single_command.sh DEBUG4
$(dirname "$BASEDIR")/tests/single_command.sh DEBUG4
$(dirname "$BASEDIR")/tests/multi_command.sh DEBUG4
$(dirname "$BASEDIR")/tests/commented_command.sh DEBUG4

