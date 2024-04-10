// Ryan Heffelman
// Perry Kivolowitz
// CSC 3510 - Computer Organization
// Thursday, March 28, 2024
// Project 3

// This is my own code, I did not work with a partner.

// strlen() can be unsafe if your string isn't properly null terminated.

// Note on my commenting:
// My functions typically modify some "global registers" x19-x28. A lot of them effectively have
// the signature void funcName();. Most wouldn't technically have return types or parameters.
// Because of this, I've deviated from your commenting scheme, but I've done my best to add
// descriptive comments despite not following your scheme exactly.

.text
.global main
.EQU    TAILLEN, 10

main:
    // push x19-x28
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     x19, x20, [sp, -16]!
    stp     x21, x22, [sp, -16]!
    stp     x23, x24, [sp, -16]!
    stp     x25, x26, [sp, -16]!
    stp     x27, x28, [sp, -16]!

    // initialize x19-x28 to 0 to prevent the mistake I made last time.
    mov     x19, 0
    mov     x20, 0 // pointer to buffer
    mov     x21, 0 // writeIndex
    mov     x22, 0 
    mov     x23, 0 // fd of filePath in *argv[1]
    mov     x24, 0
    mov     x25, 0 // only used in shrink4096Buffer()
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

    // initialize memory in 80 byte buffer to 0
    mov     x1, 0
    mov     x2, 80
    bl      memset

    readAllLines:
        // x27 is 0
        bl      get4096Buffer
        cmp     x0, -1
        beq     cleanUp
        // x27 is pointer to 4096 bytes, all of which are off (0).
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

        mov     x0, x23
        bl      close
        cmp     w0, 0
        bmi     couldntClose

        bl      prynt
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

    couldntClose:
        ldr     x0, =badclose
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
void prynt();

Prints all the strings in the circular buffer in the order they'd naturally appear
in the file, and then deallocating the buffers which contain the strings. All memory
belonging to this program should be deallocated by the time this function returns.

Global Variables:
        x20     pointer to the circular buffer.
        x21     index of the last element written.
        x24     a counting variable
        x28     another counting variable

 */
prynt: stp     x29, x30, [sp, -16]!

    cbz     x20, pryntExit // this might handle a case that's impossible
    mov     x28, 0
    mov     x24, 0
    lsl     x24, x21, 3

    printEachElem:
        cmp     x24, 80
        beq     resetCounter2

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

        resetCounter2:
            mov     x24, 0
            b       printEachElem

    pryntExit: 
        mov     x0, x20
        bl      free
        mov     x24, 0
        mov     x28, 0
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
    ret

//--
/*
void overflow();

This should be branched to when getLine() has read 4094 bytes without running into a newline or null 
terminator. It truncates the buffer, appends a newline, adds it to the circular buffer, and then reads until
it hits a newline or null terminator.

Global Variables:
        x20     pointer to circular buffer.
        x21     index of the last element written in circular buffer.
        x27     buffer with 4094/4096 characters.
 */
overflow: stp     x29, x30, [sp, -16]! 

    mov     w1, 10
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
int getLine();

This reads byte by byte from the file descriptor fd into the buffer b until:
#1 we read in a newline character (10)
#2 we read in a null character or eof
#3 read returns 0
#4 we've read 4094 bytes without the first 3 exit conditions happening.

Global Variables:
        x23     it will read from the file descriptor in x23.
        x24     is used as a counting variable for condition #4, and reset to 0 upon function exit.
        x27     it will read into the buffer pointed to by x27 byte by byte.

Returns:
        x0      Returns 0 in x0 if it exits through the aforementioned condition #1 (it reads in 10 aka newline).
                Returns -1 in x0 if condition #2 or #3 (reads in 0 aka eof or read returns 0).
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
        cmp     w5, 10 // common case
        beq     exitGetLine
        cmp     w5, 0
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
int get4096Buffer();

This allocates 4096 bytes, sets them to 0, and puts the pointer to the memory in x27.

Global Variables:
        x27     puts a pointer to 4096 null bytes on x27.
Returns:
        x0      returns -1 to x0 if malloc fails to allocate the memory. otherwise returns 0.
 */
get4096Buffer: stp     x29, x30, [sp, -16]!
    // allocate 4096 bytes
    mov     x0, 4096
    bl      malloc
    cbz     x0, mallocFail

    // memset bytes to null
    mov     x1, 0
    mov     x2, 4096
    bl      memset
    mov     x27, x0

    ldp     x29, x30, [sp], 16
    mov     x0, xzr
    ret

    mallocFail:
        ldr     x0, =noline
        bl      printf
        ldp     x29, x30, [sp], 16
        mov     x0, -1
    ret

//--
/*
void *shrink4096Buffer(void * b);

"You are to dynamically allocate a perfectly sized buffer to hold the finalized line"

This takes a buffer b containing a string and effectively does b = realloc(b, strlen(b) + 2);.
If b[strlen(b) - 1] != a newline, it appends a newline. This is for the case where our string
is null terminated but there's no newline before the null terminator (often the last line of a file),
in order to follow part of the spec.

Global Variables:
        x27     x27 = realloc(x27, strlen(x27) + 2) (effectively shrinking it)
        x25     used to hold strlen(x27). assigned to 0 on exit.

 */
shrink4096Buffer: stp     x29, x30, [sp, -16]!

    cbz     x27, exitShrink4096Buffer // this might handle a case that's impossible

    mov     x0, x27
    bl      strlen
    cbz     x0, exitShrink4096Buffer // this might handle a case that's impossible
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
        b       exitShrink4096Buffer

    appendNewLine:
        add     x6, x6, 1
        mov     x4, 10
        str     x4, [x27, x6]
        b       shrink
        
    exitShrink4096Buffer:
        mov     x25, 0
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
    ret

//--
/*
void writeToBuffer();

This writes/inserts the buffer in x27 to our circular buffer in x20. 
It also deallocates what was previously in buffers[writeIndex] if it's non-null.
This is the only function which modifies x21 (writeIndex), it handles that internally
so I didn't put it down as a return value or parameter.

Global Variables:
        x20     a pointer to the circular buffer of char pointers.
        x27     a buffer to write to the circular buffer.
        x21     a counter for the circular buffer, only modified in this function.

 */
writeToBuffer: stp     x29, x30, [sp, -16]!

    cbz     x20, writeExit

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
/*
void vacuumCleaner();

This actually isn't where memory cleanup happens 99.99% of the time. This function exists for the
case where you have malloc'd 6 lines for instance, and mallocing a 7th fails, then an error message 
will be printed, this function will be called to deallocate any memory allocated before the malloc() fail.
This code is untested because I don't know how to test this case, purposefully inducing a hyperspecific 
kind of malloc() fail which COULD in theory happen.

Global Variables:
        x19     used as a counting variable. Assigned to 0 on exit.
        x20     points to the circular buffer-- all nodes in it are deallocated,
                and then the buffer itself is deallocated.

 */
vacuumCleaner: stp     x29, x30, [sp, -16]! 

    mov     x19, 0
    
    recursiveClean:
        cmp     x19, 80
        beq     vacuumCleanerExit

        ldr     x0, [x20, x19]
        cbz     x0, skipClean

        bl      free
        add     x19, x19, 8

        b       recursiveClean

    skipClean:
        add     x19, x19, 8
        b       recursiveClean

    vacuumCleanerExit: 
        mov     x0, x20
        bl      free
        mov     x19, 0
        mov     x20, 0
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--

.data
buffer:     .space 8
exited:     .asciz "exited\n"
printString:.asciz "%s"

badclose:	.asciz	"Close file failed"

usage:		.asciz	"File name must be given."
badopen:	.asciz	"Open file failed"
noline:		.asciz	"Allocating line buffer failed."
badtail:	.asciz	"Allocating tail pointer buffer failed."
dbgprnt:	.asciz	"Bytes read: %d String: %s\n"
badalloc:	.asciz	"Allocating a tail line failed."
pstring:	.asciz	"%s"

		.end