#!/bin/sh

./rhasher <<< 'SHA1 "1' > tmp.txt
if echo -ne 1 | sha1sum - | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 1"; else exit 1; fi #echo "failed"; fi
rm tmp.txt
