.PHONY: clean

prog: clean
	gcc prog.c -o $@ -pthread

prog_exec: prog
	./$^
	rm -f $^

clean:
	rm -f *.o
	rm -f out.txt