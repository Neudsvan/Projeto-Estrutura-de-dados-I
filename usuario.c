#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "usuario.h"

#define limite_NOME_TAMANHO 50
#define limite_EMAIL_TAMANHO 80
#define limite_SENHA_TAMANHO 20

// Estrutura para armazenar informações do usuário
struct usuario
{
  char nome[limite_NOME_TAMANHO];
  char senha[limite_SENHA_TAMANHO];
  char email[limite_EMAIL_TAMANHO];
};

// Função para realizar login
int login()
{
  char nome[limite_NOME_TAMANHO];
  char senha[limite_SENHA_TAMANHO];

  printf("Login\n");
  printf("Nome de usuário: ");
  scanf("%s", nome);
  printf("Senha: ");
  scanf("%s", senha);

  FILE *file = fopen("users.b", "rb");
  Usuario a;
  while (fread(&a, sizeof(Usuario), 1, file))
  {
    if (strcmp(a.nome, nome) == 0 && strcmp(a.senha, senha) == 0)
    {
      printf("Login realizado com sucesso!\n");
      return 1;
    }
  }
  fclose(file);

  printf("Nome de usuário ou senha inválidos. Por favor, tente novamente.\n");
  return 0;
}

// Função que verifica se o email já existe no arquivo
int verificar_se_ja_existe_email(const char *email)
{
  FILE *file = fopen("emails.txt", "r");
  if (file == NULL)
  {
    return 0; // Arquivo não existe, então email não está cadastrado
  }
  char linha[limite_EMAIL_TAMANHO];
  while (fgets(linha, limite_EMAIL_TAMANHO, file) != NULL)
  {
    // Remover o caractere de nova linha de fgets
    linha[strcspn(linha, "\n")] = 0;
    if (strcmp(linha, email) == 0)
    {
      fclose(file);
      return 1; // Email já cadastrado
    }
  }
  fclose(file);
  return 0; // Email não encontrado no arquivo
}

// Função para verificar a validade do e-mail
int validar_email(char email[])
{
  if (strlen(email) >= limite_EMAIL_TAMANHO || strchr(email, '@') == NULL)
  {
    return 0; // E-mail inválido se não contiver '@' ou exceder o comprimento limite
  }
  if (verificar_se_ja_existe_email(email))
  {
    return 0; // E-mail já cadastrado
  }

  // Adicionando email no arquivo
  FILE *file = fopen("emails.txt", "a");
  fprintf(file, "%s\n", email);
  fclose(file);

  printf("E-mail cadastrado!\n");

  return 1; // E-mail válido
}

// Função para cadastrar novo usuário
void cadastrar_usuario()
{
  FILE *file = fopen("users.b", "ab");
  Usuario a;
  printf("Cadastro de novo usuário\n");
  printf("Nome de usuário: ");
  scanf("%s", a.nome);
  printf("Senha: ");
  scanf("%s", a.senha);
  printf("E-mail: ");
  scanf("%s", a.email);

  if (!validar_email(a.email))
  {
    printf("E-mail inválido ou já cadastrado. Por favor, forneça um e-mail válido.\n");
    return;
  }
  fwrite(&a, sizeof(Usuario), 1, file);
  fclose(file);
  printf("Cadastro realizado!\n");
}