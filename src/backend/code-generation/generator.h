#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "../support/shared.h" 

void Generator(Program * program);

void GenerateCode(Code *code);

void GenerateDefinitions(Definitions *definitions);

void GenerateDefinition(Definition *definition);

void GenerateInstructions(InstructionsArray *instructionsArray);

void GenerateInstruction(Instruction *instruction);

void GenerateBinaryExpression(BinaryExpression *binaryExpression);

void GenerateUnaryExpression(UnaryExpression *unaryExpression);

#endif
