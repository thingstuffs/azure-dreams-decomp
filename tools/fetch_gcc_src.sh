#!/bin/bash
# GNU gcc sources for every stock cell, for lanes that read the passes (sched.c, combine.c, cse.c,
# local-alloc.c, global.c, reorg.c, config/mips/mips.md ...). Idempotent; rerun after a fresh clone.
# Output: toolchain/gcc-src/<cell version>/ (gitignored with toolchain/): only the compiler's own
# sources, top-level *.c *.h *.def *.md and config/mips/. Tarballs stay in toolchain/gcc-src/tarballs/.
# 2.7.2-cdk has no public source (use 2.7.2); 2.91.66 is egcs-1.1.2.
set -u
cd "$(dirname "$0")/.."
D=toolchain/gcc-src
mkdir -p $D/tarballs

fetch() {  # version, then "url root" pairs tried in order
  local v=$1; shift
  if [ -d $D/$v ]; then echo "$v: present"; return; fi
  while [ $# -ge 2 ]; do
    local url=$1 root=$2 t=$D/tarballs/$v-$(basename $1); shift 2
    [ -s $t ] || curl -sfL --max-time 600 -o $t "$url" || { rm -f $t; echo "$v: no $url"; continue; }
    rm -rf $D/$v.tmp && mkdir -p $D/$v.tmp
    tar -xf $t -C $D/$v.tmp --wildcards --no-wildcards-match-slash \
        "$root/*.c" "$root/*.h" "$root/*.def" "$root/*.md" "$root/config/mips/*" 2>/dev/null
    if [ -f $D/$v.tmp/$root/combine.c ]; then
      mv $D/$v.tmp/$root $D/$v && rm -rf $D/$v.tmp
      echo "$v: $(ls $D/$v | wc -l) files, $(du -sh $D/$v | cut -f1) from $url"
      return
    fi
    rm -rf $D/$v.tmp; echo "$v: $url did not hold $root/combine.c"
  done
  echo "$v: FAILED"
}

G=https://ftp.gnu.org/gnu/gcc
O=https://ftp.gnu.org/old-gnu/gcc
M=https://github.com/gcc-mirror/gcc/archive/refs/tags/releases
for v in 2.6.3 2.7.2 2.8.0 2.8.1; do        # 2.6.3 exists only as .tar.bz2
  fetch $v $G/gcc-$v.tar.gz gcc-$v $O/gcc-$v.tar.gz gcc-$v $O/gcc-$v.tar.bz2 gcc-$v \
        https://gcc.gnu.org/pub/gcc/old-releases/gcc-2/gcc-$v.tar.bz2 gcc-$v $M/gcc-$v.tar.gz gcc-releases-gcc-$v/gcc
done
fetch 2.95.2 $G/gcc-2.95.2.tar.gz gcc-2.95.2/gcc $M/gcc-2.95.2.tar.gz gcc-releases-gcc-2.95.2/gcc
fetch 2.91.66 https://gcc.gnu.org/pub/gcc/old-releases/egcs/egcs-1.1.2.tar.bz2 egcs-1.1.2/gcc \
              $M/egcs_1_1_2_release.tar.gz gcc-releases-egcs_1_1_2_release/gcc
