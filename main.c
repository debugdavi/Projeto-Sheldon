#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // Para usar time() e difftime()
#include <unistd.h> // Para usar a função sleep()
#include <termios.h>

enum Escolha { PEDRA = 1, PAPEL, TESOURA, LAGARTO, SPOCK };

void mensagem_Rodada(int escolha1, int escolha2, int rodada, int vencedor) {
    printf("RODADA %d:\n", rodada+1);
    switch(escolha1){
        case 1: printf("PEDRA x "); break;
        case 2: printf("PAPEL x "); break;
        case 3: printf("TESOURA x "); break;
        case 4: printf("LAGARTO x "); break;
        case 5: printf("SPOCK x "); break;
    }
    switch(escolha2){
        case 1: printf("PEDRA\n"); break;
        case 2: printf("PAPEL\n"); break;
        case 3: printf("TESOURA\n"); break;
        case 4: printf("LAGARTO\n"); break;
        case 5: printf("SPOCK\n"); break;
    }

    switch (vencedor) {
    case 1: printf("Jogador 1 marcou um ponto nessa rodada!\n"); break;
    case 2: printf("Jogador 2 marcou um ponto nessa rodada!\n"); break;
    case 0: printf("Empate!\n"); break;
    }

    printf("\n");
}

int verifica_vencedor(int jogador1, int jogador2, int* pontos1, int* pontos2, int rodadas) {
    int vencedor;
    if (jogador1 == jogador2) {
        vencedor = 0;
        mensagem_Rodada(jogador1, jogador2, rodadas, vencedor);
        return 0; // Empate
    }
    if ((jogador1 == TESOURA && (jogador2 == PAPEL || jogador2 == LAGARTO)) ||
        (jogador1 == PAPEL && (jogador2 == PEDRA || jogador2 == SPOCK)) ||
        (jogador1 == PEDRA && (jogador2 == TESOURA || jogador2 == LAGARTO)) ||
        (jogador1 == LAGARTO && (jogador2 == SPOCK || jogador2 == PAPEL)) ||
        (jogador1 == SPOCK && (jogador2 == TESOURA || jogador2 == PEDRA))) {
        (*pontos1)++; // Jogador 1 vence, incrementa pontos
        vencedor = 1;
        mensagem_Rodada(jogador1, jogador2, rodadas, vencedor);
        return 1;
    } else {
        (*pontos2)++; // Jogador 2 vence, incrementa pontos
        vencedor = 2;
        mensagem_Rodada(jogador1, jogador2, rodadas, vencedor);
        return 2;
    }
}

int escolhe_maquina() {
    return (rand() % 5) + 1;
}

void imprime_Pergunta() {
    printf("Escolha um adversário:\n");
    printf("1. Player 2\n");
    printf("2. Computador\n");
}

void imprime_Escolhas(const char* jogador) {
    printf("Faça sua escolha, %s:\n", jogador);
    printf("1. Pedra\n");
    printf("2. Papel\n");
    printf("3. Tesoura\n");
    printf("4. Lagarto\n");
    printf("5. Spock\n");
}

void mensagem_Final(int pontos1, int pontos2) {
    printf("FIM DA PARTIDA!\n");
    if (pontos1 > pontos2) {
        printf("JOGADOR 1: YOU WIN! 🏆 (%d pontos)\n", pontos1);
        printf("JOGADOR 2: YOU LOSE! ❌ (%d pontos)\n", pontos2);
    } else if (pontos2 > pontos1) {
        printf("JOGADOR 2: YOU WIN! 🏆 (%d pontos)\n", pontos2);
        printf("JOGADOR 1: YOU LOSE! ❌ (%d pontos)\n", pontos1);
    } else {
        printf("EMPATE! 🏳️\n");
        printf("Ambos fizeram %d pontos\n", pontos1);
    }
}

void limpa_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void desativar_echo() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void ativar_echo() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int main() {
    int jogador1, jogador2, escolha, resultado, contarodadas = 0;
    int pontos1 = 0, pontos2 = 0;
    time_t inicio, fim;

    srand(time(NULL));
    limpa_tela();
    imprime_Pergunta();
    scanf("%d", &escolha);
    limpa_tela();
    
    if (escolha == 1) {
        time(&inicio);
        
    desativar_echo();

        while (difftime(fim, inicio) < 10) { // Por exemplo, jogo de 10 segundos
            printf("Rodada %d\n", contarodadas + 1);
            imprime_Escolhas("jogador 1");
            scanf("%d", &jogador1);
            printf("\n");
            imprime_Escolhas("jogador 2");
            scanf("%d", &jogador2);
            printf("\n");
            verifica_vencedor(jogador1, jogador2, &pontos1, &pontos2, contarodadas);
            time(&fim);

            contarodadas++;
        }
        mensagem_Final(pontos1, pontos2);
        printf("%d rodadas jogadas\n", contarodadas);

    } else if (escolha == 2) {
        limpa_tela();
        time(&inicio);

        while (difftime(fim, inicio) < 10) {
            imprime_Escolhas("jogador 1");
            scanf("%d", &jogador1);
            printf("\n");
            jogador2 = escolhe_maquina();

            verifica_vencedor(jogador1, jogador2, &pontos1, &pontos2, contarodadas);
            time(&fim);

            contarodadas++;
        }
        mensagem_Final(pontos1, pontos2);
        printf("%d rodadas jogadas\n", contarodadas);

    } else {
        printf("Escolha uma opção válida!\n");
    }

    return 0;
}
