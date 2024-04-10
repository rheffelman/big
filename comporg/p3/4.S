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


    //bl      MyGetLine
    bl      printCircularBuffer
    //bl      dataVacuum3000

mainExit:
    ldp     x26, x27, [sp], 16
    ldp     x24, x25, [sp], 16
    ldp     x22, x23, [sp], 16 
    ldp     x20, x21, [sp], 16 
    mov     sp, x29
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

dataVacuum3000: stp     x29, x30, [sp, -16]!
    ldr     x0, [x24]
    bl      free
    ldr     x0, [x24, 8]
    bl      free
    ldr     x0, [x24, 16]
    bl      free
    ldr     x0, [x24, 24]
    bl      free
    ldr     x0, [x24, 32]
    bl      free
    ldr     x0, [x24, 40]
    bl      free
    ldr     x0, [x24, 48]
    bl      free
    ldr     x0, [x24, 56]
    bl      free
    ldr     x0, [x24, 64]
    bl      free
    ldr     x0, [x24, 72]
    bl      free
    mov     x0, x24
    bl      free

    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

printCircularBuffer: stp     x29, x30, [sp, -16]!
    // print/free first element in buffer if it exists.
    ldr     x1, [x24, x25]
    cbz     x1, exitPrintBuffer // if there's nothing read in at the current index, there is nothing in the file.
    ldr     x0, =fmt
    bl      printf

    
    lsr     x26, x25, 3 // 64 >> 3 = 8, so x26 = 8 for example.
    add     x26, x26, 1 // 

    recursivelyPrintAndFree:
        cmp     x26, 10
        bpl     resetPrintCounter

        //lsl
        lsl     x5, x26, 3
        ldr     x1, [x24, x5]
        cbz     x1, skip
        ldr     x0, =fmt
        bl      printf

        lsl     x5, x26, 3
        ldr     x0, [x24, x5]
        //ldr     x0, [x24, x26]
        bl      free

        lsl     x5, x26, 3
        cmp     x26, x5
        beq     exitPrintCircularBuffer

        add     x26, x26, 1
        b       recursivelyPrintAndFree

    skip:
        add     x26, x26, 1
        b       recursivelyPrintAndFree

    resetPrintCounter:
    mov     x26, 0
    b       recursivelyPrintAndFree

    exitPrintCircularBuffer:
        //ldr     x0, [x24, x25]
        //bl      free
        //mov     x0, x24
        //bl      free
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret

printBuffer: stp     x29, x30, [sp, -16]!
    ldr     x1, [x24, x25]
    ldr     x0, =fmt
    bl      printf
    
    badLabel:
        cmp     x26, 9
        beq     exitPrintBuffer

        add     x25, x25, 8
        cmp     x25, 80
        bpl     otherBadLabel

        ldr     x1, [x24, x25]
        ldr     x0, =fmt
        bl      printf
        
        add     x26, x26, 1
        b       badLabel

        otherBadLabel:
            mov     x25, 0
            ldr     x1, [x24, x25]
            ldr     x0, =fmt
            bl      printf

            add     x26, x26, 1
            b       badLabel

exitPrintBuffer:
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

// LEGEND:
// x20 buffer of 4096 bytes.
// x21 = counting variable for use on x20.
// x22 = opened file file descriptor
MyGetLine: stp     x29, x30, [sp, -16]!

    // open filepath, put fd on x22
    ldr     x0, =filepath
    mov     x1, 2
    bl      open
    mov     x22, x0 // stores filepath on x22

    preRecursion:
        mov     x21, 0
        // allocate 4096 bytes, put bytes on x20.
        mov     x0, 4096
        bl      malloc
        mov     x20, x0 // stores 4096 bytes on x20

        // memset bytes to null
        mov     x0, x20
        mov     x1, 0x0
        mov     x2, 4096
        bl      memset
        mov     x20, x0

        recursion:
            mov     x0, x22 // arg1 = fd
            add     x1, x20, x21 // arg2 x1 = x20 + x21
            mov     x2, 1 // arg3
            bl      read // read(arg1, arg2, arg3)
            cbz     x0, insertButStopReading // if read returns null, exit.
            ldr     x5, [x20, x21]
            cmp     x5, 10
            beq     insertButKeepReading
            cmp     x5, 0
            beq     insertButStopReading
            
            add     x21, x21, 1
            b       recursion
    
insertButKeepReading:
    lsr     x5, x25, 3
    cmp     x5, 10
    beq     resetCounter

    ldr     x0, [x24, x25]
    bl      free

    str     x20, [x24, x25]
    add     x25, x25, 8
    b       preRecursion

    resetCounter:
    mov     x25, 0
    b       insertButKeepReading

insertButStopReading:
    lsr     x5, x25, 3
    cmp     x5, 10
    beq     resetCounter2

    ldr     x0, [x24, x25]
    bl      free

    str     x20, [x24, x25]
    add     x25, x25, 8
    b       GLExit

    resetCounter2:
        mov     x25, 0
        b       insertButStopReading
        
    GLExit:
    mov     x0, x22
    bl      close
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

.data
exited:     .asciz "exited\n"
fmt:        .asciz  "%s"
filepath:   .asciz "3.S"
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
// 5 line
// 6 line
// 7 line
// 8 line
// 9 line
// 10 line