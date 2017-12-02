	AREA myCode, CODE
		ENTRY
		EXPORT __main
			
__main   	FUNCTION
		MOV r1, #45
		MOV r2, #15
		B gcd		
loop	CMP r1, r2		;compare r1 and r2 
		ITE GT 			
		SUBGT r1, r1, r2	;if true 
		SUBLE r2, r2, r1	;else	
gcd		CMP r1, r2			;compare r1 and r1 
		BNE loop			;jump to loop on not equal
stop	B stop
		ENDFUNC
		END
		
		
