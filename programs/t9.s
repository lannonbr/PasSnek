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
	movq	-8(%rbp), %rax
	cmp	$0, %rax
	jne .L2
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	jmp .L3
.L2:
	movq	$7, %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
.L3:
	movq	-8(%rbp), %rax
	cmp	$10, %rax
	je .L4
	movq	$20, %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	jmp .L5
.L4:
.L5:
	movq	-8(%rbp), %rax
	cmp	$10, %rax
	jge .L6
	movq	$9, %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	jmp .L7
.L6:
.L7:
	movq	-8(%rbp), %rax
	cmp	$10, %rax
	jg .L8
	movq	$10, %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	jmp .L9
.L8:
.L9:
	movq	-8(%rbp), %rax
	cmp	$10, %rax
	jle .L10
	movq	$11, %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	jmp .L11
.L10:
.L11:
	movq	-8(%rbp), %rax
	cmp	$10, %rax
	jl .L12
	movq	$10, %rax
	movq	%rax, %rsi
	movq	$.LC0, %rdi
	movq	$0, %rax
	call	printf
	jmp .L13
.L12:
.L13:
	movq	$0, %rax
	leave
	ret
