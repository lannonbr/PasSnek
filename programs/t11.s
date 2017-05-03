	.section .rodata
.LC0:
	.string "%d\n"
.LC1:
	.string "%d"
	.text
foo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	$20, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	cmp	$20, %rax
	jne .L2
	movq	$0, %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	jmp .L3
.L2:
.L3:
	leave
	ret
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	$2, %rax
	movq	%rax, -12(%rbp)
	movq	-12(%rbp), %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	movq	$0, %rax
	call	foo
	movq	$0, %rax
	leave
	ret
