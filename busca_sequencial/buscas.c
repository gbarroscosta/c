//Aluno: Gabriel Barros Costa

#include <stdio.h> 
#include <stdlib.h> // Para usar a função rand()
#include <locale.h>
#include <time.h>
#include <sys/timeb.h> // Calcular a diferença de tempo em milisegundos

#define TF 100000 // Tamanho do vetor
#define MAX 99999 // Número máximo gerado randomicamente dentro do vetor

void cria(int vetor[TF]);
void exibe(int vetor[TF]);
void bolha(int vetor[TF]);
int busca_sequencial_ordenado(int vetor[TF], int num);
int busca_sequencial_desordenado(int vetor[TF], int num);


int main() 
{
    setlocale(LC_ALL, "pt_br.UTF-8");
    struct timeb tempoim, tempofm;
    int difmile;
    int vetor[TF];
    int opc = 0;
    int num;
    int posicao;

    while (opc != 6)
    {
        printf("\n1 - Criar vetor com números aleatórios\n");
        printf("2 - Exibir vetor criado\n");
        printf("3 - Ordenar vetor (via Método Bolha)\n");
        printf("4 - Buscar número no vetor ordenado (via Busca Sequencial)\n");
        printf("5 - Buscar número no vetor desordenado (via Busca Sequencial)\n");
        printf("6 - Sair\n\n");
        printf("Digite a opção desejada: "); 
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            cria(vetor);
            printf("\nVetor de números aleatórios criado com sucesso.\n\n");
            break;
        case 2:
            exibe(vetor);
            break;
        case 3:
            bolha(vetor);
            printf("\nVetor ordenado com sucesso.\n\n"); 
            break;
        case 4:
            printf("\nDigite o número a ser procurado no vetor ordenado: ");
            scanf("%d", &num); 
            ftime(&tempoim);
            posicao = busca_sequencial_ordenado(vetor, num);
            ftime(&tempofm);
            difmile = (int) (1000.0 * (tempofm.time - tempoim.time) + (tempofm.millitm - tempoim.millitm));
            if (posicao != -1)
                printf("\nO número %d foi encontrado na posição %d (começando de 0) do vetor ordenado.\n\n", num, posicao);
            else
                printf("\nO número %d não foi encontrado no vetor.\n\n", num); 
            printf("\nA Busca sequencial demorou %d milissegundos num vetor ordenado de %d elementos\n\n", difmile, TF); 
            break;
        case 5:
            printf("\nDigite o número a ser procurado no vetor desordenado: ");
            scanf("%d", &num);
            ftime(&tempoim); 
            posicao = busca_sequencial_desordenado(vetor, num);
            ftime(&tempoim);
            difmile = (int) (1000.0 * (tempofm.time - tempoim.time) + (tempofm.millitm - tempoim.millitm));
            if (posicao != -1)
                printf("\nO número %d foi encontrado na posição %d (começando de 0) do vetor desordenado.\n\n", num, posicao);
            else
                printf("\nO número %d não foi encontrado no vetor.\n\n", num); 
            printf("\nA Busca sequencial demorou %d milissegundos num vetor desordenado de %d elementos\n\n", difmile, TF);
            break;
        default: 
            break;
        }
    }
    
    return 0;
}

void cria(int vetor[TF])
{
    srand(time(NULL)); //Semente inicial - Não gerar sempre os mesmos números
    for(int i=0; i<TF; i++)
    {
        vetor[i] = rand() % MAX; //  Gera aleatoriamente os números
    }
}

void exibe(int vetor[TF])
{
    printf("\nVetor: ");
    for(int i=0; i<TF; i++)
    {
        printf("[%d] %d   ", i, vetor[i]);
    }
    printf("\n");
}

void bolha(int vetor[TF])
{
    int aux, i, j;

    for(i = 0; i < TF; i++)
    {
        for(j = 0; j < TF-1; j++)
        {
            if(vetor[j] > vetor[j+1])
            {
                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }
}

int busca_sequencial_ordenado(int vetor[TF], int num)
{
    int i = 0;
    int achou = 0;

    while (i <= TF-1 && achou == 0 && num >= vetor[i])
    {
        if (num == vetor[i])    
            achou = 1;
        else
            i++;
    }

    if (achou == 0)
        i = -1;

    return i;
}
int busca_sequencial_desordenado(int vetor[TF], int num)
{
    int achou = 0;
    int i = 0;

    while (i <= TF-1 && achou == 0)
    {
        if (num == vetor[i])
           achou = 1;
        else
            i++; 
    } 

    if (achou == 0)
        i = -1;

    return i;
}
