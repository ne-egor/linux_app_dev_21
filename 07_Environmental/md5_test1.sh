#!/bin/sh

./rhasher <<< 'MD5 "1' > tmp.txt
if echo -ne 1 | md5sum - | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 3"; else exit 1;  fi
rm tmp.txt
