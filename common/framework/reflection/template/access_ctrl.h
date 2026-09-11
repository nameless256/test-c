//
// Created by CodingDev on 2026/8/29.
//

#ifndef accessCtrl
#define accessCtrl $public
#endif

#define accessLv $private

#if accessCtrl > $public
#define protected(...) _export(__VA_ARGS__)
#else
#define protected(...)
#endif
#if accessCtrl > $protected
#define private(...) _export(__VA_ARGS__)
#else
#define private(...)
#endif
#define public(...) _export(__VA_ARGS__)

#ifdef vtabDecl
#define accessStart classVtabDefStart
#define accessEnd classVtabDefEnd
#define export(...)
#define virtual(...) accessDispatch(_dummyVirtual, _virtual, ##__VA_ARGS__);
#elif defined(vtabBind)
#define accessStart
#define accessEnd
#define export(...)
#define virtual(ret, func, ...) bind(func),
#else
#define accessStart
#define accessEnd
#define export(...) accessDispatch(_dummyVoid, _export, ##__VA_ARGS__);
#define virtual(...) export(__VA_ARGS__)
#endif
