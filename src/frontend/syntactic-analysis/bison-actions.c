#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

/**
 * Implementación de "bison-grammar.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char * string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/
int ProgramGrammarAction(const int value) {
	LogDebug("\tProgramGrammarAction(%d)", value);
	/*
	* "state" es una variable global que almacena el estado del compilador,
	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
	* es utilizada en la función "main".
	*/
	state.succeed = true;
	
	/*
	* Por otro lado, "result" contiene el resultado de aplicar el análisis
	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
	* la expresión se computa on-the-fly, y es la razón por la cual esta
	* variable es un simple entero, en lugar de un nodo.
	*/
	state.result = value;
	return value;
}

int CodeGrammarAction(const int left, const int right) {
	LogDebug("\tCodeGrammarAction(%d, %d)", left, right);
	return 1;
}

int OnlyDefinitionsGrammarAction(const int value) {
	LogDebug("\tOnlyDefinitionsGrammarAction(%d)", value);
	return 1;
}

int DefinitionsGrammarAction(const int left,const int right) {
	LogDebug("\tDefinitionsGrammarAction(%d, %d)", left, right);
	return 1;
}

int DefinitionGrammarAction(const int value) {
	LogDebug("\tDefinitionGrammarAction(%d)", value);
	return 1;
}

int SongGrammarAction(const int left, const int right) {
	LogDebug("\tSongGrammarAction(%d, %d)", left, right);
	return 1;
}

int TrackGrammarAction(const int left, const int right) {
	LogDebug("\tTrackGrammarAction(%d, %d)", left, right);
	return 1;
}

int NoteGrammarAction(const int left, const int right) {
	LogDebug("\tNoteGrammarAction(%d, %d)", left, right);
	return 1;
}

int InstructionGrammarAction(const int value) {
	LogDebug("\tInstructionGrammarAction(%d)", value);
	return 1;
}

int InstructionsGrammarAction(const int left, const int right) {
	LogDebug("\tSimpleExpressionGrammarAction(%d, %d)", left, right);
	return 1;
}

int SimpleExpressionGrammarAction(const int value) {
	LogDebug("\tSimpleExpressionGrammarAction(%d)", value);
	return 1;
}

int DoubleExpressionGrammarAction(const int value) {
	LogDebug("\tDoubleExpressionGrammarAction(%d)", value);
	return 1;
}

int NoteValueExpressionGrammarAction(const int left, const int right) {
	LogDebug("\tNoteValueExpressionGrammarAction(%d, %d)", left, right);
	return 1;
}

int RhythmExpressionGrammarAction(const int left, const int middle, const int right) {
	LogDebug("\tRhythmExpressionGrammarAction(%d, %d,%d)", left, middle,right);
	return 1;
}

int NoteFullDefinitionExpressionGrammarAction(const int left, const int middleLeft,const int middleRight, const int right) {
	LogDebug("\tNoteFullDefinitionExpressionGrammarAction(%d, %d, %d, %d)", left, middleLeft,middleRight, right);
	return 1;
}

int TrackInstrumentGrammarAction(const int left, const int right) {
	LogDebug("\tTrackInstrumentGrammarAction(%d, %d)", left, right);
	return 1;
}

int TempoExpressionGrammarAction(const int left, const int right) {
	LogDebug("\tTempoExpressionGrammarAction(%d, %d)", left, right);
	return 1;
}

int MultiplicationExpressionGrammarAction(const int left, const int middle, const int right) {
	LogDebug("\tMultiplicationExpressionGrammarAction(%d, %d, %d)", left, middle, right);
	return 1;
}

int ParentesisExpressionGramarAction(const int value) {
	LogDebug("\tDefinitionsGrammarAction(%d)", value);
	return 1;
}


int RepetitionGrammarAction(const int left, const int right){
	LogDebug("\tInstructionGrammarAction(%d, %d)", left, right);
	return 1;
}

int DoubleExpressionAdditionExpressionGrammarAction(const int left, const int right) {
	LogDebug("\tDoubleExpressionAdditionExpressionGrammarAction(%d, %d)", left, right);
	return 1;
}

int VariableAdditionExpressionGrammarAction(const int left, const int right) {
	LogDebug("\tVariableAdditionExpressionGrammarAction(%d, %d)", left, right);
	return 1;
}

int VariableAdditionVariableGrammarAction(const int left, const int right) {
	LogDebug("\tVariableAdditionVariableGrammarAction(%d, %d)", left, right);
	return 1;
}


int SubstractionExpressionGrammarAction(const int left, const int right) {
	LogDebug("\tTrackDefinitionsGrammarAction(%d, %d)", left, right);
	return 1;
}

int DivisionExpressionGrammarAction(const int left, const int right) {
	LogDebug("\tDivisionExpressionGrammarAction(%d, %d)", left, right);
	return 1;
}

int VariableNameGrammarAction(const int value) {
	LogDebug("\tVariableNameGrammarAction(%d)", value);
	return 1;
}



