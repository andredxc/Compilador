	.file	"test.c"
	.globl	vecInt
	.data
	.align 16
	.type	vecInt, @object
	.size	vecInt, 20
vecInt:
	.long	1
	.long	2
	.long	3
	.long	4
	.long	5
	.globl	vecFloat
	.align 32
	.type	vecFloat, @object
	.size	vecFloat, 40
vecFloat:
	.long	1065353216
	.long	1073741824
	.long	1077936128
	.long	1082130432
	.long	1084227584
	.zero	20
	.globl	vecChar
	.align 16
	.type	vecChar, @object
	.size	vecChar, 20
vecChar:
	.byte	1
	.byte	2
	.byte	3
	.byte	4
	.byte	5
	.zero	15
	.globl	varInt
	.align 4
	.type	varInt, @object
	.size	varInt, 4
varInt:
	.long	9
	.comm	varInt2,4,4
	.comm	varFloat,4,4
	.comm	varChar,1,1
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
.LC0:
	.string	"%d"
	.text
	.globl	func1
	.type	func1, @function
func1:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	varInt(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	func1, .-func1
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
