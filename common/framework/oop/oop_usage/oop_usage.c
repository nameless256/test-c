//
// Created by xiaoxianghui on 2024/10/18.
//

#include "oop_usage.h"
#include "class_demo/public.h"

static void test(int oopQuote(arg)) {
    oopDequote(arg)++;
}

void oopUsage(void) {
    oopObj(dog, obj);
    oopObj(animal, canidae);

    animal_eat(&canidae);
    dog_displayInfo(&obj);

    int a = 0;
    test(oopRef(a));
    printf("[%d] --------- {%s} %d \n", __LINE__, __FUNCTION__, a);
}
