.text
.global main  
                                                 
main:                                                                    
    stp     x21, x30, [sp, -16]! //  x21 stores pointer to arg array
    stp     x24, x25, [sp, -16]! //  x24 is used as head pointer. x25 is used as the "current" node we're working on.
    stp     x26, x27, [sp, -16]! //  x26 is used as 
    mov     x21, x1

    //  initialize head node (x24)
    mov     x26, 0
    mov     x27, 0
    bl      createNode
    mov     x24, x26
    b       exit
    //  initialize current node (x25)
    mov     x26, 0
    mov     x27, 0
    bl      createNode
    mov     x24, x26

    //  skip first arg and start reading.
    add     x21, x21, 8
    bl      readArgs

createNode:
    //  Node n = new Node;
    mov     x0, #16
    bl      malloc

    str     x26, [x0] // first 8 bytes of n = whatever's in x26
    str     x27, [x0, 8] //  last 8 bytes of n = whatevers in x27
    mov     x26, x0 // x26 = n
    mov     x0, xzr
    ret

exit:                           
    ldp     x26, x27, [sp], 16
    ldp     x24, x25, [sp], 16                                  
    ldp     x21, x30, [sp], 16              
    mov     x0, xzr                  
    ret

readArgs:
    ldr     x0, [x21], 8 //  increment through argv array
    cbz     x0, exit  //  if no remaining args, exit.
    bl      atoi  //  convert argv[i] to int

    //  stores the element in argv as an int in x25
    mov     x25, x0

    bl      createNode

//  converts val in x26 and other val in x27 to node in x26

    //  assign n.data to val in current (x25), then assign current to point to n which is a pointer and a value.
    //mov     x1, 0
    //str     x1, [x0]
    //str     x25, [x0, 8]
    //mov     x25, x0

insert:
    //mov     x0, x24
    //  if head == null, branch to case1
    //cbz     x0, case1
    
    //  or if head->data >= current->data, also branch to case1
    ldr     x0, [x25, 8] //  x0 = current->data
    ldr     x1, [x24, 8] //  x1 = head->data
    cmp     x1, x0
    bpl     case1

case1:
    //newNode->next = head;
    //head = newNode;
    str     x24, [x25]
    mov     x24, x25
    
    b       readArgs
    //ldr     x1, [x25]
    //ldr     x0, =fmt
    //bl      printf
    b exit
.data 
fmt:    .asciz "%d\n"
fmt2:   .asciz "%d\n%d\n" 
.end                                                                