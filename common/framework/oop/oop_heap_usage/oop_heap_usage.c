//
// Created by xiaoxianghui on 2025/3/29.
//

#include "oop_heap_usage.h"
#include "rect/rect.h"

void oopHeapUsage(void) {
    rect *oopObjCreate(rect, temp)((point){10, 20}, 50, 60);
    rect_print(temp);
    oopObjDestroy(rect, temp);
}
