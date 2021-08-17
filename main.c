#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrura do AFD
typedef struct{             //Estrutura utilizada para guardar uma transição do AFD
    int estadoInicial;
    char simbolo;
    int estadoFinal;
} transicao;

typedef struct{
    int qtdeEstados;
    int qtdeTerminais;
    char simbolosTerminais[11];
    int qtdeEstadosIniciais;
    int qtdeEstadosAceitacao;
    int estadosAceitacao[10];
    int qtdeTransicoes;
    transicao transicoes[50];
}AFD;

//Função que testa se determinada cadeia pode ser processada por um AFD
int testaCadeia(AFD automato, char cadeia[]){
    int aux = 0;
    int flag = 0;
    int estadoAtual = 0;

    for(int j=0; j<strlen(cadeia); j++){
        for(int i=0; i<automato.qtdeTransicoes; i++){
            if(automato.transicoes[i].estadoInicial == estadoAtual && automato.transicoes[i].simbolo == cadeia[j]){
                 estadoAtual = automato.transicoes[i].estadoFinal;
                 flag = 1;
                 break;
            }
            else
                flag = 0;
        }
    }

    if(flag == 0 && strcmp(cadeia, "-")!=0)
            return 0;

    else{
        //verifica se o estado atual é também final
        for(int i=0; i < automato.qtdeEstadosAceitacao; i++){
            if(estadoAtual == automato.estadosAceitacao[i]){
                aux = 1;
            }
        }
        if(aux == 0)
            return 0;
        else
            return 1;
    }
}


int main()
{
    //Capturar dados da entrada
    char cadeia[20];
    int qtdeCadeias;
    AFD* automato;
    automato = (AFD*)malloc(sizeof(AFD));

    //Linha 1
    scanf("%d", &automato->qtdeEstados);

    //Linha 2
    scanf("%d", &automato->qtdeTerminais);

    for(int i=0; i<automato->qtdeTerminais; i++){
        scanf(" %c", &automato->simbolosTerminais[i]);
        fflush(stdin);
    }

    //Linha 3
    scanf("%d", &automato->qtdeEstadosIniciais);

    //Linha 4
    scanf("%d", &automato->qtdeEstadosAceitacao);

    for(int i=0; i<automato->qtdeEstadosAceitacao; i++){
        scanf("%d", automato->estadosAceitacao);
    }

    //Linha 5
    scanf("%d", &automato->qtdeTransicoes);

    //A partir da Linha 6 -> Transições
    for(int i=0; i<automato->qtdeTransicoes; i++){
        transicao* tr = (transicao*)malloc(sizeof(transicao));
        scanf( "%d %c %d", &tr->estadoInicial, &tr->simbolo, &tr->estadoFinal);
        fflush(stdin);

        automato->transicoes[i] = *tr;
    }

    //Testes
    scanf("%d", &qtdeCadeias);

    int v[qtdeCadeias];
    for(int i=0; i<qtdeCadeias; i++){
        scanf("%s", cadeia);
        fflush(stdin);
        v[i]=testaCadeia(*automato, cadeia);
    }

    for(int i=0; i<qtdeCadeias; i++){
        if(v[i]==0)
            printf("rejeita\n");
        else
            printf("aceita\n");
    }

    return 0;
}
