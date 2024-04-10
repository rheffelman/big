.text
.global main
main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp

    ldr     x1, [x1, 16]
    ldr     x0, =fmt
    bl      printf

    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

.data
fmt:    .asciz  "argv[2]: %s\n"
.end