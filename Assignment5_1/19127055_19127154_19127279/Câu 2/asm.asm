.model small
.stack 100h

.data
message db 'Current time: $' ;For printing system time purpose

message1 db 'Input M: $' ;For UI
message2 db 'Input N: $'

x dw ? ;For printing rectangle purpose
y dw ?

m db 0 ;For calculating purpose
n db 0
c db 0 
t db 0
fd db 0

.code
main: 

    ;check light status
    mov ax, 0
    mov ah, 12h
    int 16h
    and al, 01100000b ; keep only caps and num bit
    
    cmp al, 01100000b ;check both lights
    je BothLights

    cmp al, 01000000b ; check caps
    je CapslockOnly
    
    cmp al, 00100000b ;check num
    je NumlockOnly
    
    
    exit:
        mov AH, 4ch ; no light on
        int 21h
    
    ;-----------------------------------------------------------------------------------
    
    CapslockOnly: ;Credit to L? Minh Tr? - 19127592
    
        mov ax, @data
        mov ds,ax
        
        mov dx, offset message1 ;take first number input
        mov ah, 9h
        int 21h
        mov x,0
        mov ah,1
        int 21h
        sub al,30h  ;convert whatever in al to number
        and ax,0ffh ;set the entire ax to al
        mov x,ax
        
        mov dl, 10 ;go down one line
        mov ah, 2
        int 21h
        
        mov ax, @data
        mov ds,ax
        mov dx, offset message2 ;take second number input
        mov ah, 9h
        int 21h
        mov y,0
        mov ah,1
        int 21h
        sub al,30h
        and ax,0ffh
        mov y,ax
        
        mov dl, 10 ;go down one line
        mov ah, 2
        int 21h
           
        mov cx,x
        mov bx,5
        
        mov dl,10
        mov ah,2
        int 21H
    
        L1:
            push cx
            mov cx, y
       
        L2:
            mov ah,2
            mov dl,'*'
            int 21H
       
            loop L2
     
            mov ah,2
            mov dl,10
            int 21h
     
            pop cx     
       
            loop L1
            
            
        
            jmp exit
    
    ;-----------------------------------------------------------------------------------
    
     NumlockOnly:
        call Calculate
        
        jmp exit
        
    
    ;-----------------------------------------------------------------------------------
    
    BothLights: ;credit to StackOverFlow
        mov ax, @data         ;Print message
        mov ds, ax     
        mov dx, offset message 
        mov ah, 09h         
        int 21h             
    
        mov ah, 2ch           ;Get time
        int 21h

        mov dl, ch            ;Show hours
        call itoa99

        mov ah, 02h           ;Show separator
        mov dl, ':'
        int 21h

        mov dl, cl            ;Show minutes
        call itoa99   
       
        mov ah, 02h           ;Show separator
        mov dl, ':'
        int 21h 
        
        mov dl, dh            ;Show second
        call itoa99
        
        ;exit
        mov ax, 4c00h        
        int 21h



    ;dl = number to display (0..99)
    itoa99:
        push bx
        push ax            ;Save registers used

        xor ax, ax         ;AX = 0
        mov al, dl         ;AX = DL

        mov bl, 10d
        div bl             ;AL = AX/10, AH = AX mod 10

    ;AX contains the digits

        add ax, 3030h      ;Transform digit to digitals
        mov bx, ax         ;Save for later 

        ;Show the digits
        mov dl, bl
        mov ah, 02h
        int 21h

        mov dl, bh
        int 21h

        pop ax
        pop bx
        ret
          
    ;-----------------------------------------------------------------------------------   
    
    Calculate proc ;credit to Nguy?n ??ng Khoa - 19127177
        ;take first argument
        mov ax, @data
        mov ds, ax
        mov dx, offset message1
        mov ah, 9h
        int 21h
        mov m, 0
        mov AH, 1;
        int 21h
        mov m, AL
        sub m, '0'
        
        mov dl, 10 ;go down one line
        mov ah, 2
        int 21h
        
        ;take second number input
        mov ax, @data
        mov ds,ax
        mov dx, offset message2 
        mov ah, 9h
        int 21h
        mov n,0
        mov AH, 1
        int 21h
        mov n, AL
        sub n, '0'
        
        mov dl, 10 ;go down one line
        mov ah, 2
        int 21h
        
    Addition:
        mov DL, 10 
        mov AH, 2
        int 21h


        mov DL, m 
        add DL, '0' 
        mov AH, 2
        int 21h 

        mov DL, '+' 
        mov AH, 2 
        int 21h 

        mov DL, n 
        add DL, '0' 
        mov AH, 2 
        int 21h 

        mov DL, '=' 
        mov AH, 2 
        int 21h 

        mov DL, m 
        add DL, n

        cmp DL, 10 
        jge two_digits1 
        jl one_digit1 

    two_digits1:
        mov BL, DL
        mov DL, '1'
        mov AH, 2
        int 21h
        sub BL, 10
        mov DL, BL
        jmp one_digit1

    one_digit1:
        add DL, '0'
        mov AH, 2
        int 21h

    Subtraction:
        mov DL, 10 
        mov AH, 2
        int 21h

        mov DL, m 
        add DL, '0' 
        mov AH, 2 
        int 21h 

        mov DL, '-' 
        mov AH, 2 
        int 21h 

        mov DL, n 
        add DL, '0' 
        mov AH, 2 
        int 21h 

        mov DL, '=' 
        mov AH, 2 
        int 21h 

        mov DL, m 
        sub DL, n

        cmp DL, 0
        jge normal
        jl reverse

    normal:
        add dl, '0'
        mov AH, 2
        int 21h
        jmp Multiplication
     
    reverse:
        mov dl, '-'
        mov ah, 2
        int 21h
        mov dl, n
        sub dl, m
        add dl, '0'
        mov ah, 2
        int 21h
        jmp Multiplication
        
    Multiplication:
        mov DL, 10
        mov AH, 2
        int 21h
   
        mov DL, m 
        add DL, '0' 
        mov AH, 2 
        int 21h 

        mov DL, '*' 
        mov AH, 2 
        int 21h 
    
        mov DL, n
        add DL, '0' 
        mov AH, 2 
        int 21h 

        mov DL, '=' 
        mov AH, 2 
        int 21h 

    multiply:
        mov DL, t
        add DL, m

        mov t, DL
        cmp DL, 10
        jge first_digit_tracker
        jmp counter 
    
    counter:
        mov BL, c
        inc BL
        mov c, BL
        cmp BL, n 
        je checkb4print
        jmp multiply

    checkb4print:
        mov DL ,t
        cmp fd, 0
        jg two_digits2
        je one_digit2

    first_digit_tracker:
        mov BL, fd
        inc BL
        mov fd, BL 
        mov BL, t
        sub BL, 10 
        mov t, BL
        jmp counter

    two_digits2:
        mov DL, fd 
        add DL, '0'
        mov AH, 2
        int 21h
        mov DL, t 
        add DL, '0' 
        mov AH, 2
        int 21h 
        jmp Division

    one_digit2:
        mov DL, t 
        add DL, '0'
        mov AH, 2
        int 21h
        jmp Division

    Division:

        mov DL, 10 
        mov AH, 2
        int 21h


        mov DL, m 
        add DL, '0' 
        mov AH, 2 
        int 21h 

        mov DL, '/' 
        mov AH, 2 
        int 21h 

        mov DL, n 
        add DL, '0' 
        mov AH, 2 
        int 21h 

        mov DL, '=' 
        mov AH, 2 
        int 21h 

        mov BL, m ; 
        mov t, BL
        mov c, 0 ; 

    divide: 
        mov DL, t 
        sub DL, n
        mov t, DL
        mov BL, c 
        inc BL 
        mov c, BL
        mov BL, t
        cmp BL, n 
        jl printd
        jmp divide

    printd: 
        mov DL, c 
        add DL, '0'
        mov AH, 2
        int 21h
        
        mov ax, 4c00h        
        int 21h        
    Calculate endp
    end Calculate
    
    ;----------------------------------------------------------------------------------- endp   
end main  