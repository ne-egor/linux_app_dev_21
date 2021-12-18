CFLAGS = -Wall -O0 -g

bin_PROGRAMS=hasher

hasher_SOURCES=src/hasher.c

myclean:
	rm -r autom4te.cache 
	rm -r src/.deps
	find . | grep -v "configure.ac\|Makefile.am\|src/hasher.c" | xargs rm

mytest: hasher
	./hasher <<< 'SHA1 "1' > tmp.txt
	if echo -ne 1 | sha1sum - | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 1"; else echo "failed test 1"; fi
	./hasher <<< 'SHA1 Makefile.am' > tmp.txt
	if sha1sum Makefile.am | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 2"; else echo "failed test 2"; fi
	./hasher <<< 'MD5 "1' > tmp.txt
	if echo -ne 1 | md5sum - | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 3"; else echo "failed test 3"; fi
	./hasher <<< 'MD5 Makefile.am' > tmp.txt
	if md5sum Makefile.am | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 4"; else echo "failed test 4"; fi
	rm tmp.txt
