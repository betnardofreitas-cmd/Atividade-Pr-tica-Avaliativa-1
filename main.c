#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ================= FUNÇÃO AUXILIAR ================= */

void printArray(int arr[], int n) {
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* ================= BUBBLE SORT ================= */

void bubbleSort(int arr[], int n) {
    int i, j, temp;

    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - 1 - i; j++) {
            if(arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

/* ================= SELECTION SORT ================= */

void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;

    for(i = 0; i < n - 1; i++) {
        minIndex = i;

        for(j = i + 1; j < n; j++) {
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }

        if(minIndex != i) {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

/* ================= INSERTION SORT ================= */

void insertionSort(int arr[], int n) {
    int i, j, key;

    for(i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/* ================= QUICK SORT ================= */

int partition(int arr[], int low, int high) {
    int pivot, i, j, temp;

    pivot = arr[high];
    i = low - 1;

    for(j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;

    return i+1;
}

void quickSort(int arr[], int low, int high) {
    int pi;

    if(low < high) {
        pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* ================= MERGE SORT ================= */

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1, n2;

    n1 = m - l + 1;
    n2 = r - m;

    int L[10000], R[10000];  /* tamanho suficiente para o teste */

    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    int m;

    if(l < r) {
        m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

/* ================= FUNÇÃO DE TESTE ================= */

void testar(void (*func)(int[], int), int arr[], int n, char nome[]) {

    int i;
    int copia[10000];
    clock_t inicio, fim;
    double tempo;

    for(i = 0; i < n; i++)
        copia[i] = arr[i];

    inicio = clock();
    func(copia, n);
    fim = clock();

    tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;

    printf("\n%s executado em %.4f ms\n", nome, tempo);
}

/* ================= MAIN COM MENU ================= */

int main() {

    int tamanho = 1000;
    int arr[10000];
    int i;
    int opcao;

    srand(time(NULL));

    for(i = 0; i < tamanho; i++)
        arr[i] = rand() % 10000;

    do {

        printf("\n===== MENU =====\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Selection Sort\n");
        printf("3 - Insertion Sort\n");
        printf("4 - Quick Sort\n");
        printf("5 - Merge Sort\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                testar(bubbleSort, arr, tamanho, "Bubble Sort");
                break;

            case 2:
                testar(selectionSort, arr, tamanho, "Selection Sort");
                break;

            case 3:
                testar(insertionSort, arr, tamanho, "Insertion Sort");
                break;

            case 4: {
                int copia[10000];
                clock_t inicio, fim;
                double tempo;

                for(i = 0; i < tamanho; i++)
                    copia[i] = arr[i];

                inicio = clock();
                quickSort(copia, 0, tamanho - 1);
                fim = clock();

                tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
                printf("\nQuick Sort executado em %.4f ms\n", tempo);
                break;
            }

            case 5: {
                int copia[10000];
                clock_t inicio, fim;
                double tempo;

                for(i = 0; i < tamanho; i++)
                    copia[i] = arr[i];

                inicio = clock();
                mergeSort(copia, 0, tamanho - 1);
                fim = clock();

                tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
                printf("\nMerge Sort executado em %.4f ms\n", tempo);
                break;
            }

        }

    } while(opcao != 0);

    return 0;
}
