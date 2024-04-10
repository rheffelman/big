.text
.global main
main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp

    stp     x20, x21, [sp, -16]! //  x20 = *argv, x21 = current node
    stp     x22, x23, [sp, -16]! //  x22 = numElements, x23 = head pointer.
    str     x27, [sp, -16]!

    mov     x20, x1
    mov     x22, 0
    mov     x23, 0
    add     x20, x20, 8
    bl      readArgs
    mov     x21, x23
    bl      print

exit:
    ldr     x27, [sp], 16
    ldp     x22, x23, [sp], 16
    ldp     x20, x21, [sp], 16
    mov     sp, x29
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
    ret

//--
readArgs:
    stp     x29, x30, [sp, -16]!

    mov     x21, x23
    ldr     x0, [x20], 8
    cbz     x0, RAexit
    bl      atoi

    //mov     x1, x0
    //ldr     x0, =fmt
    //bl      printf

    mov     x27, x0
    bl      insert
    ldr     x1, [x0, 8]
    ldr     x0, =fmt
    bl      printf
    bl      readArgs

RAexit:
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret
/*
x21 = current pointer, gets updated to head each recursion of readArgs function
x22 = numElements
x23 = head pointer
x27 = value we read in inserting
 */
insert:
    stp     x29, x30, [sp, -16]!

    mov     x1, 0
    cmp     x1, x22
    beq     case1 //  if (!numElements) branch case1;

    case1:
        mov     x0, 16
        bl      malloc // Node n = new Node;
        str     x23, [x0]
        str     x27, [x0, 8]
        mov     x23, x0

        ldp     x29, x30, [sp], 16
        mov     x0, 1
    ret

.data
fmt:        .asciz "%d\n"
tw:       .asciz "your test worked!"