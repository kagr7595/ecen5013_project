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
    uint8_t CB_size = sizeof(myCB);
    if( (myCB != NULL) && (CB_size == 8) ) {
        printf("CB UNIT TEST: 1/9 <Circular Buffer Init>.....................PASS\n");
        pass_cnt++;
    }
    else {
        printf("CB UNIT TEST: 1/9 <Circular Buffer Init>.....................FAIL\n	CB_size = %d\n", CB_size);
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
        printf("CB UNIT TEST: 2/9 <Circular Buffer Full>.....................FAIL\n  Buffer falsely identified as full\n");
    }
    else if( error == 2 ) {
        printf("CB UNIT TEST: 2/9 <Circular Buffer Full>.....................FAIL\n  Full buffer not identified\n");
        print_buffer(myCB);
    }
    else {
        printf("CB UNIT TEST: 2/9 <Circular Buffer Full>.....................PASS\n");
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
        printf("CB UNIT TEST: 3/9 <Circular Buffer Fill Completely>..........PASS\n");
        pass_cnt++;
    }
    else {
        printf("CB UNIT TEST: 3/9 <Circular Buffer Fill Completely>..........FAIL\n");
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
    	printf("CB UNIT TEST: 4/9 <Circular Buffer Add Item When Full>.......PASS\n");
        pass_cnt++;
    }
    else {
        printf("CB UNIT TEST: 4/9 <Circular Buffer Add Item When Full>.......FAIL\n");
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
        printf("CB UNIT TEST: 5/9 <Circular Buffer Add Item Wrapping>........FAIL\n");
        print_buffer(myCB);
    }
    else {
        printf("CB UNIT TEST: 5/9 <Circular Buffer Add Item Wrapping>........PASS\n");
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
        printf("CB UNIT TEST: 6/9 <Circular Buffer Empty>....................FAIL\n  Buffer falsely identified as empty\n");
        print_buffer(myCB);
    }
    else if( error == 2 ) {
        printf("CB UNIT TEST: 6/9 <Circular Buffer Empty>....................FAIL\n  Empty buffer not identified\n");
        print_buffer(myCB);
    }
    else {
        printf("CB UNIT TEST: 6/9 <Circular Buffer Empty>....................PASS\n");
        pass_cnt++;
    }

    // Remove an item from the buffer: error on overempty
    error = 0;
    error = remove_buffer_item(myCB, item_ptr);
    if( error == EMPTY) {
        printf("CB UNIT TEST: 7/9 <Circular Buffer Remove Item When Empty>...PASS\n");
        pass_cnt++;
    }
    else {
        printf("CB UNIT TEST: 7/9 <Circular Buffer Remove Item When Empty>...FAIL\n");
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
        printf("CB UNIT TEST: 8/9 <Circular Buffer Remove Item Wrapping>.....PASS\n");
        pass_cnt++;
    }
    else {
        printf("CB UNIT TEST: 8/9 <Circular Buffer Remove Item Wrapping>.....FAIL\n  The remove_buffer_item function did not correctly wrap back to the beginning of the circular buffer and remove the first item\n");
        print_buffer(myCB);
    }
    remove_buffer_item(myCB, item_ptr);

    // Destroy should free memory back to malloc
    destroy_buffer(&myCB);
    if( myCB != NULL ) {
        printf("CB UNIT TEST: 9/9 <Circular Buffer Destroy>..................FAIL\n  myCB = %lu", (uint64_t) myCB);
        print_buffer(myCB);
    }
    else {
        printf("CB UNIT TEST: 9/9 <Circular Buffer Destroy>..................PASS\n");
        pass_cnt++;
    }

    printf("CIRCBUFF UNIT TEST SUITE: ");
    if( pass_cnt == 9 ) {
        printf("PASS\n");
    }
    else {
        printf("FAIL (%d/9 PASS)\n", pass_cnt);
    }
    if (pass_cnt != 9) {
    	return 1;
    }
    return 0;
}

#endif
