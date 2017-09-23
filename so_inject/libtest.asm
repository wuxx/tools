
libtest.so:     file format elf32-i386


Disassembly of section .init:

0000036c <_init>:
 36c:	53                   	push   %ebx
 36d:	83 ec 08             	sub    $0x8,%esp
 370:	e8 4b 00 00 00       	call   3c0 <__x86.get_pc_thunk.bx>
 375:	81 c3 8b 1c 00 00    	add    $0x1c8b,%ebx
 37b:	8b 83 f4 ff ff ff    	mov    -0xc(%ebx),%eax
 381:	85 c0                	test   %eax,%eax
 383:	74 05                	je     38a <_init+0x1e>
 385:	e8 26 00 00 00       	call   3b0 <__gmon_start__@plt>
 38a:	83 c4 08             	add    $0x8,%esp
 38d:	5b                   	pop    %ebx
 38e:	c3                   	ret    

Disassembly of section .plt:

00000390 <__cxa_finalize@plt-0x10>:
 390:	ff b3 04 00 00 00    	pushl  0x4(%ebx)
 396:	ff a3 08 00 00 00    	jmp    *0x8(%ebx)
 39c:	00 00                	add    %al,(%eax)
	...

000003a0 <__cxa_finalize@plt>:
 3a0:	ff a3 0c 00 00 00    	jmp    *0xc(%ebx)
 3a6:	68 00 00 00 00       	push   $0x0
 3ab:	e9 e0 ff ff ff       	jmp    390 <_init+0x24>

000003b0 <__gmon_start__@plt>:
 3b0:	ff a3 10 00 00 00    	jmp    *0x10(%ebx)
 3b6:	68 08 00 00 00       	push   $0x8
 3bb:	e9 d0 ff ff ff       	jmp    390 <_init+0x24>

Disassembly of section .text:

000003c0 <__x86.get_pc_thunk.bx>:
 3c0:	8b 1c 24             	mov    (%esp),%ebx
 3c3:	c3                   	ret    
 3c4:	66 90                	xchg   %ax,%ax
 3c6:	66 90                	xchg   %ax,%ax
 3c8:	66 90                	xchg   %ax,%ax
 3ca:	66 90                	xchg   %ax,%ax
 3cc:	66 90                	xchg   %ax,%ax
 3ce:	66 90                	xchg   %ax,%ax

000003d0 <deregister_tm_clones>:
 3d0:	55                   	push   %ebp
 3d1:	89 e5                	mov    %esp,%ebp
 3d3:	53                   	push   %ebx
 3d4:	e8 e7 ff ff ff       	call   3c0 <__x86.get_pc_thunk.bx>
 3d9:	81 c3 27 1c 00 00    	add    $0x1c27,%ebx
 3df:	83 ec 14             	sub    $0x14,%esp
 3e2:	8d 83 1b 00 00 00    	lea    0x1b(%ebx),%eax
 3e8:	8d 93 18 00 00 00    	lea    0x18(%ebx),%edx
 3ee:	29 d0                	sub    %edx,%eax
 3f0:	83 f8 06             	cmp    $0x6,%eax
 3f3:	77 06                	ja     3fb <deregister_tm_clones+0x2b>
 3f5:	83 c4 14             	add    $0x14,%esp
 3f8:	5b                   	pop    %ebx
 3f9:	5d                   	pop    %ebp
 3fa:	c3                   	ret    
 3fb:	8b 83 ec ff ff ff    	mov    -0x14(%ebx),%eax
 401:	85 c0                	test   %eax,%eax
 403:	74 f0                	je     3f5 <deregister_tm_clones+0x25>
 405:	89 14 24             	mov    %edx,(%esp)
 408:	ff d0                	call   *%eax
 40a:	eb e9                	jmp    3f5 <deregister_tm_clones+0x25>
 40c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00000410 <register_tm_clones>:
 410:	55                   	push   %ebp
 411:	89 e5                	mov    %esp,%ebp
 413:	53                   	push   %ebx
 414:	e8 a7 ff ff ff       	call   3c0 <__x86.get_pc_thunk.bx>
 419:	81 c3 e7 1b 00 00    	add    $0x1be7,%ebx
 41f:	83 ec 14             	sub    $0x14,%esp
 422:	8d 83 18 00 00 00    	lea    0x18(%ebx),%eax
 428:	8d 93 18 00 00 00    	lea    0x18(%ebx),%edx
 42e:	29 d0                	sub    %edx,%eax
 430:	c1 f8 02             	sar    $0x2,%eax
 433:	89 c1                	mov    %eax,%ecx
 435:	c1 e9 1f             	shr    $0x1f,%ecx
 438:	01 c8                	add    %ecx,%eax
 43a:	d1 f8                	sar    %eax
 43c:	75 06                	jne    444 <register_tm_clones+0x34>
 43e:	83 c4 14             	add    $0x14,%esp
 441:	5b                   	pop    %ebx
 442:	5d                   	pop    %ebp
 443:	c3                   	ret    
 444:	8b 8b fc ff ff ff    	mov    -0x4(%ebx),%ecx
 44a:	85 c9                	test   %ecx,%ecx
 44c:	74 f0                	je     43e <register_tm_clones+0x2e>
 44e:	89 44 24 04          	mov    %eax,0x4(%esp)
 452:	89 14 24             	mov    %edx,(%esp)
 455:	ff d1                	call   *%ecx
 457:	eb e5                	jmp    43e <register_tm_clones+0x2e>
 459:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00000460 <__do_global_dtors_aux>:
 460:	55                   	push   %ebp
 461:	89 e5                	mov    %esp,%ebp
 463:	53                   	push   %ebx
 464:	e8 57 ff ff ff       	call   3c0 <__x86.get_pc_thunk.bx>
 469:	81 c3 97 1b 00 00    	add    $0x1b97,%ebx
 46f:	83 ec 14             	sub    $0x14,%esp
 472:	80 bb 18 00 00 00 00 	cmpb   $0x0,0x18(%ebx)
 479:	75 24                	jne    49f <__do_global_dtors_aux+0x3f>
 47b:	8b 83 f0 ff ff ff    	mov    -0x10(%ebx),%eax
 481:	85 c0                	test   %eax,%eax
 483:	74 0e                	je     493 <__do_global_dtors_aux+0x33>
 485:	8b 83 14 00 00 00    	mov    0x14(%ebx),%eax
 48b:	89 04 24             	mov    %eax,(%esp)
 48e:	e8 0d ff ff ff       	call   3a0 <__cxa_finalize@plt>
 493:	e8 38 ff ff ff       	call   3d0 <deregister_tm_clones>
 498:	c6 83 18 00 00 00 01 	movb   $0x1,0x18(%ebx)
 49f:	83 c4 14             	add    $0x14,%esp
 4a2:	5b                   	pop    %ebx
 4a3:	5d                   	pop    %ebp
 4a4:	c3                   	ret    
 4a5:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 4a9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

000004b0 <frame_dummy>:
 4b0:	55                   	push   %ebp
 4b1:	89 e5                	mov    %esp,%ebp
 4b3:	53                   	push   %ebx
 4b4:	e8 07 ff ff ff       	call   3c0 <__x86.get_pc_thunk.bx>
 4b9:	81 c3 47 1b 00 00    	add    $0x1b47,%ebx
 4bf:	83 ec 14             	sub    $0x14,%esp
 4c2:	8b 83 08 ff ff ff    	mov    -0xf8(%ebx),%eax
 4c8:	85 c0                	test   %eax,%eax
 4ca:	74 15                	je     4e1 <frame_dummy+0x31>
 4cc:	8b 83 f8 ff ff ff    	mov    -0x8(%ebx),%eax
 4d2:	85 c0                	test   %eax,%eax
 4d4:	74 0b                	je     4e1 <frame_dummy+0x31>
 4d6:	8d 93 08 ff ff ff    	lea    -0xf8(%ebx),%edx
 4dc:	89 14 24             	mov    %edx,(%esp)
 4df:	ff d0                	call   *%eax
 4e1:	83 c4 14             	add    $0x14,%esp
 4e4:	5b                   	pop    %ebx
 4e5:	5d                   	pop    %ebp
 4e6:	e9 25 ff ff ff       	jmp    410 <register_tm_clones>

000004eb <lib_func1>:
 4eb:	55                   	push   %ebp
 4ec:	89 e5                	mov    %esp,%ebp
 4ee:	83 ec 10             	sub    $0x10,%esp
 4f1:	8b 45 0c             	mov    0xc(%ebp),%eax
 4f4:	8b 55 08             	mov    0x8(%ebp),%edx
 4f7:	01 d0                	add    %edx,%eax
 4f9:	89 45 fc             	mov    %eax,-0x4(%ebp)
 4fc:	8b 45 fc             	mov    -0x4(%ebp),%eax
 4ff:	c9                   	leave  
 500:	c3                   	ret    

Disassembly of section .fini:

00000504 <_fini>:
 504:	53                   	push   %ebx
 505:	83 ec 08             	sub    $0x8,%esp
 508:	e8 b3 fe ff ff       	call   3c0 <__x86.get_pc_thunk.bx>
 50d:	81 c3 f3 1a 00 00    	add    $0x1af3,%ebx
 513:	83 c4 08             	add    $0x8,%esp
 516:	5b                   	pop    %ebx
 517:	c3                   	ret    
