#include "../support/logger.h"
#include "generator.h"
#include <stdlib.h>
#include "../support/symbolsTable.h"
#include "../support/freeTree.h"
/**
 * Implementación de "generator.h".
 */

static void copy_to_java(char * string) {
    fprintf(yyout, "%s", string);
}


void Generator(Program * program) {
	//LogInfo("El resultado de la expresion computada es: '%d'.", result);
    LogInfo("Produciendo el codigo en java:"); 

	// TODO: CAmbiar el path del fopen
    yyout = fopen("src/backend/generated-java/source_classes/src/main/java/classes/Out.java", "w");
   
    if (yyout == NULL) {
        LogError("Error al abrir el archivo Out.java");
        return;
    }
	// TODO: Ver de cambiar esto de package por el nombre que realmente sea
    copy_to_java("package com.example.java;\n\n");
    copy_to_java("import com.emcaple.java.OutputUtils;\n");
    copy_to_java("import org.jfugue.player.Player;\n");
    copy_to_java("public class Out {\n");
    copy_to_java("\tpublic static void main(String[] args) {\n");
    copy_to_java("\t\tOutputUtils outputUtils = new OutputUtils();\n");
    copy_to_java("\t\tString outputString = \"\";\n");

	if(program->code != NULL) {
    	GenerateCode(program->code);
	}

    copy_to_java("new Player().play(outputString);\n");
    copy_to_java("}\n");
    copy_to_java("}\n");

    LogInfo("Finalizacion del codigo");
    free(program);
}


void GenerateCode(Code *code) {
	if(code != NULL){
		GenerateDefinitions(code->definitions);
		GenerateInstructions(code->instructionArray);
		free(code);
	}
}

void GenerateDefinitions (Definitions *definitions) {
	if(definitions != NULL) {
		GenerateDefinition(definitions->definition);
		GenerateDefinitions(definitions->definitions);
		free(definitions);
	}
}

void GenerateDefinition (Definition *definition) {
	if(definition != NULL) {
		if(definition->variableType==SONG_VAR){
			fprintf(yyout, "\t\tString %s = outputUtils.defineSong();\n", definition->variableName->name);
		} else if(definition->variableType == TRACK_VAR) {
			fprintf(yyout, "\t\tString %s = outputUtils.defineTrack();\n", definition->variableName->name);
		} else if(definition->variableType == NOTE_VAR) {
			fprintf(yyout, "\t\tString %s = new String("");\n", definition->variableName->name);
		}
		freeDefinitions(definition);
	}
}


void GenerateInstructions(InstructionsArray *instructionsArray) {
	if(instructionsArray != NULL) {
		GenerateInstruction(instructionsArray->instruction);
		GenerateInstructions(instructionsArray->instructionArray);
		free(instructionsArray);
	}
}

void GenerateInstruction(Instruction *instruction) {
	if(instruction != NULL) {
		if(instruction->unaryExpression != NULL){
			GenerateUnaryExpression(instruction->unaryExpression);
		} else {
			GenerateBinaryExpression(instruction->binaryExpression);
		}		
		free(instruction);
	}
}

static SymbolType getRightType(BinaryExpression *binaryExpression){
	if(binaryExpression->binaryExpression != NULL){
		return getVariableType(state.table,binaryExpression->binaryExpression->variableNameLeft->name);
	}else if(binaryExpression->unaryExpression != NULL){
		return getVariableType(state.table,binaryExpression->unaryExpression->variableName->name);
	}
	return getVariableType(state.table,binaryExpression->variableNameRight->name);
}

void GenerateBinaryExpression(BinaryExpression *binaryExpression){
	if(binaryExpression != NULL){
		SymbolType symbolLeft = getVariableType(state.table,binaryExpression->variableNameLeft->name);
		SymbolType symbolRight = getRightType(binaryExpression);
			
		if(binaryExpression->type == ADDITION) {
			if((symbolLeft == TRACK_SYMBOL) && (symbolRight == TRACK_SYMBOL)) {
				fprintf(yyout, "\t\t%s = outputUtils.trackAddTrack();\n", binaryExpression->variableNameLeft->name);
			} else if(symbolLeft == TRACK_SYMBOL && symbolRight == NOTE_SYMBOL) {
				fprintf(yyout, "\t\t%s = outputUtils.trackAddNote();\n", binaryExpression->variableNameLeft->name);
			} else if((symbolLeft == SONG_SYMBOL) && (symbolRight == TRACK_SYMBOL)) {
				fprintf(yyout, "\t\t%s = outputUtils.songAddTrack();\n", binaryExpression->variableNameLeft->name);
			}
		} else if(binaryExpression->type == SUBTRACTION){
			if((symbolLeft == TRACK_SYMBOL && symbolRight == NOTE_SYMBOL)) {
				fprintf(yyout, "\t\t%s = outputUtils.trackSubstraction();\n", binaryExpression->variableNameLeft->name);			
			}
		} else if(binaryExpression->type == DIVISION) {
			if(symbolLeft == TRACK_SYMBOL && symbolRight == NOTE_SYMBOL) {
				fprintf(yyout, "\t\t%s = outputUtils.tracktrackDivision();\n", binaryExpression->variableNameLeft->name);
			} 
		}
		freeBinaryExpression(binaryExpression);
	}
}

void GenerateUnaryExpression(UnaryExpression *unaryExpression) {
	if(unaryExpression != NULL) {
		SymbolType symbol = getVariableType(state.table,unaryExpression->variableName->name);

		if(unaryExpression->type ==  MULTIPLICATION) {
			if(symbol == TRACK_SYMBOL) {
				fprintf(yyout, "\t\t%s = outputUtils.trackMultiply(%s, %s);\n", unaryExpression->variableName->name, unaryExpression->variableName->name);
			}
		} else if(unaryExpression->type == TEMPO_ASSINGMENT){
			if(symbol == TRACK_SYMBOL) {
				fprintf(yyout, "\t\t%s = outputUtils.changeTempo();\n", unaryExpression->variableName->name);
			}
		} else if(unaryExpression == INSTRUMENT_ASSINGMENT) {
			if(symbol == TRACK_SYMBOL) {
				fprintf(yyout, "\t\t%s = outputUtils.changeInstrument();\n", unaryExpression->variableName->name);
			}
		} else if(unaryExpression == NOTE_RHYTHM_CHORD_ASSIGNMENT) {
			if(symbol == NOTE_SYMBOL) {
				fprintf(yyout, "\t\t%s = outputUtils.changeInstrument();\n", unaryExpression->variableName->name);
			}
		} //todo en linea 122 del bison.y y ver parametros de entrada de funcoines de mateo
			
		
		
		
		freeUnaryExpression(unaryExpression);
	}		
}

	











