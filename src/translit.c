/*** translit.c -- unicode -> ascii transliterator
 *
 * Copyright (C) 2014-2017 Sebastian Freundt
 *
 * Author:  Sebastian Freundt <freundt@ga-group.nl>
 *
 * This file is part of aeiou.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the author nor the names of any contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***/
#if defined HAVE_CONFIG_H
# include "config.h"
#endif	/* HAVE_CONFIG_H */
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <assert.h>
#include "tr_proto.h"
#include "boobs.h"
#include "nifty.h"

#define BSZ	(4096U)

static char *tr[0x10000U] = {
#include "tr_unidecode.c"
};


static void
__attribute__((format(printf, 1, 2)))
error(const char *fmt, ...)
{
	va_list vap;
	va_start(vap, fmt);
	vfprintf(stderr, fmt, vap);
	va_end(vap);
	if (errno) {
		fputc(':', stderr);
		fputc(' ', stderr);
		fputs(strerror(errno), stderr);
	}
	fputc('\n', stderr);
	return;
}


static struct tr_proto_s*
open_tr(const char *fn)
{
	struct tr_proto_s *dr = NULL;
	struct stat st;
	ssize_t z;
	uint32_t n;
	int fd;

	if (UNLIKELY((fd = open(fn, O_RDONLY)) < 0)) {
		return NULL;
	} else if (UNLIKELY(read(fd, &n, sizeof(n)) < (ssize_t)sizeof(n))) {
		goto clo;
	} else if (UNLIKELY(!(n = be32toh(n)))) {
		/* not necessarily unsuccessful */
		goto clo;
	} else if (UNLIKELY(n > countof(tr))) {
		goto clo;
	} else if (UNLIKELY(fstat(fd, &st) < 0)) {
		goto clo;
	} else if (UNLIKELY(st.st_size < (3 * n + 1) * (ssize_t)sizeof(n))) {
		/* too small */
		goto clo;
	} else if (UNLIKELY((dr = malloc(st.st_size - sizeof(n))) == NULL)) {
		/* shame */
		goto clo;
	}
	/* we need to read everything */
	z = st.st_size - sizeof(dr->n);
	for (ssize_t nrd, of = 0;
	     z > 0 && (nrd = read(fd, (uint8_t*)dr->data + of, z)) > 0;
	     z -= nrd, of += nrd);
	if (UNLIKELY(z > 0)) {
	free:
		/* read probably fucked */
		free(dr);
		dr = NULL;
		goto clo;
	}
	/* should be max offset */
	z = st.st_size - (2U * n + 1U) * sizeof(dr->n);
	/* massage array, this is an all or nothing approach ... */
	dr->n = n;
	for (size_t i = 0U; i < n; i++) {
		dr->data[0 + i] = be32toh(dr->data[0 + i]);
		dr->data[n + i] = be32toh(dr->data[n + i]);
		if (UNLIKELY(dr->data[0 + i] >= countof(tr) ||
			     dr->data[n + i] >= z)) {
			goto free;
		}
	}
clo:
	close(fd);
	return dr;
}

static int
close_tr(struct tr_proto_s *dr)
{
	if (UNLIKELY(dr == NULL)) {
		return -1;
	}
	free(dr);
	return 0;
}

static int
install_tr(struct tr_proto_s *dr)
{
	char *of;

	if (UNLIKELY(dr == NULL)) {
		return -1;
	}
	of = (char*)(dr->data + (2U * dr->n));
	for (size_t i = 0U; i < dr->n; i++) {
		tr[dr->data[0 + i]] = of + dr->data[dr->n + i];
	}
	return 0;
}


/* printing */
static char outbuf[4U * BSZ];
static size_t outidx;

static int
flush(void)
{
	if (UNLIKELY(!outidx)) {
		return 0;
	}
	with (ssize_t nwr = write(STDOUT_FILENO, outbuf, outidx)) {
		if (UNLIKELY(nwr <= 0)) {
			return -1;
		}
		/* otherwise move stuff for future flushing */
		memmove(outbuf, outbuf + nwr, outidx - nwr);
		outidx -= nwr;
	}
	return 0;
}

static inline void
printc(const char x)
{
	if (UNLIKELY(outidx >= countof(outbuf))) {
		flush();
	}
	outbuf[outidx++] = x;
	return;
}

static inline void
print(const char *x)
{
	const size_t len = strlen(x);

	if (UNLIKELY(!len)) {
		return;
	} else if (UNLIKELY(outidx + len >= countof(outbuf))) {
		flush();
	}
	outbuf[outidx++] = x[0U];
	for (size_t j = 1U; j < len; j++) {
		outbuf[outidx++] = x[j];
	}
	return;
}


static size_t
transbuf(const uint_fast8_t *buf, size_t bsz)
{
	uint_fast32_t stash = 0U;
	ssize_t i = 0U;

	while (i < (ssize_t)bsz) {
		uint_fast32_t x = 0U;

		if (LIKELY(buf[i] < 0x80U)) {
			x = buf[i++];
		} else if (buf[i] < 0xc2U) {
			/* illegal utf8 */
			x = '?';
			i++;
		} else if (buf[i] < 0xe0U) {
			/* 110x xxxx 10xx xxxx */
			if (UNLIKELY(i + 1U >= (ssize_t)bsz)) {
				break;
			}

			x ^= buf[i + 0U] & 0b11111U;
			x <<= 6U;
			x ^= buf[i + 1U] & 0b111111U;

			i += 2;
		} else if (buf[i] < 0xf0U) {
			/* 1110 xxxx 10xx xxxx 10xx xxxx */
			if (UNLIKELY(i + 2U >= (ssize_t)bsz)) {
				break;
			}

			x ^= buf[i + 0U] & 0b1111U;
			x <<= 6U;
			x ^= buf[i + 1U] & 0b111111U;
			x <<= 6U;
			x ^= buf[i + 2U] & 0b111111U;

			i += 3;
		} else if (buf[i] < 0xf8U) {
			/* 1111 0xxx  10xx xxxx  10xx xxxx  10xx xxxx */
			if (UNLIKELY(i + 3U >= (ssize_t)bsz)) {
				break;
			}

			x ^= buf[i + 0U] & 0b111U;
			x <<= 6U;
			x ^= buf[i + 1U] & 0b111111U;
			x <<= 6U;
			x ^= buf[i + 2U] & 0b111111U;
			x <<= 6U;
			x ^= buf[i + 3U] & 0b111111U;

			i += 4;
		} else {
			x = '?';
			i++;
		}

		/* check stash */
		if (UNLIKELY(stash)) {
			size_t alt = 0U;
			uint32_t itr;

		rechk:
			itr = 0U;
			itr ^= (unsigned char)tr[stash][alt++];
			itr <<= 8U;
			itr ^= (unsigned char)tr[stash][alt++];
			itr <<= 8U;
			itr ^= (unsigned char)tr[stash][alt++];
			itr <<= 8U;
			itr ^= (unsigned char)tr[stash][alt++];

			if (itr == x) {
				/* bingo */
				print(tr[stash] + alt);
				stash = 0U;
				continue;
			}
			/* otherwise skip over string */
			while (tr[stash][(alt += 4U) - 1U]);
			/* now we're either on the last element
			 * or on the next candidate */
			if (!tr[stash][alt]) {
				goto rechk;
			}
			/* otherwise 'twas the last element, print him */
			print(tr[stash] + alt);
			stash = 0U;
		}

		if (LIKELY(x < 0x80U)) {
			printc(x);
			continue;
		} else if (UNLIKELY(x >= countof(tr) || tr[x] == NULL)) {
			printc('?');
			continue;
		} else if (UNLIKELY(!tr[x][0U])) {
			/* needs stashing */
			stash = x;
			continue;
		}
		/* otherwise print transliteration */
		print(tr[x]);
		continue;
	}

	(void)flush();
	return bsz - i;
}


static int
transfd(int fd)
{
	uint_fast8_t buf[BSZ];
	size_t of = 0U;
	ssize_t nrd;

	while ((nrd = read(fd, buf + of, sizeof(buf) - of)) > 0) {
		of = transbuf(buf, of + nrd);
		for (size_t i = 0U; i < of; i++) {
			buf[i] = buf[sizeof(buf) - of + i];
		}
	}
	fsync(STDOUT_FILENO);
	return 0;
}


#include "translit.yucc"

int
main(int argc, char *argv[])
{
	struct tr_proto_s **trxt = NULL;
	yuck_t argi[1U];
	int rc = 0;
	int fd;

	if (yuck_parse(argi, argc, argv)) {
		rc = 1;
		goto out;
	}

	if (argi->lang_nargs) {
		trxt = calloc(sizeof(*trxt), argi->lang_nargs);
	}
	/* open all transliteration extensions */
	for (size_t i = 0U; i < argi->lang_nargs; i++) {
		if ((trxt[i] = open_tr(argi->lang_args[i])) == NULL) {
			error("\
Error: cannot load language file `%s'", argi->lang_args[i]);
			rc = 2;
			continue;
		}
	}
	/* and install them */
	for (size_t i = 0U; i < argi->lang_nargs; i++) {
		if (trxt[i]) {
			install_tr(trxt[i]);
		}
	}

	if (!argi->nargs) {
		fd = STDIN_FILENO;
		goto translit;
	}
	for (size_t i = 0U; i < argi->nargs; i++) {
		if (UNLIKELY((fd = open(argi->args[i], O_RDONLY)) < 0)) {
			error("Error: cannot open file `%s'", argi->args[i]);
			rc = 1;
			continue;
		}

	translit:
		/* turn asciified buffer into utf8 */
		if (UNLIKELY(transfd(fd) < 0)) {
			error("Error: cannot process file `%s'", argi->args[i]);
			rc = 1;
		}

		close(fd);
	}

	for (size_t i = 0U; i < argi->lang_nargs; i++) {
		(void)close_tr(trxt[i]);
	}

out:
	yuck_free(argi);
	return rc;
}

/* translit.c ends here */
