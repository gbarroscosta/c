//Trabalho 1 - Programação II
//Alunos: Gabriel Barros Costa e Fabiana Ramos

#include <stdio.h>
#include <string.h>

#define TF 100

struct cliente
{
    int numconta;
    char nome[20];
    float saldo;
};

void carrega(struct cliente clientes[TF],int *ptl);
void exibe(struct cliente clientes[TF], int tl);
int busca(struct cliente clientes[TF], int tl, int numconta);
void deposito(struct cliente clientes[TF], int tl, int numconta, float valor);
void retirada(struct cliente clientes[TF], int tl, int numconta, float valor);
void regravar(struct cliente clientes[TF], int tl);

int main(void)
{
    int opcao=0, numconta, posicao, tl = 0;
    double valor;
    struct cliente clientes[TF];
    while (opcao!=7)
    {
        printf("\n\n1 - Ler arquivo texto para carregar o vetor de contas de clientes");
        printf("\n2 - Exibir o vetor na memoria principal");
        printf("\n3 - Consultar a conta de um cliente (busca) no vetor");
        printf("\n4 - Depositar");
        printf("\n5 - Retirar");
        printf("\n6 - Regravar tabela no arquivo texto");
        printf("\n7 - Sair");
        printf("\n\nOpção: "); scanf("%d",&opcao);
        switch (opcao)
        {
            case 1: if(tl!=0)
                        tl = 0;
                    //carrega(clientes,&tl);
                    carrega(clientes,&tl);
                    printf("\nVetor de clientes carregado com %d clientes", tl);
                    break;
            case 2: exibe(clientes,tl);
                        break;
            case 3: printf("\nDigite o número da conta a ser consultada: ");
                    scanf("%d", &numconta);
                    posicao = busca(clientes, tl, numconta);
                    if (posicao==-1)
                        printf("\nConta não encontrada / inexistente.");
                    else
                        printf("\nConta encontrada na posição %d\nNúmero da conta: %d\nNome: %s\nSaldo: $%.2f", posicao, clientes[posicao].numconta, clientes[posicao].nome, clientes[posicao].saldo);
                    break;
            case 4: printf("Digite o número da conta na qual será feito o depósito: ");
                    scanf("%d", &numconta);
                    printf("Digite o valor a ser depositado: ");
                    scanf("%lf", &valor);
                    deposito(clientes, tl, numconta, valor);
                    break;
            case 5: printf("Digite o número da conta na qual será feito a retirada: ");
                    scanf("%d", &numconta);
                    printf("Digite o valor a ser retirado: ");
                    scanf("%lf", &valor);
                    retirada(clientes, tl, numconta, valor);
                    break;
            case 6: regravar(clientes,tl);
                    break;
        }
    }
    return 0;
}

void carrega(struct cliente clientes[TF],int *ptl)
{
    //tl = 0;
    
    int numconta;
    char nome[20];
    float saldo;
    
    FILE *arq = fopen("contas.txt", "r");
    if(arq == NULL)
        printf("Erro, não foi possivel abrir o arquivo\n");
    else
    {
        while( !feof(arq) )
        {
            fscanf(arq,"%d %s %f\n", &numconta, nome, &saldo);
            clientes[*ptl].numconta = numconta;
            strcpy(clientes[*ptl].nome,nome);
            clientes[*ptl].saldo = saldo;
            *ptl = *ptl+1;
        }
        fclose(arq);
    }
}

void exibe(struct cliente clientes[TF], int tl)
{
    int i;
    printf("\nLista de clientes no array clientes: \n");
    for (i=0; i<tl; i++)
       printf("\n    Posição: %d  Número da conta: %d Nome: %s Saldo: $%5.2f ", i,clientes[i].numconta, clientes[i].nome , clientes[i].saldo);
}

int busca(struct cliente clientes[TF], int tl, int numconta)
{
    int posicao=-1;
    int i=0;
    while ((i<tl)&&(numconta != clientes[i].numconta))
            i++;
    if (i<tl)
        posicao = i;
    else
        posicao = -1;
    return posicao;
}

void deposito(struct cliente clientes[TF], int tl, int numconta, float valor)
{
    int posicao = busca(clientes, tl, numconta);
    if (posicao == -1)
        printf("\nConta não encontrada / inexistente!");
    else
    {
        clientes[posicao].saldo += valor;
        printf("\nDepósito realizado com sucesso!\n");
    }
       
}

void retirada(struct cliente clientes[TF], int tl, int numconta, float valor)
{
    int posicao = busca(clientes, tl, numconta);
    if (posicao == -1)
        printf("\nConta não encontrada / inexistente!");
    else if (clientes[posicao].saldo < valor)
        printf("\nSaldo insuficiente para que seja retirada essa quantia!");
    else
    {
        clientes[posicao].saldo -= valor;
        printf("\nRetirada relizada com sucesso!\n");
    }
        
}

void regravar(struct cliente clientes[TF], int tl)
{
    FILE *arq = fopen("contas.txt","w");
    int i;
    for (i=0; i<tl; i++)
       fprintf(arq,"%d %s %f\n", clientes[i].numconta, clientes[i].nome, clientes[i].saldo);
    fclose(arq);
    printf("\n Tabela regravada com sucesso no arquivo texto!");
}
