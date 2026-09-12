//
// Created by CodingDev on 2026/9/12.
//

#ifdef classVtabDecl
#if accessCtrl == $private
#undef accessCtrl
#define accessCtrl $protected
#endif
#define classStart
#define classEntry(...)
#define classEnd
#else
#ifdef accessCtrl
#undef accessCtrl
#endif
#ifdef classVtabBind
#include "reg_meta_class.h"
#else
#include "def_class.h"
#endif
#endif
