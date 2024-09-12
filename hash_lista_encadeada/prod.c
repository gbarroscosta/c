//Fabiana Ramos
// Gabriel Barros

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <cctype>

#define TF 4


struct no{

    char descricao[10];
    char tipo;
    no *prox;

};


struct partab{

    no *cabeca;

};


int hash(char tipo) {

    int ender = tipo % TF;
    return ender;

}

void criar(struct partab v[TF]){

    int i;

    for (i=0; i<TF; i++){

        v[i].cabeca = NULL;

    }

    printf("\n Tabela Criada!!");

}

void inserir(struct partab v[TF], char tipo, char descricao[10]) {

    int ender = hash(tipo);

    no *novo;
    novo = new(no);

    strcpy(novo->descricao,descricao);

    novo->tipo = tipo;
    novo->prox = NULL;

    if(v[ender].cabeca == NULL){

        v[ender].cabeca = novo;

    } else {

        novo->prox = v[ender].cabeca;
        v[ender].cabeca = novo;

    }

    printf("\n Produto inserido com sucesso!!");

}

void contarOsTipos (struct partab v[TF]){

    int i;
    int ali = 0,
        vest = 0,
        limp = 0,
        hig = 0;

    char tipoAli = 'A';
    char tipoVest = 'V';
    char tipoHig = 'H';
    char tipoLimp = 'L';


    for(i=0; i<TF; i++){

        no* atual= v[i].cabeca;

        while(atual != NULL){

            if(atual->tipo == tipoAli){

                ali++;

            }

            if(atual->tipo == tipoVest){

                vest++;

            }

            if(atual->tipo == tipoHig){

                hig++;

            }

            if(atual->tipo == tipoLimp){

                limp++;

            }

            atual = atual->prox;

        }
    }

    printf("\n _______________________");
    printf("\n Alimento: %d", ali);
    printf("\n Vestimenta: %d", vest);
    printf("\n Higiene: %d", hig);
    printf("\n Limpeza: %d", limp);
    printf("\n _______________________");
}

void consultarProdutos (struct partab v[TF], char tipo){

    int i;
    int ender = hash(tipo);

    no *atual = v[ender].cabeca;

    if(v[ender].cabeca == NULL){

        printf("\n Nao existem produtos para serem exibidos!! \n");

    } else {

        while(atual != NULL){

            if(atual->tipo == tipo){

                printf("\n%s", atual->descricao);

            }

            atual = atual->prox;

        }
    }
}

void exibirTudo(struct partab v[TF]){

    int i;
    no *atual;

    for(i=0; i<TF; i++){

        printf("\n Descricao:");

        if(v[i].cabeca == NULL){

            printf("NULL");

        } else {

            atual = v[i].cabeca;

            while(atual != NULL){

                printf("%s", atual->descricao);

                atual = atual->prox;
            }
        }
    }
    printf("\n");
}


main(){

    struct  partab v[TF];
    char tipo;
    char descricao[10];
    int opcao = 0;

    criar(v);

    while (opcao != 5){

        printf("\n 1 - Inserir Produtos");
        printf ("\n 2 - Consultar todos os produtos cadastrados de um tipo");
        printf ("\n 3 - Contar quantos produtos estao cadastrados em cada tipo");
        printf("\n 4 - Exibir todos");
        printf ("\n 5 - Sair");
        printf ("\n Opcao?: \n");
        scanf ("%d", &opcao);

        switch (opcao){

            case 1:

                printf("\nEntre com o tipo do produto:\n(A - Alimento, H - Higiene, L - Limpeza, V - Vestuario) \n");
                scanf ("%s", &tipo);

                printf("\nEntre com a descricao do produto: \n");
                scanf ("%s", descricao);

                inserir(v, tipo, descricao);

            break;

            case 2:

                printf("\n Entre com o produto:\n(A - Alimento, H - Higiene, L - Limpeza, V - Vestuario) \n");
                scanf ("%s", &tipo);

                consultarProdutos(v, tipo);

            break;

            case 3:

                contarOsTipos(v);

            break;

            case 4:

                exibirTudo(v);

            break;

            }

    }
}

