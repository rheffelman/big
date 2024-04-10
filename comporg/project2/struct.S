                                                            
        .global main                                  
        .text                                               
        .p2align    2                                        
                                                             
main:                                                         
        stp         x29, x30, [sp, -16]!                    
        mov         x29, sp                                 
                                                             
        ldr         x0, =fmt                                  
        ldr         x1, =bar                                  
        ldrh        w2, [x1, 0]                              
        ldrb        w3, [x1, 2]                              
        ldr         w4, [x1, 4]                              
                                            
        stp         x3, x4, [sp, -16]!                             
        stp         x1, x2, [sp, -16]!                      
        bl         printf                                   
        add         sp, sp, 32                                                                                      
        //bl         printf                                                                                      
        ldp       x29, x30, [sp], 16                            
        mov          w0, wzr                                 
        ret                                                  
                                                             
        //.data                                                
                                                         
fmt:    .asciz      "%p a: 0x%lx b: %x c: %x\n"            

bar:    .short      0xaaaa                                   
        .byte       0xbb                                     
        .byte       0               // padding               
        .word       0xcccccccc                               
                                                             
        .end                                                