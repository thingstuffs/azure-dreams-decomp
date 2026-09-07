"""T1: hoist the m2c 'valid syntax' macro block into include/m2c_compat.h.

Subtracts the canonical block's lines one by one (exact text), so hand-added lines that sit
inside the block region survive.  Adds `#include "m2c_compat.h"` after `#include "common.h"`
when any of the hoisted names is still used.
"""
import re
from pathlib import Path
COMPAT = Path(__file__).resolve().parents[2] / "include/m2c_compat.h"

def _canon_lines():
    t = COMPAT.read_text().split("#define M2C_COMPAT_H\n", 1)[1].rsplit("#endif", 1)[0]
    return [l for l in t.split("\n")]

CANON = _canon_lines()
CANON_SET = {l for l in CANON if l.strip()}
CANON_NORM = {re.sub(r"\s+", " ", l).strip() for l in CANON if l.strip()}
def _canon(l):
    return l in CANON_SET or re.sub(r"\s+", " ", l).strip() in CANON_NORM
NAMES = sorted({m for m in re.findall(r"^(?:#define|typedef .*?)\s+([A-Za-z_][A-Za-z0-9_]*)", "\n".join(CANON), re.M)} |
               {"f32", "f64", "s64", "u64", "NULL", "M2C_UNK", "M2C_UNK8", "M2C_UNK16", "M2C_UNK32", "M2C_UNK64"})
NAME_RE = re.compile(r"\b(" + "|".join(re.escape(n) for n in NAMES) + r")\b")
MARK = "This header contains macros emitted by m2c"

class T:
    name = "t1_boiler"; level = 1
    @staticmethod
    def eligible(text, row, census):
        if '#include "common.h"' not in text:
            return "no common.h include (self-contained prelude)"
        if MARK in text or "typedef float f32;" in text:
            return None
        # a file already carrying the compat header but with stray duplicates of its lines
        if '#include "m2c_compat.h"' in text and any(_canon(l) for l in text.split("\n")):
            return None
        return "no boilerplate"
    @staticmethod
    def apply(text, row, census):
        lines = text.split("\n")
        out = []; removed = 0; in_comment = False
        i = 0
        while i < len(lines):
            l = lines[i]
            # the 7-line explanatory comment that starts with '/*' and contains MARK on the next line
            if l.strip() == "/*" and i + 1 < len(lines) and MARK in lines[i + 1]:
                j = i
                while j < len(lines) and not lines[j].rstrip().endswith("*/"): j += 1
                removed += j - i + 1; i = j + 1; continue
            if l.strip() == "#ifndef NULL" and i + 2 < len(lines) and lines[i + 1].strip() == "#define NULL 0" and lines[i + 2].strip() == "#endif":
                removed += 3; i += 3; continue
            if _canon(l) and not l.startswith("#endif"):
                removed += 1; i += 1; continue
            if l.startswith("/* ") and l.rstrip().endswith("*/") and any(l == c for c in CANON):
                removed += 1; i += 1; continue
            out.append(l); i += 1
        body = "\n".join(out)
        # collapse runs of blank lines left behind
        body = re.sub(r"\n{3,}", "\n\n", body)
        if NAME_RE.search(body.split("\n", 1)[1] if "\n" in body else body) and '#include "m2c_compat.h"' not in body:
            body = body.replace('#include "common.h"\n', '#include "common.h"\n#include "m2c_compat.h"\n', 1)
        return body if removed else None
