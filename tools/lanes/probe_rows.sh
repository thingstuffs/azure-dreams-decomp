#!/bin/bash
# Run the allocator counterfactual probe over a row list into one JSON report per row (analysis only):
#   bash tools/lanes/probe_rows.sh ROWS.txt OUTDIR [parallel rows, default 3] [--jobs per row, default 2]
# ROWS.txt: row ids in the first field per line. Existing reports whose `sha` still matches are kept.
# Reports are small (knob records without assembly); OUTDIR gets a .ignore so agents' searches skip it.
set -u
cd "$(dirname "$0")/../.."
ROWS=${1:?rows file}; OUT=${2:?out dir}; P=${3:-3}; J=${4:-2}
mkdir -p "$OUT"; [ -f "$OUT/.ignore" ] || echo '*' > "$OUT/.ignore"
export OUT J
one() {
  rid=$1; f="$OUT/$(echo "$rid" | tr / _).json"
  if [ -f "$f" ]; then
    cur=$(sha256sum "src/$rid.c" | cut -d' ' -f1)
    old=$(python3 -c "import json,sys; print(json.load(open(sys.argv[1])).get('sha',''))" "$f" 2>/dev/null)
    [ "$cur" = "$old" ] && return 0
  fi
  nice -n 10 timeout 1200 python3 tools/alloc_probe.py "$rid" --jobs "$J" --json --out "$f.tmp" > /dev/null 2> "$f.err" \
    && mv "$f.tmp" "$f" && rm -f "$f.err" || echo "FAIL $rid"
}
export -f one
grep -v '^#' "$ROWS" | awk 'NF {print $1}' | xargs -P "$P" -I{} bash -c 'one {}'
echo "probe done $(date -u +%H:%M): $(ls "$OUT"/*.json 2>/dev/null | wc -l) reports"
