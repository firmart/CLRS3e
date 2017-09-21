all: perf crpt1 crpt2

perf: rec_find_max_subarray.o brute_find_max_subarray.o hybrid_find_max_subarray.o linear_find_max_subarray.o tst_perf.o 
	gcc $^ -o tst_perf
crpt1: rec_find_max_subarray.o brute_find_max_subarray.o tst_crossover_pt_1.o
	gcc $^ -o tst_crossover_pt_1
crpt2: rec_find_max_subarray.o hybrid_find_max_subarray.o brute_find_max_subarray.o tst_crossover_pt_2.o
	gcc $^ -o tst_crossover_pt_2

.PHONY: clean

clean:
	rm *.o tst_perf tst_crossover_pt_1 tst_crossover_pt_2

