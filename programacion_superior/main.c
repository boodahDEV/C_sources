#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>
#include <string.h>

#define MAX_DATO_IN 180

//---=== ESTRUCTURA PRINCIPAL DE ALAFABETOS ===---
struct ALPHABETIC_STRUCTURE {
	char com_name [3];
	char cod_asc[8];
	struct ALPHABETIC_STRUCTURE *liga;
};
//---=== ESTRUCTURA PRINCIPAL DE ALAFABETOS ===---

typedef struct ALPHABETIC_STRUCTURE nod;
nod * memoria (nod *); 
nod * CREATES_ALPHABET(nod*, FILE *,FILE *);
void imprimir(nod *);
int busca(nod *, char *);
void openDocument(char *, FILE *, nod *);
void Excecuting_com(int, char *,nod *);
void endBuffer(nod *);
void pause();

//---===	MAIN	===---	
void main (){
		nod *p;
		FILE *archivo1,*archivo2,*archivo;
		char texto_entrada[MAX_DATO_IN];

    system("clear"); //---=== EN UNIX EX CLEAR		EN WINDOWS ES CLS
	scanf("%[^\n]",texto_entrada);
	p=CREATES_ALPHABET(p,archivo1,archivo2);
	openDocument(texto_entrada,archivo,p);
	endBuffer(p);
}//---=== END MAIN()
//---===	MAIN	===---	


nod * memoria (nod * x){
	x=(nod*)malloc(sizeof(struct ALPHABETIC_STRUCTURE));
	return (x); 
}//---=== LIBERA MEMORIA

void imprimir(nod * p){
	nod *q;
	q=p;
	while (q!=NULL){
		printf("--------------------------------------\n");
		printf("%s --- %s\n",q->com_name, q->cod_asc);
		q=q->liga;
	}
		printf("--------------------------------------\n");
}

nod * CREATES_ALPHABET(nod *p, FILE *archivo1,FILE *archivo2){
	int i=0;
	nod *q;
	archivo1 = fopen("../dll/data_1.dll","r");
	archivo2 = fopen("../dll/data_2.dll","r");
	p =memoria (p);

	if (archivo1 == NULL && archivo2 == NULL){
            printf("\nError en el analicis1. \n\n");
			pause();
        }else{
          while (feof(archivo1) == 0 && feof(archivo2)==0){  // el while se ejecuta hasta que encuentre el final del archivo
			  if(i==1){
				//printf("Dentro de q->liga = p\n");
				q=memoria (q);
				fgets(q->com_name,3,archivo1);
				fgets(q->cod_asc,8,archivo2);
				q->liga=p;
				p=q;
			  }else{
				//printf("Dentro de p->liga = null\n");
				fgets(p->com_name,3,archivo1);
			  	fgets(p->cod_asc,8,archivo2);
				  p->liga=NULL;
				  i=1;
			  }
			}
		}
        fclose(archivo1);
		fclose(archivo2);
	return (p);	
}//---=== 	CREA LA LISTA EN BASE AL ALFABETO

int busca(nod *p, char *texto){
	nod *q;
	q=p;
	int band = 0;
 while(q != NULL && !band){
    if (strcmp(q->com_name,texto)==0) {
        band = 1; // si esta en la lista el texto
    	} else {
      	 	 q=q->liga;// si no esta pasa al siguiente nodo
    	}
 }//end while
	return band;
}//---=== BUSCA DENTRO DE LA LISTA, O ALFABETO


void openDocument(char *texto, FILE *archivo,nod *p){  // ---==== UNIR CON LA VERSION DEL MAIN0.0.01_. EN EL CUAL NECESITO GUARDAR EL ARCHIVO
	char temp[MAX_DATO_IN]; //---===  RECUPERA EL TEXTO DEL ARCHIVO DE COMPILACION
	char palabra[1];	//almacena temporalmente el comando definido en las  primeras lineas del comando.
	int bandera;
	int i=0, num;
	archivo = fopen(texto,"r"); //---=== abre el documento de la linea de comando

 if (archivo== NULL){
            printf("\nError, ruta del archivo incorrecta. \n\n");
			pause();
        }else{
          while (feof(archivo) == 0){
			  fgets(temp,MAX_DATO_IN,archivo);//---=== TEMP[] TIENE LA DATA DEL ARCHIVO
		  }
		  for(i = 0; i < 50; i++){
			   if(temp[i]=='l' && temp[i+1]=='m'){
					//strncpy(palabra,temp,2);	este copiaba la cadena entera osea todo temp, por eso lo comente
					
					strncat(palabra,temp,2);
					//printf("\t\t[%s][%d]",palabra,i);
					bandera = busca(p,palabra);
					//break;
				}
				
				if(bandera){
						// si el comando fue exitoso! paso a analizar el resto sde texto
						Excecuting_com(i,temp,p);
						//DEBO LLAMAR A OTRO METODO 
					}
			}//end for
		}
}//---===	DETERMINA LA ENTRADA DEL ARCHIVO A COMPILAR, LO ANALIZA, Y POSTERIORMENTE EJECUTA LA INSTRUCCION.

void Excecuting_com(int i,char *temp,nod *p){
	char valida[1];
	int bandera = 0;
	int j=0;
				//if((int)temp[i]==39 && (  ((int)temp[i+1]>=97 && (int)temp[i+1]<=122) || ((int)temp[i+1]>=65 && (int)temp[i+1]<=90)  ||((int) temp[i+1])  /**/) ){
				if((int)temp[i]==96 && (int)temp[i+1]>=48){
				valida[0]=temp[i];
					bandera = busca(p,valida);
				}//end if para el comando de lectura

				
				if(bandera){
						for(j = 1;(int)temp[i+j]!=96;j++){
							printf("%c",temp[i+j]);
							//pause();
						} //entraccion del texto correcta
						pause();
				}
}//---=== FIN EJECUTA COMANDO!

void endBuffer(nod *p){
	free(p);
}// FIN LIBERA EL BUFFER!
void pause(){
	getchar();
	getchar();
}//FIN PAUSA
