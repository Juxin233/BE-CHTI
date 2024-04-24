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
; void GestionSon_
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
	
