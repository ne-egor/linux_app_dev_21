#!/bin/sh

./rhasher <<< 'MD5 Makefile.am' > tmp.txt
if md5sum Makefile.am | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 4"; else echo exit 1;  fi
rm tmp.txt
