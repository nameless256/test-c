//
// Created by CodingDev on 2026/7/21.
//

#include "obj.h"
#include <memory.h>

static void (*getDtor(const meta_class *class))(objBase *obj) {
    if (class->vptr == NULL) return NULL;
    return ((objBase_vtab *) class->vptr)->dtor;
}

static void dtorBase(const meta_type *meta, objBase *obj) {
    const meta_class *class = &meta->mClass;
    if (getDtor(class)) getDtor(class)(obj);
    if (class->base) dtorBase(class->base, obj);
}

void obj_dtor(void *obj) {
    if (obj == NULL) return;
    if (((objBase *) obj)->meta == NULL) return;
    dtorBase(((objBase *) obj)->meta, obj);
}

static bool (*getCtor(const meta_class *class))(objBase *obj) {
    if (class->vptr == NULL) return NULL;
    return ((objBase_vtab *) class->vptr)->ctor;
}

static bool ctorBase(const meta_type *meta, objBase *obj) {
    const meta_class *class = &meta->mClass;
    if (class->base && ctorBase(class->base, obj)) return true;
    if (getCtor(class) && getCtor(class)(obj)) {
        dtorBase(class->base, obj);
        return true;
    }
    return false;
}

bool obj_ctor(void *obj) {
    if (obj == NULL) return true;
    if (((objBase *) obj)->meta == NULL) return true;
    ((objBase *) obj)->vptr = ((objBase *) obj)->meta->mClass.vptr;
    return ctorBase(((objBase *) obj)->meta, obj);
}

static bool (*getCopy(const meta_class *class))(objBase *dst, objBase *src) {
    if (class->vptr == NULL) return NULL;
    return ((objBase_vtab *) class->vptr)->copy;
}

static bool copyBase(const meta_type *meta, objBase *restrict dst, objBase *restrict src) {
    const meta_class *class = &meta->mClass;
    if (class->base && copyBase(class->base, dst, src)) return true;
    if (getCopy(class) == NULL) {
        size_t baseSize = class->base->meta.size;
        memcpy(dst + baseSize, src + baseSize, meta->meta.size - baseSize);
        return false;
    }
    if (getCopy(class)(dst, src)) {
        dtorBase(class->base, dst);
        return true;
    }
    return false;
}

bool obj_copy(void *restrict dst, void *restrict src) {
    if (dst == NULL || src == NULL || ((objBase *) src)->meta == NULL) return true;
    if (((objBase *) dst)->meta != NULL && ((objBase *) dst)->meta != ((objBase *) src)->meta) return true;
    ((objBase *) dst)->vptr = ((objBase *) dst)->meta->mClass.vptr;
    return copyBase(((objBase *) src)->meta, dst, src);
}
