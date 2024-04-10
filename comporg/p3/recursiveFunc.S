.text
.p2align        2
.global         fact

/* long fact(long n){
        if (n <= 1)
            return 1;
        return n * fact(n - 1);
 */
fact:   stp     x20, x30,   [sp, -16]!
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
        ldp     x20, x30, [sp], 16

        ret

        .end