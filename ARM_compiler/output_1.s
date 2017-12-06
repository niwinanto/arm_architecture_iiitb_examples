;expression parsed is: 1/(2-2)
;It is a balanced expression
;postfix form is : 1,2,2,-,/,


;****************CODE STARTS*****************
	AREA myCode, CODE
		ENTRY
		EXPORT __main


__main FUNCTION

	MOV R0, #1
	PUSH {R0}
	MOV R0, #2
	PUSH {R0}
	MOV R0, #2
	PUSH {R0}

	POP {R1, R0}
;Substraction operation
	SUB R0, R0, R1
	PUSH {R0}

	POP {R1, R0}
;Division operation
	CMP R1, #0
	BEQ stop
	DIV R0, R0, R1
	PUSH {R0}

stop 	B stop
	ENDFUNC
	END
;****************CODE ENDS********************
