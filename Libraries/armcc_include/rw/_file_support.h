/* _file_support.h
 *
 * Copyright 2002 ARM Limited. All rights reserved.
 *
 * $Id: _file_support.h 172106 2011-11-02 17:04:12Z statham $
 * $URL: http://cam-svn1.cambridge.arm.com/svn/devsys/rvct/cpplib/BRA_RVCT_5.06/stdlib/include/rw/_file_support.h $
 */

/* added file to implement some of the fileno behaviour */

#ifndef _RWSTD_FILE_SUPPORT_H_INCLUDED
#define _RWSTD_FILE_SUPPORT_H_INCLUDED

#include <rw/_defs.h>
#include _RWSTD_CSTDIO

_RWSTD_NAMESPACE_BEGIN (__rw)

_USING (namespace std);

#ifdef _RWSTD_NO_FILENO

#ifndef STDIN_FILENO 
#  define STDIN_FILENO  0
#  define STDOUT_FILENO 1
#  define STDERR_FILENO 2
#endif //STDIN_FILENO 

inline int fileno (FILE* _C_fptr) // very simple and not complete implementation of fileno
// not extern "C", which introduces additional complications by masquerading as a 'real' fileno
{
    
   if (_C_fptr == &std::__stdin) return STDIN_FILENO;
   if (_C_fptr == &std::__stdout) return STDOUT_FILENO;
   if (_C_fptr == &std::__stderr) return STDERR_FILENO;
   return (int)_C_fptr; // should be unique, but fdopen will not work
}
#endif //STDIN_FILENO

_RWSTD_NAMESPACE_END   // __rw

#endif //_RWSTD_FILE_SUPPORT_H_INCLUDED



