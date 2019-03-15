/**************************************************************************
 *
 * Definition of class except_msg_string
 *
 * This is an internal header file used to implement the C++ Standard
 * Library. It should never be #included directly by a program.
 *
 * $Id: _error.h 172106 2011-11-02 17:04:12Z statham $
 *
 ***************************************************************************
 *
 * Copyright (c) 1994-2001 Rogue Wave Software, Inc.  All Rights Reserved.
 *
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software,
 * Inc. pursuant to a written license agreement and may be used, copied,
 * transmitted, and stored only in accordance with the terms of such
 * license and with the inclusion of the above copyright notice.  This
 * computer software or any other copies thereof may not be provided or
 * otherwise made available to any other person.
 *
 * U.S. Government Restricted Rights.  This computer software is provided
 * with Restricted Rights.  Use, duplication, or disclosure by the
 * Government is subject to restrictions as set forth in subparagraph (c)
 * (1) (ii) of The Rights in Technical Data and Computer Software clause
 * at DFARS 252.227-7013 or subparagraphs (c) (1) and (2) of the
 * Commercial Computer Software--Restricted Rights at 48 CFR 52.227-19,
 * as applicable.  Manufacturer is Rogue Wave Software, Inc., 5500
 * Flatiron Parkway, Boulder, Colorado 80301 USA.
 *
 ***************************************************************************/

#ifndef _RWSTD_ERROR_H_INCLUDED
#define _RWSTD_ERROR_H_INCLUDED

#ifndef _RWSTD_NO_INCLUDES
   // prevent inclusion if compiling a .rc file with MSVC
#  include <rw/_defs.h>

_RWSTD_NAMESPACE_BEGIN (__rw)

// throws an exception identified by first argument, optional arguments
// (if any) used to format the exception object's what() string
void _RWSTD_EXPORT __rw_throw (int, ...);

extern "C" {

// throws an exception identified by first argument with the second
// argument containing the exception object's what() string, which
// if non-zero and the first argument <= _RWSTD_ERROR_BAD_CAST, is
// dynamically allocated and must be delete[]'d unless the function
// returns or calls the original throw_proc
// may be assigned to a user-defined handler (e.g., to prevent
// the library from throwing exceptions or to implement logging)
extern void _RWSTD_EXPORT (*__rw_throw_proc)(int, char*);

}   // extern "C"

_RWSTD_NAMESPACE_END   // __rw

#endif   // _RWSTD_NO_INCLUDES


#ifndef _RWSTD_ERROR_CATALOG
   // name of catalog optionally followed by a colon and a set number
   // catalog looked up according to rules of catopen(3)
   // may be customized at lib build time (pathname okay)
#  define _RWSTD_ERROR_CATALOG "rwstderr:1"
#endif   // _RWSTD_ERROR_CATALOG

#ifndef _RWSTD_ERROR_ENVVAR
   // environment variable name - overrides _RWSTD_ERROR_CATALOG
   // may be customized at lib build time
#  define _RWSTD_ERROR_ENVVAR "RWSTDERR"
#endif   // _RWSTD_ERROR_ENVVAR

#ifndef _RWSTD_ERROR_FIRST
   // id of first message - 1, may be customized at lib build time
#  define _RWSTD_ERROR_FIRST 0
#endif   // _RWSTD_ERROR_FIRST


// these must be macros to accomodate MSVC's resource compiler, with values
// expected to be consecutive starting with _RWSTD_ERROR_FIRST + 1

// #  define _RWSTD_ERROR_EXCEPTION                   (_RWSTD_ERROR_FIRST +  1)
// #  define _RWSTD_ERROR_BAD_EXCEPTION               (_RWSTD_ERROR_FIRST +  2)
// #  define _RWSTD_ERROR_BAD_ALLOC                   (_RWSTD_ERROR_FIRST +  3)
#  define _RWSTD_ERROR_BAD_CAST                    (_RWSTD_ERROR_FIRST +  4)
#  define _RWSTD_ERROR_LOGIC_ERROR                 (_RWSTD_ERROR_FIRST +  5)
#  define _RWSTD_ERROR_DOMAIN_ERROR                (_RWSTD_ERROR_FIRST +  6)
#  define _RWSTD_ERROR_INVALID_ARGUMENT            (_RWSTD_ERROR_FIRST +  7)
#  define _RWSTD_ERROR_LENGTH_ERROR                (_RWSTD_ERROR_FIRST +  8)
#  define _RWSTD_ERROR_OUT_OF_RANGE                (_RWSTD_ERROR_FIRST +  9)
#  define _RWSTD_ERROR_RUNTIME_ERROR               (_RWSTD_ERROR_FIRST + 10)
#  define _RWSTD_ERROR_RANGE_ERROR                 (_RWSTD_ERROR_FIRST + 11)
#  define _RWSTD_ERROR_OVERFLOW_ERROR              (_RWSTD_ERROR_FIRST + 12)
#  define _RWSTD_ERROR_UNDERFLOW_ERROR             (_RWSTD_ERROR_FIRST + 13)

#  define _RWSTD_ERROR_FAILBIT_SET                 (_RWSTD_ERROR_FIRST + 14)
#  define _RWSTD_ERROR_BADBIT_SET                  (_RWSTD_ERROR_FIRST + 15)
#  define _RWSTD_ERROR_EOFBIT_SET                  (_RWSTD_ERROR_FIRST + 16)
#  define _RWSTD_ERROR_IOSTATE_BIT_SET             (_RWSTD_ERROR_FIRST + 17)

#  define _RWSTD_ERROR_FACET_NOT_FOUND             (_RWSTD_ERROR_FIRST + 18)
#  define _RWSTD_ERROR_LOCALE_BAD_NAME             (_RWSTD_ERROR_FIRST + 20)
#  define _RWSTD_ERROR_LOCALE_ERROR_NAME           (_RWSTD_ERROR_FIRST + 21)
#  define _RWSTD_ERROR_CODECVT                     (_RWSTD_ERROR_FIRST + 22)

#  define _RWSTD_ERROR_BAD_POINTER                 (_RWSTD_ERROR_FIRST + 23)

#  define _RWSTD_ERROR_STRINGS                          \
          "%s: unspecified error",                      \
          "%s: exception",                              \
          "%s: unexpected exception",                   \
          "%s: bad_alloc: out of memory",               \
          "%s: bad cast",                               \
          "%s: logic error",                            \
          "%s: out of memory",                          \
          "%s: bad cast",                               \
          "%s: length error: %u > %u",                  \
          "%s: argument value %u out of range [0, %u)", \
          "%s: runtime error",                          \
          "%s: range error: invalid range [%d, %d)",    \
          "%s: overflow error",                         \
          "%s: underflow error",                        \
          "%s: stream object has set ios::failbit",     \
          "%s: stream object has set ios::badbit",      \
          "%s: stream object has set ios::eofbit",      \
          "%s: stream object has set %s",               \
          "%s: facet %u not found in \"%s\" locale",    \
          "%s: bad locale name: \"%s\"",                \
          "%s: failed to construct locale name",        \
          "%s: conversion failed",                      \
          "%s: invalid pointer %p"

#define _RWSTD_ERROR_EXCEPTION     "exception"
#define _RWSTD_ERROR_BAD_EXCEPTION "unexpected exception"
#define _RWSTD_ERROR_BAD_ALLOC     "bad_alloc: out of memory"


#endif   // _RWSTD_ERROR_H_INCLUDED

