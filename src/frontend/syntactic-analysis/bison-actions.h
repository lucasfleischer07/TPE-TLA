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

int SongGrammarAction(const int left, const int right);
int TrackGrammarAction(const int left, const int right);
int NoteGrammarAction(const int left, const int right);

int InstructionGrammarAction(const int value);
int InstructionsGrammarAction(const int left, const int right);

int SimpleExpressionGrammarAction(const int value);
int DoubleExpressionGrammarAction(const int value);

int NoteValueExpressionGrammarAction(const int left, const int right);
int RhythmExpressionGrammarAction(const int left, const int middle, const int right);
int NoteFullDefinitionExpressionGrammarAction(const int left, const int middleLeft,const int middleRight, const int right);
int TrackInstrumentGrammarAction(const int left, const int right);
int TempoExpressionGrammarAction(const int left, const int right);
int MultiplicationExpressionGrammarAction(const int left, const int middle, const int right);
int ParentesisExpressionGramarAction(const int value);
int RepetitionGrammarAction(const int left, const int right);

int SongAdditionExpressionGrammarAction(const int left, const int right);
int TrackAdditionExpressionGrammarAction(const int left, const int right);
int SubstractionNoteExpressionGrammarAction(const int left, const int right);
int SubstractionTrackExpressionGrammarAction(const int left, const int right);
int TrackSubstractionNoteExpressionGrammarAction(const int left, const int right);
int DivisionExpressionGrammarAction(const int left, const int right);

int SongTermGrammarAction(const int value);

int TrackTermGrammarAction(const int value);

int NoteTermGrammarAction(const int value);

#endif
