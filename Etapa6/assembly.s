

# TAC_VARDEC
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

    .globl	varChar
	.type	varChar, @object
	.size	varChar, 1
varChar:
	.byte	9

# TAC_BEGINFUNC
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

# TAC_ENDFUNC
    nop
    popq	%rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE1:
    .size	func, .-func

# TAC_MOVE

# Atribuição imediata char
    movb	$2, varChar(%rip)
# Atribuição varChar = varChar2
    movzbl	varChar2(%rip), %eax
	movb	%al, varChar(%rip)
# Atribuição imediata float
    movss	.LC1(%rip), %xmm0
	movss	%xmm0, varFloat(%rip)
	movss	.LC2(%rip), %xmm0
	movss	%xmm0, varFloat2(%rip)
# Atribuição varFloat = varFloat2
    movss	varFloat2(%rip), %xmm0
    movss	%xmm0, varFloat(%rip)
# Atribuição imediata int
    movl	$2, varInt(%rip)
# Atribuição varInt = varInt2
    movl	varInt2(%rip), %eax
    movl	%eax, varInt(%rip)

# Operações imediatas (comp. calcula o resultado de todas)
    movl	$4, varInt(%rip)

# #TAC_VECDEC
    .globl	varInt2
    .align 32   # Ignora
    .type	varInt2, @object
    .size	varInt2, 40
varInt2:
    .long	1
    .long	2
    .long	3
    .long	4
    .long	5
    .zero	20

    .globl	varChar
    .align 16
    .type	varChar, @object
    .size	varChar, 20
    varChar:
    .byte	1
    .byte	2
    .byte	3
    .byte	4
    .byte	5
    .zero	15

    .globl	varFloat #1,2,3,4,5
	.align 32
	.type	varFloat, @object
	.size	varFloat, 40
varFloat:
	.long	1065353216
	.long	1073741824
	.long	1077936128
	.long	1082130432
	.long	1084227584
	.zero	20

# TAC_RET (move para eax e faz ret como sempre)
    movl	$2, %eax

# TAC_ADD (varInt + varInt2)
    movl	varInt(%rip), %edx
    movl	varInt2(%rip), %eax
    addl	%edx, %eax
    movl	%eax, varInt(%rip)

# TAC_SUB (varInt + varInt2)
    movl	varInt(%rip), %edx
    movl	varInt2(%rip), %eax
    subl	%eax, %edx
    movl	%edx, %eax
    movl	%eax, varInt(%rip)

#TAC_MUL (varInt + varInt2)
    movl	varInt(%rip), %edx
    movl	varInt2(%rip), %eax
    imull	%edx, %eax
    movl	%eax, varInt(%rip)

#TAC_DIV (varInt + varInt2)
    movl	varInt(%rip), %eax
    movl	varInt2(%rip), %ecx
    cltd
    idivl	%ecx
    movl	%eax, varInt(%rip)
