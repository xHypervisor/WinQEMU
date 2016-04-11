 /**************************************************************************\
 *                                                                          *
 *   pxwc - wgcc's gcc to cl libc wrapper                                   *
 *   Copyright (C) 2006  Markus Duft <markus.duft@salomon.at>               *
 *                                                                          *
 *   This library is free software; you can redistribute it and/or          *
 *   modify it under the terms of the GNU Lesser General Public             *
 *   License as published by the Free Software Foundation; either           *
 *   version 2.1 of the License, or (at your option) any later version.     *
 *                                                                          *
 *   This library is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *   Lesser General Public License for more details.                        *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with this library; if not, write to the Free Software    *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,             *
 *   MA  02110-1301 USA                                                     *
 *                                                                          *
 \**************************************************************************/

// NOTE: This file was modified by Markus Duft to suit the needs of pxwc,
// read the original copyright notice below. (modification was about duplicating
// some code, so that both wide-character and normal versions of all functions
// exist in one library.

/*
 * dirent.c
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is a part of the mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within the package.
 *
 * Derived from DIRLIB.C by Matt J. Weinstein 
 * This note appears in the DIRLIB.H
 * DIRLIB.H by M. J. Weinstein   Released to public domain 1-Jan-89
 *
 * Updated by Jeremy Bettis <jeremy@hksys.com>
 * Significantly revised and rewinddir, seekdir and telldir added by Colin
 * Peters <colin@fu.is.saga-u.ac.jp>
 *	
 */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include "dirent.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h> /* for GetFileAttributes */

#include <tchar.h>

/*
#ifdef _UNICODE
#define _tdirent	_wdirent
#define _TDIR 		_WDIR
#define _topendir	_wopendir
#define _tclosedir	_wclosedir
#define _treaddir	_wreaddir
#define _trewinddir	_wrewinddir
#define _ttelldir	_wtelldir
#define _tseekdir	_wseekdir
#else
#define _tdirent	dirent
#define _TDIR 		DIR
#define _topendir	opendir
#define _tclosedir	closedir
#define _treaddir	readdir
#define _trewinddir	rewinddir
#define _ttelldir	telldir
#define _tseekdir	seekdir
#endif
*/

#define SUFFIX	"*"
#define	SLASH	"\\"

#define SUFFIX_W L"*"
#define SLASH_W L"\\"


/* Following is ASCII */

/*
 * opendir
 *
 * Returns a pointer to a DIR structure appropriately filled in to begin
 * searching a directory.
 */
DIR * 
opendir (const char *szPath)
{
  DIR *nd;
  unsigned int rc;
  char szFullPath[MAX_PATH];
	
  errno = 0;

  if (!szPath)
    {
      errno = EFAULT;
      return (DIR *) 0;
    }

  if (szPath[0] == _T('\0'))
    {
      errno = ENOTDIR;
      return (DIR *) 0;
    }

  /* Attempt to determine if the given path really is a directory. */
  rc = GetFileAttributes (szPath);
  if (rc == (unsigned int)-1)
    {
      /* call GetLastError for more error info */
      errno = ENOENT;
      return (DIR *) 0;
    }
  if (!(rc & FILE_ATTRIBUTE_DIRECTORY))
    {
      /* Error, entry exists but not a directory. */
      errno = ENOTDIR;
      return (DIR *) 0;
    }

  /* Make an absolute pathname.  */
  _tfullpath (szFullPath, szPath, MAX_PATH);

  /* Allocate enough space to store DIR structure and the complete
   * directory path given. */
  nd = (DIR *) malloc (sizeof (DIR) + (_tcslen(szFullPath) + _tcslen (SLASH) +
			 _tcslen(SUFFIX) + 1) * sizeof(char));

  if (!nd)
    {
      /* Error, out of memory. */
      errno = ENOMEM;
      return (DIR *) 0;
    }

  /* Create the search expression. */
  _tcscpy (nd->dd_name, szFullPath);

  /* Add on a slash if the path does not end with one. */
  if (nd->dd_name[0] != _T('\0') &&
      nd->dd_name[_tcslen (nd->dd_name) - 1] != _T('/') &&
      nd->dd_name[_tcslen (nd->dd_name) - 1] != _T('\\'))
    {
      _tcscat (nd->dd_name, SLASH);
    }

  /* Add on the search pattern */
  _tcscat (nd->dd_name, SUFFIX);

  /* Initialize handle to -1 so that a premature closedir doesn't try
   * to call _findclose on it. */
  nd->dd_handle = -1;

  /* Initialize the status. */
  nd->dd_stat = 0;

  /* Initialize the dirent structure. ino and reclen are invalid under
   * Win32, and name simply points at the appropriate part of the
   * findfirst_t structure. */
  nd->dd_dir.d_ino = 0;
  nd->dd_dir.d_reclen = 0;
  nd->dd_dir.d_namlen = 0;
  memset (nd->dd_dir.d_name, 0, FILENAME_MAX);

  return nd;
}


/*
 * readdir
 *
 * Return a pointer to a dirent structure filled with the information on the
 * next entry in the directory.
 */
struct dirent *
readdir (DIR * dirp)
{
  errno = 0;

  /* Check for valid DIR struct. */
  if (!dirp)
    {
      errno = EFAULT;
      return (struct dirent *) 0;
    }

  if (dirp->dd_stat < 0)
    {
      /* We have already returned all files in the directory
       * (or the structure has an invalid dd_stat). */
      return (struct dirent *) 0;
    }
  else if (dirp->dd_stat == 0)
    {
      /* We haven't started the search yet. */
      /* Start the search */
      dirp->dd_handle = _tfindfirst (dirp->dd_name, &(dirp->dd_dta));

  	  if (dirp->dd_handle == -1)
	{
	  /* Whoops! Seems there are no files in that
	   * directory. */
	  dirp->dd_stat = -1;
	}
      else
	{
	  dirp->dd_stat = 1;
	}
    }
  else
    {
      /* Get the next search entry. */
      if (_tfindnext (dirp->dd_handle, &(dirp->dd_dta)))
	{
	  /* We are off the end or otherwise error.	
	     _findnext sets errno to ENOENT if no more file
	     Undo this. */ 
	  DWORD winerr = GetLastError();
	  if (winerr == ERROR_NO_MORE_FILES)
	    errno = 0;	
	  _findclose (dirp->dd_handle);
	  dirp->dd_handle = -1;
	  dirp->dd_stat = -1;
	}
      else
	{
	  /* Update the status to indicate the correct
	   * number. */
	  dirp->dd_stat++;
	}
    }

  if (dirp->dd_stat > 0)
    {
      /* Successfully got an entry. Everything about the file is
       * already appropriately filled in except the length of the
       * file name. */
      dirp->dd_dir.d_namlen = _tcslen (dirp->dd_dta.name);
      _tcscpy (dirp->dd_dir.d_name, dirp->dd_dta.name);
      return &dirp->dd_dir;
    }

  return (struct dirent *) 0;
}


/*
 * closedir
 *
 * Frees up resources allocated by opendir.
 */
int
closedir (DIR * dirp)
{
  int rc;

  errno = 0;
  rc = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return -1;
    }

  if (dirp->dd_handle != -1)
    {
      rc = _findclose (dirp->dd_handle);
    }

  /* Delete the dir structure. */
  free (dirp);

  return rc;
}

/*
 * rewinddir
 *
 * Return to the beginning of the directory "stream". We simply call findclose
 * and then reset things like an opendir.
 */
void
rewinddir (DIR * dirp)
{
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return;
    }

  if (dirp->dd_handle != -1)
    {
      _findclose (dirp->dd_handle);
    }

  dirp->dd_handle = -1;
  dirp->dd_stat = 0;
}

/*
 * telldir
 *
 * Returns the "position" in the "directory stream" which can be used with
 * seekdir to go back to an old entry. We simply return the value in stat.
 */
long
telldir (DIR * dirp)
{
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return -1;
    }
  return dirp->dd_stat;
}

/*
 * seekdir
 *
 * Seek to an entry previously returned by telldir. We rewind the directory
 * and call readdir repeatedly until either dd_stat is the position number
 * or -1 (off the end). This is not perfect, in that the directory may
 * have changed while we weren't looking. But that is probably the case with
 * any such system.
 */
void
seekdir (DIR * dirp, long lPos)
{
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return;
    }

  if (lPos < -1)
    {
      /* Seeking to an invalid position. */
      errno = EINVAL;
      return;
    }
  else if (lPos == -1)
    {
      /* Seek past end. */
      if (dirp->dd_handle != -1)
	{
	  _findclose (dirp->dd_handle);
	}
      dirp->dd_handle = -1;
      dirp->dd_stat = -1;
    }
  else
    {
      /* Rewind and read forward to the appropriate index. */
      rewinddir (dirp);

      while ((dirp->dd_stat < lPos) && readdir (dirp))
	;
    }
}

/* Following is UNICODE! */

/*
 * opendir
 *
 * Returns a pointer to a DIR structure appropriately filled in to begin
 * searching a directory.
 */
_WDIR * 
_wopendir (const WCHAR *szPath)
{
  _WDIR *nd;
  unsigned int rc;
  WCHAR szFullPath[MAX_PATH];
	
  errno = 0;

  if (!szPath)
    {
      errno = EFAULT;
      return (_WDIR *) 0;
    }

  if (szPath[0] == _T('\0'))
    {
      errno = ENOTDIR;
      return (_WDIR *) 0;
    }

  /* Attempt to determine if the given path really is a directory. */
  rc = GetFileAttributesW (szPath);
  if (rc == (unsigned int)-1)
    {
      /* call GetLastError for more error info */
      errno = ENOENT;
      return (_WDIR *) 0;
    }
  if (!(rc & FILE_ATTRIBUTE_DIRECTORY))
    {
      /* Error, entry exists but not a directory. */
      errno = ENOTDIR;
      return (_WDIR *) 0;
    }

  /* Make an absolute pathname.  */
  _wfullpath (szFullPath, szPath, MAX_PATH);

  /* Allocate enough space to store DIR structure and the complete
   * directory path given. */
  nd = (_WDIR *) malloc (sizeof (_WDIR) + (wcslen(szFullPath) + wcslen (SLASH_W) +
			 wcslen(SUFFIX_W) + 1) * sizeof(wchar_t));

  if (!nd)
    {
      /* Error, out of memory. */
      errno = ENOMEM;
      return (_WDIR *) 0;
    }

  /* Create the search expression. */
  wcscpy (nd->dd_name, szFullPath);

  /* Add on a slash if the path does not end with one. */
  if (nd->dd_name[0] != _T('\0') &&
      nd->dd_name[wcslen (nd->dd_name) - 1] != _T('/') &&
      nd->dd_name[wcslen (nd->dd_name) - 1] != _T('\\'))
    {
      wcscat (nd->dd_name, SLASH_W);
    }

  /* Add on the search pattern */
  wcscat (nd->dd_name, SUFFIX_W);

  /* Initialize handle to -1 so that a premature closedir doesn't try
   * to call _findclose on it. */
  nd->dd_handle = -1;

  /* Initialize the status. */
  nd->dd_stat = 0;

  /* Initialize the dirent structure. ino and reclen are invalid under
   * Win32, and name simply points at the appropriate part of the
   * findfirst_t structure. */
  nd->dd_dir.d_ino = 0;
  nd->dd_dir.d_reclen = 0;
  nd->dd_dir.d_namlen = 0;
  memset (nd->dd_dir.d_name, 0, FILENAME_MAX);

  return nd;
}


/*
 * readdir
 *
 * Return a pointer to a dirent structure filled with the information on the
 * next entry in the directory.
 */
struct _wdirent *
_wreaddir (_WDIR * dirp)
{
  errno = 0;

  /* Check for valid DIR struct. */
  if (!dirp)
    {
      errno = EFAULT;
      return (struct _wdirent *) 0;
    }

  if (dirp->dd_stat < 0)
    {
      /* We have already returned all files in the directory
       * (or the structure has an invalid dd_stat). */
      return (struct _wdirent *) 0;
    }
  else if (dirp->dd_stat == 0)
    {
      /* We haven't started the search yet. */
      /* Start the search */
      dirp->dd_handle = _wfindfirst (dirp->dd_name, &(dirp->dd_dta));

  	  if (dirp->dd_handle == -1)
	{
	  /* Whoops! Seems there are no files in that
	   * directory. */
	  dirp->dd_stat = -1;
	}
      else
	{
	  dirp->dd_stat = 1;
	}
    }
  else
    {
      /* Get the next search entry. */
      if (_wfindnext (dirp->dd_handle, &(dirp->dd_dta)))
	{
	  /* We are off the end or otherwise error.	
	     _findnext sets errno to ENOENT if no more file
	     Undo this. */ 
	  DWORD winerr = GetLastError();
	  if (winerr == ERROR_NO_MORE_FILES)
	    errno = 0;	
	  _findclose (dirp->dd_handle);
	  dirp->dd_handle = -1;
	  dirp->dd_stat = -1;
	}
      else
	{
	  /* Update the status to indicate the correct
	   * number. */
	  dirp->dd_stat++;
	}
    }

  if (dirp->dd_stat > 0)
    {
      /* Successfully got an entry. Everything about the file is
       * already appropriately filled in except the length of the
       * file name. */
      dirp->dd_dir.d_namlen = wcslen (dirp->dd_dta.name);
      wcscpy (dirp->dd_dir.d_name, dirp->dd_dta.name);
      return &dirp->dd_dir;
    }

  return (struct _wdirent *) 0;
}


/*
 * closedir
 *
 * Frees up resources allocated by opendir.
 */
int
_wclosedir (_WDIR * dirp)
{
  int rc;

  errno = 0;
  rc = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return -1;
    }

  if (dirp->dd_handle != -1)
    {
      rc = _findclose (dirp->dd_handle);
    }

  /* Delete the dir structure. */
  free (dirp);

  return rc;
}

/*
 * rewinddir
 *
 * Return to the beginning of the directory "stream". We simply call findclose
 * and then reset things like an opendir.
 */
void
_wrewinddir (_WDIR * dirp)
{
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return;
    }

  if (dirp->dd_handle != -1)
    {
      _findclose (dirp->dd_handle);
    }

  dirp->dd_handle = -1;
  dirp->dd_stat = 0;
}

/*
 * telldir
 *
 * Returns the "position" in the "directory stream" which can be used with
 * seekdir to go back to an old entry. We simply return the value in stat.
 */
long
_wtelldir (_WDIR * dirp)
{
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return -1;
    }
  return dirp->dd_stat;
}

/*
 * seekdir
 *
 * Seek to an entry previously returned by telldir. We rewind the directory
 * and call readdir repeatedly until either dd_stat is the position number
 * or -1 (off the end). This is not perfect, in that the directory may
 * have changed while we weren't looking. But that is probably the case with
 * any such system.
 */
void
_wseekdir (_WDIR * dirp, long lPos)
{
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return;
    }

  if (lPos < -1)
    {
      /* Seeking to an invalid position. */
      errno = EINVAL;
      return;
    }
  else if (lPos == -1)
    {
      /* Seek past end. */
      if (dirp->dd_handle != -1)
	{
	  _findclose (dirp->dd_handle);
	}
      dirp->dd_handle = -1;
      dirp->dd_stat = -1;
    }
  else
    {
      /* Rewind and read forward to the appropriate index. */
      _wrewinddir (dirp);

      while ((dirp->dd_stat < lPos) && _wreaddir (dirp))
	;
    }
}
