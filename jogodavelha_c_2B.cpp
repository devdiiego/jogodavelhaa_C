#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/* Jogo da Velha. Projeto para TÃ©cnicas e Desenvolvimento de Algoritmos */

// Estrutura para armazenar os dados de cada jogador
struct Jogador {
    char nome[50];   // Nome do jogador
    int vitorias;    // Número de vitórias do jogador
};

// Função para ler um número inteiro e garantir que a entrada seja válida
int lerNumero() {
    int numero;
    while (scanf("%d", &numero) != 1) {  // Verifica se a entrada é um número
        printf("\nOpção Inválida! Digite um número: \n ");
        while (getchar() != '\n');  // Limpa o buffer
    }
    return numero;  // Retorna o número inserido
}

// Função para exibir o tabuleiro do jogo
void exibirTabuleiro(char **jogo) {
    // Loop para percorrer as linhas e colunas do tabuleiro
    for (int l = 0; l < 3; l++) {
        for (int c = 0; c < 3; c++) {
            if (c == 0) printf("\t");  // Adiciona espaçamento à esquerda
            printf(" %c ", jogo[l][c]);  // Exibe a célula atual
            if (c < 2) printf("|");  // Exibe o separador entre as colunas
        }
        if (l < 2) printf("\n\t-----------\n");  // Adiciona separador entre as linhas
        else printf("\n");
    }
}

// Função para verificar se há um vencedor
int verificarVencedor(char **jogo) {
    // Verifica se algum jogador venceu em linhas, colunas ou diagonais
    for (int i = 0; i < 3; i++) {
        if ((jogo[i][0] == jogo[i][1] && jogo[i][1] == jogo[i][2] && jogo[i][0] != ' ') ||
            (jogo[0][i] == jogo[1][i] && jogo[1][i] == jogo[2][i] && jogo[0][i] != ' ')) {
            return 1;  // Retorna 1 se houver um vencedor
        }
    }

    // Verifica as duas diagonais
    if ((jogo[0][0] == jogo[1][1] && jogo[1][1] == jogo[2][2] && jogo[0][0] != ' ') ||
        (jogo[0][2] == jogo[1][1] && jogo[1][1] == jogo[2][0] && jogo[0][2] != ' ')) {
        return 1;  // Retorna 1 se houver um vencedor
    }

    return 0;  // Retorna 0 se não houver vencedor
}

// Função para verificar se o jogo deu velha
int jogoVelha(char **jogo) {
    // Verifica se todas as células estão preenchidas
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (jogo[i][j] == ' ') return 0;  // Se houver célula vazia, o jogo não terminou
        }
    }
    return 1;  // Se não houver células vazias, deu velha
}

// Função para salvar o ranking em arquivo
void salvarRanking(struct Jogador jogadores[2]) {
    FILE *arquivo = fopen("ranking.txt", "a");  // Abre o arquivo em modo append
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de ranking!\n");
        return;
    }

    // Grava as vitórias de cada jogador no arquivo
    fprintf(arquivo, "%s: %d vitórias\n", jogadores[0].nome, jogadores[0].vitorias);
    fprintf(arquivo, "%s: %d vitórias\n", jogadores[1].nome, jogadores[1].vitorias);
    fclose(arquivo);  // Fecha o arquivo
}

// Função para mostrar o ranking
void mostrarRanking() {
    FILE *arquivo = fopen("ranking.txt", "r");  // Abre o arquivo em modo leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de ranking!\n");
        return;
    }

    char linha[100];
    printf("\nRanking:\n");
    // Lê o arquivo linha por linha e exibe
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }
    fclose(arquivo);  // Fecha o arquivo
}

// Função para exibir os créditos
void exibirCreditos() {
    printf("\n\t\t\t\tCREDITOS\n\n");
    printf("\n\tDesenvolvido por Diego Feitosa, Alex Dantas, José Kleyton e Handrey Kaleu.\n");
    printf("\n\tAlunos do UNIPÊ - Ciência da Computação\n");
    printf("\n\tTurma: Técnicas e Desenvolvimento de Algoritmos - 2B 2024.2\n\n");
}

int main() {
    setlocale(LC_ALL, "portuguese");  // Define o idioma como português

    struct Jogador jogadores[2];  // Array de jogadores
    int numero, jogador, linha, coluna, ganhou, jogadas;
    char **jogo;
    int loop = 1;

    // Aloca memória dinamicamente para a matriz jogo
    jogo = (char **)malloc(3 * sizeof(char *));
    for (int i = 0; i < 3; i++) {
        jogo[i] = (char *)malloc(3 * sizeof(char));
    }

    while (loop == 1) {
        system("cls");  // Limpa a tela
        printf("\n\tJOGO DA VELHA\n\n");
        printf("1 - JOGAR\n");
        printf("2 - VER RANKING\n");
        printf("3 - CRÉDITOS\n");
        printf("4 - SAIR\n\n");
        printf("Digite a opção desejada: ");
        numero = lerNumero();  // Lê a opção escolhida

        switch (numero) {
            case 1: {
                printf("\nDigite o nome do jogador 1 (apenas 1 nome): ");
                scanf("%s", jogadores[0].nome);

                printf("\nDigite o nome do jogador 2 (apenas 1 nome): ");
                scanf("%s", jogadores[1].nome);

                jogador = 1;
                ganhou = 0;
                jogadas = 0;
                // Inicializa a matriz do tabuleiro
                for (int l = 0; l < 3; l++) {
                    for (int c = 0; c < 3; c++) {
                        jogo[l][c] = ' ';  // Preenche todas as células com espaço
                    }
                }

                do {
                    exibirTabuleiro(jogo);  // Exibe o tabuleiro

                    if (jogador == 1) {
                        printf("\nJOGADOR 1 (%s) = o\nJOGADOR 2 (%s) = x\n", jogadores[0].nome, jogadores[1].nome);
                        printf("\nJOGADOR 1: Digite a linha e a coluna (0 a 2): ");
                    } else {
                        printf("\nJOGADOR 1 (%s) = o\nJOGADOR 2 (%s) = x\n", jogadores[0].nome, jogadores[1].nome);
                        printf("\nJOGADOR 2: Digite a linha e a coluna (0 a 2): ");
                    }

                    // Loop para garantir que a jogada seja válida
                    do {
                        if (scanf("%d %d", &linha, &coluna) != 2 || linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || jogo[linha][coluna] != ' ') {
                            printf("\nEntrada inválida! Certifique-se de que a linha e a coluna estão entre 0 e 2, e a célula está vazia.\n");
                            while (getchar() != '\n');  // Limpar o buffer
                        } else {
                            break;  // Jogada válida
                        }
                    } while (1);

                    // Realiza a jogada do jogador
                    if (jogador == 1) {
                        jogo[linha][coluna] = 'o';  // Jogador 1 joga com 'o'
                        jogador = 2;  // Passa a vez para o jogador 2
                    } else {
                        jogo[linha][coluna] = 'x';  // Jogador 2 joga com 'x'
                        jogador = 1;  // Passa a vez para o jogador 1
                    }
                    jogadas++;

                    // Verifica se algum jogador venceu
                    if (verificarVencedor(jogo)) {
                        exibirTabuleiro(jogo);  // Exibe o tabuleiro
                        if (jogador == 2) {
                            printf("\nO jogador 1 (%s) venceu!\n", jogadores[0].nome);
                            jogadores[0].vitorias++;  // Incrementa a vitória do jogador 1
                        } else {
                            printf("\nO jogador 2 (%s) venceu!\n", jogadores[1].nome);
                            jogadores[1].vitorias++;  // Incrementa a vitória do jogador 2
                        }
                        ganhou = 1;  // Jogo terminado
                    }

                    // Verifica se deu velha
                    if (jogoVelha(jogo)) {
                        exibirTabuleiro(jogo);
                        printf("\nO jogo terminou em velha!\n");
                        ganhou = 1;  // Jogo terminou em velha
                    }

                } while (!ganhou);  // Continua enquanto ninguém venceu ou deu velha

                salvarRanking(jogadores);  // Salva o ranking
                break;
            }
            case 2:
                mostrarRanking();  // Exibe o ranking
                break;
            case 3:
                exibirCreditos();  // Exibe os créditos
                break;
            case 4:
                printf("\nSaindo do jogo...\n");
                loop = 0;  // Sai do loop
                break;
            default:
                printf("\nOpção Inválida!\n");  // Caso o usuário digite uma opção inválida
                break;
        }

        // Pergunta se o usuário deseja voltar ao menu ou sair
        if (loop != 0) {
            printf("\nDigite '1' para voltar ao menu, ou '0' para sair do jogo.\n");
            loop = lerNumero();  // Lê a opção
        }
    }

    // Libera a memória alocada para o tabuleiro
    for (int i = 0; i < 3; i++) {
        free(jogo[i]);  // Libera cada linha do tabuleiro
    }
    free(jogo);  // Libera a memória da matriz de jogo

    return 0;
}
