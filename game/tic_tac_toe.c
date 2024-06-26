//
// Created by xiaoxianghui on 2023/12/29.
//

#include <malloc.h>
#include <string.h>
#include "tic_tac_toe.h"

static inline bool checkGameOver(ticTacToe *obj) {
    uint8_t sideCheck, empty, draw = 0;
    for (uint8_t i = 0; i < 8; ++i) {
        sideCheck = 0, empty = 0;
        for (uint8_t j = 0; j < 3; ++j) {
            char symbol;
            if (i < 3) symbol = obj->board[i][j];
            else if (i < 6) symbol = obj->board[j][i - 3];
            else if (i < 7) symbol = obj->board[j][j];
            else symbol = obj->board[3 - j - 1][j];
            if (!symbol) empty++;
            else sideCheck |= symbol;
        }
        if (sideCheck != 'X' && sideCheck != 'O') draw++;
        else if (!empty) obj->winner = (char) sideCheck;
    }
    if (draw == 8 && !obj->winner) obj->winner = '-';
    if (!obj->winner) return false;
    return true;
}

void ticTacToeReset(ticTacToe *obj) {
    memset(obj, 0, sizeof(ticTacToe));
}

char ticTacToeGetSide(ticTacToe *obj) {
    if (obj->side != 'O' && obj->side != 'X') obj->side = 'X';
    return obj->side;
}

char ticTacToeGetOtherSide(ticTacToe *obj) {
    return ticTacToeGetSide(obj) == 'X' ? 'O' : 'X';
}

bool ticTacToeSet(ticTacToe *obj, uint8_t x, uint8_t y) {
    if (obj->gameOver) return true;
    if (x >= 3 || y >= 3) return true;
    if (obj->board[y][x] != 0) return true;
    obj->board[y][x] = ticTacToeGetSide(obj);
    obj->side = ticTacToeGetOtherSide(obj);
    obj->count++;
    if (checkGameOver(obj)) obj->gameOver = true;
    return false;
}

char ticTacToeGet(ticTacToe *obj, uint8_t x, uint8_t y) {
    return obj->board[y][x];
}

char ticTacToeGetWinner(ticTacToe *obj) {
    return obj->winner;
}

bool ticTacToeIsDraw(ticTacToe *obj) {
    return obj->winner == '-';
}

bool ticTacToeIsFinish(ticTacToe *obj) {
    return obj->gameOver;
}

ticTacToe *ticTacToeCreate() {
    ticTacToe *obj = malloc(sizeof(ticTacToe));
    ticTacToeReset(obj);
    return obj;
}

void ticTacToeDestroy(ticTacToe **pObj) {
    if (*pObj) free(*pObj), *pObj = NULL;
}
