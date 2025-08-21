#!/bin/bash

# get root directory
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
TODO_TXT="$SCRIPT_DIR/todo.txt"

if [ -f "$TODO_APP" ]; then 
    ./todo $TODO_TXT
else
    g++ $SCRIPT_DIR/src/todo.cpp -o todo && ./todo $TODO_TXT
fi
