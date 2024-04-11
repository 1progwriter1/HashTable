global sum_ascii

section .text
;-------------------------------
;Calculates sum of ASCII codes
;Expects: rdi - string, rsi - hash_table_size
;Returns: rax - ASCII sum
;-------------------------------
sum_ascii:
            xor rax, rax
.ascii_loop:
            cmp [rdi], '\0'
            je .end
            add rax, [rdi]
.end
            ret
