.text
.global main

main:

    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     x20, x21, [sp, -16]!
    stp     x22, x23, [sp, -16]!
    mov     x21, x1

    ldr     x0, [x21, 8]
    mov     x1, 2
    bl      open
    mov     x22, x0
    ldr     x23, =buffer

    recursiveRead:

        mov     x0, x22
        ldr     x1, =buffer
        mov     x2, 1
        bl      read
        cbz     x0, mainExit
        ldr     x1, [x23]
        cmp     x1, 10
        beq     newlineFound
        b       recursiveRead

    
    newlineFound:
        ldr     x0, =fmt
        bl      printf
        b       mainExit

    mainExit:
    ldp     x22, x23, [sp], 16 
    ldp     x20, x21, [sp], 16 
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret


.data
fmt:        .asciz "New Line Found!\n"
buffer:     .space 1
.end