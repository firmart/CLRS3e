all: tst

tst: tst.c xorlist.c xorlist.h
	cc tst.c xorlist.c -g -o tst
		
.PHONY : doc clean

doc : *.c *.h
	doxygen xorlist.doxygen && make -C doc/latex 

clean :
	-rm -rf doc/
	-rm tst
