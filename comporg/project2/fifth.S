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
//pushr
    ldr     x0, [x21]   , 8 
    cbz     x0, lne
    bl      atoi

    mov     x1, x0
    mov     x27, x0

    str     x1, [sp], 16
    ldr     x0, =fmt
    bl      printf
    ldr     x1, [sp, -16]!

    bl      readArgs

//popr
insert:
pushr
    
    mov     x1, 0
    cmp     x24, x1
    beq     baseCase //  if (numElements == 0) branch to baseCase

    ldr     x0, =fmt2
    mov     x1, x27
    bl      printf
    popr

popr
baseCase: // empty linked list
pushr

    mov     x26, 0
    bl      newNode
    mov     x22, x26
    mov     x23, x26
    add     x24, x24, 1 //  increment element count
    popr

case2:  
neg:
pushr

popr

.data
fmt:    .asciz "%d\n"  
fmt2:    .asciz "case 2!: %d\n"
hw:     .asciz "Hello World!\n"  
tw:    .asciz "test worked!\n" 
ne:     .asciz "exited through normal exit\n"                                  
.end
/*
x21 = current pointer, gets updated to head each recursion of readArgs function
x22 = numElements
x23 = head pointer
x27 = value we read in inserting
insert:
    stp     x29, x30, [sp, -16]!
    
    if (!numElements) branch case1;

    if (head->val > x27) branch case1;

    if (current->next) branch case2;

        elseCase:
            Node n = new Node;
            n->next = current->next;
            n->val = x27;
            current->next = n;
            numElements++;

        ldp     x29, x30, [sp], 16
        x0 = 1;
        ret;

        case1:
            Node n = new Node;
            n->next = x23;
            n->val = x27;
            x23 points to n;
            numElements++;

        ldp     x29, x30, [sp], 16
        x0 = 1;
        ret; (returns whole insert function call)

        case2:
            if (current->next->data < data) branch recurseCase;
            branch elseCase;
        
        recurseCase:
            current = current->next
            bl      insert

        ldp     x29, x30, [sp], 16
        x0 = 1;
        ret;
 */
 /*
 print:
    
    if (!current) branch printExit;

    recursiveBit:
        if (!current->next) branch nullNext;

        nullNext:

    printExit:


    
 
 
normalPrint:       .asciz "&n: %p, n->next: %p, n->val: %d\n"
nextNullPrintCase:       .asciz "&n: %p, n->next: null, n->val: %d\n"
printCase2:       .asciz ""
  */