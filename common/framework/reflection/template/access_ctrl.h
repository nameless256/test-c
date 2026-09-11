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
