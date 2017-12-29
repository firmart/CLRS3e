all: doc tst

tst: *.c *.h
	gcc tst.c graphs.c queue.c stack.c -g -o tst
		
.PHONY : doc clean

doc : *.c *.h
	doxygen graphs.doxygen && make -C doc/latex 

clean :
	-rm -rf doc/
	-rm tst out out.png
