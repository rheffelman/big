// Ryan Heffelman
// Perry Kivolowitz
// CSC 3510 - Computer Organization
// March 24, 2024
// I had no partner.
// strlen can be dangerous in cases of strings that aren't null-terminated.
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

    mov     x26, 0
    mov     x25, 0
    mov     x24, 0
    mov     x23, 0
    mov     x22, 0
    mov     x21, 0
    mov     x20, 0

    mov     x27, x1 // store *argv[] on x27
    ldr     x5, [x27, 8]
    cbz     x5, noArgs


    //mov     x1, -5
    //ldr     x0, =printint
    //bl      printf
    //b       mainExit

    // open filepath, put fd on x22
    ldr     x0, [x27, 8]
    mov     x1, 2
    bl      open
    cmp     x0, 0
    bmi     couldntOpen
    mov     x22, x0 // stores filepath on x22

    //ldr     x0, =printint
    //mov     x1, 69
    //bl      printf

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

    bl      MyGetLine
    bl      printCircularBuffer

    b       mainExit

    couldntOpen:
        ldr     x0, =badopen
        bl      perror
        b       mainExit

    noArgs: 
        ldr     x0, =usage
        bl      printf
        b       mainExit


mainExit:
    ldr     x0, =exited
    bl      printf
    ldp     x26, x27, [sp], 16
    ldp     x24, x25, [sp], 16
    ldp     x22, x23, [sp], 16 
    ldp     x20, x21, [sp], 16 
    ldp     x29, x30, [sp], 16
    mov     x0, xzr
ret

printCircularBuffer: stp     x29, x30, [sp, -16]!
    mov     x26, x25

    recursivelyPrintAndFree:
        cmp     x26, 80
        bpl     resetPrintCounter

        // print current index
        ldr     x1, [x24, x26]
        cbz     x1, skip // skip if null instead of printing
        ldr     x0, =fmt
        bl      printf

        // free 
        ldr     x0, [x24, x26]
        bl      free

        // if we're back to the start, we're done
        add     x5, x26, 8 // off by one
        cmp     x25, x5
        beq     exitPrintCircularBuffer

        // increment and recurse
        add     x26, x26, 8
        b       recursivelyPrintAndFree

    skip:
        add     x26, x26, 8
        b       recursivelyPrintAndFree

    resetPrintCounter:
    mov     x26, 0
    b       recursivelyPrintAndFree

    exitPrintCircularBuffer:
        mov     x0, x24
        bl      free
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret

// LEGEND:
// x20 buffer of 4096 bytes.
// x21 = counting variable for use on x20.
// x22 = opened file file descriptor
MyGetLine: stp     x29, x30, [sp, -16]!

    precursion:
        mov     x21, 0
        // allocate 4096 bytes, put bytes on x20.
        mov     x0, 100
        bl      malloc
        mov     x20, x0 // stores 4096 bytes on x20

        // memset bytes to null
        mov     x0, x20
        mov     x1, 0x0
        mov     x2, 100
        bl      memset
        mov     x20, x0

        recursion:
            cmp     x21, 100
            beq     lineIsTooLong

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

lineIsTooLong:
    mov     x0, 10
    str     x0, [x20, x21] // add NL to end of buffer
    add     x21, x21, 1
    mov     x0, 0
    str     x0, [x20, x21] // add null terminator to end of buffer

    lsr     x5, x25, 3
    cmp     x5, 10
    beq     resetCounter3

    // free what was previously in it's place
    ldr     x0, [x24, x25]
    bl      free

    // add it, then increment index counter
    str     x20, [x24, x25]
    add     x25, x25, 8

    b       readTillNullOrNL

    resetCounter3:
        mov     x25, 0
        b       lineIsTooLong

    readTillNullOrNL:
        mov     x0, x22
        ldr     x1, =tempBuffer
        mov     x2, 1
        bl      read
        cbz     x0, GLExit

        cmp     x1, 10
        beq     precursion
        
        b       readTillNullOrNL

insertButKeepReading:
    lsr     x5, x25, 3
    cmp     x5, 10
    beq     resetCounter

    ldr     x0, [x24, x25]
    bl      free

    str     x20, [x24, x25]
    add     x25, x25, 8
    b       precursion

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
tempBuffer: .space 1
exited:     .asciz "\nexited\n"
fmt:        .asciz  "%s"
filepath:   .asciz "5.S"
printint:   .asciz "%d\n"

// usage is printed if you don't specify a file as your command line argument.
usage:		.asciz	"File name must be given.\n"

// badopen is printed if the file specified doesn't open. It is used with perror().
badopen:	.asciz	"Open file failed"

// noline is printed if the 4096 character array used to read text cannot be allocated.
noline:		.asciz	"Allocating line buffer failed."

// badtail is printed if a TAILLEN long array of pointers to char cannot be allocated.
badtail:	.asciz	"Allocating tail pointer buffer failed."

// badalloc is printed when malloc fails to allocate 4096 bytes for a tail.
badalloc:	.asciz	"Allocating a tail line failed."

.end 

// 1 line
// 2 line
// 3 line
// 4 line
// 5 line
// 6 line 6 line 6 line6 line6 line6 line 6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line6 line
// 7 line
// 8 line
// 9 line
// 10 line