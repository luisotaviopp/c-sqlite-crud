#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

void clrscr()
{
    system("@cls||clear");
}

void displayMenu();

void add_user(sqlite3 *db);
void list_users(sqlite3 *db);
void update_user(sqlite3 *db);
void get_user_by_id(sqlite3 *db);
void list_deleted(sqlite3 *db);
void delete_user(sqlite3 *db);
void reactivate_user(sqlite3 *db);


int main() {
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("sample.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir DB: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *create_table_query = "CREATE TABLE IF NOT EXISTS user (id INTEGER PRIMARY KEY, name TEXT, age INT, is_active BOOLEAN DEFAULT true);";

    rc = sqlite3_exec(db, create_table_query, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Falha ao criar tabela: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
       // printf("Tabela criada com sucesso!\n");
    }

    // Main menu loop
    int choice;
    do {
        displayMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_user(db);
                break;
            case 2:
                list_users(db);
                break;
            case 3:
                update_user(db);
                break;
            case 4:
                get_user_by_id(db);
                break;
            case 5:
                list_deleted(db);
                break;
            case 6:
                delete_user(db);
                break;
            case 7:
                reactivate_user(db);
                break;
            case 8:
               	printf("             .-\"\"\"-.\n");
				printf("            /       \\\n");
				printf("            \\       /\n");
				printf("     .-\"\"\"-.-`.-.-.<  _\n");
				printf("    /      _,-\\ O_O-_/ )  ~champagne, monsieur?\n");
				printf("    \\     / ,  `   . `|\n");
				printf("     '-..-| \\-.,__~ ~ /          .,\n");
				printf("           \\ `-.__/  /          /\"/\n");
				printf("          / `-.__.-\\`-._    ,\",' ;\n");
				printf("         / /|    ___\\-. `-.; /  ./-.\n");
				printf("        ( ( |.-\"`   `\\ '-( /  //.-' \n");
				printf("         \\ \\/    {}{}  |   /-. /.-'\n");
				printf("          \\|           /   '..'\n");
				printf("           \\        , /\n");
				printf("           ( __`;-;'__`)\n");
				printf("           `//'`   `||`\n");
				printf("          _//       ||\n");
				printf("   .-\"-._,(__)     .(__).-\"\"-.\n");
				printf("  /          \\    /           \\\n");
				printf("  \\          /    \\           /\n");
				printf("   `'-------`      `--------'`\n");
                break;
            default:
                printf("Opção invalida, tente novamente.\n");
        }
    } while (choice != 8);

    // Close the database
    sqlite3_close(db);

    return 0;
}

void displayMenu() {
	printf("              ,---------------------------,\n");
	printf("              |  /---------------------\\  |\n");
	printf("              | |                       | |\n");
	printf("              | |                       | |\n");
	printf("              | |     55 Technology     | |\n");
	printf("              | |    (48) 9 9696 6465   | |\n");
	printf("              | |                       | |\n");
	printf("              | |  Selecione uma opcao  | |\n");
	printf("              | |                       | |\n");
	printf("              |  \\_____________________/  |\n");
	printf("              |___________________________|\n");
	printf("            ,---\\_____     []     _______/------,\n");
	printf("          /         /______________\\           /|\n");
	printf("        /___________________________________ /  | ___\n");
	printf("        |                                   |   |    )\n");
	printf("        |  _ _ _                 [-------]  |   |   (\n");
	printf("        |  o o o                 [-------]  |  /    _)_\n");
	printf("        |__________________________________ |/     /  /\n");
	printf("    /-------------------------------------/|      ( )/\n");
	printf("  /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ /\n");
	printf("/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ /\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				
    printf("1. Adicionar usuario\n");
    printf("2. Listar usuarios\n");
    printf("3. Atualizar usuarios\n");
    printf("4. Selecionar usuario\n");
    printf("5. Ver deletados\n");
    printf("6. Deletar usuario\n");
    printf("7. Reativar usuario\n");
    printf("8. Sair \n");
}

void add_user(sqlite3 *db) {
	clrscr();
		 
    char name[100];
    int age;

    printf("Qual a idade? ");
    scanf("%d", &age);

    printf("Qual o nome? ");
    scanf("%s", name);

    char query[200];
    sprintf(query, "INSERT INTO user (name, age) VALUES ('%s', %d);", name, age);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Falha ao adicionar usuario: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("usuário adicionado!\n");
    }
}

void list_users(sqlite3 *db) {
	clrscr();
    char *query = "SELECT * FROM user WHERE is_active = true;";
    char *err_msg = 0;

    printf("\n-- Usuarios --\n");

    // Callback function to print each row
    int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        for (int i = 0; i < argc; i++) {
            printf("%s: %s \t\t", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }
 
    int rc = sqlite3_exec(db, query, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Falha ao listar usuarios: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

void update_user(sqlite3 *db) {
	clrscr();
    char name[100];
    int age;
    int id;
    
    printf("Qual o id? ");
    scanf("%d", &id);

    printf("Qual o nome? ");
    scanf("%s", name);

    printf("Qual a idade? ");
    scanf("%d", &age);

    char query[200];
    sprintf(query, "UPDATE user SET name = '%s', age = %d WHERE id = %d;", name, age, id);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Falha ao atualizar usuario: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Usuário atualizado!\n");
    }
}

void get_user_by_id(sqlite3 *db) {
	clrscr();
    int id;
    
    printf("Qual o id? ");
    scanf("%d", &id);
    
	char query[200];
    sprintf(query, "SELECT * FROM user WHERE id = %d;", id);
    
    char *err_msg = 0;

    printf("\n------\n");

    // Callback function to print each row
    int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        for (int i = 0; i < argc; i++) {
            printf("%s: %s \t\t", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }
 
    int rc = sqlite3_exec(db, query, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Falha ao listar usuarios: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

void list_deleted(sqlite3 *db) {
	clrscr();
    char *query = "SELECT * FROM user WHERE is_active = 0;";
    char *err_msg = 0;

    printf("\n-- Usuarios inativos --\n");

    // Callback function to print each row
    int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        for (int i = 0; i < argc; i++) {
            printf("%s: %s \t\t", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }
 
    int rc = sqlite3_exec(db, query, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Falha ao listar usuarios: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

void delete_user(sqlite3 *db) {
	clrscr();
    int id;
    
    printf("Qual o id? ");
    scanf("%d", &id);

    char query[200];
    sprintf(query, "UPDATE user SET is_active = false WHERE id = %d;", id);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Falha ao deletar usuário: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Usuário deletado!\n");
    }
}

void reactivate_user(sqlite3 *db) {
	clrscr();
    int id;
    
    printf("Qual o id? ");
    scanf("%d", &id);

    char query[200];
    sprintf(query, "UPDATE user SET is_active = true WHERE id = %d;", id);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Falha ao reativar usuário: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Usuário reativado!\n");
    }
}
