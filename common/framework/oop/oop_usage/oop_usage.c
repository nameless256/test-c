//
// Created by xiaoxianghui on 2024/10/18.
//

#include "oop_usage.h"
#include "class_demo/public.h"

void oopUsage(void) {
    obj_create(dog, obj);

    dog_displayInfo(&obj);

    obj_destroy(dog, obj);
}
