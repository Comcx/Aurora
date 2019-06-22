.set IRQ_BASE, 0x20
.section .text

.extern interrupt
.global interruptNull

.macro handleException num
.global _Z13exception\numv
_Z13exception\numv:
  movb $\num, (interruptnumber)
	jmp int_bottom
.endm

.macro handleRequest num
.global interrupt\num
interrupt\num:
  movb $\num + IRQ_BASE, (intNum)
  pushl $0
  jmp int_bottom
.endm

handleRequest 0x00
handleRequest 0x01
handleRequest 0x0C


int_bottom:

  //pusha
  //pushl %ds
  //pushl %es
  //pushl %fs
  //pushl %gs

  pushl %ebp
	pushl %edi
	pushl %esi

  pushl %edx
  pushl %ecx
	pushl %ebx
	pushl %eax

  pushl %esp
  push (intNum)
  call interrupt
  //add $5, %esp
  movl %eax, %esp

  popl %eax
	popl %ebx
	popl %ecx
	popl %edx

	popl %esi
	popl %edi
	popl %ebp

  //popl %gs
  //popl %fs
  //popl %es
  //popl %ds
  //popa

  add $4, %esp

interruptNull:

  iret


.data
  intNum: .byte 0


