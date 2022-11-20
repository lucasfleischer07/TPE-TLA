#include "symbolsTable.h"
#include "logger.h"

static SymbolEntry* findVariableRecursive(SymbolEntry *currentEntry,char *varnName);

SymbolTable * newTable() {
    SymbolTable * table = malloc(sizeof(SymbolTable));
    table->top = NULL;
    return table;
}

//imprimimos la variable de entrada, tampoco se si hace falta 
void printVariable(SymbolEntry* entry) { //por si quiero impimirlo x entrada
    if (entry == NULL)
        printf("es null"); //no se si nos interesa
    else
        printf("%s, %d, \n", entry->name, entry->type);
}


//esta funcion la vamos a usar en el bison.c para agregar simbolos una vez creados a la tabla
// seria como un init table
void addSymbolToTable(SymbolTable* table, char* name, SymbolType type) {
    //creo q value no hace falta xq puedo crear song cancion1
    SymbolEntry* entry = malloc(sizeof(SymbolEntry));
    if(entry == NULL){
	    LogDebug("\t\tAddSymbolToTable con entry NULL");
        //funcion para manejar q me quede sin memory
        return;
    }
    entry->name = malloc(strlen(name) + 1);
    if(entry->name == NULL){
	    LogDebug("\t\tAddSymbolToTable con name NULL");
        free(entry);
        //funcion para manejar q me quede sin memory
        return;
    }
    strcpy(entry->name, name);
    entry->type = type;
    entry->next = table->top;
    table->top = entry;
    LogDebug("\t\tAddSymbolToTable(%s))", entry->name);
}

/** Funcion que devuelve 1 si la variable ya esta definida, 0 en otro caso*/
int isVariableInTable(SymbolTable *table,char *varName){
    SymbolEntry *varFound = findVariableRecursive(table->top,varName);
    return varFound == NULL ? 0 : 1;
}


/** Funcion que devuelve 1 si la variable tiene el tipo esperado, 0 si no existe la variable o no es el del tipo espardo*/
int isVariableOfType(SymbolTable *table,char *varName,SymbolType type){
    SymbolEntry *varFound = findVariableRecursive(table->top,varName);
    if(varFound == NULL){
        return 0;
    }
    return varFound->type == type ? 1 : 0;
}

/** Funcion que devuelve el tipo de la variable*/
SymbolType getVariableType(SymbolTable *table,char *varName){
    SymbolEntry* symbol = findVariableRecursive(table->top,varName);
    return symbol->type;
}

static void freeRecursive(SymbolEntry* current){
    if (current== NULL){
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

static SymbolEntry* findVariableRecursive(SymbolEntry *currentEntry,char *varName){
    if(currentEntry==NULL)
        return NULL;
    if(strcmp(currentEntry->name,varName)==0)
        return currentEntry;
    return findVariableRecursive(currentEntry->next,varName);
}
