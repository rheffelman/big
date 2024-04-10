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

    mov     x25, 0
    mov     x26, 0

    // allocate 80 bytes 
    mov     x0, 80
    bl      malloc
    cbz     x0, mainExit
    mov     x24, x0 // store 80 bytes for 10 pointers on x24

    bl      MyGL
    bl      printBuffer

mainExit:
    ldp     x26, x27, [sp], 16
    ldp     x24, x25, [sp], 16
    ldp     x22, x23, [sp], 16 
    ldp     x20, x21, [sp], 16 
    mov     sp, x29
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
MyGL: stp     x29, x30, [sp, -16]!

    // open filepath, put fd on x22
    ldr     x0, =filepath
    mov     x1, 2 // flag meaning read/write... probably
    bl      open
    mov     x22, x0 // stores filepath on x22

    preRecursion:
        mov     x21, 0
        // allocate 4096 bytes, put bytes on x20.
        mov     x0, 4096
        bl      malloc
            
        mov     x20, x0 // stores 4096 bytes on x20
        b       recursion
        // memset bytes to null
        mov     x0, x20 // this whole memset thing might be pointless
        mov     x1, 0x0
        mov     x2, 4096
        bl      memset
        mov     x20, x0 

        recursion:
            //cmp     x21, 4094
            //beq     bufferMaxCapacity
            mov     x0, x22 // arg1 = fd
            add     x1, x20, x21 // arg2 x1 = x20 + x21
            mov     x2, 1 // arg3 = 1 (for 1 byte)
            bl      read // read(arg1, arg2, arg3)
            cbz     x0, insertButStopReading // if read returns null.
            ldr     x5, [x20, x21]
            cmp     x5, 10
            beq     insertButKeepReading
            cmp     x5, 0
            beq     insertButStopReading
            
            add     x21, x21, 1
            b       recursion

    GLExit:
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret

insertButKeepReading:
    lsr     x5, x25, 3
    cmp     x5, 10
    beq     resetCounter

    ldr     x0, [x24, x25]
    bl      free
    str     x20, [x24, x25] // store line in circular buffer
    add     x25, x25, 8
    //add     x21, x21, 1
    // set up new buffer to start reading next line into
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
    str     x20, [x24, x25] // store line in circular buffer
    add     x25, x25, 8
    
    b       GLExit

    resetCounter2:
        mov     x25, 0
        b       insertButStopReading

.data
tempBuffer: .space 8
exited:     .asciz "exited\n"
fmt:        .asciz  "%s"
filepath:   .asciz "test3.txt"
badalloc:	.asciz	"Allocating a tail line failed."
printint:   .asciz "%d\n"
.end 
//  hello world