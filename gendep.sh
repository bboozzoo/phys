#!/bin/sh
echo > Makefile.depend
for f in `find . -type f -name '*.cc'`; do
	gcc -std=gnu++0x -MG -MM $f >> Makefile.depend
done
