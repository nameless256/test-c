//
// Created by CodingDev on 2026/8/29.
//

#undef className
#undef protected
#undef private
#undef public

#if $access > $public
#undef $access
#define $access $protected
#else
#undef $access
#define $access $public
#endif
