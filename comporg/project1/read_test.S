            .p2align   2
            .text
            .global     main

/*  x30     link register
    x29     frame pointer
    x20     address of buffer in RAM into which read will deposit characters.
    x21     counts the number of characters read. 
*/

main:   stp     x29, x30, [sp, -16]!
        stp     x20, x21, [sp, -16]!
        mov     x29, sp
        
        ldr     x20, =buffer
        mov     w21, wzr

// ssize_t read(int fd, void * buffer, size_t length);

1:      mov     w0, 1
        mov     x1, x20
        mov     x2, 1
        bl      read
        cmp     x0, 0
        ble     10f
        // When we get here, read returned 1.
        add     w21, w21, 1
        b       1b
// printf("ajdjgqirhg %d\n", counter);
10:     ldr     x0, =fmt
        mov     w1, w21
        bl      printf

99:     ldp     x20, x21, [sp], 16
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
        ret

        .data

buffer: .space      8
fmt:    .asciz      "Number of bytes read: %d\n"
        .end