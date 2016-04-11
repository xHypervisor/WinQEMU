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
# error "Never use <bits/sigset.h> directly; include <signal.h> instead."
#endif

#ifndef __have_sigval_t
# define __have_sigval_t

/* Type for data associated with a signal.  */
typedef union sigval {
  int sival_int;
  void *sival_ptr;
} sigval_t;
#endif

#ifndef __have_siginfo_t
# define __have_siginfo_t

typedef struct siginfo {
  int si_signo;		/* Signal number.  */
  int si_errno;		/* If non-zero, an errno value associated with
                     this signal, as defined in <errno.h>.  */
  int si_code;		/* Signal code.  */

  pid_t si_pid;   /* Sending process ID.  */
  uid_t si_uid;   /* Real user ID of sending process.  */

    /* POSIX.1b signals.  */
  sigval_t si_value; /* Signal value.  */
# define si_int  si_value.sival_int
# define si_ptr  si_value.sival_ptr

# if !defined (__GNUC__) || defined (__cplusplus)
  union {
    /* POSIX.1b timers.  */
    struct {
      unsigned int si_timer1; /* sec */
      unsigned int si_timer2; /* nsec */
# ifdef _PSXSYS_
      timer_t timer_id;
# endif
    };

    /* SIGCHLD.  */
    struct {
      int si_status;    /* Exit value or signal.  */
      clock_t si_utime;
      clock_t si_stime;
    };

    /* SIGILL, SIGFPE, SIGSEGV, SIGBUS.  */
    void *si_addr;	/* Faulting insn/memory ref.  */

    /* SIGPOLL.  */
    struct {
      long int si_band;	/* Band event for SIGPOLL.  */
      int si_fd;
    };
  };
# else
  union {
    /* POSIX.1b timers.  */
    struct {
      unsigned int _timer1;
      unsigned int _timer2;
    } _timer;
#  define si_timer1 _sifields._timer._timer1
#  define si_timer2 _sifields._timer._timer2

    /* SIGCHLD.  */
    struct {
      int si_status;    /* Exit value or signal.  */
      clock_t si_utime;
      clock_t si_stime;
    } _sigchld;
#  define si_status _sifields._sigchld.si_status
#  define si_utime _sifields._sigchld.si_utime
#  define si_stime _sifields._sigchld.si_stime


    /* SIGILL, SIGFPE, SIGSEGV, SIGBUS.  */
    void *si_addr;	/* Faulting insn/memory ref.  */
#  define si_addr	_sifields.si_addr

    /* SIGPOLL.  */
    struct {
      long int si_band;	/* Band event for SIGPOLL.  */
      int si_fd;
    } _sigpoll;
#  define si_band _sifields._sigpoll.si_band
#  define si_fd _sifields._sigpoll.si_fd

  } _sifields;
# endif
} siginfo_t;

/* Values for `si_code'. Positive values are reserved for kernel-generated signals.  */
/* Sent by asynch name lookup completion.  */
# define SI_ASYNCNL -6
/* Sent by queued SIGIO. */
# define SI_SIGIO -5
/* Sent by AIO completion. */
# define SI_ASYNCIO	-4
/* Sent by real time mesq state change. */
# define SI_MESGQ -3
/* Sent by timer expiration. */
# define SI_TIMER -2
/* Sent by sigqueue.  */
# define SI_QUEUE -1
/* Sent by kill, sigsend, raise. */
# define SI_USER 0
/* Send by kernel. */
# define SI_KERNEL 0x80

/* `si_code' values for SIGILL signal. */
/* Illegal opcode. */
# define ILL_ILLOPC 1
/* Illegal operand. */
# define ILL_ILLOPN 2
/* Illegal addressing mode. */
# define ILL_ILLADR 3
/* Illegal trap. */
# define ILL_ILLTRP 4
/* Privileged opcode. */
# define ILL_PRVOPC 5
/* Privileged register. */
# define ILL_PRVREG 6
/* Coprocessor error. */
# define ILL_COPROC 7
/* Internal stack error. */
# define ILL_BADSTK 8

/* `si_code' values for SIGFPE signal. */
/* Integer divide by zero. */
# define FPE_INTDIV 1
/* Integer overflow. */
# define FPE_INTOVF 2
/* Floating point divide by zero. */
# define FPE_FLTDIV 3
/* Floating point overflow. */
# define FPE_FLTOVF 4
/* Floating point underflow. */
# define FPE_FLTUND 5
/* Floating point inexact result. */
# define FPE_FLTRES 6
/* Floating point invalid operation. */
# define FPE_FLTINV 7
/* Subscript out of range. */
# define FPE_FLTSUB 8

/* `si_code' values for SIGSEGV signal. */
/* Address not mapped to object. */
# define SEGV_MAPERR 1
/* Invalid permissions for mapped object. */
# define SEGV_ACCERR 2

/* `si_code' values for SIGBUS signal. */
/* Invalid address alignment. */
# define BUS_ADRALN 1
/* Non-existant physical address. */
# define BUS_ADRERR 2
/* Object specific hardware error. */
# define BUS_OBJERR 3

/* `si_code' values for SIGTRAP signal. */
/* Process breakpoint. */
# define TRAP_BRKPT 1
/* Process trace trap. */
# define TRAP_TRACE 2

/* `si_code' values for SIGCHLD signal. */
/* Child has exited.  */
# define CLD_EXITED 1
/* Child was killed.  */
# define CLD_KILLED 2
/* Child terminated abnormally.  */
# define CLD_DUMPED 3
/* Traced child has trapped.  */
# define CLD_TRAPPED 4
/* Child has stopped.  */
# define CLD_STOPPED 5
/* Stopped child has continued.  */
# define CLD_CONTINUED 6

/* `si_code' values for SIGPOLL signal.  */
/* Data input available.  */
# define POLL_IN 1
/* Output buffers available.  */
# define POLL_OUT 2
/* Input message available.   */
# define POLL_MSG 3
/* I/O error.  */
# define POLL_ERR 4
/* High priority input available.  */
# define POLL_PRI 5
/* Device disconnected.  */
# define POLL_HUP 6

/* `si_code' values for SIGLALRM signal.  */
/*  si_ptr is pointer to lock structure */
# ifdef __USE_GNU
#  define LKALRM_SPIN 1
#  define LKALRM_MUTEX 2
#  define LKALRM_RELEASE_MUTEX 3
#  define LKALRM_RWLOCK_ACQUIRE 4
#  define LKALRM_RWLOCK_READ 5
#  define LKALRM_RWLOCK_WRITE 6
#  define LKALRM_ONCE 7
#  define LKALRM_ALTSTACK 8
#  define LKALRM_SEMAPHORE 9
#  define LKALRM_CONDITION 10
#  define LKALRM_BARRIER 11
# endif

#endif

#define BRK_USERBP    1
#define BRK_SSTEPBP   2
#define BRK_OVERFLOW  3
#define BRK_DIVZERO   4
#define BRK_MULOVF    5

#ifdef __need_siginfo_t
# undef __need_siginfo_t
#endif
