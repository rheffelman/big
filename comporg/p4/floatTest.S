.text
.p2align
.global main

main:

    stp     x29, x30, [sp, -16]!
    mov     x29, sp

    ldr     x5, =factorials
    ldr     d0, [x5, 32]
    ldr     x0, =printFloat
    bl      printf
    

    ldp     x29, x30, [sp], 16
    mov     x0, xzr
    ret

.data
sixtyNine: .double      69
pi:     .double     0.01745329251994329576923690768488612713442871888
printFloat: .asciz      "%f\n"
factorials: .double 2, 24, 720, 40320, 3628800, 479001600, 87178291200, 20922789888000, 6402373705728000, 2432902008176640000
.end