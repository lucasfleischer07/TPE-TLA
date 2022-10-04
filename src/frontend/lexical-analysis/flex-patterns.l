%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno


/* Patrones reutilizables. */
endline			    \n
whitespace		    [ \f\n\r\t\v]
integer 	        [0-9]+          
tempo               ([0-9]){1,2}((\.)([0-9]){1})?
duration            (q|qqq|h|w)
rhythm              (q|qqq|h|w)
note                (do|re|mi|fa|sol|la|si|r)#?
instrument          (P|F)
chord               (G-Major|C-Major)


%%

"song"                                      { return SongDefinitionPatternAction(yytext); }
"note"                                      { return NoteDefinitionPatternAction(yytext); }
"track"                                     { return TrackDefinitionPatternAction(yytext); }

"+"                                         { return AddPatternAction(yytext); }
"*"                                         { return RepeatPatternAction(yytext); }
"-"                                         { return SubstractPatternAction(yytext); }
"{"                                         { return OpenBracePatternAction(yytext); }
"}"                                         { return CloseBracePatternAction(yytext); }
"/"                                         { return DividePatternAction(yytext); }
"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }


{chord}                                     { return ChordPatternAction(yytext);}
{note}                                      { return NotePatternAction(yytext);}

{tempo}                                     { return TempoPatternAction(yytext); }
{rhythm}                                    { return RhythmPatternAction(yytext); }
{instrument}                                { return InstrumentPatternAction(yytext); }

{integer}									{ return IntegerPatternAction(yytext); }
{whitespace}								{ return IgnoredPatternAction(yytext); }
.											{ return UnknownPatternAction(yytext); }

%%

