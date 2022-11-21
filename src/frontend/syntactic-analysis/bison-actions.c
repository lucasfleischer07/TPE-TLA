#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include "../../backend/support/symbolsTable.h"
/**
 * Implementación de "bison-grammar.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char *string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}


static int checkSubDivAndMult(VariableName *variableNameLeft, VariableName *variableNameRight){
	if( !isVariableInTable(state.table,variableNameLeft->name) || !isVariableInTable(state.table,variableNameRight->name)){
		return false;
	}

	if ( isVariableOfType(state.table,variableNameLeft->name,TRACK_SYMBOL)){
		if( isVariableOfType(state.table,variableNameRight->name,NOTE_SYMBOL)) {
			return true;
		}
	}
	return false;
}

//Chequeo que ambas variables existan, despues chequeo la compatibilidad
static int checkAddition(VariableName *variableNameLeft,VariableName *variableNameRight){
	LogDebug("Entrando a checkAddition");
	if(!isVariableInTable(state.table,variableNameLeft->name) || !isVariableInTable(state.table,variableNameRight->name)){
		LogDebug("Variable no esta en la tabla %s", variableNameLeft->name);
		LogDebug("Variable no esta en la tabla %s", variableNameRight->name);
		return false;
	}

	if (isVariableOfType(state.table,variableNameLeft->name,TRACK_SYMBOL)){
		LogDebug("A la izquierda tengo una track: %s", variableNameLeft->name);
		if(isVariableOfType(state.table,variableNameRight->name,TRACK_SYMBOL) || isVariableOfType(state.table,variableNameRight->name,NOTE_SYMBOL)){
			LogDebug("Lo que tengo a la derecha es: %s", variableNameLeft->name);
			return true;
		}
	}else if(isVariableOfType(state.table, variableNameLeft->name,SONG_SYMBOL)) {
		LogDebug("A la izquierda tengo una song: %s", variableNameLeft->name);
		if(isVariableOfType(state.table,variableNameRight->name,TRACK_SYMBOL)) {
			LogDebug("Lo que tengo a la derecha es: %s", variableNameLeft->name);
			return true;
		}
	}
	LogDebug("No entre en ninguno Sad");
	return false;
}

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/

//ver si es void o program
Program *ProgramGrammarAction(Code *code) {
	Program *program = (Program *) calloc(1, sizeof(Program));
	program->code = code;

	LogDebug("\tProgramGrammarAction(%s)", "Code");
	/*
	* "state" es una variable global que almacena el estado del compilador,
	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
	* es utilizada en la función "main".
	*/
	
	state.succeed = !state.failed;
	
	/*
	* Por otro lado, "result" contiene el resultado de aplicar el análisis
	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
	* la expresión se computa on-the-fly, y es la razón por la cual esta
	* variable es un simple entero, en lugar de un nodo.
	*/
	state.result = program;

	return program;
}

//todas estan van a llamar a funciones del back
Code *CodeGrammarAction(Definitions *definitions, InstructionsArray *instructionsArray) {
	Code *definitionsAndInstructions = (Code *) calloc(1, sizeof(Code));
	definitionsAndInstructions->definitions = definitions;
	definitionsAndInstructions->instructionArray = instructionsArray;
		
	LogDebug("\tCodeGrammarAction(%s, %s)", "definitions", "instructionsArray");
	return definitionsAndInstructions;
}

Code *OnlyDefinitionsGrammarAction(Definitions *definitions) {
	Code *onlyDefinitions = (Code *) calloc(1, sizeof(Code));
	onlyDefinitions->definitions = definitions;
	onlyDefinitions->instructionArray = NULL;

	LogDebug("\tOnlyDefinitionsGrammarAction(%s)", onlyDefinitions->definitions->definition->variableName->name);
	return onlyDefinitions;
}

Definitions *DefinitionsGrammarAction(Definition *definitionParam, Definitions *definitionsParam) {
	Definitions *definition = (Definitions *) calloc(1, sizeof(Definitions));
	definition->definition = definitionParam;
	definition->definitions = definitionsParam;

	LogDebug("\tDefinitionsGrammarAction(Definition: %s, Definitions: %s)", definition->definition->variableName->name, definition->definitions->definition->variableName->name);
	return definition;
}

Definitions *DefinitionGrammarAction(Definition *definitionParam) {
	Definitions *definitions = (Definitions *) calloc(1, sizeof(Definitions));
	definitions->definition = definitionParam;
	definitions->definitions = NULL;

	LogDebug("\tDefinitionGrammarAction(%s)", definitions->definition->variableName->name);
	return definitions;
}

Definition *SongGrammarAction(VariableName *variableName) {
	if(isVariableInTable(state.table,variableName->name)){
		LogDebug("\tERROR SongGrammarAction(%s, %s) this variable already exists", "SONG", variableName->name);
		state.failed=true;
	}
	
	Definition *songDefinition = (Definition *) calloc(1, sizeof(Definition));
	songDefinition->variableType = SONG_VAR;
	songDefinition->variableName = variableName;

	addSymbolToTable(state.table,variableName->name,SONG_SYMBOL);
	LogDebug("\tSongGrammarAction(%s, %s)", "SONG", songDefinition->variableName->name);
	return songDefinition;
}

Definition *TrackGrammarAction(VariableName *variableName) {
	if(isVariableInTable(state.table, variableName->name)){
		LogDebug("\tERROR TrackGrammarAction(%s, %s) this variable already exists", "TRACK", variableName->name);
		state.failed=true;
	}
	
	Definition *trackDefinition = (Definition *) calloc(1, sizeof(Definition));
	trackDefinition->variableType = TRACK_VAR;
	trackDefinition->variableName = variableName;
	addSymbolToTable(state.table,variableName->name,TRACK_SYMBOL);
	LogDebug("\tTrackGrammarAction(%s, %s)", "TRACK", trackDefinition->variableName->name);
	return trackDefinition;
}

Definition *NoteGrammarAction(VariableName *variableName) {
	if(isVariableInTable(state.table,variableName->name)){
		LogDebug("\tERROR NoteGrammarAction(%s, %s) this variable already exists", "NOTE", variableName->name);
		state.failed=true;
	}
	Definition *noteDefinition = (Definition *) calloc(1, sizeof(Definition));
	noteDefinition->variableName = variableName;
	noteDefinition->variableType = NOTE_VAR;
	addSymbolToTable(state.table,variableName->name,NOTE_SYMBOL);
	LogDebug("\tNoteGrammarAction(%s, %s)", "NOTE", noteDefinition->variableName->name);
	return noteDefinition;
}

InstructionsArray *InstructionGrammarAction(Instruction *instruction) {
	InstructionsArray *instructionsArray = (InstructionsArray *) calloc(1, sizeof(InstructionsArray));
	instructionsArray->instruction = instruction;
	instructionsArray->instructionArray = NULL;

	LogDebug("\tInstructionGrammarAction(%s)", "instruction");
	return instructionsArray;
}

InstructionsArray *InstructionsGrammarAction(Instruction *instruction, InstructionsArray *instructionArrayParam) {
	InstructionsArray *instructionsArray = (InstructionsArray *) calloc(1, sizeof(InstructionsArray));
	instructionsArray->instruction = instruction;
	instructionsArray->instructionArray = instructionArrayParam;
	
	LogDebug("\tInstructionsGrammarAction(Instruction: %s, Instruction Array: %s)", "instruction", "instruction Array");
	return instructionsArray;
}

Instruction *UnaryExpressionGrammarAction(UnaryExpression *unaryExpression) {
	Instruction *unaryExpressionInstruction = (Instruction *) calloc(1, sizeof(Instruction));
	unaryExpressionInstruction->unaryExpression = unaryExpression;
	unaryExpressionInstruction->binaryExpression = NULL;

	LogDebug("\tUnaryExpressionGrammarAction(%s)", unaryExpressionInstruction->unaryExpression->variableName->name);
	return unaryExpressionInstruction;
}

Instruction *BinaryExpressionGrammarAction(BinaryExpression *binaryExpression) {
	Instruction *binaryExpressionInstruction = (Instruction *) calloc(1, sizeof(Instruction));
	binaryExpressionInstruction->binaryExpression = binaryExpression;
	binaryExpressionInstruction->unaryExpression = NULL;

	LogDebug("\tBinaryExpressionGrammarAction(%s, %s)", binaryExpressionInstruction->binaryExpression->variableNameLeft->name, binaryExpressionInstruction->binaryExpression->variableNameRight->name);
	return binaryExpressionInstruction;
}

UnaryExpression *NoteValueExpressionGrammarAction(VariableName *variableName, Note *noteValue) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name,NOTE_SYMBOL)){
		LogDebug("\tFailed NoteValueExpressionGrammarAction variable %s is not defined or is not a note",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression *unaryExpression = (UnaryExpression *) calloc(1, sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;

	ValueStruct *valueStruct = (ValueStruct *) calloc(1, sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;	
	unaryExpression->type = NOTE_ASSIGNMENT;

	valueStruct->tempo = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->repetition = NULL;
	
	valueStruct->note = noteValue;
	valueStruct->typeValue = NOTE_FIGURE;

	unaryExpression->secondValueType = NULL;

	unaryExpression->thirdValueType = NULL;

	LogDebug("\tNoteValueExpressionGrammarAction(%s, %d)", unaryExpression->variableName, unaryExpression->firstValueType->note);
	
	return unaryExpression;
}

UnaryExpression *RhythmExpressionGrammarAction(VariableName *variableName, Note *noteValue, Rhythm *rythmValue) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name,NOTE_SYMBOL)){
		LogError("\tFailed RhythmExpressionGrammarAction variable %s is not defined or is not a note",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression *unaryExpression = (UnaryExpression *) calloc(1, sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;

	ValueStruct *valueStruct = (ValueStruct *) calloc(1, sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;	
	valueStruct->tempo = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->repetition = NULL;

	valueStruct->note = noteValue;
	valueStruct->typeValue = NOTE_FIGURE;
	

	ValueStruct *valueStruct2 = (ValueStruct *) calloc(1, sizeof(ValueStruct));
	// valueStruct = (ValueStruct *) calloc(1, sizeof(ValueStruct));
	unaryExpression->secondValueType = valueStruct;	
	valueStruct2->tempo = NULL;
	valueStruct2->instrument = NULL;
	valueStruct2->chord = NULL;
	valueStruct2->repetition = NULL;
	valueStruct2->note = NULL;

	valueStruct2->rhythm = rythmValue;
	valueStruct2->typeValue = RHYTHM_TYPE;

	unaryExpression->thirdValueType = NULL;

	unaryExpression->type = NOTE_AND_RHYTHM_ASSIGNMENT;

	LogDebug("\tRhythmExpressionGrammarAction(Name: %s, Note: %s, Rythm: %s)",unaryExpression->variableName->name, unaryExpression->firstValueType->note, unaryExpression->secondValueType->rhythm);
	return unaryExpression;
}

UnaryExpression *NoteFullDefinitionExpressionGrammarAction(VariableName *variableName, Note *noteValue, Rhythm *rythmValue, int *chordValue) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name,NOTE_SYMBOL)){
		LogDebug("\tFailed NoteFullDefinitionExpressionGrammarAction variable %s is not defined or is not a note",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression *unaryExpression = (UnaryExpression *) calloc(1, sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;

	ValueStruct *valueStruct = (ValueStruct *) calloc(1, sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;	
	valueStruct->tempo = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->repetition = NULL;

	valueStruct->note = noteValue;
	valueStruct->typeValue = NOTE_FIGURE;

	ValueStruct *valueStruct2 = (ValueStruct *) calloc(1, sizeof(ValueStruct));
	unaryExpression->secondValueType = valueStruct2;	
	valueStruct2->tempo = NULL;
	valueStruct2->instrument = NULL;
	valueStruct2->chord = NULL;
	valueStruct2->note = NULL;
	valueStruct2->repetition = NULL;

	valueStruct2->rhythm = rythmValue;
	valueStruct2->typeValue = RHYTHM_TYPE;

	ValueStruct *valueStruct3 = (ValueStruct *) calloc(1, sizeof(ValueStruct));
	unaryExpression->thirdValueType = valueStruct3;	
	valueStruct3->tempo = NULL;
	valueStruct3->instrument = NULL;
	valueStruct3->rhythm = NULL;
	valueStruct3->note = NULL;
	valueStruct3->repetition = NULL;
	valueStruct3->chord = chordValue;
	valueStruct3->typeValue = CHORD_TYPE;


	unaryExpression->type = NOTE_RHYTHM_CHORD_ASSIGNMENT;
	
	LogDebug("\tNoteFullDefinitionExpressionGrammarAction(%s, %s, %s, %d)",unaryExpression->variableName->name, unaryExpression->firstValueType->note, unaryExpression->secondValueType->rhythm, *(unaryExpression->thirdValueType->chord));
	return unaryExpression;
}

UnaryExpression * TrackInstrumentGrammarAction(VariableName *variableName, Instrument *instrumentValue) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name,TRACK_SYMBOL)){
		LogDebug("\tFailed TrackInstrumentGrammarAction variable %s is not defined or is not a note",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression * unaryExpression = (UnaryExpression *) calloc(1, sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;

	ValueStruct * valueStruct = (ValueStruct *) calloc(1, sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;

	valueStruct->typeValue = INSTRUMENT_TYPE;
	valueStruct->instrument = instrumentValue;
	valueStruct->note = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->repetition = NULL;
	valueStruct->tempo = NULL;	

	unaryExpression->secondValueType = NULL;
	unaryExpression->thirdValueType = NULL;

	unaryExpression->type = INSTRUMENT_ASSINGMENT;

	LogDebug("\tTrackInstrumentGrammarAction(%s, instrument: %d)", variableName->name, *(valueStruct->instrument));
	
	return unaryExpression;
}

UnaryExpression * TempoExpressionGrammarAction(VariableName *variableName, double *tempoValue) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name, TRACK_SYMBOL)){
		LogDebug("\tFailed TempoExpressionGrammarAction variable %s is not defined or is not a track",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression *unaryExpression = (UnaryExpression *) calloc(1, sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;
	unaryExpression->type = TEMPO_ASSINGMENT;

	ValueStruct *valueStruct = (ValueStruct *) calloc(1, sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;
	valueStruct->typeValue = TEMPO_TYPE;
	valueStruct->note = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->repetition = NULL;
	
	valueStruct->tempo = tempoValue;

	unaryExpression->secondValueType = NULL;
	unaryExpression->thirdValueType = NULL;

	LogDebug("\tTempoExpressionGrammarAction(%s, tempo: %f)", variableName->name, valueStruct->tempo);
	return unaryExpression;
}


//VER XQ ESTA IGUAL A REPETITION, CUAL ERA LA DIFERENCIA
UnaryExpression *MultiplicationExpressionGrammarAction(VariableName *variableName, int *repetition) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name,TRACK_SYMBOL)){
		LogDebug("\tFailed MultiplicationExpressionGrammarAction variable %s is not defined or is not a note",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression *unaryExpression = (UnaryExpression *) calloc(1, sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;
	unaryExpression->type = MULTIPLICATION;

	ValueStruct *valueStruct = (ValueStruct *) calloc(1, sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;
	valueStruct->typeValue = REPETITION_TYPE;
	valueStruct->note = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->tempo = NULL;

	valueStruct->repetition = repetition;

	unaryExpression->secondValueType = NULL;
	unaryExpression->thirdValueType = NULL;

	LogDebug("\tMultiplicationExpressionGrammarAction(%s, * %d)", variableName->name, *(valueStruct->repetition));
	
	return unaryExpression;
}

//ESTE NO ESTA CHEQUEADO XQ NO SE EL CASO DE USO
UnaryExpression *ParentesisExpressionGramarAction(VariableName *variableName) {
	UnaryExpression * unaryExpression = (UnaryExpression *) calloc(1, sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;
	unaryExpression->firstValueType = NULL;
	unaryExpression->secondValueType = NULL;
	unaryExpression->thirdValueType = NULL;
	unaryExpression->type = PARENTHESIS;
	LogDebug("\tParentesisExpressionGramarAction(%s)", unaryExpression->variableName->name);
	return unaryExpression;
}

//ESTE NO ESTA CHEQUEADO XQ NO SE EL CASO DE USO
UnaryExpression *RepetitionGrammarAction(VariableName *variableName, int *repetition){
	UnaryExpression *unaryExpression = (UnaryExpression *) calloc(1, sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;
	
	ValueStruct *valueStruct = (ValueStruct *) calloc(1, sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;
	valueStruct->typeValue = REPETITION_TYPE;
	valueStruct->note = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;

	valueStruct->repetition = repetition;

	LogDebug("\tRepetitionGrammarAction(%s, repetition: (%d))", variableName->name, *(valueStruct->repetition));
	return unaryExpression;
}

BinaryExpression *BinaryExpressionAdditionExpressionGrammarAction(VariableName *variableNameLeft, BinaryExpression *binaryExpressionRight) {
	if(!checkAddition(variableNameLeft,binaryExpressionRight->variableNameLeft)){
		LogDebug("\tFailed BinaryExpressionAdditionExpressionGrammarAction (%s, +binaryExp %s) the combination of variables is not compatible or one of the is not defined",variableNameLeft->name,binaryExpressionRight->variableNameLeft->name);
		state.failed=true;
	}
	BinaryExpression *binaryExpression = (BinaryExpression *) calloc(1, sizeof(BinaryExpression));
	binaryExpression->variableNameLeft = variableNameLeft;
	binaryExpression->variableNameRight = NULL;
	binaryExpression->type = ADDITION;
	binaryExpression->binaryExpression = binaryExpressionRight;
	binaryExpression->unaryExpression = NULL;

	LogDebug("\tBinaryExpressionAdditionExpressionGrammarAction(%s +binaryExp %s)", variableNameLeft->name, binaryExpression->binaryExpression->type);
	return binaryExpression;
}

BinaryExpression *VariableAdditionExpressionGrammarAction(VariableName *variableNameLeft, UnaryExpression *unaryExpressionRight) {
	if( !checkAddition(variableNameLeft,unaryExpressionRight->variableName)){
		LogDebug("\tFailed VariableAdditionExpressionGrammarAction (%s, +binaryExp %s) the combination of variables is not compatible or one of the is not defined",variableNameLeft->name,unaryExpressionRight->variableName->name);
		state.failed=true;
	}
	
	BinaryExpression *binaryExpression = (BinaryExpression *) calloc(1, sizeof(BinaryExpression));
	binaryExpression->variableNameLeft = variableNameLeft;
	binaryExpression->variableNameRight = NULL;
	binaryExpression->type = ADDITION;
	binaryExpression->binaryExpression = NULL;
	binaryExpression->unaryExpression = unaryExpressionRight;

	LogDebug("\tVariableAdditionExpressionGrammarAction(%s, +UnaExp %s)", variableNameLeft->name, unaryExpressionRight->variableName->name);
	return binaryExpression;
}

BinaryExpression *VariableAdditionVariableGrammarAction(VariableName *variableNameLeft, VariableName *variableNameRight) {
	if( !checkAddition(variableNameLeft,variableNameRight)){
		LogError("\tFailed VariableAdditionVariableGrammarAction (%s +binaryExp %s) the combination of variables is not compatible or one of the is not defined",variableNameLeft->name,variableNameRight->name);
		state.failed=true;
	}
	
	BinaryExpression *binaryExpression = (BinaryExpression *) calloc(1, sizeof(BinaryExpression));
	binaryExpression->variableNameLeft = variableNameLeft;
	binaryExpression->variableNameRight = variableNameRight;
	binaryExpression->type = ADDITION;
	binaryExpression->binaryExpression = NULL;
	binaryExpression->unaryExpression = NULL;

	LogDebug("\tVariableAdditionVariableGrammarAction(%s + %s)", variableNameLeft->name, variableNameRight->name);
	return binaryExpression;
}

BinaryExpression *SubstractionExpressionGrammarAction(VariableName *variableNameLeft, VariableName *variableNameRight) {
	if(!checkSubDivAndMult(variableNameLeft, variableNameRight)){
		LogError("\tFailed SubstractionExpressionGrammarAction (%s +binaryExp %s) the combination of variables is not compatible or one of the is not defined",variableNameLeft->name,variableNameRight->name);
		state.failed=true;
	}
	
	BinaryExpression *binaryExpression = (BinaryExpression *) calloc(1, sizeof(BinaryExpression));
	binaryExpression->variableNameLeft = variableNameLeft;
	binaryExpression->variableNameRight = variableNameRight;
	binaryExpression->type = SUBTRACTION;
	binaryExpression->binaryExpression = NULL;
	binaryExpression->unaryExpression = NULL;

	LogDebug("\tSubstractionExpressionGrammarAction(%s, - %s)", variableNameLeft->name, variableNameRight->name);
	return binaryExpression;
}

BinaryExpression *DivisionExpressionGrammarAction(VariableName *variableNameLeft, VariableName *variableNameRight) {
	if( !checkSubDivAndMult(variableNameLeft,variableNameRight)){
		LogError("\tFailed DivisionExpressionGrammarAction (%s +binaryExp %s) the combination of variables is not compatible or one of the is not defined",variableNameLeft->name,variableNameRight->name);
		state.failed=true;
	}
	
	BinaryExpression *binaryExpression = (BinaryExpression *) calloc(1, sizeof(BinaryExpression));
	binaryExpression->variableNameRight = variableNameRight;
	binaryExpression->type = DIVISION;
	binaryExpression->binaryExpression = NULL;
	binaryExpression->unaryExpression = NULL;

	LogDebug("\tDivisionExpressionGrammarAction(%s / %s)", variableNameLeft->name, variableNameRight->name);
	return binaryExpression;
}

VariableName * VariableNameGrammarAction(char *variable) {
	VariableName *variableName = (VariableName *) calloc(1, sizeof(VariableName));
    variableName->name = (char*) calloc((strlen(variable) + 1), sizeof(char));
    strcpy(variableName->name, variable);

	LogDebug("\tVariableNameGrammarAction(%s)", variableName->name);
	return variableName;
}



