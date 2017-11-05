;find largest of 3 numbers
	AREA myData, DATA
		
LARGEST_STORE		EQU 0x20000000 ;place to store largest value in memory
	
	AREA myCode, CODE
		ENTRY
		EXPORT __main

__main
	MOV r0, #0	;3 registers for saving 3 number
	MOV r1, #1	
	MOV r2, #2
	MOV r4, r0   ;current assumed larget
	LDR r3, =LARGEST_STORE
	
	CMP r4, r1		;compare r1 with largest and replace if it is larger
	IT LT	
	MOVLT r4, r1
	
	CMP r4, r2		;compare r2 with largest and replace if it is larger
	IT LT
	MOVLT r4, r2
	
	STR r4, [r3]	;store largest to memory
	
	END
