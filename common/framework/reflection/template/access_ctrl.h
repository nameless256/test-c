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

#ifdef classVtabDecl
#define accessStart classVtabDefStart
#define accessEnd classVtabDefEnd
#define bind(...)
#define export(...)
#define virtual(...) accessDispatch(_dummyVirtual, _virtual, ##__VA_ARGS__);
#elif defined(classVtabBind)
#define accessStart classVtabStart
#define accessEnd classVtabEnd
#define bind(name) _bind(name),
#define export(...)
#define virtual(ret, func, ...) _bind(func),
#else
#define accessStart
#define accessEnd
#define bind(...)
#define export(...) accessDispatch(_dummyVoid, _export, ##__VA_ARGS__);
#define virtual(...) export(__VA_ARGS__)
#endif
