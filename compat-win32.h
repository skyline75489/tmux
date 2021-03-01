/*
 * Copyright (c) 2007 Nicholas Marriott <nicholas.marriott@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef COMPAT_WIN32_H
#define COMPAT_WIN32_H

#ifdef _WIN32

#define _WIN32_WINNT_WIN10		0x0A00 		// Windows 10
#define NTDDI_VERSION 			0x0A000006  /* _WIN10_RS5 */

#define WIN32_LEAN_AND_MEAN

#define NOGDI
#define NOMCX
#define NOSOUND
#define NOSERVICE
#define NOUSER

struct winsize {
	unsigned short  ws_row;         /* rows, in characters */
	unsigned short  ws_col;         /* columns, in characters */
	unsigned short  ws_xpixel;      /* horizontal size, pixels - not used */
	unsigned short  ws_ypixel;      /* vertical size, pixels - not used */
};

#define O_NONBLOCK	  04000

#define WIFEXITED(a) (a != 0)
#define WEXITSTATUS(a) a
#define WTERMSIG(a) 0
#define WIFSIGNALED(a) 0
#define realpath(path, resolved_path) _fullpath(resolved_path, path, PATH_MAX)
#define wcwidth(a) 0
#define SIGHUP  	1
#define SIGQUIT		3
#define SIGCHLD 	17
#define SIGCONT		18
#define SIGUSR1 	10
#define SIGUSR2		12
#define SIGPIPE 	13
#define SIGTSTP		20
#define	SIGTTIN		21
#define	SIGTTOU		22
#define SIGWINCH 	28

#include <winsock2.h>
#include <ws2tcpip.h>

struct iovec
{
	void *iov_base;	/* Pointer to data.  */
	size_t iov_len;	/* Length of data.  */
};

struct msghdr
  {
    void *msg_name;		/* Address to send to/receive from.  */
    socklen_t msg_namelen;	/* Length of address data.  */

    struct iovec *msg_iov;	/* Vector of data to send/receive into.  */
    size_t msg_iovlen;		/* Number of elements in the vector.  */

    void *msg_control;		/* Ancillary data (eg BSD filedesc passing). */
    size_t msg_controllen;	/* Ancillary data buffer length.
				   !! The type should be socklen_t but the
				   definition of the kernel is incompatible
				   with this.  */

    int msg_flags;		/* Flags on received message.  */
  };

#define SHUT_RD 	SD_RECEIVE
#define SHUT_WR 	SD_SEND
#define SHUT_RDWR	SD_BOTH

#define UNIX_PATH_MAX 108
typedef unsigned int uid_t;

typedef struct sockaddr_un
{
     ADDRESS_FAMILY sun_family;     /* AF_UNIX */
     char sun_path[UNIX_PATH_MAX];  /* pathname */
} SOCKADDR_UN, *PSOCKADDR_UN;

#define SIO_AF_UNIX_GETPEERPID _WSAIOR(IOC_VENDOR, 256) // Returns ULONG PID of the connected peer process

#define _PATH_POWERSHELL	"powershell.exe"

DWORD forkpty_conpty(char *shell, HPCON hPC, struct winsize *ws);

#if defined(HAVE_NCURSES_H)
#include <ncurses/term.h>
#undef lines
#undef columns
#endif

#define fnmatch(a, b, c) TRUE
#endif /* _WIN32 */
#endif /* COMPAT_WIN32_H */
