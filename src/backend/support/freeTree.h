#ifndef FREE_TREE
#define FREE_TREE
#include "../semantic-analysis/abstract-syntax-tree.h"


void freeProgramTree(Program *program);

void freeCodeTree(Code *code);

void freeDefinition(Definition *definition);

void freeBinaryExpression(BinaryExpression *binaryExpression);

void freeUnaryExpression(UnaryExpression *unaryExpression);

void freeVarName(VariableName *VariableName);

void freeValueStruct(ValueStruct *valueStruct);

#endif