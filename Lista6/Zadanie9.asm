data
  format: .asciz "%d\n"
  scan: .asciz "%d %d"
  a: .word 0
  b: .word 0

.text
  .global main
  .extern printf
  .extern scanf

main:
  LDR r0, =scan
  LDR r1, =a
  LDR r2, =b
  BL scanf
  LDR r1, =a
  LDR r2, =b
  LDR r1, [r1]
  LDR r2, [r2]

gcd:
  CMP r1, r2
  SUBGT r1, r1, r2
  SUBLT r2, r2, r1
  BNE gcd

print:
  LDR r0, =format
  BL printf
  MOV r7, #1
  SWI 0