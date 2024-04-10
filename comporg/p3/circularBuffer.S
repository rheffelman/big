.text
.global main
.EQU        TAILLEN, 10

main:   
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     x20, x21, [sp, -16]!
    stp     x22, x23, [sp, -16]!
    stp     x24, x25, [sp, -16]!
    stp     x26, x27, [sp, -16]!

    mov     x1, 10 MOD 2
    ldr     x0, =printint
    bl      printf

    // allocate 80 bytes 
    //mov     x0, 80
    //bl      malloc
    //cbz     x0, mainExit
    //mov     x24, x0 // store 80 bytes for 8 pointers on x24



mainExit:
    ldp     x26, x27, [sp], 16
    ldp     x24, x25, [sp], 16
    ldp     x22, x23, [sp], 16 
    ldp     x20, x21, [sp], 16 
    mov     sp, x29
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

//x20 = element inserting
//x25 == writeIndex
//x26 == readIndex
put:    stp     x29, x30, [sp, -16]!
    add     x6, x25, 1
    mov     x2, 0
    umull   


putExit:
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret


.data
exited:     .asciz "exited\n"
fmt:    .asciz  "%s"
filepath: .asciz "test1.txt"
badalloc:	.asciz	"Allocating a tail line failed."
printint:   .asciz "%d\n"
.end