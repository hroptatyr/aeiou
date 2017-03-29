/*** aeiou.c -- ascii<->unicode converter/normaliser
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

static inline char
_hexc(const uint_fast8_t c)
{
	if (LIKELY(c < 10)) {
		return (char)(c ^ '0');
	}
	/* no check for the upper bound of c */
	return (char)(c + 'W');
}

static uint_fast32_t
_chex(const uint_fast8_t c)
{
	if (LIKELY((c ^ '0') < 10)) {
		return c ^ '0';
	} else if ((c | 0x20) - 'W') {
		return (c | 0x20) - 'W';
	}
	/* no error code */
	return 0U;
}


static size_t
aeebuf(const uint_fast8_t *buf, size_t bsz)
{
	char out[4U * BSZ];
	ssize_t i = 0U;
	size_t n = 0U;

	while (i < (ssize_t)bsz) {
		/* utf8 seq ranges */
		static const uint_fast32_t lohi[4U] = {
			16U * (1U << (4U - 1U)),
			16U * (1U << (8U - 1U)),
			16U * (1U << (13U - 1U)),
			16U * (1U << (16U - 1U)) + 16U * (1U << (13U - 1U)),
		};
		uint_fast32_t x = 0U;

		if (LIKELY(buf[i] != '\\')) {
		literal:
			out[n++] = buf[i++];
		} else if (i + 1U >= (ssize_t)bsz) {
			/* grrr just when I got excited ... */
			break;
		} else if ((buf[i + 1] | 0x20U) != 'u') {
			/* nope, not \u nor \U, something else */
			goto literal;
		} else if (i + 5U >= (ssize_t)bsz) {
			/* better ask for more bytes then */
			break;
		} else if (buf[i + 1] == 'u') {
			x ^= _chex(buf[i + 2U]);
			x <<= 4U;
			x ^= _chex(buf[i + 3U]);
			x <<= 4U;
			x ^= _chex(buf[i + 4U]);
			x <<= 4U;
			x ^= _chex(buf[i + 5U]);

			i += 6U;
			goto pr_mb;
		} else if (i + 9U >= (ssize_t)bsz) {
			break;
		} else /*if (buf[i + 1] == 'U')*/ {
			x ^= _chex(buf[i + 2U]);
			x <<= 4U;
			x ^= _chex(buf[i + 3U]);
			x <<= 4U;
			x ^= _chex(buf[i + 4U]);
			x <<= 4U;
			x ^= _chex(buf[i + 5U]);
			x <<= 4U;
			x ^= _chex(buf[i + 6U]);
			x <<= 4U;
			x ^= _chex(buf[i + 7U]);
			x <<= 4U;
			x ^= _chex(buf[i + 8U]);
			x <<= 4U;
			x ^= _chex(buf[i + 9U]);

			i += 10U;
			goto pr_mb;
		}
		continue;
	pr_mb:
		if (x < lohi[0U]) {
			out[n++] = x;
		} else if (x < lohi[1U]) {
			/* 110x xxxx  10xx xxxx */
			out[n++] = 0xc0U ^ (x >> 6U);
			out[n++] = 0x80U ^ (x & 0b111111U);
		} else if (x < lohi[2U]) {
			/* 1110 xxxx  10xx xxxx  10xx xxxx */
			out[n++] = 0xe0U | (x >> 12U);
			out[n++] = 0x80U | ((x >> 6U) & 0b111111U);
			out[n++] = 0x80U | (x & 0b111111U);
		} else if (x < lohi[3U]) {
			/* 1111 0xxx  10xx xxxx  10xx xxxx  10xx xxxx*/
			out[n++] = 0xf0U | (x >> 18U);
			out[n++] = 0x80U | ((x >> 12U) & 0b111111U);
			out[n++] = 0x80U | ((x >> 6U) & 0b111111U);
			out[n++] = 0x80U | (x & 0b111111U);
		}
	}

	write(STDOUT_FILENO, out, n);
	return bsz - i;
}

static size_t
aedbuf(const uint_fast8_t *buf, size_t bsz)
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

			out[n++] = '\\';
			out[n++] = 'u';

			x ^= buf[i + 0U] & 0b11111U;
			x <<= 6U;
			x ^= buf[i + 1U] & 0b111111U;

			i += 2;
			goto pr_u;
		} else if (buf[i] < 0xf0U) {
			/* 1110 xxxx 10xx xxxx 10xx xxxx */
			if (UNLIKELY(i + 2U >= (ssize_t)bsz)) {
				break;
			}

			out[n++] = '\\';
			out[n++] = 'u';

			x ^= buf[i + 0U] & 0b1111U;
			x <<= 6U;
			x ^= buf[i + 1U] & 0b111111U;
			x <<= 6U;
			x ^= buf[i + 2U] & 0b111111U;

			i += 3;
			goto pr_u;
		} else if (buf[i] < 0xf8U) {
			/* 1111 0xxx  10xx xxxx  10xx xxxx  10xx xxxx */
			if (UNLIKELY(i + 3U >= (ssize_t)bsz)) {
				break;
			}

			out[n++] = '\\';
			out[n++] = 'U';

			x ^= buf[i + 0U] & 0b111U;
			x <<= 6U;
			x ^= buf[i + 1U] & 0b111111U;
			x <<= 6U;
			x ^= buf[i + 2U] & 0b111111U;
			x <<= 6U;
			x ^= buf[i + 3U] & 0b111111U;

			i += 4;
			goto pr_U;
		} else {
			out[n++] = '?';
			i++;
		}
		continue;
	pr_U:
		out[n++] = _hexc(x >> 28U & 0xfU);
		out[n++] = _hexc(x >> 24U & 0xfU);
		out[n++] = _hexc(x >> 20U & 0xfU);
		out[n++] = _hexc(x >> 16U & 0xfU);
	pr_u:
		out[n++] = _hexc(x >> 12U & 0xfU);
		out[n++] = _hexc(x >> 8U & 0xfU);
		out[n++] = _hexc(x >> 4U & 0xfU);
		out[n++] = _hexc(x >> 0U & 0xfU);
	}

	write(STDOUT_FILENO, out, n);
	return bsz - i;
}


static int
aedfd(int fd)
{
	uint_fast8_t buf[BSZ];
	size_t of = 0U;
	ssize_t nrd;

	while ((nrd = read(fd, buf + of, sizeof(buf) - of)) > 0) {
		of = aedbuf(buf, of + nrd);
		for (size_t i = 0U; i < of; i++) {
			buf[i] = buf[sizeof(buf) - of + i];
		}
	}
	fsync(STDOUT_FILENO);
	return 0;
}

static int
aeefd(int fd)
{
	uint_fast8_t buf[BSZ];
	size_t of = 0U;
	ssize_t nrd;

	while ((nrd = read(fd, buf + of, sizeof(buf) - of)) > 0) {
		of = aeebuf(buf, of + nrd);
		for (size_t i = 0U; i < of; i++) {
			buf[i] = buf[sizeof(buf) - of + i];
		}
	}
	fsync(STDOUT_FILENO);
	return 0;
}


#include "aeiou.yucc"

int
main(int argc, char *argv[])
{
	yuck_t argi[1U];
	size_t i = 0U;
	int rc = 0;
	int fd;

	if (yuck_parse(argi, argc, argv)) {
		rc = 1;
		goto out;
	}

	if (!argi->nargs) {
		fd = STDIN_FILENO;
		goto option;
	}
	for (i = 0U; i < argi->nargs; i++) {
		if (UNLIKELY((fd = open(argi->args[i], O_RDONLY)) < 0)) {
			error("Error: cannot open file `%s'", argi->args[i]);
			rc = 1;
			continue;
		}

	option:
		if (argi->decode_flag) {
			goto decode;
		}
		goto encode;

	encode:
		/* turn asciified buffer into utf8 */
		if (UNLIKELY(aeefd(fd) < 0)) {
			error("Error: cannot process file `%s'", argi->args[i]);
			rc = 1;
		}
		goto close;

	decode:
		/* turn utf8 buffer into ascii */
		if (UNLIKELY(aedfd(fd) < 0)) {
			error("Error: cannot process file `%s'", argi->args[i]);
			rc = 1;
		}
		goto close;

	close:
		close(fd);
	}

out:
	yuck_free(argi);
	return rc;
}

/* aeiou.c ends here */
