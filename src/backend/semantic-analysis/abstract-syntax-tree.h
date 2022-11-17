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
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
} ExpressionType;

typedef enum {
	TEMPO,
	RHYTHM,
	NOTE,
	INSTRUMENT,
	CHORD,
	REPETITION
} Values;

typedef enum {
	SONG,
	TRACK,
	NOTE
} Variable;

typedef struct {
	Values typeValue;
	char * name; 
	int * value;
} ValueStruct;

typedef struct {
	char * name;
} VariableName;

typedef struct {
	VariableName * variableNameLeft;
	VariableName * variableNameRight;
	ExpressionType type;
	DoubleExpression * doubleExpression;
	SingleExpression * singleExpression;
} DoubleExpression;

typedef struct {
	VariableName * variableName;
	ValueStruct * firstValueType;
	ValueStruct * secondValueType;
	ValueStruct * thirdValueType;
	ExpressionType type;
} SingleExpression;

typedef struct {
	SingleExpression * singleExpression;
	DoubleExpression * doubleExpression;
} Instruction;

typedef struct {
	Instruction * instruction;
	InstructionsArray * instructionArray; 
} InstructionsArray;

typedef struct {
	Variable * variableType;
	VariableName * variableName;
} Definition;

typedef struct {
	Definition * definition;
	Definitions * definitions;
} Definitions;

typedef struct {
	Definitions * definitions;
	InstructionsArray * instructionArray;
} Code;

typedef struct {
	Code * code;
} Program;

#endif
