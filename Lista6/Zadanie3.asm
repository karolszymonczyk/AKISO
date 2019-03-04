section .data
  message: db "input : ", 0
  input: db "%lf %c %lf", 0
  output: db "result : %lf", 10, 0

section .bss
  a resb 8
  b resb 8
  sign resb 1
  
section .text
  global main
  extern printf
  extern scanf

main:

  push message
  call printf
  add esp, 2

  push b
  push sign
  push a
  push input
  call scanf
  add esp, 8

  finit
  fld qword [a]

  cmp byte [sign], '+'
  je add
  cmp byte [sign], '-'
  je substract
  cmp byte [sign], '*'
  je multiply
  cmp byte [sign], '/'
  je divide

  add:

    fadd qword [b]
    jmp printing

  substract:

    fsub qword [b]
    jmp printing

  multiply:

    fmul qword [b]
    jmp printing

  divide:

    fdiv qword [b]
    jmp printing


  printing:

    fst qword [a]
    push dword [a+4]
    push dword [a]
    push output
    call printf
    add esp, 10 


  mov ebx, 0
  mov eax, 1
  int 0x80