    KERNEL_SECTOR_LENGTH EQU 50

    [bits 16]

    global _start
_start:
    ;; read the rest of the sectors from the floppy disk
    ;; to right after us in memory

    mov ah, 0 ; Reset Disk Drives
    mov dl, 0 ; first floppy disk
    int 0x13

    ; zero es before reading to es:bx
    mov ax, 0
    mov es, ax

    mov ah, 2 ; Read Sectors From Drive
    mov dl, 0 ; first floppy disk
    mov ch, 0 ; cylinder 0
    mov dh, 0 ; head 0
    mov cl, 2 ; sector 2
    mov al, (KERNEL_SECTOR_LENGTH - 1) ; read N sectors
    mov bx, sector_1 ; where to read to
    int 0x13

    ; setup memory table
    lgdt [gdt_descriptor]

    ; disable interrupts
    cli

    ; switch to 32bit protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp (gdt_code - gdt_start):protected_mode

    [bits 32]
protected_mode:

    ; memory
    mov ax, (gdt_data - gdt_start)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; TODO: setup stack somewhere
    ; mov esp, ???

    ; setup interrupt table
    lidt [idt_descriptor]

    ; enable interrupts
    sti

    ; call the c code to continue
    extern main
    call main

gdt_descriptor:
    dw (gdt_end - gdt_start) - 1 ; size
    dd gdt_start ; table address
gdt_start:
gdt_null:
    dw 0            ; limit 0:15
    dw 0            ; base 0:15
    db 0            ; base 16:23
    db 0            ; access byte
    db 0            ; flags + limit 16:19
    db 0            ; base 24:31
gdt_data:
    dw 0xffff       ; limit 0:15
    dw 0x0000       ; base 0:15
    db 0x00         ; base 16:23
    db 0b10010010   ; access byte
    db 0b11001111   ; flags + limit 16:19
    db 0x00         ; base 24:31
gdt_code:
    dw 0xffff       ; limit 0:15
    dw 0x0000       ; base 0:15
    db 0x00         ; base 16:23
    db 0b10011010   ; access byte
    db 0b11001111   ; flags + limit 16:19
    db 0x00         ; base 24:31
gdt_end:





    ; pad to 0x200 and put 55 AA
    times (0x200 - ($-$$) - 2) db 0
    db 0x55, 0xAA
sector_1:






%macro declare_interrupt 1
   dw %1 ; offset 0:15
   dw (gdt_code - gdt_start) ; segment
   db 0 ; unused, 0
   db 0b10001111 ; type and attributes
   dw 0 ; offset 16:31
%endmacro

idt_descriptor:
   dw (idt_end - idt_start) - 1 ; size
   dd idt_start ; table address
idt_start:
    ; 0..31     cpu
    ; 32..255   anything else

    ; BIOS sets:
    ;   8259 (master) - 0x08..0x0f
    ;   8259 (slave)  - 0x70..0x77

    ; keyboard IRQ1               = 0x08+1 == 0x09
    ; mouse    IRQ12 = slave IRQ4 = 0x70+4 == 0x74

    %assign i 0
    %rep 32
        declare_interrupt interrupt%[i]
    %assign i i+1
    %endrep
idt_end:


    %assign i 0
    %rep 32
    interrupt%[i]:
        pusha
        push %[i]
        jmp interrupt_common
    %assign i i+1
    %endrep

interrupt_common:
    extern handle_interrupt
    call handle_interrupt
    add esp, 4
    popa
    iret
