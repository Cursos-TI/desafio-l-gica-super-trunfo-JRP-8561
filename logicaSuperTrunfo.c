/*Este é o desafio super trunfo nível mestre, desenvolvido por Juliana Rodrigues Procópio
Procurei conhecer novas opções de comandos, loops para uma codificação mais limpa e tratativas de erros

ETAPAS:

1- Declaração de variáveis
2- Imput de dados para as cartas
    a- incluí a opção de input de dados manual ou aleatório para melhorar os testes do jogo e aumentar agilidade (Responda 1 ou 2)
    b- incluí tratativa de erros para imput de dados não aceitáveis pelo sistema
    c- Incluí a possibilidade de cadastro de vários países sob escolha do usuário (Deseja cadastrar outro pais? Responda Y/N)
3- Saída de dados: Código PAIS_ESTADO e cidade conforme instrução.
    a- todas as propriedades cadastradas são apresentadas
    b- propriendades calculadas são exibidas
4- Jogo com dois jogadores:
    a- Cada jogador coloca seu nome
    b- O código de todas as cartas cadastradas aparecem para escolha do jogador
    c- A partir das cartas escolhidas, é calculado o super poder
    d- Exibido o resultado da carta com maior super poder e o nome do vencedor!
*/

//Declaração de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Imput de variáveis com as propriedades de uma cidade
typedef struct {
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
} Cidade;

// Declaração de codigo para cada carta de cidade
typedef struct {
    char codigo[20];
    Cidade propriedades;
} Carta;

// Função para calcular as propriedades de desnidade populacional e pib per capita
void calcular_propriedades(Carta *carta) {
    carta->propriedades.densidade_populacional = carta->propriedades.populacao / carta->propriedades.area;
    carta->propriedades.pib_per_capita = carta->propriedades.pib / carta->propriedades.populacao;
}

// Verifica se a entrada de valores é correta. Se não, exibe mensagem e pede correção ao usuário

// Função para validar entrada inteira
int ler_inteiro(const char *mensagem, int min, int max) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1 && valor >= min && valor <= max) {
            return valor;
        } else {
            printf("Entrada inválida. Por favor, insira um número entre %d e %d.\n", min, max);
            while (getchar() != '\n'); // Limpa o buffer
        }
    }
}

// Função para validar entrada float
float ler_float(const char *mensagem, float min, float max) {
    float valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%f", &valor) == 1 && valor >= min && valor <= max) {
            return valor;
        } else {
            printf("Entrada inválida. Por favor, insira um número entre %.2f e %.2f.\n", min, max);
            while (getchar() != '\n'); // Limpa o buffer
        }
    }
}

// Função para validar entrada char
char ler_char(const char *mensagem, const char *opcoes) {
    char valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf(" %c", &valor) == 1 && strchr(opcoes, valor)) {
            return valor;
        } else {
            printf("Entrada inválida. Por favor, insira uma das seguintes opções: %s\n", opcoes);
            while (getchar() != '\n'); // Limpa o buffer
        }
    }
}

// Função para cadastrar cidades manualmente
void cadastrar_cidade_manual(Carta *carta) {
    printf("\nInserir propriedades para a carta %s:\n", carta->codigo);

    carta->propriedades.populacao = ler_inteiro("População: ", 1000, 100000000);
    carta->propriedades.area = ler_float("Área (km2): ", 1, 100000);
    carta->propriedades.pib = ler_float("PIB (bilhões): ", 0.1, 10000);
    carta->propriedades.pontos_turisticos = ler_inteiro("Número de pontos turísticos: ", 0, 100);

    calcular_propriedades(carta);
}

// Função para cadastrar cidades com valores aleatórios
void cadastrar_cidade_aleatorio(Carta *carta) {
    carta->propriedades.populacao = rand() % 1000000 + 1000; // População entre 1.000 e 1.000.000
    carta->propriedades.area = (rand() % 5000) + 10;         // Área entre 10 e 5000 km2
    carta->propriedades.pib = (rand() % 500) + 1;            // PIB entre 1 e 500 bilhões
    carta->propriedades.pontos_turisticos = rand() % 10 + 1; // Pontos turísticos entre 1 e 10

    calcular_propriedades(carta);
}

// Função para cadastrar estados e cidades
void cadastrar_estados(char *pais, Carta cartas[8][4]) {
    char estados[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    int escolha = ler_inteiro("\nDeseja cadastrar manualmente ou gerar aleatoriamente para todas as cartas do país?\n1 - Manual\n2 - Aleatório\nEscolha: ", 1, 2);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            // Gera o código da carta
            snprintf(cartas[i][j].codigo, sizeof(cartas[i][j].codigo), "%s_%c%02d", pais, estados[i], j + 1);

            if (escolha == 1) {
                cadastrar_cidade_manual(&cartas[i][j]);
            } else {
                cadastrar_cidade_aleatorio(&cartas[i][j]);
            }
        }
    }
}

// Função para exibir as cartas de um país
void exibir_cartas(char *pais, Carta cartas[8][4]) {
    printf("\nPropriedades do país %s:\n", pais);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            Carta *carta = &cartas[i][j];
            printf("\nCarta: %s\n", carta->codigo);
            printf("População: %d\n", carta->propriedades.populacao);
            printf("Área: %.2f km2\n", carta->propriedades.area);
            printf("PIB: %.2f bilhões\n", carta->propriedades.pib);
            printf("Pontos Turísticos: %d\n", carta->propriedades.pontos_turisticos);
            printf("Densidade Populacional: %.2f hab/km2\n", carta->propriedades.densidade_populacional);
            printf("PIB per Capita: %.2f milhões\n", carta->propriedades.pib_per_capita);
        }
    }
}

// Função para calcular o super poder de uma carta
int calcular_super_poder(Carta *carta) {
    return carta->propriedades.populacao + (int)carta->propriedades.area + (int)carta->propriedades.pib + carta->propriedades.pontos_turisticos;
}

// Função para jogadores escolherem cartas e determinar o vencedor
void jogar(int total_cartas, Carta *todas_cartas) {
    char jogador1[50], jogador2[50];
    char codigo_escolhido1[20], codigo_escolhido2[20];
    Carta *carta1 = NULL, *carta2 = NULL;

    printf("\nJogador 1, insira seu nome: ");
    scanf("%s", jogador1);

    printf("\nCartas disponíveis:\n");
    for (int i = 0; i < total_cartas; i++) {
        printf("%s\n ", todas_cartas[i].codigo);
    }

    while (carta1 == NULL) {
        printf("\n%s, escolha uma carta pelo código: ", jogador1);
        scanf("%s", codigo_escolhido1);
        for (int i = 0; i < total_cartas; i++) {
            if (strcmp(codigo_escolhido1, todas_cartas[i].codigo) == 0) {
                carta1 = &todas_cartas[i];
                break;
            }
        }
        if (carta1 == NULL) {
            printf("Código inválido. Tente novamente.\n");
        }
    }

    printf("\nJogador 2, insira seu nome: ");
    scanf("%s", jogador2);

    while (carta2 == NULL) {
        printf("\n%s, escolha uma carta pelo código: ", jogador2);
        scanf("%s", codigo_escolhido2);
        for (int i = 0; i < total_cartas; i++) {
            if (strcmp(codigo_escolhido2, todas_cartas[i].codigo) == 0) {
                carta2 = &todas_cartas[i];
                break;
            }
        }
        if (carta2 == NULL) {
            printf("Código inválido. Tente novamente.\n");
        }
    }

    int poder1 = calcular_super_poder(carta1);
    int poder2 = calcular_super_poder(carta2);

    printf("\nResultado:\n");
    printf("%s escolheu a carta %s com super poder %d.\n", jogador1, carta1->codigo, poder1);
    printf("%s escolheu a carta %s com super poder %d.\n", jogador2, carta2->codigo, poder2);

    if (poder1 > poder2) {
        printf("\n%s venceu!\n", jogador1);
    } else if (poder2 > poder1) {
        printf("\n%s venceu!\n", jogador2);
    } else {
        printf("\nEmpate!\n");
    }
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa gerar números aleatórios

    Carta todas_cartas[1000];
    int total_cartas = 0;

    char continuar;

    do {
        char pais[20];
        printf("Digite o nome do país: ");
        scanf("%s", pais);

        Carta cartas[8][4];
        cadastrar_estados(pais, cartas);

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                todas_cartas[total_cartas++] = cartas[i][j];
            }
        }

        exibir_cartas(pais, cartas);

        continuar = ler_char("\nDeseja cadastrar mais um país? (y/n): ", "yYnN");

    } while (continuar == 'y' || continuar == 'Y');

    printf("\nInício do jogo!\n");
    jogar(total_cartas, todas_cartas);

    printf("\nQue legal este jogo!\n");

    return 0;
}