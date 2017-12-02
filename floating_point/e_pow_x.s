; Taylor series implementation of e pow x
; e^x = 1 + x + (x^2 / 2) + (x^3 / 6) + ... + (x^n / n!) + ...



	AREA myData, DATA
		
LARGEST_STORE		EQU 0x20000000 ;place to store largest value in memory
	

	
	AREA myCode, CODE
		ENTRY
		EXPORT __main

__main	FUNCTION
	;ENABLE FPU
	; CPACR is located at address 0xE000ED88
	LDR.W   R0, =0xE000ED88
	; Read CPACR
	LDR     R1, [R0]
	; Set bits 20-23 to enable CP10 and CP11 coprocessors
	ORR     R1, R1, #(0xF << 20)
	; Write back the modified value to the CPACR
	STR     R1, [R0]; wait for store to complete
	DSB
	;reset pipeline now the FPU is enabled
	ISB

			VMOV.F32 s0, #1.0 
			VMOV.F32 s5, #1.0 				  
			VMOV.F32 s1, #5.0 
			VMOV.F32 s2, #15.0 
			VMOV.F32 s3, #1.0 
			
			VDIV.F32 s4, s1, s0 		; ((x = 5) / (n = 1)).
			
loop			VADD.F32 s3, s3, s4 		; rslt = rslt + id
			VMUL.F32 s4, s4, s1 		; id = id * x
			VADD.F32 s0, s0, s5 		; cntr = cntr + inc
			VDIV.F32 s4, s4, s0 		; id = id / cntr
			VCMP.F32 s0, s2     		; compare (cntr == i)
			VMRS 	 APSR_nzcv, FPSCR 	; Copy FPSCR to APSR_nzcv
			BNE 	 loop			; If (cntr != i) then loop

stop			B	 stop			; else stop. 

; Code ends here,
	ENDFUNC
	END
