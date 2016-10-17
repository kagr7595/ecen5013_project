/***************************************************************************
*
*  	Filename: buf_utests.c
*	Description: Runs the unit tests for the circular buffer
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _BUF_UTESTS_C
#define _BUF_UTESTS_C

#include <stdint.h>
#include "circbuf.h"
#include "log.h"

uint8_t pass_cnt = 0;
    int8_t error = 0;
    int8_t error2 = 0;

uint8_t buffer_unit_tests() {
    // Initialize should return a valid pointer of heap when heap is available and should error if allocation is bigger than expected
    CircBuf_t *myCB = buffer_init(5);
    uint8_t CB_size = sizeof(*myCB);
#ifdef FRDM
    if( (myCB != NULL) && (CB_size == 20) ) {
        uint8_t print0[256] = "\nCB UNIT TEST: 1/9 <Circular Buffer Init>.....................PASS\0";
        LOG_0(print0,count2null(print0));
        pass_cnt++;
    }
#else
    if( (myCB != NULL) && ((CB_size == 20) || (CB_size == 32)) ) {
        uint8_t print0[256] = "\nCB UNIT TEST: 1/9 <Circular Buffer Init>.....................PASS\0";
        LOG_0(print0,count2null(print0));
        pass_cnt++;
    }
#endif
    else {
        uint8_t print1[256] = "\nCB UNIT TEST: 1/9 <Circular Buffer Init>.....................FAIL\n	CB_size = \0";
        LOG_1(print1,count2null(print1),CB_size,UI8);
        print_buffer(myCB);
    }

    // Test that buffer full returns true/false for empty/non-empty/full conditions
    error = 0;
    add_buffer_item(myCB, '1');
    add_buffer_item(myCB, '2');
    add_buffer_item(myCB, '3');
    add_buffer_item(myCB, '4');
    if( buffer_full(myCB) == FULL ) {error = 1;}
    add_buffer_item(myCB, '5');
    if( buffer_full(myCB) != FULL ) {error = 2;}
    if( error == 1 ) {
        uint8_t print2[256] = "\nCB UNIT TEST: 2/9 <Circular Buffer Full>.....................FAIL\n  Buffer falsely identified as full\0";
	LOG_0(print2,count2null(print2));
    }
    else if( error == 2 ) {
        uint8_t print3[256] = "\nCB UNIT TEST: 2/9 <Circular Buffer Full>.....................FAIL\n  Full buffer not identified\0";
	LOG_0(print3,count2null(print3));
        print_buffer(myCB);
    }
    else {
        uint8_t print4[256] = "\nCB UNIT TEST: 2/9 <Circular Buffer Full>.....................PASS\0";
	LOG_0(print4,count2null(print4));
        pass_cnt++;
    }

    // Test that Add item to the buffer works correctly: fill completely - checks current items added/size to see this is full
    uint8_t items[5];
    remove_buffer_item(myCB, items);
    remove_buffer_item(myCB, items+1);
    remove_buffer_item(myCB, items+2);
    remove_buffer_item(myCB, items+3);
    remove_buffer_item(myCB, items+4);

    if((*items == '1') && ((*(items+1)) == '2') && ((*(items+2)) == '3') && ((*(items+3)) == '4') && ((*(items+4)) == '5')) {
        uint8_t print5[256] = "\nCB UNIT TEST: 3/9 <Circular Buffer Fill Completely>..........PASS\0";
	LOG_0(print5,count2null(print5));
        pass_cnt++;
    }
    else {
        uint8_t print6[256] = "\nCB UNIT TEST: 3/9 <Circular Buffer Fill Completely>..........FAIL\0";
	LOG_0(print6,count2null(print6));
        print_buffer(myCB);
    }

    // Test that Add item to the buffer works correctly: error on overfill
    add_buffer_item(myCB, '1');
    add_buffer_item(myCB, '2');
    add_buffer_item(myCB, '3');
    add_buffer_item(myCB, '4');
    add_buffer_item(myCB, '5');
    error = add_buffer_item(myCB, 6);
    if(error == FULL) {
    	uint8_t print7[256] = "\nCB UNIT TEST: 4/9 <Circular Buffer Add Item When Full>.......PASS\0";
	LOG_0(print7,count2null(print7));
        pass_cnt++;
    }
    else {
        uint8_t print8[256] = "\nCB UNIT TEST: 4/9 <Circular Buffer Add Item When Full>.......FAIL\0";
	LOG_0(print8,count2null(print8));
        print_buffer(myCB);
    }

    // Test that Add item to the buffer works correctly: wraps around at boundary
    error = 0;
    uint8_t item, item2;
    uint8_t *item_ptr = &item;
    uint8_t *item_ptr2 = &item2;
    remove_buffer_item(myCB, item_ptr);
    remove_buffer_item(myCB, item_ptr);
    error = add_buffer_item(myCB, '7');
    error2 = add_buffer_item(myCB, '8');
    if( error || error2 || (*(myCB->buffer) != '7') || (*(myCB->buffer + 1) != '8') ) {
        uint8_t print9[256] = "\nCB UNIT TEST: 5/9 <Circular Buffer Add Item Wrapping>........FAIL\0";
	LOG_0(print9,count2null(print9));
        print_buffer(myCB);
    }
    else {
        uint8_t print10[256] = "\nCB UNIT TEST: 5/9 <Circular Buffer Add Item Wrapping>........PASS\0";
	LOG_0(print10,count2null(print10));
        pass_cnt++;
    }

    // Test that buffer empty retruns true/false for empty/non-empty/full conditions
    error = 0;
    error2 = 0;
    remove_buffer_item(myCB, item_ptr);
    remove_buffer_item(myCB, item_ptr);
    remove_buffer_item(myCB, item_ptr);
    remove_buffer_item(myCB, item_ptr);
    if( buffer_empty(myCB) == EMPTY ) {error = 1;}
    remove_buffer_item(myCB, item_ptr);
    if( buffer_empty(myCB) != EMPTY ) {error = 2;}
    if( error == 1 ) {
        uint8_t print11[256] = "\nCB UNIT TEST: 6/9 <Circular Buffer Empty>....................FAIL\n  Buffer falsely identified as empty\0";
	LOG_0(print11,count2null(print11));
        print_buffer(myCB);
    }
    else if( error == 2 ) {
        uint8_t print12[256] = "\nCB UNIT TEST: 6/9 <Circular Buffer Empty>....................FAIL\n  Empty buffer not identified\0";
	LOG_0(print12,count2null(print12));
        print_buffer(myCB);
    }
    else {
        uint8_t print13[256] = "\nCB UNIT TEST: 6/9 <Circular Buffer Empty>....................PASS\0";
	LOG_0(print13,count2null(print13));
        pass_cnt++;
    }

    // Remove an item from the buffer: error on overempty
    error = 0;
    error = remove_buffer_item(myCB, item_ptr);
    if( error == EMPTY) {
        uint8_t print14[256] = "\nCB UNIT TEST: 7/9 <Circular Buffer Remove Item When Empty>...PASS\0";
	LOG_0(print14,count2null(print14));
        pass_cnt++;
    }
    else {
        uint8_t print15[256] = "\nCB UNIT TEST: 7/9 <Circular Buffer Remove Item When Empty>...FAIL\0";
	LOG_0(print15,count2null(print15));
        print_buffer(myCB);
    }
    destroy_buffer(&myCB);

    // Remove an item from the buffer: should wrap around at boundary
    myCB = buffer_init(5);
    add_buffer_item(myCB, '1');
    add_buffer_item(myCB, '2');
    add_buffer_item(myCB, '3');
    add_buffer_item(myCB, '4');
    add_buffer_item(myCB, '5');

    remove_buffer_item(myCB, item_ptr);
    remove_buffer_item(myCB, item_ptr);
    remove_buffer_item(myCB, item_ptr);

    add_buffer_item(myCB, '6');
    add_buffer_item(myCB, '7');

    // buffer should now contain 6 7 X 4 5
    remove_buffer_item(myCB, item_ptr);
    remove_buffer_item(myCB, item_ptr);
    remove_buffer_item(myCB, item_ptr2);

    // Now the last items removed should be the last (5) and first items (6)
    if( (item == '5') && (item2 == '6') ) {
        uint8_t print16[256] = "\nCB UNIT TEST: 8/9 <Circular Buffer Remove Item Wrapping>.....PASS\0";
	LOG_0(print16,count2null(print16));
        pass_cnt++;
    }
    else {
        uint8_t print17[256] = "\nCB UNIT TEST: 8/9 <Circular Buffer Remove Item Wrapping>.....FAIL\n  The remove_buffer_item function did not correctly wrap back to the beginning of the circular buffer and remove the first item\0";
	LOG_0(print17,count2null(print17));
        print_buffer(myCB);
    }
    remove_buffer_item(myCB, item_ptr);

    // Destroy should free memory back to malloc
    destroy_buffer(&myCB);
    if( myCB != NULL ) {
        uint8_t print18[256] = "\nCB UNIT TEST: 9/9 <Circular Buffer Destroy>..................FAIL\n  myCB = %lu\0";
	LOG_1(print18,count2null(print18),(uint32_t) myCB,UI32);
        print_buffer(myCB);
    }
    else {
        uint8_t print19[256] = "\nCB UNIT TEST: 9/9 <Circular Buffer Destroy>..................PASS\0";
	LOG_0(print19,count2null(print19));
        pass_cnt++;
    }

    uint8_t print20[256] = "\nCIRCBUFF UNIT TEST SUITE: \0";
	LOG_0(print20,count2null(print20));
    if( pass_cnt == 9 ) {
        uint8_t print21[256] = "PASS\n\0";
	LOG_0(print21,count2null(print21));
    }
    else {
        uint8_t print22[256] = "FAIL (\0";
        uint8_t print23[256] = "/9 PASS)\n\0";
    LOG_1(print22,count2null(print22),(uint64_t)pass_cnt,UI8);
    LOG_0(print23,count2null(print23));
    }
    if (pass_cnt != 9) {
    	return 1;
    }
    my_newcharacter('\n',1);
    return 0;
}

#endif
