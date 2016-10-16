/***************************************************************************
*
*  	Filename: profiler.c
*	Description: Runs the profiler on our functions and various standard functions
*	depending on the platform
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _PROFILER_C
#define _PROFILER_C

#include <stdint.h>
#include "timer.h"
#include "data.h"
#include "memory.h"
#include "log.h"
#include "circbuf.h"
#include <string.h>

void my_memmove_profiler(uint32_t size) {
#ifdef FRDM
	uint8_t src[size];
	uint8_t dst[size];
	timer_start();
	my_memmove(src, dst, size);
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nmy_memmove runtime (\0";
	uint8_t msg2[10] = " bytes): \0";
	uint8_t msg3[10] = " cycles, \0";
	uint8_t msg4[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),size,UI64);
	LOG_1(msg2, count2null(msg2),cycles,UI64);
	LOG_1(msg3, count2null(msg3),time,UI64);
	LOG_0(msg4, count2null(msg4));
#else
	// add BBB
#endif
}

void memmove_profiler(uint32_t size) {
#ifdef FRDM
	uint8_t src[size];
	uint8_t dst[size];
	timer_start();
	memmove(src, dst, size);
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nmemmove runtime (\0";
	uint8_t msg2[10] = " bytes): \0";
	uint8_t msg3[10] = " cycles, \0";
	uint8_t msg4[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),size,UI64);
	LOG_1(msg2, count2null(msg2),cycles,UI64);
	LOG_1(msg3, count2null(msg3),time,UI64);
	LOG_0(msg4, count2null(msg4));
#else
	// add BBB
#endif
}

void my_memzero_profiler(uint32_t size) {
#ifdef FRDM
	uint8_t src[size];
	timer_start();
	my_memzero(src, size);
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nmy_memzero runtime (\0";
	uint8_t msg2[10] = " bytes): \0";
	uint8_t msg3[10] = " cycles, \0";
	uint8_t msg4[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),size,UI64);
	LOG_1(msg2, count2null(msg2),cycles,UI64);
	LOG_1(msg3, count2null(msg3),time,UI64);
	LOG_0(msg4, count2null(msg4));
#else
	// add BBB
#endif
}

void memset_profiler(uint32_t size) {
#ifdef FRDM
	uint8_t src[size];
	timer_start();
	memset(src, 0, size);
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nmemset runtime (\0";
	uint8_t msg2[10] = " bytes): \0";
	uint8_t msg3[10] = " cycles, \0";
	uint8_t msg4[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),size,UI64);
	LOG_1(msg2, count2null(msg2),cycles,UI64);
	LOG_1(msg3, count2null(msg3),time,UI64);
	LOG_0(msg4, count2null(msg4));
#else
	// add BBB
#endif
}

void my_reverse_profiler(uint32_t size) {
#ifdef FRDM
	uint8_t src[size];
	timer_start();
	my_reverse(src, size);
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nmy_reverse runtime (\0";
	uint8_t msg2[10] = " bytes): \0";
	uint8_t msg3[10] = " cycles, \0";
	uint8_t msg4[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),size,UI64);
	LOG_1(msg2, count2null(msg2),cycles,UI64);
	LOG_1(msg3, count2null(msg3),time,UI64);
	LOG_0(msg4, count2null(msg4));
#else
	// add BBB
#endif
}

void my_itoa_profiler() {
#ifdef FRDM
	uint8_t str[10];
	uint32_t data = 123456;
	timer_start();
	my_itoa(str, data, 10);
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nmy_itoa runtime (\0";
	uint8_t msg2[10] = " cycles, \0";
	uint8_t msg3[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),cycles,UI64);
	LOG_1(msg2, count2null(msg2),time,UI64);
	LOG_0(msg3, count2null(msg3));
#else
	// add BBB
#endif
}

void my_ftoa_profiler() {
#ifdef FRDM
	uint8_t str[40];
	float data = 123456789E20;
	timer_start();
	my_ftoa(str, data);
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nmy_ftoa runtime (\0";
	uint8_t msg2[10] = " cycles, \0";
	uint8_t msg3[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),cycles,UI64);
	LOG_1(msg2, count2null(msg2),time,UI64);
	LOG_0(msg3, count2null(msg3));
#else
	// add BBB
#endif
}

void my_atoi_profiler() {
#ifdef FRDM
	uint8_t str[6] = "123456";
	timer_start();
	my_atoi(str);
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nmy_atoi runtime (\0";
	uint8_t msg2[10] = " cycles, \0";
	uint8_t msg3[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),cycles,UI64);
	LOG_1(msg2, count2null(msg2),time,UI64);
	LOG_0(msg3, count2null(msg3));
#else
	// add BBB
#endif
}

void malloc_empty_profiler(uint32_t size) {
#ifdef FRDM
	uint8_t *ptr;
	timer_start();
    ptr = malloc(size);
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	free(ptr);
	uint8_t msg1[50] = "\nmalloc (empty) runtime (\0";
	uint8_t msg2[10] = " bytes): \0";
	uint8_t msg3[10] = " cycles, \0";
	uint8_t msg4[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),size,UI64);
	LOG_1(msg2, count2null(msg2),cycles,UI64);
	LOG_1(msg3, count2null(msg3),time,UI64);
	LOG_0(msg4, count2null(msg4));
#else
	// add BBB
#endif
}

void malloc_nonempty_profiler(uint32_t size) {
#ifdef FRDM
	uint8_t *ptr;
	uint8_t *ptr2;
	ptr = malloc(100);
	timer_start();
    ptr2 = malloc(size);
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	free(ptr);
	free(ptr2);
	uint8_t msg1[50] = "\nmalloc (non-empty) runtime (\0";
	uint8_t msg2[10] = " bytes): \0";
	uint8_t msg3[10] = " cycles, \0";
	uint8_t msg4[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),size,UI64);
	LOG_1(msg2, count2null(msg2),cycles,UI64);
	LOG_1(msg3, count2null(msg3),time,UI64);
	LOG_0(msg4, count2null(msg4));
#else
	// add BBB
#endif
}

void free_profiler(uint32_t size) {
#ifdef FRDM
	uint8_t *ptr;
    ptr = malloc(size);
	timer_start();
	free(ptr);
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nfree runtime (\0";
	uint8_t msg2[10] = " bytes): \0";
	uint8_t msg3[10] = " cycles, \0";
	uint8_t msg4[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),size,UI64);
	LOG_1(msg2, count2null(msg2),cycles,UI64);
	LOG_1(msg3, count2null(msg3),time,UI64);
	LOG_0(msg4, count2null(msg4));
#else
	// add BBB
#endif
}

void circbuf_add_profiler() {
#ifdef FRDM
	CircBuf_t *myCB = buffer_init(5);
	timer_start();
	add_buffer_item(myCB, '1');
	uint64_t cycles = timer_end();
	destroy_buffer(&myCB);
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nadd circular buffer runtime: \0";
	uint8_t msg2[10] = " cycles, \0";
	uint8_t msg3[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),cycles,UI64);
	LOG_1(msg2, count2null(msg2),time,UI64);
	LOG_0(msg3, count2null(msg3));
#else
	// add BBB
#endif
}

void circbuf_remove_profiler() {
#ifdef FRDM
	CircBuf_t *myCB = buffer_init(5);
	uint8_t item;
	uint8_t *item_ptr = &item;
	add_buffer_item(myCB, '1');
	timer_start();
	remove_buffer_item(myCB, item_ptr);
	uint64_t cycles = timer_end();
	destroy_buffer(&myCB);
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nremove circular buffer runtime: \0";
	uint8_t msg2[10] = " cycles, \0";
	uint8_t msg3[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),cycles,UI64);
	LOG_1(msg2, count2null(msg2),time,UI64);
	LOG_0(msg3, count2null(msg3));
#else
	// add BBB
#endif
}

void log_profiler() {
#ifdef FRDM
	uint8_t print[35] = "\n   Test message for profiler. \0";
	timer_start();
	LOG_0(print, count2null(print));
	uint64_t cycles = timer_end();
	uint64_t time = count_to_time(cycles);
	uint8_t msg1[50] = "\nLOG runtime: \0";
	uint8_t msg2[10] = " cycles, \0";
	uint8_t msg3[10] = " us, \0";
	LOG_1(msg1, count2null(msg1),cycles,UI64);
	LOG_1(msg2, count2null(msg2),time,UI64);
	LOG_0(msg3, count2null(msg3));
#else
	// add BBB
#endif
}

void profiler_tests() {
#ifdef FRDM
	init_timer();
#endif
	my_memmove_profiler(10);
	my_memmove_profiler(100);
	my_memmove_profiler(1000);
	my_memmove_profiler(5000);
#ifdef FRDM
	memmove_profiler(10);
	memmove_profiler(100);
	memmove_profiler(1000);
	memmove_profiler(5000);
#endif

	my_memzero_profiler(10);
	my_memzero_profiler(100);
	my_memzero_profiler(1000);
	my_memzero_profiler(5000);
#ifdef FRDM
	memset_profiler(10);
	memset_profiler(100);
	memset_profiler(1000);
	memset_profiler(5000);
#endif

	my_reverse_profiler(10);
	my_reverse_profiler(100);
	my_reverse_profiler(1000);
	my_reverse_profiler(5000);

	my_itoa_profiler();
	my_ftoa_profiler();
	my_atoi_profiler();

	malloc_empty_profiler(10);
	malloc_empty_profiler(100);
	malloc_empty_profiler(500);
	malloc_empty_profiler(1000);

	malloc_nonempty_profiler(10);
	malloc_nonempty_profiler(100);
	malloc_nonempty_profiler(500);
	malloc_nonempty_profiler(1000);

	free_profiler(10);
	free_profiler(100);
	free_profiler(500);
	free_profiler(1000);

	circbuf_add_profiler();
	circbuf_remove_profiler();

	log_profiler();
}

#endif
