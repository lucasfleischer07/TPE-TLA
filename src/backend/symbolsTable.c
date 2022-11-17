#include "symbolsTable.h"

// Manejo de tabla de si,bolos
SymbolEntry* newSymbol(char* name, SymbolType type) {
    //creo q value no hace falta xq puedo crear song cancion1
    SymbolEntry* entry = malloc(sizeof(SymbolEntry));
    if(entry == NULL){
        //funcion para manejar q me quede sin memory
        return NULL;
    }
    entry->name = malloc(strlen(name) + 1);
    if(entry->name == NULL){
        free(entry);
         //funcion para manejar q me quede sin memory
        return NULL;
    }
    strcpy(entry->name, name);
    entry->type = type;
    return entry;
}

//imprimimos la variable de entrada, tampoco se si hace falta 
void printVariable(SymbolEntry* entry) { //por si quiero impimirlo x entrada
    if (entry == NULL)
        printf("es null"); //no se si nos interesa
    else
        printf("%s, %s, \n", entry->name, entry->type);
}


// ----------------------------------------------------
    // esto no ya que en tabla de simbolos solo declaramos el char* osea nombre y el tipo de variable


//borar con ek - una variable
// void deleteVariable(SymbolEntry* entry) {

//     if (entry == NULL)
//         return;

//     if (entry->name != NULL)
//         //funcion para manejar q me quede sin memory
//         free(entry->name);

//     deleteSymbolEntryList(entry->next);
//     free(entry);
// }


// Agregar variable a la tabla

// void addVariable(SymbolTable* table, SymbolEntry* entry) {
//     entry->next = table->top;
//     table->top = entry;
// }

