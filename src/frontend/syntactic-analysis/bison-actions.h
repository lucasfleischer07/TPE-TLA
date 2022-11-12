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
int ProgramGrammarAction(const int value);

int CodeGrammarAction(const int left, const int right);

int DefinitionsGrammarAction(const int left,const int right);
int DefinitionGrammarAction(const int value);
int OnlyDefinitionsGrammarAction(const int value);

int SongGrammarAction(const int left, const int right);
int TrackGrammarAction(const int left, const int right);
int NoteGrammarAction(const int left, const int right);

int InstructionGrammarAction(const int value);
int InstructionsGrammarAction(const int left, const int right);

int UnaryExpressionGrammarAction(const int value);
int BinaryExpressionGrammarAction(const int value);

int NoteValueExpressionGrammarAction(const int left, const int right);
int RhythmExpressionGrammarAction(const int left, const int middle, const int right);
int NoteFullDefinitionExpressionGrammarAction(const int left, const int middleLeft,const int middleRight, const int right);
int TrackInstrumentGrammarAction(const int left, const int right);
int TempoExpressionGrammarAction(const int left, const int right);
int MultiplicationExpressionGrammarAction(const int left, const int middle, const int right);
int ParentesisExpressionGramarAction(const int value);
int RepetitionGrammarAction(const int left, const int right);

int BinaryExpressionAdditionExpressionGrammarAction(const int left, const int right);
int VariableAdditionVariableGrammarAction(const int left, const int right);
int VariableAdditionExpressionGrammarAction(const int left, const int right);
int SubstractionExpressionGrammarAction(const int left, const int right);
int DivisionExpressionGrammarAction(const int left, const int right);

int VariableNameGrammarAction(const int value);

#endif
