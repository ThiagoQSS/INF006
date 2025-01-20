#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TAM 1000


typedef struct
{
    int x;
    int y;
    double distanceToOrigin;
} point;

void removePalavra(char string[], char alvo[]);
float distance(point a, point b);
void ordenarPontos(point Pontos[], int qntPontos);

int main () 
{
    system("cls||clear");

    FILE* entrada;
    FILE* saida;
    entrada = fopen("L0Q1.in", "r");
    saida = fopen("L0Q1.out", "w");

    int cont = 0;

    point origin;
    origin.x = 0;
    origin.y = 0;
    origin.distanceToOrigin = 0;
    

    char linhaEntrada[TAM];

    if (entrada == NULL || saida == NULL){
        printf("Arquivos inexistentes.");
        return 0;
    }

    char separador[] = "(,) ";
    char * parte;

    while (fgets(linhaEntrada, TAM, entrada) != NULL) {
        point Pontos[400];
        removePalavra(linhaEntrada, "points ");

        int index = 0;
        float soma = 0;
        float shortcut;

        fprintf(saida, "points");

        //pegar a primeira palavra
        parte = strtok(linhaEntrada, separador);

        while (parte != NULL) 
        {
            if (cont % 2 == 0) 
                Pontos[index].x = atoi(parte);
            else 
            {
                Pontos[index].y = atoi(parte);

                Pontos[index].distanceToOrigin = distance(Pontos[index], origin);

                if (index > 0)
                {
                    soma += distance(Pontos[index], Pontos[index - 1]);

                    shortcut = distance(Pontos[0], Pontos[index]);
                }

                index++;
            }
            cont++;

            //separar os pedaços da linha do File
            parte = strtok(NULL, separador);
        }

        //printf("%d", index);
        ordenarPontos(Pontos, index);

        for (int i = 0; i < index; i++) {
            fprintf(saida, " (%d,%d)", Pontos[i].x, Pontos[i].y);
        }

        fprintf(saida, " distance %.2f", soma);
        fprintf(saida, " shortcut %.2f\n", shortcut);
    }

    fclose(saida);
    fclose(entrada);
}

void removePalavra(char string[], char alvo[]) 
{
    int j, k;
    int achou;
    for (int i = 0; string[i]; i++) {
        if (string[i] == alvo[0]) 
        {
            achou = 1;
            for (j = i, k = 0; alvo[k]; j++, k++)
                if (string[j] != alvo[k])
                    achou = 0;
        }
        if (achou) 
        {
            //printf("%d %d\n\n", i, j);
            while (i <= j)
            {
                for (int l = 0; string[l]; l++)
                {   
                    string[l] = string[l + 1];
                }
                i++;
            }
            break;
        }
    }
}

float distance(point a, point b) 
{
    float xdistance, ydistance;

    xdistance = a.x - b.x;
    ydistance = a.y - b.y;

    return sqrt(pow(xdistance, 2) + pow(ydistance, 2));
}

void ordenarPontos(point Pontos[], int index)
{
    point aux;
    int troca = 1;
    for (int j = 0; troca; j++) 
    {
        troca = 0;
        for (int i = 1; i < index - j; i++) 
        {
            if (Pontos[i - 1].distanceToOrigin > Pontos[i].distanceToOrigin)
            {
                aux = Pontos[i];
                Pontos[i] = Pontos[i - 1];
                Pontos[i - 1] = aux;
                troca = 1;
            }
        }
    }
}