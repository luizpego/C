#include <stdio.h>
#include <stdlib.h>
#define MaxTam 100
typedef struct
{
    int item[MaxTam];
    int verificacao[4];
    int apontador;
    int flag;
} TipoLista;
void votacao(TipoLista *Lista)
{
    int opcao = 1;
    while (opcao != 0)
    {
        printf("1-Counter Strike 2\n");
        printf("2-League of legens\n");
        printf("3-Valorant\n");
        printf("4-Minecraft\n");
        printf("0-Encerrar\n");
        printf("Digite em qual jogo voce deseja votar\n");
        scanf("%d", &opcao);

        if (opcao < 0 || opcao > 4)
            printf("Opcao invalida\n");
        else
        {
            if (opcao == 0)
                break;
            else
            {
                Lista->item[Lista->apontador] = opcao;
                Lista->apontador++;
                system("pause");
                system("cls");
            }
        }
    }
}
void verificacao(TipoLista *Lista)
{
    if (Lista->apontador == 0)
        printf("Nenhum voto foi registrado\n");
    else
    {
        int maior = 0;
        int op0 = 0, op1 = 0, op2 = 0, op3 = 0;
        for (int j = 0; j < Lista->apontador; j++)
        {
            if (Lista->item[j] == 1)
            {
                op0++;
                Lista->verificacao[0] = op0;
            }
            else if (Lista->item[j] == 2)
            {
                op1++;
                Lista->verificacao[1] = op1;
            }
            else if (Lista->item[j] == 3)
            {
                op2++;
                Lista->verificacao[2] = op2;
            }
            else if (Lista->item[j] == 4)
            {
                op3++;
                Lista->verificacao[3] = op3;
            }
        }

        for (int k = 0; k < 4; k++)
        {

            if (Lista->verificacao[maior] < Lista->verificacao[k])
                maior = k;
        }
        switch (maior)
        {
        case 0:
        {
            printf("O vencedor foi Counter Strike 2\n");
            break;
        }
        case 1:
        {
            printf("O vencedor foi League of Legends\n");
            break;
        }
        case 2:
        {
            printf("O vencedor foi Valorant\n");
            break;
        }
        case 3:
        {
            printf("O vencedor foi Minecraft\n");
            break;
        }
        }
    }
}

int main()
{

    TipoLista Lista;
    Lista.apontador = 0;
    for (int i = 0; i < 4; i++)
    {
        Lista.verificacao[i] = 0;
    }
    votacao(&Lista);
    verificacao(&Lista);
}