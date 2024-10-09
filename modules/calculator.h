//
// Created by xiaoxianghui on 2023/3/14.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "tool.h"

typedef enum {
    calcEqnErr_Null = 0,
    calcEqnErr_NaN = 1,
    calcEqnErr_FuncParse = 2,
    calcEqnErr_Parse = 3,
    calcEqnErr_DivByZero = 4,
    calcEqnErr_ExcessiveParam = 5,
    calcEqnErr_MissingParam = 6,
    calcEqnErr_MissingLBracket = 7,
    calcEqnErr_MissingRBracket = 8,
    calcEqnErr_Undefined = 9,
} calcEqnErr;

typedef struct {
    char *errLoc;
    calcEqnErr eqnErr;
} calcErr;

typedef double calcVal;

calcErr calculator(const char *eqnStr, calcVal *result);

const char *calcEqnErr2Str(calcEqnErr err);

__attribute__((unused)) void calculatorUsage(void);

#endif //CALCULATOR_H
