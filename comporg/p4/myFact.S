.text
.p2align
.global main
main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     x19, x20, [sp, -16]!
    stp     x21, x22, [sp, -16]!
    stp     x23, x24, [sp, -16]!

    mov     x1, 7
    mov     x0, 8
    bl      myFact
    ldr     x0, =printFloat
    bl      printf



    mainExit:
        ldp     x23, x24, [sp], 16 
        ldp     x21, x22, [sp], 16 
        ldp     x19, x20, [sp], 16 
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret

myFact:    stp     x29, x30, [sp, -16]!

    ldr     x1, =factorials
    ldr     d0, [x1, x0]
    
    ldp     x29, x30, [sp], 16
ret

.data

factorials: .double 2, 24, 720, 40320, 3628800, 479001600, 87178291200, 20922789888000, 6402373705728000, 2432902008176640000
printFloat: .asciz  "%.04f"
printLU:    .asciz "%lu\n"

.end