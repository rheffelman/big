        .p2align    2
        .text
        .global     main
        
/*  x30     link register
    x29     frame pointer
    x20     address of buffer in RAM into which read will deposit characters.
    x21     is no longer needed as we're not counting anything anymore :)
*/

//  pushes/predecrements x29 and x30 on the stack as a pair
main:   stp     x29, x30, [sp, -16]!

//  pushes/predecrements x20 on the stack
        str     x20, [sp, -16]!

//  sets up frame pointer by copying stack pointer into x29
        mov     x29, sp

//  loads the buffer function defined at the bottom into x20
        ldr     x20, =buffer
 
//  read() function: ssize t read(int fd, void *buf, size_t count); as per the Linux Programmer's Manual

//  this puts the file descriptor 1 into the x0 register to pass as the first argument in the read and write functions.
1:      mov     x0, 1

//  passes the second buffer argument where we will store the characters that we read in in x1
        mov     x1, x20

//  passes 3rd arg in x2, reading in 1 byte at a time
        mov     x2, 1

//  calls read() function with aforementioned args
        bl      read

//  compares return value of read() to 1, if not equal "gracefully exits"
        cmp     x0, 1
        bne     99f
        
//  calls write() function with aforementioned args
        bl      write 

//  compares return value of read() to 0, if negative "gracefully exits"
        cmp     x0, 0
        bmi     99f

//  "recurse"/"unconditional" branch
        b       1b

//  pops stack and returns 0
99:     ldr     x20, [sp], 16
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
        ret

        .data

buffer: .space      8

        .end