#!/bin/bash

set -e

./sudoku.o -v && echo "isVaild failed!" || echo "isValid worked."

res=`./sudoku.o -s 12345670 -p | head -n 1 | sed "s/|//g;s/ //g"`
if [[ $res != "123456700" ]]; then
    echo "setBoard failed!"
    exit 1
fi
echo "setBoard worked!"
