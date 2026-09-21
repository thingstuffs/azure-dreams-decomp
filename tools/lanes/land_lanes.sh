#!/bin/bash
# Land lane wins, then the cascade, tidy, T2 and ONE gate:  bash tools/lanes/land_lanes.sh <tag> <lane>...
#   A lane output (work/native_lane/<lane>/out/<container>/<name>.c) lands only when its base is current (the
#   .base_sha next to it), its pins fell and no scaffolding kind grew (ASM_*, while (0), __asm__, volatile);
#   it goes through apply_candidates.py as transform lane_<lane>. CELLS=<jsonl> passes cell switches
#   (apply_candidates --cells). EXTRA_T adds generators to the cascade. The caller reviews and commits.
#   Run ONLY after every lane has exited (verify.py shares build_ovl with the gate), and from its own command
#   line: the guards use pgrep -f, which also matches a wrapper shell whose command line ran sweep.py.
#   LAND_ISOLATED=1 lifts the "wait for a gap" rule: the gate then runs in its OWN view root
#   (build_ovl_gate) so mk_ovl_root.sh never replaces the build_ovl the lanes' verify.py scores in,
#   lanes may keep scoring through the whole landing, and a second landing queues on the land lock
#   instead of exiting (docs/LANE_KIT.md, "Isolated landing (round 68)").
# Moved from the session scratchpad (land20.sh ... land25.sh) in round 24.
set -u
cd "$(dirname "$0")/../.."
# one landing at a time: two concurrent landings (an orchestrator's and a hand-queued one) both rewrite src/ and
# gate; the second waits here on a cross-process lock (2026-09-19)
mkdir -p build_ovl/work; exec 9>build_ovl/work/land.lock; flock 9
TAG=${1:?tag}; shift
LANES="$*"; [ -n "$LANES" ] || { echo "usage: land_lanes.sh <tag> <lane>..."; exit 1; }
# Concurrency.  Default (LAND_ISOLATED unset or 0): byte-for-byte the old behaviour - refuse while any
# codex lane or any sweep runs, because the gate's mk_ovl_root.sh replaces build_ovl/tools and
# build_ovl/work/g3/overlay_func_compare.py under a lane's running scorer (a false "not exact").
# LAND_ISOLATED=1: the gate runs in build_ovl_gate, build_ovl is never touched, so lanes score
# throughout; this landing already holds the land lock above, so a second landing QUEUES there, and a
# FOREIGN sweep (one no landing started) is waited for rather than refused.
#   LAND_BUSY_CMD     overrides the foreign-sweep test (exit 0 = busy); tools/tests/test_land_isolated.py
#   LAND_POLL         seconds between checks (default 10)
#   LAND_WAIT_MAX     polls before giving up on a foreign sweep (default 720 = 2 h)
#   LAND_GUARD_ONLY=1 run the guards, print LAND_GUARD_OK and exit 0 (self-test hook: lands nothing)
ISO=${LAND_ISOLATED:-0}
if [ "$ISO" != 1 ]; then
  if pgrep -f "[c]odex exec" >/dev/null; then echo "a codex lane is running: wait for it"; exit 1; fi
  if pgrep -f "[s]weep.py " >/dev/null; then echo "a sweep is running: wait for it"; exit 1; fi
else
  # THE SELF-MATCH TRAP (see tools/lanes/land_gap.sh): our own shell and its ancestors can carry
  # "sweep.py" in their command lines (the wrapper `bash -c "... > some_sweep.py.log"` that started
  # us), and so does every subshell this script forks; our own cascade sweeps are ours too.  A pid is
  # foreign only when it is neither this shell, nor one of its ancestors, nor one of its descendants.
  MINE=" $$ "; ppid=$$
  for _ in 1 2 3 4 5; do
    ppid=$(ps -o ppid= -p "$ppid" 2>/dev/null | tr -d ' ')
    [ -n "${ppid:-}" ] && [ "$ppid" != 0 ] || break
    MINE="$MINE$ppid "
  done
  is_ours() {
    local p=$1 i=0
    case "$MINE" in *" $p "*) return 0;; esac
    while [ "$i" -lt 8 ]; do
      p=$(ps -o ppid= -p "$p" 2>/dev/null | tr -d ' ')
      [ -n "${p:-}" ] && [ "$p" != 0 ] || return 1
      [ "$p" = "$$" ] && return 0
      i=$((i + 1))
    done
    return 1
  }
  foreign_sweep() {
    if [ -n "${LAND_BUSY_CMD:-}" ]; then eval "$LAND_BUSY_CMD"; return $?; fi
    local p
    for p in $(pgrep -f "[s]weep.py " 2>/dev/null); do
      [ -d "/proc/$p" ] || continue            # gone between pgrep and here: not a running sweep
      is_ours "$p" || return 0
    done
    return 1
  }
  w=0
  while foreign_sweep; do
    [ "$w" = 0 ] && echo "== $TAG: a foreign sweep is running: queued (this landing waits, it does not refuse)"
    w=$((w + 1))
    if [ "$w" -gt "${LAND_WAIT_MAX:-720}" ]; then echo "a foreign sweep outlasted LAND_WAIT_MAX polls: wait for it"; exit 1; fi
    sleep "${LAND_POLL:-10}"
  done
fi
[ "${LAND_GUARD_ONLY:-0}" = 1 ] && { echo "LAND_GUARD_OK iso=$ISO"; exit 0; }
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
           t51_sched_order t53_reg_state t53k_keep t54_pagebase t57_keepafterstore t57b_keepafternext t59_offsetsym t63_memdep t66_sameregmerge t69_prologue t71_updateaftercall t72_stmtperm t38b_unstage_run t74_multiset t76_arity t78_aggcopy t80_derivecall t81_reuselocal t82_armsink t83_storeafterproducer t84_narrowparams t86_symaddr t87_lifetimemerge \
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
  echo "== gate"
  if [ "$ISO" = 1 ]; then
    # the isolated root gates the SAME src/ (overlays/<ov>/first_pass_matched -> src/<ov>) with the same
    # window YAMLs and the same SLUS build: only the throw-away build dirs and the tools copy differ
    EXP=gate SRCROOT="$PWD/src" bash tools/build/mk_ovl_root.sh && GATE_BUILD_ROOT=build_ovl_gate python3 tools/build/gate_all.py --workers 8 && bash tools/build/build_slus.sh -j 8
  else
    bash tools/build/mk_ovl_root.sh && python3 tools/build/gate_all.py --workers 8 && bash tools/build/build_slus.sh -j 8
  fi
  echo "GATE_RC=$?"
  if [ "$ISO" = 1 ] && ! diff -rq --exclude=__pycache__ tools/gate build_ovl/tools >/dev/null 2>&1; then
    echo "note: build_ovl/tools no longer mirrors tools/gate (an isolated landing never rebuilds the lanes' scorer root): run 'bash tools/build/mk_ovl_root.sh' in the next lane gap"
  fi
  python3 tools/levels.py >/dev/null; python3 tools/status.py >/dev/null; grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md
fi
rm -rf "$STAGE"
echo "== done"
