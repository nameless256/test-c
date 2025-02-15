//
// Created by xiaoxianghui on 2025/1/9.
//

#ifndef TEST_C_WORD_SEARCH_H
#define TEST_C_WORD_SEARCH_H

#include "util.h"

struct wordSearch;

typedef struct wordSearch wordSearch;

wordSearch *wordSearchCreate();

void wordSearchDestroy(wordSearch **pObj);

void wordSearchSetLevel(wordSearch *obj, uint8_t level);

void wordSearchPrintAlphabet(wordSearch *obj);

void wordSearchFillAlphabet(wordSearch *obj);

void wordSearchSetLineStart(wordSearch *obj, int x, int y);

bool wordSearchSetLineEnd(wordSearch *obj, int x, int y);

bool wordSearchFoundWord(wordSearch *obj);

void wordSearchUsage(void);

#endif //TEST_C_WORD_SEARCH_H
