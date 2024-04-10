.text
.global main
/*
x21 = current pointer, gets updated to head each recursion of readArgs function
x22 = numElements
x23 = head pointer
x27 = value we read in inserting
 */
main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     x20, x21, [sp, -16]!
    stp     x22, x23, [sp, -16]!
    str     x27, [sp, -16]!

    mov     x23, xzr
    mov     x21, x23

    mov     x27, 47
    bl      insert

    mov     x27, 12
    bl      insert

    mov     x27, 86
    bl      insert

    mov     x27, 33
    bl      insert

    mov     x27, 59
    bl      insert

    mov     x27, 25
    bl      insert

    mov     x27, 71
    bl      insert

    mov     x27, 5
    bl      insert

    mov     x27, 98
    bl      insert

    mov     x27, 40
    bl      insert

    // 5->12->25->33->40->47->59->71->86->98

    ldr     x0, =head_address
    ldr     x1, [x23]
    bl      printf

    mov     x21, x23
    bl      prynt


exit:
    ldr     x27, [sp], 16
    ldp     x22, x23, [sp], 16
    ldp     x20, x21, [sp], 16
    mov     sp, x29
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

//--  inserts the value in x27
insert:  stp    x29, x30, [sp, -16]!

    cbz     x27, insertExit //  ignore if asked to insert 0

    cmp     x27, 0
    bmi     insertExit //  assert x27 is positive

    mov     x0, 16 //  allocate 16 bytes on the heap for our node.
    bl      malloc
    cbz     x0, badMalloc //  exit and print error message if

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


//--  set x21 to head before calling
prynt:  stp     x29, x30, [sp, -16]!

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
    bl      prynt
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

.data
head_address:   .asciz  "head points to: %x\n"
node_info:      .asciz  "node at 0x%8x contains payload: %lu next: 0x%8x\n"
bad_malloc:     .asciz  "malloc() failed\n"
.end