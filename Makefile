all: memgrind memtest Test1 Test2 Test3 Test4_1 Test4_2 Test4_3 Test5

memgrind: memgrind.o mymalloc.o
	gcc memgrind.o mymalloc.o -o memgrind

memtest: memtest.o mymalloc.o
	gcc memtest.o mymalloc.o -o memtest

Test1: Test1.o mymalloc.o
	gcc Test1.o mymalloc.o -o Test1

Test2: Test2.o mymalloc.o
	gcc Test2.o mymalloc.o -o Test2

Test3: Test3.o mymalloc.o
	gcc Test3.o mymalloc.o -o Test3

Test4_1: Test4_1.o mymalloc.o
	gcc Test4_1.o mymalloc.o -o Test4_1

Test4_2: Test4_2.o mymalloc.o
	gcc Test4_2.o mymalloc.o -o Test4_2

Test4_3: Test4_3.o mymalloc.o
	gcc Test4_3.o mymalloc.o -o Test4_3

Test5: Test5.o mymalloc.o
	gcc Test5.o mymalloc.o -o Test5


mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c

memgrind.o: memgrind.c mymalloc.h
	gcc -c memgrind.c

memtest.o: memtest.c mymalloc.h
	gcc -c memtest.c

Test1.o: Test1.c mymalloc.h
	gcc -c Test1.c

Test2.o: Test2.c mymalloc.h
	gcc -c Test2.c

Test3.o: Test3.c mymalloc.h
	gcc -c Test3.c

Test4_1.o: Test4_1.c mymalloc.h
	gcc -c Test4_1.c

Test4_2.o: Test4_2.c mymalloc.h
	gcc -c Test4_2.c

Test4_3.o: Test4_3.c mymalloc.h
	gcc -c Test4_3.c

Test5.o: Test5.c mymalloc.h
	gcc -c Test5.c

clean:
	rm -f *.o mymalloc memgrind memtest Test1 Test2 Test3 Test4_1 Test4_2 Test4_3 Test5
