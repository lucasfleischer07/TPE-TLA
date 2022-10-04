#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>

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

token StartPatternAction(char * lexeme) {
	LogDebug("StartPatternAction: '%s'.", lexeme);
	yylval.token = START;
	return START;
}

token EndPatternAction(char * lexeme) {
	LogDebug("EndPatternAction: '%s'.", lexeme);
	yylval.token = END;
	return END;
}

token SongPatternAction(char * lexeme) {
	LogDebug("SongPatternAction: '%s'.", lexeme);
	yylval.token = ;
	return END;
}


// TODO: FALTA EL ADD PATTERN ACTION


token RepeatPatternAction(char * lexeme) {
	LogDebug("RepeatPatternAction: '%s'.", lexeme);
	yylval.token = REPETITION;
	return REPETITION;
}


token AddToTrackPatternAction(char * lexeme) {
	LogDebug("AddToTrackPatternAction: '%s'.", lexeme);
	yylval.token = ADD;
	return ADD;
}


token SubtractPatternAction(const char * lexeme) {
	LogDebug("SubtractionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = SUB;
	return SUB;
}


token DivideOperatorPatternAction(const char * lexeme) {
	LogDebug("DivisionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = DIV;
	return DIV;
}


token OpenParenthesisPatternAction(const char * lexeme) {
	LogDebug("OpenParenthesisPatternAction: '%s'.", lexeme);
	yylval.token = OPEN_PARENTHESIS;
	return OPEN_PARENTHESIS;
}

token CloseParenthesisAction(const char * lexeme) {
	LogDebug("CloseParenthesisAction: '%s'.", lexeme);
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


// TODO: FALTA DelimiterPatternAction


token NotePatternAction(const char * lexeme) {
	LogDebug("NotePatternAction: '%s'.", lexeme);
	yylval.token = SCALE;
	return SCALE;
}


token ChordPatternAction(const char * lexeme) {
	LogDebug("ChordPatternAction: '%s'.", lexeme);
	yylval.token = CHORD_VALUE;
	return CHORD_VALUE;
}


token TempoPatternAction(const char * lexeme) {
	LogDebug("TempoPatternAction: '%s'.", lexeme);
	yylval.token = TEMPO_VALUE;
	return TEMPO_VALUE;
}


token RhythmPatternAction(const char * lexeme) {
	LogDebug("DurationPatternAction: '%s'.", lexeme);
	yylval.token = RHYTHM_VALUE;
	return RHYTHM_VALUE;
}


token InstrumentPatternAction(const char * lexeme) {
	LogDebug("InstrumentPatternAction: '%s'.", lexeme);
	yylval.token = INST_VALUE;
	return INST_VALUE;
}


token UnknownPatternAction(const char * lexeme, const int length) {
	LogDebug("UnknownPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = YYUNDEF;
	// Al emitir este token, el compilador aborta la ejecución.
	return YYUNDEF;
}


void IgnoredPatternAction(const char * lexeme, const int length) {
	LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
	// Como no debe hacer nada con el patrón, solo se loguea en consola.
}







/* LOS DE LA CATEDRA */
void BeginCommentPatternAction() {
	LogDebug("BeginCommentPatternAction.");
}

void EndCommentPatternAction() {
	LogDebug("EndCommentPatternAction.");
}

token AdditionOperatorPatternAction(const char * lexeme) {
	LogDebug("AdditionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = ADD;
	return ADD;
}

token CloseParenthesisPatternAction(const char * lexeme) {
	LogDebug("CloseParenthesisPatternAction: '%s'.", lexeme);
	yylval.token = CLOSE_PARENTHESIS;
	return CLOSE_PARENTHESIS;
}

token DivisionOperatorPatternAction(const char * lexeme) {
	LogDebug("DivisionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = DIV;
	return DIV;
}



token DurationPatternAction(const char * lexeme) {
	LogDebug("Duration: '%s' ", lexeme);
	yylval.token = DURATION;
	return DURATION;
}


token MultiplicationOperatorPatternAction(const char * lexeme) {
	LogDebug("MultiplicationOperatorPatternAction: '%s'.", lexeme);
	yylval.token = MUL;
	return MUL;
}

token OpenParenthesisPatternAction(const char * lexeme) {
	LogDebug("OpenParenthesisPatternAction: '%s'.", lexeme);
	yylval.token = OPEN_PARENTHESIS;
	return OPEN_PARENTHESIS;
}

token SubtractionOperatorPatternAction(const char * lexeme) {
	LogDebug("SubtractionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = SUB;
	return SUB;
}