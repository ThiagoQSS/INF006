#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TAM 10000


typedef struct no {
    int valor;
    struct no * esquerda;
    struct no * direita;
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


int inserirEmArv(Raiz * arv, int valor) //vai retornar a altura
{
    No * novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;

    if (arv->inicio == NULL) {
        arv->inicio = novo;
        return 0;
    }

    No * aux = arv->inicio;
    int keep = 1;
    int altura = 0;
    
    while (1)
    {
        altura++;
        if (valor >= aux->valor) 
        {
            if(aux->direita != NULL) 
                aux = aux->direita;
            else {
                aux->direita = novo;
                return altura;
            }
        } 
        else 
        {
            if(aux->esquerda != NULL) 
                aux = aux->esquerda;
            else {
                aux->esquerda = novo;
                return altura;
            }
        }
    }

}

int buscarMaiorElemento(Raiz * arv) {
    if(arv->inicio == NULL)
        return -1;
    //
    No * aux = arv->inicio;
    while(aux->direita)
        aux = aux->direita;
    //
    return aux->valor;
}

int buscarAlturaDoMaiorElemento(Raiz * arv) {
    if(arv->inicio == NULL)
        return -1;
    //
    No * aux = arv->inicio;
    int altura = 0;
    while(aux->direita) {
        altura++;
        aux = aux->direita;
    }
    //
    return altura;
}

int buscarPredecessorDoMaiorElemento(Raiz * arv) {
    No * aux = arv->inicio;
    No * sacrifice = arv->inicio;
    if(sacrifice->direita)
        sacrifice = sacrifice->direita;
    while(sacrifice->direita) {
        sacrifice = sacrifice->direita;
        aux = aux->direita;
    }
    //
    return aux->valor;
}


int main () 
{
    system("cls||clear");

    FILE * entrada;
    FILE * saida;

    char string[TAM];
    char separador[] = " ";
    char * chunk;

    entrada = fopen("L2Q1.in", "r");
    saida = fopen("L2Q1.out", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir arquivos!");
        return 0;
    }

    int isFirst = 0;
    int max;
    int pred;
    int alt;

    while (fgets(string, TAM, entrada)) {
        Raiz * arvore = initArv();
        isFirst = 1;

        for (int i = 0; i < 1000; i++)
            printf("%c", string[i]);
        //
        chunk = strtok(string, separador);

        while(chunk != NULL) {
            
            if(isFirst) {
                fprintf(saida, "%d", inserirEmArv(arvore, atoi(chunk)));
                isFirst = 0;
            }
            else 
                fprintf(saida, " %d", inserirEmArv(arvore, atoi(chunk)));
            //
            //printf("%d ", atoi(chunk));

            chunk = strtok(NULL, separador);
        }

        alt = buscarAlturaDoMaiorElemento(arvore);
        max = buscarMaiorElemento(arvore);
        pred = buscarPredecessorDoMaiorElemento(arvore);

        fprintf(saida, " max %d", max);
        fprintf(saida, " alt %d", alt);

        if(pred != arvore->inicio->valor)
            fprintf(saida, " pred %d", pred);
        else
            fprintf(saida, " pred NaN");
        //

        //printf("\n");
        fprintf(saida, "\n");
    }
}