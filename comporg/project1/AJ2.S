#include  "apple-linux-convergence.S"

        .p2align   2
        .text
        GLABEL     main

main
    START_PROC
    .data
buffer:
    .space 1

    .text
read_loop:

    //Call read() to read 1 byte from stdin
    mov         x0, 0
    LLD_ADDR    x1, buffer
    mov        x2, 1
    bl         read
    cmp         x0, 0 //check if read() returned 0
    beq         exit_program

    //Call write() to write the byte read stdout
    mov         x0, 1
    LLD_ADDR    x1, buffer
    mov         x2, 1
    bl          write
    cmp         x0, 1
    blt         write_error
write_error:
    //print error message and exit
    LLD_ADDR    x0, errmsg_write
    bl          perror
    mov         x0, 1
    b           exit_program
 exit_program:
//exit program
    ret
    END_PROC

errmsg_write:
    AASCIZ      errmsg_write, "Error writing to stdout\n"