//
// Created by xiaoxianghui on 2023/12/29.
//

#ifndef TEST_TIC_TAC_TOE_H
#define TEST_TIC_TAC_TOE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    char board[3][3];
    bool gameOver;
    uint8_t count;
    char winner, side;
} ticTacToe;

void ticTacToeReset(ticTacToe *obj);

char ticTacToeGetSide(ticTacToe *obj);

char ticTacToeGetOtherSide(ticTacToe *obj);

bool ticTacToeSet(ticTacToe *obj, uint8_t x, uint8_t y);

char ticTacToeGet(ticTacToe *obj, uint8_t x, uint8_t y);

char ticTacToeGetWinner(ticTacToe *obj);

bool ticTacToeIsDraw(ticTacToe *obj);

bool ticTacToeIsFinish(ticTacToe *obj);

ticTacToe *ticTacToeCreate();

void ticTacToeDestroy(ticTacToe **pObj);

#endif //TEST_TIC_TAC_TOE_H
