#include <stdio.h>
#include <stdlib.h>
#define TAM 5


char menu() {
    unsigned char opcao;
    printf("X.X.X.X Bem-vindo ao Batalha Naval X.X.X.X\n");
    printf("\n1. Jogar");
    printf("\n2. Ver regras");
    printf("\n3. Sair");
    printf("\nOpcao desejada: ");
    scanf("%d", &opcao);
    return opcao;
}

void sorteiaNavio(int tab[][TAM]){
    int linha, coluna, i=1;
    srand(time(NULL));
    
    while(i<=3){
        linha = rand()%TAM;
        coluna = rand()%TAM;
    
        if(tab[linha][coluna]!=0){
         tab[linha][coluna]=0;
         i++;
        }
    }
}

void iniciaTabuleiro(int tab[][TAM]){
    int i, j;
    for (i=0; i<TAM; i++){
        for(j=0; j<TAM; j++)
            tab[i][j]= -1;
    }
}

void imprimeJogo(int tab[][TAM], int tiros){
    int i, j;
    
    system("cls");
    printf("\n   ------------------------------\n");
    printf("   X.X.X.X Batalha Naval X.X.X.X");
    printf("\n   ------------------------------\n\n");
    printf("   Tiros disponiveis: %d\n\n", tiros);  

    for (i=0; i<TAM; i++)
        printf ("\t%d", i+1);
        
    printf("\t\t------------------------------------------");
    for (i=0; i<TAM; i++){
        printf("\n%d", i+1);
        for(j=0; j<TAM; j++){
            if(tab[i][j]<=0)
                printf ("\t-");
            if(tab[i][j]==1)
                printf ("\tX");
            if(tab[i][j]==2)
                printf ("\t*");
        }    
            if (i==0)
             printf ("\t\t -> Legenda");
            if (i==1)
             printf ("\t\t   - (Nenhum tiro dado nesse bloco)");
            if (i==2)
             printf ("\t\t   * (Tiro dado, acerto na agua)");
            if (i==3)
             printf ("\t\t   X (Tiro dado, acerto em uma embarcacao)");
            if (i==4)
             printf ("\t\t------------------------------------------");                
    }
}

int gerarDica(int tab[][TAM], int l, int c){
    int i, achou=0;
    
    for (i=0; i<TAM; i++)
        if (tab[i][c-1]==0)
            achou=1;
    
    for (i=0; i<TAM; i++)
        if (tab[l-1][i]==0)
            achou+=2;
    
    return achou;
}

void imprimeDica(int dica){   
    printf ("\nDica: ");
    
    if (dica == 1)
        printf ("Ha embarcacao nessa coluna. ;)\n\n");
    
    if (dica == 2)
        printf ("Ha embarcacao nessa linha. ;)\n\n");
    
    if (dica == 3)
        printf ("Ha embarcacao nessa linha e nessa coluna. ;)\n\n");
    
    if (dica == 0)
        printf ("Nao ha embarcacao nessa linha ou coluna. ;)\n\n");
}

void receberTiro(int *l, int *c){
    printf("\n\nInforme as coordenadas em que deseja atirar: \n");
    printf("Linha: ");
    scanf("%d", l);
    printf("Coluna: ");
    scanf("%d", c);
}

void verificarTiro(int tab[][TAM], int l, int c, int *tiros, int *acertos){  
    
    if (tab[l-1][c-1]>0){
        printf("\nVoce ja atirou ai. Tente outro lugar!");
    }
    
    else{
        if(tab[l-1][c-1]== -1){
            tab[l-1][c-1] = 2;
            printf("\nVoce acertou... NA AGUA! HAHA, quem sabe na proxima!\n");
            (*tiros)--;
        }
        
        if(tab[l-1][c-1]== 0){
            tab[l-1][c-1] = 1;
            printf("\nBOA! Acertou uma embarcacao!\n");
            (*acertos)++;
        }
    }
}

int resultado(int tiros, int acertos){
    if (tiros == 0 && acertos<3){
        printf ("\n\tX.X VOCE PERDEU X.X\nNao conseguiu acertar todas as embarcacoes :(\n\n");
        return 0;
    }
    
    if (acertos == 3){
        printf ("\n\tX.X VOCE VENCEU X.X\nConseguiu acertar todas as embarcacoes!\n\n");
        return 1;
    }
    
    else
        return -1;
}

void imprimeResposta(int tab[][TAM]){
    int i, j;

    printf ("As embarcacoes estavam nos pontos: \n");

    for (i=0; i<TAM; i++){
        for(j=0; j<TAM; j++){
            if (tab[i][j]==0 || tab [i][j]==1)
                printf ("\n(%d, %d)\n", i+1, j+1);
        }
   }
}

int main() {
    char opcao;
    int tabuleiro[TAM][TAM];
    int lin, col;
    
    do {
      system("cls");
      opcao = menu();
      int tiros=7, acertos=0, dica;
      
      switch (opcao) {
        case 1:
            iniciaTabuleiro(tabuleiro);
            sorteiaNavio(tabuleiro);
                
            do{
                imprimeJogo(tabuleiro, tiros);
                do{
                    receberTiro(&lin, &col);
                    if (lin>5 || lin<1 || col>5 || col<1)
                        printf ("\nCoordenada invalida.");
                }while (lin>5 || lin<1 || col>5 || col<1);
 
                verificarTiro(tabuleiro, lin, col, &tiros, &acertos);
                
                if (tabuleiro[lin-1][col-1]!=1){
                    dica = gerarDica(tabuleiro, lin, col);
                    imprimeDica(dica);
                }
                
                system("pause");
                if(resultado (tiros, acertos)!= -1)
                    imprimeJogo(tabuleiro, tiros);
                
            }while(resultado (tiros, acertos)== -1);
            
            if (acertos<3)
                imprimeResposta(tabuleiro);
            
            system("pause");
          break;

        case 2:
            system("cls");
            printf ("\nX.X Regras do Batalha Naval X.X\n");
            printf ("\nO Jogo e um tabuleiro 5x5, que representa o mar.");
            printf("\nNele estao escondidas tres embarcacoes");
            printf("\nO jogador fornece coordenadas para atirar, \ne o objetivo e acertar todas as tres embarcacoes.");
            printf("\nTente acertar antes que seus tiros disponiveis acabe!");
            printf("\nQue comecem os jogos!!\n\n");
            system("pause");
          break;
      }
      
    }while(opcao!=3);
    
    return (EXIT_SUCCESS);
}

