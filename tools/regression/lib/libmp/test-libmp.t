#!/bin/sh
# $FreeBSD: src/tools/regression/lib/libmp/test-libmp.t,v 1.1.12.1 2010/02/10 00:26:20 kensmith Exp $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
