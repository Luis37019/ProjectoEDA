#define _CRT_SECURE_NO_WARNINGS
#define TRANSPORT_FILE "transportes.txt"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transportes.h"
#include "cliente.h"

#define MAX_TRANSPORTS 100
#define BICYCLE 0
#define SCOOTER 1

transport* transportHead = NULL;

void cpy_transport(transport* transport1, transport* transport2) {
    if (transport1 != NULL && transport2 != NULL) {
        transport1->id = transport2->id;
        transport1->type = transport2->type;
        transport1->battery = transport2->battery;
        transport1->autonomy = transport2->autonomy;
        strcpy(transport1->geocode, transport2->geocode);
    }
}
void addTransport() {
    int id, type, battery, autonomy;
    char geocode[MAX_GEOCODE_SIZE];

    // Get the transport information from the user
    printf("Id: ");
    scanf("%d", &id);

    printf("Tipo (0 para Bicicleta, 1 para Scooter): ");
    scanf("%d", &type);
    if (type != BICYCLE && type != SCOOTER) {
        printf("Tipo de transporte inválido!\n");
        return;
    }

    printf("Bateria (em percentagem): ");
    scanf("%d", &battery);
    if (battery < 0 || battery > 100) {
        printf("Valor de bateria inválido!\n");
        return;
    }

    printf("Autonomia (em km): ");
    scanf("%d", &autonomy);
    if (autonomy < 0) {
        printf("Valor de autonomia inválido!\n");
        return;
    }

    printf("Geocode: ");
    scanf("%s", geocode);

    // Create the transport variable with the user input
    transport* new_transport = (transport*)malloc(sizeof(transport));
    if (new_transport == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    new_transport->id = id;
    new_transport->type = type;
    new_transport->battery = battery;
    new_transport->autonomy = autonomy;
    strcpy(new_transport->geocode, geocode);

    // Add the new transport to the linked list of transports
    new_transport->next = NULL;
    if (transportHead == NULL) {
        transportHead = new_transport;
    }
    else {
        transport* current = transportHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_transport;
    }

    // Save the transport information to the file
    FILE* file = fopen(TRANSPORT_FILE, "a");
    if (file != NULL) {
        fprintf(file, "%d %d %d %d %s\n", id, type, battery, autonomy, geocode);
        fclose(file);
    }

    printf("Transporte adicionado com sucesso!\n");
}

transport* searchTransport(int id) {
    transport* current = transportHead;

    while (current != NULL) {
        if (current->id == id) {
            return current;
        }

        current = current->next;
    }

    FILE* file = fopen(TRANSPORT_FILE, "r");
    if (file != NULL) {
        transport* temp = (transport*)malloc(sizeof(transport));

        while (fscanf(file, "%d %d %d %d %s", &temp->id, &temp->type, &temp->battery, &temp->autonomy, temp->geocode) == 5) {
            if (temp->id == id) {
                fclose(file);
                return temp;
            }
        }

        fclose(file);
        free(temp);
    }

    return NULL;
}
void updateTransport() {
    int id;
    printf("ID do transporte a ser editado: ");
    scanf("%d", &id);
    getchar(); // Consumir o caractere de nova linha pendente no buffer

    transport* foundTransport = searchTransport(id);
    if (foundTransport != NULL) {
        int type, battery, autonomy;
        char geocode[MAX_GEOCODE_SIZE], input[MAX_GEOCODE_SIZE];

        printf("Tipo (0 para Bicicleta, 1 para Scooter): ");
        fgets(input, MAX_GEOCODE_SIZE, stdin);
        type = atoi(input);

        printf("Bateria (em percentagem): ");
        fgets(input, MAX_GEOCODE_SIZE, stdin);
        battery = atoi(input);

        printf("Autonomia (em km): ");
        fgets(input, MAX_GEOCODE_SIZE, stdin);
        autonomy = atoi(input);

        printf("Geocode: ");
        fgets(geocode, MAX_GEOCODE_SIZE, stdin);
        geocode[strcspn(geocode, "\n")] = '\0'; // Remove o caractere de nova linha

        foundTransport->type = type;
        foundTransport->battery = battery;
        foundTransport->autonomy = autonomy;
        strcpy(foundTransport->geocode, geocode);

        // Atualizar o arquivo de texto
        FILE* file = fopen(TRANSPORT_FILE, "w");
        if (file != NULL) {
            transport* temp = transportHead;
            while (temp != NULL) {
                fprintf(file, "%d %d %d %d %s\n", temp->id, temp->type, temp->battery, temp->autonomy, temp->geocode);
                temp = temp->next;
            }
            fclose(file);
        }

        printf("Transporte editado com sucesso!\n");
    }
    else {
        printf("Transporte nao encontrado!\n");
    }
}
void removeTransport() {
    int id;
    printf("ID do transporte a ser removido: ");
    scanf("%d", &id);

    transport* current = transportHead;
    transport* previous = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (previous == NULL) {
                // Removing the head of the list
                transportHead = current->next;
            }
            else {
                previous->next = current->next;
            }

            // Atualizar o arquivo de texto
            FILE* file = fopen(TRANSPORT_FILE, "w");
            if (file != NULL) {
                transport* temp = transportHead;
                while (temp != NULL) {
                    fprintf(file, "%d %d %d %d %s\n", temp->id, temp->type, temp->battery, temp->autonomy, temp->geocode);
                    temp = temp->next;
                }
                fclose(file);
            }

            printf("Transporte removido com sucesso!\n");
            free(current);
            return;
        }

        previous = current;
        current = current->next;
    }

    printf("Transporte nao encontrado!\n");
}
void searchByGeocode() {
    char geocode[MAX_GEOCODE_SIZE];
    printf("Geocode: ");
    scanf("%s", geocode);

    transport* current = transportHead;
    transport* resultsHead = NULL;
    transport* resultsTail = NULL;

    // Encontrar os transportes com o geocode fornecido
    while (current != NULL) {
        if (strcmp(current->geocode, geocode) == 0) {
            transport* new_result = (transport*)malloc(sizeof(transport));
            cpy_transport(new_result, current);
            new_result->next = NULL;

            if (resultsHead == NULL) {
                resultsHead = new_result;
                resultsTail = new_result;
            }
            else {
                resultsTail->next = new_result;
                resultsTail = new_result;
            }
        }

        current = current->next;
    }

    // Verificar se não foram encontrados transportes
    if (resultsHead == NULL) {
        printf("Nenhum transporte encontrado com o geocode '%s'\n", geocode);
        return;
    }

    // Ordenar os transportes em ordem decrescente de autonomia (opcional)

    // Exibir os transportes encontrados
    printf("Transportes encontrados com o geocode '%s':\n", geocode);
    current = resultsHead;
    while (current != NULL) {
        printf("ID: %d, Tipo: %d, Bateria: %d%%, Autonomia: %dkm\n", current->id, current->type, current->battery, current->autonomy);
        current = current->next;
    }

    // Liberar a memória alocada para os resultados
    current = resultsHead;
    while (current != NULL) {
        transport* next = current->next;
        free(current);
        current = next;
    }
}