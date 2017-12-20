

# Declaração de variáveis
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

#Início de função
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

#Fim de função
    nop
    popq	%rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE1:
    .size	func, .-func

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

# Operações imediatas (comp. calcula o resultado)
    movl	$4, varInt(%rip)
