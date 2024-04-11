section .text

global ascii_sum

;-------------------------------
;Calculates sum of ASCII codes
;Expects: rdi - string, rsi - hash_table_size
;Returns: rax - ASCII sum
;-------------------------------
ascii_sum:
            xor rax, rax
.ascii_loop:
            cmp byte [rdi], 0x0
            je .end
            add rax, [rdi]
            inc rdi
.end:
            and rax, 0x7FF
            ret
