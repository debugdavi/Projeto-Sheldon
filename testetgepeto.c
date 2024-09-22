#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

enum Escolha { PEDRA = 1, PAPEL, TESOURA, LAGARTO, SPOCK };

// Função para capturar uma tecla sem pressionar Enter
char captura_tecla() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt); // Salva a configuração atual do terminal
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Desabilita o modo canônico e o eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Aplica as novas configurações
    ch = getchar(); // Captura a tecla
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaura as configurações antigas
    return ch;
}

// Traduz a tecla pressionada para uma escolha
int traduz_escolha(char tecla) {
    switch (tecla) {
        case 'q': case 'y': return PEDRA;
        case 'w': case 'u': return PAPEL;
        case 'e': case 'i': return TESOURA;
        case 'r': case 'o': return LAGARTO;
        case 't': case 'p': return SPOCK;
        default: return -1;
    }
}

int verifica_vencedor(int jogador1, int jogador2, int* pontos1, int* pontos2) {
    if (jogador1 == jogador2) {
        return 0; // Empate
    }
    if ((jogador1 == TESOURA && (jogador2 == PAPEL || jogador2 == LAGARTO)) ||
        (jogador1 == PAPEL && (jogador2 == PEDRA || jogador2 == SPOCK)) ||
        (jogador1 == PEDRA && (jogador2 == TESOURA || jogador2 == LAGARTO)) ||
        (jogador1 == LAGARTO && (jogador2 == SPOCK || jogador2 == PAPEL)) ||
        (jogador1 == SPOCK && (jogador2 == TESOURA || jogador2 == PEDRA))) {
        (*pontos1)++;
        return 1;
    } else {
        (*pontos2)++;
        return 2;
    }
}

void imprime_escolha(int escolha) {
    switch (escolha) {
        case PEDRA: printf("Pedra"); break;
        case PAPEL: printf("Papel"); break;
        case TESOURA: printf("Tesoura"); break;
        case LAGARTO: printf("Lagarto"); break;
        case SPOCK: printf("Spock"); break;
    }
}

void imprime_resultado(int resultado, int escolha1, int escolha2) {
    printf("Jogador 1 escolheu ");
    imprime_escolha(escolha1);
    printf(" e Jogador 2 escolheu ");
    imprime_escolha(escolha2);
    printf(".\n");

    if (resultado == 1) {
        printf("Jogador 1 venceu!\n");
    } else if (resultado == 2) {
        printf("Jogador 2 venceu!\n");
    } else {
        printf("Empate!\n");
    }
}

void imprime_mensagem_final(int pontos1, int pontos2) {
    if (pontos1 > pontos2) {
        printf("Jogador 1 ganhou o jogo!\n");
    } else if (pontos2 > pontos1) {
        printf("Jogador 2 ganhou o jogo!\n");
    } else {
        printf("O jogo terminou empatado!\n");
    }
}

int main() {
    int pontos1 = 0, pontos2 = 0, resultado, rodadas = 0;
    char tecla1, tecla2;

    srand(time(NULL));

    while (rodadas < 10) { // Jogo de 10 rodadas, por exemplo
        printf("Rodada %d\n", rodadas + 1);

        // Captura da tecla para o Jogador 1
        printf("Jogador 1 (q: Pedra, w: Papel, e: Tesoura, r: Lagarto, t: Spock): ");
        tecla1 = captura_tecla();
        printf("\n");

        // Captura da tecla para o Jogador 2
        printf("Jogador 2 (y: Pedra, u: Papel, i: Tesoura, o: Lagarto, p: Spock): ");
        tecla2 = captura_tecla();
        printf("\n");

        int escolha1 = traduz_escolha(tecla1);
        int escolha2 = traduz_escolha(tecla2);

        --------------------------------------
        if (escolha1 == -1 || escolha2 == -1) {
            printf("Uma escolha inválida foi feita. Tente novamente.\n");
            continue;  // Pula para a próxima iteração se houver erro
        }
        --------------------------------------
        
        resultado = verifica_vencedor(escolha1, escolha2, &pontos1, &pontos2);
        imprime_resultado(resultado, escolha1, escolha2);

        rodadas++;
    }

    imprime_mensagem_final(pontos1, pontos2);
    return 0;
}
