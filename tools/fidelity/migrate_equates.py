#!/usr/bin/env python3
"""Move file-scope absolute-address equates out of row C texts into the per-container symbol file.

    python3 migrate_equates.py scan  [--rows ID,...] [--json OUT]       census: every equate site + its fate
    python3 migrate_equates.py apply --rows ID,... --out-dir DIR      dry run: migrated texts under DIR/<container>/,
                                                                     symbol files under DIR/config/ (seeded from config/)
    python3 migrate_equates.py apply --all --in-place                 the migration: rewrites src/<container>/*.c and
                                                                     appends to config/overlays/abs_syms.txt and
                                                                     config/slus_006.14.c_syms.txt

Accepted equate forms (file scope, one statement per line or several `.set` joined with \\n in ONE string):
    __asm__(".set NAME, 0xADDR");          asm("NAME = 0xADDR");          __asm__(".set NAME, BASE + 0xOFF");
Anything else inside the same asm string (.globl, .size, .type, labels, instructions) => the whole string is
REFUSED and left in place (composite stamps and aliases are other census classes awaiting a ruling).

Fate of each accepted equate:
    encoded  NAME is D_<ADDR>/func_<ADDR> and its value == ADDR (offset equates `BASE + 0xOFF` are evaluated first):
             the line is deleted; the overlay paths need no file line (the window gate's symbol_addr and the scorer's
             inject_name_encoded_symbols resolve such a name to its address); a SLUS row gets a C_SYMS line, because
             the SLUS link (tools/build/configure.py) has no by-name fallback.
    alias    any other NAME that spells its address, <prefix>_<ADDR>[_<tag>] (D_X_2, D_X_store, T_X, jtbl_X, D_X_R):
             deleted, one `NAME = 0xADDR;` line in config/overlays/abs_syms.txt (SLUS: config/slus_006.14.c_syms.txt).
    dead     an alias the C never uses beyond its `extern` line: deleted, no file line.
    REFUSED  (the whole asm string stays) NAME is name-encoded but its value differs (it would contradict the by-name
             rule every other row relies on: rename the C symbol instead), an alias does not spell its address, the
             value is a symbol (`.set a_returning, a` label aliases: another census class), or an offset base is
             unknown.  A name already in a symbol file at another address stops the apply (exit 2).
The C keeps (or gains) `extern` declarations untouched: the generator never edits C, only deletes asm lines.
"""
import argparse, json, re, sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
from common import ROOT as REPO  # noqa: E402

ASM_STMT = re.compile(r'^[ \t]*(?:__asm__|asm)[ \t]*\([ \t]*"((?:[^"\\]|\\.)*)"[ \t]*\)[ \t]*;[ \t]*\n?', re.M)
SET_RE = re.compile(r'^\s*\.set\s+([A-Za-z_][A-Za-z0-9_]*)\s*,\s*(.+?)\s*$')
EQ_RE = re.compile(r'^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(.+?)\s*$')
HEX = re.compile(r'^0[xX]([0-9A-Fa-f]+)$')
OFF = re.compile(r'^([A-Za-z_][A-Za-z0-9_]*)\s*\+\s*0[xX]([0-9A-Fa-f]+)$')
ENC = re.compile(r'^(?:D|func)_([0-9A-Fa-f]{8})$')


def parse_string(s):
    """asm string -> [(name, expr)] when EVERY statement is an equate, else None."""
    stmts = [x for x in s.replace("\\n", "\n").replace("\\t", " ").split("\n") if x.strip()]
    out = []
    for st in stmts:
        m = SET_RE.match(st) or EQ_RE.match(st)
        if not m:
            return None
        out.append((m.group(1), m.group(2)))
    return out or None


def evaluate(name, expr, known):
    m = HEX.match(expr)
    if m:
        return int(m.group(1), 16), None
    m = OFF.match(expr)
    if m:
        base = m.group(1)
        if base in known:
            return known[base] + int(m.group(2), 16), None
        e = ENC.match(base)
        if e:
            return int(e.group(1), 16) + int(m.group(2), 16), None
        return None, f"offset base {base} unknown"
    return None, f"unsupported expression {expr!r}"


def scan_text(text):
    """-> (sites, migrated_text).  sites: dicts {line, string, equates:[{name, addr, fate, why}], refused}."""
    sites, known, cut = [], {}, []
    for m in ASM_STMT.finditer(text):
        eqs = parse_string(m.group(1))
        line = text.count("\n", 0, m.start()) + 1
        if eqs is None:
            continue                                   # not an equate string: other class, untouched
        site = {"line": line, "string": m.group(1), "equates": [], "refused": None}
        for name, expr in eqs:
            addr, why = evaluate(name, expr, known)
            rec = {"name": name, "expr": expr, "addr": None if addr is None else f"0x{addr:08X}"}
            if addr is None:
                rec.update(fate="REFUSED", why=why)
            else:
                known[name] = addr
                e = ENC.match(name)
                if e and int(e.group(1), 16) != addr:
                    rec.update(fate="REFUSED", why="name-encoded address differs from the value")
                elif e:
                    rec["fate"] = "encoded"
                elif not re.fullmatch(r"[A-Za-z]+_%08X(?:_\w+)?" % addr, name, re.I):
                    rec.update(fate="REFUSED", why="alias name does not spell its address (<prefix>_<ADDR>[_<tag>])")
                else:
                    rec["fate"] = "alias"
            site["equates"].append(rec)
        if any(r["fate"] == "REFUSED" for r in site["equates"]):
            site["refused"] = "; ".join(r["why"] for r in site["equates"] if r["fate"] == "REFUSED")
        else:
            cut.append((m.start(), m.end()))
        sites.append(site)
    out, pos = [], 0
    for a, b in cut:
        out.append(text[pos:a]); pos = b
    out.append(text[pos:])
    new = "".join(out)
    # an alias the C never uses (only an `extern` line names it) needs no symbol-file line: nothing references it
    for site in sites:
        for e in site["equates"]:
            if e["fate"] == "alias" and not site["refused"]:
                uses = [l for l in new.splitlines() if re.search(r"\b%s\b" % re.escape(e["name"]), l)
                        and not l.lstrip().startswith("extern ")]
                if not uses:
                    e["fate"] = "dead"
    return sites, new


def load_rows(ids=None):
    from common import rows, clean_path
    rs = rows(ids)
    return [(r, clean_path(r)) for r in rs if r["container"] != "ovmovie"]


def sym_file_for(container, syms_dir):
    if container == "slus":
        return Path(syms_dir) / "slus_006.14.c_syms.txt"
    return Path(syms_dir) / "overlays" / "abs_syms.txt"          # one file for every overlay container


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("mode", choices=["scan", "apply"])
    ap.add_argument("--rows", default="")
    ap.add_argument("--all", action="store_true", help="every registered row (default for scan)")
    ap.add_argument("--in-place", action="store_true", help="write src/ and config/ (the quiet-window migration)")
    ap.add_argument("--json")
    ap.add_argument("--out-dir")
    ap.add_argument("--syms-dir", help="a config/ root to extend (default: the repo's config/, copied)")
    args = ap.parse_args()
    ids = [x for x in args.rows.split(",") if x] or None
    if args.mode == "apply" and not (ids or args.all):
        ap.error("apply needs --rows or --all")
    if args.mode == "apply" and bool(args.in_place) == bool(args.out_dir):
        ap.error("apply needs exactly one of --out-dir (dry run) and --in-place")
    report = []
    for row, path in load_rows(ids):
        if not path.exists():
            continue
        text = path.read_text(errors="replace")
        sites, new = scan_text(text)
        if not sites:
            continue
        report.append({"id": row["id"], "cfg": row["cfg"], "sites": sites, "changed": new != text})
        if args.mode == "apply" and new != text:
            if args.in_place:
                path.write_text(new)
            else:
                od = Path(args.out_dir) / row["container"]; od.mkdir(parents=True, exist_ok=True)
                (od / path.name).write_text(new)
    if args.mode == "apply":
        syms_dir = REPO / "config" if args.in_place else Path(args.syms_dir or (Path(args.out_dir) / "config"))
        seed = REPO / "config/slus_006.14.c_syms.txt"
        if not args.in_place and not args.syms_dir and seed.exists() and not (syms_dir / seed.name).exists():
            syms_dir.mkdir(parents=True, exist_ok=True); (syms_dir / seed.name).write_text(seed.read_text())
        entries = {}
        for rep in report:
            c = rep["id"].split("/")[0]
            for s in rep["sites"]:
                if s["refused"]:
                    continue
                for e in s["equates"]:
                    if e["fate"] == "alias" or (c == "slus" and e["fate"] == "encoded"):
                        entries.setdefault(c, {}).setdefault(e["name"], set()).add((e["addr"], rep["id"]))
        for c, names in entries.items():
            f = sym_file_for(c, syms_dir); f.parent.mkdir(parents=True, exist_ok=True)
            have = {}
            if f.exists():
                for ln in f.read_text().splitlines():
                    m = re.match(r"\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;", ln)
                    if m: have[m.group(1)] = int(m.group(2), 16)
            lines = []
            if not f.exists() and c != "slus":
                lines += ["// Absolute-address symbols for the overlay containers (main/town/dungeon/ovmovie), read by the window gate",
                          "// (tools/gate/overlay_local_gate.py ABS_SYMS_FILE) and the per-row scorer (tools/gate/match.py ABS_SYMS).",
                          "// One `NAME = 0xADDR; // users` line per name a row references that no object defines and the by-name rule",
                          "// (D_<ADDR>/func_<ADDR> resolve to <ADDR>) cannot resolve.  Every NAME spells its own address",
                          "// (<prefix>_<ADDR>[_<tag>]): a second name for one address keeps gcc from CSE-ing two accesses into one",
                          "// base register (the extra-name equates of the r95 census, tied to the cdk address-split cell: retire a line",
                          "// when its rows stop needing the second name).  Generated by tools/fidelity/migrate_equates.py (round 95)."]
            for n in sorted(names):
                addrs = {a for a, _ in names[n]}
                users = sorted({r for _, r in names[n]})
                if len(addrs) != 1 or (n in have and have[n] != int(next(iter(addrs)), 16)):
                    print(f"CONFLICT {c} {n}: {sorted(addrs)} vs file {have.get(n)}", file=sys.stderr); sys.exit(2)
                if n in have:
                    continue
                a = next(iter(addrs))
                if c == "slus":
                    lines.append(f"/* {', '.join(users)} (r95 equate migration) */")
                    lines.append(f"{n} = {a};")
                else:
                    lines.append(f"{n} = {a}; // {', '.join(users)}")
            if lines:
                with f.open("a") as fh:
                    fh.write("\n".join(lines) + "\n")
    if args.json:
        Path(args.json).write_text(json.dumps(report, indent=1))
    n_sites = sum(len(r["sites"]) for r in report)
    fates = {}
    for r in report:
        for s in r["sites"]:
            for e in s["equates"]:
                fates[e["fate"]] = fates.get(e["fate"], 0) + 1
    print(f"rows {len(report)}  equate strings {n_sites}  equates {sum(fates.values())}  fates {fates}")


if __name__ == "__main__":
    main()
