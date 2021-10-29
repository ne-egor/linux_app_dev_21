GENERATES = move 
CFLAGS = -std=gnu11 -Wall -Wextra -O0 -g
.SILENT: test

all:	 move

%: %.c
	gcc $(CFLAGS) $< -o $@
	

test: move


clean:
	rm -f $(GENERATES)

