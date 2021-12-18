#!/bin/sh

./rhasher <<< 'SHA1 Makefile.am' > tmp.txt
if sha1sum Makefile.am | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 2"; else exit 1; fi
rm tmp.txt
