#ifndef H_USUARIO
#define H_USUARIO

typedef struct usuario Usuario;
typedef struct lista Lista;
typedef struct no No;

int login();
int verificar_se_ja_existe_email(const char *email);
int validar_email(char email[]);
void cadastrar_usuario();

#endif