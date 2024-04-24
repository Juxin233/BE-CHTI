	PRESERVE8
	THUMB   
		

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly

;Section RAM (read write):
	area    maram,data,readwrite
GestionSon_Index dcd 0 ; int GestionSon_Index=0;
SortieSon dcd 0;	int SortieSon =0;
	export GestionSon_Index
	export GestionSon_callback
	import Son
	export SortieSon
	import LongueurSon
	import PeriodeSonMicroSec
	import PWM_Set_Value_TIM3_Ch3
	export GestionSon_Start
; ===============================================================================================
	

;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici	
; Code en c : 
;	int GestionSon_callback(int GestionSon_Index){
;		GestionSon_Index ++;
;		return NULL;
;		}

; Code en c :
;	void GestionSon_callback(int GestionSon_Index){
;			if(GestionSon_Index<=LongueurSon)
;				{
;				short int n = Son[GestionSon_Index];
;				GestionSon_Index ++;
;				SortieSon=719*(n+32768)/65536;
;				}
;				
;							
;}
; Code en C : 
; void GestionSon_start(){
; 	int GestionSon_Index = 0;
;}

; Code en C : 
; void GestionSon_Stop(){
;	int GestionSon_Index=LongueurSon+1;
;}
GestionSon_Start proc
	push {R0}
	push {R1}
	
	LDR R1, =GestionSon_Index
	MOV R0,#0
	STR R0, [R1]
	pop {R1}
	pop {R0}
	bx lr
	ENDP

GestionSon_Stop proc
	push {R1}
	push {R0}
	LDR R0, =GestionSon_Index
	LDR R1, =LongueurSon
	LDR R1,[R1]
	ADD R1,#1
	STR R1,[R0]
	pop {R0}
	pop {R1}
	bx lr
	ENDP
		
		
GestionSon_callback proc
;				short int n = Son[GestionSon_Index];
	LDR R2,=LongueurSon
	LDR R2,[R2]
	LDR R1,=GestionSon_Index;R0 adresse d'index
	LDR R0,[R1]
	CMP R0,R2
	BGE exit	
	
	push {R1}
	
	
	LDR R1,=Son;R1 adresse de son
	ADD R1,R1,R0,LSL#1; R1=*son+i
	LDRSH R2,[R1]
	
	
	ADD R2,#32768
	MOV R1, #720
	MUL R2,R1
	LSR R2,#16
	
	LDR R1,=SortieSon
	STR R2,[R1]
	
	pop {R1}
	
	ADD R0,R0,#1
	STR R0,[R1]
	
	MOV R0,R2
	PUSH {LR}
	BL PWM_Set_Value_TIM3_Ch3
	POP {LR}
exit
	bx lr	
	ENDP
	

	end
	

