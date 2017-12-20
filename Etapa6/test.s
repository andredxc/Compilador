	.file	"test.c"
	.globl	varInt
	.data
	.align 4
	.type	varInt, @object
	.size	varInt, 4
varInt:
	.long	2
	.globl	varInt2
	.align 4
	.type	varInt2, @object
	.size	varInt2, 4
varInt2:
	.long	3
	.globl	varFloat
	.align 4
	.type	varFloat, @object
	.size	varFloat, 4
varFloat:
	.long	1066192077
	.globl	varFloat2
	.align 4
	.type	varFloat2, @object
	.size	varFloat2, 4
varFloat2:
	.long	1092511334
	.globl	varChar
	.type	varChar, @object
	.size	varChar, 1
varChar:
	.byte	9
	.globl	varChar2
	.type	varChar2, @object
	.size	varChar2, 1
varChar2:
	.byte	98
	.section	.rodata
.LC0:
	.string	"Ola"
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
	movl	$.LC0, %edi
	call	puts
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	func
	.type	func, @function
func:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	.LC1(%rip), %xmm0
	movss	%xmm0, varFloat(%rip)
	movss	.LC2(%rip), %xmm0
	movss	%xmm0, varFloat(%rip)
	movss	.LC3(%rip), %xmm0
	movss	%xmm0, varFloat(%rip)
	pxor	%xmm0, %xmm0
	movss	%xmm0, varFloat(%rip)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	func, .-func
	.section	.rodata
	.align 4
.LC1:
	.long	1082130432
	.align 4
.LC2:
	.long	3221225472
	.align 4
.LC3:
	.long	1077936128
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
