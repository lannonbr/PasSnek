	.section .rodata
.LC0:
	.string "%d\n"
.LC1:
	.string "%d"
	.text
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	movq	$.LC1, %rdi
	movq	$0, %rax
	call	__isoc99_scanf
	movq	$1, %rax
	movq	%rax, -8(%rbp)
	jmp	.L2
.L3:
	movq	-8(%rbp), %rax
	imul	-12(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-12(%rbp), %rax
	sub	$1, %rax
	movq	%rax, -12(%rbp)
.L2:
	cmp	$0, -12(%rbp)
	jg .L3
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	movq	$0, %rax
	leave
	ret
