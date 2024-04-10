.text
.global main
// x21 = current pointer, gets updated to head each recursion of readArgs function
// x22 = numElements
// x23 = head pointer
// x27 = value we read in inserting
main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     x20, x21, [sp, -16]!
    stp     x22, x23, [sp, -16]!
    stp     x27, x28, [sp, -16]!
    stp     x24, x25, [sp, -16]!
    //str

    mov     x25, x1 // back up *argv on x25
    mov     x28, 0 //  malloc call count
    mov     x24, 0 //  free call count

    mov     x23, xzr
    mov     x21, x23

    add     x25, x25, 8
    b      readArgs
    stopReading:

    //cbz     x22, exit
    //cbz     x23, exit
    //ldr     x0, =head_address
    //ldr     x1, [x23]
   // bl      printf

    mov     x21, x23
    bl      prynt

    bl      cleanUp

//--
exit:
    ldp     x24, x25, [sp], 16
    ldp     x27, x28, [sp], 16
    ldp     x22, x23, [sp], 16
    ldp     x20, x21, [sp], 16
    mov     sp, x29
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret
//--
readArgs:
    ldr     x0, [x25], 8
    cbz     x0, stopReading
    
    bl      atoi
    mov     x27, x0

    cmp     x0, xzr
    blt     neg

    bl      insert
    b       readArgs

    neg:        
        bl      delete
        b       readArgs
    
//--  inserts the value in x27
insert:  stp    x29, x30, [sp, -16]!

    cbz     x27, insertExit //  ignore if asked to insert 0

    cmp     x27, 0
    bmi     insertExit //  assert x27 is positive

    mov     x0, 16 //  allocate 16 bytes on the heap for our node.
    bl      malloc
    cbz     x0, badMalloc //  exit and print error message if bad malloc

    add     x28, x28, 1 //  increment malloc counter because we called malloc

    str     xzr, [x0]
    str     x27, [x0, 8]
    mov     x27, x0 //  x27 is now a node pointer n where n->next == nullptr and n->val is what was previously in x27

    cbz     x23, case1 //  if (head == nullptr) branch case1

    ldr     x1, [x23, 8]
    ldr     x2, [x27, 8]
    cmp     x2, x1
    beq     case1 
    bmi     case1

    mov     x21, x23
    case2:

        ldr     x1, [x21] //  x1 = current->next
        cmp     x1, 0
        bne     nextNotNull //  current->next is not null, branch nextNotNull

        exitCase2:
        //newNode->next = current->next;
        //current->next = newNode;
        ldr     x1, [x21]
        str     x1, [x27]

        mov     x1, x27
        str     x1, [x21]

        add     x22, x22, 1
        b       insertExit        
        
        nextNotNull:
            ldr     x1, [x21]
            ldr     x2, [x1, 8] //  x2 == current->next->data
            ldr     x3, [x27, 8] //  x3 == 
            cmp     x2, x3
            ble     nextLessThan
            b       exitCase2
            //current->next->data < data
            nextLessThan:
                ldr     x1, [x21]
                mov     x21, x1
                b       case2
    b       insertExit

    //--  in theory this case is branched to when (head == nullptr or head->data >= data)
    case1:
        str     x23, [x27]
        mov     x23, x27
        add     x22, x22, 1
        b       insertExit

    badMalloc:
        ldr     x0, =bad_malloc
        bl      printf
        b       insertExit

    insertExit:
        mov     x21, x23 
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret

//--
delete:  stp    x29, x30, [sp, -16]!
    cbz     x22, deleteExit

    mov     x21, x23 //  making sure current is initialized to head

    mov     x0, x27 //  x27 = abs(x27)
    bl      abs
    mov     x27, x0

    ldr     x1, [x23, 8]
    cmp     x27, x1
    beq     deleteHead
    blt     deleteExit //  if val we're deleting is smaller than the value in head, it doesn't exit in the list.

    //ldr     x21, [x21] //  head is not what needs to be deleted at this point
    search: //  x21 points to the head when entering this recursive function
        ldr     x1, [x21]
        cbz     x1, deleteExit //  if (!current->next) branch deleteExit
        ldr     x2, [x1, 8] //  x2 = current->next->val

        cmp     x27, x2 //  current->val - current->next->val
        beq     deleteNode //  if (searchVal == current->next->val) delete(current->next)
        blt     deleteExit //  if (searchVal < current->next->val) then searchVal is not in the list, we exit.

        ldr     x21, [x21] //  current = current->next
        b       search

        deleteNode: 
        // with args 1 2 3 4 5 -3 list is 1->2->3->4->5->null at this point in FoC
        // in theory deleteNode is branched to when current points to 2

        //--  prints each free
        //ldr     x0, =delete_info
        //mov     x1, x27
        //ldr     x3, [x21]
        //ldr     x2, [x3, 8]
        //bl      printf

        mov     x1, x27
        ldr     x3, [x21]
        mov     x0, x3
        ldr     x2, [x3, 8]
        ldr     x4, [x3]
        str     x4, [x21]
        bl      free
        sub     x22, x22, 1
        add     x24, x24, 1

        //ldr     x0, [x21] // temp = current->next
        //ldr     x1, [x0] //  x1 = current->next->next
        //ldr     x21, [x0] // current->next = current->next->next
        //str     x21, [x1]
        //bl      free
        //sub     x22, x22, 1
        //add     x24, x24, 1
        b       deleteExit



    deleteHead:
        mov     x0, x23
        ldr     x23, [x23]
        bl      free
        add     x24, x24, 1
        sub     x22, x22, 1

    deleteExit:
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret

//--  set x21 to head before calling
prynt:  stp     x29, x30, [sp, -16]!

    ldr     x0, =head_address
    mov     x1, x23
    bl      printf

    recursiveNodePrint:
    cbz     x22, printExit
    ldr     x1, [x21]
    cbz     x1, nullNext

    ldr     x0, =node_info
    mov     x1, x21
    ldr     x2, [x21, 8]
    ldr     x3, [x21]
    bl      printf

    ldr     x1, [x21] //  buffer swap incase ldr x21, [x21] messes something up
    mov     x21, x1
    bl      recursiveNodePrint
    b       printExit

    nullNext: //  here in case normal printcase causes segfault, maybe unnecessary
        ldr     x0, =node_info
        mov     x1, x21
        ldr     x2, [x21, 8]
        mov     x3, xzr
        bl      printf
        b       printExit
    
    printExit:
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret

//--
cleanUp:    stp    x29, x30, [sp, -16]!
    cbz     x22, cleanUpExit
    mov     x21, x23

    dataVacuum3000:
        cbz     x21, cleanUpExit //  if (!current) exit; intended exit.

        // This bit hopefully prevents a case where x21 doesn't point to 
        // what I think it does and it ends up running away deleting things
        // as it goes till null.
        cmp     x24, x28 //  ensure free count >= malloc count
        bpl     cleanUpExit

        mov     x0, x21 //  temp = current;
        ldr     x21, [x21] //  current = current->next
        ldr     x27, [x0, 8]
        bl      free //  free(temp)
        add     x24, x24, 1 //  increment free counter

        //--  this prints each value that it deletes... I think
        //ldr     x0, =deleted
        //mov     x1, x27
        //bl      printf
        
        b       dataVacuum3000

    cleanUpExit:
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--
.data
head_address:   .asciz  "head points to: %x\n"
node_info:      .asciz  "node at 0x%8x contains payload: %lu next: 0x%8x\n"
bad_malloc:     .asciz  "malloc() failed\n"
deleted:        .asciz  "deleted node containing val: %lu \n"
delete_info:    .asciz  "DELETE: searchVal: %lu, current->next->val: %lu\n"
.end