	.section .rodata
.LC0:
	.string "%d\n"
	.text
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	$2, %rax
	movq	%rax, -8(%rbp)
	movq	$1, %rax
	movq	%rax, -12(%rbp)
	movq	-8(%rbp), %rax
	cmp	-12(%rbp), %rax
	jg .L2
	movq	$7, %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	jmp .L3
.L2:
	movq	$0, %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
.L3:
	movq	$100, %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	movq	$0, %rax
	leave
	ret
