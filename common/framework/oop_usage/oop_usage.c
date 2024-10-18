//
// Created by xiaoxianghui on 2024/10/18.
//

#include "oop_usage.h"
#include "class_demo/public.h"

void oopUsage(void) {
    obj_create(classDemo, obj, classDemo_ctor);
    
    obj_destroy(obj, classDemo_ctor);
}
