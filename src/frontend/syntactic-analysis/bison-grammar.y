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
	int program;
	int code;
	int instructionsArray;
	int instruction;
	int singleExpression;
	int doubleExpression;
	int definitions;
	int definition;
	int song;
	int track;
	int note;
	int tempo;
	int integer;
	int instrument;
	int note_value;
	int rhythm;
	int chord;

	// Terminales.
	token token;

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
%token <song> SONG_NAME
%token <track> TRACK_NAME
%token <note> NOTE_NAME
%token <rhythm> RHYTHM_VALUE
%token <chord> CHORD_VALUE
%token <instrument> INSTRUMENT
%token <note_value> NOTE_VALUE 


// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <code> code
%type <instructionsArray> instructionsArray
%type <instruction> instruction
%type <singleExpression> singleExpression
%type <doubleExpression> doubleExpression
%type <definitions> definitions
%type <definition> definition
%type <song> song
%type <track> track
%type <note> note


// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MULT DIV



// El símbolo inicial de la gramatica.
%start program

%%

program: code														{$$ = ProgramGrammarAction($1); }
	; 

code: definitions instructionsArray									{$$ = CodeGrammarAction($1,$2); } 
	;

definitions: definition definitions									{$$ = DefinitionsGrammarAction($1,$2); }	
	| definition													{$$ = DefinitionGrammarAction($1); }
	;

definition:SONG song												{$$ = SongGrammarAction($1,$2); }
| TRACK track														{$$ = TrackGrammarAction($1,$2); }
| NOTE note															{$$ = NoteGrammarAction($1,$2); }
	;


instructionsArray: instruction										{$$ =InstructionGrammarAction($1);}
	| instruction instructionsArray									{$$ =InstructionsGrammarAction($1, $2);}
	;


instruction: singleExpression 										{$$ = SimpleExpressionGrammarAction($1);}
	| doubleExpression												{$$ = DoubleExpressionGrammarAction($1);}
	;

singleExpression: note NOTE_VALUE									{$$ = NoteValueExpressionGrammarAction($1,$2);}
	| note NOTE_VALUE RHYTHM_VALUE 									{$$ = RhythmExpressionGrammarAction($1,$2,$3);}
	| note NOTE_VALUE RHYTHM_VALUE CHORD_VALUE 						{$$ = NoteFullDefinitionExpressionGrammarAction($1,$2,$3,$4);}
	| track  INSTRUMENT												{$$ = TrackInstrumentGrammarAction($1, $2);}
	| track TEMPO_VALUE												{$$ = TempoExpressionGrammarAction($1, $2);}
	| track MULT TEMPO_VALUE										{$$ = MultiplicationExpressionGrammarAction($1,$2,$3);}
	| OPEN_PARENTHESIS track CLOSE_PARENTHESIS						{$$ = ParentesisExpressionGramarAction($2);}
	| track															{$$ = TrackTermGrammarAction($1);}
	| note															{$$ = NoteTermGrammarAction($1);}
	| song OPEN_BRACE REPETITION CLOSE_BRACE						{$$ = RepetitionGrammarAction($1,$3);}
	;

doubleExpression: song ADD singleExpression							{$$ = SongAdditionExpressionGrammarAction($1, $3);}
	| track ADD singleExpression									{$$ = TrackAdditionExpressionGrammarAction($1, $3);}
	| song SUB note													{$$ = SubstractionNoteExpressionGrammarAction($1, $3);}
	| song SUB track												{$$ = SubstractionTrackExpressionGrammarAction($1, $3);}
	| track SUB note												{$$ = TrackSubstractionNoteExpressionGrammarAction($1, $3);}
	| song DIV note													{$$ = DivisionExpressionGrammarAction($1, $3);}
	;

song: SONG_NAME														{$$ = SongTermGrammarAction($1);}				
	;

																	
track: TRACK_NAME													{$$ = TrackTermGrammarAction($1);}
	;


note: NOTE_NAME														{$$ = NoteTermGrammarAction($1);}
	;

%%
