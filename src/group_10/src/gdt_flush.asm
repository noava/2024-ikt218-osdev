; Edited from https://archive.is/L3pyA by James Molloy
[GLOBAL gdt_flush] ; Makes the function accessible from outside this file.

; The gdt_flush function expects the address of the gdt_pointer structure.
gdt_flush:
    mov eax, [esp+4] ; Load the GDT with the pointer passed on the stack.
    lgdt [eax]        ; Load the new GDT pointer

    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax        ; Load all data segment selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
    ret

[GLOBAL idt_flush]

idt_flush:
   mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
   lidt [eax]        ; Load the IDT pointer.
   ret