#include "apple-linux-convergence.S"

       
        .p2align     2
        .text
        GLABEL      main


MAIN

    START_PROC
    PUSH_P      x29, x30
    PUSH_P      x20, x21

    mov         w21, wzr
    LLD_ADDR    x20, buffer
1:
    mov         w0, wzr
    mov         x1, x20
    mov         x2, 1
    CRT         read


    cmp         x0, xzr
    ble         10f

    add         w21, w21, 1
    b           1b
   
10:    
    LLD_ADDR    x0, fmt
    mov         w1, w21
#if defined(__APPLE__)
    PUSH_R      w1
    CRT         printf
    add         sp, sp, 16
#else
        bl      printf
#endif

        POP_P       x20, x21
        POP_P       x29, x30
        mov         w0, wzr
        ret
        END_PROC

        .data
buffer: .space  8
fmt:    .asciz  "Number of bytes read: %d/n"

        .end