.comm head, 8 // this is my head

.text

.global main

main:
    stp     x21, x30, [sp, -16]!    // push onto stack
    mov     x21, x1                 // argc -> x0, argv -> x1
    
    
    // store head in global
    mov x0, #123
    bl storehead

    // load head from global
    bl loadhead

    // printf
    mov x1, x0 // storing head into x1
    ldr x0, =fmt
    bl printf

    // read input variables
top:
    ldr     x0, [x21], 8            // argv++, old value in x0
    cbz     x0, bottom              // if *argv == NULL goto bottom
    bl      puts                    // puts(*argv)
    b       top                     // goto top
    
bottom:
    ldp     x21, x30, [sp], 16      // pop from stack
    mov     x0, xzr                 // return 0
    ret

storehead:
    //stp     x21, x30, [sp, -16]!    // push onto stack

    // write to global
    ldr x1, =head // load pointer to foo
    str x0, [x1] // store value into foo

    //ldp     x21, x30, [sp], 16      // pop from stack
    ret

loadhead:
    //stp     x21, x30, [sp, -16]!    // push onto stack

    // read from global
    ldr x1, =head // load pointer to foo
    ldr x0, [x1] // load value from foo

    // ldp     x21, x30, [sp], 16      // pop from stack
    ret

.data
    fmt: .asciz "Denis: %d\n"

    .end