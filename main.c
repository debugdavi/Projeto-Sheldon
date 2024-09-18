#include <stdio.h>
#include <time.h> // Para usar time() e difftime()

enum Escolha { PEDRA = 1, PAPEL, TESOURA, LAGARTO, SPOCK };

int verificar_vencedor(int jogador1, int jogador2) {
    if (jogador1 == jogador2) return 0; // Empate
    if ((jogador1 == TESOURA && (jogador2 == PAPEL || jogador2 == LAGARTO)) ||
        (jogador1 == PAPEL && (jogador2 == PEDRA || jogador2 == SPOCK)) ||
        (jogador1 == PEDRA && (jogador2 == TESOURA || jogador2 == LAGARTO)) ||
        (jogador1 == LAGARTO && (jogador2 == SPOCK || jogador2 == PAPEL)) ||
        (jogador1 == SPOCK && (jogador2 == TESOURA || jogador2 == PEDRA))) {
        return 1; // Jogador 1 vence
    } else {
        return 2; // Jogador 2 vence
    }
}

int escolha_jogador() {
    int escolha;
    printf("Escolha: 1 = Pedra, 2 = Papel, 3 = Tesoura, 4 = Lagarto, 5 = Spock\n");
    printf("Faça sua escolha: ");
    scanf("%d", &escolha);
    return escolha;
}

int escolha_maquina() {
    return (rand() % 5) + 1; // Gera um número entre 1 e 5
}

void jogar_turno(int *pontos_jogador1, int *pontos_jogador2, int tempo_limite) {
    int jogador1, jogador2, vencedor;

    // Player 1 faz sua escolha
    jogador1 = escolha_jogador();
    
    // Player 2 ou máquina faz a escolha
    jogador2 = escolha_maquina();

    // Determina o vencedor
    vencedor = verificar_vencedor(jogador1, jogador2);

    // Atualiza o placar
    if (vencedor == 1) (*pontos_jogador1)++;
    else if (vencedor == 2) (*pontos_jogador2)++;
}


void contagem_regressiva(int segundos) {
    time_t inicio, agora;
    int restante = segundos;
    
    // Pegando o tempo atual
    time(&inicio);

    // Loop da contagem regressiva
    while (restante > 0) {
        time(&agora);  // Atualiza o tempo atual
        if (difftime(agora, inicio) >= 1.0) {  // Se passou 1 segundo
            inicio = agora;  // Atualiza o tempo de referência
            restante--;  // Decrementa o tempo restante
            printf("\rTempo restante: %d segundos", restante);  // \r para sobrescrever a linha
            fflush(stdout);  // Força a atualização imediata do buffer
        }
    }

    printf("\nTempo esgotado!\n");
}



int main() {
    int tempo = 5;
    
    
    return 0;
}
