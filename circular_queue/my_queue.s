;Circular dequeue implementation in assembly

	AREA myData, DATA
		
QUEUE_START		EQU 0x20000000
QUEUE_END		EQU 0x20000028
LENGTH			EQU QUEUE_END - QUEUE_START
	
	AREA myCode, CODE
		ENTRY
		EXPORT __main

ENQ							;Enqueue function starts here

lp	CMP r2, #LENGTH			;compare queue length with r2
	BNE lp0
	BX lr
	
lp0	CMP r3, #0				;compare r3 for number of elements to be added
	BNE lp1
	BX lr
	
lp1	STR r4, [r1]			;store queue
	ADD r2, r2, #1			;increment present queue length
	SUB r3, r3, #1			;decrement number count
	CMP r1, r8				;loop till number count reaches
	BNE lp2
	LDR r1, =QUEUE_START 	;mode operation for circular queue
	B lp

lp2 ADD r1, r1, #4
	B lp


DEQ							;function Dequeue starts here

do	CMP r2, #0				;compare for queue lenght empty
	BNE do0
	BX lr

do0 CMP r3, #0				;compare for loop to repeat r3 times
	BNE do1
	BX lr

	
do1	SUB r2, r2, #1 			;deque operation
	SUB r3, r3, #1
	CMP r0, r8				;check for end of queue
	BNE do2
	LDR r0, =QUEUE_START	;mod operation for circular queue
	B do					;repeat

do2 ADD r0, r0, #4 			;next register
	B do		   			;repeat


__main
	LDR r0, =QUEUE_START	;Head of queue
	LDR r1, =QUEUE_START	;Tail of queue
	LDR r8, =QUEUE_END		;End address of queue
	MOV r2, #0
	
	MOV r3, #0x1			;r3 times enque or dequeue runs(that is 1)
	MOV r4, #22				;value in r4 writes to queue(that is 22 heare)
	BL ENQ

	MOV r3, #0x01			;1 time deque
	BL DEQ					;call dequeue

	MOV r3, #0x20			;r3 times enque or dequeue runs
	MOV r4, #11				;value in r4 writes to queue(that is 11 heare)
	BL ENQ					;call enqueue
	
	MOV r3, #0x10			;10 times dequeue
	BL DEQ					;call dequeue

	END
	
	
