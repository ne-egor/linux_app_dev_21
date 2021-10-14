GENERATES = prog prog-a prog-so *.so README
TRASH = *.o *~ o.* *.a 
CFLAGS = -Wall -fPIC
.SILENT: test

all:	README prog prog-a prog-so

prog:   const.o fun.o prog.o

liboutput_static.a:	const.o fun.o
	ar -rcs $@ $^

prog-a: prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@

liboutput.so: const.o fun.o
	cc -shared $^ -o $@

prog-so: prog.o liboutput.so
	cc -L. $< -loutput -o $@

README: prog
	./$< 2> $@

fun.o:  outlib.h

test: prog prog-a prog-so
	./prog > 1_1.tmp 2>&1 
	./prog-a 2>&1 | sed 's/prog-a/prog/' > 2_1.tmp
	LD_LIBRARY_PATH=`pwd` ./prog-so 2>&1 | sed 's/prog-so/prog/' > 3_1.tmp
	if cmp 1_1.tmp 2_1.tmp > /dev/null 2>&1; then echo "prog and prog-a don't differ at 0 params"; else echo "prog and prog-a differ at 0 params"; cat 1_1.tmp; cat 2_1.tmp; fi
	if cmp 1_1.tmp 3_1.tmp > /dev/null 2>&1; then echo "prog and prog-so don't differ at 0 params"; else echo "prog and prog-so differ at 0 params"; cat 1_1.tmp; cat 3_1.tmp; fi
	if cmp 2_1.tmp 3_1.tmp > /dev/null 2>&1; then echo "prog-a and prog-so don't differ at 0 params"; else echo "prog-a and prog-so differ at 0 params"; cat 2_1.tmp; cat 3_1.tmp; fi
	echo ""
	./prog 1 > 1_2.tmp 2>&1
	./prog-a 1 > 2_2.tmp 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so 1 > 3_2.tmp 2>&1
	if cmp 1_2.tmp 2_2.tmp > /dev/null 2>&1; then echo "prog and prog-a don't differ at params '1'"; else echo "prog and prog-a differ at params '1'"; cat 1_2.tmp; cat 2_2.tmp; fi
	if cmp 1_2.tmp 3_2.tmp > /dev/null 2>&1; then echo "prog and prog-so don't differ at params '1'"; else echo "prog and prog-so differ at params '1'"; cat 1_2.tmp; cat 3_2.tmp; fi
	if cmp 2_2.tmp 3_2.tmp > /dev/null 2>&1; then echo "prog-a and prog-so don't differ at params '1'"; else echo "prog-a and prog-so differ at params '1'"; cat 2_2.tmp; cat 3_2.tmp; fi
	echo ""
	./prog 1 2 3 > 1_3.tmp 2>&1
	./prog-a 1 2 3 > 2_3.tmp 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so 1 2 3 > 3_3.tmp 2>&1
	if cmp 1_3.tmp 2_3.tmp > /dev/null 2>&1; then echo "prog and prog-a don't differ at params '1 2 3'"; else echo "prog and prog-a differ at params '1 2 3'"; cat 1_3.tmp; cat 2_3.tmp; fi
	if cmp 1_3.tmp 3_3.tmp > /dev/null 2>&1; then echo "prog and prog-so don't differ at params '1 2 3'"; else echo "prog and prog-so differ at params '1 2 3'"; cat 1_3.tmp; cat 3_3.tmp; fi
	if cmp 2_3.tmp 3_3.tmp > /dev/null 2>&1; then echo "prog-a and prog-so don't differ at params '1 2 3'"; else echo "prog-a and prog-so differ at params '1 2 3'"; cat 2_3.tmp; cat 3_3.tmp; fi
	rm *.tmp




clean:
	rm -f $(TRASH)

distclean:	  clean
	rm -rf $(GENERATES)
