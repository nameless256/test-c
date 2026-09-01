//
// Created by CodingDev on 2026/8/29.
//

#ifndef $access
#define $access $public
#endif

#if $access > $public
#define protected(...) export(__VA_ARGS__)
#else
#define protected(...)
#endif
#if $access > $protected
#define private(...) export(__VA_ARGS__)
#else
#define private(...)
#endif
#define public(...) export(__VA_ARGS__)
