typedef struct enemy{
	int ID;
	char nome[30];
	int vida;
	int chance_critico;
	int dano;
}CREATURE;

typedef struct player{
	char nome[30];
	int vida;
	int vida_max;
	int forca;
	int destreza;
	int armor[4];
	int armas[5];//a quantidade de muniÃ§Ã£o de armas[x] estÃ¡ armazenada no vetor muniÃ§Ã£o[x];
	int municao[5];
}PLAYER;

typedef struct{ // SLOT DA MOCHILA, CONTENDO O ITEM E A QUANTIDADE DO ITEM
    int ID;
    int quantidade;
}recurso;

typedef struct mochila{
	int nivel;
	recurso *item;
}BAG;

typedef struct item{
	int ID;// a struct item vai criar todos os itens, a ID é a parte que importa pro código, o nome é so pra o usuário saber com o que ta mexendo
	char nome[20];
}ITEM;

typedef struct weapons{
	int ID;
	char nome[30];
	int dano;
	int chance_critico;
	int receita[5];
	int quantidade[5];
}WEAP;

typedef struct armor{
	int ID;
	char nome[30];
	int protecao;
	int receita[5];
	int quantidade[5];// protecao é uma porcentagem que é diminuida do dano final do inimigo;
}ARMOR;

typedef struct potions{
	int ID; 
	char nome[20];
	int cura;
	int receita[5];
	int quantidade[5];
}POT;

typedef struct municao{
	int ID;
	int armaID;
	char nome[30];
	int quantidade_muni;
	int receita[2];
	int quantidade[2];
}MUNI;
//por enquanto variáveis globais são a melhor opção para que não seja necessário se preocupar com a passagem de parâmetros e somente com a lógica
CREATURE danger[3];
PLAYER character;//struct armazena dados do player, como skills, armas, armadura e nome
BAG mochila; //vai ser a mochila do player durante o jogo inteiro, começando com 10 espaços e podendo chegar a 20 no maximo;
ITEM itens[17];// vetor que armazena os itens primários do jogo, os recursos básicos que serão ferramenta derivação para outros itens
WEAP armas[9];// vetor que armazena as armas do jogo, estas feitas atráves dos recursos primários
ARMOR armor[15];//vetor que armazena as armaduras do jogo, estas feitas através dos recursos primários
POT potions[3];//vetor que armazena as poções do jogo, estas feitas através dos recursos primários
MUNI municoes[7];// vetor que armazena as munições do jogo, estas feitas através dos recursos primários
char cenario[ALTURA*3][LARGURA*3], map_interact[ALTURA*3][LARGURA*3];
int x=20, y=20, block[ALTURA*3][LARGURA*3], multx=0, multy=0, tamanho_da_mochila=10, nivel=0, inimigos_mortos=0, comb=0;
//x e y são ar coordenadas do player no mapa, essas são alteradas toda vez que o jogador pressiona uma tecla de movimento
//block é uma matriz de inteiros feita para controle, declarada com o mesmo tamanho da matriz cenario, dessa maneira, é possível colocar
//números representando uma propriedade de cada área do jogo, por exemplo, onde tem 0 é area neutra e pode caminhar normalmente, onde é 1,
//o personagem passa por trás do objeto, causando um efeito legal no jogo, já onde é 2, zonas fora de combate, onde é 3, são muros e o personagem não pode
//passar diretamente por ele, etc...
//matriz cenario é estética, serve para ser colorida e armazenar o cenário do jogo
//matriz map_interact é uma matriz que gera coordenadas aleatórias para inimigos, respeitando as zonas seguras (sem combate) e as bordas de cenário
//essa matriz também gera as lojas, mas essas são geradas manualmente, em lugares planejados do mapa
//multx e multy: apesar das matrizes serem de tamanho 120x435, só é acessada uma parcela dessa matriz de 40x145 por vez, multx e multy são variáveis que
//controlam qual parcela da matriz está sendo acessada;
//tamanho_da_mochila controla a alocação dinamica de memória para os upgrades da mochila 						
/* 	Sumário de Cores:
	1-Verde Claro - Folhas de Arvores (personagem passa por tras)
	2-Marrom - Tronco de Arvores	(personagem passa por tras)
	3-Amarelo - Cor do personagem
	4-Cinza Escuro - Pedra escura da estrada - (personagem se sobrepõe)
	5-Cinza Claro - Pedra clara da estrada - (personagem se sobrepõe)
	6-Vermelho - Inimultxgos no geral - (personagem não pode chegar perto sem entrar em combate)
	7-Branco - Cor de borda ou elemento do cenário - (personagem passa por tras)
	8-Azul Claro - Cor de vidros - (personagem passa por tras)
	11-Verde Claro - Nada ainda - (personagem se sobrepoe)
	22-Marrom - Estrada de Terra - (personagem se sobrepoe)
	44-Cinza Escuro - Elemento de Cenário - (personagem passa por tras)
	66-Vermelho - Elemento de Cenário - (personagem passa por tras)
	
	Interações na matriz BLOCK:
	0 - o personagem se sobrepõe ao objeto normalmente
	1 - o personagem passa por trás do objeto
	2 - o personagem está em uma zona fora de combate (acampamento)*/


void cria_cenario();
void cria_interacoes();
void imprime_cenario();
void person();
void cria_matriz_block();
void move(char set);
void start();
void load();
int menu();
void sit0();
void sit1();
void sit2();
void sit3();
int game();
int checa_interacoes();
void weapons();
void protection();
void pots();
void municao();
void cria_itens();
void inicializa_player();
void imprime_player();
void compra_item(int pos, int setor);
void cria_itens();
void weapons();
void protection();
void pots();
void municao();
int cria_mochila();
void interage_item(int n);
void interage_pot(int pos, int n);
void interage_rec(int pos, int n);
void remove_da_mochila(int ID, int quant);
int interage_arma(int n, int modo);
int combate();
void printa_sit();
void defende(int ini);
void dropa_itens(int ini);
void reseta_player();
void options();
void save_progress();

//carrega variáveis
void creatures(){
	int i;
	for(i=0; i<3; i++){
		switch(i){
			case 0:
				danger[i].ID=1;
				strcpy(danger[i].nome, "Animal selvagem");
				danger[i].vida = 120;
				danger[i].dano = 15;
				danger[i].chance_critico = 45;
				break;
			case 1:
				danger[i].ID=2;
				strcpy(danger[i].nome, "Caçador das Montanhas");
				danger[i].vida = 180;
				danger[i].dano = 40;
				danger[i].chance_critico = 45;
				break;
			case 2:
				danger[i].ID=3;
				strcpy(danger[i].nome, "Terráqueo Sobrevivente");
				danger[i].vida = 240;
				danger[i].dano = 55;
				danger[i].chance_critico = 50;
				break;
		}
	}
}

void cria_itens(){
	int i;
	FILE *it;
	if((it=(fopen("itens.bin", "rb")))!=NULL){
		for(i=0; i<17; i++){
			fread(&itens[i].ID, sizeof(int), 1, it);
			fread(&itens[i].nome, sizeof(itens[i].nome), 1, it);
		}
		fclose(it);
	}
}

void weapons(){//todos os itens foram armazenados em arquivos pq era mais rapido pra declarar tudo
	int i, j, k, compra;
	FILE *it;
	if((it=(fopen("armas.bin", "rb")))!=NULL){
		for(i=0;i<9; i++){
			fread(&armas[i].ID, sizeof(int), 1, it);
			fread(&armas[i].nome, sizeof(char), 30, it);
			fread(&armas[i].dano, sizeof(int), 1, it);
			fread(&armas[i].chance_critico, sizeof(int), 1, it);
			for(j=0; j<5; j++)
				fread(&armas[i].receita[j], sizeof(int), 1, it);
			for(j=0; j<5; j++)
				fread(&armas[i].quantidade[j], sizeof(int), 1, it);	
		}
		fclose(it);
	}
}

void protection(){
	int i, j, k, compra;
	FILE *it;
	if((it=(fopen("armor.bin", "rb")))!=NULL){
		for(i=0;i<15; i++){
			fread(&armor[i].ID, sizeof(int), 1, it);
			fread(&armor[i].nome, sizeof(char), 30, it);
			fread(&armor[i].protecao, sizeof(int), 1, it);
			for(j=0; j<5; j++)
				fread(&armor[i].receita[j], sizeof(int), 1, it);
			for(j=0; j<5; j++)
				fread(&armor[i].quantidade[j], sizeof(int), 1, it);	
		}
	}
}

void pots(){
	int i, j, k, compra;
	FILE *it;
	if((it=(fopen("potions.bin", "rb")))!=NULL){
		for(i=0;i<3; i++){
			fread(&potions[i].ID, sizeof(int), 1, it);
			fread(&potions[i].nome, sizeof(char), 30, it);
			fread(&potions[i].cura, sizeof(int), 1, it);
			for(j=0; j<5; j++)
				fread(&potions[i].receita[j], sizeof(int), 1, it);
			for(j=0; j<5; j++)
				fread(&potions[i].quantidade[j], sizeof(int), 1, it);	
		}
	}
}

void municao(){
	int i, compra;
	for(i=0; i<7; i++){
		municoes[i].ID=i+1;
		switch(i){
			case 0:
				strcpy(municoes[i].nome,"Flechas");
				municoes[i].armaID=1;
				municoes[i].quantidade_muni=40;
				municoes[i].receita[0]=5;
				municoes[i].receita[1]=6;
				municoes[i].quantidade[0]=20;
				municoes[i].quantidade[1]=5;
				break;
			case 1:
				strcpy(municoes[i].nome,"Balas de Revólver");
				municoes[i].armaID=4;
				municoes[i].quantidade_muni=40;
				municoes[i].receita[0]=6;
				municoes[i].quantidade[0]=5;
				municoes[i].receita[1]=0;
				municoes[i].quantidade[1]=0;
				break;
			case 2:
				strcpy(municoes[i].nome,"Balas de Pistola");
				municoes[i].armaID=5;
				municoes[i].quantidade_muni=40;
				municoes[i].receita[0]=6;
				municoes[i].quantidade[0]=10;
				municoes[i].receita[1]=0;
				municoes[i].quantidade[1]=0;
				break;
			case 3:
				strcpy(municoes[i].nome,"Balas de Pistola Automática");
				municoes[i].armaID=6;
				municoes[i].quantidade_muni=40;
				municoes[i].receita[0]=6;
				municoes[i].quantidade[0]=15;
				municoes[i].receita[1]=0;
				municoes[i].quantidade[1]=0;
				break;
			case 4:
				strcpy(municoes[i].nome,"Balas de Espingarda");
				municoes[i].armaID=7;
				municoes[i].quantidade_muni=20;
				municoes[i].receita[0]=10;
				municoes[i].quantidade[0]=15;
				municoes[i].receita[1]=0;
				municoes[i].quantidade[1]=0;;
				break;
			case 5:
				strcpy(municoes[i].nome,"Balas de Fuzil");
				municoes[i].armaID=8;
				municoes[i].quantidade_muni=15;
				municoes[i].receita[0]=9;
				municoes[i].quantidade[0]=10;
				municoes[i].receita[1]=0;
				municoes[i].quantidade[1]=0;
				break;
			case 6:
				strcpy(municoes[i].nome,"Balas de Rifle");
				municoes[i].armaID=9;
				municoes[i].quantidade_muni=10;
				municoes[i].receita[0]=8;
				municoes[i].quantidade[0]=5;
				municoes[i].receita[1]=0;
				municoes[i].quantidade[1]=0;
				break;
		}
	}
}
//SEÇÃO MENU
int menu(){
    char set;
    static int i;
    for(;;){
        switch(i){
            case 0:
                sit0();
                break;
            case 1:
                sit1();
                break;
            case 2:
                sit2();
                break;
            default:
                break;
        }
        set=getch();
        if(set==-32){
            set=getch();
            if(set==72&&i>0)
                i--;
            if(set==80&&i<2)
                i++;
    	}else{
        	return i;
        }
    }
}

void logo(void){
	int coluna,linha,k;
	for(coluna=0;coluna<13;coluna++){
		textcolor(4);
		textbackground(0); 
		for(linha=0;linha<145;linha++){
			if(((coluna==0)||(coluna==12))||((linha == 0)||(linha==144))){
				textcolor(5);
				printf("%c",219);
				textcolor(5);
			}else{
				textbackground(0);
				if((coluna >= 2 && coluna <= 10) && ((linha > 4 ) && (linha <= 142))){
					textbackground(0);
					switch (coluna){
						case 2:
							if((linha >= 5 && linha <= 17)|| (linha >= 19 && linha <= 31)||(linha >= 43 && linha <= 45)||(linha >= 47 && linha <= 59)||(linha >= 61 && linha <= 68)||(linha >= 72 && linha <= 79)||(linha >= 81 && linha <= 93)||(linha >= 95 && linha <= 107)||(linha >= 109 && linha <= 111)||(linha >= 113 && linha <= 125)||(linha >= 127 && linha <= 130)||(linha >= 139 && linha <= 141)){
								printf("%c",219);
							}else{
								textcolor(8);
								printf("%c",219);
								textcolor(5);
							}	
							break;
						case 3:
							if((linha >= 5 && linha <= 7)||(linha >= 15 && linha <= 17)||(linha >= 19 && linha <= 21)||(linha >= 43 && linha <= 45)||(linha >= 47 && linha <= 49)||(linha >= 61 && linha <= 63)||(linha >= 68 && linha <= 69)||(linha >= 71 && linha <= 72)||(linha >= 77 && linha <= 79)||(linha >= 81 && linha <= 83)||(linha >= 91 && linha <= 93)||(linha >= 100 && linha <= 102)||(linha >= 113 && linha <= 115)||(linha >= 123 && linha <= 125)||(linha >= 127 && linha <= 129)||(linha == 131)||(linha >= 139 && linha <= 141)){
								printf("%c",219);
							}else{
								textcolor(8);
								printf("%c",219);
								textcolor(5);
							}	
							break;
						case 4:
							if((linha >= 5 && linha <= 7)||(linha >= 15 && linha <= 17)||(linha >= 19 && linha <= 21)||(linha >= 43 && linha <= 45)||(linha >= 47 && linha <= 49)||(linha >= 61 && linha <= 63)||(linha >= 69 && linha <= 71)||(linha >= 77 && linha <= 79)||(linha >= 81 && linha <= 83)||(linha >= 91 && linha <= 93)||(linha >= 100 && linha <= 102)||(linha >= 109 && linha <= 111)||(linha >= 113 && linha <= 115)||(linha >= 123 && linha <= 125)||(linha >= 127 && linha <= 129)||(linha == 132)||(linha >= 139 && linha <= 141)){
								printf("%c",219);
							}else{
								textcolor(8);
								printf("%c",219);
								textcolor(5);
							}	
							break;
						case 5:
							if((linha >= 5 && linha <= 7)||(linha >= 15 && linha <= 17)||(linha >= 19 && linha <= 21)||(linha >= 43 && linha <= 45)||(linha >= 47 && linha <= 49)||(linha >= 61 && linha <= 63)||(linha >= 77 && linha <= 79)||(linha >= 81 && linha <= 83)||(linha >= 91 && linha <= 93)||(linha >= 100 && linha <= 102)||(linha >= 109 && linha <= 111)||(linha >= 113 && linha <= 115)||(linha >= 123 && linha <= 125)||(linha >= 127 && linha <= 129)||(linha == 133)||(linha >= 139 && linha <= 141)){
								printf("%c",219);
							}else{
								textcolor(8);
								printf("%c",219);
								textcolor(5);
							}	
							break;
						//Meio
						case 6:
							if((linha >= 5 && linha <= 17)||(linha >= 19 && linha <= 29)||(linha >= 33 && linha <= 45)||(linha >= 47 && linha <= 57)||(linha >= 61 && linha <= 63)||(linha >= 77 && linha <= 79)||(linha >= 81 && linha <= 93)||(linha >= 100 && linha <= 102)||(linha >= 109 && linha <= 111)||(linha >= 113 && linha <= 115)||(linha >= 123 && linha <= 125)||(linha >= 127 && linha <= 129)||(linha == 134)||(linha >= 139 && linha <= 141)){
								printf("%c",219);
							}else{
								textcolor(8);
								printf("%c",219);
								textcolor(5);
							}	
							break;
						case 7:
							if((linha >= 5 && linha <= 7)||(linha >= 8 && linha <= 12)||(linha >= 19 && linha <= 21)||(linha >= 33 && linha <= 35)||(linha >= 43 && linha <= 45)||(linha >= 47 && linha <= 49)||(linha >= 61 && linha <= 63)||(linha >= 77 && linha <= 79)||(linha >= 81 && linha <= 83)||(linha >= 100 && linha <= 102)||(linha >= 109 && linha <= 111)||(linha >= 113 && linha <= 115)||(linha >= 123 && linha <= 125)||(linha >= 127 && linha <= 129)||(linha == 135)||(linha >= 139 && linha <= 141)){
								printf("%c",219);
							}else{
								textcolor(8);
								printf("%c",219);
								textcolor(5);
							}	
							break;
						case 8:
							if((linha >= 5 && linha <= 7)||(linha >= 12 && linha <= 14)||(linha >= 19 && linha <= 21)||(linha >= 33 && linha <= 35)||(linha >= 43 && linha <= 45)||(linha >= 47 && linha <= 49)||(linha >= 61 && linha <= 63)||(linha >= 77 && linha <= 79)||(linha >= 81 && linha <= 83)||(linha >= 100 && linha <= 102)||(linha >= 109 && linha <= 111)||(linha >= 113 && linha <= 115)||(linha >= 123 && linha <= 125)||(linha >= 127 && linha <= 129)||(linha == 136)||(linha >= 139 && linha <= 141)){
								printf("%c",219);
							}else{
								textcolor(8);
								printf("%c",219);
								textcolor(5);
							}	
							break;
						case 9:
							if((linha >= 5 && linha <= 7)||(linha >= 14 && linha <= 16)||(linha >= 19 && linha <= 21)||(linha >= 33 && linha <= 35)||(linha >= 43 && linha <= 45)||(linha >= 47 && linha <= 49)||(linha >= 61 && linha <= 63)||(linha >= 77 && linha <= 79)||(linha >= 81 && linha <= 83)||(linha >= 100 && linha <= 102)||(linha >= 109 && linha <= 111)||(linha >= 113 && linha <= 115)||(linha >= 123 && linha <= 125)||(linha >= 127 && linha <= 129)||(linha == 137)||(linha >= 139 && linha <= 141)){
								printf("%c",219);
							}else{
								textcolor(8);
								printf("%c",219);
								textcolor(5);
							}	
							break;
						case 10:
							if((linha >= 5 && linha <= 7)||(linha >= 15 && linha <= 17)||(linha >= 19 && linha <= 31)||(linha >= 33 && linha <= 45)||(linha >= 47 && linha <= 59)||(linha >= 61 && linha <= 63)||(linha >= 77 && linha <= 79)||(linha >= 81 && linha <= 83)||(linha >= 100 && linha <= 102)||(linha >= 109 && linha <= 111)||(linha >= 113 && linha <= 125)||(linha >= 127 && linha <= 129)||(linha == 138)||(linha >= 139 && linha <= 141)){
								printf("%c",219);
							}else{								
								textcolor(8);
								printf("%c",219);
								textcolor(5);
							}
							break;													  			   	
					}
					textbackground(0);
				}
				else{
					textcolor(8);
					printf("%c",219);
					textcolor(5);
				}
			}
		}
		if(coluna == 13){
			textcolor(5);
			printf("%c",219);						
		}
			textcolor(7); 
			textbackground(0);
			printf("\n");		
		}
	}
	
void sit0(){
    system("cls");
    logo();
    gotoxy(70,20);
    printf("   ");
    textbackground(WHITE);
    textcolor(BLACK);
    printf("START GAME!\n\n");
    gotoxy(70,22);
    textbackground(BLACK);
    textcolor(WHITE);
    printf("     ");
    printf("HELP!\n\n");
    gotoxy(70,24);
    printf("     ");
    printf("EXIT!\n\n");
    return;
}
void sit1(){
	system("cls");
	logo();
	gotoxy(70,20);
    printf("   ");
    printf("START GAME!\n\n");
    gotoxy(70,22);
    printf("     ");
    textbackground(WHITE);
    textcolor(BLACK);
    printf("HELP!\n\n");
    gotoxy(70,24);
    textbackground(BLACK);
    textcolor(WHITE);
    printf("     ");
    printf("EXIT!\n\n");
    return;
}
void sit2(){
	system("cls");
	logo();
	gotoxy(70,20);
    printf("   ");
    printf("START GAME!\n\n");
    gotoxy(70,22);
    printf("     ");
    printf("HELP!\n\n");
    gotoxy(70,24);
    printf("     ");
    textbackground(WHITE);
    textcolor(BLACK);
    printf("EXIT!\n\n");
    textbackground(BLACK);
    textcolor(WHITE);
    return;
}

void imprime_player(){//imprime as informações atuais do player
	int i, j, prot_total=0, helmet=0, chest=0, legs=0, boots=0, n=0;
	char set;
	for(;;){
		system("cls");
		printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\tSTATUS\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
		printf("NAME: %s\n", character.nome);
		printf("HP: %d\n", character.vida);
		printf("STRENGTH: %d\n", character.forca);
		printf("EFFICIENCY: %d\n\n", character.destreza);
		printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\tPROTECTION\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
		for(i=0; i<15; i++){
			if(character.armor[0]!=0&&character.armor[0]==armor[i].ID){
				prot_total+=armor[i].protecao;
				printf("HELMET: %s\n\tPROTECT: %d%%\n\n", armor[i].nome, armor[i].protecao);
				helmet++;
				break;
			}
		}
		if(helmet==0)
			printf("HELMET: Unequipped\n\n");
		for(i=0; i<15; i++){
			if(character.armor[1]!=0&&character.armor[1]==armor[i].ID){
				prot_total+=armor[i].protecao;
				printf("CHEST: %s\n\tPROTECT: %d%%\n\n", armor[i].nome, armor[i].protecao);
				chest++;
				break;
			}
		}
		if(chest==0)
			printf("CHEST: Unequipped\n\n");
		for(i=0; i<15; i++){
			if(character.armor[2]!=0&&character.armor[2]==armor[i].ID){
				prot_total+=armor[i].protecao;
				printf("LEGS: %s\n\tPROTECT: %d%%\n\n", armor[i].nome, armor[i].protecao);
				legs++;
				break;
			}
		}
		if(legs==0)
			printf("LEGS: Unequipped\n\n");
		for(i=0; i<15; i++){
			if(character.armor[3]!=0&&character.armor[3]==armor[i].ID){
				prot_total+=armor[i].protecao;
				printf("BOOTS: %s\n\tPROTECT: %d%%\n\n", armor[i].nome, armor[i].protecao);
				boots++;
				break;
			}
		}
		if(boots==0)
			printf("BOOTS: Unequipped\n\n");
		if(prot_total!=0)
			printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\tTOTAL PROTECT: %d%%\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n", prot_total);
		printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\tWEAPONS\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
		for(i=0; i<5; i++){
		    if(i==n){
		    	textbackground(WHITE);
		    	textcolor(BLACK);
			}
		    if(character.armas[i]==0)
		        printf("WEAPON %d: Empty\n", i+1); // slot vazio
			else{
		    	for(j=0;j<9;j++){
		    		if(character.armas[i]==armas[j].ID)
		        		printf("WEAPON %d: %s\n", i+1, armas[j].nome);
		       	}
		    }
			if(i==n){
				textbackground(BLACK);
				textcolor(WHITE);
			}
		}
		set=getch();
				if(set==-32){
		            set=getch();
		            if(set==72){
		            	if(n==0){
		            		n=4;
		            		continue;
		            	}
						if(n>0)
							n--;
					}
					if(set==80){
						if(n==4){
		            		n=0;
	    	 				continue;
						}
						if(n<4)
							n++;
					}	
		    	}else{
		    		if(set==27)
		        		return;
		        	else{
		        		if(character.armas[n]==0){
		        			system("cls");
		        			printf("Slot Vazio!");
		        			getch();
						}else{
		        			interage_arma(n, 0);
		        		}
					}
	        	}
	}
}

int interage_arma(int n, int modo){//modo 0 = acesso pela bag, modo 1 = acesso pelo menu de batalha
	int pos, i;
	char set;
	for(i=0; i<9; i++){
		if(character.armas[n]==armas[i].ID){
			pos=i;
			break;
		}
	}
	if(modo==0){
		for(;;){
		system("cls");
		printf("WEAPON: %s\n", armas[pos].nome);
		printf("DAMAGE: %d\n", armas[pos].dano);
		printf("CRITICAL CHANCE: %d%%\n", armas[pos].chance_critico);
		if(character.armas[n]!=2&&character.armas[n]!=3)
		printf("AMMO: %d\n\n", character.municao[n]);
		printf("Deseja descartar essa arma?\n");
		if(i==0){
			textbackground(WHITE);
			textcolor(BLACK);
			printf("SIM!\n");
			textbackground(BLACK);
			textcolor(WHITE);
			printf("NÃO!\n");
		}else{
			printf("SIM!\n");
			textbackground(WHITE);
			textcolor(BLACK);
			printf("NÃO!\n");
			textbackground(BLACK);
			textcolor(WHITE);
		}
		set=getch();
		if(set==-32){
	            set=getch();
	            if(set==72){
	            	if(i==0){
	            		i=1;
	            		continue;
	            	}
					if(i>0)
						i--;
				}
				if(set==80){
					if(i==1){
	            		i=0;
	            		continue;
					}
					if(i<1)
						i++;
				}
	    	}else{
	    		if(set==27)
	        		return;
	        	else{
	        		if(i==0){
	        			character.armas[n]=0;
	        			character.municao[n]=0;
	        			system("cls");
	        			printf("A arma foi removida do seu inventário\n");
	        			getch();
					}
					return;
				}
	        }
		}
	}
	if(modo==1){
		for(;;){
		system("cls");
		printf("WEAPON: %s\n", armas[pos].nome);
		printf("DAMAGE: %d\n", armas[pos].dano);
		printf("CRITICAL CHANCE: %d%%\n", armas[pos].chance_critico);
		if(character.armas[n]!=2&&character.armas[n]!=3)
		printf("AMMO: %d\n\n", character.municao[n]);
		printf("Deseja equipar essa arma?\n");
		if(i==0){
			textbackground(WHITE);
			textcolor(BLACK);
			printf("SIM!\n");
			textbackground(BLACK);
			textcolor(WHITE);
			printf("NÃO!\n");
		}else{
			printf("SIM!\n");
			textbackground(WHITE);
			textcolor(BLACK);
			printf("NÃO!\n");
			textbackground(BLACK);
			textcolor(WHITE);
		}
		set=getch();
		if(set==-32){
	            set=getch();
	            if(set==72){
	            	if(i==0){
	            		i=1;
	            		continue;
	            	}
					if(i>0)
						i--;
				}
				if(set==80){
					if(i==1){
	            		i=0;
	            		continue;
					}
					if(i<1)
						i++;
				}
	    	}else{
	    		if(set==27)
	        		return;
	        	else{
	        		if(i==0)
	        			return n;
					return -1;
				}
	        }
		}
	}
}
//FIM DA SEÇÃO MENU
//SEÇÃO MOCHILA
int cria_mochila(){ // 0 = erro, 1 = sucesso
    int i;
    if((mochila.item=(recurso*)malloc(tamanho_da_mochila*sizeof(recurso)))!=NULL){ // aloca os espacos vazios na mochila.
        mochila.nivel = 1;
        for(i=0; i < tamanho_da_mochila; i++){//inicializa todos os espaços com 0
            mochila.item[i].ID=0;
            mochila.item[i].quantidade=0;
        }
        return 0;
    }
    else
    	exit(1);//se nao for possível alocar memória, da erro;
}

void imprime_mochila(){
    int i, j;
    int n=0;
    char set;
    for(;;){
    	system("cls");
    	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\tITEM E QUANTIDADE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    	for(i=0; i<3; i++){
    		if(i==n){
    			textbackground(WHITE);
    			textcolor(BLACK);
			}
    		if(mochila.item[i].ID==0)
    			printf("Slot %d: Reservado para pots\n", i+1);
    		else{
    			for(j=0;j<3; j++){
    				if(mochila.item[i].ID==potions[j].ID)
    					printf("Slot %d: %s - %d\n", i+1, potions[j].nome, mochila.item[i].quantidade);
				}
			}
			if(i==n){
				textbackground(BLACK);
				textcolor(WHITE);
			}
		}
	    for(i=3; i <tamanho_da_mochila; i++){
	    	if(i==n){
	    		textbackground(WHITE);
	    		textcolor(BLACK);
			}
	        if(mochila.item[i].ID == 0)
	            printf("Slot %d: Vazio\n", i+1); // slot vazio
	        else{
	        	for(j=0;j<17;j++){
	        		if(mochila.item[i].ID==itens[j].ID)
	            		printf("Slot %d: %s - %d\n", i+1, itens[j].nome, mochila.item[i].quantidade);
	            }
	        }
	        if(i==n){
				textbackground(BLACK);
				textcolor(WHITE);
			}
	    }
			set=getch();
			if(set==-32){
	            set=getch();
	            if(set==72){
	            	if(n==0){
	            		n=tamanho_da_mochila-1;
	            		continue;
	            	}
					if(n>0)
						n--;
				}
				if(set==80){
					if(n==tamanho_da_mochila-1){
	            		n=0;
	            		continue;
					}
					if(n<tamanho_da_mochila-1)
						n++;
				}
	    	}else{
	    		if(set==27)
	        		return;
	        	else{
	        		if(mochila.item[n].ID==0&&mochila.item[n].quantidade==0){
	        			system("cls");
	        			printf("Slot Vazio!\n");
	        			getch();
					}else
	        			interage_item(n);
				}
        	}
	}
}

void interage_item(int n){
	int pos, i;
	if(n<3){
		for(i=0;i<3; i++){
			if(mochila.item[n].ID==potions[i].ID){
				pos=i;
				break;
			}
		}
		interage_pot(pos, n);
	}
	if(n>=3){
		for(i=0;i<17; i++){
			if(mochila.item[n].ID==itens[i].ID){
				pos=i;
				break;
			}
		}
		interage_rec(pos, n);
	}
}

void interage_rec(int pos, int n){
	char set;
	int i=0, quant;
	for(;;){
		system("cls");
		printf("Deseja remover %s da mochila?\n", itens[pos].nome);
		if(i==0){
			textbackground(WHITE);
			textcolor(BLACK);
			printf("SIM!\n");
			textbackground(BLACK);
			textcolor(WHITE);
			printf("NÃO!\n");
		}else{
			printf("SIM!\n");
			textbackground(WHITE);
			textcolor(BLACK);
			printf("NÃO!\n");
			textbackground(BLACK);
			textcolor(WHITE);
		}
		set=getch();
		if(set==-32){
	            set=getch();
	            if(set==72){
	            	if(i==0){
	            		i=1;
	            		continue;
	            	}
					if(i>0)
						i--;
				}
				if(set==80){
					if(i==1){
	            		i=0;
	            		continue;
					}
					if(i<1)
						i++;
				}
	    	}else{
	    		if(set==27)
	        		return;
	        	else{
	        		if(i==0){
	        			printf("Informe a quantidade de %s que deseja remover: ", itens[pos].nome);
	        			scanf("%d", &quant);
	        			if(quant>=mochila.item[n].quantidade){
	        				remove_da_mochila(mochila.item[n].ID, mochila.item[n].quantidade);
	        				system("cls");
	        				printf("Voce removeu todos %s da sua mochila.\n", itens[pos].nome);
	        				getch();
	        			}else{
	        				if(quant==0)
	        					return;
	        				remove_da_mochila(mochila.item[n].ID, quant);
	        				system("cls");
	        				printf("Voce removeu %d %s da sua mochila.\n", quant, itens[pos].nome);
	        				getch();
						}
					}
					return;
				}
        	}
	}
}

void interage_pot(int pos, int n){
	char set;
	int i=0, hp;
	for(;;){
		system("cls");
		printf("Beber %s?\n", potions[pos].nome);
		if(i==0){
			textbackground(WHITE);
			textcolor(BLACK);
			printf("SIM!\n");
			textbackground(BLACK);
			textcolor(WHITE);
			printf("NÃO!\n");
		}else{
			printf("SIM!\n");
			textbackground(WHITE);
			textcolor(BLACK);
			printf("NÃO!\n");
			textbackground(BLACK);
			textcolor(WHITE);
		}
		set=getch();
		if(set==-32){
	            set=getch();
	            if(set==72){
	            	if(i==0){
	            		i=1;
	            		continue;
	            	}
					if(i>0)
						i--;
				}
				if(set==80){
					if(i==1){
	            		i=0;
	            		continue;
					}
					if(i<1)
						i++;
				}
	    	}else{
	    		if(set==27)
	        		return;
	        	else{
	        		if(i==0){
	        			if(character.vida+potions[pos].cura<=character.vida_max){
	        				character.vida+=potions[pos].cura;
	        				mochila.item[n].quantidade--;
	        				if(mochila.item[n].quantidade==0)
	        					mochila.item[n].ID=0;
	        				system("cls");
	        				printf("Você bebeu uma %s e se curou em %d HP\n", potions[pos].nome, potions[pos].cura);
	        				getch();
	        				if(comb!=0){
								defende(comb-1);
							}
	        			}else{
	        				if(character.vida_max-character.vida>0){
	        					hp=character.vida_max-character.vida;
	        					character.vida+=hp;
								mochila.item[n].quantidade--;
								if(mochila.item[n].quantidade==0)
									mochila.item[n].ID=0;
								system("cls");
								printf("Voce bebeu uma %s e se curou em %d HP", potions[pos].nome, hp);
								getch();
								if(comb!=0){
									defende(comb-1);
								}
							}else{
								system("cls");
								printf("Seu HP ja esta cheio.\n");
								getch();
							}
						}
						return;
					}
					else
						return;
				}
        	}
	}
}

int aumenta_mochila(){ // 0 = erro, 1 = sucesso
    int i, aux;
    if(tamanho_da_mochila<20&&mochila.nivel<3){
    	aux = tamanho_da_mochila;
    	tamanho_da_mochila+=5;
    	if((mochila.item=(recurso*)realloc(mochila.item,tamanho_da_mochila*sizeof(recurso)))!=NULL){ // realoca a mochila para 15 e 20 espacos (ou mais).
        	mochila.nivel++;
        	for(i=aux; i < tamanho_da_mochila; i++)
            	mochila.item[i].ID = 0;
        	return 1;
    	}
    	else
        	return 0;
	}else{
		printf("Sua mochila já está no nivel máximo!\n");
		return 1;
	}
}

void por_na_mochila(int ID, int quant, int setor){//ID é a ID do item que vai ser colocado na mochila, quant é a quantidade que vai ser colocada na mochila
	int pos=-1, i, j;
	switch(setor){//cada tipo de item é armazenado num lugar diferente, os setores servem pra organizar isso
	    case 1:	//se setor for 1, então é uma compra de arma, ou seja, é armazenado no vetor character.armas[], e não na mochila
	    	for(i=0; i<5; i++){
	    		if(character.armas[i]==0){
	    			character.armas[i]=ID;
	    			break;
				}
			}
			break;
		case 2://parte do Yuji, se for 2, então é uma armadura, deve ser armazenado no vetor character.armor, só tem um problema, tem que te ligar numa coisa
				//o capacete fica no character armor[0], o peitoral no character.armor[1], as calças no character.armor[2] e botas ficam no character.armor[3]
			if(ID>=12&&ID<=15)
				character.armor[0]=ID;
			if(ID>=1&&ID<=3)
				character.armor[1]=ID;
			if(ID==10||ID==11)
				character.armor[2]=ID;
			if(ID>=4&&ID<=9)
				character.armor[3]=ID;
			break;
		case 3://se for 3 são poções, ai tu tem que armazenar as poções NOS PRIMEIROS 3 SLOTS DA MOCHILA, o resto da mochila é feita pra recursos
		//tem que ver se ja existe esse tipo de poção, se não existir poe no primeiro slot vazio DOS PRIMEIROS 3 SLOTS, se existir tu so aumenta a quantidade;
			for(i=0; i<3; i++){
				if(mochila.item[i].ID==ID){
					mochila.item[i].quantidade+=quant;
					system("pause");
					return;
				}
				if(mochila.item[i].ID==0){
					mochila.item[i].ID=ID;
					mochila.item[i].quantidade+=quant;
					return;
				}
			}
			break;
		case 4://cpa essa é a parte mais dificil, tu tem que ver que tipo de munição o player comprou e armazenar no vetor character.municao na mesma posição
		//que a arma que usa aquela munição ta armazenada, por exemplo, se tu tem arco armazenado no vetor character.armas[0], então tu armazena as flechas na
		//character.municao[0], se o player não tiver arma que use esse tipo de munição aí tu impede a compra;
			for(i=0; i<7; i++){
				if(ID==municoes[i].ID){
					for(j=0;j<5;j++){
						if(municoes[i].armaID==character.armas[j]){
							character.municao[j]+=quant;
							break;
						}
					}
					break;
				}
			}
			break;
		case 5://essa parte é do Hyhickle, serve pra colocar os itens dropados dos inimigos dentro da mochila
			for(i=3; i<tamanho_da_mochila; i++){
				if(mochila.item[i].ID==ID){
					pos=i;
					break;
				}
			}
    		if(pos == -1){ // o novo item nao existe na mochila
    	    	for(i=3; i<tamanho_da_mochila; i++){
    	    		if(mochila.item[i].ID==0){
    	    			pos=i;
    	    			break;
					}
				}
				if(pos==-1){
					printf("Hmmm... Não há mais espaço para recursos, um upgrade de mochila agora seria bom\nVoce tambem pode remover algum item sem utilidade no momento\n");
					return;
				}else{
					mochila.item[pos].ID=ID;
					mochila.item[pos].quantidade=quant;
				}
	    	}else{ // se o item existe, apenas aumenta sua quantidade
	        	mochila.item[pos].quantidade+=quant;
	        	return;
	    	}
	    	break;
		default:
			break;
	}
}

void remove_da_mochila(int ID, int quant){//tira o item de troca da mochila
    int i, num_do_slot;
    for(i=3; i<tamanho_da_mochila; i++){//checa se o item existe
    	if(mochila.item[i].ID==ID){
    		num_do_slot=i;
    		break;
    	}
	}
    if(mochila.item[num_do_slot].quantidade==0){ // checa se eh um slot vazio
        printf("\nO item nao existe\n");
        return;
    }else{
        if(mochila.item[num_do_slot].ID==ID&&mochila.item[num_do_slot].quantidade>=quant)// apenas diminui a quantidade do item se ela eh maior que 1
            mochila.item[i].quantidade-=quant;
        for(i=3;i<tamanho_da_mochila;i++){//percorre a mochila procurando pos slots vazios para organiza-la
            if(mochila.item[i].quantidade==0&&i<tamanho_da_mochila-1){
            	mochila.item[i]=mochila.item[i+1];
            	mochila.item[i+1].ID=0;
            	mochila.item[i+1].quantidade=0;
            }
            if(mochila.item[i].quantidade==0&&i==tamanho_da_mochila-1)
           		mochila.item[i].ID=0;
        }
        return;
    }
}

void upgrade_mochila(){//a parte de dar upgrade na mochila eu ja implementei toda, nem te preocupa
	char set;
	int i=0, nitens=0;
	system("cls");
	if(mochila.nivel==1){
		printf("Upgrade mochila nivel 2 - + 5 slots!\n");
		printf("Custo:\n\tCouro x10\n\tCipó x5\n\tPrata x2\n\n");//Couro ID 3, Cipó ID 14, Prata ID 9
		printf("Deseja mesmo adquirir mochila nivel 2? Y/N.\n");
		set=getch();
		if(set=='Y'||set=='y'){
			for(i=2;i<tamanho_da_mochila; i++){
				if(mochila.item[i].ID==3&&mochila.item[i].quantidade>=10)
					nitens++;
			}
			for(i=2;i<tamanho_da_mochila; i++){
				if(mochila.item[i].ID==14&&mochila.item[i].quantidade>=5)
					nitens++;
			}
			for(i=2;i<tamanho_da_mochila; i++){
				if(mochila.item[i].ID==9&&mochila.item[i].quantidade>=2)
					nitens++;
			}
			if(nitens==3){
				remove_da_mochila(3, 10);
				remove_da_mochila(14, 5);
				remove_da_mochila(9,2);
				aumenta_mochila();			
			}else{
				system("cls");
				printf("Voce nao tem os recursos para fazer o upgrade, volte mais tarde!\n");
				getch();
			}
		}
		if(set=='N'||set=='n')
			return;
			
		return;
	}
	if(mochila.nivel==2){
		printf("Upgrade mochila nivel 3 - + 5 slots!\n");
		printf("Custo:\n\tCouro x20\n\tCipó x10\n\tOuro x2\n\n");//Couro ID 3, Cipó ID 14, Ouro ID 8
		printf("Deseja mesmo adquirir mochila nivel 3? Y/N.\n");
		set=getch();
		if(set=='Y'||set=='y'){
			for(i=0;i<tamanho_da_mochila; i++){
				if(mochila.item[i].ID==3&&mochila.item[i].quantidade>=20)
					nitens++;
			}
			for(i=0;i<tamanho_da_mochila; i++){
				if(mochila.item[i].ID==14&&mochila.item[i].quantidade>=10)
					nitens++;
			}
			for(i=0;i<tamanho_da_mochila; i++){
				if(mochila.item[i].ID==8&&mochila.item[i].quantidade>=2)
					nitens++;
			}
			if(nitens==3){
				remove_da_mochila(3, 20);
				remove_da_mochila(14, 10);
				remove_da_mochila(8,2);
				aumenta_mochila();			
			}else{
				system("cls");
				printf("Voce nao tem os recursos para fazer o upgrade, volte mais tarde!\n");
				getch();
			}
		}
		if(set=='N'||set=='n')
			return;
		return;
	}
	if(mochila.nivel==3)
		printf("Sua mochila já está no nivel máximo!\n");
}
//FIM DA SEÇÃO MOCHILA
//SEÇÃO LOJA
void abre_loja(){
	int escolha, compra, quebra=0;
	cria_itens();
    for(;;){
    	escolha=loja();
    	switch(escolha){
    		case 0:
    			system("cls");
    			compra=menu_armas();
    			compra_item(compra, 1);
    			break;
    		case 1:
    			system("cls");
    			compra=menu_armor();
    			compra_item(compra, 2);
    			break;
    		case 2:
    			system("cls");
    			compra=menu_pots();
    			compra_item(compra, 3);
    			break;
    		case 3:
    			system("cls");
    			compra=menu_municao();
    			compra_item(compra, 4);
    			break;
    		case 4:
    			upgrade_mochila();
    			break;
    		case 5:
    			return;
		}
    }
}

int loja(){
    char set;
    static int i;
    for(;;){
        switch(i){
            case 0:
                system("cls");
    			gotoxy(70,20);
    			printf("   ");
    			textbackground(WHITE);
    			textcolor(BLACK);
    			printf("BUY WEAPONS!\n\n");
    			gotoxy(70,22);
    			textbackground(BLACK);
    			textcolor(WHITE);
    			printf("    ");
    			printf("BUY ARMOR!\n\n");
    			gotoxy(70,24);
    			printf("   ");
    			printf("BUY POTIONS!\n\n");
    			gotoxy(70,26);
    			printf("    ");
    			printf("BUY AMMO!\n\n");
    			gotoxy(70, 28);
    			printf(" ");
    			printf("UPGRADE - BACKPACK!\n\n");
				gotoxy(70, 30);
    			printf("   ");
    			printf("EXIT TO GAME!\n\n");	
                break;
            case 1:
                system("cls");
				gotoxy(70,20);
    			printf("   ");
    			printf("BUY WEAPONS!\n\n");
    			gotoxy(70,22);
    			printf("    ");
    			textbackground(WHITE);
    			textcolor(BLACK);
    			printf("BUY ARMOR!\n\n");
    			gotoxy(70,24);
    			textbackground(BLACK);
    			textcolor(WHITE);
    			printf("   ");
    			printf("BUY POTIONS!\n\n");
    			gotoxy(70,26);
    			printf("    ");
    			printf("BUY AMMO!\n\n");
    			gotoxy(70, 28);
    			printf(" ");
    			printf("UPGRADE - BACKPACK!\n\n");
				gotoxy(70, 30);
    			printf("   ");
    			printf("EXIT TO GAME!\n\n");
                break;
            case 2:
                system("cls");
				gotoxy(70,20);
    			printf("   ");
    			printf("BUY WEAPONS!\n\n");
    			gotoxy(70,22);
    			printf("    ");
    			printf("BUY ARMOR!\n\n");
    			gotoxy(70,24);
    			printf("   ");
    			textbackground(WHITE);
    			textcolor(BLACK);
    			printf("BUY POTIONS!\n\n");
    			gotoxy(70,26);
    			textbackground(BLACK);
    			textcolor(WHITE);
    			printf("    ");
    			printf("BUY AMMO!\n\n");
    			gotoxy(70, 28);
    			printf(" ");
    			printf("UPGRADE - BACKPACK!\n\n");
				gotoxy(70, 30);
    			printf("   ");
    			printf("EXIT TO GAME!\n\n");
                break;
            case 3:
                system("cls");
				gotoxy(70,20);
    			printf("   ");
    			printf("BUY WEAPONS!\n\n");
    			gotoxy(70,22);
    			printf("    ");
    			printf("BUY ARMOR!\n\n");
    			gotoxy(70,24);
   				printf("   ");
    			printf("BUY POTIONS!\n\n");
    			gotoxy(70,26);
    			printf("    ");
    			textbackground(WHITE);
    			textcolor(BLACK);
    			printf("BUY AMMO!\n\n");
    			textbackground(BLACK);
    			textcolor(WHITE);
    			gotoxy(70, 28);
    			printf(" ");
    			printf("UPGRADE - BACKPACK!\n\n");
				gotoxy(70, 30);
    			printf("   ");
    			printf("EXIT TO GAME!\n\n");
                break;
            case 4:
            	system("cls");
				gotoxy(70,20);
    			printf("   ");
    			printf("BUY WEAPONS!\n\n");
    			gotoxy(70,22);
    			printf("    ");
    			printf("BUY ARMOR!\n\n");
    			gotoxy(70,24);
    			printf("   ");
    			printf("BUY POTIONS!\n\n");
    			gotoxy(70,26);
    			printf("    ");
    			printf("BUY AMMO!\n\n");
    			gotoxy(70,28);
    			printf(" ");
    			textbackground(WHITE);
    			textcolor(BLACK);
    			printf("UPGRADE - BACKPACK!\n\n");
    			textbackground(BLACK);
    			textcolor(WHITE);
    			gotoxy(70, 30);
    			printf("   ");
    			printf("EXIT TO GAME!\n\n");
            	break;
            case 5:
            	system("cls");
				gotoxy(70,20);
    			printf("   ");
    			printf("BUY WEAPONS!\n\n");
    			gotoxy(70,22);
    			printf("    ");
    			printf("BUY ARMOR!\n\n");
    			gotoxy(70,24);
    			printf("   ");
    			printf("BUY POTIONS!\n\n");
    			gotoxy(70,26);
    			printf("    ");
    			printf("BUY AMMO!\n\n");
    			gotoxy(70,28);
    			printf(" ");
    			printf("UPGRADE - BACKPACK!\n\n");
    			gotoxy(70, 30);
    			printf("   ");
    			textbackground(WHITE);
    			textcolor(BLACK);
    			printf("EXIT TO GAME!\n\n");
    			textbackground(BLACK);
    			textcolor(WHITE);
            	break;
        }
        set=getch();
        if(set==-32){
            set=getch();
            if(set==72&&i>0)
                i--;
            if(set==80&&i<5)
                i++;
    	}else{
        	return i;
        }
    }
}

void compra_item(int pos, int setor){
	int i, j, vaga=-1, nitens=0;
	system("cls");
	switch(setor){
		case 1://setor de armas, se a variável de controle "setor" for 1, significa que o cliente quer comprar armas
			for(i=0; i<5; i++){
				if(character.armas[i]==armas[pos].ID){
					printf("Voce ja possui essa arma, nao pode comprar novamente");
					getch();
					return;
				}
				if(character.armas[i]==0){
					vaga=i;
					break;
				}
			}
			if(vaga==-1){
				printf("Voce ja possui 5 armas, descarte alguma para poder obter outra.\n");
				getch();
				return;
			}
			for(i=0;i<5;i++){
				for(j=0;j<17;j++){
					if(armas[pos].receita[i]==itens[j].ID){
						nitens++;
						break;
					}
				}
			}
			for(i=3;i<tamanho_da_mochila; i++){
				for(j=0; j<5; j++){
					if(mochila.item[i].ID==armas[pos].receita[j]&&mochila.item[i].quantidade>=armas[pos].quantidade[j]&&armas[pos].receita[j]!=0){
						nitens--;
						break;
					}
				}
			}
			if(nitens==0){
				for(i=0;i<5;i++){
					for(j=0;j<17;j++){
						if(armas[pos].receita[i]==itens[j].ID){
							remove_da_mochila(armas[pos].receita[i], armas[pos].quantidade[i]);
							break;
						}
					}
				}
				por_na_mochila(armas[pos].ID, 1, setor);
				printf("Parabens, voce adquiriu %s!\n", armas[pos].nome);	
			}else
				printf("Voce nao possui os itens necessarios para obter esse item!\n");
			getch();
			break;
		case 2://setor de armaduras
			for(i=0;i<5;i++){
				for(j=0;j<17;j++){
					if(armor[pos].receita[i]==itens[j].ID){
						nitens++;
						break;
					}
				}
			}
			for(i=0;i<tamanho_da_mochila; i++){
				for(j=0; j<5; j++){
					if(mochila.item[i].ID==armor[pos].receita[j]&&mochila.item[i].quantidade>=armor[pos].quantidade[j]&&armor[pos].receita[j]!=0){
						nitens--;
						break;
					}
				}
			}
			if(nitens==0){
				for(i=0;i<5;i++){
					for(j=0;j<17;j++){
						if(armor[pos].receita[i]==itens[j].ID){
							remove_da_mochila(armor[pos].receita[i], armor[pos].quantidade[i]);
							break;
						}
					}
				}
				por_na_mochila(armor[pos].ID, 1, setor);
				printf("Parabens, voce adquiriu %s!", armor[pos].nome);	
			}else
				printf("Voce não possui os itens necessarios para obter esse item!\n");
			getch();
			break;
		case 3://setor de poções
			for(i=0;i<3; i++){
				if(mochila.item[i].ID==potions[pos].ID||mochila.item[i].ID==0)//procura o espaço pra armazenar a poção, ela existindo na mochila ou não
					vaga=i;
					break;
			}
			for(i=0; i<5; i++){
				for(j=0; j<17; j++){//incrementa nitens toda vez que tiver um item valido armazenado na receita
					if(potions[pos].receita[i]==itens[j].ID){
						nitens++;
						break;
					}
				}
			}
			for(i=3; i<tamanho_da_mochila; i++){
				for(j=0; j<5; j++){//decrementa nitens toda vez que estiver presente na mochila o recurso e a quantidade requisitada para comprar o item
					if(mochila.item[i].ID==potions[pos].receita[j]&&mochila.item[i].quantidade>=potions[pos].quantidade[j]&&potions[pos].receita[j]!=0){
						nitens--;
						break;
					}
				}
			}
			if(nitens==0){//caso nitens seja 0, o player tem todos os recursos necessários para a confecção do item
				for(i=0;i<5;i++){
					for(j=0;j<17;j++){
						if(potions[pos].receita[i]==itens[j].ID){
							remove_da_mochila(potions[pos].receita[i], potions[pos].quantidade[i]);
							break;
						}
					}
				}
				por_na_mochila(potions[pos].ID, 1, setor);
				printf("Parabens, voce adquiriu %s!\n", potions[pos].nome);
			}else
				printf("Voce nao possui os recursos necessarios para obter esse item!\n");
			getch();
			break;
		case 4://setor de munições
			for(i=0;i<5;i++){
				if(municoes[pos].armaID==character.armas[i]){
					vaga=i;
					break;
				}
			}
			if(vaga==-1){
				for(i=0; i<9; i++){
					if(municoes[pos].armaID==armas[i].ID){
							printf("Voce nao tem %s para comprar essa municao.\n", armas[i].nome);
							getch();
							return;	
						}
					}
			}else{
				for(i=0; i<2; i++){
					for(j=0; j<17; j++){//incrementa nitens toda vez que tiver um item valido armazenado na receita
						if(municoes[pos].receita[i]==itens[j].ID){
							nitens++;
							break;
						}
					}
				}
				for(i=3; i<tamanho_da_mochila; i++){
					for(j=0; j<2; j++){//decrementa nitens toda vez que estiver presente na mochila o recurso e a quantidade requisitada para comprar o item
						if(mochila.item[i].ID==municoes[pos].receita[j]&&mochila.item[i].quantidade>=municoes[pos].quantidade[j]&&municoes[pos].receita[j]!=0){
							nitens--;
							break;
						}
					}
				}
				if(nitens==0){//caso nitens seja 0, o player tem todos os recursos necessários para a confecção do item
					for(i=0;i<5;i++){
						for(j=0;j<17;j++){
							if(municoes[pos].receita[i]==itens[j].ID){
								remove_da_mochila(municoes[pos].receita[i], municoes[pos].quantidade[i]);
								break;
							}
						}
					}	
					por_na_mochila(municoes[pos].ID, municoes[pos].quantidade_muni, setor);
					printf("Parabens, voce adquiriu %s!\n", municoes[pos].nome);
				}else
					printf("Voce nao possui os recursos necessarios para obter esse item! %d\n", nitens);
				getch();
			}
			break;
		default:
			break;
	}
}

void mostrar_arma(int i){
	int j, k;
	system("cls");
	printf("=================\n");
	printf("Arma %d: %s\nDano: %d\nChance de acerto critico: %d\n", armas[i].ID, armas[i].nome, armas[i].dano, armas[i].chance_critico);
	printf("\nCusto:\n");
	for(j=0; j<5; j++){
		for(k=0; k<17; k++){
			if(armas[i].receita[j]==itens[k].ID)
				printf("\t%s x%d\n", itens[k].nome, armas[i].quantidade[j]);
		}
	}
	printf("=================\n");
}

int menu_armas(){
    char set;
    static int i;
    for(;;){
    	mostrar_arma(i);
        set=getch();
        if(set==-32){
            set=getch();
            if(set==72&&i>0)
                i--;
            if(set==80&&i<8)
                i++;
    	}else{
        	return i;
        }
    }
}

void mostrar_armor(int i){
	int j, k;
	system("cls");
	printf("=================\n");
	printf("Armor %d: %s\nProtecao: %d\n", armor[i].ID, armor[i].nome, armor[i].protecao);
	printf("\nCusto:\n");
	for(j=0; j<5; j++){
		for(k=0; k<17; k++){
			if(armor[i].receita[j]==itens[k].ID)
				printf("\t%s x%d\n", itens[k].nome, armor[i].quantidade[j]);
			}
		}
	printf("=================\n");
}

int menu_armor(){
    char set;
    static int i;
    for(;;){
    	mostrar_armor(i);
        set=getch();
        if(set==-32){
            set=getch();
            if(set==72&&i>0)
                i--;
            if(set==80&&i<14)
                i++;
    	}else{
        	return i;
        }
    }
}

void mostrar_pots(int i){
	int j, k;
	system("cls");
	printf("=================\n");
	printf("Pot: %s\nID: %d\nCura: %d\n", potions[i].nome, potions[i].ID, potions[i].cura);
	printf("\nCusto:\n");
	for(j=0; j<5; j++){
		for(k=0; k<17; k++){
			if(potions[i].receita[j]==itens[k].ID)
				printf("\t%s x%d\n", itens[k].nome, potions[i].quantidade[j]);
		}
	}
	printf("=================\n");
}

int menu_pots(){
    char set;
    static int i;
    for(;;){
    	mostrar_pots(i);
        set=getch();
        if(set==-32){
            set=getch();
            if(set==72&&i>0)
                i--;
            if(set==80&&i<2)
                i++;
    	}else{
        	return i;
        }
    }
}

void mostrar_municoes(int i){
	int j, k;
	system("cls");
	printf("=================\n");
	printf("AMMO %d: %s\nQuantidade: %d\n",municoes[i].ID, municoes[i].nome, municoes[i].quantidade_muni);
	printf("\nCusto:\n");
	for(j=0; j<2; j++){
		for(k=0; k<17; k++){
			if(municoes[i].receita[j]==itens[k].ID)
				printf("\t%s x%d\n", itens[k].nome, municoes[i].quantidade[j]);
		}
	}
	printf("=================\n");	
}

int menu_municao(){
	char set;
    static int i;
    for(;;){
    	mostrar_municoes(i);
        set=getch();
        if(set==-32){
            set=getch();
            if(set==72&&i>0)
                i--;
            if(set==80&&i<6)
                i++;
    	}else{
        	return i;
        }
    }		
}
//FIM DA SEÇÃO MENU
//SEÇÃO EU NEM SEI MAIS OQ É ISSO
void cria_cenario(){
	int i, j, n, sum, control, rep=0, par=2;
	static int Nchamadas;
	for(i=0; i<ALTURA*3; i++){
		for(j=0; j<LARGURA*3; j++){
			cenario[i][j]=219;
		}
	}
	//INICIO DO CENARIO 1
	if(multx==0 &&multy==0){	//checa em que setor o cenário em questão se localiza
	//ESTRADA
		for(i=(ALTURA*multx)+18; i<(ALTURA*multx)+23; i++){
			for(j=(LARGURA*multy)+57;j<(LARGURA*(multy+1))-2; j++){//posiciona os indicadores i e j para o centro da matriz pra montar a estrada
				switch(i-(ALTURA*multx)){
					case 18:
						if(j%2==0)//usa o resto da divisão pra criar uma sequencia pseudo-aleatória de posições e randomultxzar as pedras da estrada
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 19:
						if(j%3==0)//rt
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 20:
						if(j%4==0)//rt
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 21:
						if(j%5==0)//rt
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 22:
						if(j%6==0||j%4==0)//rt
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
				}
			}
		}
		for(i=(ALTURA*multx)+33; i<(ALTURA*multx)+39; i++){
			for(j=(LARGURA*multy)+25;j<LARGURA*multy+35; j++){//posiciona os indicadores i e j para o centro da matriz pra montar a estrada
				switch(i-(ALTURA*multx)){
					case 33:
						if(j%2==0)//usa o resto da divisão pra criar uma sequencia pseudo-aleatória de posições e randomultxzar as pedras da estrada
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 34:
						if(j%3==0)//rt
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 35:
						if(j%4==0)//rt
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 36:
						if(j%5==0)//rt
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 37:
						if(j%6==0||j%4==0)//rt
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 38:
						if(j%2==0)//usa o resto da divisão pra criar uma sequencia pseudo-aleatória de posições e randomultxzar as pedras da estrada
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
				}
			}
		}
		//ACAMPAMENTO
		for(i=(ALTURA*multx)+34; i<(ALTURA*multx)+36; i++){
			j=LARGURA*multy+22;
			switch(i-(ALTURA*multx)){
				case 34:
					for(control=0;control<15; control++){
						if(control!=1&&control!=2&&control!=4&&control!=5&&control!=7&&control!=8&&control!=9&&control!=12)
							cenario[i][j+control]=22;
					}
					break;
				case 35:
					for(control=2;control<13; control++){
						if(control!=3&&control!=7&&control!=10&&control!=11)
							cenario[i][j+control]=22;
					}
					break;
			}			
		}
		for(i=ALTURA*multx+15;i<ALTURA*multx+26;i++){// 11 iterações de laço nesse laço aqui
			j=ALTURA*multy+57;
			switch(i-ALTURA*multx){
				case 15:
					for(control=0;control<4; control++){
						if(control!=1)
							cenario[i][j+control]=22;
					}	
					break;
				case 16:
					for(control=0;control<4; control++){
						if(control!=2)
							cenario[i][j+control]=22;
					}
					break;
				case 17:
					for(control=0;control<5; control++){
						if(control!=2&&control!=3)
							cenario[i][j+control]=22;
					}
					break;
				case 18:
					for(control=0;control<4; control++)
						cenario[i][j+control]=22;
					break;
				case 19:
					for(control=0; control<5; control++){
						if(control!=3)
							cenario[i][j+control]=22;
					}
					break;
				case 20:
					for(control=0; control<5; control++){
						if(control!=2)
							cenario[i][j+control]=22;
					}
					break;
				case 21:
					for(control=0;control<4; control++)
						cenario[i][j+control]=22;
					break;
				case 22:
					for(control=0;control<3; control++)
						cenario[i][j+control]=22;
					break;
				case 23:
					for(control=0;control<2; control++)
						cenario[i][j+control]=22;
					break;
				case 24:
					for(control=0;control<3; control++){
						if(control!=1)
							cenario[i][j+control]=22;
					}
					break;
				case 25:
					for(control=0;control<5; control++){
						if(control!=1&&control!=2)
							cenario[i][j+control]=22;
					}
					break;
			}
		}
		//ACAMPAMENTO E NAVE
		for(i=ALTURA*multx;i<ALTURA*(multx+1); i++){//percorre o cenario inteiro para montar o acampamento e a nave
			for(j=LARGURA*multy;j<LARGURA*(multy+1); j++){
				//ACAMPAMENTO
				if(i==6&&j==4){//esse if é responsavel pela montagem do "circulo" que forma a área do acampamento
					for(sum=0;sum<28;sum++){
						if(sum==0){//esse é o padrão que eu desenvolvi pra montar o cenário, não rola explicar isso aqui, muita complicação
							for(control=8;control<45;control++)
								cenario[i+sum][j+control]=22;
						}
						if(sum==1){
							for(control=6;control<47;control++)
								cenario[i+sum][j+control]=22;
						}
						if(sum==2||sum==3){	
							for(control=4;control<49;control++)
								cenario[i+sum][j+control]=22;
						}
						if(sum==4||sum==5||sum==6){
							for(control=2;control<51;control++)
								cenario[i+sum][j+control]=22;
						}
						if(sum>=7&&sum<=20){
							for(control=0;control<53;control++)
								cenario[i+sum][j+control]=22;
						}	
						if(sum==21||sum==22||sum==23){
							for(control=2;control<51;control++)
								cenario[i+sum][j+control]=22;
						}
						if(sum==24||sum==25){
							for(control=4;control<49;control++)
								cenario[i+sum][j+control]=22;
						}
						if(sum==26){
							for(control=6;control<47;control++)
								cenario[i+sum][j+control]=22;
						}
						if(sum==27){
							for(control=8;control<45;control++)
								cenario[i+sum][j+control]=22;
						}
					}
				}
				//NAVE
				if(i==6&&j==6){//esse if é responsavel pela montagem da nave
					for(sum=0;sum<10; sum++){
						if(sum==0){
							cenario[i][j+3]=66;
							cenario[i][j+4]=66;
						}
						if(sum==1){
							for(control=2;control<6;control++)
								cenario[i+sum][j+control]=66;
						}
						if(sum>=2&&sum<6){
							for(control=1; control<7; control++)
								cenario[i+sum][j+control]=7;
							for(control=2;control<6; control++){
								cenario[i+control][j+control]=8;
							}
						}
						if(sum==6){
							for(control=1;control<7;control++)
								cenario[i+sum][j+control]=7;
							for(control=2;control<6;control++)
								cenario[i+sum][j+control]=44;
							for(control=3;control<5;control++)
								cenario[i+sum][j+control]=8;	
						}	
						if(sum==7||sum==8){
							for(control=0;control<8;control++)
								cenario[i+sum][j+control]=7;
							for(control=1;control<7;control++)
								cenario[i+sum][j+control]=44;
							for(control=2;control<6;control++)
								cenario[i+sum][j+control]=7;
						}
						if(sum==9){
							cenario[i+sum][j]=7;
							cenario[i+sum][j+7]=7;
							for(control=2;control<6;control++){
								cenario[i+sum][j+control]=44;
							}
						}							
					}	
				}
			}
		}
		for(i=ALTURA*multx;i<ALTURA*(multx+1);i++){
			if(rep==3)
				n=42;
			else
				n=57;
			if(i==(ALTURA*multx)+2||i==(ALTURA*multx)+8||i==(ALTURA*multx)+24||i==(ALTURA*multx)+30){
				rep++;
				for(j=LARGURA*multy+n;j<LARGURA*(multy+1);j++){			
					if(j%9==0){			
						if(par%2==0){			
							i+=3;
						}else{
							i-=3;
						}
						for(sum=0; sum<5; sum++){
							switch(sum){	
								case 0:		
									if(j+2<LARGURA*(multy+1)-3)
										cenario[i+sum][j+2]=1;
									break;
								case 1:
									for(control=1;control<=3;control++){
										if(j+control<LARGURA*(multy+1)-3)
											cenario[i+sum][j+control]=1;
									}	
									break;
								case 2:
									for(control=0;control<=4;control++){
										if(j+control<LARGURA*(multy+1)-3)
											cenario[i+sum][j+control]=1;
									}
									break;
								case 3:
									for(control=-1;control<=5; control++){
										if(j+control<LARGURA*(multy+1)-3)
											cenario[i+sum][j+control]=1;
									}
									break;
								case 4:
									if(j+2<LARGURA*(multy+1)-3)
										cenario[i+sum][j+2]=2;
									break;
							}
						}
					par++;
					}
				}
			}
		}
	}
	//FIM DO CENARIO 1
	//INICIO DO CENARIO 2
	if(multx==0&&multy==1){
		for(i=ALTURA*multx;i<ALTURA*(multx+1);i++){		
			if(i==(ALTURA*multx)+2||i==(ALTURA*multx)+8||i==(ALTURA*multx)+24||i==(ALTURA*multx)+30){		
				for(j=LARGURA*multy;j<LARGURA*(multy+1);j++){			
					if(j%9==0){			
						if(par%2==0)			
							i+=3;
						else
							i-=3;
						for(sum=0; sum<5; sum++){
							switch(sum){	
								case 0:		
									if(j+2<LARGURA*(multy+1)-3)
										cenario[i+sum][j+2]=1;
									break;
								case 1:
									for(control=1;control<=3;control++){
										if(j+control<LARGURA*(multy+1)-3)
											cenario[i+sum][j+control]=1;
									}	
									break;
								case 2:
									for(control=0;control<=4;control++){
										if(j+control<LARGURA*(multy+1)-3)
											cenario[i+sum][j+control]=1;
									}
									break;
								case 3:
									for(control=-1;control<=5; control++){
										if(j+control<LARGURA*(multy+1)-3)
											cenario[i+sum][j+control]=1;
									}
									break;
								case 4:
									if(j+2<LARGURA*(multy+1)-3)
										cenario[i+sum][j+2]=2;
									break;
							}
						}
					par++;
					}
				}
			}
		}
		for(i=(ALTURA*multx)+18; i<(ALTURA*multx)+23; i++){
			for(j=(LARGURA*multy)+2;j<(LARGURA*(multy+1))-2; j++){
				switch(i-(ALTURA*multx)){
					case 18:
						if(j%2==0)
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 19:
						if(j%3==0)
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 20:
						if(j%4==0)
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 21:
						if(j%5==0)
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 22:
						if(j%6==0||j%4==0)
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
				}
			}
		}
	}
	//FIM DO CENARIO 2
	//INICIO DO CENARIO 3
	if(multx==0&&multy==2){
		for(i=(ALTURA*multx)+18; i<(ALTURA*multx)+23; i++){
			for(j=(LARGURA*multy)+2;j<(LARGURA*(multy+1))-2; j++){
				switch(i-(ALTURA*multx)){
					case 18:
						if(j%2==0)
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 19:
						if(j%3==0)
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 20:
						if(j%4==0)
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 21:
						if(j%5==0)
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
					case 22:
						if(j%6==0||j%4==0)
							cenario[i][j]=4;
						else
							cenario[i][j]=5;
						break;
				}
			}
		}
	}	
	cria_matriz_block();
	cria_interacoes();
	for(i=0;i<ALTURA*3;i++){
		for(j=0;j<LARGURA*3;j++){
			if(map_interact[i][j]!='\0'){
				cenario[i][j]=map_interact[i][j];
			}
		}
	}
}

void cria_interacoes(){
	int a, b, i, j, count=0;
	static int n=0, mx , my;
	srand(time(NULL));
	if(n==0||mx!=multx||my!=multy){
		for(a=ALTURA*multx; a<ALTURA*(multx+1); a++){
			for(b=LARGURA*multy; b<LARGURA*(multy+1); b++){
				map_interact[a][b]='\0';
			}
		}
		map_interact[7][32]=9;
		map_interact[7][33]=9;
		for(;;){
			if(multx==0&&multy==0){
				a=rand()%(ALTURA*(multx+1)-4);
				b=rand()%(LARGURA*(multy+1)-8);
				if(a>(ALTURA*multx)+2&&b>(LARGURA*multy)+60&&count<=4){
					if(block[a][b]!=1&&block[a][b+1]!=1){
						map_interact[a][b]=6;
						map_interact[a][b+1]=6;
						count++;
					}
				}
				if(count==5)
					break;
			}else{
				a=rand()%(ALTURA*(multx+1)-4);
				b=rand()%(LARGURA*(multy+1)-8);
				if(a>(ALTURA*multx)+2&&b>(LARGURA*multy)+4&&count<=4){
					if(block[a][b]!=1&&block[a][b+1]!=1){
						map_interact[a][b]=6;
						map_interact[a][b+1]=6;
						count++;
					}
				}
				if(count==5)
					break;
			}
		}
	}
	mx=multx;
	my=multy;
	n++;
}	

int checa_interacoes(){
	int i, j;
	srand(time(NULL));
	if(rand()%100<5&&block[x][y]!=2){
		if(combate()==-1)
			return -1;
	}
	for(i=0; i<3; i++){
		for(j=0; j<6; j++){
			if(map_interact[x+i][y+j]==6||map_interact[x+i][y-j]==6||map_interact[x-i][y+j]==6||map_interact[x-i][y-j]==6){
				if(combate()==-1)
					return -1;//retorna -1 para as funções que chamaram essa função, para resetar o save, o player está morto
				else{
					map_interact[x+i][y+j]='\0';//apaga qualquer inimigo que esteja no raio de detecção do player caso ele fuja ou mate o inimigo
					map_interact[x+i][y+j-1]='\0';
					map_interact[x+i][y+j+1]='\0';
					map_interact[x+i][y-j]='\0';
					map_interact[x+i][y-j+1]='\0';
					map_interact[x+i][y-j-1]='\0';
					map_interact[x-i][y+j]='\0';
					map_interact[x-i][y+j+1]='\0';
					map_interact[x-i][y+j-1]='\0';
					map_interact[x-i][y-j]='\0';
					map_interact[x-i][y-j+1]='\0';
					map_interact[x-i][y-j-1]='\0';
					return;
				}
			}
		}
	}
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(map_interact[x+i][y+j]==9||map_interact[x+i][y-j]==9||map_interact[x-i][y+j]==9||map_interact[x-i][y-j]==9){
				system("cls");
				abre_loja();
				return;
			}
		}
	}
}
	
void imprime_cenario(){
	int i, j;
	for(i=(ALTURA*multx); i<(ALTURA*(multx+1)); i++){
		for(j=(LARGURA*multy); j<(LARGURA*(multy+1)); j++){
			if(i==(ALTURA*multx)|i==(ALTURA*(multx+1))-1||j==(LARGURA*multy)||j==(LARGURA*multy)+1||j==(LARGURA*(multy+1))-2||j==(LARGURA*(multy+1))-1){
				textcolor(WHITE);
				printf("%c", cenario[i][j]);
				textcolor(GREEN);
			}else{
				switch(cenario[i][j]){
					case 1:
						textcolor(LIGHTGREEN);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;
					case 2:
						textcolor(BROWN);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;
					case 3:
						textcolor(YELLOW);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;
					case 4:
						textcolor(DARKGRAY);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;
					case 5:
						textcolor(LIGHTGRAY);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;
					case 6:
						textcolor(RED);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;
					case 7:
						textcolor(WHITE);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;
					case 8:
						textcolor(LIGHTBLUE);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;
					case 9:
						textcolor(MAGENTA);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;	
					case 22:
						textcolor(BROWN);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;
					case 44:
						textcolor(DARKGRAY);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;
					case 66:
						textcolor(RED);
						cenario[i][j]=219;
						printf("%c", cenario[i][j]);
						textcolor(GREEN);
						break;
					default:
						printf("%c", cenario[i][j]);
						break;
				}
			}
		}
		printf("\n");
	}
	printf("\n");
	textbackground(RED);
	textcolor(WHITE);
	printf("\t|-CONTROLES-| ");
	printf("|W - move pra cima| ");
	printf("|A - move pra esquerda| ");
	printf("|S - move pra baixo| ");
	printf("|D - move pra direita| ");
	printf("|ESC - pause|");
	textcolor(WHITE);
	textbackground(BLACK);
	return;
}

void cria_matriz_block(){
	int i, j;
	for(i=0; i<ALTURA*3; i++){
		for(j=0; j<LARGURA*3; j++){
			if(cenario[i][j]==1||cenario[i][j]==2||cenario[i][j]==7||cenario[i][j]==8||cenario[i][j]==44||cenario[i][j]==66){
				block[i][j]=1;
			}else{
				if(cenario[i][j]==22){
					block[i][j]=2;
				}
				else{
					block[i][j]=0;
				}
			}
		}
	}
}

void person(){
	if(block[x][y]!=1){
		cenario[x][y]=3;
	}
	if(block[x][y+1]!=1){
		cenario[x][y+1]=3;
	}
}

void pause(){
	char set;
    static int i;
    for(;;){
        switch(i){
            case 0:
                system("cls");
    			gotoxy(70,20);
    			printf(" ");
    			textbackground(WHITE);
    			textcolor(BLACK);
    			printf("BACK TO GAME!\n\n");
    			gotoxy(70,22);
    			textbackground(BLACK);
    			textcolor(WHITE);
    			printf("     ");
    			printf("HELP!\n\n");
    			gotoxy(70,24);
   				printf("     ");
    			printf("EXIT!\n\n");
                break;
            case 1:
                system("cls");
    			gotoxy(70,20);
    			printf(" ");
    			printf("BACK TO GAME!\n\n");
    			gotoxy(70,22);
    			printf("     ");
    			textbackground(WHITE);
    			textcolor(BLACK);
    			printf("HELP!\n\n");
    			textbackground(BLACK);
    			textcolor(WHITE);
    			gotoxy(70,24);
   				printf("     ");
    			printf("EXIT!\n\n");
                break;
            case 2:
                system("cls");
    			gotoxy(70,20);
    			printf(" ");
    			printf("BACK TO GAME!\n\n");
    			gotoxy(70,22);
    			printf("     ");
    			printf("HELP!\n\n");
    			gotoxy(70,24);
   				printf("     ");
   				textbackground(WHITE);
    			textcolor(BLACK);
    			printf("EXIT!\n\n");
    			textbackground(BLACK);
    			textcolor(WHITE);
                break;
            default:
                break;
        }
        set=getch();
        if(set==-32){
            set=getch();
            if(set==72&&i>0)
                i--;
            if(set==80&&i<2)
                i++;
    	}else{
        	if(i==0)
        		return;
        	if(i==1){
        		options();
        		return;
        	}
        	if(i==2){
        		save_progress();
        		exit(0);
        	}
        }
    }
}

void move(char set){
	switch(set){
		case'w':
			if(x==(ALTURA*multx)+1&&multx>0){
				multx--;
				x-=2;
			}
			if(x==(ALTURA*multx)+2&&multx>0){
				x--;
			}
			if(x>(ALTURA*multx)+1)
				x-=2;
				break;
		case'W':
			if(x==(ALTURA*multx)+1&&multx>0){
				multx--;
				x-=2;
			}
			if(x==(ALTURA*multx)+2&&multx>0){
				x--;
			}
			if(x>(ALTURA*multx)+1)
				x--;
				break;
		case 's':
			if(x==(ALTURA*multx)+38&&multx<2){
				multx++;
				x+=2;
			}
			if(x==(ALTURA*multx)+37&&multx<2){
				x++;
			}
			if(x<(ALTURA*multx)+38)
				x+=2;
				break;
		case 'S':
			if(x==(ALTURA*multx)+38&&multx<2){
				multx++;
				x+=2;
			}
			if(x==(ALTURA*multx)+37&&multx<2){
				x++;
			}
			if(x<(ALTURA*multx)+38)
				x+=2;
				break;
		case 'a':
			if(y==(LARGURA*multy)+2&&multy>0){
				multy--;
				y-=4;
			}
			if(y>(LARGURA*multy)+2){
				if(y==(LARGURA*multy)+3){
					y--;
				}else{
					y-=3;
				}
			}
			break;
		case 'A':
			if(y==(LARGURA*multy)+2&&multy>0){
				multy--;
				y-=4;
			}
			if(y>(LARGURA*multy)+2){
				if(y==(LARGURA*multy)+3){
					y--;
				}else{
					y-=3;
				}
			}
			break;
		case 'd':
			if(y==(LARGURA*(multy))+141&&multy<2){
				multy++;
				y+=4;
			}
			if(y<(LARGURA*multy)+141){
				if(y==(LARGURA*(multy))+140){
					y++;
				}else{
					y+=3;
				}
			}
			break;
		case 'D':
			if(y==(LARGURA*(multy))+141&&multy<2){
				multy++;
				y+=4;
			}
			if(y<(LARGURA*multy)+141){
				if(y==(LARGURA*(multy))+140){
					y++;
				}else{
					y+=3;
				}
			}
			break;
		case 27:
			pause();
			break;
		case 'Q':
			imprime_player();
			break;
		case 'q':
			imprime_player();
			break;
		case 'E':
			imprime_mochila();
			break;
		case 'e':
			imprime_mochila();
			break;
	}
	return;
}

void start(){
    system("cls");
    FILE *player;
    int i;
    if(((player=fopen("player.bin","rb"))==NULL)&&((player=fopen("player.bin","wb"))!=NULL)){
        gotoxy(70,20);
        printf("Bem vindo ao Redemption.\n ");
        gotoxy(70,21);
        printf("Insira o nickname: ");
        scanf("%[^\n]", character.nome);
        character.vida=200;
        character.vida_max=200;
        character.forca=1;
        character.destreza=1;
        for(i=0; i<4; i++)
            character.armor[i]=0;
        for(i=0; i<5; i++){
            character.armas[i]=0;
            character.municao[i]=0;
        }
        character.armas[0]=2;
        character.municao[0]=-1;
		fwrite(&character.nome, sizeof(character.nome), 1, player);
    	fwrite(&character.vida, sizeof(int), 1, player);
    	fwrite(&character.vida_max, sizeof(int), 1, player);
    	fwrite(&character.forca, sizeof(int), 1, player);
    	fwrite(&character.destreza, sizeof(int), 1, player);
    	for(i=0; i<4; i++)
        	fwrite(&character.armor[i], sizeof(int), 1, player);
    	for(i=0; i<5; i++){
    	    fwrite(&character.armas[i], sizeof(int), 1, player);
    	    fwrite(&character.municao[i], sizeof(int), 1, player);
   		}
    	fwrite(&x, sizeof(int), 1, player);
    	fwrite(&y, sizeof(int), 1, player);
    	fwrite(&multx, sizeof(int), 1, player);
    	fwrite(&multy, sizeof(int), 1, player);
    	fwrite(&tamanho_da_mochila, sizeof(int), 1, player);
    	fwrite(&nivel, sizeof(int), 1, player);
    	fwrite(&inimigos_mortos, sizeof(int), 1, player);
    	fwrite(&mochila.nivel, sizeof(int), 1, player);
    	for(i=0; i < tamanho_da_mochila; i++){
    	    fwrite(&mochila.item[i].ID, sizeof(int), 1, player);
    	    fwrite(&mochila.item[i].quantidade, sizeof(int), 1, player);
    	}
        fclose(player);
        load();
    }
    else{
        load();
    }
}

void load(){
    system("cls");
    int i;
    FILE *player;
    if((player=fopen("player.bin","rb"))!=NULL){
        fread(&character.nome, sizeof(character.nome), 1, player);
        fread(&character.vida, sizeof(int), 1, player);
        fread(&character.vida_max, sizeof(int), 1, player);
        fread(&character.forca, sizeof(int), 1, player);
        fread(&character.destreza, sizeof(int), 1, player);
        for(i=0; i<4; i++)
            fread(&character.armor[i], sizeof(int), 1, player);
        for(i=0; i<5; i++){
            fread(&character.armas[i], sizeof(int), 1, player);
            fread(&character.municao[i], sizeof(int), 1, player);
        }
        fread(&x, sizeof(int), 1, player);
        fread(&y, sizeof(int), 1, player);
        fread(&multx, sizeof(int), 1, player);
        fread(&multy, sizeof(int), 1, player);
        fread(&tamanho_da_mochila, sizeof(int), 1, player);
        fread(&nivel, sizeof(int), 1, player);
        fread(&inimigos_mortos, sizeof(int), 1, player);
        fread(&mochila.nivel, sizeof(int), 1, player);
        for(i=0; i < tamanho_da_mochila; i++){
            fread(&mochila.item[i].ID, sizeof(int), 1, player);
            fread(&mochila.item[i].quantidade, sizeof(int), 1, player);
        }
        fclose(player);
        printf("Save ID: %s\n", character.nome);
        Sleep(500);
        if(game()==-1){
            reseta_player();
        }
    }else{
        printf("Nao ha nenhum save disponivel!\n");
        system("pause");
    }
}

void reseta_player(){
	int i;
	character.vida=200;
	character.vida_max=200;
	character.forca=1;
	character.destreza=1;
	for(i=0; i<4; i++)
		character.armor[i]=0;
	for(i=0; i<5; i++){
		character.armas[i]=0;
		character.municao[i]=0;
	}
	character.armas[0]=2;
	character.municao[0]=-1;
	x=20;
	y=20;
	multx=0; 
	multy=0; 
	tamanho_da_mochila=10;
	nivel=0; 
	inimigos_mortos=0;
	mochila.nivel=1;
	for(i=0; i < tamanho_da_mochila; i++){
        mochila.item[i].ID=0;
        mochila.item[i].quantidade=0;
    }
}

int game(){
	char set;
	for(;;){
		system("cls");
		cria_cenario();
		person();
		imprime_cenario();
		set=getch();
		move(set);
		if(checa_interacoes()==-1){
			return -1;
		}
	}
}

void options(){
	printf("Voce entrou no menu options! Funçao ainda nao foi implementada :c\n");
	system("pause");
}

int combate(){
	creatures();
	system("cls");
	int inimigo, vitoria;
	srand(time(NULL));
	inimigo=rand()%100;
	if(nivel<15){
		if(inimigo>=0&&inimigo<=60)//até o nivel 15 as chances de encontrar animais selvagens é de 60%
			inimigo=0;
		if(inimigo>60&&inimigo<=90)//até o nivel 15 as chances de encontrar caçadores selvagens é de 30%
			inimigo=1;
		if(inimigo>90&&inimigo<100)//até o nivel 15 as chances de encontrar terráqueos sobreviventes é de 10%
			inimigo=2;
	}
	if(nivel>15&&nivel<30){
		if(inimigo>=0&&inimigo<=45)//do nivel 15 até o nivel 30 as chances de encontrar animais selvagens é de 45%
			inimigo=0;
		if(inimigo>45&&inimigo<=80)//do nivel 15 até o nivel 30 as chances de encontrar caçadores selvagens é de 35%
			inimigo=1;
		if(inimigo>75&&inimigo<100)//do nivel 15 até o nivel 30 as chances de encontrar terráqueos sobreviventes é de 20%
			inimigo=2;
	}
	if(nivel>30){
		if(inimigo>=0&&inimigo<=33)//depois do nivel 30 as chances de encontrar animais selvagens é de 45%
			inimigo=0;
		if(inimigo>33&&inimigo<=66)//depois do nivel 30 as chances de encontrar caçadores selvagens é de 35%
			inimigo=1;
		if(inimigo>66&&inimigo<100)//depois do nivel 30 as chances de encontrar terráqueos sobreviventes é de 20%
			inimigo=2;
	}
	printf("Voce encontrou um %s!!!\n", danger[inimigo].nome);
	getch();
	comb=inimigo+1;
	vitoria=inicia_luta(inimigo);
	comb=0;
	return vitoria;
}

int inicia_luta(int inimigo){
	system("cls");
	char set;
	int n=0, arma_selecionada=0, vitoria;
	for(;;){
		system("cls");
		printa_sit(arma_selecionada, inimigo);
		printf("\nEscolha o Que Deseja Fazer:\n");
		switch(n){	
			case 0:
				textbackground(WHITE);
				textcolor(BLACK);
				gotoxy(5,9);
				printf("LUTAR"); //Opcao 1
				textbackground(BLACK);
				textcolor(WHITE);
				gotoxy(18,9);
				printf("FUGIR"); //Opcao 2
				gotoxy(5,11);
				printf("ITENS"); //Opcao 3
				gotoxy(18,11);
				printf("ARMAS"); //Opcao 4
				break;
			case 1:
				gotoxy(5,9);
				printf("LUTAR"); //Opcao 1
				textbackground(WHITE);
				textcolor(BLACK);
				gotoxy(18,9);
				printf("FUGIR"); //Opcao 2
				textbackground(BLACK);
				textcolor(WHITE);
				gotoxy(5,11);
				printf("ITENS"); //Opcao 3
				gotoxy(18,11);
				printf("ARMAS"); //Opcao 4
				break;
			case 2:
				gotoxy(5,9);
				printf("LUTAR"); //Opcao 1
				gotoxy(18,9);
				printf("FUGIR"); //Opcao 2
				textbackground(WHITE);
				textcolor(BLACK);
				gotoxy(5,11);
				printf("ITENS"); //Opcao 3
				textbackground(BLACK);
				textcolor(WHITE);
				gotoxy(18,11);
				printf("ARMAS"); //Opcao 4
				break;
			case 3:
				gotoxy(5,9);
				printf("LUTAR"); //Opcao 1
				gotoxy(18,9);
				printf("FUGIR"); //Opcao 2
				gotoxy(5,11);
				printf("ITENS"); //Opcao 3
				textbackground(WHITE);
				textcolor(BLACK);
				gotoxy(18,11);
				printf("ARMAS"); //Opcao 4
				textbackground(BLACK);
				textcolor(WHITE);
				break;
		}
		set=getch();
				if(set==-32){
		            set=getch();
		            if(set==72){
		            	if(n==0){
		            		n=3;
		            		continue;
		            	}
						if(n>0)
							n--;
					}
					if(set==80){
						if(n==3){
		            		n=0;
	    	 				continue;
						}
						if(n<3)
							n++;
					}	
		    	}else{
		    		if(n==0){
		        		vitoria=ataca(arma_selecionada, inimigo);
						if(vitoria==1){
							system("cls");
							printf("Você derrotou %s, parabéns.\n", danger[inimigo].nome);
							getch();
							inimigos_mortos++;
							if(inimigos_mortos%5==0){
								nivel++;
								if(nivel%2==0){
									character.destreza++;
									printf("Parabéns, você subiu de nível e ganhou um ponto de destreza.\n Nivel: %d\n Destreza: %d\n Forca: %d\n", nivel, character.destreza, character.forca);
								}else{
									character.forca++;
									printf("Parabéns, você subiu de nível e ganhou um ponto de forca.\n Nivel: %d\n Destreza: %d\n Forca: %d\n", nivel, character.destreza, character.forca);
								}
								getch();
							}
							dropa_itens(inimigo);
							getch();
							return;
						}
					}
					if(n==1){
						if(fugir(inimigo)==1)
							return;
					}
					if(n==2){
						imprime_mochila();
					}
					if(n==3){
						arma_selecionada=-1;
						arma_selecionada=select_armas();
						if(arma_selecionada!=-1){
							system("cls");
							printf("Arma selecionada com sucesso\n");
							getch();
						}else{
							arma_selecionada=0;//seleciona a primeira arma do inventário caso não equipe nenhuma
						}
					}						
				}
				if(character.vida<=0){
					system("cls");
					printf("Você morreu!\n");
					getch();
					return -1;
				}
	}
}
	
int fugir(int ini){
	system("cls");
	int chance;
	srand(time(NULL));
	chance=rand()%100;
	if((chance>=0)&&(chance<=30)){
		printf("VOCE CONSEGUIU FUGIR!\n");
		getch();
		return 1;
	}
	else{
		printf("VOCE NAO CONSEGUIU FUGIR!\n");
		getch();
		defende(ini);
		return 0;
	}
}

int ataca(int gun, int ini){
	if(character.municao[gun]>0||character.armas[gun]==2||character.armas[gun]==3){//caso a arma tenha municao, ou a arma selecionada seja uma faca ou katana, executa o ataque;
		character.municao[gun]--;
		srand(time(NULL));
		int i, j, pos, crit, dodge, chance_dodge;
		for(i=0; i<9; i++){
			if(character.armas[gun]==armas[i].ID){
				pos=i;
				break;
			}
		}
		if(ini==0)
			chance_dodge=15;
		if(ini==1)
			chance_dodge=20;
		if(ini==2)
			chance_dodge=25;
		dodge=rand()%100;
		if(dodge<=chance_dodge){
			system("cls");
			printf("O inimigo desviou.\n");
			getch();
			defende(ini);
			return 0;
		}
		crit=rand()%100;
		if(crit<=armas[pos].chance_critico){
			system("cls");
			danger[ini].vida-=((armas[pos].dano+character.forca)*2);
			printf("Acerto critico! causou %d dano!\n",((armas[pos].dano+character.forca)*2));
			getch();
		}else{
			system("cls");
			danger[ini].vida-=(armas[pos].dano+character.forca);
			printf("Acertou! causou %d dano!\n",(armas[pos].dano+character.forca));
			getch();
		}
		if(danger[ini].vida<=0)
			return 1;
		else{
			defende(ini);
			return 0;
		}
	}else{
		system("cls");
		printf("Voce esta sem municao\n");
		getch();
	}
}

void defende(int ini){
	int i, j, crit, dodge, chance_dodge, prot_total=0;
	for(i=0; i<4; i++){
		for(j=0; j<16; j++){
			if(character.armor[i]!=0&&character.armor[i]==armor[j].ID){
				prot_total+=armor[j].protecao;
				break;
			}
		}
	}
	if(character.destreza<=5)
			chance_dodge=15;
		if(character.destreza>5&&character.destreza<=10)
			chance_dodge=20;
		if(character.destreza>10&&character.destreza<=15)
			chance_dodge=25;
		dodge=rand()%100;
		if(dodge<=chance_dodge){
			system("cls");
			printf("Voce desviou do ataque.\n");
			getch();
			return;
		}
		crit=rand()%100;
		if(crit<=danger[ini].chance_critico){
			system("cls");
			character.vida-=((danger[ini].dano*2)-(((danger[ini].dano*2)*prot_total)/100));
			printf("O inimigo causou dano critico você perdeu %d pontos de vida.\n",((danger[ini].dano*2)-(((danger[ini].dano*2)*prot_total)/100)));
			getch();
		}else{
			system("cls");
			character.vida-=((danger[ini].dano)-(((danger[ini].dano)*prot_total)/100));
			printf("O inimigo causou %d de dano em voce.\n",((danger[ini].dano)-(((danger[ini].dano)*prot_total)/100)));
			getch();
		}
		return;
}

int select_armas(){
	int i, j, n=0;
	char set;
	for(;;){
		system("cls");
		for(i=0; i<5; i++){
			    if(i==n){
			    	textbackground(WHITE);
			    	textcolor(BLACK);
				}
			    if(character.armas[i]==0)
			        printf("WEAPON %d: Empty\n", i+1); // slot vazio
				else{
			    	for(j=0;j<9;j++){
			    		if(character.armas[i]==armas[j].ID)
			        		printf("WEAPON %d: %s\n", i+1, armas[j].nome);
			       	}
		    	}
				if(i==n){
					textbackground(BLACK);
					textcolor(WHITE);
				}
			}
			set=getch();
					if(set==-32){
			            set=getch();
			            if(set==72){
			            	if(n==0){
			            		n=4;
			            		continue;
			            	}
							if(n>0)
								n--;
						}
						if(set==80){
							if(n==4){
			            		n=0;
	    		 				continue;
							}
							if(n<4)
								n++;
						}	
			    	}else{
			    		if(set==27)
			        		return;
			        	else{
			        		if(character.armas[n]==0){
			        			system("cls");
			        			printf("Slot Vazio!");
			        			getch();
							}else
			        			return interage_arma(n, 1);
						}
	    	    	}
	}		
}

void printa_sit(int gun, int ini){
	int i, pos;
	for(i=0; i<9; i++){
		if(character.armas[gun]==armas[i].ID){
			pos=i;
			break;
		}
	}
	printf("Seus dados:         \t\tDados do Inimigo:\n");
	printf("Arma Equipada: %s   \t\tInimigo: %s\n", armas[pos].nome, danger[ini].nome);
	printf("Dano: %d            \t\tDano: %d\n", armas[pos].dano, danger[ini].dano);
	printf("Chance Critico: %d%%\t\tChance Critico: %d%%\n", armas[pos].chance_critico, danger[ini].chance_critico);
	printf("Vida: %d            \t\tVida: %d\n", character.vida, danger[ini].vida);
	if(armas[pos].ID!=2&&armas[pos].ID!=3){
		printf("AMMO: %d\n", character.municao[gun]);
	}
}

void dropa_itens(int ini){
	int quant, id, i, drop;
	srand(time(NULL));
	printf("O %s dropou:\n", danger[ini].nome);
	for(i=0; i<5; i++){
		id=rand()%20;
		quant=rand()%10;
		quant++;
		if(id<17){
			printf("%s x%d\n", itens[id].nome, quant);
			por_na_mochila(itens[id].ID, quant, 5);
		}else{
			id-=17;
			printf("%s x%d\n", potions[id].nome, quant);
			por_na_mochila(potions[id].ID, quant, 3);
		}
	}
}

void save_progress(){
    FILE *player;
    int i;
    player = fopen("player.bin", "wb");

    fwrite(&character.nome, sizeof(character.nome), 1, player);
    fwrite(&character.vida, sizeof(int), 1, player);
    fwrite(&character.vida_max, sizeof(int), 1, player);
    fwrite(&character.forca, sizeof(int), 1, player);
    fwrite(&character.destreza, sizeof(int), 1, player);
    for(i=0; i<4; i++)
        fwrite(&character.armor[i], sizeof(int), 1, player);
    for(i=0; i<5; i++){
        fwrite(&character.armas[i], sizeof(int), 1, player);
        fwrite(&character.municao[i], sizeof(int), 1, player);
    }
    fwrite(&x, sizeof(int), 1, player);
    fwrite(&y, sizeof(int), 1, player);
    fwrite(&multx, sizeof(int), 1, player);
    fwrite(&multy, sizeof(int), 1, player);
    fwrite(&tamanho_da_mochila, sizeof(int), 1, player);
    fwrite(&nivel, sizeof(int), 1, player);
    fwrite(&inimigos_mortos, sizeof(int), 1, player);
    fwrite(&mochila.nivel, sizeof(int), 1, player);
    for(i=0; i < tamanho_da_mochila; i++){
        fwrite(&mochila.item[i].ID, sizeof(int), 1, player);
        fwrite(&mochila.item[i].quantidade, sizeof(int), 1, player);
    }

    fclose(player);
}
