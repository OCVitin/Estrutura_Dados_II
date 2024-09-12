#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar a árvore AVL
struct No {
  int valor;
  struct No *esq;
  struct No *dir;
  int altura;
};

struct No *criarNo(int dado) {
  struct No *no = (struct No *)malloc(sizeof(struct No));
  if (no == NULL) {
    printf("Erro: Falha ao alocar memória para o novo nó.\n");
    exit(-1);
  }
  no->valor = dado;
  no->esq = NULL;
  no->dir = NULL;
  no->altura = 0;
  return no;
}

// Pré requisitos básicos para fazer balanceamento e atribuição de valores
int altura(struct No *no) {
  if (no == NULL)
    return -1;
  return no->altura;
}
int fatorBalanc(struct No *no) {
  if (no == NULL)
    return -1;
  return altura(no->esq) - altura(no->dir);
};

// Comandos para balanceamento e rotações que a árvore pode receber
struct No *rotacaoDir(struct No *no) {
  struct No *noEsq = no->esq;
  struct No *noEsqDir = noEsq->dir;
  noEsq->dir = no;
  no->esq = noEsqDir;
  if (altura(no->esq) > altura(no->dir))
    no->altura = 1 + altura(no->esq);
  else
    no->altura = 1 + altura(no->dir);
  if (altura(noEsq->esq) > altura(noEsq->dir))
    noEsq->altura = 1 + altura(noEsq->esq);
  else
    noEsq->altura = 1 + altura(noEsq->dir);
  return noEsq;
};
struct No *rotacaoEsq(struct No *no) {
  struct No *noDir = no->dir;
  struct No *noDirEsq = noDir->esq;
  noDir->esq = no;
  no->dir = noDirEsq;
  if (altura(no->esq) > altura(no->dir))
    no->altura = 1 + altura(no->esq);
  else
    no->altura = 1 + altura(no->dir);
  if (altura(noDir->esq) > altura(noDir->dir))
    noDir->altura = 1 + altura(noDir->esq);
  else
    noDir->altura = 1 + altura(noDir->dir);
  return noDir;
};
struct No *balanceamento(struct No *raiz, int valor) {
  int fatorRaiz;
  if (raiz == NULL) {
    return raiz;
  }
  if (altura(raiz->esq) > altura(raiz->dir))
    raiz->altura = 1 + altura(raiz->esq);
  else
    raiz->altura = 1 + altura(raiz->dir);

  fatorRaiz = fatorBalanc(raiz);

  if (fatorRaiz > 1 && valor < raiz->esq->valor)
    return rotacaoDir(raiz);

  if (fatorRaiz < -1 && valor > raiz->dir->valor)
    return rotacaoEsq(raiz);

  if (fatorRaiz > 1 && valor > raiz->esq->valor) {
    raiz->esq = rotacaoEsq(raiz->esq);
    return rotacaoDir(raiz);
  }

  if (fatorRaiz < -1 && valor < raiz->dir->valor) {
    raiz->dir = rotacaoDir(raiz->dir);
    return rotacaoEsq(raiz);
  }

  return raiz;
};

// Pré requisitos do comando de exclusão
struct No *encontrarMinimo(struct No *no) {
  struct No *atual = no;
  while (atual && atual->esq != NULL)
    atual = atual->esq;
  return atual;
}
struct No *encontrarMaximo(struct No *no) {
  if (no == NULL)
    return NULL;
  while (no->dir != NULL) {
    no = no->dir;
  }
  return no;
}

// Comandos para inserção e exclusão na árvore
struct No *inserir(struct No *raiz, int valor) {
  if (raiz == NULL) {
    return criarNo(valor);
  }
  if (valor < raiz->valor) {
    raiz->esq = inserir(raiz->esq, valor);
  } else if (valor > raiz->valor) {
    raiz->dir = inserir(raiz->dir, valor);
  } else {
    return raiz;
  }
  return balanceamento(raiz, valor);
}
struct No *excluir(struct No *raiz, int valor) {
  if (raiz == NULL) {
    return raiz;
  }

  if (valor < raiz->valor) {
    raiz->esq = excluir(raiz->esq, valor);
  } else if (valor > raiz->valor) {
    raiz->dir = excluir(raiz->dir, valor);
  } else {
    if (raiz->esq == NULL) {
      struct No *temp = raiz->dir;
      free(raiz);
      return temp;
    } else if (raiz->dir == NULL) {
      struct No *temp = raiz->esq;
      free(raiz);
      return temp;
    }
    if (altura(raiz->esq) >= altura(raiz->dir)) {
      struct No *temp = encontrarMaximo(raiz->esq);
      raiz->valor = temp->valor;
      raiz->esq = excluir(raiz->esq, temp->valor);
    } else {
      struct No *temp = encontrarMinimo(raiz->dir);
      raiz->valor = temp->valor;
      raiz->dir = excluir(raiz->dir, temp->valor);
    }
  }
  return balanceamento(raiz, valor);
}

// Comandos para representação da árvore em listas ordenadas
void emOrdem(struct No *raiz) {
  if (raiz != NULL) {
    emOrdem(raiz->esq);
    printf("%d ", raiz->valor);
    emOrdem(raiz->dir);
  }
}
void preOrdem(struct No *raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz->valor);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
  }
}
void posOrdem(struct No *raiz) {
  if (raiz != NULL) {
    posOrdem(raiz->esq);
    posOrdem(raiz->dir);
    printf("%d ", raiz->valor);
  }
}

// Comandos para representação da árvore em grafo
void imprimeNo(int j, int i) {
  int k;
  for (k = 0; k < i; k++)
    printf("   ");
  printf("%i\n", j);
}
void imprimeArvore(struct No *raiz, int i) {
  if (raiz != NULL) {
    imprimeArvore(raiz->dir, i + 1);
    imprimeNo(raiz->valor, i);
    imprimeArvore(raiz->esq, i + 1);
  }
}

// Extras
int alturaArv(struct No *raiz) {
  if (raiz == NULL) {
    return -1;
  }
  int altEsq = alturaArv(raiz->esq) + 1;
  int altDir = alturaArv(raiz->dir) + 1;
  if (1 + ((altEsq > altDir))) {
    return altEsq;
  } else {
    return altDir;
  }
}
struct No *buscarNo(struct No *raiz, int valor) {
  if (raiz == NULL || raiz->valor == valor)
    return raiz;

  if (valor < raiz->valor)
    return buscarNo(raiz->esq, valor);
  else
    return buscarNo(raiz->dir, valor);
}

int main() {
  int altura;
  int vetorInclusao[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  struct No *raiz = NULL;
  for (int i = 0; i < 10; i++) {
    raiz = inserir(raiz, i);
    printf("Inserido %d\n", vetorInclusao[i]);
  }
  imprimeArvore(raiz, alturaArv(raiz));
  printf("Em ordem:  [ "); emOrdem(raiz); printf("]\n");
  printf("Pré ordem: [ "); preOrdem(raiz); printf("]\n");
  printf("Pós ordem: [ "); posOrdem(raiz); printf("]\n");
  return 0;
}
