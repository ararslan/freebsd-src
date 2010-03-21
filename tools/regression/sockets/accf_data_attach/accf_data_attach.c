/*-
 * Copyright (c) 2004 Robert N. M. Watson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/tools/regression/sockets/accf_data_attach/accf_data_attach.c,v 1.4.24.1 2010/02/10 00:26:20 kensmith Exp $
 */

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define	ACCF_NAME	"dataready"

/*
 * A number of small tests to confirm that attaching ACCF_DATA accept filters
 * to inet4 ports works as expected.  We test:
 *
 * - That no accept filter is attached on a newly created socket.
 * - That bind() has no affect on the accept filter state.
 * - That we can't attach an accept filter to a socket that isn't in the
 *   listen state.
 * - That after we fail to attach the filter, querying the kernel shows no
 *   filter attached.
 * - That we can attach an accept filter to a socket that is in the listen
 *   state.
 * - That once an accept filter is attached, we can query to make sure it is
 *   attached.
 * - That once an accept filter is attached, we can remove it and query to
 *   make sure it is removed.
 */
int
main(int argc, char *argv[])
{
	struct accept_filter_arg afa;
	struct sockaddr_in sin;
	socklen_t len;
	int lso, ret;

	printf("1..11\n");

	/*
	 * Step 0. Open socket().
	 */
	lso = socket(PF_INET, SOCK_STREAM, 0);
	if (lso == -1)
		errx(-1, "not ok 1 - socket: %s", strerror(errno));
	printf("ok 1 - socket\n");

	/*
	 * Step 1. After socket().  Should return EINVAL, since no accept
	 * filter should be attached.
	 */
	bzero(&afa, sizeof(afa));
	len = sizeof(afa);
	ret = getsockopt(lso, SOL_SOCKET, SO_ACCEPTFILTER, &afa, &len);
	if (ret != -1)
		errx(-1, "not ok 2 - getsockopt() after socket() succeeded");
	if (errno != EINVAL)
		errx(-1, "not ok 2 - getsockopt() after socket() failed with "
		    "%d (%s)", errno, strerror(errno));
	printf("ok 2 - getsockopt\n");

	/*
	 * Step 2. Bind().  Ideally this will succeed.
	 */
	bzero(&sin, sizeof(sin));
	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8080);
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (bind(lso, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		errx(-1, "not ok 3 - bind %s", strerror(errno));
	printf("ok 3 - bind\n");

	/*
	 * Step 3: After bind().  getsockopt() should return EINVAL, since no
	 *  accept filter should be attached.
	 */
	len = sizeof(afa);
	ret = getsockopt(lso, SOL_SOCKET, SO_ACCEPTFILTER, &afa, &len);
	if (ret != -1)
		errx(-1, "not ok 4 - getsockopt() after bind() succeeded");
	if (errno != EINVAL)
		errx(-1, "not ok 4 -  getsockopt() after bind() failed with %d (%s)",
		    errno, strerror(errno));
	printf("ok 4 - getsockopt\n");

	/*
	 * Step 4: Setsockopt() before listen().  Should fail, since it's not
	 * yet a listen() socket.
	 */
	bzero(&afa, sizeof(afa));
	strcpy(afa.af_name, ACCF_NAME);
	ret = setsockopt(lso, SOL_SOCKET, SO_ACCEPTFILTER, &afa, sizeof(afa));
	if (ret == 0)
		errx(-1, "not ok 5 - setsockopt() before listen() succeeded");
	printf("ok 5 - setsockopt\n");

	/*
	 * Step 5: Getsockopt() after pre-listen() setsockopt().  Should
	 * fail with EINVAL, since setsockopt() should have failed.
	 */
	len = sizeof(afa);
	ret = getsockopt(lso, SOL_SOCKET, SO_ACCEPTFILTER, &afa, &len);
	if (ret == 0)
		errx(-1, "not ok 6 - getsockopt() after pre-listen() setsockopt() "
		    "succeeded");
	if (errno != EINVAL)
		errx(-1, "not ok 6 - pre-listen() getsockopt() failed with %d (%s)",
		    errno, strerror(errno));
	printf("ok 6 - getsockopt\n");

	/*
	 * Step 6: listen().
	 */
	if (listen(lso, -1) < 0)
		errx(-1, "not ok 7 - listen: %s", strerror(errno));
	printf("ok 7 - listen\n");

	/*
	 * Step 7: Getsockopt() after listen().  Should fail with EINVAL,
	 * since we have not installed accept filter yet.
	 */
	len = sizeof(afa);
	ret = getsockopt(lso, SOL_SOCKET, SO_ACCEPTFILTER, &afa, &len);
	if (ret == 0)
		errx(-1, "not ok 8 - getsockopt() after listen() but before "
		    "setsockopt() succeeded");
	if (errno != EINVAL)
		errx(-1, "not ok 8 - getsockopt() after listen() but before "
		    "setsockopt() failed with %d (%s)", errno, strerror(errno));
	printf("ok 8 - getsockopt\n");

	/*
	 * Step 8: After listen().  This call to setsockopt() should succeed.
	 */
	bzero(&afa, sizeof(afa));
	strcpy(afa.af_name, ACCF_NAME);
	ret = setsockopt(lso, SOL_SOCKET, SO_ACCEPTFILTER, &afa, sizeof(afa));
	if (ret != 0)
		errx(-1, "not ok 9 - setsockopt() after listen() failed with %d "
		    "(%s)", errno, strerror(errno));
	if (len != sizeof(afa))
		errx(-1, "not ok 9 - setsockopt() after listen() returned wrong "
		    "size (%d vs expected %d)", len, sizeof(afa));
	printf("ok 9 - setsockopt\n");

	/*
	 * Step 9: After setsockopt().  Should succeed and identify
	 * ACCF_NAME.
	 */
	bzero(&afa, sizeof(afa));
	len = sizeof(afa);
	ret = getsockopt(lso, SOL_SOCKET, SO_ACCEPTFILTER, &afa, &len);
	if (ret != 0)
		errx(-1, "not ok 10 - getsockopt() after listen() setsockopt() "
		    "failed with %d (%s)", errno, strerror(errno));
	if (len != sizeof(afa))
		errx(-1, "not ok 10 - getsockopt() after setsockopet()  after "
		    "listen() returned wrong size (got %d expected %d)", len,
		    sizeof(afa));
	if (strcmp(afa.af_name, ACCF_NAME) != 0)
		errx(-1, "not ok 10 - getsockopt() after setsockopt() after "
		    "listen() mismatch (got %s expected %s)", afa.af_name,
		    ACCF_NAME);
	printf("ok 10 - getsockopt\n");

	/*
	 * Step 10: Remove accept filter.  After removing the accept filter
	 * getsockopt() should fail with EINVAL.
	 */
	ret = setsockopt(lso, SOL_SOCKET, SO_ACCEPTFILTER, NULL, 0);
	if (ret != 0)
		errx(-1, "not ok 11 - setsockopt() after listen() "
		    "failed with %d (%s)", errno, strerror(errno));
	bzero(&afa, sizeof(afa));
	len = sizeof(afa);
	ret = getsockopt(lso, SOL_SOCKET, SO_ACCEPTFILTER, &afa, &len);
	if (ret == 0)
		errx(-1, "not ok 11 - getsockopt() after removing "
		    "the accept filter returns valid accept filter %s",
		    afa.af_name);
	if (errno != EINVAL)
		errx(-1, "not ok 11 - getsockopt() after removing the accept"
		    "filter failed with %d (%s)", errno, strerror(errno));
	printf("ok 11 - setsockopt\n");

	close(lso);
	return (0);
}
