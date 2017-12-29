all: doc tst

tst: tst.c queue.c queue.h
	cc tst.c queue.c -o tst
		
.PHONY : doc clean

doc : *.c *.h
	doxygen queue.doxygen && make -C doc/latex 

clean :
	-rm -rf doc/
	-rm tst
