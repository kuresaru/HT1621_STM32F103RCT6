; rt_mem_h.s
;
; Copyright 1999 ARM Limited. All rights reserved.
;
; RCS $Revision: 172039 $
; Checkin $Date: 2011-11-02 12:58:12 +0000 (Wed, 02 Nov 2011) $
; Revising $Author: statham $

; This header defines the offsets, in the __user_perproc_libspace
; block, of the words of storage reserved to the memory model
; implementation.

; (This is now only of historical use, since users are recommended
; to use __rt_stackheap_storage instead, which is always four words
; of data starting at the returned address.)

        MAP     16
rt_mm0  FIELD   4
rt_mm1  FIELD   4
rt_mm2  FIELD   4
rt_mm3  FIELD   4

        END

