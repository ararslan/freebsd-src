#!/bin/sh
#
# $FreeBSD: src/release/scripts/proflibs-install.sh,v 1.6.12.1 2010/02/10 00:26:20 kensmith Exp $
#

if [ "`id -u`" != "0" ]; then
	echo "Sorry, this must be done as root."
	exit 1
fi
cat proflibs.?? | tar --unlink -xpzf - -C ${DESTDIR:-/}
exit 0
