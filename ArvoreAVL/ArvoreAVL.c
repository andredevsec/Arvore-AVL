#include <stdio.h>
#include <stdlib.h>
typedef struct{
	int matricula;
	char nome[40];
}tdado;

typedef struct no{
	int key;
	int fb;
	tdado dado;
	struct no *dir,*esq;
}tno;
//-----------------------
tno *criaNo(int chave, tdado d){
	tno *novo;
	novo = malloc(sizeof(tno));
	novo->key = chave;
	novo->dado = d;
	novo->esq=NULL;
	novo->dir=NULL;
	novo->fb=0;
	//printf("Endereco novo no:%x\n",novo);
	return novo;
}
//----------------------
int altura(tno *r){
	int altEsq,altDir;
	if(r==NULL)
	  return -1;
	altEsq = altura(r->esq);
	altDir = altura(r->dir);
	if(altDir > altEsq)
	  return altDir +1;
	else
	  return altEsq +1;    
}
//-----------------------
tno *rotacaoEsq(tno *raiz){
	tno *nova = raiz->dir;
	raiz->dir = nova->esq;
	nova->esq = raiz;
	nova->fb = 
	    altura(nova->dir)-altura(nova->esq);
	raiz->fb = 
	    altura(raiz->dir) - altura(raiz->esq);
    printf("<--Rotacao esquerda");
	return nova;	    
}
//-----------------------
tno *rotacaoDir(tno *raiz){
	tno *nova = raiz->esq;
	raiz->esq = nova->dir;
	nova->dir = raiz;
	raiz->fb = altura(raiz->dir) - altura(raiz->esq);
	nova->fb = altura(nova->dir) - altura(nova->esq);
	printf("Rotacao direita-->");
	return nova;
}
//------------------------
tno *insere(tno *raiz, tno *novo){
	if(raiz==NULL)
		return novo;
	if(novo->key < raiz->key)
		raiz->esq = insere(raiz->esq, novo);
	else
		raiz->dir = insere(raiz->dir, novo);
	//atualizando o fator de balanceamento
	raiz->fb = altura(raiz->dir) - altura(raiz->esq);
	switch(raiz->fb){
		case -2: if(raiz->esq->fb <=0)
					raiz= rotacaoDir(raiz); //simples para a direita
				else{
					raiz->esq = rotacaoEsq(raiz->esq);
					raiz = rotacaoDir(raiz);
			break;
				}
		case 2: if(raiz->dir->fb >=0)
					raiz= rotacaoEsq(raiz); //simples para a direita
				else{
					raiz->dir = rotacaoDir(raiz->dir);
					raiz = rotacaoEsq(raiz);
					break;
		}
					
	}
	return raiz;
}
//------------------------------
tno *insereComentado(tno *raiz, tno *novo){
	if(raiz == NULL) // caso base
		return novo;
	if(novo->key < raiz->key)	{
	    printf("<<< %d < %d\n",novo->key,raiz->key);
		raiz->esq = insereComentado(raiz->esq, novo);
	}	
	else{
	     printf(" %d > %d >>>\n",novo->key,raiz->key);
		raiz->dir = insereComentado(raiz->dir, novo);
	}
	printf("Retornando o endereco %x de %d\n",raiz, raiz->key);
	return raiz; // devolve a raiz atual		
}
//-----------------------
void preOrder(tno *raiz){
	if(raiz!=NULL){
		printf("%d - ",raiz->key);
		preOrder(raiz->esq);
		preOrder(raiz->dir);
	}
}
//-----------------------
void inOrder(tno *raiz){
	if(raiz!=NULL){
		inOrder(raiz->esq);
		printf("%d - ",raiz->key);
		inOrder(raiz->dir);
	}
}
//-----------------------
void preOrderComentado(tno *raiz){
	if(raiz!=NULL){
		printf("%x |%d[%x] |%x -",raiz->esq, raiz->key,raiz, raiz->dir);
		preOrderComentado(raiz->esq);
		preOrderComentado(raiz->dir);
	}
}
//-----------------------
int busca(tno *raiz, int chave){
	if(raiz==NULL)
	 return 0;
	if(chave == raiz->key)
	 return 1;
	if(chave < raiz->key)
		return busca(raiz->esq, chave);
	else
		return busca(raiz->dir,chave);	  
}
//-----------------------
int buscaComentado(tno *raiz, int chave){
	if(raiz==NULL)
	 return 0;
	
	printf("%d - ",raiz->key); getch(); 
	if(chave == raiz->key)
	 return 1;
	if(chave < raiz->key)
		return buscaComentado(raiz->esq, chave);
	else
		return buscaComentado(raiz->dir,chave);	  
}
//-----------------------
tno *removeNo(tno *r){
	tno *nova,*pai;
	if(r->dir==NULL){
		nova = r->esq;
		free(r);
		return nova;
	}// fim if
	// percorrer até achar o menor da direita
	pai = r; nova = r->dir;
	while(nova->esq!=NULL){
		pai=nova;
		nova = nova->esq;
	}// fim while
	//---------------------
	// reorganizar os ponteiros
	if(pai!=r){
		pai->esq = nova->dir;
		nova->dir = r->dir;
	}
	nova->esq = r->esq;
	// limpar a memoria e retonar a nova raiz
	free(r);
	return nova;
}
//------------------------
tno *buscaRemove(tno *raiz, int chave){
	if(raiz==NULL)
		return NULL;
	if(raiz->key == chave)
		return removeNo(raiz);
	if(chave < raiz->key)
		raiz->esq = buscaRemove(raiz->esq,chave);
	else
	    raiz->dir = buscaRemove(raiz->dir,chave);
	    
		//atualizando o fator de balanceamento
	raiz->fb = altura(raiz->dir) - altura(raiz->esq);
	switch(raiz->fb){
		case -2: if(raiz->esq->fb <=0)
					raiz= rotacaoDir(raiz); //simples para a direita
				else{
					raiz->esq = rotacaoEsq(raiz->esq);
					raiz = rotacaoDir(raiz);
			break;
				}
		case 2: if(raiz->dir->fb >=0)
					raiz= rotacaoEsq(raiz); //simples para a direita
				else{
					raiz->dir = rotacaoDir(raiz->dir);
					raiz = rotacaoEsq(raiz);
					break;
		}
	}
	return raiz;				
}
//------------------------
tno *carrega(tno *raiz){
	FILE *arq;
	int chave;
	tdado dado;
	int i, n;
	arq = fopen("numeros.txt", "r");
	if(arq==NULL){
		printf("Arquivo nao encontrado :(\n");
		return raiz;
	}// fim if
	printf("Qtde de numeros para leitura no arquivo:");
	scanf("%d",&n);
    for(i=0;i<n;i++){
        fscanf(arq,"%d",&chave);
		raiz=insere(raiz,criaNo(chave,dado)); // aqui este dado está sendo inserido com nossa função insere já pronta
	}// fim for
	fclose(arq);
	printf("Dados carregados com sucesso :)\n");
	return raiz; // retornando a raiz atualizada.
}
//------------------------
int menu(){
	int op;
	printf("*** Arvore de Busca Binaria ***\n");
	printf("1-Inserir\n");
	printf("2-Percursos\n");
	printf("3-Busca\n");
	printf("4-Remove\n");
	printf("0-Sair\n");
	scanf("%d",&op);
	return op;
}
//-----------------------
int main(){
	tno *raiz=NULL; // definicao da nossa arvore
	int chave,op;
	tdado dado;
	printf("Carregar dados do arquivo?[1-Sim | 0- Nao]:");
	scanf("%d",&op);
	if(op==1)
		raiz=carrega(raiz);
    do{
    	printf("PreOrder:");
    	preOrder(raiz);
    	printf("\n");
    	op = menu();
    	switch(op){
    		case 1: printf("Chave:");
    				scanf("%d",&chave);
    				//printf("Matricula:");
    				//scanf("%d",&dado.matricula);
    				raiz = insere(raiz,criaNo(chave,dado));
    		 break;
    		case 2: // percursos
    		 break;
    		case 3: printf("Chave de busca:");
    				scanf("%d",&chave);
    				if(buscaComentado(raiz,chave)==1)
    					printf("Chave encontrada\n");
    				else
						printf("Chave inexistente :(\n");	
			 break; 
			case 4:printf("Chave para remocao:");
    			   scanf("%d",&chave); 
			       raiz= buscaRemove(raiz,chave);
				break; 
    		case 0: printf("Saindo...\n");
			 break;
			default: printf("Opcao invalida\n");  
		}//
    	getch();// pausa
    	system("cls");
	}while(op!=0);
	
}
