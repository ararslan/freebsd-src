#!/bin/sh
# $FreeBSD: src/tools/regression/fstest/tests/chown/04.t,v 1.1.12.1 2010/02/10 00:26:20 kensmith Exp $

desc="chown returns ENOENT if the named file does not exist"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..4"

n0=`namegen`
n1=`namegen`

expect 0 mkdir ${n0} 0755
expect ENOENT chown ${n0}/${n1}/test 65534 65534
expect ENOENT chown ${n0}/${n1} 65534 65534
expect 0 rmdir ${n0}
