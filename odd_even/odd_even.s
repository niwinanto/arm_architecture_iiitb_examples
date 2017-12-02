	AREA myCode, CODE
		ENTRY
		EXPORT __main

__main		FUNCTION
		MOV r1, #45		
		AND r2, r1, #1	;AND with last bit
stop 	B stop
		ENDFUNC
		END
