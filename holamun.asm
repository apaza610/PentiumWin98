;-----------------------------------------------------------
; Programa simple en TASM
;-----------------------------------------------------------
            MODEL   small
            STACK   256

;-----      Equates
Nombre      EQU     "Homar"
Edad        =       985

            DATASEG
cadena1     DB      'Presione una tecla$'

            CODESEG
Main:       mov     ax, @data               ; Inicializar DS to address
            mov     ds, ax                  ;  of data segment
            
            mov     dx, offset cadena1      ; Puntero al inicio de cadena
            inc     dx                      ; meto desfase que borra 1ra letra
            mov     ah, 9                   ; DOS function: write to console
            int     21h                     ; Call DOS (software interruption DOS kernel lee AH)
            
            mov     ah, 0                   ;
            int     16h                     ; Reads 1 key input into AL
            
            mov     dx, 378h                ;
            ;mov     al, 00001111b           ; 
            out     dx, al                  ; Pines prendidos en puerto LPT

Exit:       mov     ax, 04C00h              ; DOS function: Exit program
            int     21h                     ; Call DOS ... Terminate program
            
            END     Main
