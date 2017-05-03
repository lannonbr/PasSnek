	.section .rodata
.LC0:
	.string "%d\n"
.LC1:
	.string "%d"
	.text
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$7, %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	popq	%rbp
	ret
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	$0, %rax
	call	boo
	movq	$0, %rax
	leave
	ret
