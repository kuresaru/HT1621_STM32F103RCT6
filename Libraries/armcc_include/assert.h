/* assert.h: ANSI 'C' (X3J11 Oct 88) library header section 4.2 */
/* Copyright (C) Codemist Ltd., 1988-1993                       */
/* Copyright 1991-1993 ARM Limited. All rights reserved.        */
/* version 0.04 */

/*
 * RCS $Revision: 179217 $
 * Checkin $Date: 2013-03-12 14:03:19 +0000 (Tue, 12 Mar 2013) $
 * Revising $Author: drodgman $
 */

/*
 * The assert macro puts diagnostics into programs. When it is executed,
 * if its argument expression is false, it writes information about the
 * call that failed (including the text of the argument, the name of the
 * source file, and the source line number - the latter are respectively
 * the values of the preprocessing macros __FILE__ and __LINE__) on the
 * standard error stream. It then calls the abort function.
 * If its argument expression is true, the assert macro returns no value.
 */

/*
 * Note that <assert.h> may be included more that once in a program with
 * different setting of NDEBUG. Hence the slightly unusual first-time
 * only flag.
 */

#ifndef __assert_h
#   define __assert_h
#define _ARMABI_NORETURN __declspec(__nothrow) __declspec(__noreturn)
#define __ARMCLIB_VERSION 5060002
#   ifndef __ARM_PROMISE
#      define __ARM_PROMISE __promise
#   endif
#   undef __CLIBNS
#   ifdef __cplusplus
        namespace std {
#           define __CLIBNS ::std::
            extern "C" {
#   else
#       define __CLIBNS
#   endif  /* __cplusplus */
    extern _ARMABI_NORETURN void abort(void);
    extern _ARMABI_NORETURN void __aeabi_assert(const char *, const char *, int) __attribute__((__nonnull__(1,2)));
#   ifdef __cplusplus
            }  /* extern "C" */
        }  /* namespace std */
#   endif
#else
#   undef assert
#   undef __promise
#endif

#ifdef NDEBUG
#   define assert(ignore) ((void)0)
#   define __promise(e) ((__ARM_PROMISE)((e)?1:0))
#else
#   if defined __DO_NOT_LINK_PROMISE_WITH_ASSERT
#      if defined __OPT_SMALL_ASSERT && !defined __ASSERT_MSG && !defined __STRICT_ANSI__ && !(_AEABI_PORTABILITY_LEVEL != 0 || (!defined _AEABI_PORTABILITY_LEVEL && __DEFAULT_AEABI_PORTABILITY_LEVEL != 0))
#          define assert(e) ((e) ? (void)0 : __CLIBNS abort())
#      elif defined __STDC__
#          define assert(e) ((e) ? (void)0 : __CLIBNS __aeabi_assert(#e, __FILE__, __LINE__))
#      else
#          define assert(e) ((e) ? (void)0 : __CLIBNS __aeabi_assert("e", __FILE__, __LINE__))
#      endif
#      define __promise(e) ((__ARM_PROMISE)((e)?1:0))
#   else
#      if defined __OPT_SMALL_ASSERT && !defined __ASSERT_MSG && !defined __STRICT_ANSI__ && !(_AEABI_PORTABILITY_LEVEL != 0 || (!defined _AEABI_PORTABILITY_LEVEL && __DEFAULT_AEABI_PORTABILITY_LEVEL != 0))
#undef __promise
#          define assert(e) ((e) ? (void)0 : __CLIBNS abort(), (__ARM_PROMISE)((e)?1:0))
#      else
#          define assert(e) ((e) ? (void)0 : __CLIBNS __aeabi_assert(#e, __FILE__, __LINE__), (__ARM_PROMISE)((e)?1:0))
#      endif
#      define __promise(e) assert(e)
#   endif
#endif

#if _AEABI_PORTABILITY_LEVEL != 0 && !defined _AEABI_PORTABLE
  #define _AEABI_PORTABLE
#endif

/* end of assert.h */

