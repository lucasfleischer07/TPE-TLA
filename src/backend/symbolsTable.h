#ifndef SYMBOL_TABLE_HEADER
#define SYMBOL_TABLE_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum SymbolType {
    NOTE,
    SONG,
    TRACK
} SymbolType; 


typedef struct SymbolEntry {
    char * name;
    SymbolType type; 
    struct SymbolEntry * next; 
} SymbolEntry; 


typedef struct SymbolTable {
    SymbolEntry * top; 
} SymbolTable; 


SymbolEntry * newSymbol(char * name,  SymbolType type); 



void addVariable(SymbolTable* table, SymbolEntry* entry) ;
void deleteVariable(SymbolEntry* entry);

void printVariable(SymbolEntry* entry);

#endif