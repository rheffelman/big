.macro pushr 
    str     x30, [sp, -16]!
    .endm
.macro popr 
    ldr     x30, [sp], 16
    ret
.endm
.text
.global main                                              
main:                                                                    
    stp     x21, x30, [sp, -16]! 
    stp     x24, x25, [sp, -16]!
    stp     x26, x27, [sp, -16]!
    stp     x22, x23, [sp, -16]!
    mov     x21, x1 //  x1 is pointer to arguments. it's copied to x21 for safekeeping and later use.
    mov     x24, 0
    add     x21, x21, 8 //  skips argv[0] (probably ./a.out)
    bl      readArgs

lne:
    ldr     x1, [x22, 8]
    ldr     x0, =fmt
    bl      printf
    ldp     x22, x23, [sp], 16
    ldp     x26, x27, [sp], 16
    ldp     x24, x25, [sp], 16                                  
    ldp     x21, x30, [sp], 16
    mov     x0, xzr
    ret

newNode:
pushr

    mov     x0, #16 //  allocating 16 bytes on heap
    bl      malloc
    str     x26, [x0] //  put what's in x26 on call in first 8 bytes
    str     x27, [x0, 8] //  put what's in x27 on call in last 8 bytes
    mov     x26, x0 // put node on x26 and return

popr         
readArgs:
pushr

    ldr     x0, [x21], 8
    cbz     x0, lne
    bl      atoi
    mov     x27, x0
    mov     x23, x0
    cmp     x0, xzr
    //mov     x1, x0
    blt     neg
    //ldr     x0, =fmt
    //bl     printf
     
    bl      insert
    popr
    b       readArgs
    
    

popr
insert:
pushr
    
    mov     x1, 0
    cmp     x24, x1
    beq     baseCase //  if (numElements == 0) branch to baseCase

    ldr     x1, [x22, 8]
    cmp     x1, x27
    bpl     case2 //  if head > element we're inserting, branch to case2

popr
baseCase: // empty linked list
pushr

    mov     x26, 0
    bl      newNode
    mov     x22, x26
    mov     x23, x26
    add     x24, x24, 1 //  increment element count
    //popr
    b       readArgs

case2:
pushr

    //mov     x1, x23
    //ldr     x0, =fmt
    //bl      printf
    //popr
    //b       readArgs
popr 
neg:
pushr

popr

.data
fmt:    .asciz "%d\n"  
hw:     .asciz "Hello World!\n"  
tw:    .asciz "test worked!\n" 
ne:     .asciz "exited\n"                                  
.end