//
// Created by CodingDev on 2026/8/29.
//

#undef className
#undef protected
#undef private
#undef public

#if accessCtrl > accLvPublic
#undef accessCtrl
#define accessCtrl accLvProtected
#else
#undef accessCtrl
#define accessCtrl accLvPublic
#endif
