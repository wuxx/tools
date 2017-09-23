
main:     file format elf32-i386


Disassembly of section .init:

080483fc <_init>:
 80483fc:	53                   	push   %ebx
 80483fd:	83 ec 08             	sub    $0x8,%esp
 8048400:	e8 9b 00 00 00       	call   80484a0 <__x86.get_pc_thunk.bx>
 8048405:	81 c3 fb 1b 00 00    	add    $0x1bfb,%ebx
 804840b:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 8048411:	85 c0                	test   %eax,%eax
 8048413:	74 05                	je     804841a <_init+0x1e>
 8048415:	e8 26 00 00 00       	call   8048440 <__gmon_start__@plt>
 804841a:	83 c4 08             	add    $0x8,%esp
 804841d:	5b                   	pop    %ebx
 804841e:	c3                   	ret    

Disassembly of section .plt:

08048420 <printf@plt-0x10>:
 8048420:	ff 35 04 a0 04 08    	pushl  0x804a004
 8048426:	ff 25 08 a0 04 08    	jmp    *0x804a008
 804842c:	00 00                	add    %al,(%eax)
	...

08048430 <printf@plt>:
 8048430:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 8048436:	68 00 00 00 00       	push   $0x0
 804843b:	e9 e0 ff ff ff       	jmp    8048420 <_init+0x24>

08048440 <__gmon_start__@plt>:
 8048440:	ff 25 10 a0 04 08    	jmp    *0x804a010
 8048446:	68 08 00 00 00       	push   $0x8
 804844b:	e9 d0 ff ff ff       	jmp    8048420 <_init+0x24>

08048450 <__libc_start_main@plt>:
 8048450:	ff 25 14 a0 04 08    	jmp    *0x804a014
 8048456:	68 10 00 00 00       	push   $0x10
 804845b:	e9 c0 ff ff ff       	jmp    8048420 <_init+0x24>

08048460 <lib_func1@plt>:
 8048460:	ff 25 18 a0 04 08    	jmp    *0x804a018
 8048466:	68 18 00 00 00       	push   $0x18
 804846b:	e9 b0 ff ff ff       	jmp    8048420 <_init+0x24>

Disassembly of section .text:

08048470 <_start>:
 8048470:	31 ed                	xor    %ebp,%ebp
 8048472:	5e                   	pop    %esi
 8048473:	89 e1                	mov    %esp,%ecx
 8048475:	83 e4 f0             	and    $0xfffffff0,%esp
 8048478:	50                   	push   %eax
 8048479:	54                   	push   %esp
 804847a:	52                   	push   %edx
 804847b:	68 20 86 04 08       	push   $0x8048620
 8048480:	68 b0 85 04 08       	push   $0x80485b0
 8048485:	51                   	push   %ecx
 8048486:	56                   	push   %esi
 8048487:	68 6d 85 04 08       	push   $0x804856d
 804848c:	e8 bf ff ff ff       	call   8048450 <__libc_start_main@plt>
 8048491:	f4                   	hlt    
 8048492:	66 90                	xchg   %ax,%ax
 8048494:	66 90                	xchg   %ax,%ax
 8048496:	66 90                	xchg   %ax,%ax
 8048498:	66 90                	xchg   %ax,%ax
 804849a:	66 90                	xchg   %ax,%ax
 804849c:	66 90                	xchg   %ax,%ax
 804849e:	66 90                	xchg   %ax,%ax

080484a0 <__x86.get_pc_thunk.bx>:
 80484a0:	8b 1c 24             	mov    (%esp),%ebx
 80484a3:	c3                   	ret    
 80484a4:	66 90                	xchg   %ax,%ax
 80484a6:	66 90                	xchg   %ax,%ax
 80484a8:	66 90                	xchg   %ax,%ax
 80484aa:	66 90                	xchg   %ax,%ax
 80484ac:	66 90                	xchg   %ax,%ax
 80484ae:	66 90                	xchg   %ax,%ax

080484b0 <deregister_tm_clones>:
 80484b0:	b8 27 a0 04 08       	mov    $0x804a027,%eax
 80484b5:	2d 24 a0 04 08       	sub    $0x804a024,%eax
 80484ba:	83 f8 06             	cmp    $0x6,%eax
 80484bd:	77 01                	ja     80484c0 <deregister_tm_clones+0x10>
 80484bf:	c3                   	ret    
 80484c0:	b8 00 00 00 00       	mov    $0x0,%eax
 80484c5:	85 c0                	test   %eax,%eax
 80484c7:	74 f6                	je     80484bf <deregister_tm_clones+0xf>
 80484c9:	55                   	push   %ebp
 80484ca:	89 e5                	mov    %esp,%ebp
 80484cc:	83 ec 18             	sub    $0x18,%esp
 80484cf:	c7 04 24 24 a0 04 08 	movl   $0x804a024,(%esp)
 80484d6:	ff d0                	call   *%eax
 80484d8:	c9                   	leave  
 80484d9:	c3                   	ret    
 80484da:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

080484e0 <register_tm_clones>:
 80484e0:	b8 24 a0 04 08       	mov    $0x804a024,%eax
 80484e5:	2d 24 a0 04 08       	sub    $0x804a024,%eax
 80484ea:	c1 f8 02             	sar    $0x2,%eax
 80484ed:	89 c2                	mov    %eax,%edx
 80484ef:	c1 ea 1f             	shr    $0x1f,%edx
 80484f2:	01 d0                	add    %edx,%eax
 80484f4:	d1 f8                	sar    %eax
 80484f6:	75 01                	jne    80484f9 <register_tm_clones+0x19>
 80484f8:	c3                   	ret    
 80484f9:	ba 00 00 00 00       	mov    $0x0,%edx
 80484fe:	85 d2                	test   %edx,%edx
 8048500:	74 f6                	je     80484f8 <register_tm_clones+0x18>
 8048502:	55                   	push   %ebp
 8048503:	89 e5                	mov    %esp,%ebp
 8048505:	83 ec 18             	sub    $0x18,%esp
 8048508:	89 44 24 04          	mov    %eax,0x4(%esp)
 804850c:	c7 04 24 24 a0 04 08 	movl   $0x804a024,(%esp)
 8048513:	ff d2                	call   *%edx
 8048515:	c9                   	leave  
 8048516:	c3                   	ret    
 8048517:	89 f6                	mov    %esi,%esi
 8048519:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048520 <__do_global_dtors_aux>:
 8048520:	80 3d 24 a0 04 08 00 	cmpb   $0x0,0x804a024
 8048527:	75 13                	jne    804853c <__do_global_dtors_aux+0x1c>
 8048529:	55                   	push   %ebp
 804852a:	89 e5                	mov    %esp,%ebp
 804852c:	83 ec 08             	sub    $0x8,%esp
 804852f:	e8 7c ff ff ff       	call   80484b0 <deregister_tm_clones>
 8048534:	c6 05 24 a0 04 08 01 	movb   $0x1,0x804a024
 804853b:	c9                   	leave  
 804853c:	f3 c3                	repz ret 
 804853e:	66 90                	xchg   %ax,%ax

08048540 <frame_dummy>:
 8048540:	a1 08 9f 04 08       	mov    0x8049f08,%eax
 8048545:	85 c0                	test   %eax,%eax
 8048547:	74 1f                	je     8048568 <frame_dummy+0x28>
 8048549:	b8 00 00 00 00       	mov    $0x0,%eax
 804854e:	85 c0                	test   %eax,%eax
 8048550:	74 16                	je     8048568 <frame_dummy+0x28>
 8048552:	55                   	push   %ebp
 8048553:	89 e5                	mov    %esp,%ebp
 8048555:	83 ec 18             	sub    $0x18,%esp
 8048558:	c7 04 24 08 9f 04 08 	movl   $0x8049f08,(%esp)
 804855f:	ff d0                	call   *%eax
 8048561:	c9                   	leave  
 8048562:	e9 79 ff ff ff       	jmp    80484e0 <register_tm_clones>
 8048567:	90                   	nop
 8048568:	e9 73 ff ff ff       	jmp    80484e0 <register_tm_clones>

0804856d <main>:
 804856d:	55                   	push   %ebp
 804856e:	89 e5                	mov    %esp,%ebp
 8048570:	83 e4 f0             	and    $0xfffffff0,%esp
 8048573:	83 ec 20             	sub    $0x20,%esp
 8048576:	c7 44 24 04 c8 00 00 	movl   $0xc8,0x4(%esp)
 804857d:	00 
 804857e:	c7 04 24 64 00 00 00 	movl   $0x64,(%esp)
 8048585:	e8 d6 fe ff ff       	call   8048460 <lib_func1@plt>
 804858a:	89 44 24 1c          	mov    %eax,0x1c(%esp)
 804858e:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 8048592:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048596:	c7 04 24 40 86 04 08 	movl   $0x8048640,(%esp)
 804859d:	e8 8e fe ff ff       	call   8048430 <printf@plt>
 80485a2:	b8 00 00 00 00       	mov    $0x0,%eax
 80485a7:	c9                   	leave  
 80485a8:	c3                   	ret    
 80485a9:	66 90                	xchg   %ax,%ax
 80485ab:	66 90                	xchg   %ax,%ax
 80485ad:	66 90                	xchg   %ax,%ax
 80485af:	90                   	nop

080485b0 <__libc_csu_init>:
 80485b0:	55                   	push   %ebp
 80485b1:	57                   	push   %edi
 80485b2:	31 ff                	xor    %edi,%edi
 80485b4:	56                   	push   %esi
 80485b5:	53                   	push   %ebx
 80485b6:	e8 e5 fe ff ff       	call   80484a0 <__x86.get_pc_thunk.bx>
 80485bb:	81 c3 45 1a 00 00    	add    $0x1a45,%ebx
 80485c1:	83 ec 1c             	sub    $0x1c,%esp
 80485c4:	8b 6c 24 30          	mov    0x30(%esp),%ebp
 80485c8:	8d b3 04 ff ff ff    	lea    -0xfc(%ebx),%esi
 80485ce:	e8 29 fe ff ff       	call   80483fc <_init>
 80485d3:	8d 83 00 ff ff ff    	lea    -0x100(%ebx),%eax
 80485d9:	29 c6                	sub    %eax,%esi
 80485db:	c1 fe 02             	sar    $0x2,%esi
 80485de:	85 f6                	test   %esi,%esi
 80485e0:	74 27                	je     8048609 <__libc_csu_init+0x59>
 80485e2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 80485e8:	8b 44 24 38          	mov    0x38(%esp),%eax
 80485ec:	89 2c 24             	mov    %ebp,(%esp)
 80485ef:	89 44 24 08          	mov    %eax,0x8(%esp)
 80485f3:	8b 44 24 34          	mov    0x34(%esp),%eax
 80485f7:	89 44 24 04          	mov    %eax,0x4(%esp)
 80485fb:	ff 94 bb 00 ff ff ff 	call   *-0x100(%ebx,%edi,4)
 8048602:	83 c7 01             	add    $0x1,%edi
 8048605:	39 f7                	cmp    %esi,%edi
 8048607:	75 df                	jne    80485e8 <__libc_csu_init+0x38>
 8048609:	83 c4 1c             	add    $0x1c,%esp
 804860c:	5b                   	pop    %ebx
 804860d:	5e                   	pop    %esi
 804860e:	5f                   	pop    %edi
 804860f:	5d                   	pop    %ebp
 8048610:	c3                   	ret    
 8048611:	eb 0d                	jmp    8048620 <__libc_csu_fini>
 8048613:	90                   	nop
 8048614:	90                   	nop
 8048615:	90                   	nop
 8048616:	90                   	nop
 8048617:	90                   	nop
 8048618:	90                   	nop
 8048619:	90                   	nop
 804861a:	90                   	nop
 804861b:	90                   	nop
 804861c:	90                   	nop
 804861d:	90                   	nop
 804861e:	90                   	nop
 804861f:	90                   	nop

08048620 <__libc_csu_fini>:
 8048620:	f3 c3                	repz ret 

Disassembly of section .fini:

08048624 <_fini>:
 8048624:	53                   	push   %ebx
 8048625:	83 ec 08             	sub    $0x8,%esp
 8048628:	e8 73 fe ff ff       	call   80484a0 <__x86.get_pc_thunk.bx>
 804862d:	81 c3 d3 19 00 00    	add    $0x19d3,%ebx
 8048633:	83 c4 08             	add    $0x8,%esp
 8048636:	5b                   	pop    %ebx
 8048637:	c3                   	ret    
