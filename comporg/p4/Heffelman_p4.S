// Ryan Heffelman
// Perry Kivolowitz
// CSC 3510 - Computer Organization
// Wednesday, April 10, 2024
// Project 4

// My program still gets slightly different answers from your c version program in very specific cases
// like ./a.out 888.93 9 gives a different result than the cversion.
// Oh well, I'm not better than the compiler yet.

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
    
    bl      parseInput
    cmp     x0, -1
    beq     mainExit

    mov     x21, 1 // counter 1
    mov     x22, 0 // counter 2
    mov     x28, 0 // binary switch thingy to toggle back in forth between addition and subtraction.
    ldr     d20, zero // theta in degrees
    ldr     d21, zero // theta in radians (x)
    ldr     d22, zero // x^(2i)/(2i)!
    ldr     d23, zero // x^(2i)
    ldr     d24, one // total in computeCosine. starts at 1 because of "first" term.
    ldr     d25, zero // what cos() says the cosine is

    fmov    d20, d0 // d0 is argv[1] as double (from atof)
    ldr     d1, piOver180 // pre-computed pi/180
    fmul    d21, d1, d20 // "D2R"

    fmul    d23, d21, d21 // d23 = x^2
    ldr     d1, two // 2! == 2
    fdiv    d22, d23, d1 // x^2/2
    fsub    d24, d24, d22
    
    computeCosine: // for (int i = 1; i < argv[2]; i++) 
        cmp     x21, x20
        beq     wrapUp

        fmul    d23, d23, d21
        fmul    d23, d23, d21 // d23 = x^(2i)

        // This accesses an array of factorial values for 4!, 6!, 8! ... 20! to get precomputed (2i)!.
        // I chose to do this because it's simpler and all around more efficient (I think).
        // Yes, this would cease to work if you expanded the spec to include an 11th term, however
        // so would your cversion of the program, so would the factorial function you gave us, and
        // so would any other student's factorial function. This is because 22! > 2^64. You'd
        // have to do some fancy stuff far outside the scope of this assignment to accomodate more
        // than 10 terms.
        ldr     x1, =factorials
        ldr     d1, [x1, x22]
        fdiv    d22, d23, d1 // d22 = x^(2i) / (2i)!

        cbz     x28, dontSubtract // I'd call this "add", but that's an instruction already

        fsub    d24, d24, d22 // subtract term from total
        add     x21, x21, 1
        add     x22, x22, 8   // increment counters
        mov     x28, 0        // flip binary toggle switch thingy
        b       computeCosine

        dontSubtract:
            fadd    d24, d24, d22 // add term to total
            add     x21, x21, 1
            add     x22, x22, 8   // increment counters
            add     x28, x28, 1   // flip binary toggle switch thingy
            b       computeCosine

    wrapUp: // computeCosine loop branches to here from its exit condition (i >= argc)
        fmov    d0, d21
        bl      cos
        fmov    d26, d0

        // cos() jumbles d20 which was theta in degrees as a double, so I need to
        // grab theta from argv and convert it to a double again.
        ldr     x0, [x19, 8]
        bl      atof // d0 = theta

        fsub    d2, d26, d24 // d2 = cos(theta) minus my computed cosine.
        fmov    d1, d24 // d1 = my computed cosine
        ldr     x0, =fmt1
        bl      printf
        mov     x0, xzr

    mainExit:
        ldp     d25, d26, [sp], 16
        ldp     d23, d24, [sp], 16
        ldp     d21, d22, [sp], 16
        ldp     d19, d20, [sp], 16
        ldp     x27, x28, [sp], 16 
        ldp     x21, x22, [sp], 16 
        ldp     x19, x20, [sp], 16 
        ldp     x29, x30, [sp], 16
ret

//--
/*
int parseInput(int argc, char ** argv);

parseInput() asserts argc == 3, and 1 <= argv[2] <= 10.
It prints a corresponding error message if an assertation is false.
Doesn't do any input checking on argv[1] because the example program doesn't either.

Parameters:
    x20     int argc
    x19     char ** argv

Returns:
    x0      -1 if (argc != 3 or (argv[2] < 1 or argv[2] > 10))
            xzr is returned in x0 otherwise.
    x20     int(argv[2])

Registers Preserved:
    x19     is used but never modified. It will still point to argv on exit.
 */
parseInput:    stp     x29, x30, [sp, -16]!

    // assert there are exactly 3 args.
    cmp     x20, 3 // x20 = argc
    bne     notThreeArguments

    ldr     x0, [x19, 16]
    bl      atoi
    cmp     x0, 10 // 10 >= assert argv[2]
    bgt     badTerms
    cmp     x0, 1 // assert 1 <= argv[2] 
    blt     badTerms

    mov     x20, x0
    ldr     x0, [x19, 8]
    bl      atof
    mov     x0, xzr
    b       parseInputExit

    badTerms: // badTerms is branched to if argv[2] is not 1-10 inclusive.
        mov     x0, 2
        ldr     x1, =badTerm
        bl      dprintf
        mov     x0, -1
        b       parseInputExit

    notThreeArguments:
        mov     x0, 2
        ldr     x1, =notThreeArgs
        bl      dprintf
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
    notThreeArgs:   .asciz      "Two numerical arguments must be given.\n"

.end