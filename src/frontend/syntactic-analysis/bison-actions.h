#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
Program *ProgramGrammarAction(Code *code);

Code *CodeGrammarAction(Definitions *definitions, InstructionsArray *instructionsArray);

Code *OnlyDefinitionsGrammarAction(Definitions *definitions);
Definitions *DefinitionsGrammarAction(Definition *definitionParam, Definitions *definitionsParam);
Definitions *DefinitionGrammarAction(Definition *definitionParam);

Definition *SongGrammarAction(VariableName *variableName);
Definition *TrackGrammarAction(VariableName *variableName);
Definition *NoteGrammarAction(VariableName *variableName);

InstructionsArray *InstructionGrammarAction(Instruction *instruction);
InstructionsArray *InstructionsGrammarAction(Instruction *instruction, InstructionsArray *instructionArrayParam);

Instruction *UnaryExpressionGrammarAction(UnaryExpression *unaryExpression);
Instruction *BinaryExpressionGrammarAction(BinaryExpression *binaryExpression);

UnaryExpression *NoteValueExpressionGrammarAction(VariableName *variableName, Note *noteValue);
UnaryExpression *RhythmExpressionGrammarAction(VariableName *variableName, Note *noteValue, Rhythm *rythmValue);
UnaryExpression *NoteFullDefinitionExpressionGrammarAction(VariableName * variableName, Note *noteValue, Rhythm *rythmValue, int *chordValue);
UnaryExpression *TrackInstrumentGrammarAction(VariableName *variableName, Instrument *instrumentValue);
UnaryExpression *TempoExpressionGrammarAction(VariableName *variableName, double *tempoValue);
UnaryExpression *MultiplicationExpressionGrammarAction(VariableName *variableName, int *repetition);
UnaryExpression *DurationGrammarAction(VariableName *variableName, int *repetition);

BinaryExpression *BinaryExpressionAdditionExpressionGrammarAction(VariableName *variableNameLeft, BinaryExpression *binaryExpressionRight);
BinaryExpression *VariableAdditionVariableGrammarAction(VariableName *variableNameLeft, VariableName *variableNameRight);
BinaryExpression *VariableAdditionExpressionGrammarAction(VariableName *variableNameLeft, UnaryExpression *unaryExpressionRight);
BinaryExpression *SubstractionExpressionGrammarAction(VariableName *variableNameLeft, VariableName *variableNameRight);
BinaryExpression *DivisionExpressionGrammarAction(VariableName *variableNameLeft, VariableName *variableNameRight);
BinaryExpression *ParentesisExpressionGramarAction(VariableName *variableNameLeft, VariableName *variableNameRight);

VariableName *VariableNameGrammarAction(char *variable);

#endif
