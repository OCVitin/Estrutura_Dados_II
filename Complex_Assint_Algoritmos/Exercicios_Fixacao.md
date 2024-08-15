## Exercício 1: Soma de Elementos
Dado o seguinte algoritmo, determine a complexidade em termos de Big O:
```c
int soma(int vetor[], int n) {     //1
    int soma = 0;                  //1
    for (int i = 0; i < n; i++) {  //n+1
        soma += vetor[i];          //n
    }
    return soma;                   //1
}
```
Qual é a complexidade desse algoritmo?
O(n)
i = 2n + 4

## Exercício 2: Multiplicação de Matrizes
Considere o algoritmo abaixo para multiplicar duas matrizes:
```c
void multiplica_matrizes(int A[][n], int B[][n], int C[][n], int n) { //1
    for (int i = 0; i < n; i++) {                                     //n+1
        for (int j = 0; j < n; j++) {                                 //(n+1)^2
            C[i][j] = 0;                                              //n^2
            for (int k = 0; k < n; k++) {                             //(n+1)^3
                C[i][j] += A[i][k] * B[k][j];                         //n^3
            }
        }
    }
}
```
Qual é a complexidade desse algoritmo em termos de n?
O(n^3)
i = 2n^3 + 5n^2 + 6n + 4 

## Exercício 3: Busca Binária
Analise a complexidade do seguinte algoritmo de busca binária:
```c
int busca_binaria(int vetor[], int n, int x) {  //1
    int inicio = 0, fim = n - 1;                //1
    while (inicio <= fim) {                     //n
        int meio = inicio + (fim - inicio) / 2; //log n
        if (vetor[meio] == x)                   //n
            return meio;                        //n
        if (vetor[meio] < x)                    //n
            inicio = meio + 1;                  //n
        else                                    //n
            fim = meio - 1;                     //n
    }
    return -1;                                  //1
}
```
Qual é a complexidade do algoritmo de busca binária?
O(n)
i = log n + 7n - 4

## Exercício 4: Verificação de Número Primo
Dado o algoritmo abaixo que verifica se um número é primo, determine a complexidade:
```c
int eh_primo(int n) {                  //1
    if (n <= 1)                        //1
        return 0;                      //1
    for (int i = 2; i * i <= n; i++) { //n^1/2 + 1
        if (n % i == 0)                //n^1/2
            return 0;                  //n^1/2
    }
    return 1;                          //1
}
```
Qual é a complexidade do algoritmo para verificar se um número é primo?
O(n^1/2)
i = 3(n^1/2) + 5

## Exercício 5: Ordenação por Inserção
Analise a complexidade do algoritmo de ordenação por inserção abaixo:
```c
void insertion_sort(int vetor[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}
```
Qual é a complexidade do pior caso para o algoritmo de ordenação por inserção?

## Exercício 6: Fibonacci Recursivo
Considere o seguinte algoritmo recursivo para calcular o n-ésimo número de Fibonacci:
```c
int fibonacci(int n) {                      //1
    if (n <= 1)                             //1
        return n;                           //1
    return fibonacci(n-1) + fibonacci(n-2); //2^n
}
```
Qual é a complexidade do algoritmo recursivo para calcular o n-ésimo número de Fibonacci?
O(2^n)
i = 2^n + 3

## Exercício 7: Soma Recursiva dos Números de 1 a N
Analise a complexidade do algoritmo recursivo abaixo:
```c
int soma_recursiva(int n) {           //1
    if (n == 1)                       //1
        return 1;                     //1
    return n + soma_recursiva(n - 1); //n
}
```
Qual é a complexidade do algoritmo para somar recursivamente os números de 1 a N?

## Exercício 8: Quick Sort
Dado o seguinte algoritmo de Quick Sort, determine sua complexidade no melhor, pior e caso médio:
```c
void quick_sort(int vetor[], int baixo, int alto) {  //1
    if (baixo < alto) {                              //1
        int pi = particiona(vetor, baixo, alto);     //n
        quick_sort(vetor, baixo, pi - 1);            //n log n
        quick_sort(vetor, pi + 1, alto);             //n log n
    }
}
```
Qual é a complexidade do Quick Sort nos três casos (melhor, pior e caso médio)?
O(n log n)
i = 2(n log n) + n + 2

## Exercício 9: Contagem de Dígitos
Analise a complexidade do seguinte algoritmo que conta o número de dígitos de um número inteiro:
```c
int conta_digitos(int n) {
    int contagem = 0;
    while (n != 0) {
        n = n / 10;
        contagem++;
    }
    return contagem;
}
```
Qual é a complexidade desse algoritmo para contar o número de dígitos?

## Exercício 10: Merge Sort
Considere o seguinte algoritmo de Merge Sort:
```c
void merge_sort(int vetor[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(vetor, l, m);
        merge_sort(vetor, m + 1, r);
        merge(vetor, l, m, r);
    }
}
```
Qual é a complexidade do algoritmo de Merge Sort?
