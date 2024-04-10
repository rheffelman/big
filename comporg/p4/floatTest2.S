        .text                                                   // 1 
        .global main                                            // 2 
        .align    2                                             // 3 
                                                                // 4 
main:   str        x30, [sp, -16]!                              // 5 
        ldr        s0, =0x3fc00000                              // 6 
        fcvt       d0, s0                                       // 7 
        ldr        x0, =fmt                                     // 8 
        bl         printf                                       // 9 
        ldr        x30, [sp], 16                                // 10 
        mov        w0, wzr                                      // 11 
        ret                                                     // 12 
                                                                // 13 
        .data                                                   // 14 
fmt:    .asciz    "%f\n"                                        // 15 
        .end                                                    // 16 