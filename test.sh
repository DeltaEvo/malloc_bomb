#!/usr/bin/env bash

PROGRAM="$@"
echo $PROGRAM
PIPE=$(mktemp -u)
OUT=/dev/tty
function run {
    DYLD_INSERT_LIBRARIES=$(pwd)/malloc.dylib MALLOC_FD=10 MALLOC_FAIL_AT="$1" $PROGRAM 10>$PIPE 2>$OUT 1>$OUT
    ret=$?
    tail -1 $PIPE
    > $PIPE
    exit $ret
}

max=$(run -1)

for i in $(seq $max)
do
    c=$(run $i)
    echo Exited with $? at $i [mallocs $c]
done

rm $PIPE