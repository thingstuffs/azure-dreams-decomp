#!/bin/bash
# Land every FINISHED lane that still holds unlanded candidates, continuously, with isolated landings (round 68).
#   nohup bash tools/lanes/land_finished.sh [interval_seconds=1200] [glob='r6[5-9]_* r7[0-9]_*'] &
# A lane is finished when it has last_message.txt (model lane) or a journal.jsonl that no running gen_drive/clone_transfer
# names (generator lane).  A candidate is unlanded when its .base_sha still equals the sha of the row's current src text.
# Stale candidates are skipped by apply_candidates anyway; this only decides which lanes are worth a landing transaction.
# A (lane,row,base_sha) candidate is offered ONCE (state: work/native_lane/.land_finished_seen.json): a candidate the landing
# rule refuses would otherwise trigger a full cascade + gate every cycle.
# Stops when the file work/native_lane/STOP_LAND_FINISHED2 exists.  Never uses pgrep/pkill on its own name.
cd "$(dirname "$0")/../.."
INT=${1:-1200}; GLOB=${2:-"r6[5-9]_* r7[0-9]_*"}
while [ ! -f work/native_lane/STOP_LAND_FINISHED2 ]; do
  LANES=$(python3 - $GLOB <<'PY'
import sys, glob, os, subprocess, json
sys.path.insert(0, 'tools'); from common import rows, clean_path, sha_text
by = {r['id']: r for r in rows()}
ps = subprocess.run(['ps', '-eo', 'args'], capture_output=True, text=True).stdout
SEEN='work/native_lane/.land_finished_seen.json'
seen=set(json.load(open(SEEN))) if os.path.exists(SEEN) else set()
out = []
for pat in sys.argv[1:]:
    for d in sorted(glob.glob('work/native_lane/' + pat)):
        name = os.path.basename(d)
        if name.endswith(('_check', '_base')) or '_check' in name or not os.path.isdir(d + '/out'): continue
        model = os.path.exists(d + '/last_message.txt')
        gen = os.path.exists(d + '/journal.jsonl') and (' ' + name + ' ') not in (ps + ' ') and not os.path.exists(d + '/PROMPT.txt')
        if not (model or gen): continue
        fresh = 0
        for f in glob.glob(d + '/out/*/*.c'):
            rid = '/'.join(f.split('/')[-2:])[:-2]; r = by.get(rid); b = f + '.base_sha'
            if r and os.path.exists(b) and open(b).read().strip() == sha_text(clean_path(r).read_text()):
                key = name + '|' + rid + '|' + open(b).read().strip()
                if key not in seen: fresh += 1; seen.add(key)
        if fresh: out.append(name)
json.dump(sorted(seen), open(SEEN,'w'))
print(' '.join(out))
PY
)
  if [ -n "$LANES" ]; then
    echo "== $(date -u +%FT%TZ) landing: $LANES"
    LAND_ISOLATED=1 GAP_MAX_WAIT=7200 bash tools/lanes/land_gap.sh fin$(date -u +%H%M) $LANES 2>&1 | grep -E "^keep |applied|refused|GATE_RC|Pin sites|LAND_GAP_END|MATCH" | grep -v "^pass"
  else echo "== $(date -u +%FT%TZ) nothing to land"; fi
  sleep $INT
done
echo LAND_FINISHED_END
