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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(__PXWC__)
#error "You have another version of pxwc in your environment! Please remove it befor building pxwc!"
#endif

static int find_char(const char * str, char ch)
{
	while(*str != '\0')
	{
		if(*(++str) == ch)
			return 1;
	}
	return 0;
}

/* Returns NULL or a pointer to "Buffer" if successfull */
char * __pxwc_convert(char * Buffer, int Size)
{
	/* Take Buffer (contains Path) and convert it, replace old value and return buffer */
	char * Output = malloc(Size);
	char * InterixDir = getenv("SFUDIR");
	char * command = malloc(strlen(InterixDir) + Size + 100);
	FILE * pipe;

	strcpy(command, InterixDir);
	strcat(command, "/bin/unixpath2win ");
	strcat(command, Buffer);
	strcat(command, " 2>__pxwc_env_tmp");

	pipe = _popen(command, "r");

	if(!fgets(Output, Size, pipe))
	{
		/* Don't return immediatly, because we need to clean up */
		/* But still let us know we've failed */
		free(Output);
		Output = NULL;
	}

	_pclose(pipe);
	free(command);
	unlink("__pxwc_env_tmp");

	if(!Output || strlen(Output) <= 0)
		return NULL;

	Output[strlen(Output) - 1] = '\0';	/* Strip the '\n' */

	strncpy(Buffer, Output, Size);

	free(Output);

	return Buffer;
}



/* This has the same signature as the real getenv. */
/* In pxwc.h getenv is redefined to this one. This
	affects stdlib.h, which is fine here, because
	we then get this function by only including stdlib.h.
	No need to include win_paths.h anywhere for now! */


static char * __dummy_getenv(const char * EnvName)
{
	char * EnvContent = getenv(EnvName);

	/* Return null if nothing was found for that env */
	if(!EnvContent)
		return NULL;

	/* Return unconverted Env if it does not start with "/" or ":/" */
	/* The ":" may appear as first char in seperated path lists ... */
	if(!(EnvContent[0] == '/' || (strncmp(EnvContent, ":/", 2) == 0) || (strncmp(EnvContent, ".:/", 3) == 0)))
		return EnvContent;

	/* It seems here we can asume we have a path ... Just find out how many of them */
	/* Inside this "if" conversion takes place and the modified vars get written back to the Env */
	if(find_char(EnvContent, ':'))
	{
		/* Multiple Paths found  */
		char * Content	= strdup(EnvContent);
		char * Final	= malloc(strlen(EnvContent) * 2);
		char * Token	= strtok(Content, ":");

		Final[0] = '\0';	/* So we can use strcat */

		while(Token != NULL)
		{
			if(Token[0] == '.')
			{
				strcat(Final, Token);
				strcat(Final, ";");
			} else {
				char * Buffer = malloc(strlen(Token) * 2);
				strcpy(Buffer, Token);	/* Don't use Token directly, may corrupt Content */

				if(!__pxwc_convert(Buffer, strlen(Token) * 2))
				{
					strcat(Final, Token);	/* Still insert original path if conversion failed */
				} else {
					strcat(Final, Buffer);
				}

				free(Buffer);
				strcat(Final, ";");
			}
			Token = strtok(NULL, ":");
		}

		if(Final && strlen(Final) >= 0)
		{
			char * PutEnv = malloc(strlen(EnvName) + strlen(Final) + 1 /* For the "=" */);

			Final[strlen(Final) - 1] = '\0'; /* Strip last ";" */

			strcpy(PutEnv, EnvName);
			strcat(PutEnv, "=");
			strcat(PutEnv, Final);

			if(_putenv(PutEnv) != 0)
			{
				free(Content);
				free(Final);
				free(PutEnv);
				return EnvContent;
			}

			free(PutEnv);
		}

		free(Content);
		free(Final);

	} else {
		/* One single Path found */
		char * Buffer = malloc(strlen(EnvContent) * 2);
		strcpy(Buffer, EnvContent);

		if(!__pxwc_convert(Buffer, strlen(EnvContent) * 2))
		{
			/* Buffer is untouched, so it's save to free() it */
			free(Buffer);
			return EnvContent;
		} else {
			char * PutEnv = malloc(strlen(EnvName) + strlen(Buffer) + 1 /* for the "=" */ + 1 /* for the \0 */);
			strcpy(PutEnv, EnvName);
			strcat(PutEnv, "=");
			strcat(PutEnv, Buffer);

			if(_putenv(PutEnv) != 0)
			{
				free(PutEnv);
				free(Buffer);
				return EnvContent;
			}
			free(PutEnv);
		}

		free(Buffer);
	}

	/* If everything went well, we return an original getenv on the converted var... */
	return getenv(EnvName);
}

char * __cdecl __pxwc_getenv(const char * EnvName)
{
	return __dummy_getenv(EnvName);
}

#ifndef PIC
char * (*_imp____pxwc_getenv)(const char*) = __pxwc_getenv;
#endif
