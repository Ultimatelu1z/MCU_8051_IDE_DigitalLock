#include <8052.h>
#define LINHA1 P1_0
#define LINHA2 P1_1
#define LINHA3 P1_2
#define LINHA4 P1_3
#define COLUNA1 P1_4
#define COLUNA2 P1_5
#define COLUNA3 P1_6
#define COLUNA4 P1_7

int digitCont=0; /*conta quantos digitos foram inseridos*/
int tentativa=0; /* Conta as tentativas*/
volatile unsigned int tecladoPress=0; /* Recebe o valor do teclado */
int digito[4]={0}; /* armazena o dado digtd */
const int senha[4]={1,2,3,4}; /* senha dfna */
const unsigned char codigo[]={192,249,164,176,136,153,146,130,131,248,128,144,198,192,137,161}; /* código do display */
int teclado[4][4]={
	{1,  2,  3,  4},
	{5,  6,  7,  8},
	{9,  10, 11, 12},
	{13, 14, 15, 16}};
/* cada número representa um carcter do keypad 4x4 */


int LerTeclado(void);
void Display7Seg(void);
/*Prototipos das funções*/

void main(void){



	while(1){
		tecladoPress=LerTeclado();

        if(tecladoPress==13){
                if(digito[0]!=0&&digito[1]!=0&&digito[2]!=0){digito[3]=0; tecladoPress=0; digitCont--;}/* Apaga o digito 4 se * for acionado */
                if(digito[0]!=0&&digito[1]!=0&&digito[3]==0){digito[2]=0; tecladoPress=0; digitCont--;}/* Apaga o digito 3 se * for acionado */
                if(digito[0]!=0&&digito[2]==0&&digito[3]==0){digito[1]=0; tecladoPress=0; digitCont--;}/* Apaga o digito 2 se * for acionado */
                if(digito[1]==0&&digito[2]==0&&digito[3]==0){digito[0]=0; tecladoPress=0; digitCont--;}/* Apaga o digito 1 se * for acionado */
        }
		

		if(tecladoPress==14)tecladoPress=13; /* 0 */
		if(tecladoPress==15)tecladoPress=14; /* # */
		if(tecladoPress==16)tecladoPress=15; /* d */

        /* Armazena os digitos da senha*/
        if(tecladoPress!=0){
                if(digito[0]==0){digito[0]=tecladoPress; tecladoPress=0;}
                if(digito[0]!=0&&digito[1]==0){digito[1]=tecladoPress; tecladoPress=0;}
                if(digito[1]!=0&&digito[2]==0){digito[2]=tecladoPress; tecladoPress=0;}
                if(digito[2]!=0&&digito[3]==0){digito[3]=tecladoPress; tecladoPress=0;}
        }

		if(digito[0]==senha[0]&&digito[1]==senha[1]&&digito[2]==senha[2]&&digito[3]==senha[3]){
			
			P0_7=0;
			digito[0]=0;
            digito[1]=0;
            digito[2]=0;
            digito[3]=0;
		}
		else if(digitCont==4&&digito[0]!=senha[0] || digitCont==4&&digito[1]!=senha[1] || digitCont==4&&digito[2]!=senha[2] || digitCont==4&&digito[3]!=senha[3] ){

			tentativa++;
						
		}
		Display7Seg();
	}

}

void Display7Seg(void){
	if(tentativa<3){
		if(digito[0]<16){
			P0=255;
			P2=codigo[digito[0]];
			P0_3=0;
			
			
			if(digito[1]<16){
				P0=255;
				P2=codigo[digito[1]];
				P0_2=0;
				
	
				if(digito[2]<16){
					P0=255;
					P2=codigo[digito[2]];
					P0_1=0;
					
					
					if(digito[3]<16){
						P0=255;
						P2=codigo[digito[3]];
						P0_0=0;
						P0=255;

					}
				}
			}
		}
	
	}

	if(tentativa==3){

		P0=255;
		P2=134;
		P0_3=0;

		P0=255;
		P2=206;
		P0_2=0;

		P0=255;
		P2=206;
	        P0_1=0;

		P0=255;
		P2=192;
		P0_0=0;
		while(1);
	}
}
int LerTeclado(void){

	int retornaTecla=0;
	int col;
	P1=0xFF;

	for(col=0;col<4;col++){

		switch(col){

			case 0: COLUNA1=0;
				if(LINHA1==0){retornaTecla=teclado[0][0]; digitCont++;}
				while(LINHA1==0);
				if(LINHA2==0){retornaTecla=teclado[1][0]; digitCont++;}
				while(LINHA2==0);
				if(LINHA3==0){retornaTecla=teclado[2][0]; digitCont++;}
				while(LINHA3==0);
				if(LINHA4==0)retornaTecla=teclado[3][0]; 
				while(LINHA4==0);
				COLUNA1=1;
				if(retornaTecla!=0)col=4; /* Caso uma tecla tenha sido encontrada, termina o loop*/
				break;

			case 1: COLUNA2=0;
				if(LINHA1==0){retornaTecla=teclado[0][1]; digitCont++;}
				while(LINHA1==0);
				if(LINHA2==0){retornaTecla=teclado[1][1]; digitCont++;}
				while(LINHA2==0);
				if(LINHA3==0){retornaTecla=teclado[2][1]; digitCont++;}
				while(LINHA3==0);
				if(LINHA4==0){retornaTecla=teclado[3][1]; digitCont++;}
				while(LINHA4==0);
				COLUNA2=1;
				if(retornaTecla!=0)col=4;
				break;

			case 2: COLUNA3=0;
				if(LINHA1==0){retornaTecla=teclado[0][2]; digitCont++;}
				while(LINHA1==0);
				if(LINHA2==0){retornaTecla=teclado[1][2]; digitCont++;}
				while(LINHA2==0);
				if(LINHA3==0){retornaTecla=teclado[2][2]; digitCont++;}
				while(LINHA3==0);
				if(LINHA4==0){retornaTecla=teclado[3][2]; digitCont++;}
				while(LINHA4==0);
				COLUNA3=1;
				if(retornaTecla!=0)col=4;
				break;

			case 3: COLUNA4=0;
				if(LINHA1==0){retornaTecla=teclado[0][3]; digitCont++;}
				while(LINHA1==0);
				if(LINHA2==0){retornaTecla=teclado[1][3]; digitCont++;}
				while(LINHA2==0);
				if(LINHA3==0){retornaTecla=teclado[2][3]; digitCont++;}
				while(LINHA3==0);
				if(LINHA4==0){retornaTecla=teclado[3][3]; digitCont++;}
				while(LINHA4==0);
				COLUNA4=1;
				if(retornaTecla!=0)col=4;
				break;
			
			default: break;

		}


	}
	P1=0x0F;
	return retornaTecla;
}

