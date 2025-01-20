#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TAM 10000

typedef struct simple {
    float valor;
    struct simple * proximo;
} Simple;

typedef struct no {
    float valor;
    struct no * anterior;
    struct no * proximo;
    struct simple * listaCirc;
} No;



No * initListaDupla () 
{

    No * lista = malloc(sizeof(No));

    lista->anterior = NULL;
    lista->proximo = NULL;
    lista->listaCirc = NULL;

    return lista;

}

Simple * initListaSimples () 
{
    Simple * lista = malloc(sizeof(Simple));

    lista->proximo = NULL;

    return lista;
}

void inserirOrdenadoEmListaSimples(Simple * lista, float valor) 
{
    Simple * novo = malloc(sizeof(Simple));
    if(novo == NULL) {
        printf("Erro ao alocar memoria");
        return;
    }
    novo->valor = valor;
    
    if (lista->proximo == NULL) {
        lista->proximo = novo;
        novo->proximo = novo;
    } //correto
    else {
        if (lista->proximo->valor > novo->valor) {
            // novo nó aponta pro começo da lista
            novo->proximo = lista->proximo;
            // Encontrar o último nó da lista
            Simple *aux = lista->proximo;
            while (aux->proximo != lista->proximo) {
                aux = aux->proximo;
            }
            // O último nó agora aponta para o novo nó
            aux->proximo = novo;
            // O novo nó se torna o primeiro
            lista->proximo = novo;
        } else {
            Simple * aux = lista->proximo; 
            while(aux->proximo != lista->proximo && aux->proximo->valor < novo->valor)
                aux = aux->proximo;
            if (aux->proximo == lista) {
                aux->proximo = novo;
                novo->proximo = lista->proximo;
            } else {
                novo->proximo = aux->proximo;
                aux->proximo = novo;
            }
        }
    }
}

void inserirOrdenadoEmListaDupla(No * lista, float valor) 
{
    No * novo = malloc(sizeof(No));
    if(novo == NULL) {
        printf("Erro ao alocar memoria");
        return; 
    }
    novo->valor = valor;
    novo->listaCirc = initListaSimples();

    if (lista->proximo == NULL) {
        lista->proximo = novo;
        novo->anterior = NULL;
        novo->proximo = NULL;
    } else {
        if (novo->valor < lista->proximo->valor) {
            novo->proximo = lista->proximo;
            novo->anterior = NULL;
            lista->proximo->anterior = novo;
            lista->proximo = novo;
        } else {
            No * aux = lista->proximo;
            while (aux->proximo != NULL && aux->proximo->valor < novo->valor)
                aux = aux->proximo;
            if (aux->proximo != NULL) {
                novo->proximo = aux->proximo;
                aux->proximo->anterior = novo;
                aux->proximo = novo;
                novo->anterior = aux;
            } else {
                aux->proximo = novo;
                novo->anterior = aux;
                novo->proximo = NULL;
            }
        }
    }
}

void imprimirListaDupla (No * lista) 
{
    //printf("Printando...\n");
    No * aux = lista->proximo;
    printf("%.2f <=> ", aux->valor);
    while (aux->proximo != NULL) {
        aux = aux->proximo;
        printf("%.2f <=> ", aux->valor);
    }
}

void contrario (No * lista) 
{
    No * aux = lista->proximo;
    while (aux->proximo != NULL)
        aux = aux->proximo;
    //
    printf("%d <=> ", aux->valor);
    while (aux->anterior != NULL && aux->anterior != lista) {
        aux = aux->anterior;
        printf("%d <=> ", aux->valor);
    } 
}

void imprimirListaSimples(Simple *lista) {
    // Verifica se a lista não está vazia
    if (lista->proximo == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    Simple *aux = lista->proximo;
    // Percorre a lista circular e imprime os valores
    do {
        printf("%d", aux->valor);
        if (aux->proximo != lista->proximo) {
            printf("->");
        }
        aux = aux->proximo;
    } while (aux != lista->proximo);  // Para quando voltar ao primeiro nó

}

float modulo (int valor) {
    if (valor < 0)
        return valor * -1;
    return valor;
}

void fprintfSimples(Simple *lista, FILE * saida) {
    // Verifica se a lista não está vazia
    if (lista->proximo == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    Simple *aux = lista->proximo;
    // Percorre a lista circular e imprime os valores
    do {
        fprintf(saida,"%g", aux->valor);



        if (aux->proximo != lista->proximo) {
            fprintf(saida,"->");
        }
        aux = aux->proximo;
    } while (aux != lista->proximo);  // Para quando voltar ao primeiro nó
}


void removeListaSimples (Simple * lista, float valor) {}


int main () 
{
    system("cls||clear");

    FILE * entrada;
    FILE * saida;

    entrada = fopen("L1Q3.in", "r");
    saida = fopen("L1Q3.out", "w");
    
    Simple * listaSimples = initListaSimples();

    char string[TAM];
    char * chunk;
    char separador[] = " ";
    char sacrifice[TAM];
    int alternador = 1;
    int firstLine = 1;

    while (fgets(string, TAM, entrada))
    {
        No * listaDupla = initListaDupla();
        inserirOrdenadoEmListaDupla(listaDupla, 99);
        chunk = strtok(string, separador);
        while (chunk != NULL)
        {
            if (strcmp(chunk, "LE") == 0) {
                alternador = 1;
            }
            else if (strcmp(chunk, "LI") == 0) {
                alternador = 2;
            } else {
                if (alternador == 1) {
                    printf("%.2g ", atof(chunk));
                    inserirOrdenadoEmListaDupla(listaDupla, atof(chunk));
                }
                else if (alternador == 2) {
                    float num = atof(chunk);

                    No * aux = listaDupla->proximo;

                    while (aux->proximo != NULL)
                    {
                        //printf("Andando\n");
                        float newNum = modulo(num - aux->valor);
                        int existe = 0;
                        if (newNum < 1) {
                            inserirOrdenadoEmListaSimples(aux->listaCirc, num);
                            break;
                        }
                        aux = aux->proximo;
                    }
                }
            }
            chunk = strtok(NULL, separador);
        }
        printf("\n");
        imprimirListaDupla(listaDupla);
        printf("\n");

        if(firstLine) {
            firstLine = 0;
        } else {
            fprintf(saida,"\n");
        }
        fprintf(saida ,"[");
        No * aux = listaDupla->proximo;
        while(aux->proximo != NULL) {
            fprintf(saida, "%g(", aux->valor);
            fprintfSimples(aux->listaCirc, saida);
            fprintf(saida, ")");
            if (aux->proximo->proximo)
                fprintf(saida, "->");
            aux = aux->proximo;
        }
        fprintf(saida,"]");
    }
}