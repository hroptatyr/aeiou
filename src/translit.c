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
#include <errno.h>
#include <fcntl.h>
#include <assert.h>
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


static size_t
transbuf(const uint_fast8_t *buf, size_t bsz)
{
	char out[4U * BSZ];
	ssize_t i = 0U;
	size_t n = 0U;

	while (i < (ssize_t)bsz) {
		uint_fast32_t x = 0U;

		if (LIKELY(buf[i] < 0x80U)) {
			out[n++] = buf[i++];
		} else if (buf[i] < 0xc2U) {
			/* illegal utf8 */
			out[n++] = '?';
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
			goto tr;
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
			goto tr;
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
			goto tr;
		} else {
			out[n++] = '?';
			i++;
		}
		continue;
	tr:
		if (UNLIKELY(tr[x] == NULL || x >= countof(tr))) {
			out[n++] = '?';
			continue;
		}
		/* otherwise print transliteration */
		out[n++] = tr[x][0U];
		for (size_t j = 1U; tr[x][j]; j++) {
			out[n++] = tr[x][j];
		}
		continue;
	}

	write(STDOUT_FILENO, out, n);
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
	yuck_t argi[1U];
	int rc = 0;
	int fd;

	if (yuck_parse(argi, argc, argv)) {
		rc = 1;
		goto out;
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

out:
	yuck_free(argi);
	return rc;
}

/* translit.c ends here */
