	.text
	.globl _forsum
_forsum:
LFB4:
	movq	%rdi, %rax		; long acc = start						note: acc in %rax and start in %rdi
	leaq	1(%rdi), %rdx	; long i = start + 1					note: i in %rdx
	cmpq	%rsi, %rdx		; compare i to finish --> guard			note: finish in %rsi
	jg	L1					; guarded do							if i > finish, return.
	addq	$1, %rsi		; finish++ (??)
L3:
	addq	%rdx, %rax		; acc += i
	addq	$1, %rdx		; i++
	cmpq	%rsi, %rdx		; compare i to finish 
	jne	L3					; if finish != i, jump to L3			!! whilesum and forsum are exactly the same.
L1:
	ret
LFE4:
	.globl _dosum
_dosum:
LFB5:
	movq	%rdi, %rax		; long acc = start						note: acc in %rax and start in %rdi
	leaq	1(%rdi), %rdx	; long i = start + 1					note: i in %rdx
L7:
	addq	%rdx, %rax		; acc += i
	addq	$1, %rdx		; i++
	cmpq	%rsi, %rdx		; compare i to finish 
	jle	L7					; if i <= finish, jump to L7			!! goto1sum and dosum are identical
	ret
LFE5:
	.globl _whilesum
_whilesum:
LFB6:
	movq	%rdi, %rax		; long acc = start						note: acc in %rax and start in %rdi
	leaq	1(%rdi), %rdx	; long i = start + 1					note: i in %rdx
	cmpq	%rsi, %rdx		; compare i to finish --> guard			note: finish in %rsi
	jg	L9					; guard									if i > finish, return.
	addq	$1, %rsi		; finish++ (??)
L11:
	addq	%rdx, %rax		; acc += i
	addq	$1, %rdx		; i++
	cmpq	%rsi, %rdx		; compare i to finish 
	jne	L11					; if finish != i, jump to L3			!! whilesum and forsum are exactly the same.
L9:
	ret
LFE6:
	.globl _gotosum
_gotosum:
LFB7:
	movq	%rdi, %rax		; long acc = start						note: acc in %rax and start in %rdi
	leaq	1(%rdi), %rdx	; long i = start + 1					note: i in %rdx
L15:
	addq	%rdx, %rax		; acc += i
	addq	$1, %rdx		; i++
	cmpq	%rsi, %rdx		; compare i to finish 
	jle	L15					; if i <= finish, jump to L15			!! goto1sum and dosum are identical
	ret
LFE7:
	.cstring
	.align 3
lC0:
	.ascii "The sum of all of the numbers a - b = %ld\12\0"
	.section __TEXT,__text_startup,regular,pure_instructions
	.globl _main
_main:
LFB8:
	subq	$8, %rsp
LCFI0:
	movl	$11, %esi
	leaq	lC0(%rip), %rdi
	movl	$0, %eax
	call	_printf
	movl	$0, %eax
	addq	$8, %rsp
LCFI1:
	ret
LFE8:
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$0,LECIE1-LSCIE1
	.long L$set$0
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x1
	.byte	0x10
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 3
LECIE1:
LSFDE1:
	.set L$set$1,LEFDE1-LASFDE1
	.long L$set$1
LASFDE1:
	.long	LASFDE1-EH_frame1
	.quad	LFB4-.
	.set L$set$2,LFE4-LFB4
	.quad L$set$2
	.uleb128 0
	.align 3
LEFDE1:
LSFDE3:
	.set L$set$3,LEFDE3-LASFDE3
	.long L$set$3
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB5-.
	.set L$set$4,LFE5-LFB5
	.quad L$set$4
	.uleb128 0
	.align 3
LEFDE3:
LSFDE5:
	.set L$set$5,LEFDE5-LASFDE5
	.long L$set$5
LASFDE5:
	.long	LASFDE5-EH_frame1
	.quad	LFB6-.
	.set L$set$6,LFE6-LFB6
	.quad L$set$6
	.uleb128 0
	.align 3
LEFDE5:
LSFDE7:
	.set L$set$7,LEFDE7-LASFDE7
	.long L$set$7
LASFDE7:
	.long	LASFDE7-EH_frame1
	.quad	LFB7-.
	.set L$set$8,LFE7-LFB7
	.quad L$set$8
	.uleb128 0
	.align 3
LEFDE7:
LSFDE9:
	.set L$set$9,LEFDE9-LASFDE9
	.long L$set$9
LASFDE9:
	.long	LASFDE9-EH_frame1
	.quad	LFB8-.
	.set L$set$10,LFE8-LFB8
	.quad L$set$10
	.uleb128 0
	.byte	0x4
	.set L$set$11,LCFI0-LFB8
	.long L$set$11
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.set L$set$12,LCFI1-LCFI0
	.long L$set$12
	.byte	0xe
	.uleb128 0x8
	.align 3
LEFDE9:
	.ident	"GCC: (Homebrew GCC 11.3.0) 11.3.0"
	.subsections_via_symbols
