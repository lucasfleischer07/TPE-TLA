#ifndef FREE_TREE
#define FREE_TREE
#include "../semantic-analysis/abstract-syntax-tree.h"


void freeProgramTree(Program *program);

void freeCodeTree(Code* code);

void freeDefinition(Definition* definition);

void freeVarType(Variable *varType);

void freeVarName(VariableName *VariableName);

#endif