.text
.global main

main:

    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     x20, x21, [sp, -16]!
    stp     x22, x23, [sp, -16]!
    stp     x24, x25, [sp, -16]! // x24 = circuluar buffer. x25 = write index.
    stp     x26, x27, [sp, -16]!
    str     x28, [sp, -16]!
    mov     x28, x1

    mov     x20, 0 // pointer to buffer
    mov     x21, 0 // buffer
    mov     x22, 0
    mov     x23, 0 // fd
    mov     x24, 0
    mov     x25, 0
    mov     x26, 0
    mov     x27, 0

    // create buffer, place it on x20
    mov     x0, 80
    bl      malloc
    mov     x20, x0

    mov     x0, 4096
    bl      malloc
    mov     x21, x0
    str     x21, [x20]

    // memset bytes to null
    mov     x0, x21
    mov     x1, 0x0
    mov     x2, 4096
    bl      memset
    mov     x21, x0

    // open file, put returned fd on x23
    ldr     x0, [x28, 8]
    mov     x1, 2
    bl      open
    mov     x23, x0

    mov     x0, x23
    mov     x1, x21
    mov     x2, 10
    bl      read

    mov     x0, x21
    bl      strlen
    mov     x1, x0
    add     x1, x1, 2
    mov     x0, x21
    bl      realloc
    mov     x21, x0
    str     x21, [x20]
    
    ldr     x1, [x20]
    ldr     x0, =printString
    bl      printf

    ldr     x0, [x20]
    bl      free
    mov     x0, x20
    bl      free
    mainExit:
        //ldr     x0, =exited
        //bl      printf
        
        
        ldr     x28, [sp], 16
        ldp     x26, x27, [sp], 16
        ldp     x24, x25, [sp], 16
        ldp     x22, x23, [sp], 16 
        ldp     x20, x21, [sp], 16 
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
.data
exited:     .asciz "exited\n"
printString:.asciz "%s"
fmt:        .asciz "New Line Found!\n"
printInt:   .asciz "%d\n"
buffer:     .space 1
.end