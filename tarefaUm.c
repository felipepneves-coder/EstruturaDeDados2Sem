#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void *a, const void *b) {
    return (*(double*)a - *(double*)b);
}

int main() {
    int N;
    printf("Quantos números na sua série (N): ");
    scanf("%d", &N);

    double *valores = malloc(N * sizeof(double));
    if (valores == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    printf("Entre com os números:\n");
    for (int i = 0; i < N; i++) {
        printf("> ");
        scanf("%lf", &valores[i]);
    }

    double max = valores[0], min = valores[0], soma = 0.0;
    for (int i = 0; i < N; i++) {
        if (valores[i] > max) max = valores[i];
        if (valores[i] < min) min = valores[i];
        soma += valores[i];
    }

    double media = soma / N;
    qsort(valores, N, sizeof(double), compare);

    double mediana;
    if (N % 2 == 0) {
        mediana = (valores[N/2 - 1] + valores[N/2]) / 2.0;
    } else {
        mediana = valores[N/2];
    }

    double soma_diferencas_quadrado = 0.0;
    for (int i = 0; i < N; i++) {
        soma_diferencas_quadrado += pow(valores[i] - media, 2);
    }
    double desvio_padrao = sqrt(soma_diferencas_quadrado / N);

    printf("Valor mínimo: %.2lf\n", min);
    printf("Valor máximo: %.2lf\n", max);
    printf("Média: %.2lf\n", media);
    printf("Mediana: %.2lf\n", mediana);
    printf("Desvio padrão: %.14lf\n", desvio_padrao);

    free(valores);

    return 0;
}
