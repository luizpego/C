#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int apontador;
    int item_player[2];
} TipoLista;

void jogar(TipoLista *Lista)
{
    int escolha = 0;
    do
    {
        printf("Voce deseja jogar contra outro jogador ou contra a maquina?\n");
        printf("1-Player, 2-Maquina");
        scanf("%d", &escolha);

        if (escolha != 1 && escolha != 2)
            printf("Opcao invalida\n");

    } while (escolha != 1 && escolha != 2);

    if (escolha == 1)
    {
        printf("Escolha: 1-Pedra, 2-Papel, 3-Tesoura\n");

        printf("Player 1 digite o valor que voce deseja jogar\n");
        scanf("%d", &Lista->item_player[0]);

        printf("Player 2 digite o que voce quer jogar\n");
        scanf("%d", &Lista->item_player[1]);

        if (Lista->item_player[0] == Lista->item_player[1])
        {
            printf("Empate!\n");
        }
        else if ((Lista->item_player[0] == 1 && Lista->item_player[1] == 3) ||
                 (Lista->item_player[0] == 2 && Lista->item_player[1] == 1) ||
                 (Lista->item_player[0] == 3 && Lista->item_player[1] == 2))
        {
            printf("Player 1 ganhou!\n");
        }
        else
        {
            printf("Player 2 ganhou!\n");
        }
    }
}

int main()
{
    TipoLista Lista;
    Lista.apontador = 0;
}