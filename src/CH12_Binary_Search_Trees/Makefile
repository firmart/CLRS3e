all: tst 

tst: tst.c bst.c bst.h
	$(CC) tst.c bst.c -g -o tst

		
.PHONY : doc clean

doc : *.c *.h
	doxygen bst.doxygen && make -C doc/latex 

clean :
	-rm -rf doc/
	-rm tst
