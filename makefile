prog:
	gcc prog.c -o $@

prog_exec: prog
	./$^
	rm $^

clean:
	rm *.o