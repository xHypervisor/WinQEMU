/* Thread package specific definitions of stream lock type.
   Copyright (C) 1996, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include <pthread.h>

typedef pthread_mutex_t _IO_lock_t;

/* We need recursive (counting) mutexes.  */
#define _IO_lock_initializer PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP


#define _IO_cleanup_region_start(_fct, _fp) \
  { NTTH_CLEANUP_BUFFER _L_buffer; \
    int _L_avail = ((_fp)->_flags & _IO_USER_LOCK) == 0; \
    if (_L_avail) \
      __rt_push_cleanup_buffer (&_L_buffer, (_fct), (_fp), 1)

#define _IO_cleanup_region_start_noarg(_fct) \
  { NTTH_CLEANUP_BUFFER _L_buffer; \
    __rt_push_cleanup_buffer (&_L_buffer, (_fct), NULL, 1)

#define _IO_cleanup_region_end(_doit) \
     __libc_cleanup_region_end (_doit)
#define _IO_lock_init(_name) \
     __libc_lock_init_recursive (_name)
#define _IO_lock_fini(_name) \
     __libc_lock_fini_recursive (_name)
#define _IO_lock_lock(_name) \
     __libc_lock_lock (_name)
#define _IO_lock_unlock(_name) \
     __libc_lock_unlock (_name)
