//
// Created by CodingDev on 2026/7/21.
//

#include "obj.h"

static void dtorBase(const meta_class *class, objBase *obj);

static if_dtor getDtor(const meta_class *class) {
    if (class->vptr == NULL) return NULL;
    return ((if_specMethod *) class->vptr)->dtor;
}

static void dtorBase(const meta_class *class, objBase *obj) {
    if (getDtor(class)) getDtor(class)(obj);
    if (class->baseClass) dtorBase(class->baseClass, obj);
}

void obj_dtor(objBase *obj) {
    if (obj == NULL) return;
    if (obj->class == NULL) return;
    dtorBase(obj->class, obj);
}

static if_ctor getCtor(const meta_class *class) {
    if (class->vptr == NULL) return NULL;
    return ((if_specMethod *) class->vptr)->ctor;
}

static bool ctorBase(const meta_class *class, objBase *obj) {
    if (class->baseClass && ctorBase(class->baseClass, obj)) return true;
    if (getCtor(class) && getCtor(class)(obj)) {
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

static if_copy getCopy(const meta_class *class) {
    if (class->vptr == NULL) return NULL;
    return ((if_specMethod *) class->vptr)->copy;
}

static bool copyBase(const meta_class *class, objBase *dst, objBase *src) {
    if (class->baseClass && copyBase(class->baseClass, dst, src)) return true;
    if (getCopy(class) && getCopy(class)(dst, src)) {
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
