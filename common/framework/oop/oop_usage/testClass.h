//
// Created by CodingDev on 2026/2/24.
//

// 公共
#if !defined(PROTECTED)
#define PUBLIC
// 公共 继承
/*
 * #define EXTENDS_PUBLIC
 * #include "testClassBase"
 */
#undef PUBLIC
#endif

// 保护
#if defined(EXTENDS_INTERNAL) || defined(EXTENDS_PRIVATE) || defined(EXTENDS_PROTECTED) || defined(EXTENDS_PUBLIC)
#define PROTECTED
// 保护 继承
/*
 * #define EXTENDS_PROTECTED
 * #include "testClassBase"
 */
// 公共 继承
/*
 * #define EXTENDS_PUBLIC
 * #include "testClassBase"
 */
#undef PROTECTED
#endif

// 私有
#if defined(EXTENDS_INTERNAL)
#define PRIVATE
// 私有 继承
/*
 * #define EXTENDS_PRIVATE
 * #include "testClassBase"
 */
#undef PRIVATE
#endif

#undef EXTENDS_INTERNAL
#undef EXTENDS_PRIVATE
#undef EXTENDS_PROTECTED
#undef EXTENDS_PUBLIC
