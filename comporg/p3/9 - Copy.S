.text
.global main
.EQU    TAILLEN, 10

main:

    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     x19, x20, [sp, -16]!
    stp     x21, x22, [sp, -16]!
    stp     x23, x24, [sp, -16]!
    stp     x25, x26, [sp, -16]!
    stp     x27, x28, [sp, -16]!
    
    mov     x19, 0
    mov     x20, 0 // pointer to buffer
    mov     x21, 0 // writeIndex
    mov     x22, 0 // 
    mov     x23, 0 // fd of filePath in *argv[]
    mov     x24, 0 // counter used in getLines
    mov     x25, 0
    mov     x26, 0
    mov     x27, 0 // used in get4096Buffer
    mov     x28, 0

    ldr     x2, [x1, 8]
    cbz     x2, noFileName
    // open file, put file descriptor on x22.
    ldr     x0, [x1, 8]
    mov     x1, 2
    bl      open
    cmp     w0, 0
    bmi     couldntOpen
    mov     x23, x0

    // create buffer, place it on x20
    mov     x0, 80
    bl      malloc
    cbz     x0, badTailAlloc
    mov     x20, x0

    // initialize memory in 80 byte buffer to 0x0
    mov     x0, x20
    mov     x1, 0x0
    mov     x2, 80
    bl      memset

    readAllLines:
    // x27 is 0
        bl      get4096Buffer
    // x27 is pointer to 4096 bytes, all of which are off (0x0).
        bl      getLine
        cmp     x0, -1
        beq     stopReading
        cmp     x0, -2
        beq     overflowCase
    // x27 is a pointer to 4096 bytes with a string in it that is < 4094 bytes.
        bl      shrink4096Buffer
    // x27 = realloc(x27, strlen(x27) + 2)
        bl      writeToBuffer
        b       readAllLines

    stopReading:
        bl      shrink4096Buffer
        bl      writeToBuffer
        bl      prynt
        mov     x0, x20 
        bl      free
        b       mainExit
    
    overflowCase:
        bl      overflow
        b       readAllLines

    noFileName:
        ldr     x0, =usage
        bl      printf
        b       mainExit

    badTailAlloc:
        ldr     x0, =badtail
        bl      printf
        b       mainExit

    couldntOpen:
        ldr     x0, =badopen
        bl      perror

    mainExit:
        ldr     x0, =exited
        bl      printf
        ldp     x27, x28, [sp], 16 
        ldp     x25, x26, [sp], 16 
        ldp     x23, x24, [sp], 16 
        ldp     x21, x22, [sp], 16 
        ldp     x19, x20, [sp], 16 
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--
prynt: stp     x29, x30, [sp, -16]!
    mov     x28, 0
    mov     x24, 0
    lsl     x24, x21, 3

    printEachElem:
        cmp     x24, 80
        beq     resetCounter4

        cmp     x28, 10
        beq     pryntExit

        ldr     x1, [x20, x24]
        ldr     x0, =printString
        bl      printf
        ldr     x0, [x20, x24]
        bl      free
        add     x28, x28, 1
        add     x24, x24, 8
        b       printEachElem

        resetCounter4:
            mov     x24, 0
            b       printEachElem

    pryntExit: 
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--
vacuumCleaner: stp     x29, x30, [sp, -16]! 

    vacuumCleanerExit: 
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--
overflow: stp     x29, x30, [sp, -16]! 
    mov     x1, 10
    mov     x2, 4094
    str     x1, [x27, x2]
    bl      writeToBuffer

    nextNLorNull:
        mov     x0, x23
        ldr     x1, =buffer
        mov     x2, 1
        bl      read
        cbz     x0, overflowExit

        ldr     x0, =buffer
        ldr     x1, [x0]
        cmp     x1, 0
        beq     overflowExit
        cmp     x1, 10
        beq     overflowExit

        b       nextNLorNull

    overflowExit: 
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--
getLine: stp     x29, x30, [sp, -16]! 

    recursiveReadTillNLOrNull:
        cmp     x24, 4094
        beq     returnNegativeTwo

        mov     x0, x23
        add     x1, x27, x24
        mov     x2, 1
        bl      read
        cbz     x0, returnNegativeOne

        ldr     x5, [x27, x24]
        cmp     x5, 10
        beq     exitGetLine
        cmp     x5, 0
        beq     returnNegativeOne

        add     x24, x24, 1
        b       recursiveReadTillNLOrNull

    returnNegativeTwo:
        mov     x24, 0
        ldp     x29, x30, [sp], 16
        mov     x0, -2
    ret
    
    returnNegativeOne:
        mov     x24, 0
        ldp     x29, x30, [sp], 16
        mov     x0, -1
    ret

    exitGetLine:
        mov     x24, 0
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
    ret
//--
// puts a buffer of 4096 bytes on x27
get4096Buffer: stp     x29, x30, [sp, -16]!
    mov     x0, 4096
    bl      malloc
    mov     x27, x0

    // memset bytes to null
    mov     x0, x27
    mov     x1, 0x0
    mov     x2, 4096
    bl      memset
    mov     x27, x0

    get4096BufferExit:
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--
shrink4096Buffer: stp     x29, x30, [sp, -16]!
    //realloc(buffer1, strlen(buffer1) + 2)
    mov     x0, x27
    bl      strlen
    mov     x25, x0

    sub     x6, x25, 1
    ldr     x5, [x27, x6]
    cmp     x5, 10
    bne     appendNewLine  

    shrink:
        mov     x1, x25
        add     x1, x1, 2
        mov     x0, x27
        bl      realloc
        mov     x27, x0
        b      exitShrink4096Buffer

    appendNewLine:
        add     x6, x6, 1
        mov     x4, 10
        str     x4, [x27, x6]
        b       shrink
        
    exitShrink4096Buffer:
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--
// void writeToBuffer (T elem);
writeToBuffer: stp     x29, x30, [sp, -16]!
    startOfWrite:
        cmp     x21, TAILLEN
        beq     resetCounter

        lsl     x5, x21, 3
        ldr     x0, [x20, x5]
        cbz     x0, dontFree
        bl      free

        dontFree:
        lsl     x5, x21, 3 // free() jumbles x5, so need to reinitialize
        str     x27, [x20, x5]
        add     x21, x21, 1

        b       writeExit

    resetCounter:
        mov     x21, 0
        b       startOfWrite

    writeExit:
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--
.data
exited:     .asciz "exited\n"
printString:.asciz "%s"
fmt:        .asciz "New Line Found!\n"
printInt:   .asciz "%d\n"

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

buffer:     .space 1
.end