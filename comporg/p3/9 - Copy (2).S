// Ryan Heffelman
// Perry Kivolowitz
// CSC 3510 - Computer Organization
// Thursday, March 28, 2024
// Project 3

// This is my own code, I did not work with a partner.

// strlen() can be unsafe if your string isn't properly null terminated.

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
    mov     x22, 0 
    mov     x23, 0 // fd of filePath in *argv[1]
    mov     x24, 0
    mov     x25, 0
    mov     x26, 0
    mov     x27, 0 // where line buffers are often put
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
        cmp     x0, -1
        beq     cleanUp
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
        b       mainExit

    cleanUp: 
        bl      vacuumCleaner

    mainExit:
        // ldr     x0, =exited
        // bl      printf
        ldp     x27, x28, [sp], 16 
        ldp     x25, x26, [sp], 16 
        ldp     x23, x24, [sp], 16 
        ldp     x21, x22, [sp], 16 
        ldp     x19, x20, [sp], 16 
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret

//--
/*
void prynt(char * buffers[], int writeIndex);

Prints all the strings in the circular buffer in the order they'd naturally appear
in the file, and then deallocating the buffers which contain the strings.

Parameters:
        x20     pointer to the buffer.
        x21     index of the last element written.

 */
prynt: stp     x29, x30, [sp, -16]!
    mov     x28, 0
    mov     x24, 0
    lsl     x24, x21, 3

    printEachElem:
        cmp     x24, 80
        beq     resetCounter4

        cmp     x28, TAILLEN
        beq     pryntExit

        ldr     x1, [x20, x24]
        cbz     x1, skipPrint
        ldr     x0, =printString
        bl      printf
        ldr     x0, [x20, x24]
        bl      free

        skipPrint:
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
/*
 */
overflow: stp     x29, x30, [sp, -16]! 

    mov     x1, 10
    mov     x2, 4094
    strb    w1, [x27, x2]
    bl      writeToBuffer

    nextNLorNull:
        mov     x0, x23
        ldr     x1, =buffer
        mov     x2, 1
        bl      read
        cbz     x0, overflowExit

        ldr     x0, =buffer
        ldrb    w1, [x0]
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
/*
void *getLine(int fd, void * b);

This reads byte by byte from the file descriptor fd into the buffer b until:
#1 we read in a newline character (10)
#2 we read in a null character or eof
#3 read returns 0
#4 we've read 4094 bytes without the first 3 exit conditions happening.

Parameters:
        x23     it will read from the file descriptor in x23.
        x27     it will read into the buffer pointed to by x27 byte by byte.

Returns:
        x0      Returns 0 in x0 if it exits through the aforementioned condition #1 (it reads in 10/a newline).
                Returns -1 in x0 if condition #2 or #3 (reads in 0/eof or read returns 0).
                Returns -2 in x0 if condition #4
 */
getLine: stp     x29, x30, [sp, -16]! 

    recursiveReadTillNLOrNull:
        cmp     x24, 4094
        bpl     returnNegativeTwo

        mov     x0, x23
        add     x1, x27, x24
        mov     x2, 1
        bl      read
        cbz     x0, returnNegativeOne

        ldrb    w5, [x27, x24]
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
/*
void *get4096Buffer();

This allocates 4096 bytes, sets them to 0, and returns a pointer to the first byte.

Returns:
        x27     pointer to the allocated memory. If malloc fails, x27 will be untouched.
        x0      returns -1 to x0 if malloc fails to allocate the memory. otherwise returns 0.
 */
get4096Buffer: stp     x29, x30, [sp, -16]!
    // allocate 4096 bytes
    mov     x0, 4096
    bl      malloc
    cbz     x0, mallocFail
    mov     x27, x0

    // memset bytes to null
    mov     x0, x27
    mov     x1, 0
    mov     x2, 4096
    bl      memset
    mov     x27, x0

    b       get4096BufferExit

    mallocFail:
        ldr     x0, =noline
        bl      printf
        ldp     x29, x30, [sp], 16
        mov     x0, -1
    ret

    get4096BufferExit:
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret

//--
/*
void *shrink4096Buffer(void * b);

"You are to dynamically allocate a perfectly sized buffer to hold the finalized line"

This takes a buffer b containing a string and effectively does b = realloc(b, strlen(b) + 2);.
If b[strlen(b) - 1] != a newline, it appends a newline. This is for the case where our string
is null terminated but there's no newline before the null terminator (often the last line of a file),
in order to follow part of the spec.

Parameters:
        x27     pointer to a buffer 4096 bytes in size containing a string.

Returns:
        x27     puts a "perfectly" shrunken down version of the buffer from the parameters back in x27.
 */
shrink4096Buffer: stp     x29, x30, [sp, -16]!
    // what happens if you do strlen(0)?
    mov     x0, x27
    bl      strlen
    mov     x25, x0

    // (in case last line doesnt end in newline->null terminator)
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
/*
void writeToBuffer (char * buffers[], void * b);

This writes/inserts the buffer in x27 to our circular buffer in x20. 
It also deallocates what was previously in buffers[writeIndex] if it's non-null.
This is the only function which modifies x21 (writeIndex), it handles that internally
so I didn't put it down as a return value or parameter.

Parameters:
        x20     a pointer to the circular buffer of char pointers.
        x27     a buffer to write to the circular buffer
 */
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
vacuumCleaner: stp     x29, x30, [sp, -16]! 

    recursiveClean:
        cmp     x26, 10
        beq     vacuumCleanerExit

        ldr     x0, [x20, x19]
        cbz     x0, skipClean

        bl      free
        add     x19, x19, 8
        add     x26, x26, 1
        b       recursiveClean

    skipClean:
        add     x19, x19, 8
        add     x26, x26, 1
        b       recursiveClean

    vacuumCleanerExit: 
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--

.data
buffer:     .space 8
exited:     .asciz "exited\n"
printString:.asciz "%s"

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