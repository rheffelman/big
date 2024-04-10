.text
.comm head, 8
.comm current, 8
.global main  
                                                 
main:                                                                    
    stp     x21, x30, [sp, -16]!
    mov     x21, x1

    //  initialize head data
    mov     x0, 0
    ldr     x1, =head
    str     x0, [x1]
    
    //  initialize current data
    mov     x0, 0
    ldr     x1, =current
    str     x0, [x1]

    //  skip first arg and start reading.
    add     x21, x21, 8
    bl      readArgs
exit:                                                              
    ldp     x21, x30, [sp], 16              
    mov     x0, xzr                  
    ret

readArgs:
    ldr     x0, [x21], 8 //  increment through argv array
    cbz     x0, exit  //  if no remaining args, exit.
    bl      atoi  //  convert argv[i] to int

    //  store it in current variable
    ldr     x1, =current
    str     x0, [x1]

    bl      createNode

createNode:
    //  Node n = new Node;
    mov     x0, #16
    bl      malloc

    //  n->next = nullptr
    mov     x2, 0  
    str     x2, [x0]

    //  n->data = arg
    ldr     x1, =current //  access current data
    ldr     x2, [x1]
    str     x2, [x0, 8] //  put it in last 4 bytes

    //  current points to n
    ldr     x1, =current
    str     x0, [x1]

    
    //mov     x2, 0
    //str     x2, [x0]

    b       exit


.data 
fmt:    .asciz "%d\n"
fmt2:   .asciz "%d\n%d\n" 
.end                                                                