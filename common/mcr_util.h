//
// Created by Admin on 25-10-26.
//

#ifndef MCR_UTIL_H
#define MCR_UTIL_H

#define BIT(n)                      (1UL << (n))
#define checkBit(arg, n)            (((arg) & BIT(n)) == BIT(n))
#define ARRAY_SIZE(array)           (sizeof(array) / sizeof((array)[0]))
#define MAX(a, b)                   ((a) > (b) ? (a) : (b))
#define MIN(a, b)                   ((a) < (b) ? (a) : (b))
#define ABS(a)                      ((0 - (a)) > 0 ? (-(a)) : (a))
#define SWAP(arg0, arg1)            do{(arg0) ^= (arg1); (arg1) ^= (arg0); (arg0) ^= (arg1);} while(0)
#define name2Str(name)              #name
#define nameVal2Str(name)           name2Str(name)
#define name2StrCase(name)          case name: return name2Str(name)
#define valMap(value, num, total) \
((total) ? (((value) > (total)) ? (num) : ((num) * (value) / (total))) : 0)
#define valMapRange(value, num, lBound, uBound) valMap(value - lBound, num, uBound - lBound)

#define structOffsetOf(type, member) ((uintptr_t)(&((type *)0)->member))

#define containerOf(ptr, type, member) ((type *)((uintptr_t *)(ptr) - structOffsetOf(type, member)))

#define _cat2(a, b) a ## b
#define cat2(a, b) _cat2(a, b)
#define _cat_2(a, b) a ## _ ## b
#define cat_2(a, b) _cat_2(a, b)

#define ALIAS(function)             __attribute__((alias(#function)))
#define WEAK                        __attribute__((weak))
#define UNUSED                      __attribute__((unused))
#define CLEANUP(function)           __attribute__((cleanup(function)))

#pragma region "succ"
#define succ0 1
#define succ1 2
#define succ2 3
#define succ3 4
#define succ4 5
#define succ5 6
#define succ6 7
#define succ7 8
#define succ8 9
#define succ9 10
#define succ10 11
#define succ11 12
#define succ12 13
#define succ13 14
#define succ14 15
#define succ15 16
#define succ16 17
#define succ17 18
#define succ18 19
#define succ19 20
#define succ20 21
#define succ21 22
#define succ22 23
#define succ23 24
#define succ24 25
#define succ25 26
#define succ26 27
#define succ27 28
#define succ28 29
#define succ29 30
#define succ30 31
#define succ31 32
#define succ(n) cat2(succ, n)
#pragma endregion

#pragma region "pred"
#define pred1 0
#define pred2 1
#define pred3 2
#define pred4 3
#define pred5 4
#define pred6 5
#define pred7 6
#define pred8 7
#define pred9 8
#define pred10 9
#define pred11 10
#define pred12 11
#define pred13 12
#define pred14 13
#define pred15 14
#define pred16 15
#define pred17 16
#define pred18 17
#define pred19 18
#define pred20 19
#define pred21 20
#define pred22 21
#define pred23 22
#define pred24 23
#define pred25 24
#define pred26 25
#define pred27 26
#define pred28 27
#define pred29 28
#define pred30 29
#define pred31 30
#define pred32 31
#define pred(n) cat2(pred, n)
#pragma endregion

#pragma region "mcrIter"
#define _mcrIter0(f, arg, ...)
#define _mcrIter1(f, arg, ...) f(arg)
#define _mcrIter2(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter3(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter4(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter5(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter6(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter7(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter8(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter9(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter10(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter11(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter12(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter13(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter14(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter15(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter16(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter17(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter18(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter19(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter20(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter21(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter22(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter23(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter24(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter25(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter26(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter27(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter28(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter29(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter30(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define _mcrIter31(f, arg, ...) f(arg) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#define mcrIter(f, ...) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#pragma endregion

#pragma region "mcrPIter"
#define _mcrPIter0(f, fpi, p, arg, ...)
#define _mcrPIter1(f, fpi, p, arg, ...) f(p, arg)
#define _mcrPIter2(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter3(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter4(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter5(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter6(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter7(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter8(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter9(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter10(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter11(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter12(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter13(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter14(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter15(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter16(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter17(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter18(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter19(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter20(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter21(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter22(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter23(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter24(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter25(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter26(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter27(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter28(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter29(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter30(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrPIter31(f, fpi, p, arg, ...) f(p, arg) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define mcrPIter(f, fpi, p, ...) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, p, __VA_ARGS__)
#pragma endregion

#define _not0 ,
#define mcrNot(i) pred(mcrVaCount(cat2(_not, i)))
#define __exBy00(arg)
#define __exBy01(arg) arg
#define _exBy0(i, arg) cat2(__exBy0, mcrNot(i))(arg)
#define mcrVaArg(i, ...) mcrPIter(_exBy0, pred, i, __VA_ARGS__)

#define asIs(...) __VA_ARGS__

#define __mcrVaCount(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, \
    _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, N, ...) N
#define _mcrVaCount(...) __mcrVaCount(__VA_ARGS__, \
    32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, \
    16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define mcrVaCount(...) pred(_mcrVaCount(dummy, ##__VA_ARGS__))

#define _mcrVaTupleUnpack(...) __VA_ARGS__
#define mcrVaTupleUnpack(arg) _mcrVaTupleUnpack arg
#define _mcrVaTupleCheck(...) , _1
#define mcrVaTupleCheck(arg) pred(mcrVaCount(_mcrVaTupleCheck arg))
#define __mcrVaTuple10(arg) arg
#define __mcrVaTuple11(arg) mcrVaTupleUnpack(arg)
#define _mcrVaTuple0(arg)
#define _mcrVaTuple1(arg) cat2(__mcrVaTuple1, mcrVaTupleCheck(arg))(arg)
#define _mcrVaTuple2(arg, i) mcrVaArg(i, _mcrVaTuple1(arg))
#define mcrVaTuple(...) cat2(_mcrVaTuple, mcrVaCount(__VA_ARGS__)) (__VA_ARGS__)

#define mcrVaTupleArgCount(tuple) _mcrVaCount(mcrVaTuple(tuple))

#endif //MCR_UTIL_H
