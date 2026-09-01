//
// Created by CodingDev on 2026/8/29.
//

#undef className
#undef protected
#undef private
#undef public

#if accessCtrl > $public
#undef accessCtrl
#define accessCtrl $protected
#else
#undef accessCtrl
#define accessCtrl $public
#endif
