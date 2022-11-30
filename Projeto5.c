/*
PAULO HENRIQUE ZIEMER DOS SANTOS
ANÁLISE E DESENVOLVIMENTO DE SISTEMAS MÓDULO II
ALGORITMOS E ESTRUTURA DE DADOS - FILAS E PILHAS
*/

//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>

//STRUCTS
typedef struct _no{
	void *e;
	struct _no *prox;
}No;

typedef struct _lista{
	No *primeiro;
	No *ultimo;
	int tamanho;
}Lista;

typedef struct _pessoa{
    Lista* gibis;
    char nome[20];
}Pessoa;

typedef struct _gibi{
    char nome[20];
}Gibis;


// DECLARAÇÃO DE FUNÇÕES
void interface();
Lista* criarLista();

void inserir(Lista *lista, void *novoElemento);
int remover(Lista *lista, int pos);

Gibis* buscarGibi(Lista *lista, int pos);
Pessoa* buscarPessoa(Lista *lista, int pos);

void listarListaGibi(Lista* lista);
void listarListaPessoa(Lista* lista);


void main()
{
    Lista* pessoas = criarLista();
    Lista* gibis = criarLista();
    
    Lista* fila_pessoas = criarLista();
    Lista* pilha_gibis = criarLista();
    
    int id, op = 0;
	char esc;
	
    Pessoa *pessoa;
	Gibis *gibi;

    while (op != -1)
    {
        interface();
        printf("\n--> ");
        scanf("%d", &op);

        switch (op)
        {
            case 1:
			    pessoa = malloc(sizeof(Pessoa));
                puts("Digite o nome da pessoa que deseja adicionar");
			    scanf("%s", pessoa->nome);
			    pessoa->gibis = criarLista();
			    inserir(pessoas, (void*)pessoa);
            break;

            case 2:
                gibi = malloc(sizeof(Gibis));
                puts("Digite o titulo do gibi que deseja adicionar");
			    scanf("%s", gibi->nome);
			    inserir(gibis, (void*)gibi);
            break;

            case 3:
                listarListaPessoa(pessoas);
            break;

            case 4:
                listarListaGibi(gibis);
            break;

            case 5:
                listarListaPessoa(pessoas);
                puts("Digite o ID da pessoa que deseja inserir na fila\n");
			    scanf("%d", &id);
			    inserir(fila_pessoas, buscarPessoa(pessoas, id));
			break;

            case 6:
                listarListaGibi(gibis);
                puts("Digite o ID do gibi que deseja inserir na pilha\n");
			    scanf("%d", &id);
			    inserir(pilha_gibis, buscarGibi(gibis, id));
            break;
            
            case 7:
                listarListaPessoa(fila_pessoas);
            break;

            case 8:
                listarListaGibi(pilha_gibis);
				printf("-- TOPO DA PILHA --\n\n");
            break;
            
            case 9: // inserir(Lista *lista, void *novoElemento);
                inserir(buscarPessoa(fila_pessoas,0)->gibis,buscarGibi(pilha_gibis,(pilha_gibis->tamanho-1)));
			    remover(pilha_gibis, (pilha_gibis->tamanho-1));
                remover(fila_pessoas, 0);
            break;

            case 10:
                listarListaPessoa(pessoas);
		        puts("digite o id da pessoa que deseja visualisar os gibis");
		        scanf("%d", &id);
		        listarListaGibi(buscarPessoa(pessoas,id)->gibis);
            break;
        }
    }
    

}

Lista* criarLista()
{
	Lista *novaLista = (Lista*) malloc(sizeof(Lista));
	novaLista->primeiro = NULL;
	novaLista->ultimo = NULL;
	novaLista->tamanho = 0;
	return novaLista;
}

void inserir(Lista *lista, void *novoElemento)
{
	No *novoNo = (No*) malloc(sizeof(No));
	novoNo->e = novoElemento;
	novoNo->prox = NULL;

	if(lista->tamanho == 0){
		lista->primeiro = novoNo;
		lista->ultimo = novoNo;
		lista->tamanho++;
	}else{
		lista->ultimo->prox = novoNo;
		lista->ultimo = novoNo;
		lista->tamanho++;
	}
}

int remover(Lista *lista, int pos)
{
	if(pos < 0 || pos>= lista->tamanho)
		return -1;
	No *removido;
	if(lista->tamanho == 1 && pos == 0){
		removido = lista->primeiro;
		free(removido);
		lista->primeiro = NULL;
		lista->ultimo = NULL;
		lista->tamanho--;
		return 0;
	}
	if(pos == 0){
		removido = lista->primeiro;
		lista->primeiro = lista->primeiro->prox;
		free(removido);
		lista->tamanho--;
		return 0;
	}
	No *aux = lista->primeiro;
	int i;
	for(i=0; i<pos-1; i++){
		aux = aux->prox;
	}
	aux->prox = aux->prox->prox;
	free(removido);
	if(lista->tamanho-1 == pos){
		lista->ultimo = aux;
	}
	lista->tamanho--;
	return 0;
}

void listarListaPessoa(Lista* lista)
{
    No *aux = lista->primeiro;
    Pessoa *a;
	int id = 0;
    printf("id        dados\n");
    while(aux != NULL){
        a = (Pessoa*) aux->e;
        printf("%d - %s\n",id ,a->nome);
        aux = aux->prox;
		id++;
    }
    printf("\n\n");
}

void listarListaGibi(Lista* lista)
{
    No *aux = lista->primeiro;
    Gibis *a;
	int id = 0;
    printf("id        dados\n");
    while(aux != NULL){
        a = (Gibis*) aux->e;
        printf("%d - %s\n",id ,a->nome);
        aux = aux->prox;
		id++;
    }
    printf("\n\n");
}

Pessoa* buscarPessoa(Lista *lista, int pos)
{
	int i;
	if(pos < 0 || pos>= lista->tamanho)
		return NULL;
	No *aux = lista->primeiro;
	for(i=0; i<pos; i++)
		aux = aux->prox;
	return aux->e;
}

Gibis* buscarGibi(Lista *lista, int pos)
{
	int i;
	if(pos < 0 || pos>= lista->tamanho)
		return NULL;
	No *aux = lista->primeiro;
	for(i=0; i<pos; i++)
		aux = aux->prox;
	return aux->e;
}

void interface()
{
    puts("\n1  - Cadastrar pessoa");
    puts("\n2  - Cadastrar gibi");
    puts("\n3  - Listar pessoas");
    puts("\n4  - Listar gibis");
    puts("\n5  - Inserir pessoa em fila");
    puts("\n6  - Inserir gibi em pilha");
    puts("\n7  - Exibir fila de pessoas");
    puts("\n8  - Exibir pilha de gibis");
    puts("\n9  - Anexar gibi a uma pessoa");
    puts("\n10 - Exibir gibis de uma pessoa");
}