//
// Created by CodingDev on 2026/8/29.
//

#undef accessLv
#undef className
#undef protected
#undef private
#undef public
#undef accessStart
#undef accessEnd
#undef export
#undef virtual

#if accessCtrl == $private
#undef accessCtrl
#define accessCtrl $protected
#endif
