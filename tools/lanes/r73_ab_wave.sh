#!/bin/bash
# Round 73 (2026-09-22/23): A/B of the new codex models gpt-6-sol / gpt-6-luna against the measured
# gpt-5.6-sol kit baseline (3-6-pin rows 8/35, 8-12-pin rows 35%) and a small gpt-6-astra control.
# Rows: docs/evidence/r73_ab_rows.json - rows with live pins, no byte-exact candidate in any lane,
# never served by astra; 3-7 band alternated by rank between sol6/luna6 (8 packs each), 8+ band split
# 2:1 sol6/astra by rank, 1-2 band to luna6 (6 packs). All rows are retries of 5.6-era lanes (~3% for a
# same-model retry), so any lift is the model.  Usage:
#   bash tools/lanes/r73_ab_wave.sh build    # CPU: build_class_pack --rows --duck, then kit_pack (v2 brief + kit)
#   bash tools/lanes/r73_ab_wave.sh launch   # three pools, --no-land (land_finished2.sh lands continuously)
set -u
cd "$(dirname "$0")/../.."
RJ=docs/evidence/r73_ab_rows.json
LOG=${R73_LOG:-work/native_lane/_r73_logs}; mkdir -p $LOG
lanes() { python3 -c "import json;print(' '.join(k for k in json.load(open('$RJ')) if k.startswith('$1')))"; }
case "${1:-}" in
build)
  for L in $(lanes r7); do
    [ -f work/native_lane/$L/PROMPT.txt ] && { echo "built already: $L"; continue; }
    IDS=$(RJ=$RJ LN=$L python3 -c "import json,os;print(','.join(json.load(open(os.environ['RJ']))[os.environ['LN']]))")
    python3 tools/lanes/build_class_pack.py $L "CHANGED|17-32,BOTH|17-32,CHANGED|3-4,MOVED|1-2" 5 --rows "$IDS" --duck --exemplars 6 2>&1 | tail -1
    python3 tools/lanes/kit_pack.py $L --paragraphs big_rows,new_findings 2>&1 | tail -1
  done
  echo R73_BUILT ;;
launch)
  S6=$(lanes r73_sol6_ | tr ' ' ,); L6=$(lanes r73_luna6_ | tr ' ' ,); AS=$(lanes r73_astra_ | tr ' ' ,)
  LAND_ISOLATED=1 nohup python3 tools/lanes/pool.py R73SOL6 --model sol6 -c 4 --lanes $S6 --no-land --note "r73 A/B gpt-6-sol: 3-7 band retries + 8+ band" > $LOG/pool_r73sol6.log 2>&1 &
  echo "R73SOL6 pid $!"
  LAND_ISOLATED=1 nohup python3 tools/lanes/pool.py R73LUNA6 --model luna6 -c 4 --lanes $L6 --no-land --note "r73 A/B gpt-6-luna: 3-7 band retries + 1-2 band" > $LOG/pool_r73luna6.log 2>&1 &
  echo "R73LUNA6 pid $!"
  LAND_ISOLATED=1 nohup python3 tools/lanes/pool.py R73ASTRA --model astra -c 2 --lanes $AS --no-land --note "r73 A/B astra control on the 8+ band" > $LOG/pool_r73astra.log 2>&1 &
  echo "R73ASTRA pid $!"
  echo R73_POOLS_STARTED ;;
*) echo "usage: $0 build|launch"; exit 1 ;;
esac
