#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 *
 * Debería existir una acción por cada patrón disponible en Flex (es decir,
 * por cada regla).
 *
 * Solo aquellas acciones que tengan interés en conocer el largo del lexema
 * emplean el parámetro adicional "length". Esto es útil cuando se desea
 * asignar memoria dinámica, y por lo tanto, se debe saber exactamente el
 * largo de aquello que se va a almacenar.
 */

token IntegerPatternAction(const char * lexeme, const int lenght);

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char * lexeme, const int length);


// * NUESTRAS!!!!
// token StartPatternAction(char * lexeme);
// token EndPatternAction(char * lexeme);


token SongDefinitionPatternAction(char * lexeme);
token NoteDefinitionPatternAction(char * lexeme);
token TrackDefinitionPatternAction(char * lexeme);

token AddPatternAction(char * lexeme);
token RepeatPatternAction(char * lexeme);
token SubstractPatternAction(const char * lexeme);
token OpenBracePatternAction(const char * lexeme);
token CloseBracePatternAction(const char * lexeme);
token DividePatternAction(const char * lexeme);
token OpenParenthesisPatternAction(const char * lexeme);
token CloseParenthesisPatternAction(const char * lexeme);

token ChordPatternAction(const char * lexeme);
token NotePatternAction(const char * lexeme);

token TempoPatternAction(const char * lexeme);
token RhythmPatternAction(const char * lexeme);
token InstrumentPatternAction(const char * lexeme);

token VariablePatternAction(char * lexeme, const int length);

// Patrón desconocido, permite abortar debido a un error de sintaxis.
token UnknownPatternAction(const char * lexeme, const int lenght);
#endif
