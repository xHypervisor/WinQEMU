/*
 * WINNT POSIX Library
 * Version:  1.0
 * 
 * Copyright (C) 2002  Andrew Gnezdilov avi@risp.ru  All Rights Reserved.
 *
 * WINNT POSIX is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * WINNT POSIX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WINNT POSIX; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#if !defined _SIGNAL_ && !defined _SYSUCONTEXT_ && !defined _PSXSYS_
# error "Never use <bits/sigaction.h> directly; include <signal.h> instead."
#endif

#ifndef __have_sigaction_t
# define __have_sigaction_t

struct sigaction {
  /* Signal handler. */
# ifdef __USE_POSIX199309
#  if !defined (__GNUC__) || defined (__cplusplus)
  union {
    /* Used if SA_SIGINFO is not set. */
    void (*sa_handler) (int);
    /* Used if SA_SIGINFO is set. */
    void (*sa_sigaction) (int, siginfo_t *, void *);
  };
#  else
  union {
    /* Used if SA_SIGINFO is not set. */
    void (*sa_handler) (int);
    /* Used if SA_SIGINFO is set. */
    void (*sa_sigaction) (int, siginfo_t *, void *);
  } _sh;
#   define sa_handler _sh.sa_handler
#   define sa_sigaction _sh.sa_sigaction
#  endif
# else
  void (*sa_handler) (int);
# endif

  /* Additional set of signals to be blocked. */
  sigset_t sa_mask;

  /* Special flags. */
  int sa_flags;
};

/* Bits in `sa_flags'. */
# define SA_NOCLDSTOP  0x001 /* Don't send SIGCHLD when children stop. */
# define SA_NOCLDWAIT  0x002 /* Don't create zombie on child death. */
# define SA_SIGINFO    0x004 /* Invoke signal-catching function with
                           three arguments instead of one.  */
# if defined __USE_UNIX98 || defined __USE_MISC
#  define SA_ONSTACK   0x008 /* Use signal stack. */
#  define SA_RESTART   0x010 /* Restart syscall on signal return.  */
#  define SA_NODEFER   0x020 /* Don't automatically block the signal when
                                    its handler is being executed.  */
#  define SA_RESETHAND 0x040 /* Reset to SIG_DFL on entry to handler.  */
# endif
# ifdef __USE_MISC
#  define SA_INTERRUPT 0x080 /* Historical no-op.  */

/* Some aliases for the SA_ constants.  */
#  define SA_NOMASK    SA_NODEFER
#  define SA_ONESHOT   SA_RESETHAND
#  define SA_STACK     SA_ONSTACK
# endif

/* Values for the HOW argument to `sigprocmask'.  */
# define	SIG_BLOCK     0		 /* Block signals.  */
# define	SIG_UNBLOCK   1		 /* Unblock signals.  */
# define	SIG_SETMASK   2		 /* Set the set of blocked signals.  */

#endif