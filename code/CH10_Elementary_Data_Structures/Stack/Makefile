all: doc tst

tst: tst.c stack.c stack.h
	cc tst.c stack.c -o tst
		
.PHONY : doc clean

doc : *.c *.h
	doxygen stack.doxygen && make -C doc/latex 

clean :
	-rm -rf doc/
	-rm tst
