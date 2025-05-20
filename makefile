
out: main.o db_operations.o
	cc main.o db_operations.o -o out

main.o: main.c
	cc -c main.c

db_operations.o: db_operations.c
	cc -c db_operations.c

clean:
	rm -f *.o out
