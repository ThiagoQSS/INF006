#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TAM 10000

/*

Dupla: Thiago Quadros e Cauã Will

*/

typedef struct no {
    int valor;
    int altura;
    struct no * esquerda;
    struct no * direita;
    struct no * parent;
} No;


typedef struct {
    No * inicio;
} Raiz;


Raiz * initArv() 
{
    Raiz * arv = malloc(sizeof(Raiz));
    arv->inicio = NULL;
    return arv;
}


int inserirEmArv(Raiz * arv, int valor) //vai retornar se ocorreu a inserção
{
    No * novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->parent = NULL;

    if (arv->inicio == NULL) {
        arv->inicio = novo;
        return 1;
    }

    No * aux = arv->inicio;
    int keep = 1;
    int altura = 0;
    
    while (1)
    {
        altura++;
        if (valor > aux->valor) 
        {
            if(aux->direita != NULL) 
                aux = aux->direita;
            else {
                aux->direita = novo;
                novo->parent = aux;
                novo->altura = altura;
                return 1;
            }
        } 
        else if(valor < aux->valor)
        {
            if(aux->esquerda != NULL) 
                aux = aux->esquerda;
            else {
                aux->esquerda = novo;
                novo->parent = aux;
                novo->altura = altura;
                return 1;
            }
        } else
            return 0;
    }
}


No * buscarElemento(Raiz * arv, int valor) 
{
    No * aux = arv->inicio;
    while(aux != NULL) {
        if(valor > aux->valor)
            aux = aux->direita;
        else if (valor < aux->valor)
            aux = aux->esquerda;
        else
            return aux;
    }
    printf("Buscar elemento: Null\n");
    return NULL;
}


No * buscarSucessorimediato(No * elemento, Raiz * arv) 
{
    if(elemento == NULL)
        return NULL;
    No * aux = elemento;
    No * parent;
    if(aux->direita != NULL) {
        aux = aux->direita;
        while (aux->esquerda)
            aux = aux->esquerda;
        return aux;
    } 
    else if (aux->parent != NULL){
        parent = aux->parent;
        while(parent->direita == aux && parent->parent != NULL) {
            aux = parent;
            parent = aux->parent;
        }
        if (parent->valor > aux->valor)
            return parent;
        else
            return NULL;
    }
    else
        return NULL;
}


No * buscarMinimo(Raiz * arv) 
{
    No * aux = arv->inicio;
    while(aux->esquerda)
        aux = aux->esquerda;
    return aux;
}


int somarSubArvore(No * galho) 
{
    if (galho == NULL)
        return 0;
    int valor = galho->valor;
    if (galho->direita == NULL && galho->esquerda == NULL) 
        return valor;
    if (galho->direita == NULL)
        return valor + somarSubArvore(galho->esquerda);
    if (galho->esquerda == NULL)
        return valor + somarSubArvore(galho->direita);
    return valor + somarSubArvore(galho->esquerda) + somarSubArvore(galho->direita);
}


int calcularDiffEsqDir(No * galho) {
    if (galho->direita == NULL && galho->esquerda == NULL) 
        return 0;
    if (galho->esquerda == NULL)
        return somarSubArvore(galho->direita);
    if (galho->direita == NULL)
        return 0 - somarSubArvore(galho->esquerda);
    return somarSubArvore(galho->direita) - somarSubArvore(galho->esquerda);
}


int main() 
{

    system("clear||cls");

    FILE * entrada = fopen("L2Q2.in", "r");
    FILE * saida = fopen("L2Q2.out", "w");

    if(entrada == NULL || saida == NULL) {
        printf("Erro ao abrir Arquivos!!!");
        return 0;
    }

    char string[TAM];
    char separador[] = " ";
    char * chunk;

    int isFirst = 1;
    int inicioLinha = 1;
    
    while (fgets(string, TAM, entrada)) {

        string[strcspn(string, "\n")] = '\0';
        string[strcspn(string, "\r")] = '\0';

        inicioLinha = 1;
        Raiz * arvore = initArv();
        if(!isFirst) 
            fprintf(saida, "\n"); 
        else
            isFirst = 0;
        //

        chunk = strtok(string, separador);

        while (chunk) {
            printf("%d\n", inserirEmArv(arvore, atoi(chunk)));
            printf("<%s>\n", chunk);
            chunk = strtok(NULL, separador);
        }

        No * atual = buscarMinimo(arvore); 
        while (atual != NULL) {
            if(inicioLinha == 1) {
                fprintf(saida, "%d", atual->valor);
                inicioLinha = 0;
            } else {
                fprintf(saida, " %d", atual->valor);
            }
            int somaDif = calcularDiffEsqDir(atual);
            fprintf(saida, " (%d)", somaDif);

            atual = buscarSucessorimediato(atual, arvore);
        }
    }
}
