#include <stdio.h>
#include <time.h>

void bubbleSort(int vetor[], int tamanho, long long *comparacoes, long long *movimentacoes) {
    int temp;

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - 1 - i; j++) {

            (*comparacoes)++;

            if (vetor[j] > vetor[j + 1]) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                (*movimentacoes)++;
            }
        }
    }
}

void selectionSort(int vetor[], int tamanho, long long *comparacoes, long long *movimentacoes) {

    int menor, temp;

    for (int i = 0; i < tamanho - 1; i++) {
        menor = i;

        for (int j = i + 1; j < tamanho; j++) {

            (*comparacoes)++;

            if (vetor[j] < vetor[menor]) {
                menor = j;
            }
        }

        if (menor != i) {
            temp = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = temp;
            (*movimentacoes)++;
        }
    }
}

void testar(int tamanho) {

    int vetor[tamanho];

    for (int i = 0; i < tamanho; i++)
        vetor[i] = tamanho - i;

    long long comp = 0, mov = 0;
    clock_t inicio, fim;
    double tempo;

    inicio = clock();
    bubbleSort(vetor, tamanho, &comp, &mov);
    fim = clock();
    tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;

    printf("Bubble\t%d\t%.2lf ms\t%lld\t%lld\n", tamanho, tempo, comp, mov);

    for (int i = 0; i < tamanho; i++)
        vetor[i] = tamanho - i;

    comp = 0;
    mov = 0;

    inicio = clock();
    selectionSort(vetor, tamanho, &comp, &mov);
    fim = clock();
    tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;

    printf("Selection\t%d\t%.2lf ms\t%lld\t%lld\n", tamanho, tempo, comp, mov);
}

int main() {

    printf("Algoritmo\tTamanho\tTempo\tComparacoes\tMovimentacoes\n\n");

    testar(100);
    testar(1000);
    testar(10000);

    return 0;
}

