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

#define	SIG_ERR	  ((void (*) (int)) -1)  /* Error return. */
#define	SIG_DFL	  ((void (*) (int))  0)  /* Default action. */
#define	SIG_IGN	  ((void (*) (int))  1)  /* Ignore signal. */

#ifdef __USE_UNIX98
# define SIG_HOLD ((void (*) (int))  2)  /* Add signal to hold mask. */
#endif

#define SIGHUP       1    /* Exit     Hangup */
#define SIGINT       2    /* Exit     Interrupt */
#define SIGQUIT      3    /* Core     Quit */
#define SIGILL       4    /* Core     Illegal Instruction */
#define SIGTRAP      5    /* Core     Trace/Breakpoint Trap */
#define SIGABRT      6    /* Core     Abort */
#define SIGEMT       7    /* Core     Emulation Trap */
#define SIGFPE       8    /* Core     Arithmetic Exception */
#define SIGKILL      9    /* Exit     Killed */
#define SIGBUS      10    /* Core     Bus Error */
#define SIGSEGV     11    /* Core     Segmentation	Fault */
#define SIGSYS      12    /* Core     Bad System Call */
#define SIGPIPE     13    /* Exit     Broken Pipe */
#define SIGALRM     14    /* Exit     Alarm Clock */
#define SIGTERM     15    /* Exit     Terminated */
#define SIGUSR1     16    /* Exit     User Signal 1 */
#define SIGUSR2     17    /* Exit     User Signal 2 */
#define SIGCLD      18    /* Ignore   Same  as SIGCHLD (System V). */
#define SIGCHLD     18    /* Ignore   Child Status	Changed */
#define SIGPWR      19    /* Ignore   Power Fail/Restart */
#define SIGWINCH    20    /* Ignore   Window Size Change */
#define SIGURG      21    /* Ignore   Urgent Socket Condition */
#define SIGPOLL     22    /* Exit     Pollable Event */
#define SIGIO       22    /* Exit     input/output	possible signal */
#define SIGSTOP     23    /* Stop     Stopped (signal) */
#define SIGTSTP     24    /* Stop     Stopped (user) */
#define SIGCONT     25    /* Ignore   Continued */
#define SIGTTIN     26    /* Stop     Stopped (tty	input) */
#define SIGTTOU     27    /* Stop     Stopped (tty	output) */
#define SIGVTALRM   28    /* Exit     Virtual Timer Expired */
#define SIGPROF     29    /* Exit     Profiling Timer Expired */
#define SIGXCPU     30    /* Core     CPU time limit exceeded */
#define SIGXFSZ     31    /* Core     File	size limit exceeded */
#define	SIGSTKFLT   32	  /* Core     Stack fault. */
#define SIGCKPT     33    /* Ignore   Checkpoint warning */
#define SIGRESTART  34    /* Ignore   Restart warning */
#define SIGLKALRM   35    /* Core     infinite lock timeout expired (default 30 days)*/
#define SIGPRE      36    /* Core     NT exception, si_value is pointer to EXCEPTION_RECORD */
#define SIGLOST     37    /* Exit     Resource lost (Sun).  */
#define SIGRTMIN    49    /* Exit     POSIX 1003.1b SIGRTMIN */
#define SIGRTMAX    63    /* Exit     POSIX 1003.1b SIGRTMAX */

#define _NSIG       64    /* Biggest signal number + 1, but really the sigset_t bit count. */
