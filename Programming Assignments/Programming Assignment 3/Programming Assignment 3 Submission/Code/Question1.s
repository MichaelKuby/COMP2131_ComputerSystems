	.text
	.globl _x
	.data
	.align 1
_x:
	.word	100
	.globl _y
	.align 1
_y:
	.word	200
	.cstring
lC0:
	.ascii "Hello, programmers!\0"
lC1:
	.ascii "Welcome to the world of,\0"
lC2:
	.ascii "Linux assembly programming!\0"
	.text
	.globl _main
_main:
LFB4:
	pushq	%rbp
LCFI0:
	movq	%rsp, %rbp
LCFI1:
	leaq	lC0(%rip), %rax
	movq	%rax, %rdi
	call	_puts
	leaq	lC1(%rip), %rax
	movq	%rax, %rdi
	call	_puts
	leaq	lC2(%rip), %rax
	movq	%rax, %rdi
	call	_puts
	movl	$0, %eax
	popq	%rbp
LCFI2:
	ret
LFE4:
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
	.byte	0x4
	.set L$set$3,LCFI0-LFB4
	.long L$set$3
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.set L$set$4,LCFI1-LCFI0
	.long L$set$4
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.set L$set$5,LCFI2-LCFI1
	.long L$set$5
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 3
LEFDE1:
	.ident	"GCC: (Homebrew GCC 11.3.0) 11.3.0"
	.subsections_via_symbols
