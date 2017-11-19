/* $Id$ */
/*
 * Copyright (c) 2017 Michael Graves
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <kcgi.h>
#include <kcgihtml.h>

int
main(void)
{
	struct kreq	 r;
	enum kcgi_err	 er;
	char 		*addr = NULL;
	size_t		i;

	/* Set up our main HTTP context. */
	er = khttp_parse(&r, NULL, 0, NULL, 0, 0);

	if (KCGI_OK != er) {
		fprintf(stderr, "Terminate: parse error: %d\n", er);
		khttp_free(&r);
		return(EXIT_FAILURE);
	}
	if (r.reqsz > 0) {
		for (i=0;i<r.reqsz && addr==NULL;i++) {
			if (strcasecmp("X-Forwarded-For",r.reqs[i].key) == 0)
				addr = r.reqs[i].val;
		}
	}
	if (addr == NULL) 
		addr = r.remote;

	khttp_head(&r, kresps[KRESP_STATUS], "%s", khttps[KHTTP_200]);
	khttp_head(&r, kresps[KRESP_CONTENT_TYPE], "%s", kmimetypes[KMIME_TEXT_PLAIN]);
	khttp_head(&r, kresps[KRESP_CACHE_CONTROL], "%s", "no-cache, no-store, must-revalidate");
	khttp_head(&r, kresps[KRESP_EXPIRES], "%s", "0");
	khttp_head(&r, kresps[KRESP_PRAGMA], "%s", "no-cache");
	khttp_body(&r);
	khttp_puts(&r, addr);
	khttp_free(&r);
	return(EXIT_SUCCESS);
}

