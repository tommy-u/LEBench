lebench: OS_Eval.c
	gcc -o $@ OS_Eval.c -O0 -lpthread --static

tubench: TU_PPID.c
	gcc -o $@ TU_PPID.c -O0 --static -g

run:
	./lebench 0 TEST-OS-$i 32 > /dev/null
exp_0_single_long_run:
	./lebench 0 exp_0_ 10000 &> /dev/null

exp_1_base32_10x:
# for i in {1..10}; do LEBENCH_DIR=/root/LEBench/TEST_DIR/results/ ./lebench 0 TEST-OS-$i 32 &> /dev/null; done
	for i in {1..10}; do taskset 0x1 ./lebench 0 exp_1_repeat_$$i 32 &> /dev/null; done

exp_1_base256_10x:
# for i in {1..10}; do LEBENCH_DIR=/root/LEBench/TEST_DIR/results/ ./lebench 0 TEST-OS-$i 32 &> /dev/null; done
	for i in {1..10}; do taskset 0x1 ./lebench 0 exp_1_256_repeat_$$i 256 &> /dev/null; done

exp_1_base2048_10x:
# for i in {1..10}; do LEBENCH_DIR=/root/LEBench/TEST_DIR/results/ ./lebench 0 TEST-OS-$i 32 &> /dev/null; done
	for i in {1..10}; do taskset 0x1 ./lebench 0 exp_1_2048_repeat_$$i 2048  &> /dev/null; done

exp_1_base16384_10x:
# for i in {1..10}; do LEBENCH_DIR=/root/LEBench/TEST_DIR/results/ ./lebench 0 TEST-OS-$i 32 &> /dev/null; done
	for i in {1..10}; do taskset 0x1 ./lebench 0 exp_1_16384_repeat_$$i 16384  &> /dev/null; done

exp_2_sweep_32_16k:
	echo e2

exp_3_individual_stats:
	echo IS

exp_4_control_proc_numa_pin_nice:
	echo c

exp_5_repeat_1-3:
	echo repeat

formatData16384:
	cat results/output.exp_1_2048_repeat_1.csv | cut -d':' -f 1 > results/labels.txt
# Stop judging me.
	bash -c "paste results/labels.txt <(cat results/output.exp_1_16384_repeat_1.csv | cut -d',' -f2) <(cat results/output.exp_1_16384_repeat_2.csv | cut -d',' -f2) <(cat results/output.exp_1_16384_repeat_3.csv | cut -d',' -f2) <(cat results/output.exp_1_16384_repeat_4.csv | cut -d',' -f2) <(cat results/output.exp_1_16384_repeat_5.csv | cut -d',' -f2) <(cat results/output.exp_1_16384_repeat_6.csv | cut -d',' -f2) <(cat results/output.exp_1_16384_repeat_7.csv | cut -d',' -f2) <(cat results/output.exp_1_16384_repeat_8.csv | cut -d',' -f2) <(cat results/output.exp_1_16384_repeat_9.csv | cut -d',' -f2) <(cat results/output.exp_1_16384_repeat_10.csv | cut -d',' -f2)"

formatData2048:
	cat results/output.exp_1_2048_repeat_1.csv | cut -d':' -f 1 > results/labels.txt
# Stop judging me.
	bash -c "paste results/labels.txt <(cat results/output.exp_1_2048_repeat_1.csv | cut -d',' -f2) <(cat results/output.exp_1_2048_repeat_2.csv | cut -d',' -f2) <(cat results/output.exp_1_2048_repeat_3.csv | cut -d',' -f2) <(cat results/output.exp_1_2048_repeat_4.csv | cut -d',' -f2) <(cat results/output.exp_1_2048_repeat_5.csv | cut -d',' -f2) <(cat results/output.exp_1_2048_repeat_6.csv | cut -d',' -f2) <(cat results/output.exp_1_2048_repeat_7.csv | cut -d',' -f2) <(cat results/output.exp_1_2048_repeat_8.csv | cut -d',' -f2) <(cat results/output.exp_1_2048_repeat_9.csv | cut -d',' -f2) <(cat results/output.exp_1_2048_repeat_10.csv | cut -d',' -f2)"

formatData256:
	cat results/output.exp_1_repeat_1.csv | cut -d':' -f 1 > results/labels.txt
# Stop judging me.
	bash -c "paste results/labels.txt <(cat results/output.exp_1_256_repeat_1.csv | cut -d',' -f2) <(cat results/output.exp_1_256_repeat_2.csv | cut -d',' -f2) <(cat results/output.exp_1_256_repeat_3.csv | cut -d',' -f2) <(cat results/output.exp_1_256_repeat_4.csv | cut -d',' -f2) <(cat results/output.exp_1_256_repeat_5.csv | cut -d',' -f2) <(cat results/output.exp_1_256_repeat_6.csv | cut -d',' -f2) <(cat results/output.exp_1_256_repeat_7.csv | cut -d',' -f2) <(cat results/output.exp_1_256_repeat_8.csv | cut -d',' -f2) <(cat results/output.exp_1_256_repeat_9.csv | cut -d',' -f2) <(cat results/output.exp_1_256_repeat_10.csv | cut -d',' -f2)"

formatData:
	cat results/output.exp_1_repeat_1.csv | cut -d':' -f 1 > results/labels.txt
# Stop judging me.
	bash -c "paste results/labels.txt <(cat results/output.exp_1_repeat_1.csv | cut -d',' -f2) <(cat results/output.exp_1_repeat_2.csv | cut -d',' -f2) <(cat results/output.exp_1_repeat_3.csv | cut -d',' -f2) <(cat results/output.exp_1_repeat_4.csv | cut -d',' -f2) <(cat results/output.exp_1_repeat_5.csv | cut -d',' -f2) <(cat results/output.exp_1_repeat_6.csv | cut -d',' -f2) <(cat results/output.exp_1_repeat_7.csv | cut -d',' -f2) <(cat results/output.exp_1_repeat_8.csv | cut -d',' -f2) <(cat results/output.exp_1_repeat_9.csv | cut -d',' -f2) <(cat results/output.exp_1_repeat_10.csv | cut -d',' -f2)"

perf_rec:
	perf record -F 1000 -g -- ./lebench 0 linux-perf 1024

perf_fg:
	perf script > out.perf
	~/FlameGraph/stackcollapse-perf.pl out.perf > out.folded
	~/FlameGraph/flamegraph.pl out.folded > benchmark.svg

clean:
	- rm lebench
	- rm ./results/*
	- rm out
	- rm test_file.txt
	- rm out.perf
	- rm perf.data
	- rm out.folded
	- rm benchmark.svg
