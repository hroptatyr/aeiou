#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tr_proto.h"
#include "boobs.h"
#include "nifty.h"

int
main(void)
{
	char *x[0x10000U] = {
#include TRFILE
	};
	/* disk-representation */
	struct tr_proto_s *dr;
	size_t of = 0U;
	size_t n = 0U;
	size_t z;

	/* count non-nils */
	for (size_t i = 0U; i < countof(x); i++) {
		n += (x[i] != NULL);
	}
	/* try and initialise */
	dr = malloc((z = 8U * n * sizeof(dr->n)));
	memset(dr, 0, z);
	/* fill the proto */
	for (size_t i = 0U, j = 0U; i < countof(x); i++) {
		if (x[i]) {
			const size_t len = strlen(x[i]);

			/* write entry point */
			dr->data[j] = htobe32(i);

			/* write offset */
			dr->data[n + j] = htobe32(of * sizeof(dr->n));

			/* write string data */
			if (UNLIKELY(2U * n + of + len + 1U > z)) {
				/* resize */
				z *= 2U;
				dr = realloc(dr, z);
				memset((char*)dr + z / 2U, 0, z / 2U);
			}
			memcpy(dr->data + 2U * n + of, x[i], len);
			of += len / sizeof(dr->n) + 1U;
			j++;
		}
	}
	/* make sure we won't forget about N */
	dr->n = htobe32(n);

	/* write to file */
	fwrite(dr, sizeof(dr->n), 2U * n + 1U + of, stdout);

	free(dr);
	return 0;
}

/* translcc.c ends here */
