#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <conio2.h>
#include <locale.h>
#define LARGURA 145
#define ALTURA 40
#include "gamebib.h"

void main(){
	cria_itens();
	weapons();
	protection();
	pots();
	municao();
	cria_mochila();
    int escolha;
    for(;;){
    	escolha=menu();
    	switch(escolha){
    		case 0:
    			start();
    			break;
    		case 1:
    			options();
    			break;
    		case 2:
    			exit(0);
    			break;
		}
    }
    	return;
}    
