#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // Para usar time() e difftime()
#include <unistd.h> // Para usar a função sleep()

enum Escolha { PEDRA = 1, PAPEL, TESOURA, LAGARTO, SPOCK };

void mensagem_Rodada(int escolha1, int escolha2) {
    switch(escolha1){
        case 1: printf("PEDRA x ");
        case 2: printf("PAPEL x ");
        case 3: printf("TESOURA x ");
        case 4: printf("LAGARTO x ");
        case 5: printf("SPOCK x ");
    }
    switch(escolha2){
        case 1: printf("PEDRA\n");
        case 2: printf("PAPEL\n");
        case 3: printf("TESOURA\n");
        case 4: printf("LAGARTO\n");
        case 5: printf("SPOCK\n");
    }

    printf("Jogador 1 marcou um ponto nessa rodada!\n");
}

int verifica_vencedor(int jogador1, int jogador2, int* pontos1, int* pontos2) {
    if (jogador1 == jogador2) {
        mensagem_Rodada(jogador1, jogador2);
        return 0; // Empate
    }
    if ((jogador1 == TESOURA && (jogador2 == PAPEL || jogador2 == LAGARTO)) ||
        (jogador1 == PAPEL && (jogador2 == PEDRA || jogador2 == SPOCK)) ||
        (jogador1 == PEDRA && (jogador2 == TESOURA || jogador2 == LAGARTO)) ||
        (jogador1 == LAGARTO && (jogador2 == SPOCK || jogador2 == PAPEL)) ||
        (jogador1 == SPOCK && (jogador2 == TESOURA || jogador2 == PEDRA))) {
        (*pontos1)++; // Jogador 1 vence, incrementa pontos
        mensagem_Rodada(jogador1, jogador2);
        return 1;
    } else {
        (*pontos2)++; // Jogador 2 vence, incrementa pontos
        mensagem_Rodada(jogador1, jogador2);
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

void imprime_Mensagem(const char* vencedor, const char* perdedor) {
    printf("%s, YOU WIN! 🏆\n", vencedor);
    printf("%s, YOU LOSE! ❌\n", perdedor);
}

void mensagem_Final(int pontos1, int pontos2) {
    if (pontos1 > pontos2) {
        imprime_Mensagem("JOGADOR 1", "JOGADOR 2");
    } else if (pontos2 > pontos1) {
        imprime_Mensagem("JOGADOR 2", "JOGADOR 1");
    } else {
        printf("EMPATE! 🏳️\n");
    }

    if (pontos1 != pontos2) {
        printf("Jogador 1: %d pontos\n", pontos1);
        printf("Jogador 2: %d pontos\n", pontos2);
    } else {
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

void pause_para_continuar() {
    printf("Pressione qualquer tecla para continuar...\n");
    getchar();  // Captura o enter pendente do scanf
    getchar();  // Aguarda o usuário pressionar qualquer tecla
}

int main() {
    int jogador1, jogador2, escolha, resultado, contarodadas = 0;
    int pontos1 = 0, pontos2 = 0;
    time_t inicio, fim;

    srand(time(NULL));

    imprime_Pergunta();
    scanf("%d", &escolha);

    if (escolha == 1) {
        time(&inicio);
        while (difftime(fim, inicio) < 10) { // Por exemplo, jogo de 10 segundos
            limpa_tela();
            printf("Rodada %d\n", contarodadas + 1);
            imprime_Escolhas("jogador 1");
            scanf("%d", &jogador1);
            limpa_tela();
            printf("Rodada %d\n", contarodadas + 1);
            imprime_Escolhas("jogador 2");
            scanf("%d", &jogador2);
            limpa_tela();

            verifica_vencedor(jogador1, jogador2, &pontos1, &pontos2);
            time(&fim);

            contarodadas++;
        }
        limpa_tela();
        mensagem_Final(pontos1, pontos2);
        printf("%d rodadas jogadas\n", contarodadas);

    } else if (escolha == 2) {
        limpa_tela();
        time(&inicio);
        while (difftime(fim, inicio) < 10) { // Jogo contra a máquina
            imprime_Escolhas("jogador 1");
            scanf("%d", &jogador1);
            limpa_tela();
            jogador2 = escolhe_maquina();
            resultado = verifica_vencedor(jogador1, jogador2, &pontos1, &pontos2);
            mensagem_Final(pontos1, pontos2);  // Corrigido para usar pontos1 e pontos2
            time(&fim);

            contarodadas++;

            pause_para_continuar();  // Pausa o jogo para aguardar input
        }
        mensagem_Final(pontos1, pontos2);
        printf("%d rodadas jogadas\n", contarodadas);

    } else {
        printf("Escolha uma opção válida!\n");
    }

    return 0;
}
