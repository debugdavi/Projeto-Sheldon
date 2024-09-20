#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para usar time() e difftime()
#include <unistd.h> // Para usar a função sleep()

enum Escolha { PEDRA = 1, PAPEL, TESOURA, LAGARTO, SPOCK };

int verifica_vencedor(int jogador1, int jogador2) {
    if (jogador1 == jogador2) {
        return 0; // Empate
    }
    if ((jogador1 == TESOURA && (jogador2 == PAPEL || jogador2 == LAGARTO)) ||
        (jogador1 == PAPEL && (jogador2 == PEDRA || jogador2 == SPOCK)) ||
        (jogador1 == PEDRA && (jogador2 == TESOURA || jogador2 == LAGARTO)) ||
        (jogador1 == LAGARTO && (jogador2 == SPOCK || jogador2 == PAPEL)) ||
        (jogador1 == SPOCK && (jogador2 == TESOURA || jogador2 == PEDRA))) {
        return 1; // J1 vence
    } else {
        return 2; // J2 vence
    }
}

int escolhe_maquina() {
    return (rand() % 5) + 1;
}

void imprime_Pergunta(){
    printf("Escolha um adversário:\n");
    printf("1. Player 2\n");
    printf("2. Computador\n");
}

void imprime_Escolhas(char* jogador){
    printf("Faça sua escolha, %s:\n", jogador);
    printf("1. Pedra\n");
    printf("2. Papel\n");
    printf("3. Tesoura\n");
    printf("4. Lagarto\n");
    printf("5. Spock\n");
}

void imprime_Mensagem(char* vencedor, char* perdedor){
    printf("%s, YOU WIN! 🏆\n", vencedor);
    printf("%s, YOU LOSE! ❌\n", perdedor);
}

void mensagem_Vencedor(int codigoVencedor){
    if(codigoVencedor == 1){
        imprime_Mensagem("JOGADOR 1", "JOGADOR 2");
    }else if(codigoVencedor == 2){
        imprime_Mensagem("JOGADOR 2", "JOGADOR 1");
    }else{
        printf("EMPATE! 🏳️\n");
    }
}

void mensagem_Final(int Vencedor){
    if (Vencedor == 1)
        printf("Jogador 1 ganhou a rodada com %d pontos");
    else if (Vencedor == 2)
        printf("Jogador 2 ganhou a rodada com %d pontos");
    else
        printf("Empate! Os 2 jogadores fizeram %d pontos");
}

void limpa_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    int jogador1, jogador2, escolha, auxiliarverifica;
    int* pontos1, pontos2;
    time_t inicio, fim;
    srand(time(NULL));

    imprime_Pergunta();
    scanf("%d", &escolha);
    
    if(escolha == 1){
        time(&inicio);
        while(difftime(fim, inicio) < 5) {
            limpa_tela();
            imprime_Escolhas("jogador 1");
            scanf("%d", &jogador1);
            limpa_tela();
            imprime_Escolhas("jogador 2");
            scanf("%d", &jogador2);
            limpa_tela();

            auxiliarverifica = verifica_vencedor(jogador1, jogador2);
            if
            mensagem_Vencedor(auxiliarverifica);
            time(&fim);
        }
        mensagem_Final(verifica_vencedor(jogador1, jogador2));

    } else if(escolha == 2){
        limpa_tela();
        imprime_Escolhas("jogador 1");
        scanf("%d", &jogador1);
        limpa_tela();
        jogador2 = escolhe_maquina();
        mensagem_Vencedor(verifica_vencedor(jogador1, jogador2));

    } else{
        printf("Escolha uma opção válida!\n");
    }

    
    return 0;
}
