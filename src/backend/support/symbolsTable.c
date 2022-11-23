#include "symbolsTable.h"
#include "logger.h"

static SymbolEntry *findVariableRecursive(SymbolEntry *currentEntry,char *varnName);

SymbolTable *newTable() {
    SymbolTable *table = (SymbolTable *) calloc(1, sizeof(SymbolTable));
    table->top = NULL;
    return table;
}

//imprimimos la variable de entrada, tampoco se si hace falta 
void printVariable(SymbolEntry *entry) { //por si quiero impimirlo x entrada
    if (entry == NULL)
        printf("es null"); //no se si nos interesa
    else
        printf("%s, %d, \n", entry->name, entry->type);
}


//esta funcion la vamos a usar en el bison.c para agregar simbolos una vez creados a la tabla
// seria como un init table
void addSymbolToTable(SymbolTable *table, char *name, SymbolType type) {

    SymbolEntry *entry = (SymbolEntry *) calloc(1, sizeof(SymbolEntry));

    if(entry == NULL){
        return;
    }
    entry->name = (char *) calloc(strlen(name) + 1, sizeof(char));

    if(entry->name == NULL){
        free(entry);
        return;
    }
    strcpy(entry->name, name);
    entry->type = type;
    entry->next = table->top;
    table->top = entry;
    LogDebug("\t\tAddSymbolToTable Name: (%s))", entry->name);
}

/** Funcion que devuelve 1 si la variable ya esta definida, 0 en otro caso*/
int isVariableInTable(SymbolTable *table,char *varName){
    SymbolEntry *varFound = findVariableRecursive(table->top,varName);
    return varFound == NULL ? 0 : 1;
}


/** Funcion que devuelve 1 si la variable tiene el tipo esperado, 0 si no existe la variable o no es el del tipo espardo*/
int isVariableOfType(SymbolTable *table, char *varName, SymbolType type){
    SymbolEntry *varFound = findVariableRecursive(table->top,varName);
    if(varFound == NULL){
        return 0;
    }
    return varFound->type == type ? 1 : 0;
}

/** Funcion que devuelve el tipo de la variable*/
SymbolType getVariableType(SymbolTable *table, char *varName){
    SymbolEntry* symbol = findVariableRecursive(table->top, varName);
    return symbol->type;
}

static void freeRecursive(SymbolEntry* current){
    if (current == NULL){
        return;
    }
    SymbolEntry* aux = current->next;
    free(current);
    freeRecursive(aux);
}

void freeTable(SymbolTable *table){
    freeRecursive(table->top);
    free(table);
}

static SymbolEntry *findVariableRecursive(SymbolEntry *currentEntry,char *varName) {
    if(currentEntry == NULL)
        return NULL;
    
    if(strcmp(currentEntry->name, varName) == 0) {
        return currentEntry;
    }
    return findVariableRecursive(currentEntry->next, varName);
}

int isSongDefined(SymbolEntry *currentEntry){
    if(currentEntry == NULL){
        return 0;
    }
    if(currentEntry->type == SONG_SYMBOL){
        return 1;
    }
    return isSongDefined(currentEntry->next);
}