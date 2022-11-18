#include <stdlib.h>
#include "../semantic-analysis/abstract-syntax-tree.h"




void freeProgramTree(Program *program){
    if (program == NULL){
        return;
    }
    Code* aux = program->code;
    free(program);
    freeCodeTree(aux);
}

void freeCodeTree(Code* code){
    if (code == NULL){
        return;
    }
    Definitions* defAux = code->definitions;
    InstructionsArray *instAux = code->instructionArray;
    free(code);
    freeDefinitions(defAux);
    freeInstructionsArray(instAux);
}

void freeDefinition(Definition* definition){
    if (definition == NULL){
        return;
    }
    freeVarType(definition->variableType);
    freeVarName(definition->variableName);
}

void freeBinaryExpression(BinaryExpression *binaryExpression){
    if(binaryExpression == NULL){
        return;
    }
    if(binaryExpression->variableNameLeft != NULL){
        freeVarName(binaryExpression->variableNameLeft);
    }
    if(binaryExpression->variableNameRight != NULL){
        freeVarName(binaryExpression->variableNameRight);
    }
    if(binaryExpression->binaryExpression != NULL){
        freeBinaryExpression(binaryExpression->binaryExpression);
    }
    if(binaryExpression->unaryExpression != NULL){
        freeUnaryExpression(binaryExpression->unaryExpression);
    }
    free(binaryExpression);
}

void freeUnaryExpression(UnaryExpression *unaryExpression){
    if(unaryExpression == NULL){
        return;
    }
    if(unaryExpression->variableName != NULL){
        freeVarName(unaryExpression->variableName);
    }
    if(unaryExpression->firstValueType != NULL){
        freeValueStruct(unaryExpression->firstValueType);
    }
    if(unaryExpression->secondValueType != NULL){
        freeValueStruct(unaryExpression->secondValueType);
    }
    if(unaryExpression->thirdValueType != NULL){
        freeValueStruct(unaryExpression->thirdValueType);
    }
    free(unaryExpression);
}

void freeVarType(Variable *varType){
    free(varType);
}

void freeVarName(VariableName *VariableName){
    free(VariableName);
}

void freeValueStruct(ValueStruct *valueStruct){
    if(valueStruct->note != NULL){
        free(valueStruct->note);
    }
    if(valueStruct->instrument != NULL){
        free(valueStruct->instrument);
    }
    if(valueStruct->chord != NULL){
        free(valueStruct->chord);
    }
    if(valueStruct->rhythm != NULL){
        free(valueStruct->rhythm);
    }
    if(valueStruct->repetition != NULL){
        free(valueStruct->repetition);
    }
    if(valueStruct->tempo != NULL){
        free(valueStruct->tempo);
    }
    free(valueStruct);
}

