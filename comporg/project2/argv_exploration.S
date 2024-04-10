#include "apple-linux-convergence.S"

        .p2align    2
        .text
        GLABEL      main

MAIN
        PUSH_P      x29, x30
        PUSH_R      x20
        mov         x29, sp
        mov         x20, x1     // backup of argv
        add         x20, x20, 8 // skip argv[0]

1:      ldr         x0, [x20],8 // dereference **argv to *argv
        cbz         x0, 99f     // if *argv is zero, we are done with
                                // the arguments

        // When we get here, we know we have a valid *argv in x0
        // ssize_t (long) atoi(char *)

        CRT         atoi        // x0 will contain a number

        // temp code - print out the number
        mov         x1, x0      // the number needs to be in x1
        PUSH_R      x1
        ldr         x0, =fmt     // ldr x0, =fmt on linux
        CRT         printf
        POP_R       x1          // x1 contains the number again

        cmp         x1, xzr
        blt         10f

        // If we get here, the number is positive and it is an insert
        LLD_ADDR    x0, pos
        CRT         puts
        
        b           1b

10:     // If we get here, the number is negative and is a delete
        // of the POSITIVE version so we must negate it
        neg         x1, x1
        // Now the number is positive

        // If this were the real program, we would process the delete
        // now - instead we will just print "negative"

        LLD_ADDR    x0, nega
        CRT         puts

        b           1b


99:     POP_R       x20
        POP_P       x29, x30
        mov         w0, wzr
        ret

        .data
fmt:    .asciz      "%ld\n"
pos:    .asciz      "positive"
nega:   .asciz      "negative"

        .end
        
