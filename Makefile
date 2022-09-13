all : c2f_table

test : c2f_table
	./c2f_table

c2f_table : c2f_table.o tempconv.o
	cc -o c2f_table -Wall -Wextra -Werror -std=c17 c2f_table.o tempconv.o

c2f_table.o : c2f_table.c tempconv.h
	cc -Wall -Wextra -Werror -std=c17 -c c2f_table.c

tempconv.o : tempconv.c tempconv.h
	cc -Wall -Wextra -Werror -std=c17 -c tempconv.c

clean :
	rm *.o
	rm c2f_table
