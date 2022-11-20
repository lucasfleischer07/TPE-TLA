#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/
typedef struct Expression Expression;

/**
* Para cada no-terminal se define una nueva estructura que representa su tipo
* de dato y, por lo tanto, su nodo en el AST (Árbol de Sintaxis Abstracta).
*/
typedef struct {
	int value;
} Constant;

/**
* En caso de que un no-terminal ("Factor" en este caso), posea más de una
* regla de producción asociada, se crea además de la estructura un enumerado
* que identitifque cada reducción posible (cada regla de producción). Luego,
* se agrega una instancia de este enumerado dentro del nodo del no-terminal.
*
* De este modo, al recorrer el AST, es posible determinar qué nodos hijos
* posee según el valor de este enumerado.
*/

typedef enum {
	DO='C',
	RE='D',
	MI='E',
	FA='F',
	SOL='G', 
	LA='A',
	SI='B',
} Note;

typedef enum {
	P,
	F,
} Instrument;

// typedef enum {
// 	G_Major,
// 	C_Major,
// } Chord;

typedef enum {
	q='q',
	qqq='i',
	h='h',
	w='w',
} Rhythm;

typedef enum {
	//Binary
	ADDITION,
	SUBTRACTION,
	DIVISION,

	//Unary
	NOTE_ASSIGNMENT,
	MULTIPLICATION,
	TEMPO_ASSINGMENT,
	NOTE_AND_RHYTHM_ASSIGNMENT,
	NOTE_RHYTHM_CHORD_ASSIGNMENT,
	PARENTHESIS,
	INSTRUMENT_ASSINGMENT,
} ExpressionType;

typedef enum {
	TEMPO_TYPE,
	RHYTHM_TYPE,
	NOTE_FIGURE,
	INSTRUMENT_TYPE,
	CHORD_TYPE,
	REPETITION_TYPE
} Values;

typedef enum {
	SONG_VAR,
	TRACK_VAR,
	NOTE_VAR
} Variable;

typedef struct {
	Values typeValue;
	Note *note;
	Instrument *instrument;
	int *chord;
	Rhythm *rhythm;
	int *repetition;
	double *tempo;
} ValueStruct;

typedef struct {
	char * name;
} VariableName;

typedef struct {
	VariableName *variableName;
	ValueStruct *firstValueType;
	ValueStruct *secondValueType;
	ValueStruct *thirdValueType;
	ExpressionType type;
} UnaryExpression;

typedef struct binaryExp{
	VariableName *variableNameLeft;
	VariableName *variableNameRight;
	ExpressionType type;
	struct binaryExp *binaryExpression;
	UnaryExpression *unaryExpression;
} BinaryExpression;

typedef struct {
	UnaryExpression *unaryExpression;
	BinaryExpression *binaryExpression;
} Instruction;

typedef struct instructArray{
	Instruction *instruction;
	struct instructArray *instructionArray; 
} InstructionsArray;

typedef struct {
	Variable variableType;
	VariableName *variableName;
} Definition;

typedef struct definitions{
	Definition *definition;
	struct definitions *definitions;
} Definitions;	

typedef struct {
	Definitions *definitions;
	InstructionsArray *instructionArray;
} Code;

typedef struct {
	Code *code;
} Program;

#endif
