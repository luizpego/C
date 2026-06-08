#include <stdio.h>
#include <stdlib.h>
#define MaxTam 100

typedef struct
{
    int item[MaxTam];
    int inicio;
    int fim;
} TipoLista;

int menu()
{
    int A = 0;
    printf("1-Inserir dado\n");
    printf("2-Remover dado\n");
    printf("3-Exibir maior e menor valor\n");
    printf("4-Exibir dados na ordem de entrada\n");
    printf("5-Exibir endereco de memoria dos valores da lista\n");
    printf("0-Sair\n");
    printf("Qual opcao voce deseja?\n");
    scanf("%d", &A);
    return A;
}

void adicionar(TipoLista *Lista)
{
    if (Lista->fim == 100)
        printf("A lista esta cheia\n");
    else
    {
        printf("Qual valor voce deseja adicionar a lista?\n");
        scanf("%d", &Lista->item[Lista->fim]);
        Lista->fim++;
    }
}

void remover(TipoLista *Lista)
{
    int A = 0, B = 0, flag = 1;
    if (Lista->inicio == Lista->fim)
        printf("A lista esta vazia\n");
    else
    {
        printf("Qual nota voce deseja remover?\n");
        scanf("%d", &A);
        for (int j = Lista->inicio; j < Lista->fim; j++)
        {
            if (Lista->item[j] == A)
            {
                B = j;
                flag = 0;
            }
        }
        if (flag != 0)
            printf("Valor nao encontrado\n");
        else
        {
            for (int i = B; i < Lista->fim - 1; i++)
            {
                Lista->item[i] = Lista->item[i + 1];
            }
            Lista->fim--;
            printf("Valor removido\n");
        }
    }
}

void maior_menor(TipoLista *Lista)
{
    int menor = 0, maior = 0;
    if (Lista->inicio == Lista->fim)
        printf("A lista esta vazia\n");
    else
    {
        if (Lista->fim == 1)
            printf("ha apenas um elemento na lista\n");
        else
        {
            for (int i = Lista->inicio; i < Lista->fim; i++)
            {
                if (maior < Lista->item[i])
                    maior = i;
                if (menor > Lista->item[i])
                    menor = i;
            }
            printf("O maior valor e:%d\n", Lista->item[maior]);
            printf("O menor valor e:%d\n", Lista->item[menor]);
        }
    }
}
void exibir(TipoLista *Lista)
{
    if (Lista->inicio == Lista->fim)
        printf("A lista esta vazia\n");
    else
    {
        for (int i = Lista->inicio; i < Lista->fim; i++)
        {
            printf("%d ", Lista->item[i]);
        }
    }
}
void exibir_endereco_memoria(TipoLista *Lista)
{
    if (Lista->inicio == Lista->fim)
        printf("A lista esta vazia\n");
    else
    {
        for (int i = Lista->inicio; i < Lista->fim; i++)
        {
            printf("%p ", &Lista->item[i]);
        }
    }
}
int main()
{
    TipoLista Lista;
    Lista.inicio = 0;
    Lista.fim = 0;
    int Menu = 0;
    do
    {
        Menu = menu();
        switch (Menu)
        {
        case 1:
            adicionar(&Lista);
            break;
        case 2:
            remover(&Lista);
            break;
        case 3:
            maior_menor(&Lista);
            break;
        case 4:
            exibir(&Lista);
            break;
        case 5:
            exibir_endereco_memoria(&Lista);
            break;
        case 0:
            printf("Encerrando...");
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
        system("pause");
        system("cls");
    } while (Menu != 0);
}