#include "../../backend/support/logger.h"
#include "../../backend/support/symbolsTable.h"
#include "flex-actions.h"
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "flex-actions.h".
 *
 * Cada función debe realizar 2 operaciones básicas para lograr el streaming
 * de tokens hacia Bison:
 *
 *	1) Computar los atributos del token y almacenarlos donde sea conveniente
 *		(en la tabla de símbolos, en "yylval", o en ambos).
 *	2) Retornar el token que identifica el terminal identificado.
 *
 * Bison utilizará el token retornado en el punto (2) para matchear dicho
 * terminal en la gramática. Por otro lado, el valor almacenado en "yylval" es
 * el que Bison proveerá como valor semántico al realizar una reducción
 * (mediante $1, $2, $3, etc.).
 */


// TOKENS DE CREACION (SONG, NOTE Y TRACK)
token SongDefinitionPatternAction(char * lexeme) {
	LogDebug("SongDefinitionPatternAction: '%s'.", lexeme);
	yylval.token = SONG;
	return SONG;
}

token NoteDefinitionPatternAction(char * lexeme) {
	LogDebug("NoteDefinitionPatternAction: '%s'.", lexeme);
	yylval.token = NOTE;
	return NOTE;
}

token TrackDefinitionPatternAction(char * lexeme) {
	LogDebug("TrackDefinitionPatternAction: '%s'.", lexeme);
	yylval.token = TRACK;
	return TRACK;
}


//TOKENS DE EXPRESSIONS Y PALABRAS RESERVADAS
token AddPatternAction(char * lexeme) {
	LogDebug("AddPatternAction: '%s'.", lexeme);
	yylval.token = ADD;
	return ADD;
}

token RepeatPatternAction(char * lexeme) {
	LogDebug("RepeatPatternAction: '%s'.", lexeme);
	yylval.token = MULT;
	return MULT;
}

token SubstractPatternAction(const char * lexeme) {
	LogDebug("SubtractionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = SUB;
	return SUB;
}


token DividePatternAction(const char * lexeme) {
	LogDebug("DivisionPatternAction: '%s'.", lexeme);
	yylval.token = DIV;
	return DIV;
}


token OpenParenthesisPatternAction(const char * lexeme) {
	LogDebug("OpenParenthesisPatternAction: '%s'.", lexeme);
	yylval.token = OPEN_PARENTHESIS;
	return OPEN_PARENTHESIS;
}

token CloseParenthesisPatternAction(const char * lexeme) {
	LogDebug("CloseParenthesisPatternAction: '%s'.", lexeme);
	yylval.token = CLOSE_PARENTHESIS;
	return CLOSE_PARENTHESIS;
}

token OpenBracePatternAction(const char * lexeme) {
	LogDebug("OpenBracePatternAction: '%s'.", lexeme);
	yylval.token = OPEN_BRACE;
	return OPEN_BRACE;
}

token CloseBracePatternAction(const char * lexeme) {
	LogDebug("CloseBracePatternAction: '%s'.", lexeme);
	yylval.token = CLOSE_BRACE;
	return CLOSE_BRACE;
}

// "EXPRESIONES REGULARES"

//Llama el enum de chord
token ChordPatternAction(const char * lexeme) {
	LogDebug("ChordPatternAction: '%s'.", lexeme);
	yylval.chord = malloc(sizeof(int));
	*(yylval.integer) = atoi(lexeme);
	return CHORD_VALUE;
}

//Llama el enum de note
token NotePatternAction(const char * lexeme) {
	
	yylval.note = malloc(sizeof(Note));
	if(strcmp(lexeme, "do") == 0) {
		*(yylval.note) = DO;
	} else if (strcmp(lexeme, "re") == 0) {
		*(yylval.note) = RE;
	} else if (strcmp(lexeme, "mi") == 0) {
		*(yylval.note) = MI;
	}else if (strcmp(lexeme, "fa") == 0) {
		*(yylval.note) = FA;
	} else if (strcmp(lexeme, "sol") == 0) {
		*(yylval.note) = SOL;
	}else if (strcmp(lexeme, "la") == 0) {
		*(yylval.note) = LA;
	} else {
		*(yylval.note) = SI;
	} 
	LogDebug("NotePatternAction: '%s'.", lexeme);
	
	return NOTE_VALUE;
}

token IntegerPatternAction(const char * lexeme) {
	LogDebug("IntegerPatternAction: '%s'", lexeme);
	yylval.integer = malloc(sizeof(int));
	*(yylval.integer) = atoi(lexeme);
	return REPETITION;
}

token TempoPatternAction(const char * lexeme) {
	LogDebug("TempoPatternAction: '%s'.", lexeme);
	char * aux;
	yylval.tempo = malloc(sizeof(double));
	*(yylval.tempo) = strtod(lexeme, &aux);
	return TEMPO_VALUE;
}

//Llama el enum de rhythm
token RhythmPatternAction(const char * lexeme) {
	LogDebug("RhythmPatternAction: '%s'.", lexeme);
	
	yylval.rhythm = malloc(sizeof(Rhythm));
	if(strcmp(lexeme, "q") == 0) {
		*(yylval.rhythm) = q;
	} else if (strcmp(lexeme, "qqq") == 0) {
		*(yylval.rhythm) = qqq;
	}else if (strcmp(lexeme, "h") == 0) {
		*(yylval.rhythm) = h;
	} else {
		*(yylval.rhythm) = w;
	}

	return RHYTHM_VALUE;
}

//Llama el enum de instrument
token InstrumentPatternAction(const char * lexeme) {
	LogDebug("InstrumentPatternAction: '%s'.", lexeme);

	yylval.instrument = malloc(sizeof(Instrument));	
	if(strcmp(lexeme, "P") == 0) {
		*(yylval.instrument) = P;
	} else if (strcmp(lexeme, "F") == 0) {
		*(yylval.instrument) = F;
	}

	return INSTRUMENT;
}

token VariablePatternAction(char * lexeme, const int lenght) {
	LogDebug("VariablePatternAction: '%s'.", lexeme);
    char * aux = malloc(lenght +1);
	strncpy(aux,lexeme,lenght);
	yylval.string = aux;
	return VARIABLE_NAME;
}


void IgnoredPatternAction(const char * lexeme, const int length) {
	LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
	// Como no debe hacer nada con el patrón, solo se loguea en consola.
}


token UnknownPatternAction(const char * lexeme, const int length) {
	LogDebug("UnknownPatternAction: '%s' (lenght = %d).", lexeme, length);
	yylval.token = YYUNDEF;
	// Al emitir este token, el compilador aborta la ejecución.
	return YYUNDEF;
}