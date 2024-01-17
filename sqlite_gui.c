#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <ncurses.h>

void clrscr() {
    system("clear");
}

void displayMenu() {
    printw("\n-- User CRUD Menu --\n");
    printw("1. Adicionar usuario\n");
    printw("2. Listar usuarios\n");
    printw("3. Atualizar usuarios\n");
    printw("4. Selecionar usuario\n");
    printw("5. Ver deletados\n");
    printw("6. Deletar usuario\n");
    printw("7. Reativar usuario\n");
    printw("8. Exit\n");
    refresh();
}

void add_user(sqlite3 *db) {
    clrscr();
    char name[100];
    int age;

    printw("Qual a idade? ");
    scanw("%d", &age);

    printw("Qual o nome? ");
    scanw("%s", name);

    char query[200];
    sprintf(query, "INSERT INTO user (name, age) VALUES ('%s', %d);", name, age);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        printw("Falha ao adicionar usuario: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printw("usuário adicionado!\n");
    }
}

// Implement other functions similarly...

int main() {
    initscr(); // Initialize ncurses
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("sample.db", &db);

    if (rc != SQLITE_OK) {
        printw("Erro ao abrir DB: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        endwin(); // Terminate ncurses
        return 1;
    }

    const char *create_table_query = "CREATE TABLE IF NOT EXISTS user (id INTEGER PRIMARY KEY, name TEXT, age INT, is_active BOOLEAN DEFAULT true);";

    rc = sqlite3_exec(db, create_table_query, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        printw("Falha ao criar tabela: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printw("Tabela criada com sucesso!\n");
    }

    // Main menu loop
    int choice;
    do {
        displayMenu();
        printw("Escolha uma opcao: ");
        scanw("%d", &choice);

        switch (choice) {
            case 1:
                add_user(db);
                break;
            // Implement other cases similarly...
        }
    } while (choice != 8);

    // Close the database
    sqlite3_close(db);

    endwin(); // Terminate ncurses
    return 0;
}
