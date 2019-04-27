#!/bin/sh

while true; do
  ls -d include/*.h src/*.c | entr -dc ./make.sh
done
