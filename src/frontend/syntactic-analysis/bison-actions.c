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

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/

//ver si es void o program
void ProgramGrammarAction(Code *code) {
	Program *program = malloc(sizeof(Program));
	program->code = code;

	LogDebug("\tProgramGrammarAction(%d)", code);
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
}

//todas estan van a llamar a funciones del back
Code *CodeGrammarAction(Definitions *definitions, InstructionsArray *instructionsArray) {
	Code *definitionsAndInstructions = malloc(sizeof(Code));
	definitionsAndInstructions->definitions = definitions;
	definitionsAndInstructions->instructionArray = instructionsArray;
		
	LogDebug("\tCodeGrammarAction(%s, %s)", "definitions", "instructionsArray");
	return definitionsAndInstructions;
}

Code *OnlyDefinitionsGrammarAction(Definitions *definitions) {
	Code *onlyDefinitions = malloc(sizeof(Code));
	onlyDefinitions->definitions = definitions;
	onlyDefinitions->instructionArray = NULL;

	LogDebug("\tOnlyDefinitionsGrammarAction(%s)", "definitions");
	return onlyDefinitions;
}

Definitions *DefinitionsGrammarAction(Definition *definitionParam, Definitions *definitionsParam) {
	Definitions *definition = malloc(sizeof(Definitions));
	definition->definition = definitionParam;
	definition->definitions = definitionsParam;

	LogDebug("\tDefinitionsGrammarAction(%s, %s)", 'def', "defs");
	return definition;
}

Definitions *DefinitionGrammarAction(Definition *definitionParam) {
	Definitions *definition = malloc(sizeof(Definitions));
	definition->definition = definitionParam;
	definition->definitions = NULL;

	LogDebug("\tDefinitionsGrammarAction(%s)", definition->definition->variableName->name);
	return definition;
}

Definition *SongGrammarAction(VariableName *variableName) {
	if( isVariableInTable(state.table,variableName->name)){
		LogDebug("\tERROR SongGrammarAction(%s, %s) this variable already exists", "SONG", songDefinition->variableName->name);
		state.failed=true;
	}
	
	Definition *songDefinition = malloc(sizeof(Definition));
	songDefinition->variableType = SONG_VAR;
	songDefinition->variableName->name = variableName;
	addSymbolToTable(state.table,variableName->name,SONG_SYMBOL);
	LogDebug("\tSongGrammarAction(%s, %s)", "SONG", songDefinition->variableName->name);
	return songDefinition;
}

Definition *TrackGrammarAction(VariableName *variableName) {
	if( isVariableInTable(state.table,variableName->name)){
		LogDebug("\tERROR TrackGrammarAction(%s, %s) this variable already exists", "TRACK", trackDefinition->variableName->name);
		state.failed=true;
	}
	
	Definition *trackDefinition = malloc(sizeof(Definition));
	trackDefinition->variableType = TRACK_VAR;
	trackDefinition->variableName->name = variableName;
	addSymbolToTable(state.table,variableName->name,TRACK_SYMBOL);
	LogDebug("\tTrackGrammarAction(%s, %s)", "TRACK", trackDefinition->variableName->name);
	return trackDefinition;
}

Definition *NoteGrammarAction(VariableName *variableName) {
	if( isVariableInTable(state.table,variableName->name)){
		LogDebug("\tERROR NoteGrammarAction(%s, %s) this variable already exists", "NOTE", variableName->name);
		state.failed=true;
	}
	
	Definition *noteDefinition = malloc(sizeof(Definition));
	noteDefinition->variableType = NOTE_VAR;
	noteDefinition->variableName->name = variableName;
	addSymbolToTable(state.table,variableName->name,NOTE_SYMBOL);
	LogDebug("\tNoteGrammarAction(%s, %s)", "NOTE", noteDefinition->variableName->name);
	return noteDefinition;
}

InstructionsArray *InstructionGrammarAction(Instruction *instruction) {
	InstructionsArray *instructionsArray = malloc(sizeof(InstructionsArray));
	instructionsArray->instruction = instruction;
	instructionsArray->instructionArray = NULL;

	LogDebug("\tInstructionGrammarAction(%s)", "instruction");
	return instructionsArray;
}

InstructionsArray *InstructionsGrammarAction(Instruction *instruction, InstructionsArray *instructionArrayParam) {
	InstructionsArray *instructionsArray = malloc(sizeof(InstructionsArray));
	instructionsArray->instruction = instruction;
	instructionsArray->instructionArray = instructionArrayParam;
	
	LogDebug("\tInstructionsGrammarAction(%s, %s)", "instruction", "instruction Array");
	return instructionsArray;
}

Instruction *UnaryExpressionGrammarAction(UnaryExpression *unaryExpression) {
	Instruction *unaryExpressionInstruction = malloc(sizeof(Instruction));
	unaryExpressionInstruction->unaryExpression = unaryExpression;
	unaryExpressionInstruction->binaryExpression = NULL;

	LogDebug("\tSimpleExpressionGrammarAction(%s)", unaryExpressionInstruction->unaryExpression->variableName->name);
	return unaryExpressionInstruction;
}

Instruction *BinaryExpressionGrammarAction(BinaryExpression *binaryExpression) {
	Instruction *binaryExpressionInstruction = malloc(sizeof(Instruction));
	binaryExpressionInstruction->binaryExpression = binaryExpression;
	binaryExpressionInstruction->unaryExpression = NULL;

	LogDebug("\tbinaryExpressionGrammarAction(%s, %s)", binaryExpressionInstruction->binaryExpression->variableNameLeft->name, binaryExpressionInstruction->binaryExpression->variableNameRight->name);
	return binaryExpressionInstruction;
}

UnaryExpression *NoteValueExpressionGrammarAction(VariableName *variableName, Note *noteValue) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name,NOTE_SYMBOL)){
		LogDebug("\t NoteValueExpressionGrammarAction variable %s is not defined or is not a note",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression *unaryExpression = malloc(sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;
	ValueStruct *valueStruct = malloc(sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;	
	valueStruct->tempo = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->repetition = NULL;
	
	valueStruct->note = noteValue;
	valueStruct->typeValue = NOTE_FIGURE;

	unaryExpression->secondValueType = NULL;

	unaryExpression->thirdValueType = NULL;

	unaryExpression->type = NOTE_ASSIGNMENT;

	LogDebug("\tNoteValueExpressionGrammarAction(%s, %d)", unaryExpression->variableName, unaryExpression->firstValueType->note);
}

UnaryExpression *RhythmExpressionGrammarAction(VariableName *variableName, Note *noteValue, Rhythm *rythmValue) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name,NOTE_SYMBOL)){
		LogDebug("\t RhythmExpressionGrammarAction variable %s is not defined or is not a note",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression *unaryExpression = malloc(sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;

	ValueStruct *valueStruct = malloc(sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;	
	valueStruct->tempo = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->repetition = NULL;

	valueStruct->note = noteValue;
	valueStruct->typeValue = NOTE_FIGURE;

	valueStruct = malloc(sizeof(ValueStruct));
	unaryExpression->secondValueType = valueStruct;	
	valueStruct->tempo = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->repetition = NULL;
	valueStruct->note = NULL;

	valueStruct->rhythm = rythmValue;
	valueStruct->typeValue = RHYTHM_TYPE;

	unaryExpression->thirdValueType = NULL;

	unaryExpression->type = NOTE_AND_RHYTHM_ASSIGNMENT;

	LogDebug("\tRhythmExpressionGrammarAction(%s, %s,%s)",unaryExpression->variableName, "noteValue", "rhythm value");
	return unaryExpression;
}

UnaryExpression *NoteFullDefinitionExpressionGrammarAction(VariableName *variableName, Note *noteValue, Rhythm *rythmValue, Chord *chordValue) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name,NOTE_SYMBOL)){
		LogDebug("\t NoteFullDefinitionExpressionGrammarAction variable %s is not defined or is not a note",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression *unaryExpression = malloc(sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;

	ValueStruct *valueStruct = malloc(sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;	
	valueStruct->tempo = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->repetition = NULL;

	valueStruct->note = noteValue;
	valueStruct->typeValue = NOTE_FIGURE;

	valueStruct = malloc(sizeof(ValueStruct));
	unaryExpression->secondValueType = valueStruct;	
	valueStruct->tempo = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->note = NULL;
	valueStruct->repetition = NULL;


	valueStruct->rhythm = rythmValue;
	valueStruct->typeValue = RHYTHM_TYPE;

	valueStruct = malloc(sizeof(ValueStruct));
	unaryExpression->thirdValueType = valueStruct;	
	valueStruct->tempo = NULL;
	valueStruct->instrument = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->note = NULL;
	valueStruct->repetition = NULL;


	valueStruct->chord = chordValue;
	valueStruct->typeValue = CHORD_TYPE;


	unaryExpression->type = NOTE_RHYTHM_CHORD_ASSIGNMENT;
	
	LogDebug("\tNoteFullDefinitionExpressionGrammarAction(%s, %s, %s, %s)",unaryExpression->variableName, "noteValue", "rhythmValue", "chordValue");
	return unaryExpression;
}

UnaryExpression * TrackInstrumentGrammarAction(VariableName *variableName, Instrument *instrumentValue) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name,TRACK_SYMBOL)){
		LogDebug("\t TrackInstrumentGrammarAction variable %s is not defined or is not a note",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression * unaryExpression = malloc(sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;

	ValueStruct * valueStruct = malloc(sizeof(ValueStruct));
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

	unaryExpression->type == INSTRUMENT_ASSINGMENT;

	LogDebug("\tTempoExpressionGrammarAction(%s, instrument: %d)", variableName->name, valueStruct->instrument);
	return unaryExpression;
}

UnaryExpression * TempoExpressionGrammarAction(VariableName *variableName, double *tempoValue) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name,SONG_SYMBOL)){
		LogDebug("\t TempoExpressionGrammarAction variable %s is not defined or is not a note",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression *unaryExpression = malloc(sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;
	unaryExpression->type = TEMPO_TYPE;

	ValueStruct *valueStruct = malloc(sizeof(ValueStruct));
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

	LogDebug("\tTempoExpressionGrammarAction(%s, tempo: %s)", variableName->name, "tempoValue");
	return unaryExpression;
}


//VER XQ ESTA IGUAL A REPETITION, CUAL ERA LA DIFERENCIA
UnaryExpression *MultiplicationExpressionGrammarAction(VariableName *variableName, int *repetition) {
	if(!isVariableInTable(state.table,variableName->name) || !isVariableOfType(state.table,variableName->name,TRACK_SYMBOL)){
		LogDebug("\t MultiplicationExpressionGrammarAction variable %s is not defined or is not a note",variableName->name);
		state.failed=true;
	}
	
	UnaryExpression *unaryExpression = malloc(sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;
	unaryExpression->type == MULTIPLICATION;

	ValueStruct *valueStruct = malloc(sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;
	valueStruct->typeValue = REPETITION_TYPE;
	valueStruct->note = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->tempo = NULL;

	// valueStruct->repetition = malloc(sizeof(int));
	valueStruct->repetition = repetition;

	unaryExpression->secondValueType = NULL;
	unaryExpression->thirdValueType = NULL;

	LogDebug("\tMultiplicationExpressionGrammarAction(%s, * %d)", variableName->name, repetition);
	return unaryExpression;
}

//ESTE NO ESTA CHEQUEADO XQ NO SE EL CASO DE USO
UnaryExpression *ParentesisExpressionGramarAction(VariableName *variableName) {
	UnaryExpression * unaryExpression = malloc(sizeof(UnaryExpression));
	unaryExpression->variableName->name = variableName;
	unaryExpression->firstValueType = NULL;
	unaryExpression->secondValueType = NULL;
	unaryExpression->thirdValueType = NULL;
	unaryExpression->type = PARENTHESIS;
	LogDebug("\tDefinitionsGrammarAction(%S)", unaryExpression->variableName->name);
	return unaryExpression;
}

//ESTE NO ESTA CHEQUEADO XQ NO SE EL CASO DE USO
UnaryExpression *RepetitionGrammarAction(VariableName *variableName, int *repetition){
	UnaryExpression *unaryExpression = malloc(sizeof(UnaryExpression));
	unaryExpression->variableName = variableName;
	
	ValueStruct *valueStruct = malloc(sizeof(ValueStruct));
	unaryExpression->firstValueType = valueStruct;
	valueStruct->typeValue = REPETITION_TYPE;
	valueStruct->note = NULL;
	valueStruct->instrument = NULL;
	valueStruct->chord = NULL;
	valueStruct->rhythm = NULL;
	valueStruct->repetition = NULL;

	valueStruct->repetition = malloc(sizeof(int));
	*(valueStruct->repetition) = repetition;

	LogDebug("\tRepetitionGrammarAction(%s, repetition: (%d))", variableName->name, repetition);
	return unaryExpression;
}

//Chequeo que ambas variables existan, despues chequeo la compatibilidad
static int checkAddition(VariableName *variableNameLeft,VariableName *variableNameRight){
	if( !isVariableInTable(state.table,variableNameLeft->name) || !isVariableInTable(state.table,variableNameRight->name)){
		return false;
	}

	if ( isVariableOfType(state.table,variableNameLeft->name,TRACK_SYMBOL)){
		if( isVariableOfType(state.table,variableNameRight->name,TRACK_SYMBOL) || isVariableOfType(state.table,variableNameRight->name,NOTE_SYMBOL)){
			return true;
		}
	}else if( isVariableOfType(state.table,variableNameLeft->name,SONG_SYMBOL)){
		if( isVariableOfType(state.table,variableNameRight->name,TRACK_SYMBOL) ){
			return true;
		}
	}
	return false;
}


BinaryExpression *BinaryExpressionAdditionExpressionGrammarAction(VariableName *variableNameLeft, BinaryExpression *binaryExpressionRight) {
	if( !checkAddition(variableNameLeft,binaryExpressionRight->variableNameLeft)){
		LogDebug("\t BinaryExpressionAdditionExpressionGrammarAction (%s, +binaryExp %s) the combination of variables is not compatible or one of the is not defined",variableNameLeft->name,binaryExpressionRight->variableNameLeft->name);
		state.failed=true;
	}
	BinaryExpression *binaryExpression = malloc(sizeof(BinaryExpression));
	binaryExpression->variableNameLeft = variableNameLeft;
	binaryExpression->variableNameRight = NULL;
	binaryExpression->type = ADDITION;
	binaryExpression->binaryExpression = binaryExpressionRight;
	binaryExpression->unaryExpression = NULL;

	LogDebug("\tbinaryExpressionAdditionExpressionGrammarAction(%s, +binaryExp %s)", variableNameLeft->name, "binary Expression");
	return binaryExpression;
}

BinaryExpression *VariableAdditionExpressionGrammarAction(VariableName *variableNameLeft, UnaryExpression *unaryExpressionRight) {
	if( !checkAddition(variableNameLeft,unaryExpressionRight->variableName->name)){
		LogDebug("\t VariableAdditionExpressionGrammarAction (%s, +binaryExp %s) the combination of variables is not compatible or one of the is not defined",variableNameLeft->name,unaryExpressionRight->variableName->name);
		state.failed=true;
	}
	
	BinaryExpression *binaryExpression = malloc(sizeof(BinaryExpression));
	binaryExpression->variableNameLeft = variableNameLeft;
	binaryExpression->variableNameRight = NULL;
	binaryExpression->type = ADDITION;
	binaryExpression->binaryExpression = NULL;
	binaryExpression->unaryExpression = unaryExpressionRight;

	LogDebug("\tVariableAdditionExpressionGrammarAction(%s, +UnaExp %s)", variableNameLeft->name, unaryExpressionRight->variableName->name);
	return binaryExpression;
}

BinaryExpression *VariableAdditionVariableGrammarAction(VariableName *variableNameLeft, VariableName *variableNameRight) {
	if( !checkAddition(variableNameLeft,variableNameRight->name)){
		LogDebug("\t VariableAdditionVariableGrammarAction (%s, +binaryExp %s) the combination of variables is not compatible or one of the is not defined",variableNameLeft->name,variableNameRight->name);
		state.failed=true;
	}
	
	BinaryExpression *binaryExpression = malloc(sizeof(BinaryExpression));
	binaryExpression->variableNameLeft = variableNameLeft;
	binaryExpression->variableNameRight = variableNameRight;
	binaryExpression->type = ADDITION;
	binaryExpression->binaryExpression = NULL;
	binaryExpression->unaryExpression = NULL;

	LogDebug("\tVariableAdditionVariableGrammarAction(%s, + %s)", variableNameLeft->name, variableNameRight->name);
	return binaryExpression;
}

static int checkSubDivAndMult(VariableName *variableNameLeft,VariableName *variableNameRight){
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

BinaryExpression *SubstractionExpressionGrammarAction(VariableName *variableNameLeft, VariableName *variableNameRight) {
	if( !checkSubDivAndMult(variableNameLeft,variableNameRight->name)){
		LogDebug("\t VariableAdditionVariableGrammarAction (%s, +binaryExp %s) the combination of variables is not compatible or one of the is not defined",variableNameLeft->name,variableNameRight->name);
		state.failed=true;
	}
	
	BinaryExpression *binaryExpression = malloc(sizeof(BinaryExpression));
	binaryExpression->variableNameLeft = variableNameLeft;
	binaryExpression->variableNameRight = variableNameRight;
	binaryExpression->type = SUBTRACTION;
	binaryExpression->binaryExpression = NULL;
	binaryExpression->unaryExpression = NULL;

	LogDebug("\tSubstractionExpressionGrammarAction(%s, - %s)", variableNameLeft->name, variableNameRight->name);
	return binaryExpression;
}

BinaryExpression *DivisionExpressionGrammarAction(VariableName *variableNameLeft, VariableName *variableNameRight) {
	if( !checkSubDivAndMult(variableNameLeft,variableNameRight->name)){
		LogDebug("\t VariableAdditionVariableGrammarAction (%s, +binaryExp %s) the combination of variables is not compatible or one of the is not defined",variableNameLeft->name,variableNameRight->name);
		state.failed=true;
	}
	
	BinaryExpression *binaryExpression = malloc(sizeof(BinaryExpression));
	binaryExpression->variableNameRight = variableNameRight;
	binaryExpression->type = DIVISION;
	binaryExpression->binaryExpression = NULL;
	binaryExpression->unaryExpression = NULL;

	LogDebug("\tDivisionExpressionGrammarAction(%s, / %s)", variableNameLeft->name, variableNameRight->name);
	return binaryExpression;
}

VariableName * VariableNameGrammarAction(char *variable) {
	VariableName *variableName = malloc(sizeof(VariableName));
    variableName->name = (char*) malloc((strlen(variable) + 1) * sizeof (char));
    strcpy(variableName->name, variable);

	LogDebug("\tVariableNameGrammarAction(%s)", variableName->name);
	return variableName;
}



