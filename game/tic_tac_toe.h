//
// Created by xiaoxianghui on 2023/12/29.
//

#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <stdint.h>
#include <stdbool.h>

/// 对外隐藏
typedef struct TicTacToe *ticTacToe;

#define call(class, methodName, ...) class##_##methodName(this, ## __VA_ARGS__)

#define public(returnType, class, methodName, ...) returnType class##_##methodName(class *this, ## __VA_ARGS__)

public(ticTacToe *, ticTacToe, create);

public(void, ticTacToe, destroy);

public(void, ticTacToe, reset);

void ticTacToeUsage(void);

#endif //TIC_TAC_TOE_H
