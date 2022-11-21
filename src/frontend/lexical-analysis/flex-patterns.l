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
tempo               ([0-9]){1,2}((\.)([0-9]){1})
rhythm              (q|qqq|h|w)
note                (do|re|mi|fa|sol|la|si|sleep)#?
instrument          (P|F)            
chord               C([0-9]|10)
variableName        [a-zA-Z0-9_]


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


{chord}                                     { return ChordPatternAction(yytext, yyleng);}
{note}                                      { return NotePatternAction(yytext, yyleng);}

{integer}									{ return IntegerPatternAction(yytext, yyleng); }

{tempo}                                     { return TempoPatternAction(yytext, yyleng); }
{rhythm}                                    { return RhythmPatternAction(yytext, yyleng); }
{instrument}                                { return InstrumentPatternAction(yytext, yyleng); }


{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }
{variableName}+                             { return VariablePatternAction(yytext, yyleng); }
.											{ return UnknownPatternAction(yytext, yyleng); }

%%

