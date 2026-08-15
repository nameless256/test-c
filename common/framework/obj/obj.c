//
// Created by CodingDev on 2026/7/21.
//

#include "obj.h"

static void dtorBase(const meta_class *class, objBase *obj);

static void dtorBase(const meta_class *class, objBase *obj) {
    if (class->dtor) class->dtor(obj);
    if (class->baseClass) dtorBase(class->baseClass, obj);
}

void obj_dtor(objBase *obj) {
    if (obj == NULL) return;
    if (obj->class == NULL) return;
    dtorBase(obj->class, obj);
}

static bool ctorBase(const meta_class *class, objBase *obj) {
    if (class->baseClass && ctorBase(class->baseClass, obj)) return true;
    if (class->ctor && class->ctor(obj)) {
        dtorBase(class->baseClass, obj);
        return true;
    }
    return false;
}

bool obj_ctor(objBase *obj) {
    if (obj == NULL) return true;
    if (obj->class == NULL) return true;
    return ctorBase(obj->class, obj);
}

static bool copyBase(const meta_class *class, objBase *dst, objBase *src) {
    if (class->baseClass && copyBase(class->baseClass, dst, src)) return true;
    if (class->copy && class->copy(dst, src)) {
        dtorBase(class->baseClass, dst);
        return true;
    }
    return false;
}

bool obj_copy(objBase *restrict dst, objBase *restrict src) {
    if (dst == NULL || src == NULL || src->class == NULL) return true;
    if (dst->class != NULL && dst->class != src->class) return true;
    return copyBase(src->class, dst, src);
}
