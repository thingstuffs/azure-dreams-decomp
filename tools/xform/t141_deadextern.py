"""T141: an `extern` data declaration the row never uses is deleted (readability; removes scaffolding volatiles).

APPEARS     m2c / earlier lanes leave block-scope or file-scope `extern T D_X;` / `extern volatile T D_X[];` declarations
            whose symbol is not referenced anywhere else in the file (r93_sonnet_vb18: `extern volatile int
            D_80071250[];` re-declared in six rows and never read).  Round 93 census: 286 declarations in 153 rows.
RESOLVES    the declaration line is deleted.  Only whole-line, single-declarator data declarations (no `(`, `{`, `=`, no
            comma list) whose identifier occurs exactly once in the file.  Byte-neutral by construction; still verified,
            pins unchanged.
"""
import re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from pin_census import sites_of

DECL = re.compile(r"^[ \t]*extern[ \t]+[^;(){}=,\n]*?\b(?P<sym>[A-Za-z_]\w*)[ \t]*(\[[^\]\n]*\])?[ \t]*;[ \t]*\n", re.M)


def sites(text):
    out = []
    for m in DECL.finditer(text):
        if len(re.findall(r"\b%s\b" % re.escape(m.group("sym")), text)) == 1:
            out.append((m.start(), m.end()))
    return out


def rewrite(text, chosen):
    for s, e in sorted(chosen, key=lambda x: -x[0]):
        text = text[:s] + text[e:]
    return text


class T:
    name = "t141_deadextern"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text) else "no unused extern declaration"

    @staticmethod
    def apply_verified(text, row, census, vf):
        ss = sites(text)
        if not ss:
            return None, {"refused": ["no site"]}
        new = rewrite(text, ss)
        if len(sites_of(new)) == len(sites_of(text)) and vf(new).get("exact"):
            return new, {"deleted": len(ss)}
        return None, {"refused": ["not exact"]}
