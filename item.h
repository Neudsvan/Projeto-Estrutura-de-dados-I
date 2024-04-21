#ifndef H_ITEM
#define H_ITEM

typedef struct item Item;
typedef struct lista Lista;
typedef struct no No;

void adicionaFim(Lista *lista, Item e);
void editarLista(Lista *lista, int cod);
void deletar(Lista *lista, int cod);
void lerLista(Lista *lista);
void salvaLista(Lista *lista);
void ordenarLista();
void cadastrar_item();
void listar_itens();
void editar_item(int x);
void excluir_item();
void buscar_item();


#endif