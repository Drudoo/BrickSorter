//
//  main.c
//  ColorSorter
//
//  PIC-2
//
//  Created by Frederik Vanggaard on 4/2/11.
//  Copyright 2011 Drudoo Entertainment. All rights reserved.
//



#pragma config =0x3fdf
#pragma config &=0x3ff7 
#pragma config &=0x3ffc 

#include "int16CXX.h"



bit t0, t1, t2, t3, t4, t5; 


void convertValAD();
void sendBrickToSensor();
void getSensorInput();
void whereToPutBrick();
void deliverBrick();
void resetDirections();
void timerDelay(uns16);
void askForData();


uns16 valAD;
uns8 data, color, gldata;


void main() {      

	TRISA=0;    
	TRISB=0;
	TRISC=0;
    
	PORTA=0;   
	PORTB=0;
	PORTC=0;

    BRGH=1;
	BRG16=1;
    
    SPBRG=103;
    
    SPEN=1;
    
	RX9=0;      
    TX9=0;
    TX9D=0;

    CREN=1;
    
    SYNC=0;

    TXEN=1;
    
	TRMT=0;
    
	t0 = 0;
	t1 = 0;
	t2 = 0;
	t3 = 0;
	t4 = 0;
	t5 = 0;

	resetDirections();

    
	while (1) {	

		if(!t0&&!t1&&!t2&&!t3&&!t4&&!t5) {
            
            sendBrickToSensor(); 		
            
            t0 = 1;
		}
		
        timerDelay(1000);
			
        
		if(t0) {
            
         
            askForData();
            
            t0 = 0;
            t1 = 1;
		}

		if(t1) {
            
            getSensorInput();
            
            t1 = 0;
            t2 = 1;
		}


 		if(t2) {
            
            whereToPutBrick();
            
            t2 = 0;
            t3 = 1;
		}
		
		if(t3) {
            
            deliverBrick();
            t3 = 0;
            t4 = 1;
		}
		
		if(t4) {
            
            resetDirections();
            t4 = 0;
		}
		
    }
}


void resetDirections () {

	while(PORTA.4) {  

		PORTC.0 = 1;   
        PORTC.6 = 0;    
        
    }
        
	PORTC.0 = 0;
	PORTC.6 = 0;


}


void sendBrickToSensor()  {
    

		PORTC.1 = 1;
		PORTC.2 = 0;

		timerDelay(450);

		PORTC.1 = 0;
		PORTC.2 = 1;

		timerDelay(450);

		PORTC.1 = 0;
		PORTC.2 = 0;

		timerDelay(1000);

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

void askForData() {
	sendData(1);
	
}

void getSensorInput() {
  
	color = modtagData();	
    
}


void whereToPutBrick() {
  

	if (color == 1) {

		PORTC.0 = 0;
		PORTC.6 = 1;

		timerDelay(500);

		PORTC.6 = 0;
	} 



	if (color == 2) {


		PORTC.0 = 0;
		PORTC.6 = 1;

		timerDelay(1000);

		PORTC.6 = 0;


	}
	


	if (color == 3) {
		PORTC.0 = 0;
		PORTC.6 = 1;

		timerDelay(1500);

		PORTC.6 = 0;
	}	



	if (color == 4) {

		PORTC.0 = 0;
		PORTC.6 = 1;

		timerDelay(2300);

		PORTC.6 = 0;
	}
	


	if (color == 5) {
		PORTC.0 = 0;
		PORTC.6 = 1;

		timerDelay(2800);

		PORTC.6 = 0;
	}
	

	if (color == 6) {

		PORTC.0 = 0;
		PORTC.6 = 1;

		timerDelay(2700);

		PORTC.6 = 0;

	}

	


}

void deliverBrick() {

		PORTC.3 = 0;	
		PORTC.4 = 1;	

		timerDelay(150);

		PORTC.3 = 1;
		PORTC.4 = 0;
		
		timerDelay(150);
		
		PORTC.3 = 0;

		timerDelay(1000);
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