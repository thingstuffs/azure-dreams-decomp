"""try.py ROW CANDFILE [...pairs]  -> check() result per pair (listing identity + verify.py score)."""
import json, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import row_index
from check import check
R = row_index()
a = sys.argv[1:]
for rid, f in zip(a[::2], a[1::2]):
    rec = check(R[rid], Path(f).read_text())
    print(json.dumps(rec)[:1500])
