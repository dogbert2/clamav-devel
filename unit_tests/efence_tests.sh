#!/bin/sh
# Run under electric-fence
if test -z "$LIBEFENCE"; then
	for i in /usr/lib/libefence.so /usr/local/lib/libefence.so /opt/csw/lib/libefence.so; do
		if test -f "$i"; then
			LIBEFENCE="$i"
			break;
		fi
	done
fi
test -f "$LIBEFENCE" || { echo "*** electric-fence not found, skipping test"; exit 77;}

EF_DISABLE_BANNER=1
EF_FREE_WIPES=1
LIBPRELOAD="$LIBEFENCE"
export EF_FREE_WIPES LIBPRELOAD EF_DISABLE_BANNER
VALGRIND=`which ${VALGRIND-valgrind}`
if test ! -n "$VALGRIND" || test ! -x "$VALGRIND"; then
	# run check_clamav under efence only if we don't have valgrind installed
	echo "--- Running check_clamav under electric-fence"
	CK_FORK=no ../libtool --mode=execute $abs_srcdir/preload_run.sh ./check_clamav
	if test ! $?; then
		echo "*** Electric-fence has detected errors"
		exit 1
	fi
fi
# we don't run clamd under electric-fence, it always crashes in free(),
# probably doesn't work well with libpthread.
echo "--- running clamscan under electric-fence to detect overruns"
CLAMSCAN_WRAPPER=$abs_srcdir/preload_run.sh $abs_srcdir/check_clamscan.sh
if test ! $?; then
	echo "*** Electric-fence has detected errors"
	exit 2
fi
EF_PROTECT_BELOW=1
export EF_PROTECT_BELOW
echo "--- running clamscan under electric-fence to detect underruns"
CLAMSCAN_WRAPPER=$abs_srcdir/preload_run.sh $abs_srcdir/check_clamscan.sh
if test ! $?; then
	echo "*** Electric-fence has detected errors"
	exit 3
fi
