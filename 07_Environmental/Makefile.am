CFLAGS = -Wall -O0 -g
.SILENT: myclean mytest

bin_PROGRAMS=rhasher

rhasher_SOURCES=src/rhasher.c

TESTS = sha1_test1.sh sha1_test2.sh md5_test1.sh md5_test2.sh

gitclean: 
	git clean -fd

myclean:
	rm -r autom4te.cache 
	rm -r src/.deps
	find . | grep -v "configure.ac\|Makefile.am\|src/rhasher.c\|sha1_test1.sh\|sha1_test2.sh\|md5_test1.sh\|md5_test2.sh" | xargs rm

mytest: rhasher
	./rhasher <<< 'SHA1 "1' > tmp.txt
	if echo -ne 1 | sha1sum - | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 1"; else echo "failed test 1"; fi
	./rhasher <<< 'SHA1 Makefile.am' > tmp.txt
	if sha1sum Makefile.am | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 2"; else echo "failed test 2"; fi
	./rhasher <<< 'MD5 "1' > tmp.txt
	if echo -ne 1 | md5sum - | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 3"; else echo "failed test 3"; fi
	./rhasher <<< 'MD5 Makefile.am' > tmp.txt
	if md5sum Makefile.am | cut -d' ' -f1 | cmp tmp.txt; then echo "passed test 4"; else echo "failed test 4"; fi
	rm tmp.txt
