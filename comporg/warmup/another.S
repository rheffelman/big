    .global main                                                        // 1 
main:                                                                   // 2 
    stp     x21, x30, [sp, -16]!    // push onto stack                  // 3 
    mov     x21, x1                 // argc -> x0, argv -> x1           // 4 
                                                                        // 5 
top:                                                                    // 6 
    ldr     x0, [x21], 8            // argv++, old value in x0          // 7 
    cbz     x0, bottom              // if *argv == NULL goto bottom     // 8 
    bl      puts                    // puts(*argv)                      // 9 
    b       top                     // goto top                         // 10 
                                                                        // 11 
bottom:                                                                 // 12 
    ldp     x21, x30, [sp], 16      // pop from stack                   // 13 
    mov     x0, xzr                 // return 0                         // 14 
    ret                                                                 // 15 
                                                                        // 16 
    .end                                                                // 17   