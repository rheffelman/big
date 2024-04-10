.text
.global main
.EQU        TAILLEN, 10

main:
    stp     x29, x30, [sp, -16]!
    stp     x20, x21, [sp, -16]! // x20 = fd, x21 = temporary buffer in GL
    stp     x22, x23, [sp, -16]! // x22 = index counter for buffer in GL, x23 = other counting var
    mov     x29, sp
    
    bl      myGetLine
    
    mov     x1, x21
    ldr     x0, =fmt
    bl      printf


mainExit2:
    ldr     x0, =fmt2
    bl      printf
    mov     sp, x29
    ldr     x20, [sp], 16
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

myGetLine:
    stp     x29, x30, [sp, -16]!

    ldr     x0, =filepath
    mov     x1, 2 // 2 is flag that means read/write
    bl      open
    mov     x20, x0 // store fd open() returns

    ldr     x21, =buffer // x21 should now be 4096 bytes of 0x0 on stack?
    mov     x22, 0 // initialize x22 (which is index counter)

    readTillNL:
    mov     x0, x20
    mov     x1, x21
    mov     x2, 1
    bl      read
    cmp     x0, 1
    bne     myGLExit

    ldr     x5, [x1]
    cmp     x5, 10
    beq     GLExit2

    //str     x0, [x21, x22]
    add     x22, x22, 1

    b       readTillNL

    myGLExit:
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

    GLExit2:
    ldr     x0, =fmt2
    bl      printf

    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret


.data
filepath: .asciz "test1.txt"
flags: .word 2
buffer: .space  4096, 0x0
newline: .asciz "\n"
fmt:    .asciz  "%s"
fmt2:   .asciz "GLExit2\n"
.end
