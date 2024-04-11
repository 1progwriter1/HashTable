section .text

global asciiSum

;-------------------------------
;Copies value
;Expects: rdi - string, rsi - rsi
;Returns: rax - hash
;Destroys: rdi
;-------------------------------
asciiSum:
            push rdx
            xor rax, rax
.ascii_loop:
            cmp byte [rdi], 0x0
            je .end
            movsx rdx, byte [rdi]
            add rax, rdx
            inc rdi
            jmp .ascii_loop
.end:
            and rax, 0x7FF
            pop rdx
            ret
