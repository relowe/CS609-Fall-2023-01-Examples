	.file	"simplicity.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
.LC1:
	.string	"hello, world\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	$1, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	leaq	.LC0(%rip), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rbp, %rsi
	xorl	%ebx, %ebx
	call	__printf_chk@PLT
	movq	%rbp, %rsi
	movl	$2, %edx
	xorl	%eax, %eax
	movl	$1, %edi
	call	__printf_chk@PLT
	movq	%rbp, %rsi
	movl	$3, %edx
	xorl	%eax, %eax
	movl	$1, %edi
	call	__printf_chk@PLT
	movq	%rbp, %rsi
	movl	$3, %edx
	xorl	%eax, %eax
	movl	$1, %edi
	call	__printf_chk@PLT
	movq	%rbp, %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	movl	$4, %edx
	leaq	.LC1(%rip), %rbp
	call	__printf_chk@PLT
	movq	stdout@GOTPCREL(%rip), %r12
	movl	$104, %edi
	.p2align 4,,10
	.p2align 3
.L2:
	movq	(%r12), %rsi
	addl	$1, %ebx
	call	putc@PLT
	movslq	%ebx, %rax
	movsbl	0(%rbp,%rax), %edi
	testb	%dil, %dil
	jne	.L2
	popq	%rbx
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
