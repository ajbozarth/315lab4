
fib.mps:     file format elf32-bigmips

Disassembly of section .reginfo:

00400000 <.reginfo>:
  400000:	a0000000 	sb	zero,0(zero)
	...
  400014:	004482a0 	0x4482a0
Disassembly of section .init:

00400018 <_init>:
  400018:	27bdffe0 	addiu	sp,sp,-32
  40001c:	afbf0014 	sw	ra,20(sp)
  400020:	0c10003a 	jal	4000e8 <frame_dummy>
  400024:	00000000 	nop
  400028:	0c10007e 	jal	4001f8 <__do_global_ctors_aux>
  40002c:	00000000 	nop
  400030:	8fbf0014 	lw	ra,20(sp)
  400034:	27bd0020 	addiu	sp,sp,32
  400038:	03e00008 	jr	ra
  40003c:	00000000 	nop
Disassembly of section .text:

00400040 <_ftext>:
  400040:	27bdffe0 	addiu	sp,sp,-32
  400044:	afb10014 	sw	s1,20(sp)
  400048:	3c110044 	lui	s1,0x44
  40004c:	922202a8 	lbu	v0,680(s1)
  400050:	afbf0018 	sw	ra,24(sp)
  400054:	14400019 	bnez	v0,4000bc <_ftext+0x7c>
  400058:	afb00010 	sw	s0,16(sp)
  40005c:	3c100044 	lui	s0,0x44
  400060:	8e0202a4 	lw	v0,676(s0)
  400064:	00000000 	nop
  400068:	8c430000 	lw	v1,0(v0)
  40006c:	00000000 	nop
  400070:	10600009 	beqz	v1,400098 <_ftext+0x58>
  400074:	24420004 	addiu	v0,v0,4
  400078:	0060f809 	jalr	v1
  40007c:	ae0202a4 	sw	v0,676(s0)
  400080:	8e0202a4 	lw	v0,676(s0)
  400084:	00000000 	nop
  400088:	8c430000 	lw	v1,0(v0)
  40008c:	00000000 	nop
  400090:	1460fff9 	bnez	v1,400078 <_ftext+0x38>
  400094:	24420004 	addiu	v0,v0,4
  400098:	3c020000 	lui	v0,0x0
  40009c:	24420000 	addiu	v0,v0,0
  4000a0:	10400005 	beqz	v0,4000b8 <_ftext+0x78>
  4000a4:	24020001 	li	v0,1
  4000a8:	3c040040 	lui	a0,0x40
  4000ac:	0c000000 	jal	0 <_init-0x400018>
  4000b0:	24840288 	addiu	a0,a0,648
  4000b4:	24020001 	li	v0,1
  4000b8:	a22202a8 	sb	v0,680(s1)
  4000bc:	8fbf0018 	lw	ra,24(sp)
  4000c0:	8fb10014 	lw	s1,20(sp)
  4000c4:	8fb00010 	lw	s0,16(sp)
  4000c8:	03e00008 	jr	ra
  4000cc:	27bd0020 	addiu	sp,sp,32

004000d0 <call___do_global_dtors_aux>:
  4000d0:	27bdffe8 	addiu	sp,sp,-24
  4000d4:	afbf0010 	sw	ra,16(sp)
  4000d8:	8fbf0010 	lw	ra,16(sp)
  4000dc:	00000000 	nop
  4000e0:	03e00008 	jr	ra
  4000e4:	27bd0018 	addiu	sp,sp,24

004000e8 <frame_dummy>:
  4000e8:	3c020000 	lui	v0,0x0
  4000ec:	27bdffe8 	addiu	sp,sp,-24
  4000f0:	3c040040 	lui	a0,0x40
  4000f4:	3c050044 	lui	a1,0x44
  4000f8:	24420000 	addiu	v0,v0,0
  4000fc:	afbf0010 	sw	ra,16(sp)
  400100:	24840288 	addiu	a0,a0,648
  400104:	10400003 	beqz	v0,400114 <frame_dummy+0x2c>
  400108:	24a502ac 	addiu	a1,a1,684
  40010c:	0c000000 	jal	0 <_init-0x400018>
  400110:	00000000 	nop
  400114:	3c040044 	lui	a0,0x44
  400118:	8c83029c 	lw	v1,668(a0)
  40011c:	3c020000 	lui	v0,0x0
  400120:	10600007 	beqz	v1,400140 <frame_dummy+0x58>
  400124:	24590000 	addiu	t9,v0,0
  400128:	2484029c 	addiu	a0,a0,668
  40012c:	13200004 	beqz	t9,400140 <frame_dummy+0x58>
  400130:	00000000 	nop
  400134:	8fbf0010 	lw	ra,16(sp)
  400138:	03200008 	jr	t9
  40013c:	27bd0018 	addiu	sp,sp,24
  400140:	8fbf0010 	lw	ra,16(sp)
  400144:	00000000 	nop
  400148:	03e00008 	jr	ra
  40014c:	27bd0018 	addiu	sp,sp,24

00400150 <call_frame_dummy>:
  400150:	27bdffe8 	addiu	sp,sp,-24
  400154:	afbf0010 	sw	ra,16(sp)
  400158:	8fbf0010 	lw	ra,16(sp)
  40015c:	00000000 	nop
  400160:	03e00008 	jr	ra
  400164:	27bd0018 	addiu	sp,sp,24

00400168 <main>:
  400168:	27bdffe8 	addiu	sp,sp,-24
  40016c:	afbe0010 	sw	s8,16(sp)
  400170:	03a0f021 	move	s8,sp
  400174:	afc0000c 	sw	zero,12(s8)
  400178:	24020001 	li	v0,1
  40017c:	afc20008 	sw	v0,8(s8)
  400180:	afc00004 	sw	zero,4(s8)
  400184:	afc00000 	sw	zero,0(s8)
  400188:	08100073 	j	4001cc <main+0x64>
  40018c:	00000000 	nop
  400190:	8fc3000c 	lw	v1,12(s8)
  400194:	8fc20008 	lw	v0,8(s8)
  400198:	00000000 	nop
  40019c:	00621021 	addu	v0,v1,v0
  4001a0:	afc20004 	sw	v0,4(s8)
  4001a4:	8fc20008 	lw	v0,8(s8)
  4001a8:	00000000 	nop
  4001ac:	afc2000c 	sw	v0,12(s8)
  4001b0:	8fc20004 	lw	v0,4(s8)
  4001b4:	00000000 	nop
  4001b8:	afc20008 	sw	v0,8(s8)
  4001bc:	8fc20000 	lw	v0,0(s8)
  4001c0:	00000000 	nop
  4001c4:	24420001 	addiu	v0,v0,1
  4001c8:	afc20000 	sw	v0,0(s8)
  4001cc:	8fc20000 	lw	v0,0(s8)
  4001d0:	00000000 	nop
  4001d4:	2842000a 	slti	v0,v0,10
  4001d8:	1440ffed 	bnez	v0,400190 <main+0x28>
  4001dc:	00000000 	nop
  4001e0:	8fc20004 	lw	v0,4(s8)
  4001e4:	03c0e821 	move	sp,s8
  4001e8:	8fbe0010 	lw	s8,16(sp)
  4001ec:	27bd0018 	addiu	sp,sp,24
  4001f0:	03e00008 	jr	ra
  4001f4:	00000000 	nop

004001f8 <__do_global_ctors_aux>:
  4001f8:	3c020044 	lui	v0,0x44
  4001fc:	24420290 	addiu	v0,v0,656
  400200:	8c44fffc 	lw	a0,-4(v0)
  400204:	27bdffe0 	addiu	sp,sp,-32
  400208:	2403ffff 	li	v1,-1
  40020c:	afb00010 	sw	s0,16(sp)
  400210:	afbf0018 	sw	ra,24(sp)
  400214:	afb10014 	sw	s1,20(sp)
  400218:	10830008 	beq	a0,v1,40023c <__do_global_ctors_aux+0x44>
  40021c:	2450fffc 	addiu	s0,v0,-4
  400220:	2411ffff 	li	s1,-1
  400224:	0080f809 	jalr	a0
  400228:	2610fffc 	addiu	s0,s0,-4
  40022c:	8e040000 	lw	a0,0(s0)
  400230:	00000000 	nop
  400234:	1491fffb 	bne	a0,s1,400224 <__do_global_ctors_aux+0x2c>
  400238:	00000000 	nop
  40023c:	8fbf0018 	lw	ra,24(sp)
  400240:	8fb10014 	lw	s1,20(sp)
  400244:	8fb00010 	lw	s0,16(sp)
  400248:	03e00008 	jr	ra
  40024c:	27bd0020 	addiu	sp,sp,32

00400250 <call___do_global_ctors_aux>:
  400250:	27bdffe8 	addiu	sp,sp,-24
  400254:	afbf0010 	sw	ra,16(sp)
  400258:	8fbf0010 	lw	ra,16(sp)
  40025c:	00000000 	nop
  400260:	03e00008 	jr	ra
  400264:	27bd0018 	addiu	sp,sp,24
Disassembly of section .fini:

00400268 <_fini>:
  400268:	27bdffe0 	addiu	sp,sp,-32
  40026c:	afbf0014 	sw	ra,20(sp)
  400270:	0c100010 	jal	400040 <_ftext>
  400274:	00000000 	nop
  400278:	8fbf0014 	lw	ra,20(sp)
  40027c:	27bd0020 	addiu	sp,sp,32
  400280:	03e00008 	jr	ra
  400284:	00000000 	nop
Disassembly of section .eh_frame:

00400288 <__EH_FRAME_BEGIN__>:
  400288:	00000000 	nop
Disassembly of section .ctors:

0044028c <__CTOR_LIST__>:
  44028c:	ffffffff 	0xffffffff

00440290 <__CTOR_END__>:
  440290:	00000000 	nop
Disassembly of section .dtors:

00440294 <__DTOR_LIST__>:
  440294:	ffffffff 	0xffffffff

00440298 <__DTOR_END__>:
  440298:	00000000 	nop
Disassembly of section .jcr:

0044029c <__JCR_END__>:
  44029c:	00000000 	nop
Disassembly of section .data:

004402a0 <__dso_handle>:
  4402a0:	00000000 	nop

004402a4 <p.2344>:
  4402a4:	00440298 	0x440298
Disassembly of section .bss:

004402a8 <completed.2346>:
  4402a8:	00000000 	nop

004402ac <object.2427>:
	...
Disassembly of section .comment:

00000000 <.comment>:
   0:	00474343 	0x474343
   4:	3a202847 	xori	zero,s1,0x2847
   8:	4e552920 	c3	0x552920
   c:	342e312e 	ori	t6,at,0x312e
  10:	32000047 	andi	zero,s0,0x47
  14:	43433a20 	c0	0x1433a20
  18:	28474e55 	slti	a3,v0,20053
  1c:	2920342e 	slti	zero,t1,13358
  20:	312e3200 	andi	t6,t1,0x3200
  24:	00474343 	0x474343
  28:	3a202847 	xori	zero,s1,0x2847
  2c:	4e552920 	c3	0x552920
  30:	342e312e 	ori	t6,at,0x312e
  34:	Address 0x0000000000000034 is out of bounds.

Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	00000024 	and	zero,zero,zero
   4:	00020000 	sll	zero,v0,0x0
   8:	00000400 	sll	zero,zero,0x10
   c:	00000000 	nop
  10:	00400018 	mult	v0,zero
  14:	00000008 	jr	zero
  18:	00400268 	0x400268
  1c:	00000008 	jr	zero
  20:	00000000 	nop
  24:	00000000 	nop
  28:	00000024 	and	zero,zero,zero
  2c:	00020000 	sll	zero,v0,0x0
  30:	007f0400 	0x7f0400
  34:	00000000 	nop
  38:	00400030 	0x400030
  3c:	00000010 	mfhi	zero
  40:	00400278 	0x400278
  44:	00000010 	mfhi	zero
	...
Disassembly of section .debug_info:

00000000 <.debug_info>:
   0:	0000007b 	0x7b
   4:	00020000 	sll	zero,v0,0x0
   8:	00000401 	0x401
   c:	00000000 	nop
  10:	2e2e2f2e 	sltiu	t6,s1,12078
  14:	2e2f6763 	sltiu	t7,s1,26467
  18:	632f636f 	0x632f636f
  1c:	6e666967 	0x6e666967
  20:	2f6d6970 	sltiu	t5,k1,26992
  24:	732f6372 	0x732f6372
  28:	74692e61 	jalx	1a4b984 <_gp+0x16036e4>
  2c:	736d002f 	0x736d002f
  30:	686f6d65 	0x686f6d65
  34:	2f726468 	sltiu	s2,k1,25704
  38:	65617468 	0x65617468
  3c:	2f746561 	sltiu	s4,k1,25953
  40:	6368696e 	0x6368696e
  44:	672f6565 	0x672f6565
  48:	63313730 	0x63313730
  4c:	2f6d6970 	sltiu	t5,k1,26992
  50:	732f6565 	0x732f6565
  54:	63313731 	0x63313731
  58:	2f676363 	sltiu	a3,k1,25443
  5c:	2d342e31 	sltiu	s4,t1,11825
  60:	2e322f62 	sltiu	s2,s1,12130
  64:	75696c64 	jalx	5a5b190 <_gp+0x5612ef0>
  68:	2d676363 	sltiu	a3,t3,25443
  6c:	2f676363 	sltiu	a3,k1,25443
  70:	00474e55 	0x474e55
  74:	20415320 	addi	at,v0,21280
  78:	322e3137 	andi	t6,s1,0x3137
  7c:	00800100 	0x800100
  80:	00007b00 	sll	t7,zero,0xc
  84:	02000000 	0x2000000
  88:	10040100 	beq	zero,a0,48c <_init-0x3ffb8c>
  8c:	00005f2e 	0x5f2e
  90:	2e2f2e2e 	sltiu	t7,s1,11822
  94:	2f676363 	sltiu	a3,k1,25443
  98:	2f636f6e 	sltiu	v1,k1,28526
  9c:	6669672f 	0x6669672f
  a0:	6d697073 	0x6d697073
  a4:	2f637274 	sltiu	v1,k1,29300
  a8:	6e2e6173 	0x6e2e6173
  ac:	6d002f68 	0x6d002f68
  b0:	6f6d652f 	0x6f6d652f
  b4:	72646865 	0x72646865
  b8:	6174682f 	0x6174682f
  bc:	74656163 	jalx	195858c <_gp+0x15102ec>
  c0:	68696e67 	0x68696e67
  c4:	2f656563 	sltiu	a1,k1,25955
  c8:	3137302f 	andi	s7,t1,0x302f
  cc:	6d697073 	0x6d697073
  d0:	2f656563 	sltiu	a1,k1,25955
  d4:	3137312f 	andi	s7,t1,0x312f
  d8:	6763632d 	0x6763632d
  dc:	342e312e 	ori	t6,at,0x312e
  e0:	322f6275 	andi	t7,s1,0x6275
  e4:	696c642d 	0x696c642d
  e8:	6763632f 	0x6763632f
  ec:	67636300 	0x67636300
  f0:	474e5520 	c1	0x14e5520
  f4:	41532032 	0x41532032
  f8:	2e313700 	sltiu	s1,s1,14080
  fc:	Address 0x00000000000000fc is out of bounds.

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	01110010 	0x1110010
   4:	0603081b 	0x603081b
   8:	08250813 	j	94204c <_gp+0x4f9dac>
   c:	05000000 	bltz	t0,10 <_init-0x400008>
  10:	01110010 	0x1110010
  14:	0603081b 	0x603081b
  18:	08250813 	j	94204c <_gp+0x4f9dac>
  1c:	05000000 	bltz	t0,20 <_init-0x3ffff8>
Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	0000005b 	0x5b
   4:	00020000 	sll	zero,v0,0x0
   8:	00350101 	0x350101
   c:	fb0e0d00 	0xfb0e0d00
  10:	01010101 	0x1010101
  14:	00000001 	0x1
  18:	0000012e 	0x12e
  1c:	2e2f2e2e 	sltiu	t7,s1,11822
  20:	2f676363 	sltiu	a3,k1,25443
  24:	2f636f6e 	sltiu	v1,k1,28526
  28:	6669672f 	0x6669672f
  2c:	6d697073 	0x6d697073
  30:	00006372 	0x6372
  34:	74692e61 	jalx	1a4b984 <_gp+0x16036e4>
  38:	736d0001 	0x736d0001
  3c:	00000000 	nop
  40:	05020040 	0x5020040
  44:	0018030b 	0x18030b
  48:	014b0204 	0x14b0204
  4c:	00010100 	sll	zero,at,0x4
  50:	05020040 	0x5020040
  54:	02680317 	0x2680317
  58:	014b0204 	0x14b0204
  5c:	00010100 	sll	zero,at,0x4
  60:	00005d00 	sll	t3,zero,0x14
  64:	02000000 	0x2000000
  68:	350101fb 	ori	at,t0,0x1fb
  6c:	0e0d0001 	jal	8340004 <_gp+0x7ef7d64>
  70:	01010100 	0x1010100
  74:	00000100 	sll	zero,zero,0x4
  78:	00012e2e 	0x12e2e
  7c:	2f2e2e2f 	sltiu	t6,t9,11823
  80:	6763632f 	0x6763632f
  84:	636f6e66 	0x636f6e66
  88:	69672f6d 	0x69672f6d
  8c:	69707300 	0x69707300
  90:	00637274 	0x637274
  94:	6e2e6173 	0x6e2e6173
  98:	6d000100 	0x6d000100
  9c:	00000005 	0x5
  a0:	02004000 	0x2004000
  a4:	30030e01 	andi	v1,zero,0xe01
  a8:	4b4c0208 	c2	0x14c0208
  ac:	00010100 	sll	zero,at,0x4
  b0:	05020040 	0x5020040
  b4:	02780318 	0x2780318
  b8:	014b4c02 	0x14b4c02
  bc:	08000101 	j	404 <_init-0x3ffc14>
Disassembly of section .pdr:

00000000 <.pdr>:
   0:	00400168 	0x400168
   4:	40000000 	mfc0	zero,$0
   8:	fffffff8 	0xfffffff8
	...
  14:	00000018 	mult	zero,zero
  18:	0000001e 	0x1e
  1c:	0000001f 	0x1f
