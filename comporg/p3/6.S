.text
.global main
.EQU        TAILLEN, 10

main:   
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     x20, x21, [sp, -16]!
    stp     x22, x23, [sp, -16]!
    stp     x24, x25, [sp, -16]! // x24 = circuluar buffer. x25 = write index.
    stp     x26, x27, [sp, -16]!

    mov     x27, 0
    mov     x26, 0
    mov     x25, 0
    mov     x24, 0
    mov     x23, 0
    mov     x22, 0
    mov     x21, 0
    mov     x20, 0

    // allocate 80 bytes 
    mov     x0, 80
    bl      malloc
    cbz     x0, mainExit
    mov     x24, x0 // store 80 bytes for 8 pointers on x24

    mov     x0, x24
    mov     x1, 0x0
    mov     x2, 80
    bl      memset
    mov     x24, x0

    mov     x0, 1
    str     x0, [x24]

    mov     x0, 2
    str     x0, [x24, 8]

    mov     x0, 3
    str     x0, [x24, 16]

    mov     x0, 4
    str     x0, [x24, 24]

    mov     x0, 5
    str     x0, [x24, 32]

    mov     x0, 6
    str     x0, [x24, 40]

    mov     x0, 7
    str     x0, [x24, 48]

    mov     x0, 8
    str     x0, [x24, 56]

    mov     x0, 9
    str     x0, [x24, 64]

    mov     x0, 10
    str     x0, [x24, 72]

    //bl      MyGetLine
    bl      printCircularBuffer
    //bl      dataVacuum3000
    b       mainExit

mainExit:
    ldr     x0, =exited
    bl      printf
    ldp     x26, x27, [sp], 16
    ldp     x24, x25, [sp], 16
    ldp     x22, x23, [sp], 16 
    ldp     x20, x21, [sp], 16 
    mov     sp, x29
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

printCircularBuffer: stp     x29, x30, [sp, -16]!

    mov     x26, x25
    add     x26, x26, 8
    ldr     x1, [x24, x26]
    cbz     x1, exitPrintCircularBuffer // if there's nothing read in at the current index, there is nothing in the file.
    ldr     x0, =fmt
    bl      printf


    recursivelyPrintAndFree:
        cmp     x26, 80
        bpl     resetPrintCounter

        ldr     x1, [x24, x26]
        cbz     x1, skip
        ldr     x0, =fmt
        bl      printf

        // free 
        ldr     x0, [x24, x26]
        bl      free

        add     x5, x26, 8 // off by one
        cmp     x25, x5
        beq     exitPrintCircularBuffer

        add     x26, x26, 8
        b       recursivelyPrintAndFree

    skip:
        add     x26, x26, 8
        b       recursivelyPrintAndFree

    resetPrintCounter:
    mov     x26, 0
    b       recursivelyPrintAndFree

    exitPrintCircularBuffer:
        ldr     x0, [x24, x25]
        bl      free
        mov     x0, x24
        bl      free
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret

.data
exited:     .asciz "\nexited\n"
fmt:        .asciz  "%d\n"
filepath:   .asciz "test1.txt"
printint:   .asciz "%d\n"

// usage is printed if you don't specify a file as your command line argument.
usage:		.asciz	"File name must be given."
// badopen is printed if the file specified doesn't open. It is used with perror().
badopen:	.asciz	"Open file failed"
// noline is printed if the 4096 character array used to read text cannot be allocated.
noline:		.asciz	"Allocating line buffer failed."
// badtail is printed if a TAILLEN long array of pointers to char cannot be allocated.
badtail:	.asciz	"Allocating tail pointer buffer failed."
// badalloc is printed when malloc fails to allocate 4096 bytes for a tail.
badalloc:	.asciz	"Allocating a tail line failed."

l1:         .asciz  "1 line"
l2:         .asciz  "2 line"
l3:         .asciz  "3 line"
l4:         .asciz  "4 line"
l5:         .asciz  "5 line"
l6:         .asciz  "6 line"
l7:         .asciz  "7 line"
l8:         .asciz  "8 line"
l9:         .asciz  "9 line"
l10:         .asciz  "10 line"

.end 

// 1 line
// 2 line
// 3 line
// 4 line
// 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line 5 line
// 6 line
// 7 line
// 8 line
// 9 line
// 10 line