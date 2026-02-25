//
// Created by CodingDev on 2026/2/24.
//

// 公共 继承
/*
 * #define EXTENDS
 * #include "testClassBase"
 */
#define PUBLIC
// 公共
#undef PUBLIC

#if defined(DECLARE) || defined(EXTENDS)
#define PROTECTED
// 保护
// 保护 继承
/*
 * #define EXTENDS
 * #include "testClassBase"
 */
#undef PROTECTED
#endif

// 私有
#if defined(DECLARE)
#define PRIVATE
// 私有 继承
/*
 * #define EXTENDS
 * #include "testClassBase"
 */
#undef PRIVATE
#endif

#undef DECLARE
#undef EXTENDS
