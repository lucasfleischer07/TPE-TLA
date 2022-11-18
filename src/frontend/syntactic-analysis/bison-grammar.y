%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	Factor factor;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	Program *program;
	Code *code;
	InstructionsArray *instructionsArray;
	Instruction *instruction;
	UnaryExpression *unaryExpression;
	BinaryExpression *binaryExpression;
	Definitions *definitions;
	Definition *definition;
	Variable *variable;
	Values *value;
	
	int *integer;
	Note *note;
	Instrument *instrument;
	Chord *chord;
	double *tempo;
	char *string;
	Rhythm *rhythm;

	// Terminales.
	token token;
	VariableName *variableName;

}


// IDs y tipos de los tokens terminales generados desde Flex.
/* Parentesis */
%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_BRACE
%token <token> CLOSE_BRACE
%token <token> SONG
%token <token> NOTE
%token <token> TRACK

 /* Operadores aritméticos */
%token <token> ADD
%token <token> SUB
%token <token> MULT
%token <token> DIV


/* Palabras reservadas */
%token <tempo> TEMPO_VALUE
%token <integer> REPETITION
%token <rhythm> RHYTHM_VALUE
%token <chord> CHORD_VALUE
%token <instrument> INSTRUMENT
%token <note> NOTE_VALUE 
%token <string> VARIABLE_NAME


// Tipos de dato para los no-terminales generados desde Bison.
%type <variableName> variableName
%type <program> program
%type <code> code
%type <instructionsArray> instructionsArray
%type <instruction> instruction
%type <unaryExpression> unaryExpression
%type <binaryExpression> binaryExpression
%type <definitions> definitions
%type <definition> definition


// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MULT DIV



// El símbolo inicial de la gramatica.

%start program

%%

program: code																	{ProgramGrammarAction($1); }
	; 

code: definitions															    {$$ = OnlyDefinitionsGrammarAction($1); }
	| definitions instructionsArray												{$$ = CodeGrammarAction($1,$2); } 
	;

definitions: definition definitions												{$$ = DefinitionsGrammarAction($1,$2); }	
	| definition																{$$ = DefinitionGrammarAction($1); }
	;

definition: SONG variableName													{$$ = SongGrammarAction($2); }
	| TRACK variableName														{$$ = TrackGrammarAction($2); }
	| NOTE variableName															{$$ = NoteGrammarAction($2); }
	;


instructionsArray: instruction													{$$ =InstructionGrammarAction($1);}
	| instruction instructionsArray												{$$ =InstructionsGrammarAction($1, $2);}
	;

instruction: unaryExpression 													{$$ = UnaryExpressionGrammarAction($1);}
	| binaryExpression															{$$ = BinaryExpressionGrammarAction($1);}
	;

unaryExpression: variableName NOTE_VALUE										{$$ = NoteValueExpressionGrammarAction($1,$2);}
	| variableName NOTE_VALUE RHYTHM_VALUE 										{$$ = RhythmExpressionGrammarAction($1,$2,$3);}
	| variableName NOTE_VALUE RHYTHM_VALUE CHORD_VALUE 							{$$ = NoteFullDefinitionExpressionGrammarAction($1,$2,$3,$4);}
	| variableName INSTRUMENT													{$$ = TrackInstrumentGrammarAction($1, $2);}
	| variableName TEMPO_VALUE													{$$ = TempoExpressionGrammarAction($1, $2);}
	| variableName MULT REPETITION												{$$ = MultiplicationExpressionGrammarAction($1,$3);}
	| OPEN_PARENTHESIS variableName CLOSE_PARENTHESIS							{$$ = ParentesisExpressionGramarAction($2);}
	| variableName OPEN_BRACE REPETITION CLOSE_BRACE							{$$ = RepetitionGrammarAction($1,$3);}
	;

binaryExpression: variableName ADD binaryExpression								{$$ = BinaryExpressionAdditionExpressionGrammarAction($1, $3);}
	| variableName ADD unaryExpression											{$$ = VariableAdditionExpressionGrammarAction($1, $3);}
	| variableName ADD variableName												{$$ = VariableAdditionVariableGrammarAction($1, $3);}
	| variableName SUB variableName												{$$ = SubstractionExpressionGrammarAction($1, $3);}
	| variableName DIV variableName												{$$ = DivisionExpressionGrammarAction($1, $3);}
	;


variableName: VARIABLE_NAME														{$$ = VariableNameGrammarAction($1);}


%%
