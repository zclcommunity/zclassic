#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

ZCLASSICD=${ZCLASSICD:-$SRCDIR/zclassicd}
ZCLASSICCLI=${ZCLASSICCLI:-$SRCDIR/zclassic-cli}
ZCLASSICTX=${ZCLASSICTX:-$SRCDIR/zclassic-tx}

[ ! -x $ZCLASSICD ] && echo "$ZCLASSICD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
ZCLVERSTR=$($ZCLASSICCLI --version | head -n1 | awk '{ print $NF }')
ZCLVER=$(echo $ZCLVERSTR | awk -F- '{ OFS="-"; NF--; print $0; }')
ZCLCOMMIT=$(echo $ZCLVERSTR | awk -F- '{ print $NF }')

# Create a footer file with copyright content.
# This gets autodetected fine for zclassicd if --version-string is not set,
# but has different outcomes for zclassic-cli.
echo "[COPYRIGHT]" > footer.h2m
$ZCLASSICD --version | sed -n '1!p' >> footer.h2m

for cmd in $ZCLASSICD $ZCLASSICCLI $ZCLASSICTX; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=$ZCLVER --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-$ZCLCOMMIT//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
