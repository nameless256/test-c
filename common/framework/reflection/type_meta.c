//
// Created by CodingDev on 2025/12/16.
//
#define TYPE_META_H_IMPL
#include "type_meta.h"

static void dtorBase(const classMeta *class, objBase *obj);

static void memberDtor(const classMeta *class, objBase *obj, size_t cnt) {
    for (size_t i = cnt; i > 0; i--) {
        const fieldMeta *field = class->fields[i - 1];
        if (field->base.isBitField) continue;
        const typeMeta *type = field->base.base.type;
        if (type->base.id != typeId_Class) continue;
        classMeta *fieldClass = (classMeta*)&type->classMeta;
        objBase *fieldObj = (objBase*)((char*)obj + field->base.ofs);
        dtorBase(fieldClass, fieldObj);
    }
}

static void dtorBase(const classMeta *class, objBase *obj) {
    if (obj == NULL || class == NULL) return;
    memberDtor(class, obj, class->cnt);
    if (class->dtor) class->dtor(obj);
    if (class->baseClass) dtorBase(class->baseClass, obj);
}

void obj_dtor(objBase *obj) {
    if (obj == NULL) return;
    if (obj->class == NULL) return;
    dtorBase(obj->class, obj);
}

static bool ctorBase(const classMeta *class, objBase *obj) {
    if (class == NULL || obj == NULL) return true;
    if (class->baseClass && ctorBase(class->baseClass, obj)) return true;
    for (size_t i = 0; i < class->cnt; i++) {
        const fieldMeta *field = class->fields[i];
        if (field->base.isBitField) continue;
        const typeMeta *type = field->base.base.type;
        if (type->base.id != typeId_Class) continue;
        classMeta *fieldClass = (classMeta*)&type->classMeta;
        objBase *fieldObj = (objBase*)((char*)obj + field->base.ofs);
        if (!ctorBase(fieldClass, fieldObj)) continue;
        memberDtor(class, obj, i);
        return true;
    }
    if (class->ctor && class->ctor(obj)) {
        memberDtor(class, obj, class->cnt);
        return true;
    }
    return false;
}

bool obj_ctor(objBase *obj) {
    if (obj == NULL) return true;
    if (obj->class == NULL) return true;
    return ctorBase(obj->class, obj);
}

static bool copyBase(const classMeta *class, objBase *obj, objBase *other) {
    if (class == NULL || obj == NULL || other == NULL) return true;
    if (class->baseClass && copyBase(class->baseClass, obj, other)) return true;
    for (size_t i = 0; i < class->cnt; i++) {
        const fieldMeta *field = class->fields[i];
        if (field->base.isBitField) continue;
        const typeMeta *type = field->base.base.type;
        if (type->base.id != typeId_Class) continue;
        classMeta *fieldClass = (classMeta*)&type->classMeta;
        objBase *fieldObj = (objBase*)((char*)obj + field->base.ofs);
        objBase *fieldOther = (objBase*)((char*)other + field->base.ofs);
        if (!copyBase(fieldClass, fieldObj, fieldOther)) continue;
        memberDtor(class, obj, i);
        return true;
    }
    if (class->copy && class->copy(obj, other)) {
        memberDtor(class, obj, class->cnt);
        return true;
    }
    return false;
}

bool obj_copy(objBase *restrict obj, objBase *restrict other) {
    if (obj == NULL || other == NULL) return true;
    if (obj->class == NULL || other->class == NULL) return true;
    if (obj->class != other->class) return true;
    return copyBase(obj->class, obj, other);
}
