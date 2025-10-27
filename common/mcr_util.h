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
#define pred(n) cat2(pred, n)
#pragma endregion

#pragma region "mcrIter"
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
#define mcrIter(f, ...) cat2(_mcrIter, mcrVaCount(__VA_ARGS__))(f, __VA_ARGS__)
#pragma endregion

#pragma region "mcrPIter"
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
#define mcrPIter(f, fpi, p, ...) cat2(_mcrPIter, mcrVaCount(__VA_ARGS__))(f, fpi, p, __VA_ARGS__)
#pragma endregion

#pragma region "mcrParamPIter"
#define _mcrParamPIter1(f, fpi, p, arg, ...) f(p, arg)
#define _mcrParamPIter2(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter3(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter4(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter5(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter6(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter7(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter8(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter9(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter10(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter11(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter12(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter13(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter14(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter15(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define _mcrParamPIter16(f, fpi, p, arg, ...) f(p, arg),cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, fpi(p), __VA_ARGS__)
#define mcrParamPIter(f, fpi, p, ...) cat2(_mcrParamPIter, mcrVaCount(__VA_ARGS__))(f, fpi, p, __VA_ARGS__)
#pragma endregion

#define _not0 ,
#define mcrNot(i) pred(mcrVaCount(cat2(_not, i)))
#define __exBy00(arg)
#define __exBy01(arg) arg
#define _exBy0(i, arg) cat2(__exBy0, mcrNot(i))(arg)
#define mcrVaArg(i, ...) mcrPIter(_exBy0, pred, i, __VA_ARGS__)

#define asIs(arg) arg

#define _mcrVaCount(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...) N
#define mcrVaCount(...) _mcrVaCount(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define _mcrVaTupleUnpack(...) __VA_ARGS__
#define mcrVaTupleUnpack(arg) _mcrVaTupleUnpack arg
#define _mcrVaTupleCheck(...) , _1
#define mcrVaTupleCheck(arg) pred(mcrVaCount(_mcrVaTupleCheck arg))
#define __mcrVaTuple10(arg) arg
#define __mcrVaTuple11(arg) mcrVaTupleUnpack(arg)
#define _mcrVaTuple1(arg) cat2(__mcrVaTuple1, mcrVaTupleCheck(arg))(arg)
#define _mcrVaTuple2(arg, i) mcrVaArg(i, _mcrVaTuple1(arg))
#define mcrVaTuple(...) cat2(_mcrVaTuple, mcrVaCount(__VA_ARGS__)) (__VA_ARGS__)

#define mcrVaTupleArgCountEq1(tuple) mcrNot(pred(mcrVaCount(mcrVaTuple(tuple))))

#endif //MCR_UTIL_H
