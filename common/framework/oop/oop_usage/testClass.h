//
// Created by CodingDev on 2026/2/24.
//

// 公共
#if !defined(PROTECTED)
#define PUBLIC
// 公共 继承
/*
 * #define $PUBLIC
 * #include "testClassBase"
 */
#undef PUBLIC
#endif

// 保护
#if defined($INTERNAL) || defined($PRIVATE) || defined($PROTECTED) || defined($PUBLIC)
#define PROTECTED
// 保护 继承
/*
 * #define $PROTECTED
 * #include "testClassBase"
 */
// 公共 继承
/*
 * #define $PUBLIC
 * #include "testClassBase"
 */
#undef PROTECTED
#endif

// 私有
#if defined($INTERNAL)
#define PRIVATE
// 私有 继承
/*
 * #define $PRIVATE
 * #include "testClassBase"
 */
#undef PRIVATE
#endif

#undef $INTERNAL
#undef $PRIVATE
#undef $PROTECTED
#undef $PUBLIC
