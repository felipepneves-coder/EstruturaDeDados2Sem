#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

// Estrutura para um nó da ABB
typedef struct NO {
    char nome[MAX_LINE];
    char cargo[MAX_LINE];
    char uorg_lotacao[MAX_LINE];
    struct NO *esq;
    struct NO *dir;
} NO;

// Função para criar um novo nó
NO *criaNo(char *nome, char *cargo, char *uorg_lotacao) {
    NO *novoNo = (NO *)malloc(sizeof(NO));
    if (!novoNo) {
        printf("Erro ao alocar memória para o nó.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(novoNo->nome, nome);
    strcpy(novoNo->cargo, cargo);
    strcpy(novoNo->uorg_lotacao, uorg_lotacao);
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

// Função para inserir um nó na ABB
NO *insereNo(NO *raiz, char *nome, char *cargo, char *uorg_lotacao) {
    if (raiz == NULL) {
        return criaNo(nome, cargo, uorg_lotacao);
    }
    if (strcmp(nome, raiz->nome) < 0) {
        raiz->esq = insereNo(raiz->esq, nome, cargo, uorg_lotacao);
    } else if (strcmp(nome, raiz->nome) > 0) {
        raiz->dir = insereNo(raiz->dir, nome, cargo, uorg_lotacao);
    }
    return raiz;
}

// Função para buscar um nó na ABB
NO *busca(NO *raiz, char *nome) {
    if (raiz == NULL || strcmp(nome, raiz->nome) == 0) {
        return raiz;
    }
    if (strcmp(nome, raiz->nome) < 0) {
        return busca(raiz->esq, nome);
    } else {
        return busca(raiz->dir, nome);
    }
}

// Função para liberar memória da ABB
void liberaArvore(NO *raiz) {
    if (raiz != NULL) {
        liberaArvore(raiz->esq);
        liberaArvore(raiz->dir);
        free(raiz);
    }
}

// Função para remover o caractere de nova linha
void removeNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main() {
    FILE *file;
    char line[MAX_LINE];
    NO *raiz = NULL;

    // Abrir o arquivo CSV
    file = fopen("Unifesp-24r.csv", "r");
    if (!file) {
        perror("Erro ao abrir o arquivo CSV");
        return EXIT_FAILURE;
    }

    // Ler o cabeçalho
    if (fgets(line, MAX_LINE, file) == NULL) {
        fprintf(stderr, "Arquivo CSV vazio ou inválido.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Ler as linhas do arquivo CSV e inserir na ABB
    while (fgets(line, MAX_LINE, file)) {
        char *nome, *cargo, *uorg_lotacao;
        char *token = strtok(line, ",");

        // Extrair os campos relevantes
        nome = token;
        token = strtok(NULL, ",");
        cargo = token;
        token = strtok(NULL, ",");
        uorg_lotacao = token;

        // Remover nova linha dos campos
        removeNovaLinha(nome);
        removeNovaLinha(cargo);
        removeNovaLinha(uorg_lotacao);

        // Inserir na ABB
        raiz = insereNo(raiz, nome, cargo, uorg_lotacao);
    }

    fclose(file);

    // Solicitar nome para busca
    char nomeBusca[MAX_LINE];
    printf("Digite o nome completo para buscar: ");
    fgets(nomeBusca, MAX_LINE, stdin);
    removeNovaLinha(nomeBusca);

    // Realizar a busca na ABB
    NO *resultado = busca(raiz, nomeBusca);

    if (resultado) {
        printf("\nRegistro encontrado:\n");
        printf("Nome: %s\n", resultado->nome);
        printf("Cargo: %s\n", resultado->cargo);
        printf("UORG_LOTACAO: %s\n", resultado->uorg_lotacao);
    } else {
        printf("\nNenhum registro encontrado para o nome: %s\n", nomeBusca);
    }

    // Liberar a memória da ABB
    liberaArvore(raiz);

    return 0;
}
