section .data
  output: db "%d", 10, 0
  
section .text
  global main
  extern printf

main:

  mov ecx, 10000

  loop1:

  	;skip if 0
    cmp ecx, 0
    je endofloop1
    ;skip if 1
    cmp ecx, 1
    je endofloop1
    cmp ecx, 2
    je print

    mov ebx, 2

    loop2:

      mov edx, 0
      mov eax, ecx
      div ebx

      cmp edx, 0
      je endofloop1
      
      inc ebx
      cmp ebx, ecx
      jl loop2

    print:

      ;printf
      push ecx
      push dword output ;32
      call printf
      pop edx
      ;cleanup printf
      pop ecx

  endofloop1:

    loop loop1


  mov eax, 1
  int 0x80