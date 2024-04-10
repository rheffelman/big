.comm   foo, 4, 4
.global main

main:
    stp     x21, x30, [sp, -16]!
    mov     x21, x1

    ldr     x0, =foo
    mov     x2, #123
    str     x2, [x0]

    ldr     x0, =foo
    ldr     x1, [x0]

    ldr     x0, =fmt
    b      printf
.data
fmt:    .asciz "%d\n"