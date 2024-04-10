        .p2align    2
        .text
        .global     main
 
main:   stp     x29, x30, [sp, -16]!
        str     x20, [sp, -16]!
        mov     x29, sp
        ldr     x20, =buffer

1:      mov     x0, 0
        mov     x1, x20
        mov     x2, 1
        bl      read
        cmp     x0, 1
        bne     99f
        bl      write
        bmi     writeReturn
        b       1b

99:     
        ldr     x20, [sp], 16
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
        ret

writeReturn:
        bl      perror
        ldr     x20, [sp], 16
        ldp     x29, x30, [sp], 16
        mov     x0, 1
        ret

        .data
buffer: .space      8

        .end