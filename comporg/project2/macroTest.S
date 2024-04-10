.macro pushr 
    stp     x21, x30, [sp, -16]!
    stp     x24, x25, [sp, -16]!
    stp     x26, x27, [sp, -16]!
.endm
.macro popr 
    ldp     x26, x27, [sp], 16
    ldp     x24, x25, [sp], 16                                  
    ldp     x21, x30, [sp], 16
    ret
.endm

.text
.global main  
                                                 
main:                                                                    
    pushr
    ldr     x0, =fmt
    bl printf
    popr

.data       
fmt:    .asciz "Hello World!\n"                                      
.end