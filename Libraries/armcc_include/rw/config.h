/* Copyright (c) 1994-2001 Rogue Wave Software, Inc.  All Rights Reserved. */
/* Copyright (c) 2002 ARM Ltd. All Rights Reserved.                        */
#ifndef __RW_CONFIG_H_INCLUDED
#define __RW_CONFIG_H_INCLUDED

#define _RWSTD_NO_NATIVE_IO // Rogue Wave global config options
#define _RWSTD_NO_CONST_FLT_ROUNDS // auto config
#ifndef __EXCEPTIONS
#define _RWSTD_NO_EXCEPTIONS // auto config
#else
#endif
#define _RWSTD_NO_FILENO // auto config
#ifndef __EXCEPTIONS
#define _RWSTD_NO_FUNCTION_TRY_BLOCK // auto config
#endif
#define _RWSTD_NO_IEEEFP_H_REQUIRED // auto config
#define _RWSTD_LLONG_PRINTF_PREFIX "ll"
#define _RWSTD_NO_LRAND48 // auto config
#define _RWSTD_NO_MATH_EXCEPTION // auto config
#define _RWSTD_NO_MBSTATE_COMPARE // auto config
#ifndef __EXCEPTIONS
#define _RWSTD_NO_NEW_THROWS // auto config
#else
#endif
#define _RWSTD_NO_NL_TYPES_H // auto config
#define _RWSTD_NO_SSIZE_T // auto config
#ifndef __EXCEPTIONS
#define _RWSTD_NO_UNCAUGHT_EXCEPTION // auto config
#else
#endif
#define _RWSTD_WINT_T int

#endif /* __RW_CONFIG_H_INCLUDED */
