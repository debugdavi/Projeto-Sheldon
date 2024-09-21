#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // Para usar time() e difftime()
#include <unistd.h> // Para usar a função sleep()
#include <termios.h>

enum Escolha { PEDRA = 1, PAPEL, TESOURA, LAGARTO, SPOCK };

void mensagem_Rodada(int escolha1, int escolha2, int rodada, int vencedor, int pontos1, int pontos2) {
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
    case 1:
        if(pontos1 == 1)
            printf("Jogador 1: %d ponto (+1)\n", pontos1); 
        else
            printf("Jogador 1: %d pontos (+1)\n", pontos1); 
        if(pontos2 == 1)
            printf("Jogador 2: %d ponto\n", pontos2); 
        else
            printf("Jogador 2: %d pontos\n", pontos2); 
        break;
    case 2: 
        if(pontos1 == 1)
            printf("Jogador 1: %d ponto\n", pontos1); 
        else
            printf("Jogador 1: %d pontos\n", pontos1); 
        if(pontos2 == 1)
            printf("Jogador 2: %d ponto (+1)\n", pontos2); 
        else
            printf("Jogador 2: %d pontos (+1)\n", pontos2); 
        break;
    case 0: printf("Empate!\n"); break;
    }

    printf("\n");
}

int verifica_vencedor(int jogador1, int jogador2, int* pontos1, int* pontos2, int* pontos3, int rodadas) {
    int vencedor;
    if (jogador1 == jogador2) {
        (*pontos3)++;
        vencedor = 0;
        mensagem_Rodada(jogador1, jogador2, rodadas, vencedor, *pontos1, *pontos2);
        return 0; // Empate
    }
    if ((jogador1 == TESOURA && (jogador2 == PAPEL || jogador2 == LAGARTO)) ||
        (jogador1 == PAPEL && (jogador2 == PEDRA || jogador2 == SPOCK)) ||
        (jogador1 == PEDRA && (jogador2 == TESOURA || jogador2 == LAGARTO)) ||
        (jogador1 == LAGARTO && (jogador2 == SPOCK || jogador2 == PAPEL)) ||
        (jogador1 == SPOCK && (jogador2 == TESOURA || jogador2 == PEDRA))) {
        (*pontos1)++; // Jogador 1 vence, incrementa pontos
        vencedor = 1;
        mensagem_Rodada(jogador1, jogador2, rodadas, vencedor, *pontos1, *pontos2);
        return 1;
    } else {
        (*pontos2)++; // Jogador 2 vence, incrementa pontos
        vencedor = 2;
        mensagem_Rodada(jogador1, jogador2, rodadas, vencedor, *pontos1, *pontos2);
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

void mensagem_Final(int pontos1, int pontos2, int pontos_Empate) {
    printf("FIM DA PARTIDA!\n");
    if (pontos1 > pontos2) {
        if (pontos1 == 1)
            printf("JOGADOR 1: YOU WIN! 🏆 (%d ponto)\n", pontos1);
        else   
            printf("JOGADOR 1: YOU WIN! 🏆 (%d pontos)\n", pontos1);
        if (pontos2 == 1)
            printf("JOGADOR 2: YOU LOSE! ❌ (%d ponto)\n", pontos2);
        else
            printf("JOGADOR 2: YOU LOSE! ❌ (%d pontos)\n", pontos2);
    } else if (pontos2 > pontos1) {
        if (pontos2 == 1)
            printf("JOGADOR 2: YOU WIN! 🏆 (%d ponto)\n", pontos2);
        else
            printf("JOGADOR 2: YOU WIN! 🏆 (%d pontos)\n", pontos2);
        if (pontos1 == 1)
            printf("JOGADOR 1: YOU LOSE! ❌ (%d ponto)\n", pontos1);
        else   
            printf("JOGADOR 1: YOU LOSE! ❌ (%d pontos)\n", pontos1);
    } else {
        if(pontos1 >= 1 && pontos2 >= 1)
            if(pontos1 == 1 || pontos2 == 1)
                printf("EMPATE! 🏳️  (%d ponto pra cada)\n", pontos1);
            else
                printf("EMPATE! 🏳️  (%d pontos pra cada)\n", pontos1);
        else {
            printf("EMPATE! 🏳️\n");
        }
    }
    if(pontos_Empate == 1)
        printf("%d Ponto de Empate\n", pontos_Empate);
    else
        printf("%d Pontos de Empate\n", pontos_Empate);
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

void escolha_Tempo(int *Tempo){
    int TempoEscolhido=0;
    printf("Escolha o tempo da partida:\n");
    printf("1. 30s\n");
    printf("2. 45s\n");
    printf("3. 60s\n");
    while (TempoEscolhido > 3 || TempoEscolhido < 1) {
        scanf("%d", &TempoEscolhido);
        switch (TempoEscolhido) {
        case 1: *Tempo = 5; break; //MUDAR DEPOIS
        case 2: *Tempo = 45; break;
        case 3: *Tempo = 60; break;
        default: printf("Escolha uma opção válida\n"); break;
        }
    }
}

int main() {
    int jogador1, jogador2, escolha, resultado, contarodadas = 0, tempo=0;
    int pontos1 = 0, pontos2 = 0, pontos_empate = 0;
    time_t inicio, fim;

    srand(time(NULL));
    limpa_tela();
    imprime_Pergunta();
    scanf("%d", &escolha);
    limpa_tela();
    escolha_Tempo(&tempo);
    limpa_tela();
    
    if (escolha == 1) {
        time(&inicio);
        desativar_echo();

        while (difftime(fim, inicio) < tempo) {
            printf("Rodada %d\n", contarodadas + 1);
            imprime_Escolhas("jogador 1");
            scanf("%d", &jogador1);
            printf("\n");
            imprime_Escolhas("jogador 2");
            scanf("%d", &jogador2);
            printf("\n");
            verifica_vencedor(jogador1, jogador2, &pontos1, &pontos2, &pontos_empate, contarodadas);
            time(&fim);

            contarodadas++;
            if (tempo - difftime(fim, inicio) > 0) {
                printf("Tempo restante: %d segundos\n", (int)(tempo - difftime(fim, inicio)));
                printf("\n");
            }
        }
        mensagem_Final(pontos1, pontos2, pontos_empate);
        printf("%d Rodadas Jogadas\n", contarodadas);
        ativar_echo();

    } else if (escolha == 2) {
        limpa_tela();
        time(&inicio);

        while (difftime(fim, inicio) < 10) {
            imprime_Escolhas("jogador 1");
            scanf("%d", &jogador1);
            printf("\n");
            jogador2 = escolhe_maquina();

            verifica_vencedor(jogador1, jogador2, &pontos1, &pontos2, &pontos_empate, contarodadas);
            time(&fim);

            contarodadas++;
        }
        mensagem_Final(pontos1, pontos2, pontos_empate);
        printf("%d rodadas jogadas\n", contarodadas);

    } else {
        printf("Escolha uma opção válida!\n");
    }

    return 0;
}
