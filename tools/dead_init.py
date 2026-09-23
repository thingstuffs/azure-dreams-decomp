"""Dead zero initializers at a declaration - the owner's 2026-09-23 ruling (docs/PIN_CAMPAIGN_CHARTER.md, "Ruling
2026-09-23 - dead zero initializer"): `T v = 0;` / `= NULL` at a local's DECLARATION is ordinary C even when never
read.  It emits no code but makes v multi-set (REG_N_SETS > 1) - the pure-C equivalent of what an ASM_KEEP fakes -
so each landing that relies on it is a tracked spelling trade: a `{"kind": "dead_init", ...}` record in
ledger/recipe_trades.jsonl (the first one: dungeon/func_809CAE20, lane r76_opus_b12_2).

`trades(cur, new)` finds the declarations that GAIN such an initializer between a row's current text and a landing
candidate; tools/apply_candidates.py appends one record per applied landing that has any, so every landing path that
goes through it (land_lanes.sh, land_gap.sh, land_finished2.sh) records the trade without knowing about the lever.
A candidate that REMOVES such an initializer (t119_deadinit's `uninit` direction, the variable made single-set) is
not a trade and is not recorded.
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from pin_census import sites_of  # noqa: E402

ZERO = r"(?:0|0[uUlL]*|NULL|\(\s*[A-Za-z_][\w \t]*\**\s*\)\s*0)"
DECL = re.compile(r"^(?P<ind>[ \t]+)(?P<ty>(?:(?:register|unsigned|signed|const|struct|union|enum)[ \t]+)*[A-Za-z_]\w*"
                  r"(?:[ \t]+long)?)[ \t]*(?P<p>\**)[ \t]*(?P<v>[A-Za-z_]\w*)[ \t]*(?P<init>=[ \t]*" + ZERO +
                  r")?[ \t]*;", re.M)
NOT_TYPES = {"return", "goto", "case", "else", "break", "continue", "sizeof", "do"}


def decls(text):
    """{name: (has_zero_init, line text)} over the indented (local) declarations; a name declared twice keeps
    its first declaration."""
    out = {}
    for m in DECL.finditer(text):
        if m.group("ty").split()[-1] in NOT_TYPES:
            continue
        out.setdefault(m.group("v"), (bool(m.group("init")), m.group(0).strip()))
    return out


def trades(cur, new):
    """[{"name", "init"}] - locals whose declaration gains a zero initializer from `cur` to `new`."""
    a, b = decls(cur), decls(new)
    return [{"name": v, "init": b[v][1]} for v in sorted(b)
            if b[v][0] and v in a and not a[v][0]]


def removed_pins(cur, new):
    """The pin sites of `cur` whose text no longer occurs in `new` (a short description for the record)."""
    seg = lambda t, s: re.sub(r"\s+", " ", t[s[3]:s[4]]).strip()[:80]
    have = [seg(new, s) for s in sites_of(new) if s[0] != "expand"]
    out = []
    for s in sites_of(cur):
        if s[0] == "expand":
            continue
        x = seg(cur, s)
        if x in have:
            have.remove(x)
        else:
            out.append(x)
    return out


def record(row_id, cur, new, lane, at, round_tag="r76"):
    """The recipe_trades.jsonl record for one landing, or None when the candidate adds no dead initializer."""
    tr = trades(cur, new)
    if not tr:
        return None
    return {"kind": "dead_init", "id": row_id, "site": "; ".join(removed_pins(cur, new)) or "-",
            "init": "; ".join(t["init"] for t in tr), "lane": lane, "round": round_tag, "at": at,
            "note": "owner ruling 2026-09-23 (charter): zero initializer at declaration, never read; makes the "
                    "variable multi-set (recorded by tools/apply_candidates.py at landing)"}
