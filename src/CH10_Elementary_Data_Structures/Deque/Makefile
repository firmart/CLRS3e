all: tst

tst: tst.c deque.c deque.h
	cc tst.c deque.c -g -o tst
		
.PHONY : doc clean

doc : *.c *.h
	doxygen deque.doxygen && make -C doc/latex 

clean :
	-rm -rf doc/
	-rm tst
