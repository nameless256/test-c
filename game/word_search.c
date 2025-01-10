//
// Created by xiaoxianghui on 2025/1/9.
//

#include "word_search.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DEBUG
#ifdef DEBUG
#define gameLog printf
#define gameLogPutChar putchar
#else
#define gameLog
#define gameLogPutChar
#endif

// @formatter:off
// clang-format off
static const char s3LetterWordList[][4] = {
    {"COW"}, {"CAT"}, {"DOG"}, {"CAR"}, {"BUS"}, {"PEN"}, {"CUP"}, {"HAT"}, {"SUN"}, {"SKY"},
    {"SEA"}, {"COW"}, {"FOX"}, {"PIG"}, {"EGG"},
};

static const char s4LetterWordList[][5] = {
    {"BLUE"}, {"PINK"}, {"BEAR"}, {"WALK"}, {"HOPE"}, {"MOON"}, {"HOME"}, {"BOOK"}, {"TREE"}, {"FISH"},
    {"BIRD"}, {"STAR"}, {"DOOR"}, {"WALL"}, {"ROOF"}, {"DESK"}, {"CAKE"}, {"WINE"}, {"FIRE"}, {"WIND"},
    {"RAIN"}, {"SNOW"},
};

static const char s5LetterWordList[][6] = {
    {"ZEBRA"}, {"TIGER"}, {"SHARK"}, {"HORSE"}, {"GREEN"}, {"APPLE"}, {"GRAPE"}, {"LEMON"}, {"ONION"}, {"CHAIR"},
    {"TABLE"}, {"HOUSE"}, {"CLOCK"}, {"TRAIN"}, {"PLANE"}, {"STONE"}, {"RIVER"}, {"CLOUD"}, {"PHONE"}, {"SHIRT"},
    {"PANTS"}, {"SHOES"}, {"GLASS"}, {"PAPER"}, {"KNIFE"},
};

static const char s6LetterWordList[][7] = {
    {"BANANA"}, {"CAMERA"}, {"FLOWER"}, {"MONKEY"}, {"ORANGE"}, {"RABBIT"}, {"TURTLE"}, {"VIOLIN"},
};
// @formatter:on
// clang-format on

typedef struct wordDir {
    bool horizontal;
    bool positive;
} wordDir;

typedef struct wordSelectArea {
    wordDir dir;
    uint8_t length;
    int ofs, x;
} wordSelectArea;

typedef struct wordInfo {
    const char *word;
    wordSelectArea area;
    bool found;
} wordInfo;

#define WORD_MAX 4
#define ALPHA_TAB_W 8
#define ALPHA_TAB_H 7

struct wordSearch {
    uint8_t level;
    char alphabet[ALPHA_TAB_H][ALPHA_TAB_W];
    int row, col;
    wordInfo wordTab[WORD_MAX];
    uint8_t wordCount;
    wordSelectArea area;
    bool touch;
};

static const char *getRandWord(uint8_t i) {
// @formatter:off
// clang-format off
    switch (i) {
        case 0: return s3LetterWordList[rand() % ARRAY_SIZE(s3LetterWordList)];
        case 1: return s4LetterWordList[rand() % ARRAY_SIZE(s4LetterWordList)];
        case 2: return s5LetterWordList[rand() % ARRAY_SIZE(s5LetterWordList)];
        default:
        case 3: return s6LetterWordList[rand() % ARRAY_SIZE(s6LetterWordList)];
    }
// @formatter:on
// clang-format on
}

static bool placeWord(wordSearch *obj, uint8_t i) {
    for (int j = 0; j < i; ++j) {
        if (obj->wordTab[j].area.length == obj->wordTab[i].area.length) {
            if (0 == strcmp(obj->wordTab[j].word, obj->wordTab[i].word)) return true;
        }
    }
    for (int j = 0; j < obj->wordTab[i].area.length; ++j) {
        int x = obj->wordTab[i].area.ofs, y = obj->wordTab[i].area.x + (obj->wordTab[i].area.dir.positive ? j : -j);
        if (obj->wordTab[i].area.dir.horizontal) SWAP(x, y);
        if (obj->alphabet[y][x] != 0 && obj->alphabet[y][x] != obj->wordTab[i].word[j]) return true;
    }
    for (int j = 0; j < obj->wordTab[i].area.length; ++j) {
        int x = obj->wordTab[i].area.ofs, y = obj->wordTab[i].area.x + (obj->wordTab[i].area.dir.positive ? j : -j);
        if (obj->wordTab[i].area.dir.horizontal) SWAP(x, y);
        obj->alphabet[y][x] = obj->wordTab[i].word[j];
    }
    return false;
}

wordSearch *wordSearchCreate() {
    wordSearch *obj = malloc(sizeof(wordSearch));
    wordSearchSetLevel(obj, 0);
    wordSearchFillAlphabet(obj);
    return obj;
}

void wordSearchDestroy(wordSearch **pObj) {
    if (*pObj) free(*pObj), *pObj = NULL;
}

void wordSearchSetLevel(wordSearch *obj, uint8_t level) {
    memset(obj, 0, sizeof(wordSearch));
    obj->level = level;
    uint8_t wordBaseIdx = obj->level > 12 ? 2 : (obj->level > 4 ? 1 : 0);
    if (wordBaseIdx == 0) obj->row = 5, obj->col = 5;
    else if (wordBaseIdx == 1) obj->row = 6, obj->col = 6;
    else obj->row = ALPHA_TAB_H, obj->col = ALPHA_TAB_W;
    obj->wordCount = 4;
    for (int i = 0; i < obj->wordCount; ++i) {
        uint8_t randWordIdx = wordBaseIdx + (i > (WORD_MAX - 1 - (obj->level - 1) % WORD_MAX) ? 1 : 0);
        wordInfo *info = &obj->wordTab[i];
        do {
            info->word = getRandWord(randWordIdx);
            info->found = false;
            info->area.dir.horizontal = rand() % 2;
            info->area.dir.positive = rand() % 2;
            info->area.length = strlen(info->word);
            info->area.ofs = rand() % (info->area.dir.horizontal ? obj->col : obj->row);
            uint8_t lengthMax = ((info->area.dir.horizontal ? obj->row : obj->col) - info->area.length);
            obj->wordTab[i].area.x = rand() % lengthMax + (info->area.dir.positive ? 0 : (info->area.length - 1));
        } while (placeWord(obj, i));
    }
}

void wordSearchPrintAlphabet(wordSearch *obj) {
    for (int i = 0; i < obj->row; ++i) {
        for (int j = 0; j < obj->col; ++j) {
            gameLogPutChar(' ');
            if (obj->alphabet[i][j] == 0) gameLogPutChar(' ');
            else gameLogPutChar(obj->alphabet[i][j]);
            gameLogPutChar(' ');
        }
        gameLogPutChar('\n');
    }
}

void wordSearchFillAlphabet(wordSearch *obj) {
    for (int i = 0; i < obj->row; ++i) {
        for (int j = 0; j < obj->col; ++j) {
            if (obj->alphabet[i][j] != 0) continue;
            obj->alphabet[i][j] = (char) ('A' + rand() % 26);
        }
    }
}

void wordSearchSetLineStart(wordSearch *obj, int x, int y) {
    if (obj->touch) return;
    if (x >= obj->col) x = obj->col - 1;
    if (x < 0) x = 0;
    if (y >= obj->row) y = obj->row - 1;
    if (y < 0) y = 0;
    obj->area.dir.horizontal = true;
    obj->area.dir.positive = true;
    obj->area.length = 1;
    obj->area.ofs = y, obj->area.x = x;
    obj->touch = true;
}

bool wordSearchSetLineEnd(wordSearch *obj, int x, int y) {
    if (!obj->touch) return false;
    if (x >= obj->col) x = obj->col - 1;
    if (x < 0) x = 0;
    if (y >= obj->row) y = obj->row - 1;
    if (y < 0) y = 0;
    int pOfs = y, p0 = x;
    if (!obj->area.dir.horizontal) SWAP(pOfs, p0);
    bool needUpdate = false;
    if (ABS(pOfs - obj->area.ofs) > ABS(p0 - obj->area.x)) {
        obj->area.dir.horizontal = !obj->area.dir.horizontal;
        SWAP(obj->area.ofs, obj->area.x);
        SWAP(pOfs, p0);
        needUpdate = true;
    }
    if (obj->area.dir.positive != p0 > obj->area.x) {
        obj->area.dir.positive = p0 > obj->area.x;
        needUpdate = true;
    }
    if (obj->area.length != 1 + ABS(p0 - obj->area.x)) {
        obj->area.length = 1 + ABS(p0 - obj->area.x);
        needUpdate = true;
    }
    return needUpdate;
}

bool wordSearchFoundWord(wordSearch *obj) {
    if (!obj->touch) return false;
    for (int i = 0; i < obj->wordCount; ++i) {
        if (obj->wordTab[i].found) continue;
        if (obj->wordTab[i].area.dir.horizontal != obj->area.dir.horizontal) continue;
        if (obj->wordTab[i].area.dir.positive != obj->area.dir.positive) continue;
        if (obj->wordTab[i].area.length != obj->area.length) continue;
        if (obj->wordTab[i].area.ofs != obj->area.ofs) continue;
        if (obj->wordTab[i].area.x != obj->area.x) continue;
        obj->wordTab[i].found = true;
        break;
    }
    obj->touch = false;
    for (int i = 0; i < obj->wordCount; ++i) if (!obj->wordTab[i].found) return false;
    return true;
}

void wordSearchUsage(void) {
    uint32_t seed = (unsigned) time(NULL);
    gameLog("[%d] --------- {%s} seed %u \n", __LINE__, __FUNCTION__, seed);
    srand(seed);

    wordSearch *obj = wordSearchCreate();
//    wordSearchPrintAlphabet(obj);
#ifdef DEBUG
    for (int i = 12; i < 16; ++i) {
        wordSearchSetLevel(obj, i + 1);
        gameLog("[%d] --------- {%s} %d \n", __LINE__, __FUNCTION__, i + 1);
        gameLog("Words:\n");
        gameLog("%s %s %s %s\n",
                obj->wordTab[0].word, obj->wordTab[1].word, obj->wordTab[2].word, obj->wordTab[3].word);
        gameLog("Answer:\n");
        wordSearchPrintAlphabet(obj);
        wordSearchFillAlphabet(obj);
        gameLog("Puzzle:\n");
        wordSearchPrintAlphabet(obj);
    }
#endif
    wordSearchDestroy(&obj);
}
