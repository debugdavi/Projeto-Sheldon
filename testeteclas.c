#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

enum Escolha { PEDRA = 1, PAPEL, TESOURA, LAGARTO, SPOCK };

char captura_Tecla() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt); // Salva a configuração atual do terminal
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Desabilita o modo canônico e o eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Aplica as novas configurações

    fd_set set;
    struct timeval timeout;

    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    timeout.tv_sec = 5; // Tempo limite de 5 segundos para pressionar uma tecla
    timeout.tv_usec = 0;

    int rv = select(1, &set, NULL, NULL, &timeout);

    if(rv == 1) {
        ch = getchar(); // Captura a tecla
    } else {
        ch = -1; // Nenhuma tecla pressionada
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaura as configurações antigas
    return ch;
}

int traduz_Escolhaj1(char tecla) {
    switch (tecla) {
        case 'q': return PEDRA;
        case 'w': return PAPEL;
        case 'a': return TESOURA;
        case 's': return LAGARTO;
        case 'd': return SPOCK;
        default: return -2;
    }
}

int traduz_Escolhaj2(char tecla) {
    switch (tecla) {
        case 'u': return PEDRA;
        case 'i': return PAPEL;
        case 'j': return TESOURA;
        case 'k': return LAGARTO;
        case 'l': return SPOCK;
        default: return -2;
    }
}

void limpa_Buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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

void imprime_EscolhasJ1() {
    printf("Faça sua escolha, jogador 1:\n");
    printf("Q. Pedra\n");
    printf("W. Papel\n");
    printf("A. Tesoura\n");
    printf("S. Lagarto\n");
    printf("D. Spock\n");
}

void imprime_EscolhasJ2() {
    printf("Faça sua escolha, jogador 2:\n");
    printf("U. Pedra\n");
    printf("I. Papel\n");
    printf("J. Tesoura\n");
    printf("K. Lagarto\n");
    printf("L. Spock\n");
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

void pontua_Penalidade(int jogador1, int jogador2, int* pontos1, int* pontos2){
    if (jogador1 == -1 && jogador2 == -1) {
        printf("Os dois não digitaram uma tecla. Nenhum ganha ponto.\n");
    }
    else if (jogador1 == -2 && jogador2 == -2) {
        printf("Os dois apertaram teclas erradas. Nenhum ganha ponto.\n");
    }
    else {
        if (jogador1 == -1) {
            printf("PENALIDADE: Jogador 1 não digitou uma tecla. +1 para o adversário\n");
            (*pontos2)++;
        } else if (jogador1 == -2) {
            printf("PENALIDADE: Jogador 1 apertou a tecla errada. +1 para o adversário\n");
            (*pontos2)++;
        }

        if (jogador2 == -1) {
            printf("PENALIDADE: Jogador 2 não digitou uma tecla. +1 para o adversário\n");
            (*pontos1)++;
        } else if (jogador2 == -2) {
            printf("PENALIDADE: Jogador 2 apertou a tecla errada. +1 para o adversário\n");
            (*pontos1)++;
        }
    }
}

int main() {
    int jogador1, jogador2, escolha, resultado, contarodadas = 0, tempo=0;
    char teclaj1, teclaj2;
    int pontos1 = 0, pontos2 = 0, pontos_empate = 0;
    time_t inicio, fim;

    srand(time(NULL));
    limpa_tela();
    imprime_Pergunta();
    scanf("%d", &escolha);
    limpa_tela();
    escolha_Tempo(&tempo);
    limpa_tela();
    
    limpa_Buffer();
    if (escolha == 1) {
        time(&inicio);
        while (difftime(fim, inicio) < tempo) {
            printf("-----------------------------------------------------\n");
            printf("Rodada %d\n", contarodadas + 1);

            imprime_EscolhasJ1();
            teclaj1 = captura_Tecla();
            printf("Jogador 1 escolheu: %c\n", teclaj1); // Verificar o input
            printf("\n ");

            imprime_EscolhasJ2();
            teclaj2 = captura_Tecla();
            printf("Jogador 2 escolheu: %c\n", teclaj2); // Verificar o input
            printf("\n");

            jogador1 = traduz_Escolhaj1(teclaj1);
            jogador2 = traduz_Escolhaj2(teclaj2);


            printf("Jogador 1 retorno %d\n", jogador1); // Verificar o input
            printf("Jogador 2 retorno %d\n", jogador2); // Verificar o input

            
            if(jogador1 > 0 && jogador2 > 0){
                verifica_vencedor(jogador1, jogador2, &pontos1, &pontos2, &pontos_empate, contarodadas);
            }else{
                pontua_Penalidade(jogador1, jogador2, &pontos1, &pontos2);
            }
            
            time(&fim);

            contarodadas++;
        }
    } else if (escolha == 2) {
        limpa_tela();
        time(&inicio);

        while (difftime(fim, inicio) < 10) {
            printf("-----------------------------------------------------\n");
            printf("Rodada %d\n", contarodadas + 1);

            imprime_EscolhasJ1();
            teclaj1 = captura_Tecla();
            jogador1 = traduz_Escolhaj1(teclaj1);
            printf("\n");

            jogador2 = escolhe_maquina();

            
            if(jogador1 > 0 && jogador2 > 0){
                verifica_vencedor(jogador1, jogador2, &pontos1, &pontos2, &pontos_empate, contarodadas);
            }else{
                pontua_Penalidade(jogador1, jogador2, &pontos1, &pontos2);
            }

            time(&fim);

            contarodadas++;
        }

    } else {
        printf("Escolha uma opção válida!\n");
    }

    mensagem_Final(pontos1, pontos2, pontos_empate);
    printf("%d rodadas jogadas\n", contarodadas);

    return 0;
}
