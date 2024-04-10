        .p2align    2
        .text
        .global     main

//  pushes x29, x30, and x20 registers on the stack with postdecrement of 16.  
main:   stp     x29, x30, [sp, -16]!
        str     x20, [sp, -16]!
        mov     x29, sp
        ldr     x20, =buffer

//  fd arg in read() and write(), 0 for stdin file descriptor. 
1:      mov     x0, 0

//  buffer arg in read() and write(), x20 is our buffer label at the bottom. 
        mov     x1, x20

//  count arg in read() and write(), reading in 1 character at a time from stdin.
        mov     x2, 1

//  read() function call
        bl      read

//  compares value in x0 returned by read with 1, then branches to 99 if not equal.
        cmp     x0, 1
        bne     99f

//  write() function call
        bl      write

/*  gets body-mass-index of... jk, in theory this branches to the writeReturn and returns a 1
label if write returns a value with a minus/negative sign, but I haven't been able to make a sufficiently 
convincing test to prove that this works. */
        bmi     writeReturn

//  unconditional branch back to 1, recursion till 99 or writeReturn are branched to.
        b       1b

//  normal exit when CTRL+D, prints errors, pops stack, returns 0.
99:     //bl      perror
        ldr     x20, [sp], 16
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
        ret

//  if there's a negative value returned by write, goes here, prints error, pops stack, returns 1.
writeReturn:
        bl      perror
        ldr     x20, [sp], 16
        ldp     x29, x30, [sp], 16
        mov     x0, 1
        ret

        .data
buffer: .space      8

        .end