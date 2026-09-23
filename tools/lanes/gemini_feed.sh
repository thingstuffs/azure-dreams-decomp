#!/bin/bash
# Continuous Gemini (agy) pool, round 76 (owner 2026-09-23: agy usage is free this window and after its weekly reset -
# "spam it till it drops").  ONE background job, ONE completion line (GEMINI_FEED_END); no orchestrator polling.
#   nohup bash tools/lanes/gemini_feed.sh [hours=48] [packs_per_batch=6] [concurrency=2] > LOG 2>&1 &
# Each batch: probe agy (exact OK line, no limit words: tools/lanes/pool.py probe) -> tools/lanes/ab_plan.py feed
# (escalation leftovers, then never-strong-served rows by band, then 8+ cluster packs; tier guard: Gemini never gets
# a row it already served at the same text; rows of unfinished r76 lanes and the r76o_ overlap rows are reserved) ->
# pool.py --model agy --kit --no-land (lanes r76_gemf_*: land_finished2's r7[0-9]_* glob lands the wins).
# A limit-cut lane (no candidate, limit words in its output) gets limit_cut.txt so its rows count as unserved.
# When the probe fails (limit), the job sleeps 1 h and probes again (the reset watch), until the deadline.
# Stop early: touch work/native_lane/STOP_GEMINI_FEED.  Never pgrep/pkill on its own name.
cd "$(dirname "$0")/../.."
HOURS=${1:-48}; P=${2:-6}; C=${3:-2}
END=$(( $(date +%s) + HOURS * 3600 ))
F=work/native_lane/_gemini_feed; mkdir -p $F; [ -f $F/.ignore ] || echo '*' > $F/.ignore
probe() { python3 -c "import sys; sys.path.insert(0,'tools/lanes'); import pool; sys.exit(0 if pool.probe(pool.MODELS['agy']) else 1)"; }
mark_limit_cut() {
  for d in "$@"; do
    [ -d "$d" ] || continue
    ls "$d"/out/*/*.c >/dev/null 2>&1 && continue
    if cat "$d"/last_message.txt "$d"/agy.log 2>/dev/null | tail -c 4000 | grep -qiE 'usage limit|quota|rate limit|resource_exhausted|exhausted|429'; then
      echo "limit cut: $d"; date -u +%FT%TZ > "$d/limit_cut.txt"
    fi
  done
}
n=0
while [ "$(date +%s)" -lt $END ] && [ ! -f work/native_lane/STOP_GEMINI_FEED ]; do
  if ! probe; then echo "$(date -u +%FT%TZ) agy probe failed (limit?): sleeping 1 h"; sleep 3600; continue; fi
  n=$((n + 1))
  python3 tools/lanes/ab_plan.py feed --tier agy --packs $P --prefix r76_gemf --out $F/batch$n || break
  NW=$(python3 -c "import json;print(len(json.load(open('$F/batch$n.whole.json'))))")
  NC=$(python3 -c "import json;print(len(json.load(open('$F/batch$n.cluster.json'))))")
  if [ "$NW" = 0 ] && [ "$NC" = 0 ]; then echo "$(date -u +%FT%TZ) feed empty"; break; fi
  echo "$(date -u +%FT%TZ) batch $n: $NW whole, $NC cluster packs"
  [ "$NW" != 0 ] && LAND_ISOLATED=1 python3 tools/lanes/pool.py GEMF${n}W --model agy -c $C --rows-json $F/batch$n.whole.json \
      --kit --no-land --wall-cap 180 --probe-retries 1 --probe-wait 60 --poll 120 --note "r76 gemini feed (free window)" > $F/pool_${n}w.log 2>&1
  [ "$NC" != 0 ] && LAND_ISOLATED=1 python3 tools/lanes/pool.py GEMF${n}C --model agy -c $C --rows-json $F/batch$n.cluster.json \
      --cluster 3-5 --kit --no-land --wall-cap 180 --probe-retries 1 --probe-wait 60 --poll 120 --note "r76 gemini feed, 8+ clusters" > $F/pool_${n}c.log 2>&1
  mark_limit_cut $(python3 -c "import json;d={**json.load(open('$F/batch$n.whole.json')),**json.load(open('$F/batch$n.cluster.json'))};print(' '.join('work/native_lane/'+k for k in d))")
  grep -hE "exited|stops launching|no .* capacity" $F/pool_${n}*.log | tail -12
done
echo "GEMINI_FEED_END $(date -u +%FT%TZ) batches=$n"
