//
// Created by Admin on 26-9-6.
//

#include "utf16.h"

#define moduleName utf16

define(encoding_err, decode, uint16_t *src, unicode *dst, uint8_t length, uint8_t *ofs) {
    if (src == NULL || dst == NULL) return encoding_err_NullPtr;
    if (length == 0) return encoding_err_Truncated;
    encoding_err err = encoding_err_None;
    uint8_t codeUnit = 1;
    if (unicode_isSurrogateHigh(src[0])) {
        codeUnit = 2;
        if (length < codeUnit) return encoding_err_Truncated;
        if (!unicode_isSurrogateLow(src[1])) err = encoding_err_InvalidTrail;
    } else if (unicode_isSurrogateLow(src[0])) {
        err = encoding_err_InvalidLead;
    }
    if (err != encoding_err_None) goto errProcess;
    unicode cp = src[0];
    if (codeUnit == 2) {
        cp = unicode_size_Plane;
        cp += (src[0] - unicode_SurrogateHigh) * (unicode_size_Surrogate >> 1);
        cp += (src[1] - unicode_SurrogateLow);
    }
    if (cp > unicode_Max) err = encoding_err_OutOfRange;
    else if (unicode_isSurrogate(cp)) err = encoding_err_Surrogate;
    errProcess:
    if (ofs != NULL) *ofs = codeUnit;
    *dst = err == encoding_err_None ? cp : unicode_Replacement;
    return err;
}

define(encoding_err, encode, unicode src, uint16_t *dst, uint8_t length, uint8_t *ofs) {
    if (dst == NULL) return encoding_err_NullPtr;
    encoding_err err = encoding_err_None;
    if (src > unicode_Max || unicode_isSurrogate(src)) {
        err = encoding_err_InvalidCodepoint;
        src = unicode_Replacement;
    }
    uint8_t codeUnit = src >= unicode_size_Plane ? 2 : 1;
    if (codeUnit > length) return encoding_err_BufTooSmall;
    if (codeUnit == 2) {
        src -= unicode_size_Plane;
        dst[0] = unicode_SurrogateHigh + src / (unicode_size_Surrogate >> 1);
        dst[1] = unicode_SurrogateLow + src % (unicode_size_Surrogate >> 1);
    } else {
        dst[0] = src;
    }
    if (ofs != NULL) *ofs = codeUnit;
    return err;
}

#undef moduleName
