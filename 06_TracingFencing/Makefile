GENERATES = move libprotect.so
CFLAGS = -std=gnu11 -Wall -Wextra -O0 -g
.SILENT: test test_protect

all:	 move

%: %.c
	gcc $(CFLAGS) $< -o $@

a: safe
	cp -u safe a
	

test: move a
	# Unable to open file (1)
	strace -e fault=openat:when=3 -oo ./move a b 2> /dev/null; if [ $$? == 1 ] && [ -f a ] && [ ! -f b ]; then echo "Passed test 1"; else echo "Failed test 1"; fi
	rm -f a b; cp -u safe a
	# Unable to create/open file (2)
	strace -e fault=openat:when=4 -oo ./move a b 2> /dev/null; if [ $$? == 2 ] && [ -f a ] && [ ! -f b ]; then echo "Passed test 2"; else echo "Failed test 2"; fi
	rm -f a b; cp -u safe a
	# Error writing buffer (3)
	strace -e fault=write:when=1 -oo ./move a b 2> /dev/null; if [ $$? == 3 ] && [ -f a ] && [ ! -f b ]; then echo "Passed test 3"; else echo "Failed test 3"; fi
	rm -f a b; cp -u safe a
	# Error while reading file: EOF not reached (4)
	echo "Test for exit code '4' is not implemented"
	rm -f a b; cp -u safe a
	# Error while reading file: unknown (5)
	strace -e fault=read:when=2 -oo ./move a b 2> /dev/null; if [ $$? == 5 ] && [ -f a ] && [ ! -f b ]; then echo "Passed test 5"; else echo "Failed test 5"; fi
	rm -f a b; cp -u safe a
	# Error deleting input file (6)
	strace -e fault=unlink:when=1 -oo ./move a b 2> /dev/null; if [ $$? == 6 ] && [ -f a ] && [ -f b ]; then echo "Passed test 6"; else echo "Failed test 6"; fi
	rm -f a b; cp -u safe a
	# Error deleting output file (7)
	strace --fault=write:when=1 -e fault=unlink:when=1 -oo ./move a b 2> /dev/null; if [ $$? == 7 ] && [ -f a ] && [ -f b ]; then echo "Passed test 7"; else echo "Failed test 7"; fi
	rm -f a o b; 

libprotect.so: protect.c
	gcc $(CFLAGS) -shared -fPIC $< -o $@ -ldl

test_protect: move libprotect.so
	cp -u safe PROTECT_a
	LD_PRELOAD=./libprotect.so ./move PROTECT_a b
	if [ -f PROTECT_a ]; then echo "Passed PROTECT test"; else echo "Failed PROTECT test"; fi
	rm -f PROTECT_a b



clean:
	rm -f $(GENERATES)

