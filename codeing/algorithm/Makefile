CC  = g++ -o
all : list 02stack 03stack 04queue 05binarytree \
	BinarySearch

list:list.o
	$(CC) $@ $^
02stack:02stack.o
	$(CC) $@ $^
03stack:03stack.o 01list.o
	 $(CC) $@ $^ 
04queue:04queue.o 01list.o
	 $(CC) $@ $^
05binarytree:binarytree.o
	$(CC) $@ $^
BinarySearch:BinarySearch.o
	 $(CC) $@ $^

clean:
	rm *.o
