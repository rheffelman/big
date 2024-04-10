    .section .data
buffer:
    .space 1         // buffer to hold the read character

    .section .text
    .global _start

_start:
    // Open file
    mov r0, #0        // file descriptor (stdin)
    ldr r1, =buffer   // buffer to read into
    mov r2, #1        // number of bytes to read
    mov r7, #3        // syscall number for read
    swi 0             // invoke syscall

read_loop:
    // Check for newline character
    ldrb r3, [r1]     // load byte into r3
    cmp r3, #0x0A     // compare with newline character
    beq exit          // branch if equal (newline character)

    // Read next character
    mov r0, #0        // file descriptor (stdin)
    ldr r1, =buffer   // buffer to read into
    mov r2, #1        // number of bytes to read
    mov r7, #3        // syscall number for read
    swi 0             // invoke syscall
    b read_loop       // loop back to check next character

exit:
    // Exit program
    mov r7, #1        // syscall number for exit
    mov r0, #0        // exit status (success)
    swi 0             // invoke syscall