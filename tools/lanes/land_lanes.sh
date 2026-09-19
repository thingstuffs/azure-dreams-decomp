#!/bin/bash
# Land lane wins, then the cascade, tidy, T2 and ONE gate:  bash tools/lanes/land_lanes.sh <tag> <lane>...
#   A lane output (work/native_lane/<lane>/out/<container>/<name>.c) lands only when its base is current (the
#   .base_sha next to it), its pins fell and no scaffolding kind grew (ASM_*, while (0), __asm__, volatile);
#   it goes through apply_candidates.py as transform lane_<lane>. CELLS=<jsonl> passes cell switches
#   (apply_candidates --cells). EXTRA_T adds generators to the cascade. The caller reviews and commits.
#   Run ONLY after every lane has exited (verify.py shares build_ovl with the gate), and from its own command
#   line: the guards use pgrep -f, which also matches a wrapper shell whose command line ran sweep.py.
# Moved from the session scratchpad (land20.sh ... land25.sh) in round 24.
set -u
cd "$(dirname "$0")/../.."
# one landing at a time: two concurrent landings (an orchestrator's and a hand-queued one) both rewrite src/ and
# gate; the second waits here on a cross-process lock (2026-09-19)
mkdir -p build_ovl/work; exec 9>build_ovl/work/land.lock; flock 9
TAG=${1:?tag}; shift
LANES="$*"; [ -n "$LANES" ] || { echo "usage: land_lanes.sh <tag> <lane>..."; exit 1; }
if pgrep -f "[c]odex exec" >/dev/null; then echo "a codex lane is running: wait for it"; exit 1; fi
if pgrep -f "[s]weep.py " >/dev/null; then echo "a sweep is running: wait for it"; exit 1; fi
STAGE=$(mktemp -d -t "land_${TAG}_XXXX")
echo "== lane wins (staged in $STAGE)"
python3 - "$STAGE" $LANES <<'EOF'
import sys, glob, os, re, shutil, hashlib, collections
sys.path.insert(0, "tools")
from pin_census import sites_of
stage, lanes = sys.argv[1], sys.argv[2:]
bad = re.compile(r"ASM_[A-Z0-9_]+(?=\()|while\s*\(\s*0\s*\)|__asm__|\bvolatile\b")
kinds = lambda t: collections.Counter(m.group(0).replace(" ", "") for m in bad.finditer(re.sub(r"/\*.*?\*/", "", t, flags=re.S)))
for lane in lanes:
    for f in sorted(glob.glob("work/native_lane/%s/out/*/*.c" % lane)):
        rid = f.split("/out/")[1][:-2]; cand = open(f).read(); cur = open("src/%s.c" % rid).read()
        base = open(f + ".base_sha").read().strip() if os.path.exists(f + ".base_sha") else ""
        kc, ku = kinds(cand), kinds(cur); grew = [k for k in kc if kc[k] > ku[k]]
        if hashlib.sha256(cur.encode()).hexdigest() != base:
            print("skip", lane, rid, "stale base"); continue
        if len(sites_of(cand)) >= len(sites_of(cur)) or grew:
            print("skip", lane, rid, "pins", len(sites_of(cur)), "->", len(sites_of(cand)), "grew", grew); continue
        d = "%s/%s/%s" % (stage, lane, rid.split("/")[0]); os.makedirs(d, exist_ok=True)
        shutil.copy(f, d); shutil.copy(f + ".base_sha", d)
        print("keep", lane, rid, "pins", len(sites_of(cur)), "->", len(sites_of(cand)))
EOF
for lane in $LANES; do
  C=""; [ -n "${CELLS:-}" ] && C="--cells $CELLS"
  [ -d $STAGE/$lane ] && python3 tools/apply_candidates.py $STAGE/$lane --transform lane_$lane --workers 2 $C 2>&1 | tail -1
done
echo "== cascade: the cheap generators over every changed row until a pass applies nothing"
for pass in 1 2 3 4; do
  IDS=$(git diff --name-only -- src | sed -E 's#^src/##; s#\.c$##' | paste -sd,)
  [ -z "$IDS" ] && break
  n=0
  for T in t36_paramwidth t37_localwidth t37b_localwidth_keep t38_unstage t39_signbit t41_gotoloop t41b_gotoloop_while \
           t41c_gotoloop_greedy t42_sinkcopy t44_doloop_greedy t48_gotoreturn t49_looptest t16_absidiom t16b_fieldabs \
           t51_sched_order t53_reg_state t53k_keep t54_pagebase t57_keepafterstore t57b_keepafternext t59_offsetsym t63_memdep t66_sameregmerge t69_prologue t71_updateaftercall t72_stmtperm t38b_unstage_run t74_multiset t76_arity \
           ${EXTRA_T:-} t2_pins; do
    P=""; case $T in t53_reg_state|t53k_keep) P="--processes";; esac   # Python-bound; t54 stays threaded (cell switches)
    out=$(python3 tools/sweep.py $T --only "$IDS" --workers 8 $P 2>&1 | tail -1); echo "pass $pass $T: $out"
    a=$(echo "$out" | grep -o "'applied': [0-9]*" | grep -o "[0-9]*$"); n=$((n + ${a:-0}))
  done
  echo "pass $pass applied $n"; [ $n -eq 0 ] && break
done
echo "== tidy empty NON_MATCHING blocks"
python3 - <<'EOF'
import glob, sys, re
sys.path.insert(0, "tools")
from pin_sites import EMPTY_NM_RE
SHELL = re.compile(r"^[ \t]*#[ \t]*if(?:n?def)?[ \t]+NON_MATCHING[^\n]*\n(?:[ \t]*\n)*(?:[ \t]*#[ \t]*else[^\n]*\n(?:[ \t]*\n)*)?[ \t]*#[ \t]*endif[^\n]*\n", re.M)
n = 0
for f in glob.glob("src/*/*.c"):
    t = open(f).read(); u = SHELL.sub("", EMPTY_NM_RE.sub("", t))
    if u != t: open(f, "w").write(u); n += 1
print("tidied", n, "files")
EOF
IDS=$(git diff --name-only -- src | sed -E 's#^src/##; s#\.c$##' | paste -sd,)
if [ -n "$IDS" ]; then
  echo "== t2 on $(echo $IDS | tr , '\n' | wc -l) changed rows"; python3 tools/sweep.py t2_pins --only "$IDS" --workers 6 2>&1 | tail -1
  echo "== gate"; bash tools/build/mk_ovl_root.sh && python3 tools/build/gate_all.py --workers 8 && bash tools/build/build_slus.sh -j 8
  echo "GATE_RC=$?"
  python3 tools/levels.py >/dev/null; python3 tools/status.py >/dev/null; grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md
fi
rm -rf "$STAGE"
echo "== done"
