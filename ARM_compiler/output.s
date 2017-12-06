;****************CODE STARTS*****************
AREA myCode, CODE
	ENTRY
	EXPORT __main


__main FUNCTION

	MOV R0, #1
	PUSH {R0}
	MOV R0, #3
	PUSH {R0}
	POP {R0, R1}
	ADD R0, R0, R1
	PUSH {R0}

stop 	B stop
	ENDFUNC
	END
;****************CODE ENDS********************
