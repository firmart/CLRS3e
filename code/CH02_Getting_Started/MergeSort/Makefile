all: merge_sort

merge_sort: merge_sort.o tst_merge_sort.o
	gcc $^ -o tst_merge_sort

.PHONY: clean

clean:
	rm *.o tst_merge_sort

