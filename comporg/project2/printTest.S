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

    //  set up linked list
    mov     x0, 16
    bl      malloc //  Node n = new Node;
    mov     x23, x0 //  head = n;
    mov     x1, 10 //  int x = 10
    str     x1, [x23, 8] //  head->val = x

    mov     x0, 16
    bl      malloc //  Node n = new Node;
    str     x0, [x23] //  head->next = n;
    mov     x1, 20 //  int x = 20;
    ldr     x2, [x23] //  x2 points to head->next
    str     x1, [x2, 8] //  x2->val = x;

    ldr     x0, =normalPrint
    mov     x1, x23
    ldr     x2, [x1, 8]
    ldr     x3, [x23]
    bl      printf

    ldr     x0, =nullNextPrintCase
    ldr     x1, [x23]
    ldr     x2, [x1, 8]
    bl      printf

    ldr     x27, [sp], 16
    ldp     x22, x23, [sp], 16
    ldp     x20, x21, [sp], 16
    mov     sp, x29
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

.data
normalPrint:       .asciz "%p with val %d points to%p\n"
nullNextPrintCase: .asciz "%p with val %d points to null\n"
printCase2:       .asciz ""
.end