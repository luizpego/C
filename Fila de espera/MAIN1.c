#include <stdio.h>
#include <stdlib.h>
#define MaxTam 10
typedef struct
{
    int inicio;
    int fim;
    int item[MaxTam];
} TipoFila;
int menu()
{
    int A = 0;
    printf("1-Adicionar numero do cliente\n");
    printf("2-Remover cliente\n");
    printf("3-Exibir proximo cliente\n");
    printf("0-Encerrar\n");
    printf("Qual opcao voce deseja?\n");
    scanf("%d", &A);
    return A;
}
void adicionar_cliente(TipoFila *Fila)
{
    if ((Fila->fim + 1) % MaxTam == Fila->inicio)
        printf("A fila esta cheia\n");
    else
    {
        printf("Digite o numero do cliente\n");
        scanf("%d", &Fila->item[Fila->fim]);
        Fila->fim = (Fila->fim + 1) % MaxTam;
    }
}
void remover(TipoFila *Fila)
{
    if (Fila->inicio == Fila->fim)
        printf("A fila esta vazia\n");
    else
    {
        Fila->inicio = (Fila->inicio + 1) % MaxTam;
    }
}
void exibir(TipoFila *Fila)
{
    int aux1 = Fila->inicio;
    if (Fila->inicio == Fila->fim)
        printf("A fila esta vazia\n");
    else
    {
        if (((Fila->inicio + 1) % MaxTam == Fila->fim))
            printf("Ha apenas uma pessoa na fila\n");
        else
        {
            printf("O proximo cliente e:%d", (Fila->item[aux1 = ((aux1 + 1) % MaxTam)]));
            aux1 = (aux1 + 1) % MaxTam;
        }
    }
}
int main()
{
    int A = 0;
    TipoFila Fila;
    Fila.inicio = 0;
    Fila.fim = 0;
    do
    {
        A = menu();
        switch (A)
        {
        case 0:
            printf("Encerrando...");
            break;
        case 1:
            adicionar_cliente(&Fila);
            break;
        case 2:
            remover(&Fila);
            break;
        case 3:
            exibir(&Fila);
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
        system("pause");
        system("cls");
    } while (A != 0);
}