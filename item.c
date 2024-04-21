#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "item.h"

#define limite_NOME_TAMANHO 50
// Estrutura para armazenar informações do item
struct item
{
  char nome[limite_NOME_TAMANHO];
  float preco;
  int quantidade;
  int codigo;
};

// Funções adicionadas para lidar com listas
struct no
{
  Item dado;
  struct no *prox;
};

struct lista
{
  No *inicio;
};

void adicionaFim(Lista *lista, Item e)
{
  No *novo = (No *)malloc(sizeof(No));
  novo->dado = e;
  novo->prox = NULL;
  if (lista->inicio == NULL)
  {
    lista->inicio = novo;
  }
  else
  {
    No *pi;
    for (pi = lista->inicio; pi->prox != NULL; pi = pi->prox)
      ;
    pi->prox = novo;
  }
}

void editarLista(Lista *lista, int cod)
{
  if (lista->inicio == NULL)
  {
    printf("Lista vazia\n");
  }
  else
  {
    No *pi;
    for (pi = lista->inicio; pi != NULL && pi->dado.codigo != cod; pi = pi->prox)
      ;
    if (pi == NULL)
    {
      printf("Item não encontrado\n");
    }
    else
    {
      printf("Digite o novo nome do item: ");
      scanf("%s", pi->dado.nome);
      printf("Digite o novo preço do item: ");
      scanf("%f", &pi->dado.preco);
      printf("Digite a nova quantidade do item: ");
      scanf("%d", &pi->dado.quantidade);
      printf("Item editado com sucesso!\n");
    }
  }
}

void deletar(Lista *lista, int cod)
{
  if (lista->inicio == NULL)
  {
    printf("Lista vazia\n");
  }
  else
  {
    No *pa = NULL;
    No *pi;
    for (pi = lista->inicio; pi->prox != NULL && pi->dado.codigo != cod; pi = pi->prox)
    {
      pa = pi;
    }
    if (pa == NULL)
    {
      if (pi->dado.codigo == cod)
      {
        lista->inicio = pi->prox;
        free(pi);
      }
      else
      {
        printf("Item não encontrado\n");
      }
    }
    else
    {
      if (pi->dado.codigo == cod)
      {
        pa->prox = pi->prox;
        free(pi);
      }
      else
      {
        printf("Item não encontrado\n");
      }
    }
  }
}

void lerLista(Lista *lista)
{
  FILE *file = fopen("itens.b", "rb");
  Item e;
  while (fread(&e, sizeof(Item), 1, file))
  {
    adicionaFim(lista, e);
  }
  fclose(file);
}

void salvaLista(Lista *lista)
{
  FILE *file = fopen("itens.b", "wb");
  No *pi;
  for (pi = lista->inicio; pi != NULL; pi = pi->prox)
  {
    fwrite(&pi->dado, sizeof(Item), 1, file);
  }
  fclose(file);
}

void ordenarLista()
{
  Lista lista;
  lista.inicio = NULL;
  lerLista(&lista);
  No *pi;
  No *pj;
  No *pfim = NULL;
  if (lista.inicio == NULL)
  {
    return;
  }
  for (pi = lista.inicio; pi->prox != NULL; pi = pi->prox)
  {
    for (pj = lista.inicio; pj->prox != pfim; pj = pj->prox)
    {
      if (pj->dado.codigo > pj->prox->dado.codigo)
      {
        Item temp = pj->dado;
        pj->dado = pj->prox->dado;
        pj->prox->dado = temp;
      }
    }
  }
  salvaLista(&lista);
}

// Função para cadastrar um novo item
void cadastrar_item()
{
  FILE *file = fopen("itens.b", "ab");
  Item a;
  printf("Nome do item: ");
  scanf("%s", a.nome);
  printf("Preço do item: ");
  scanf("%f", &a.preco);
  printf("Quantidade do item: ");
  scanf("%d", &a.quantidade);
  printf("Código do item: ");
  scanf("%d", &a.codigo);
  fwrite(&a, sizeof(Item), 1, file);
  fclose(file);
  printf("Item cadastrado com sucesso!\n");
}

// Função para listar os itens cadastrados
void listar_itens()
{
  FILE *file = fopen("itens.b", "rb");
  Item a;
  printf("Lista de Itens:\n");
  while (fread(&a, sizeof(Item), 1, file))
  {
    printf("Nome: %s | ", a.nome);
    printf("Codigo: %d | ", a.codigo);
    printf("Preco: %.2f | ", a.preco);
    printf("Quantidade: %d\n", a.quantidade);
  }
  fclose(file);
}

// Função para editar um item
void editar_item(int x)
{
  Lista lista;
  lista.inicio = NULL;
  lerLista(&lista);
  editarLista(&lista, x);
  salvaLista(&lista);
}

// Função para excluir um item
void excluir_item()
{
  int c;
  printf("Digite o código do item que deseja excluir: ");
  scanf("%d", &c);
  Lista lista;
  lista.inicio = NULL;
  lerLista(&lista);
  deletar(&lista, c);
  salvaLista(&lista);
}

// Função para buscar um item pelo nome
void buscar_item()
{
  char nome[limite_NOME_TAMANHO];
  printf("Digite o nome do item que deseja buscar: ");
  scanf("%s", nome);

  int encontrado = 0;
  FILE *file = fopen("itens.b", "rb");
  Item a;
  while (fread(&a, sizeof(Item), 1, file))
  {
    if (strcmp(a.nome, nome) == 0)
    {
      printf("Item encontrado:\n");
      printf("Nome: %s | Preço: %.2f | Quantidade: %d\n", a.nome, a.preco, a.quantidade);
      encontrado = 1;
    }
  }
  if (!encontrado)
  {
    printf("Item não encontrado.\n");
  }
  fclose(file);
}
