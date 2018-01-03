all: tst

tst: tst.c llist.c llist.h
	cc tst.c llist.c -g -o tst
		
.PHONY : doc clean

doc : *.c *.h
	doxygen llist.doxygen && make -C doc/latex 

clean :
	-rm -rf doc/
	-rm tst
