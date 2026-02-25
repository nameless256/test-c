//
// Created by CodingDev on 2026/2/24.
//

// 公共 继承
/*
 * #define EXTENDS
 * #include "testClassBase"
 */

#if (defined(DECLARE) && !defined(EXTENDS)) || defined(EXTENDS)
// 保护 继承
/*
 * #define EXTENDS
 * #include "testClassBase"
 */
#endif

#if (defined(DECLARE) && !defined(EXTENDS))
// 私有 继承
/*
 * #define EXTENDS
 * #include "testClassBase"
 */
#endif

#undef DECLARE
#undef EXTENDS
