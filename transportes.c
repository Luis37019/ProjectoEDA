#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRANSPORTS_FILE "transports.txt"
#define MAX_GEOCODE_SIZE 100

typedef struct transports_data {
    int id;
    int type;
    int battery;
    int autonomy;
    char geocode[MAX_GEOCODE_SIZE];

} transports_data;

void add_transport(transports_data transport) {
    // Abrir o arquivo para escrita, adicionando no final do arquivo
    FILE* fp = fopen(TRANSPORTS_FILE, "a");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    // Escrever os dados do transporte no arquivo
    fprintf(fp, "%d %d %d %d %s\n", transport.id, transport.type, transport.battery, transport.autonomy, transport.geocode);

    // Fechar o arquivo
    fclose(fp);
}
void remove_transport(int id) {
    // Abrir o arquivo para leitura
    FILE* fp = fopen(TRANSPORTS_FILE, "r");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    // Abrir um novo arquivo tempor?rio para escrita
    FILE* tmp_fp = fopen("temp.txt", "w");
    if (tmp_fp == NULL) {
        printf("Erro ao criar arquivo tempor?rio!\n");
        fclose(fp);
        return;
    }

    // Ler linha por linha do arquivo original e copiar para o arquivo tempor?rio, exceto as linhas com o id do transporte a ser removido
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        transports_data transport;
        sscanf(line, "%d %d %d %d %s", &transport.id, &transport.type, &transport.battery, &transport.autonomy, transport.geocode);

        if (transport.id != id) {
            fprintf(tmp_fp, "%d %d %d %d %s", transport.id, transport.type, transport.battery, transport.autonomy, transport.geocode);
        }
    }

    // Fechar os arquivos
    fclose(fp);
    fclose(tmp_fp);

    // Remover o arquivo original e renomear o arquivo tempor?rio para o nome original
    remove(TRANSPORTS_FILE);
    rename("temp.txt", TRANSPORTS_FILE);
}
void edit_transport(int id, transports_data new_transport)
 {
    // Abrir o arquivo para leitura
    FILE* fp = fopen(TRANSPORTS_FILE, "r");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    // Abrir um novo arquivo tempor?rio para escrita
    FILE* tmp_fp = fopen("temp.txt", "w");
    if (tmp_fp == NULL) {
        printf("Erro ao criar arquivo tempor?rio!\n");
        fclose(fp);
        return;
    }

    // Ler linha por linha do arquivo original e copiar para o arquivo tempor?rio, atualizando as informa??es do transporte com o ID correspondente
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        transports_data transport;
        sscanf(line, "%d %d %d %d %s", &transport.id, &transport.type, &transport.battery, &transport.autonomy, transport.geocode);

        if (transport.id == id) {
            // Atualizar os dados do transporte
            transport.type = new_transport.type;
            transport.battery = new_transport.battery;
            transport.autonomy = new_transport.autonomy;
            strcpy(transport.geocode, new_transport.geocode);
        }

        // Escrever os dados do transporte (atualizados ou n?o) no arquivo tempor?rio
        fprintf(tmp_fp, "%d %d %d %d %s\n", transport.id, transport.type, transport.battery, transport.autonomy, transport.geocode);
    }

    // Fechar os arquivos
    fclose(fp);
    fclose(tmp_fp);

    // Remover o arquivo original e renomear o arquivo tempor?rio para o nome original
    remove(TRANSPORTS_FILE);
    rename("temp.txt", TRANSPORTS_FILE);
}
