.text
.p2align
.global main
/// gcc -g 3.S -lm; ./a.out 69 5
main:

    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    stp     x19, x20, [sp, -16]!
    stp     x21, x22, [sp, -16]!
    stp     x23, x24, [sp, -16]!
    stp     x25, x26, [sp, -16]!
    stp     x27, x28, [sp, -16]!
    stp     d19, d20, [sp, -16]!
    stp     d21, d22, [sp, -16]!
    stp     d23, d24, [sp, -16]!
    stp     d25, d26, [sp, -16]!
    stp     d27, d28, [sp, -16]!

    mov     x19, x1 // backup argc on x19
    mov     x20, x0 // backup argv on x20
    mov     x21, 0
    mov     x22, 0 
    mov     x23, 0
    mov     x24, 0
    mov     x25, 0
    mov     x26, 0
    mov     x27, 0 // binary toggle thingy
    mov     x28, 1 // counter used in computation
    ldr     x0, =zeroLol // theta in radians post-handleInput()
    ldr     d19, [x0]
    ldr     d20, zeroLol
    ldr     d21, zeroLol // stores previous a^k for optimization in exponentiation.
    ldr     d22, zeroLol // used for final computation
    ldr     d23, zeroLol // final total?
    ldr     d24, zeroLol // preserves theta in radians
    ldr     d25, zeroLol
    ldr     d26, zeroLol
    ldr     d27, zeroLol
    ldr     d28, zeroLol
    
    bl      handleInput
    cmp     x0, -1
    beq     mainExit

    bl      computeCosine // cos(theta) in d23

    fmov    d0, d24
    bl      cos
    fmov    d19, d0

    ldr     d1, oneLol
    fsub    d0, d1, d23
    fmov    d20, d0

    fmov    d0, d28
    fmov    d1, d20
    fsub    d2, d19, d20
    fabs    d2, d2
    ldr     x0, =fmt1
    bl      printf // should print the error (actual cos(theta) - my computed cos(theta))

    mainExit:

        ldr     x0, =exited
        bl      printf
        ldp     d25, d26, [sp], 16
        ldp     d25, d26, [sp], 16
        ldp     d23, d24, [sp], 16
        ldp     d21, d22, [sp], 16
        ldp     d19, d20, [sp], 16
        ldp     x27, x28, [sp], 16 
        ldp     x25, x26, [sp], 16 
        ldp     x23, x24, [sp], 16 
        ldp     x21, x22, [sp], 16 
        ldp     x19, x20, [sp], 16 
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
    ret
//--
// post-handleInput():
// d19 is theta in radians
// d21 is also theta in radians
// x20 is *argv[2]
// x19 still points to argv
handleInput:  stp     x29, x30, [sp, -16]!

    // assert there are exactly 3 args.
    cmp     x20, 3 // x20 = argc
    bne     notEnoughArguments

    ldr     x0, [x19, 16] // x19 = argv
    bl      atoi 

    // assert 0 <= 2nd arg <= 10
    cmp     x0, 10
    bgt     badTerms
    cmp     x0, 1
    blt     badTerms
    mov     x20, x0

    ldr     x0, [x19, 8]
    bl     atof
    fmov    d19, d0
    fmov    d28, d0

    b       handleInputExit

    badTerms:
        ldr     x0, =badTerm
        bl      printf
        ldp     x29, x30, [sp], 16
        mov     x0, -1
    ret

    notEnoughArguments:
        ldr     x0, =notEnoughArgs
        bl      printf
        ldp     x29, x30, [sp], 16
        mov     x0, -1
    ret

    handleInputExit:
        // D2R
        fmov    d0, d19
        ldr     d5, piOver180
        fmul    d0, d0, d5
        fmov    d19, d0
        fmov    d21, d0
        fmov    d24, d0 // backup original theta on d24

        ldp     x29, x30, [sp], 16
        mov     x0, xzr
    ret

//--
// takes an int x in x0 where 1 < x < 20 and puts x! back in x0 and double(x!) in d0.
fact:   stp     x20, x30, [sp, -16]!

        cmp     x0, 1
        bgt     10f
        mov     x0, 1
        b       99f

    10:
        mov     x20, x0
        subs    x0, x0, 1
        bl      fact
        mul     x0, x20, x0

    99:
        // ucvtf because 2^32 < 20! < 2^64, so I dont think signed will work, but I didn't test it lol.
        ucvtf   d0, x0
        ldp     x20, x30, [sp], 16

        ret

//--
// d21 = d21 * d19
integerPower: stp     x20, x30, [sp, -16]!
    
    cmp     x20, 2
    blt     integerPowerExit

    fmul    d21, d21, d19
    fmul    d21, d21, d19

    integerPowerExit:
        ldp     x29, x30, [sp], 16
        mov     x0, xzr
    ret
//--
computeCosine: stp  x20, x30, [sp, -16]!

    // 2nd term (first REAL term)
    fmul    d21, d19, d19
    lsl     x0, x28, 1
    bl      fact
    fdiv    d22, d21, d0
    fadd    d23, d23, d22 // d23 = x^2/2!
    add     x28, x28, 1
    // x28 == 2
    
    computeCosineLoop:
        cmp     x28, x20
        bgt     computeCosineExit // loop end condition

        bl      integerPower
        lsl     x0, x28, 1
        bl      fact
        fdiv    d22, d21, d0
        add     x28, x28, 1

        cbz     x27, subtraction
        
        fadd    d23, d23, d22
        mov     x27, 0

        b       computeCosineLoop

        subtraction:
            fsub    d23, d23, d22
            add     x27, x27, 1
            b       computeCosineLoop

    computeCosineExit:
        ldp     x20, x30, [sp], 16
        mov     x0, xzr
    ret

// 
//oneEighty:  .double 180.0
//test:   .asciz      "test\n" 
//printLU:   .asciz      "%lu\n"
//factorials: .double 2, 24, 720, 40320, 3628800, 479001600, 87178291200, 20922789888000, 6402373705728000, 2432902008176640000

.data

    zeroLol:        .double     0.0
    oneLol:         .double     1
    negOneLol:      .double     -1
    piOver180:      .double     0.0174532925199432957692369076848861271
    fmt1:           .asciz      "The cosine of %0.4f degrees is %0.10f. Error: %0.10f\n"
    printCosine:    .asciz      "Cosine: %0.10f\n"
    printFloat:     .asciz      "%0.10f\n"
    cosineError:    .asciz      "Error: %0.10f\n"
    exited:         .asciz      "exited!\n"
    badTerm:        .asciz      "Number of terms is out of range.\n"
    notEnoughArgs:  .asciz      "Two numerical arguments must be given.\n"

.end
