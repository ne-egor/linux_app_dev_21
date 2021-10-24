GENERATES = range README
CFLAGS = -std=gnu11 -Wall -Wextra -O0 -g
.SILENT: test

all:	README range

%: %.c
	gcc $(CFLAGS) $< -o $@
	

README: range
	./$< 2> $@

test: range
	gdb -x scripts/gdb_script1 range > /dev/null 2>&1 
	if cat gdb.output | grep @@@ | cut -d' ' -f2- | cmp tests/test1; then echo "passed test 1"; else echo "failed test 1"; fi 
	rm gdb.output
	gdb -x scripts/gdb_script2 range > /dev/null 2>&1 
	if cat gdb.output | grep @@@ | cut -d' ' -f2- | cmp tests/test2; then echo "passed test 2"; else echo "failed test 2"; fi 
	rm gdb.output



clean:
	rm -f $(GENERATES)

