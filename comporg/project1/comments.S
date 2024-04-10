        .p2align    2
        .text
        .global     main

main:   stp     x29, x30, [sp, -16]!
        stp     x20, x21, [sp, -16]!
        mov     x29, sp

        ldr     x20, =buffer
        mov     w21, wzr

// ssize_t read(int fd, void *buf, size_t count);  
// line 14 is the fd argument, 1 is the file descriptor, refers to stdout      
1:      mov     x0, 1
// 16 is the buffer arg which we assign to x20 register on line 9.
        mov     x1, x20
// idk what line 18 does, it's the count arg but beyond that idk
        mov     x2, 1
// 20 "calls" the read() function finally, previous 3 statements are implied to be the args passed
        bl      read
// 22 calls the write() function with the same args (line 14, 16, and 18)
        bl      write
// unconditional branch, recurses back up to the "1" function defined on line 14.
        b       1b

99:     ldp     x20, x21, [sp], 16
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
        ret

        .data

buffer: .space      8

        .end