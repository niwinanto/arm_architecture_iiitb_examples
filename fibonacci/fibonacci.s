	AREA myData, DATA
		
FIB_START		EQU 0x20000000

	AREA myCode, CODE
		ENTRY
		EXPORT __main

__main
	MOV r0, #0		;make r0 and r1 0 and 1 as fibonacci starting numbers 
	MOV r1, #1
	LDR r3, =FIB_START
	STR r0, [r3]
	ADD r3, r3, #4	;save those in memory
	STR r1, [r3]
	ADD r3, r3, #4
lop CMP r1, #0x0d	;check the r1 for specific fibonacci number
	BGT lop1
	MOV r2, r1		;r2 = r1
	ADD r1, r1, r0	;r1 = r1 + r0
	MOV r0, r2 		;r0 = r2 
	STR r1, [r3]	;store it in memory 
	ADD r3, r3, #4
	B lop
lop1 MOV r1, #1
	MOV r0, #0
	END
