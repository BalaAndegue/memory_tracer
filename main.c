#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

#define PAGE_SIZE 4096
#define NUM_PAGES 256
#define MAX_ACCESSES 10000

// Structure pour stocker les accès mémoire
typedef struct {
    unsigned long page_number;
    int count;
} page_access_t;

// Variables globales pour le tracing
static page_access_t page_accesses[NUM_PAGES];
static int total_accesses = 0;

// Initialiser le compteur de pages
void init_page_counter() {
    for (int i = 0; i < NUM_PAGES; i++) {
        page_accesses[i].page_number = i;
        page_accesses[i].count = 0;
    }
}

// Enregistrer un accès à une page
void record_page_access(void* address) {
    unsigned long page_num = (unsigned long)address / PAGE_SIZE;
    if (page_num < NUM_PAGES) {
        page_accesses[page_num].count++;
        total_accesses++;
    }
}

// Sauvegarder les données dans un fichier
void save_access_data(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    fprintf(file, "page_number,access_count\n");
    for (int i = 0; i < NUM_PAGES; i++) {
        fprintf(file, "%lu,%d\n", page_accesses[i].page_number, page_accesses[i].count);
    }

    fclose(file);
    printf("Données sauvegardées dans %s\n", filename);
}

// Fonctions de test avec différents patterns d'accès

// Pattern séquentiel
void sequential_access_pattern(int* buffer, int size) {
    printf("Pattern séquentiel...\n");
    for (int i = 0; i < size; i++) {
        buffer[i] = i;
        record_page_access(&buffer[i]);
    }
}

// Pattern aléatoire
void random_access_pattern(int* buffer, int size) {
    printf("Pattern aléatoire...\n");
    srand(time(NULL));
    for (int i = 0; i < size * 2; i++) {
        int index = rand() % size;
        buffer[index] = i;
        record_page_access(&buffer[index]);
    }
}

// Pattern avec localité spatiale
void spatial_locality_pattern(int* buffer, int size) {
    printf("Pattern avec localité spatiale...\n");
    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        int base = rand() % (size - 10);
        for (int j = 0; j < 10; j++) {
            buffer[base + j] = i + j;
            record_page_access(&buffer[base + j]);
        }
    }
}

int main() {
    printf("Démarrage du traceur mémoire...\n");

    // Initialiser le compteur
    init_page_counter();

    // Allouer un buffer pour les tests
    int buffer_size = NUM_PAGES * PAGE_SIZE / sizeof(int);
    int* buffer = malloc(buffer_size * sizeof(int));

    if (!buffer) {
        perror("Erreur d'allocation mémoire");
        return 1;
    }

    printf("Buffer alloué: %d pages (%d bytes)\n", NUM_PAGES, NUM_PAGES * PAGE_SIZE);

    // Exécuter différents patterns d'accès
    sequential_access_pattern(buffer, buffer_size);
    random_access_pattern(buffer, buffer_size);
    spatial_locality_pattern(buffer, buffer_size);

    // Sauvegarder les données
    save_access_data("memory_access_data.csv");

    // Nettoyer
    free(buffer);

    printf("Total d'accès enregistrés: %d\n", total_accesses);
    printf("Terminé!\n");

    return 0;
}
