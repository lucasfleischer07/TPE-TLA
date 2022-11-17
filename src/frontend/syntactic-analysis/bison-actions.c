#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include "./src/backend/symbolsTable.h"
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

//ver si es void o program
Program * ProgramGrammarAction(Code * code) {
	Program * program = malloc(sizeof(Program));
	program->code = code;

	LogDebug("\tProgramGrammarAction(%d)", code);
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
	state.result = code;
	return code;
}

//todas estan van a llamar a funciones del back
int CodeGrammarAction(Definitions * definitions, InstructionsArray * instructionsArray) {
	Code * definitionsAndInstructions = malloc(sizeof(Code));
	definitionsAndInstructions->definitions = definitions;
	definitionsAndInstructions->instructionArray = instructionsArray;
		
	// LogDebug("\tCodeGrammarAction(%d, %d)", left, right);
	return definitionsAndInstructions;
}

Code * OnlyDefinitionsGrammarAction(Definitions * definitions) {
	Code * onlyDefinitions = malloc(sizeof(Code));
	onlyDefinitions->definitions = definitions;
	onlyDefinitions->instructionArray = NULL;

	//iterativo
	// LogDebug("\tOnlyDefinitionsGrammarAction(%d)", value);
	return onlyDefinitions;
}

Definitions * DefinitionsGrammarAction(Definition * definitionParam, Definitions * definitionsParam) {
	Definitions * definition = malloc(sizeof(Definitions));
	definition->definition = definitionParam;
	definition->definitions = definitionsParam;

	//hay q hacerlos iterativos
	// LogDebug("\tDefinitionsGrammarAction(%s, %s)", definition->definition->variableName->name, );
	return definition;
}

int DefinitionGrammarAction(Definition * definitionParam) {
	Definitions * definition = malloc(sizeof(Definitions));
	definition->definition = definitionParam;
	definition->definitions = NULL;

	LogDebug("\tDefinitionsGrammarAction(%s)", definition->definition->variableName->name);
	return definition;
}

Definition * SongGrammarAction(Variable * variableType, VariableName * variableName) {
	Definition * songDefinition = malloc(sizeof(Definition));
	songDefinition->variableType = variableType;
	songDefinition->variableName->name = variableName;
	
	// LogDebug("\tNoteGrammarAction(%d, %d)", left, right);
	return songDefinition;
}

Definition * TrackGrammarAction(Variable * variableType, VariableName * variableName) {
	Definition * trackDefinition = malloc(sizeof(Definition));
	trackDefinition->variableType = variableType;
	trackDefinition->variableName->name = variableName;
	
	// LogDebug("\tNoteGrammarAction(%d, %d)", left, right);
	return trackDefinition;
}

Definition * NoteGrammarAction(Variable * variableType, VariableName * variableName) {
	Definition * noteDefinition = malloc(sizeof(Definition));
	noteDefinition->variableType = variableType;
	noteDefinition->variableName->name = variableName;
	
	// LogDebug("\tNoteGrammarAction(%d, %d)", left, right);
	return noteDefinition;
}

InstructionsArray * InstructionGrammarAction(Instruction * instruction) {
	InstructionsArray * instructionsArray = malloc(sizeof(InstructionsArray));
	instructionsArray->instruction = instruction;
	instructionsArray->instructionArray = NULL;

	// LogDebug("\tInstructionGrammarAction(%d)", value);
	return instructionsArray;
}

InstructionsArray * InstructionsGrammarAction(Instruction * instruction, InstructionsArray * instructionArrayParam) {
	InstructionsArray * instructionsArray = malloc(sizeof(InstructionsArray));
	instructionsArray->instruction = instruction;
	instructionsArray->instructionArray = instructionArrayParam;
	
	//Ver q es mejor impimir
	// LogDebug("\tSimpleExpressionGrammarAction(%d, %d)", left, right);
	return instructionsArray;
}

Instruction * SimpleExpressionGrammarAction(SingleExpression * singleExpression) {
	Instruction * singleExpressionInstruction = malloc(sizeof(Instruction));
	singleExpressionInstruction->singleExpression = singleExpression;
	singleExpressionInstruction->doubleExpression = NULL;

	LogDebug("\tSimpleExpressionGrammarAction(%s)", singleExpressionInstruction->singleExpression->variableName->name);
	return singleExpressionInstruction;
}

Instruction * DoubleExpressionGrammarAction(DoubleExpression * doubleExpression) {
	Instruction * doubleExpressionInstruction = malloc(sizeof(Instruction));
	doubleExpressionInstruction->doubleExpression = doubleExpression;
	doubleExpressionInstruction->singleExpression = NULL;

	LogDebug("\tDoubleExpressionGrammarAction(%s, %s)", doubleExpressionInstruction->doubleExpression->variableNameLeft->name, doubleExpressionInstruction->doubleExpression->variableNameRight->name);
	return doubleExpressionInstruction;
}

int NoteValueExpressionGrammarAction(const int left, const int right) {
	LogDebug("\tNoteValueExpressionGrammarAction(%d, %d)", left, right);
	return 1;
}

int RhythmExpressionGrammarAction(const int left, const int middle, const int right) {
	LogDebug("\tRhythmExpressionGrammarAction(%d, %d,%d)", left, middle,right);
	return 1;
}

SingleExpression * NoteFullDefinitionExpressionGrammarAction(const int left, const int middleLeft,const int middleRight, const int right) {
	SingleExpression * singleExpression = malloc(sizeof(SingleExpression));
	singleExpression->variableName = variableName;
	 //ver q onda el note_values
	
	LogDebug("\tNoteFullDefinitionExpressionGrammarAction(%d, %d, %d, %d)", left, middleLeft,middleRight, right);
	return singleExpression;
}

SingleExpression * TrackInstrumentGrammarAction(VariableName * variableName, Values instrumentValue) {
	SingleExpression * singleExpression = malloc(sizeof(SingleExpression));
	singleExpression->variableName = variableName;

	ValueStruct * valueStruct = malloc(sizeof(ValueStruct));
	singleExpression->firstValueType = valueStruct;
	valueStruct->typeValue = INSTRUMENT;
	valueStruct->value = NULL;

	valueStruct->name = malloc(sizeof(char));
	*(valueStruct->name) = instrumentValue;

	LogDebug("\tTempoExpressionGrammarAction(%s, instrument: %s)", variableName->name, valueStruct->name);
	return singleExpression;
}

SingleExpression * TempoExpressionGrammarAction(VariableName * variableName, Values tempoValue) {
	SingleExpression * singleExpression = malloc(sizeof(SingleExpression));
	singleExpression->variableName = variableName;

	ValueStruct * valueStruct = malloc(sizeof(ValueStruct));
	singleExpression->firstValueType = valueStruct;
	valueStruct->typeValue = TEMPO;
	valueStruct->value = NULL;

	valueStruct->name = malloc(sizeof(char));
	*(valueStruct->name) = tempoValue;

	LogDebug("\tTempoExpressionGrammarAction(%s, tempo: %s)", variableName->name, valueStruct->name);
	return singleExpression;
}


//VER XQ ESTA IGUAL A REPETITION, CUAL ERA LA DIFERENCIA
SingleExpression * MultiplicationExpressionGrammarAction(VariableName * variableName, int repetition) {
	SingleExpression * singleExpression = malloc(sizeof(SingleExpression));
	singleExpression->variableName = variableName;

	ValueStruct * valueStruct = malloc(sizeof(ValueStruct));
	singleExpression->firstValueType = valueStruct;
	valueStruct->typeValue = REPETITION;
	valueStruct->name = NULL;

	valueStruct->value = malloc(sizeof(int));
	*(valueStruct->value) = repetition;

	LogDebug("\tMultiplicationExpressionGrammarAction(%s, * %d)", variableName->name, repetition);
	return singleExpression;
}

int ParentesisExpressionGramarAction(const int value) {
	//TODO NOSE Q HACE no recordamos
	LogDebug("\tDefinitionsGrammarAction(%d)", value);
	return 1;
}


SingleExpression * RepetitionGrammarAction(VariableName * variableName, int repetition){
	SingleExpression * singleExpression = malloc(sizeof(SingleExpression));
	singleExpression->variableName = variableName;
	
	ValueStruct * valueStruct = malloc(sizeof(ValueStruct));
	singleExpression->firstValueType = valueStruct;
	valueStruct->typeValue = REPETITION;
	valueStruct->name = NULL;

	valueStruct->value = malloc(sizeof(int));
	*(valueStruct->value) = repetition;

	LogDebug("\tRepetitionGrammarAction(%s, repetition: (%d))", variableName->name, repetition);
	return singleExpression;
}

DoubleExpression * DoubleExpressionAdditionExpressionGrammarAction(VariableName * variableNameLeft, DoubleExpression * doubleExpressionRight) {
	DoubleExpression * doubleExpression = malloc(sizeof(DoubleExpression));
	doubleExpression->variableNameLeft = variableNameLeft;
	doubleExpression->variableNameRight = NULL;
	doubleExpression->type = ADDITION;
	doubleExpression->doubleExpression = doubleExpressionRight;
	doubleExpression->singleExpression = NULL;

	// TODO PRINT RECURSIVO
	// LogDebug("\tDoubleExpressionAdditionExpressionGrammarAction(%s, +DExp %s)", variableNameLeft->name, doubleExpressionRight->variableName->name);
	return doubleExpression;
}

DoubleExpression * VariableAdditionExpressionGrammarAction(VariableName * variableNameLeft, SingleExpression * singleExpressionRight) {
	DoubleExpression * doubleExpression = malloc(sizeof(DoubleExpression));
	doubleExpression->variableNameLeft = variableNameLeft;
	doubleExpression->variableNameRight = NULL;
	doubleExpression->type = ADDITION;
	doubleExpression->doubleExpression = NULL;
	doubleExpression->singleExpression = singleExpressionRight;

	LogDebug("\tVariableAdditionExpressionGrammarAction(%s, +SiExp %s)", variableNameLeft->name, singleExpressionRight->variableName->name);
	return doubleExpression;
}

DoubleExpression * VariableAdditionVariableGrammarAction(VariableName * variableNameLeft, VariableName * variableNameRight) {
	DoubleExpression * doubleExpression = malloc(sizeof(DoubleExpression));
	doubleExpression->variableNameLeft = variableNameLeft;
	doubleExpression->variableNameRight = variableNameRight;
	doubleExpression->type = ADDITION;
	doubleExpression->doubleExpression = NULL;
	doubleExpression->singleExpression = NULL;

	LogDebug("\tVariableAdditionVariableGrammarAction(%s, + %s)", variableNameLeft->name, variableNameRight->name);
	return doubleExpression;
}


DoubleExpression * SubstractionExpressionGrammarAction(VariableName * variableNameLeft, VariableName * variableNameRight) {
	DoubleExpression * doubleExpression = malloc(sizeof(DoubleExpression));
	doubleExpression->variableNameLeft = variableNameLeft;
	doubleExpression->variableNameRight = variableNameRight;
	doubleExpression->type = SUBTRACTION;
	doubleExpression->doubleExpression = NULL;
	doubleExpression->singleExpression = NULL;

	LogDebug("\tSubstractionExpressionGrammarAction(%s, - %s)", variableNameLeft->name, variableNameRight->name);
	return doubleExpression;
}

DoubleExpression * DivisionExpressionGrammarAction(VariableName * variableNameLeft, VariableName * variableNameRight) {
	DoubleExpression * doubleExpression = malloc(sizeof(DoubleExpression));
	doubleExpression->variableNameLeft = variableNameLeft;
	doubleExpression->variableNameRight = variableNameRight;
	doubleExpression->type = DIVISION;
	doubleExpression->doubleExpression = NULL;
	doubleExpression->singleExpression = NULL;

	LogDebug("\tDivisionExpressionGrammarAction(%s, / %s)", variableNameLeft->name, variableNameRight->name);
	return doubleExpression;
}

VariableName * VariableNameGrammarAction(char * variable) {
	VariableName * variableName = malloc(sizeof(VariableName));
    variableName->name = (char*) malloc((strlen(variable) + 1) * sizeof (char));
    strcpy(variableName->name, variable);

	LogDebug("\tVariableNameGrammarAction(%s)", variable);
	return variableName;
}



