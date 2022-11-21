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

//Manejo de Chords
token ChordPatternAction(const char * lexeme, const int lenght) {
	yylval.chord = (int *) calloc(lenght + 1, sizeof(int));

	if(strncmp(lexeme, "C0", lenght) == 0) {
		*(yylval.chord) = 0;
	} else if (strncmp(lexeme, "C1", lenght) == 0) {
		*(yylval.chord) = 1;
	} else if (strncmp(lexeme, "C2", lenght) == 0) {
		*(yylval.chord) = 2;
	} else if (strncmp(lexeme, "C3", lenght) == 0) {
		*(yylval.chord) = 3;
	} else if (strncmp(lexeme, "C4", lenght) == 0) {
		*(yylval.chord) = 4;
	} else if (strncmp(lexeme, "C5", lenght) == 0) {
		*(yylval.chord) = 5;
	} else if (strncmp(lexeme, "C6", lenght) == 0) {
		*(yylval.chord) = 6;
	} else if (strncmp(lexeme, "C7", lenght) == 0) {
		*(yylval.chord) = 7;
	} else if (strncmp(lexeme, "C8", lenght) == 0) {
		*(yylval.chord) = 8;
	} else if(strncmp(lexeme, "C9", lenght) == 0) {
		*(yylval.chord) = 9;
	} else {
		*(yylval.chord) = 10;
	}

	LogDebug("ChordPatternAction: '%s'.", lexeme);

	return CHORD_VALUE;
}

//Llama el enum de note
token NotePatternAction(const char * lexeme, const int lenght) {
	yylval.note = (Note *) calloc(lenght + 1, sizeof(Note));

	if(strncmp(lexeme, "do", lenght) == 0) {
		*(yylval.note) = DO;
	} else if (strncmp(lexeme, "sleep", lenght) == 0) {
		*(yylval.note) = SLEEP;
	} else if (strncmp(lexeme, "mi", lenght) == 0) {
		*(yylval.note) = MI;
	}else if (strncmp(lexeme, "fa", lenght) == 0) {
		*(yylval.note) = FA;
	} else if (strncmp(lexeme, "sol", lenght) == 0) {
		*(yylval.note) = SOL;
	}else if (strncmp(lexeme, "la", lenght) == 0) {
		*(yylval.note) = LA;
	} else if (strncmp(lexeme, "re", lenght) == 0){
		*(yylval.note) = RE;
	} else {
		*(yylval.note) = SI;
	}
	LogDebug("NotePatternAction: '%s'.", lexeme);
	
	return NOTE_VALUE;
}

token IntegerPatternAction(const char * lexeme, const int lenght) {
	LogDebug("IntegerPatternAction: '%s'", lexeme);
	yylval.integer = (int *) calloc(lenght + 1, sizeof(int));
	*(yylval.integer) = atoi(lexeme);
	return REPETITION;
}

token TempoPatternAction(const char * lexeme, const int lenght) {
	LogDebug("TempoPatternAction: '%s'.", lexeme);
	char * aux;
	yylval.tempo = (double *) calloc(lenght + 1, sizeof(double));
	*(yylval.tempo) = strtod(lexeme, &aux);
	return TEMPO_VALUE;
}

//Llama el enum de rhythm
token RhythmPatternAction(const char * lexeme, const int lenght) {	
	yylval.rhythm = (Rhythm *) calloc(lenght + 1, sizeof(Rhythm));

	if(strncmp(lexeme, "q", lenght) == 0) {
		*(yylval.rhythm) = q;
	} else if (strncmp(lexeme, "qqq", lenght) == 0) {
		*(yylval.rhythm) = qqq;
	}else if (strncmp(lexeme, "h", lenght) == 0) {
		*(yylval.rhythm) = h;
	} else {
		*(yylval.rhythm) = w;
	}

	LogDebug("RhythmPatternAction: '%s'.", lexeme);

	return RHYTHM_VALUE;
}

//Llama el enum de instrument
token InstrumentPatternAction(const char * lexeme, const int lenght) {
	yylval.instrument = (Instrument *) calloc(lenght +1, sizeof(Instrument));
	if(strncmp(lexeme, "P", lenght) == 0) {
		*(yylval.instrument) = P;
	} else if (strncmp(lexeme, "F", lenght) == 0) {
		*(yylval.instrument) = F;
	}

	LogDebug("InstrumentPatternAction: '%s'.", lexeme);

	return INSTRUMENT;
}

token VariablePatternAction(char * lexeme, const int lenght) {
    char * aux = (char *) calloc(lenght +1, sizeof(char));
	strncpy(aux,lexeme,lenght);
	yylval.string = aux;

	LogDebug("VariablePatternAction: '%s'.", lexeme);

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