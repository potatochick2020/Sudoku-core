#include "SudokuGenerator.hpp"
#include "benchmark/benchmark.h"
//average speed of generate a sudoku 
void BM_generate_1_sudoku(benchmark::State& state) {
	while (state.KeepRunning())
    {
        Sudoku sudoku;
        sudoku.initialize(); 
    }
}

BENCHMARK(BM_generate_1_sudoku)->Iterations(20);

void BM_generate_1_sudoku_and_get_flatten_board(benchmark::State& state) {
	while (state.KeepRunning())
    {
        Sudoku sudoku;
        sudoku.initialize(); 
		sudoku.getFlattenBoard();
    }
}

BENCHMARK(BM_generate_1_sudoku_and_get_flatten_board)->Iterations(20);

void BM_single_thread_sudoku_generator(benchmark::State& state) {
	for (auto _ : state) single_thread_sudoku_generator(); 
}

BENCHMARK(BM_single_thread_sudoku_generator);

void BM_multi_thread_sudoku_generator_using_ATOMIC(benchmark::State& state) {
	for (auto _ : state) multi_thread_sudoku_generator_using_ATOMIC();  
}

BENCHMARK(BM_multi_thread_sudoku_generator_using_ATOMIC);

void BM_multi_thread_sudoku_generator_using_MUTEX(benchmark::State& state) {
	for (auto _ : state) multi_thread_sudoku_generator_using_MUTEX();  
}

BENCHMARK(BM_multi_thread_sudoku_generator_using_MUTEX);

void BM_multi_thread_sudoku_generator_using_INT(benchmark::State& state) {
	for (auto _ : state) multi_thread_sudoku_generator_using_INT();  
}

BENCHMARK(BM_multi_thread_sudoku_generator_using_INT);

BENCHMARK_MAIN();