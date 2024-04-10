.text
.p2align
.global main
main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     d19, d20, [sp, -16]!
    stp     d21, d22, [sp, -16]!
    stp     d25, d26, [sp, -16]!

    ldr     d26, sixtyNine
    ldr     d20, otherVal
    
    // print before cos() call
    fmov    d0, d26
    ldr     x0, =printFloat
    bl      printf
    
    fmov    d0, d25
    bl      cos

    // print after cos() call
    fmov    d0, d26
    ldr     x0, =printFloat
    bl      printf

    mainExit:
        ldp     d25, d26, [sp], 16
        ldp     d21, d22, [sp], 16
        ldp     d19, d20, [sp], 16 // d19 RESTORED ON MAIN EXIT
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--
.data
    sixtyNine:   .double     69
    otherVal:    .double     1
    printFloat:  .asciz      "%.10f\n"
.end