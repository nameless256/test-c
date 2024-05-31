//
// Created by xiaoxianghui on 2023/3/14.
//

#include "calculator.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef enum {
    calcToken_Null,
    calcToken_Val,
    calcToken_Func,
    calcToken_Add,
    calcToken_Sub,
    calcToken_Times,
    calcToken_Div,
    calcToken_LBracket,
    calcToken_Comma,
    calcToken_RBracket,
} calcToken;

static const char *const sgOprParsingStr = "+-*/(,)";

typedef enum {
    calcFunc_Pow,
    calcFunc_Exp,
    calcFunc_Log,
    calcFunc_Sin,
    calcFunc_Cos,
    calcFunc_Tan,
} calcFunc;

typedef struct {
    listNode entry;
    calcToken token;
    union {
        calcVal val;
        calcFunc func;
    };
} calcNode;

typedef struct {
    listNode entry;
    int8_t needParamCount;
    int8_t paramCount;
} calcNestInfo;

typedef struct {
    calcErr err;
    calcToken token;
    const char *eqnCur;
    listNode stack;      /**< 表达式 在 解析及计算阶段 的 辅助栈 */
    listNode analExp;    /**< 解析结束的解析式（逆波兰表达式）存放链表，计算结束后该链表仅剩结果 */
    listNode nestInfo;   /**< 解析阶段 的 辅助栈，用于记录嵌套信息 */
} calcEqn;

static calcVal calcGetValByStr(const char *str, calcErr *err) {
    calcVal val = strtod(str, &err->errLoc);
    if (err->errLoc == str) err->eqnErr = calcEqnErr_NaN;
    return val;
}

typedef struct {
    const char *const funcName;
    int8_t needParamCount;
} calcFuncParsingItem;

static const calcFuncParsingItem sgFuncParsingTab[] = {
    [calcFunc_Pow] = {"pow", 2},
    [calcFunc_Exp] = {"exp", 1},
    [calcFunc_Log] = {"log", 1},
    [calcFunc_Sin] = {"sin", 1},
    [calcFunc_Cos] = {"cos", 1},
    [calcFunc_Tan] = {"tan", 1},
};

static calcFunc calcGetFuncByStr(const char *str, calcErr *err) {
    calcFunc funcIndex;
    for (funcIndex = calcFunc_Pow; funcIndex < ARRAY_SIZE(sgFuncParsingTab); ++funcIndex) {
        size_t len = strlen(sgFuncParsingTab[funcIndex].funcName);
        if (strncmp(str, sgFuncParsingTab[funcIndex].funcName, len) != 0) continue;
        err->errLoc = (char *) str + len;
        break;
    }
    if (err->errLoc == str) err->eqnErr = calcEqnErr_FuncParse;
    return funcIndex;
}

static bool calcSetNode(calcEqn *const eqn, calcNode *const node) {
    eqn->err.eqnErr = calcEqnErr_Null;
    node->val = calcGetValByStr(eqn->eqnCur, &eqn->err);
    if (!eqn->err.eqnErr) {
//        printf("%g ", node->val);
        node->token = calcToken_Val;
        return false;
    }
    eqn->err.eqnErr = calcEqnErr_Null;
    node->func = calcGetFuncByStr(eqn->eqnCur, &eqn->err);
    if (!eqn->err.eqnErr) {
//        printf("%s ", sgFuncParsingTab[node->func].funcName);
        node->token = calcToken_Func;
        return false;
    }
    eqn->err.eqnErr = calcEqnErr_Parse;
    char *checkOpr = strchr(sgOprParsingStr, *eqn->eqnCur);
    if (checkOpr) {
        node->token = calcToken_Add + checkOpr - sgOprParsingStr;
        eqn->err.eqnErr = calcEqnErr_Null;
        eqn->err.errLoc = (char *) eqn->eqnCur + 1;
        return false;
    }
    return true;
}

__attribute__((unused)) static void calcListPrintf(listNode *list) {
    if (listIsEmpty(list)) {
        printf("listIsEmpty! \n");
        return;
    }
    listNode *listCur = list->prev;
    while (listCur != list) {
        calcNode *node = containerOf(listCur, calcNode, entry);
        if (node->token == calcToken_Val) {
            printf("%g ", node->val);
        } else if (node->token == calcToken_Func) {
            printf("%s ", sgFuncParsingTab[node->func].funcName);
        } else if (node->token != calcToken_Null) {
            printf("%c ", sgOprParsingStr[node->token - calcToken_Add]);
        }
        listCur = listCur->prev;
    }
    printf("\n");
}

static void calcNodeListFree(listNode *list) {
    while (!listIsEmpty(list)) {
        calcNode *node = containerOf(list->next, calcNode, entry);
        listDel(list->next);
        free(node);
    }
}

/*
 *          Null    Val     Func    +       -       *       /       (       ,       )
 * Null             √       √       3       3                       √
 * Val                      2       √       √       √       √       2       4       5
 * Func                                                             √
 * +                √       √                                       √
 * -                √       √                                       √
 * *                √       √                                       √
 * /                1       √                                       √
 * (                √       √       3       3                       √
 * ,                √       √       3       3                       √
 * )                                √       √       √       √               4       5
 */
/**
 * @details 1. 无法完全在 解析阶段 抛出的 错误：除数为0，需要在 计算阶段 抛出
 * @details 2. 数字与函数及左括号之间缺少算符连接，默认插入 算符：乘号
 * @details 2.1. 判断 栈顶 是否是函数 来决定 是否创建嵌套信息结点 并 向嵌套信息栈压栈
 * @details 2.2. 函数查找函数所需参数
 * @details 3. "4 * (-(pow(3, 2) / 2))" 转换为逆波兰表达式为 "4 3 2 pow 2 / - *"，
 * @details 此处负号本意是取反，然而在转换至 逆波兰表达式 后无法区分是减法还是取反；
 * @details 合理的表达式应该是 "4 3 2 pow 2 / 0 - *"，故第3点的正负号应该拓展理解为 "0 +" 或者 "0 -"
 * @details 4. 需要 根据嵌套信息栈栈顶节点 判断参数 是否 超过所需参数个数
 * @details 5. 需要 根据嵌套信息栈栈顶节点 判断参数 是否 缺少参数 并视情况弹栈
 */
static const uint32_t sgNextTokenMask[] = {
    [calcToken_Null] = (BIT(calcToken_Val) | BIT(calcToken_Func) |
                        BIT(calcToken_Add) | BIT(calcToken_Sub) |
                        BIT(calcToken_LBracket)),
    [calcToken_Val] = (BIT(calcToken_Func) |
                       BIT(calcToken_Add) | BIT(calcToken_Sub) |
                       BIT(calcToken_Times) | BIT(calcToken_Div) |
                       BIT(calcToken_LBracket) | BIT(calcToken_Comma) | BIT(calcToken_RBracket)),
    [calcToken_Func] = (BIT(calcToken_LBracket)),
    [calcToken_Add] = (BIT(calcToken_Val) | BIT(calcToken_Func) | BIT(calcToken_LBracket)),
    [calcToken_Sub] = (BIT(calcToken_Val) | BIT(calcToken_Func) | BIT(calcToken_LBracket)),
    [calcToken_Times] = (BIT(calcToken_Val) | BIT(calcToken_Func) | BIT(calcToken_LBracket)),
    [calcToken_Div] = (BIT(calcToken_Val) | BIT(calcToken_Func) | BIT(calcToken_LBracket)),
    [calcToken_LBracket] = (BIT(calcToken_Val) | BIT(calcToken_Func) |
                            BIT(calcToken_Add) | BIT(calcToken_Sub) |
                            BIT(calcToken_LBracket)),
    [calcToken_Comma] = (BIT(calcToken_Val) | BIT(calcToken_Func) |
                         BIT(calcToken_Add) | BIT(calcToken_Sub) |
                         BIT(calcToken_LBracket)),
    [calcToken_RBracket] = (BIT(calcToken_Add) | BIT(calcToken_Sub) |
                            BIT(calcToken_Times) | BIT(calcToken_Div) |
                            BIT(calcToken_Comma) | BIT(calcToken_RBracket)),
};

static void calcMoveStackNode2AnalExpUntilTokenInBreakMask(calcEqn *const eqn, uint32_t tokenBreakMask) {
    listNode *listCur = eqn->stack.next;
    while (listCur != &eqn->stack) {
        if (checkBit(tokenBreakMask, containerOf(listCur, calcNode, entry)->token)) break;
        listAdd(listDel(listCur), &eqn->analExp);
        listCur = eqn->stack.next;
    }
}

static void calcIllegalNodeCheck(calcEqn *const eqn, calcNode *const node) {
    uint32_t tokenMask = sgNextTokenMask[eqn->token];
    if (!checkBit(tokenMask, node->token)) {
        eqn->err.eqnErr = calcEqnErr_Undefined;
    } else if (node->token == calcToken_Val) {
        if (eqn->token == calcToken_Div && node->val == 0) eqn->err.eqnErr = calcEqnErr_DivByZero;
        listAdd(&node->entry, &eqn->analExp);
    } else if (node->token == calcToken_Func || node->token == calcToken_LBracket) {
        if (eqn->token == calcToken_Val) {
            uint32_t tokenBreakMask = BIT(calcToken_LBracket) | BIT(calcToken_Comma);
            tokenBreakMask |= BIT(calcToken_Add) | BIT(calcToken_Sub);
            calcMoveStackNode2AnalExpUntilTokenInBreakMask(eqn, tokenBreakMask);
            calcNode *insertNode = malloc(sizeof(calcNode));
            insertNode->token = calcToken_Times;
            listAdd(&insertNode->entry, &eqn->stack);
        }
        if (eqn->token != calcToken_Func) {
            calcNestInfo *nestInfo = malloc(sizeof(calcNestInfo));
            memset(nestInfo, 0, sizeof(calcNestInfo));
            if (node->token == calcToken_Func) {
                nestInfo->needParamCount = sgFuncParsingTab[node->func].needParamCount;
            }
            listAdd(&nestInfo->entry, &eqn->nestInfo);
        }
        listAdd(&node->entry, &eqn->stack);
    } else if (node->token == calcToken_Add || node->token == calcToken_Sub) {
        if (eqn->token == calcToken_Null || eqn->token == calcToken_LBracket || eqn->token == calcToken_Comma) {
            calcNode *insertNode = malloc(sizeof(calcNode));
            insertNode->token = calcToken_Val;
            insertNode->val = 0;
            listAdd(&insertNode->entry, &eqn->analExp);
        }
        uint32_t tokenBreakMask = BIT(calcToken_LBracket) | BIT(calcToken_Comma);
        calcMoveStackNode2AnalExpUntilTokenInBreakMask(eqn, tokenBreakMask);
        listAdd(&node->entry, &eqn->stack);
    } else if (node->token == calcToken_Comma) {
        if (listIsEmpty(&eqn->nestInfo)) {
            eqn->err.eqnErr = calcEqnErr_Undefined;
        } else {
            uint32_t tokenBreakMask = BIT(calcToken_LBracket) | BIT(calcToken_Comma);
            calcMoveStackNode2AnalExpUntilTokenInBreakMask(eqn, tokenBreakMask);
            calcNestInfo *nestInfo = containerOf(eqn->nestInfo.next, calcNestInfo, entry);
            nestInfo->paramCount++;
            if (!nestInfo->needParamCount) {
                eqn->err.eqnErr = calcEqnErr_Undefined;
            } else if (nestInfo->paramCount >= nestInfo->needParamCount) {
                eqn->err.eqnErr = calcEqnErr_ExcessiveParam;
            }
        }
        listAdd(&node->entry, &eqn->stack);
    } else if (node->token == calcToken_RBracket) {
        if (listIsEmpty(&eqn->nestInfo)) {
            eqn->err.eqnErr = calcEqnErr_MissingLBracket;
            listAdd(&node->entry, &eqn->stack);
            return;
        }
        uint32_t tokenBreakMask = BIT(calcToken_LBracket) | BIT(calcToken_Comma);
        calcMoveStackNode2AnalExpUntilTokenInBreakMask(eqn, tokenBreakMask);
        calcNestInfo *nestInfo = containerOf(eqn->nestInfo.next, calcNestInfo, entry);
        if (nestInfo->needParamCount) nestInfo->paramCount++;
        if (nestInfo->paramCount < nestInfo->needParamCount) {
            eqn->err.eqnErr = calcEqnErr_MissingParam;
        } else if (nestInfo->paramCount > nestInfo->needParamCount) {
            eqn->err.eqnErr = calcEqnErr_ExcessiveParam;
        }
        listAdd(&node->entry, &eqn->stack);
        if (eqn->err.eqnErr) return;
        listNode *listCur = eqn->stack.next;
        while (listCur != &eqn->stack) {
            calcNode *checkNode = containerOf(listCur, calcNode, entry);
            calcToken topToken = checkNode->token;
            if (nestInfo->needParamCount && topToken == calcToken_Func) {
                listAdd(listDel(listCur), &eqn->analExp);
                break;
            }
            listDel(listCur);
            free(checkNode);
            if (!nestInfo->needParamCount && topToken == calcToken_LBracket) break;
            listCur = eqn->stack.next;
        }
        listDel(&nestInfo->entry);
        free(nestInfo);
    } else if (node->token == calcToken_Times || node->token == calcToken_Div) {
        uint32_t tokenBreakMask = BIT(calcToken_LBracket) | BIT(calcToken_Comma);
        tokenBreakMask |= BIT(calcToken_Add) | BIT(calcToken_Sub);
        calcMoveStackNode2AnalExpUntilTokenInBreakMask(eqn, tokenBreakMask);
        listAdd(&node->entry, &eqn->stack);
    } else {
        eqn->err.eqnErr = calcEqnErr_Undefined;
        listAdd(&node->entry, &eqn->analExp);
    }
}

static void calcEqnParsing(calcEqn *const eqn) {
    while (eqn->err.eqnErr == calcEqnErr_Null && *eqn->err.errLoc) {
        calcNode *node = malloc(sizeof(calcNode));
        if (!calcSetNode(eqn, node)) {
            calcIllegalNodeCheck(eqn, node);
            if (!eqn->err.eqnErr) {
                eqn->eqnCur = eqn->err.errLoc;
                eqn->token = node->token;
            }
        }
        while (*eqn->eqnCur == ' ') eqn->eqnCur++;
    }

    if (!eqn->err.eqnErr) {
        if (listIsEmpty(&eqn->analExp)) {
            eqn->err.eqnErr = calcEqnErr_Undefined;
        } else if (eqn->token == calcToken_Func) {
            eqn->err.eqnErr = calcEqnErr_MissingLBracket;
        } else if (eqn->token != calcToken_Val && eqn->token != calcToken_RBracket) {
            eqn->err.eqnErr = calcEqnErr_MissingParam;
        } else if (!listIsEmpty(&eqn->stack)) {
            uint32_t tokenBreakMask = BIT(calcToken_Func);
            tokenBreakMask |= BIT(calcToken_Val) | BIT(calcToken_RBracket);
            tokenBreakMask |= BIT(calcToken_LBracket) | BIT(calcToken_Comma);
            calcMoveStackNode2AnalExpUntilTokenInBreakMask(eqn, tokenBreakMask);
            calcNode *checkNode = containerOf(eqn->stack.next, calcNode, entry);
            if (checkNode->token == calcToken_Func) {
                eqn->err.eqnErr = calcEqnErr_MissingLBracket;
            } else if (checkNode->token == calcToken_Val || checkNode->token == calcToken_RBracket) {
                eqn->err.eqnErr = calcEqnErr_Undefined;
            } else if (checkNode->token == calcToken_LBracket || checkNode->token == calcToken_Comma) {
                eqn->err.eqnErr = calcEqnErr_MissingParam;
            }
        }
    }
}

static calcEqnErr calcEqnFuncCalculate(calcFunc func, const calcVal args[], calcVal *result) {
    switch (func) {
        case calcFunc_Pow:
            *result = pow(args[0], args[1]);
            break;
        case calcFunc_Exp:
            *result = exp(args[0]);
            break;
        case calcFunc_Log:
            *result = log(args[0]);
            break;
        case calcFunc_Sin:
            *result = sin(args[0]);
            break;
        case calcFunc_Cos:
            *result = cos(args[0]);
            break;
        case calcFunc_Tan:
            *result = tan(args[0]);
            break;
        default:
            return calcEqnErr_Undefined;
    }
    return calcEqnErr_Null;
}

static calcEqnErr calcEqnOprCalculate(calcToken opr, const calcVal args[], calcVal *result) {
    switch (opr) {
        case calcToken_Add:
            *result = args[0] + args[1];
            break;
        case calcToken_Sub:
            *result = args[0] - args[1];
            break;
        case calcToken_Times:
            *result = args[0] * args[1];
            break;
        case calcToken_Div:
            *result = args[1] ? args[0] / args[1] : 0;
            if (!args[1]) return calcEqnErr_DivByZero;
            break;
        default:
            return calcEqnErr_Undefined;
    }
    return calcEqnErr_Null;
}

/**
 * @attention 涉及多个参数的运算步骤应注意 先弹出的值在后面
 * @attention e.g. 9 1 3 2 pow / sin 8 pow 8 * 5 / 6.28 sin * 3.14 sin 6 + / 3 2 pow * - 1 2 * +
 * @param eqn
 */
static void calcEqnCalculate(calcEqn *const eqn) {
    while (!listIsEmpty(&eqn->analExp)) {
        calcNode *checkNode = containerOf(eqn->analExp.prev, calcNode, entry);
        listDel(&checkNode->entry);
        if (checkNode->token == calcToken_Val) {
            listAdd(listDel(&checkNode->entry), &eqn->stack);
            continue;
        }
        int8_t needParamCount = 2;
        if (checkNode->token == calcToken_Func) {
            needParamCount = sgFuncParsingTab[checkNode->func].needParamCount;
        }
        calcVal args[needParamCount];
        memset(args, 0, needParamCount);
        for (int8_t i = 0; i < needParamCount; ++i) {
            calcNode *argNode = containerOf(eqn->stack.next, calcNode, entry);
            listDel(&argNode->entry);
            args[needParamCount - i - 1] = argNode->val;
            free(argNode);
        }
        calcNode *insertNode = malloc(sizeof(calcNode));
        insertNode->token = calcToken_Val;
        insertNode->val = 0;
        listAdd(&insertNode->entry, &eqn->stack);
        if (checkNode->token == calcToken_Func) {
            eqn->err.eqnErr = calcEqnFuncCalculate(checkNode->func, args, &insertNode->val);
        } else {
            eqn->err.eqnErr = calcEqnOprCalculate(checkNode->token, args, &insertNode->val);
        }
        free(checkNode);
    }
}

calcErr calculator(const char *eqnStr, calcVal *result) {
    assert(eqnStr != NULL);
    assert(result != NULL);
    calcEqn eqn = {
        .eqnCur = eqnStr,
        .token = calcToken_Null,
        .stack = listNodeInit(eqn.stack),
        .analExp = listNodeInit(eqn.analExp),
        .nestInfo = listNodeInit(eqn.nestInfo),
        .err = {.errLoc = (char *) eqnStr, .eqnErr = calcEqnErr_Null},
    };

    calcEqnParsing(&eqn);
//    calcListPrintf(&eqn.analExp);
    if (!eqn.err.eqnErr) {
        calcEqnCalculate(&eqn);
    }
    *result = containerOf(eqn.stack.next, calcNode, entry)->val;

    calcNodeListFree(&eqn.stack);
    calcNodeListFree(&eqn.analExp);

    while (!listIsEmpty(&eqn.nestInfo)) {
        calcNestInfo *node = containerOf(eqn.nestInfo.next, calcNestInfo, entry);
        listDel(eqn.nestInfo.next);
        free(node);
    }

    return eqn.err;
}

const char *calcEqnErr2Str(calcEqnErr err) {
    switch (err) {
        name2StrCase(calcEqnErr_Null);
        name2StrCase(calcEqnErr_NaN);
        name2StrCase(calcEqnErr_FuncParse);
        name2StrCase(calcEqnErr_Parse);
        name2StrCase(calcEqnErr_DivByZero);
        name2StrCase(calcEqnErr_ExcessiveParam);
        name2StrCase(calcEqnErr_MissingParam);
        name2StrCase(calcEqnErr_MissingLBracket);
        name2StrCase(calcEqnErr_MissingRBracket);
        default:
        name2StrCase(calcEqnErr_Undefined);
    }
}

/// \todo 支持 未知数 常数 复数 不等式 极限 向量 矩阵 方程组 及 多个函数和不等式的图像绘制
/// \todo 封装按键输入 数制转换 及 十进制库
/// \todo 支持 三维图形 及 复数域 绘制
// 要支持以上功能需要大规模重构，且继续用C语言实现已经不大现实了
// 对于嵌入式来说，支持以上功能所占据的资源过多
// 下一步优化方向可以考虑 封装按键输入
__attribute__((unused)) void calculatorUsage(void) {
    calcErr err;
    char *eqn = "log(2.7182818284590452354)";
    calcVal result = 0;
    printf("%s\n", eqn);
    if ((err = calculator(eqn, &result)).eqnErr) {
        for (int i = 0; i < (err.errLoc - eqn - 1); ++i) {
            putchar(' ');
        }
        printf("^\n");
        printf("[%d] --------- {%s} %s \n", __LINE__, __FUNCTION__, calcEqnErr2Str(err.eqnErr));
    } else {
        printf("= %.10f \n", result);
    }
}
