        .p2align    2
        .text
        .global     main

main:   stp     x20, x30, [sp, -16]!
        mov     x20, 1

1:      cmp     x20, 11
        beq     2f

        // puts(char *)
        //      x0
        
        ldr     x0, =tick
        bl      puts
        add     x20, x20, 1
        beq     1b

2:        ldp     x20, x30, [sp], 16
        mov     w0, wzr     

        ret

        .data

tick:   .asciz      "Tick"
    .end