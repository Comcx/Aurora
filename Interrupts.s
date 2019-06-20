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



int_bottom:

  pusha
  pushl %ds
  pushl %es
  pushl %fs
  pushl %gs

  pushl %esp
  push (intNum)
  call interrupt
  //add $5, %esp
  movl %eax, %esp

  popl %gs
  popl %fs
  popl %es
  popl %ds
  popa

interruptNull:

  iret


.data
  intNum: .byte 0


