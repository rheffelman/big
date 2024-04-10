.text
.comm head, 8
.global main  
                                                 
main:                                                                    
    stp     x21, x30, [sp, -16]!
    stp     x29, x28, [sp, -16]! 
    stp     x22, x23, [sp, -16]!
    str     x27, [sp, -16]!
    mov     x0, 0
    ldr     x0, =
    mov     x21, x1 
    add     x21, x21, 8
    bl       readArgs

exit:  
    ldr     x24, [sp], 16
    ldp     x22, x23, [sp], 16
    ldp     x29, x28, [sp], 16                                                                
    ldp     x21, x30, [sp], 16              
    mov     x0, xzr                  
    ret

readArgs:
    ldr     x0, [x21], 8
    cbz     x0, exit
    bl      atoi
    
    mov     x28, x0
    bl      createNode                     
    b       exit

createNode:
    mov     x0, #12
    bl      malloc
    mov     x23, x0
    str     x28, [x0, 8]
    bl      insert
    b       readArgs

insert:
    mov     x0, x28       
    cmp     x0, 0  
    bl      headless
    ret

delete:

headless:
    str     x22, [x23]  //  newNode->next = head;
    mov     x22, x23    //  head = newNode;

    ldr     x0, =fmt2
    ldr     x1, [x22, 8]
    bl      printf
    b       exit

.data 
fmt:    .asciz "yes: %p\n"
fmt2:   .asciz "%d\n" 
.end                                                                