/*************************************************************************
*
*   Filename:main.c
*   Description: Implements the unit tests for my circbuf.c and circbuf.h files
*
*   Author: Dylan Way and Kathy Grimes
*
**************************************************************************/
#include "circbuf.c"

int main()
{
    uint8_t pass_cnt = 0;
    int8_t error = 0;
    int8_t error2 = 0;    

    // Initialize should return a valid pointer of heap when heap is available and should error if allocation is bigger than expected
    CircBuf_t *myCB = buffer_init(5);
    uint8_t CB_size = sizeof(myCB);
    if( (myCB != NULL) && (CB_size == 8) ) {
        printf("CB UNIT TEST: 1/9 <Circular Buffer Init>.....................PASS\n"); 
        pass_cnt++;
    }
    else {
        printf("CB UNIT TEST: 1/9 <Circular Buffer Init>.....................FAIL\n	CB_size = %d\n", CB_size);
    }

    // Test that buffer full returns true/false for empty/non-empty/full conditions
    error = 0;
    add_buffer_item(myCB, 1); 
    add_buffer_item(myCB, 2); 
    add_buffer_item(myCB, 3); 
    add_buffer_item(myCB, 4);
    if( buffer_full(myCB) == FULL ) {error = 1;} 
    add_buffer_item(myCB, 5); 
    if( buffer_full(myCB) != FULL ) {error = 2;}
    if( error == 1 ) {
        printf("CB UNIT TEST: 2/9 <Circular Buffer Full>.....................FAIL\n  Buffer falsely identified as full\n");
    }
    else if( error == 2 ) {
        printf("CB UNIT TEST: 2/9 <Circular Buffer Full>.....................FAIL\n  Full buffer not identified\n");
    }
    else {
        printf("CB UNIT TEST: 2/9 <Circular Buffer Full>.....................PASS\n");
        pass_cnt++;
    }

    // Test that Add item to the buffer works correctly: fill completely - checks current items added/size to see this is full
    if(((*(myCB->buffer)) == 1) && ((*(myCB->buffer+1)) == 2) && ((*(myCB->buffer+2)) == 3) && ((*(myCB->buffer+3)) == 4) && ((*(myCB->buffer+4)) == 5)) { 
        printf("CB UNIT TEST: 3/9 <Circular Buffer Fill Completely>..........PASS\n");
        pass_cnt++;
    }
    else {
        printf("CB UNIT TEST: 3/9 <Circular Buffer Fill Completely>..........FAIL\n");    
        printf("%d %d %d %d %d \n", (*(myCB->buffer)), (*(myCB->buffer+1)), (*(myCB->buffer+2)), (*(myCB->buffer+3)), (*(myCB->buffer+4)));
    }

    // Test that Add item to the buffer works correctly: error on overfill
    error = add_buffer_item(myCB, 6);
    if(error == FULL) {
        printf("CB UNIT TEST: 4/9 <Circular Buffer Add Item When Full>.......PASS\n");
        pass_cnt++;
    }
    else {
        printf("CB UNIT TEST: 4/9 <Circular Buffer Add Item When Full>.......FAIL\n");
    }

    // Test that Add item to the buffer works correctly: wraps around at boundary
    error = 0; 
    uint8_t item;
    uint8_t *item_ptr = &item;
    remove_buffer_item(myCB, item_ptr);
    remove_buffer_item(myCB, item_ptr);
    error = add_buffer_item(myCB, 7);
    error2 = add_buffer_item(myCB, 8);
    if( error || error2 || (*(myCB->buffer) != 7) || (*(myCB->buffer + 1) != 8) ) {
        printf("CB UNIT TEST: 5/9 <Circular Buffer Add Item Wrapping>........FAIL\n");
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
    }
    else if( error == 2 ) {
        printf("CB UNIT TEST: 6/9 <Circular Buffer Empty>....................FAIL\n  Empty buffer not identified\n");
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
    }

    // Remove an item from the buffer: should wrap around at boundary
    myCB->head = (myCB->buffer + 3);
    myCB->tail = (myCB->buffer + 3);
    myCB->num_items = 0;
    add_buffer_item(myCB, 1);
    add_buffer_item(myCB, 2);
    add_buffer_item(myCB, 3);

    remove_buffer_item(myCB, item_ptr);
    remove_buffer_item(myCB, item_ptr);
    remove_buffer_item(myCB, item_ptr);
    if( item == 3 ) {
        printf("CB UNIT TEST: 8/9 <Circular Buffer Remove Item Wrapping>.....PASS\n");
        pass_cnt++;
    }
    else {
        printf("CB UNIT TEST: 8/9 <Circular Buffer Remove Item Wrapping>.....FAIL\n  The remove_buffer_item function did not correctly wrap back to the beginning of the circular buffer and remove the first item\n");
    }
    remove_buffer_item(myCB, item_ptr);
    
    // Destroy should free memory back to malloc    
    destroy_buffer(&myCB);
    if( myCB != NULL ) {
        printf("CB UNIT TEST: 9/9 <Circular Buffer Destroy>..................FAIL\n  myCB = %lu", (uint64_t) myCB);
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
        printf("FAIL (%d/9 PASS)", pass_cnt);
    }
     
    return 0;
}
