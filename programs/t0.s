.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$0, %rax
	popq	%rbp
	ret
