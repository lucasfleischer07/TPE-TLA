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
tempo               ([0-9]){1,2}((\.)([0-9]){1})?
string              \"[^\n\r]*\" 
rhythm              (q|qqq|h|w)
note                (do|re|mi|fa|sol|la|si|r)#?
instrument          (P|F)
chord               (G-Major|C-Major)
integer             [0-9]+

%%

"start"                                     { return StartPatternAction(yytext); }
"end"                                       { return EndPatternAction(yytext); }    
"song"                                      { return SongPatterAction(yytext); }
"note"                                      { return NotePatternAction(yytext); }
"track"                                     { return TrackPatternAction(yytext); }

"+"                                         { return AddPatternAction(yytext); }
"*"                                         { return RepeatPatternAction(yytext); }
"-"                                         { return SubstactPatternAction(yytext); }
"/"                                         { return DividePatternAction(yytext); }
"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }
"{"											{ return OpenBracePatternAction(yytext); }
"}"											{ return CloseBracePatternAction(yytext); }
";"                                         { return DelimiterPatternAction(yytext); }

/*DE ACA NO METIMOS NINGUNA*/
"print"                                     { return PrintPatternAction(yytext); }
"print_to_chords"                           { return PrintToChordsPatternAction(yytext); }
"concat_notes"                              { return ConcatNotesPatternAction(yytext); }
"to_notes"                                  { return ToNotesPatternAction(yytext); }
"to_chord"                                  { return ToChordPatternAction(yytext); }
"create_music_score"                        { return CreateMusicScorePatternAction(yytext); }
"is_note"                                   { return IsNotePatternAction(yytext); }
"is_chord"                                  { return IsChordPatternAction(yytext); }

{chord}                                     { return ChordPatternAction(yytext);}
{note}                                      { return NotePatternAction(yytext);}

{tempo}                                     { return TempoPatternAction(yytext); }
{rhythm}                                    { return RhythmPatternAction(yytext); }
{instrument}                                { return InstrumentPatternAction(yytext); }

{integer}									{ return IntegerPatternAction(yytext); }
{string}                                    { return StringPatternAction(yytext); }
{whitespace}								{ return IgnoredPatternAction(yytext); }
.											{ return UnknownPatternAction(yytext); }

%%