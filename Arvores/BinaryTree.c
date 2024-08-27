// Versão de Vitor Motta Supelete, estudante de Ciência da Computação da turma CC6M

#include <stdio.h>
#include <stdlib.h>

struct NO {
  int info;       // Dado a ser armazenado
  struct NO *esq; // Filho da esquerda (valor menor)
  struct NO *dir; // Filho da direita (valor maior)
};

typedef struct NO *ArvBin;

ArvBin *criaArvBin() {
  ArvBin *raiz = (ArvBin *)malloc(sizeof(ArvBin));
  if (raiz !=
      NULL) // Se a árvore foi criada corretamente, ponteiro aponta para nulo
    *raiz = NULL;
  return raiz;
}

void liberaNO(struct NO *no) {
  if (no == NULL) // Se o nó é nulo, não há nada a ser liberado
    return;
  liberaNO(no->esq); // Liberar filho da esquerda
  liberaNO(no->dir); // Liberar filho da direita
  free(no);          // Liberar o atual
  no = NULL;
}

void liberaArvBin(ArvBin *raiz) {
  if (raiz == NULL)
    printf("Não foi possível liberar a árvore, ela não existe.\n");
  return;
  liberaNO(*raiz); // libera cada nó
  free(raiz);      // libera a raiz
  raiz = NULL;
}

// Inserção de elemento na árvore binária usando alocação de memória
int insereArvBin(ArvBin *raiz, int valor) {
  if (raiz == NULL) {
    printf("Não foi possível inserir o elemento, a árvore não existe.\n");
    return 0;
  }
  struct NO *novo;
  novo = (struct NO *)malloc(sizeof(struct NO));
  if (novo == NULL)
    return 0; // Se o elemento não foi criado corretamente, retorna zero
  novo->info = valor;
  novo->dir = NULL;
  novo->esq = NULL;
  if (*raiz == NULL)
    *raiz = novo; // Se a árvore está vazia, insere o elemento como raiz
  else {
    struct NO *atual = *raiz; // Se não, percorre a árvore
    struct NO *ant = NULL;
    while (atual != NULL) { // Enquanto não encontrar um ponteiro vazio...
      ant = atual;
      if (valor == atual->info) { // Elemento já existe
        free(novo);
        return 0;
      }
      if (valor > atual->info) // Se o valor atual for maior que o valor
                               // visitado, navega para a direita
        atual = atual->dir;
      else // Se não, navega para a esquerda
        atual = atual->esq;
    }
    if (valor > ant->info) // Se valor a ser inserido for maior que o valor do
                           // nó anterior
      ant->dir = novo;     // Insere na direita
    else
      ant->esq = novo; // Se valor a ser inserido for menor que o valor do nó
                       // anterior, insere na esquerda
  }
  printf("Inserido %d\n", valor);
  return 1;
}

// Procura o menor elemento partindo do atual, função usada na exclusão de um
// dado elemento
struct NO *encontrarMinimo(ArvBin raiz) {
  struct NO *atual = raiz;
  while (atual->esq != NULL) {
    atual = atual->esq;
  }
  return atual;
}

// Exclusão de um dado elemento
struct NO *excluir(ArvBin raiz, int valor) {
  if (raiz == NULL) {
    printf("Não foi possível excluir o elemento. A árvore pode estar vazia "
           "e/ou o elemento procurado não existe.\n");
    return raiz;
  }
  if (valor < raiz->info) {
    raiz->esq = excluir(raiz->esq, valor);
  } else if (valor > raiz->info) {
    raiz->dir = excluir(raiz->dir, valor);
  } else {

    // Caso do nó ter grau 0 ou 1
    if (raiz->esq == NULL) {
      struct NO *temp = raiz->dir;
      free(raiz);
      printf("Elemento excluído: %d\n", valor);
      return temp;
    } else if (raiz->dir == NULL) {
      struct NO *temp = raiz->esq;
      free(raiz);
      printf("Elemento excluído: %d\n", valor);
      return temp;
    }

    // Caso do nó ter grau 2, procura o sucessor em ordem, buscando o menor
    // filho da subárvore da direita
    struct NO *temp = encontrarMinimo(raiz->dir);
    raiz->info = temp->info;
    raiz->dir = excluir(raiz->dir, temp->info);
  }
  return raiz;
}

// Pesquisa em ordem
void imprimirArvBinEmOrdem(ArvBin raiz) {
  if (raiz != NULL) {
    imprimirArvBinEmOrdem(raiz->esq); // Navega para a esquerda
    printf("%d ", raiz->info);        // Imprime o atual
    imprimirArvBinEmOrdem(raiz->dir); // Navega para a direita
  }
  return;
}

// Pesquisa em pré-ordem
void imprimirArvBinPreOrdem(ArvBin raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz->info);         // Imprime o atual
    imprimirArvBinPreOrdem(raiz->esq); // Navega para a esquerda
    imprimirArvBinPreOrdem(raiz->dir); // Navega para a direita
  }
  return;
}

// Pesquisa em pós-ordem
void imprimirArvBinPosOrdem(ArvBin raiz) {
  if (raiz != NULL) {
    imprimirArvBinPosOrdem(raiz->esq); // Navega para a esquerda
    imprimirArvBinPosOrdem(raiz->dir); // Navega para a direita
    printf("%d ", raiz->info);         // Imprime o atual
  }
  return;
}

int main() {
  ArvBin *raiz = criaArvBin();
  int n = 10, dados[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i = 0; i < n; i++) {
    insereArvBin(raiz, dados[i]);
  }

  // Antes de excluir
  imprimirArvBinPreOrdem(*raiz);
  printf("\n");
  imprimirArvBinEmOrdem(*raiz);
  printf("\n");
  imprimirArvBinPosOrdem(*raiz);
  printf("\n");

  // Após excluir
  excluir(*raiz, 6);
  imprimirArvBinPreOrdem(*raiz);
  printf("\n");
  imprimirArvBinEmOrdem(*raiz);
  printf("\n");
  imprimirArvBinPosOrdem(*raiz);

  return 0;
}
