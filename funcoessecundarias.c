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
