section .data
  message: db "type parameter of arcsinh : ", 0
  input: db "%lf", 0
  output: db "result : %lf", 10, 0

section .bss
  x resb 8
  
section .text
  global main
  extern printf
  extern scanf

main:
  push message
  call printf
  add esp, 2

  push x
  push input
  call scanf
  add esp, 6

  finit
  fld1
  fld qword [x]
  fld st0
  fld st0
  fmulp
  fld1
  faddp
  fsqrt
  faddp
  fyl2x
  fldl2e
  fdiv 

  fst qword [x]
  push dword [x+4]
  push dword [x]
  push output
  call printf
  add esp, 4 

  mov ebx, 0
  mov eax, 1
  int 0x80