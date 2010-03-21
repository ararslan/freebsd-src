#!/bin/sh
# $FreeBSD: src/tools/regression/msdosfs/msdosfstest-5.sh,v 1.1.12.1 2010/02/10 00:26:20 kensmith Exp $
# A really simple script to create a swap-backed msdosfs filesystem, then
# test to see if msdosfs_conv.c rev 1.45[2] works properly.
# Note that this is a requisite condition but far away from sufficient condition.
# You must check file system by "dir /x" on MS Windows.

mkdir /tmp/msdosfstest
mdconfig -a -t swap -s 128m -u 10
bsdlabel -w md10 auto
newfs_msdos -F 16 -b 8192 /dev/md10a
mount_msdosfs -L ja_JP.eucJP -D CP932 -l /dev/md10a /tmp/msdosfstest
# touch /tmp/msdosfstest/U+FF71 (HALFWIDTH KATAKANA LETTER A)
touch /tmp/msdosfstest/��
if [ $? -eq 0 ]; then
	umount /tmp/msdosfstest
	mount_msdosfs -L ja_JP.eucJP -D CP932 -s /dev/md10a /tmp/msdosfstest
	ls /tmp/msdosfstest/��
	if [ $? -eq 0 ]; then
		echo "ok 5 (pass stage 1/2)"
		umount /tmp/msdosfstest
		mount_msdosfs -L uk_UA.KOI8-U -D CP866 -l /dev/md10a /tmp/msdosfstest
		# ls /tmp/msdosfstest/0xb1 (MEDIUM SHADE)
		ls /tmp/msdosfstest/�
		if [ $? -ne 0 ]; then
			# assume that U+FF71 was recorded with long name
			echo "ok 5 (pass stage 2/2)"
		else
			# only 0xb1 was found (doesn't have long name)
			echo "not ok 5"
		fi
	else
		echo "not ok 5"
	fi
else
	echo "not ok 5"
fi
umount /tmp/msdosfstest
mdconfig -d -u 10
rmdir /tmp/msdosfstest
