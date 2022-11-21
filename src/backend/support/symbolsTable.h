#ifndef SYMBOL_TABLE_HEADER
#define SYMBOL_TABLE_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum SymbolType {
    NOTE_SYMBOL,
    SONG_SYMBOL,
    TRACK_SYMBOL
} SymbolType; 


typedef struct SymbolEntry {
    char * name;
    SymbolType type; 
    struct SymbolEntry * next; 
} SymbolEntry; 


typedef struct SymbolTable {
    SymbolEntry * top; 
} SymbolTable; 


SymbolTable * newTable();

void addSymbolToTable(SymbolTable* table, char* name, SymbolType type) ;
void deleteVariable(SymbolEntry* entry);

void printVariable(SymbolEntry* entry);

int isVariableOfType(SymbolTable *table,char *varName,SymbolType type);

int isVariableInTable(SymbolTable *table,char *varName);

SymbolType getVariableType(SymbolTable *table,char *varName);

void freeTable(SymbolTable *table);

int isSongDefined(SymbolTable *entry);
#endif