all: perf crpt1 crpt2

perf: rec-find-max-subarray.o brute-find-max-subarray.o hybrid-find-max-subarray.o tst_perf.o
	gcc $^ -o tst_perf
crpt1: rec-find-max-subarray.o brute-find-max-subarray.o tst_crossover_pt_1.o
	gcc $^ -o tst_crossover_pt_1
crpt2: rec-find-max-subarray.o hybrid-find-max-subarray.o brute-find-max-subarray.o tst_crossover_pt_2.o
	gcc $^ -o tst_crossover_pt_2

.PHONY: clean

clean:
	rm *.o tst_perf tst_crossover_pt_1 tst_crossover_pt_2

