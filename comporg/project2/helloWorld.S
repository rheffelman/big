.global main

main:
    str     x30, [sp, -16]!
    ldr     x0, =HW

    bl      puts

    ldr     x30, [sp], 16
    mov     x0, xzr

    ret

    .data
HW: .asciz  "Hello World"

    .end