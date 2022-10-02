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
/*crlf			    \r\n    */
whitespace		    [ \f\n\r\t\v]
/*variable_name 	    [a-zA-Z]+[_0-9A-Za-z]* */
integer 	        [0-9]+          
string              \"[^\n\r]*\" 
duration            (q|qqq|h|w)
note                (do|re|mi|fa|sol|la|si|r)#?
instrument          (P|F)



%%

/*Nuestros*/
"start"                                     { return StartPatternAction(yytext); }
"end"                                       { return EndPatternAction(yytext); }    
"create_track"                              { return CreateTrackPatternAction(yytext); }
"+"                                         { return AddPatternAction(yytext); }
"*"                                         { return RepeatPatternAction(yytext); }
"-"                                         { return SubstactPatternAction(yytext); }
"create_song"                               { return CreateSongPatternAction(yytext); }
"while"                                     { return CiclePatternAction(yytext); }
"{"                                         { return OpenBracesPattermAction(yytext); }
"}"                                         { return CloseBracesPatternAction(yytext); }
"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }
"chord"                                     { return ChordPatternAction(yytext); }
/*Catedra*/

"start"                                     { return StartPatternAction(yytext); }
"end"                                       { return EndPatternAction(yytext); }
"is"                                        { return AssignPatternAction(yytext); }

"plus"                                      {return PlusPatternAction(yytext);}
"minus"                                     {return MinusPatternAction(yytext);}     
"times"                                     {return MultiplyPatternAction(yytext);}
"by"                                        {return DividePatternAction(yytext);}

"if"                                        { return IfPatternAction(yytext); }
"then"                                      { return ThenPatternAction(yytext); }
"else"                                      { return ElsePatternAction(yytext); }
"end_if"                                    { return EndIfPatternAction(yytext); }

"compute"                                   { return DoStatementPatternAction(yytext); }
"while"                                     { return WhilePatternAction(yytext); }

"+"                                         { return addPatternAction(yytext);}
">"                                         {return GreaterPatternAction(yytext);}
"<"                                         {return LowerPatternAction(yytext);}
"="                                         {return EqualsPatternAction(yytext);}
"!="                                        {return NotEqualsPatternAction(yytext);}
"and"                                       {return AndPatternAction(yytext);}
"or"                                        {return OrPatternAction(yytext);}
"not"                                       {return NotPatternAction(yytext);}
"true"                                      {return TruePatternAction(yytext);}
"false"                                     {return FalsePatternAction(yytext);}
`
"print"                                     { return PrintPatternAction(yytext); }
"print_to_chords"                           { return PrintToChordsPatternAction(yytext); }
"concat_notes"                              { return ConcatNotesPatternAction(yytext); }
"to_notes"                                  { return ToNotesPatternAction(yytext); }
"to_chord"                                  { return ToChordPatternAction(yytext); }
"create_music_score"                        { return CreateMusicScorePatternAction(yytext); }
"is_note"                                   { return IsNotePatternAction(yytext); }
"is_chord"                                  { return IsChordPatternAction(yytext); }

"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }
";"                                         { return DelimiterPatternAction(yytext); }

"note"                                      { return NoteTypePatternAction(yytext); }
"chord"                                     { return ChordTypePatternAction(yytext); }
"string"                                    { return StringTypePatternAction(yytext); }
"integer"                                   { return IntegerTypePatternAction(yytext); }

{chord}                                     { return ChordPatternAction(yytext);}
{note}                                      { return NotePatternAction(yytext);}
{integer}									{ return IntegerPatternAction(yytext); }
{string}                                    { return StringPatternAction(yytext); }
{whitespace}								{ IgnoredPatternAction(yytext); }
{variable_name}                             { return VariableNamePatternAction(yytext); }
.											{ return UnknownPatternAction(yytext); }

%%