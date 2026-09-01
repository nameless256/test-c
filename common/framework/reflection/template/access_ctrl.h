//
// Created by CodingDev on 2026/8/29.
//

#ifndef accessCtrl
#define accessCtrl $public
#endif

#if accessCtrl > $public
#define protected(...) export(__VA_ARGS__)
#else
#define protected(...)
#endif
#if accessCtrl > $protected
#define private(...) export(__VA_ARGS__)
#else
#define private(...)
#endif
#define public(...) export(__VA_ARGS__)
