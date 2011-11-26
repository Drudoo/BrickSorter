//
//  main.c
//  ColorSorter
//
//  PIC-1
//
//  Created by Frederik Vanggaard on 4/2/11.
//  Copyright 2011 Drudoo Entertainment. All rights reserved.
//


#pragma config =0x3fdf 
#pragma config &=0x3ff7 
#pragma config &=0x3ffc 

#include "int16CXX.h"


void timerDelay() ;
void longDelay();
void convertValAD();
void getColorInput();
void sendInputToSecondPic();
void getQuestion();

uns16 valAD;
uns8 color, needData, data;

void main()
{
	TRISC=0;
	TRISA=0;
	TRISB=0;
	PORTB=0;
	PORTA=0;
	PORTC=0;
    
    TRISB.7=1;
    
    TX9=0; 
    SPEN=1;
    TRMT=0;
    TX9D=0;
    SYNC=0;
    BRGH=1;
    BRG16=1;
    SPBRG= 103;
    TXEN=1;
    

	TRISA.0=1;
	ANSEL.0=1; 
	ADCON0=0b10000000; 
	ADCON1=0x00;
	
    
	while (1) {	
        
     
		getQuestion();
        
        timerDelay(160);

    }
}


uns8 modtagData() {
	uns8 data;
	data = 0;

    CREN = 0;
	CREN = 1;
    
	while(!RCIF) {
    }
	
    data = RCREG;
	RCIF = 0;
    return data;
}

void sendData(uns8 ud) {
    
	while(!TXIF) {
    }
	
    TXREG=ud;
	TXIF=0;
}


void getQuestion() {
	
    needData = modtagData();

	if(needData) {
        
		convertValAD();
        
        getColorInput();
        
        sendInputToSecondPic();
	}
}



void convertValAD() {

    ADCON0.0=1;  
    timerDelay(80);
    ADCON0.1=1; 
    
    
    while(!ADCON0.1)
        nop();
    
    valAD = ADRESH*256+ADRESL;
}


void getColorInput() {
    
    
    if((valAD > 369)&&(valAD <= 471)) {
        color = 1  ;  
    }

    if((valAD > 0)&&(valAD <= 368)) {
        color = 2;  
    }
    
    /*
    if((valAD > 327)&&(valAD <= 389)) {
        color = 3; 
    }
    
    if((valAD > 122)&&(valAD <= 163)) {
        color = 4;  
    }
    */
    
    if((valAD > 472)&&(valAD <= 1023)) {
        color = 5; 
    }
    

    /*
    if((valAD > 348)&&(valAD <= 399)) {
        color = 6;
    }
    */          
            
}


void sendInputToSecondPic() {
    
	sendData(color);
    
}




void timerDelay(uns16 n) {
    
    INTCON.2=0;
	OPTION_REG=2;
	TMR0 = -125	;
	
    do {
		
        do {
        }
        
		while(!INTCON.2);
		TMR0=-125;
		INTCON.2=0;
	}
	
    while(--n>0);
    
}