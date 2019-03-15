/***************************************************************************
 *
 * _messages.cc - Definitions for the Standard Library messaging facet
 *
 * $Id: _messages.cc 172106 2011-11-02 17:04:12Z statham $
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
 **************************************************************************/


_RWSTD_NAMESPACE_BEGIN (std)


template <class _CharT>
locale::id messages<_CharT>::id;


template <class _CharT>
_TYPENAME messages<_CharT>::string_type
messages<_CharT>::do_get (__rw_messages_base::catalog __cat,
                          int                    __set,
                          int                    __msgid,
                          const string_type     &__dflt) const
{
    const char *__text = _C_get_message (__cat, __set, __msgid);

    // The following is wrong -- it should be using codecvt instead of
    // ctype.widen, but this requires an effective codecvt implementation ...

    if (__text) {

        const ctype<_CharT>& __ctp = _USE_FACET (ctype<char_type>,
                                                   _C_get_locale (__cat));

#ifndef _RWSTD_NO_EXT_LOCALE
        return __ctp.widen (string (__text));
#else
        size_t __len = strlen (__text);

        char_type *__wide_text = new _CharT [__len + 1];

        __ctp.widen (__text, __text + __len, __wide_text);

        string_type __str (__wide_text, __wide_text + __len);

        delete[] __wide_text;

        return __str;

#endif   // _RWSTD_STRICT_ANSI

    }
    return __dflt;
}


_RWSTD_NAMESPACE_END   // std

