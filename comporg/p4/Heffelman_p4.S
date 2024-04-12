// Ryan Heffelman
// Perry Kivolowitz
// CSC 3510 - Computer Organization
// Wednesday, April 10, 2024
// Project 4

.text
.p2align
.global main
main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     x19, x20, [sp, -16]!
    stp     x21, x22, [sp, -16]!
    stp     x27, x28, [sp, -16]!
    stp     d19, d20, [sp, -16]!
    stp     d21, d22, [sp, -16]!
    stp     d23, d24, [sp, -16]!
    stp     d25, d26, [sp, -16]!

    mov     x19, x1 // backup argv on x19
    mov     x20, x0 // backup argc on x20
    mov     x21, 1 // counter 1
    mov     x22, 0 // counter 2
    mov     x28, 0 // binary switch thingy to toggle back in forth between addition and subtraction.
    ldr     d20, zero // theta in degrees
    ldr     d21, zero // theta in radians
    ldr     d22, zero // x^k/k!
    ldr     d23, zero // theta^i
    ldr     d24, one // total. starts at 1 because of "first" term.
    ldr     d25, zero // what cos() says the cosine is
    
    bl      parseInput
    cmp     x0, -1
    beq     mainExit

    fmov    d20, d0
    ldr     d1, piOver180 // pre-computed pi/180
    fmul    d21, d1, d20

    fmul    d23, d21, d21 // d22 = theta^2
    ldr     d1, two
    fdiv    d22, d23, d1
    fsub    d24, d24, d22
    
    computeCosine: // for (int i = 1; i < argc; i++)
        cmp     x21, x20
        beq     wrapUp

        fmul    d23, d23, d21
        fmul    d23, d23, d21
        ldr     x1, =factorials // pre-computed factorial values for 4!, 6!, 8! ... 20!
        ldr     d1, [x1, x22]
        fdiv    d22, d23, d1
        cbz     x28, dontSubtract // I'd call this "add", but that's an instruction already
        fsub    d24, d24, d22
        add     x21, x21, 1
        add     x22, x22, 8
        mov     x28, 0
        b       computeCosine

        dontSubtract:
            fadd    d24, d24, d22
            add     x21, x21, 1
            add     x22, x22, 8
            add     x28, x28, 1
            b       computeCosine

    wrapUp: // computeCosine loop branches to here from its exit condition
        fmov    d0, d21
        bl      cos
        fmov    d26, d0

        // cos() jumbles d20 which was theta in degrees as a double, so I need to
        // grab theta from argv and convert it to a double again.
        ldr     x0, [x19, 8]
        bl      atof

        fsub    d2, d26, d24
        fmov    d1, d24
        ldr     x0, =fmt1
        bl      printf

    mainExit:
        ldp     d25, d26, [sp], 16
        ldp     d23, d24, [sp], 16
        ldp     d21, d22, [sp], 16
        ldp     d19, d20, [sp], 16
        ldp     x27, x28, [sp], 16 
        ldp     x21, x22, [sp], 16 
        ldp     x19, x20, [sp], 16 
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
ret
//--
/*
int parseInput(int argc, char ** argv);

parseInput() asserts argc == 3, and 1 <= argv[3] <= 10.
It prints a corresponding error message if an assertation is false.
I don't do any input checking on argc[2] because the example program doesn't either.

Parameters:
    x20     int argc
    x19     char ** argv

Returns:
    x0      -1 if (argc != 3 or (argv[3] < 1 or argv[3] > 10))
            xzr is returned in x0 otherwise.
    x20     int(argv[3])
 */
parseInput:    stp     x29, x30, [sp, -16]!

    // assert there are exactly 3 args.
    cmp     x20, 3 // x20 = argc
    bne     notEnoughArguments

    ldr     x0, [x19, 16]
    bl      atoi 

    // assert 1 <= 2nd arg <= 10
    cmp     x0, 10 
    bgt     badTerms
    cmp     x0, 1
    blt     badTerms

    mov     x20, x0
    ldr     x0, [x19, 8]
    bl      atof
    mov     x0, xzr
    b       parseInputExit

    badTerms:
        ldr     x0, =badTerm
        bl      printf
        mov     x0, -1
        b       parseInputExit

    notEnoughArguments:
        ldr     x0, =notEnoughArgs
        bl      printf
        mov     x0, -1

    parseInputExit:
        ldp     x29, x30, [sp], 16
ret
//--
.data

    factorials:     .double     24, 720, 40320, 3628800, 479001600, 87178291200, 20922789888000, 6402373705728000, 2432902008176640000
    zero:           .double     0.0
    two:            .double     2
    one:            .double     1
    piOver180:      .double     0.0174532925199432957692369076848861271344287188854172545609719144
    fmt1:           .asciz      "The cosine of %0.4f degrees is %0.10f. Error: %0.10f\n"
    printFloat:     .asciz      "%0.10f\n"
    badTerm:        .asciz      "Number of terms is out of range.\n"
    notEnoughArgs:  .asciz      "Two numerical arguments must be given.\n"

.end