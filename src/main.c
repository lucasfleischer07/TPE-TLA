#include "backend/code-generation/generator.h"
#include "backend/support/logger.h"
#include "backend/support/shared.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include <stdio.h>

// Estado de la aplicación.
CompilerState state;

// Punto de entrada principal del compilador.
const int main(const int argumentCount, const char ** arguments) {
	// Inicializar estado de la aplicación.
	state.program = NULL;
	state.result = 0;
	state.succeed = false;
	state.errorFound = no_error;
	// state.failed = false;
	state.table = newTable();

	// Mostrar parámetros recibidos por consola.
	for (int i = 0; i < argumentCount; ++i) {
		LogInfo("Argumento %d: '%s'", i, arguments[i]);
	}

	// Compilar el programa de entrada.
	LogInfo("Compilando...\n");
	const int result = yyparse();
	

	switch (result) {
		case 0:
			// La variable "succeed" es la que setea Bison al identificar el símbolo
			// inicial de la gramática satisfactoriamente.
			if (state.succeed) {
				LogInfo("La compilacion fue exitosa.");
				Generator(state.result);
			}
			else {
				switch(state.errorFound){
					case wrong_variable_type_error:
						LogError("Se produjo un error en la aplicacion. Se utilizo una variable con el tipo incorrecto");
						break;
					case variable_undefined_error:
						LogError("Se produjo un error en la aplicacion. Se utilizo una variable que no fue previamente definida");
						break;
					case variable_redefined_error:
						LogError("Se produjo un error en la aplicacion. Se intento redefinir una variable");
						break;
					case duplicate_song_variable_error:
						LogError("Se produjo un error en la aplicacion. Se definieron dos song's en el programa");
						break;
					default:
						LogError("Se produjo un error en la aplicacion.");
						break;
				}
				return -1;
			}
			break;
		case 1:
			LogError("Bison finalizo debido a un error de sintaxis.");
			break;
		case 2:
			LogError("Bison finalizo abruptamente debido a que ya no hay memoria disponible.");
			break;
		default:
			LogError("Error desconocido mientras se ejecutaba el analizador Bison (codigo %d).", result);
	}
	
	freeTable(state.table);
	LogInfo("Fin.");
	return result;
}
