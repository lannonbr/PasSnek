	.section .rodata
.LC0:
	.string "%d\n"
	.text
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	$4, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	movq	$0, %rax
	leave
	ret
