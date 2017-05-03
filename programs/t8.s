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
	leaq	-8(%rbp), %rax
	movq	%rax, %rsi
	movq	$.LC1, %rdi
	movq	$0, %rax
	call	__isoc99_scanf
	jmp	.L2
.L3:
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	movq	-8(%rbp), %rax
	sub	$1, %rax
	movq	%rax, -8(%rbp)
.L2:
	movq	-8(%rbp), %rax
	cmp	$0, %rax
	jg .L3
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	movq	$0, %rax
	leave
	ret
