#!/usr/bin/env python3
"""Generate STATUS.md from the ledger (rows, baseline, census, levels)."""
import collections, json, re, time
from pathlib import Path
from common import LEDGER, ROOT, rows, read_jsonl, PARKED_CONTAINERS
from source_layout import row_path as layout_row_path
from pin_census import sites_of, hidden_asm, strip_composite_asm, composite_asm_spans
import levels as _levels   # the live L5 predicates: the clean column reuses them, never a second copy
from census import _fakedep, _real_tail_count
from row_cache import RowCache, FactInputs, text_key

def current_row_records(records, current_ids):
    """A retired composite's historical census/levels entry is not a current row."""
    return [r for r in records if r["id"] in current_ids]


def placement_unproven_status(rs):
    data = [r for r in rs if r.get("row_kind") == "data"]
    unproven = [r for r in rs if r.get("placement") == "unproven"]
    stale = [r for r in data if r.get("residue") == "stale-image"]
    return (f"\nData rows: {len(data)} ({sum(r['size'] for r in data):,} B); "
            f"stale-image residue DATA: {len(stale)} ({sum(r['size'] for r in stale):,} B).\n"
            f"\nPlacement unproven (excluded from L4 module placement): {len(unproven)} rows "
            f"({sum(r['size'] for r in unproven):,} B)" +
            (": " + ", ".join(r['id'] for r in unproven) if unproven else "") + "\n")


# --- module certificate states (STATUS.md must never print exception text or file paths) -------------------------
# Order is the display order.  The reasons come from overlay_module_evidence.certificate_reason,
# slus_module_evidence.certificate_reason and certify_batch._validate_certificate; anything unrecognised lands in
# "attention" so a new reason string can never leak into the page.
CERT_STATES = collections.OrderedDict([
    ("current", ("current", "complete TU, all affected windows and the genuine assembler agree with retail, bound to the current inputs")),
    ("stale", ("stale: inputs changed", "a certificate exists but a source, recipe, header, tool or review it covers has changed since; it needs renewing")),
    ("missing", ("not certified yet", "no certificate has been issued for this module")),
    ("unchecked", ("not checked here", "an input the check reads (compiler, disc image) is not present in this checkout, so the certificate could not be validated")),
    ("attention", ("needs attention", "the certificate is unreadable or its recorded proof does not hold; it needs a rerun")),
])
_STALE_RE = re.compile(r"changed|stale|migration|differs", re.I)


def cert_state(reason):
    """Classify a certificate_reason string (None = valid) into a CERT_STATES key; the raw text is never shown."""
    if reason is None:
        return "current"
    r = str(reason)
    if "FileNotFoundError" in r or "No such file" in r:
        # the certificate file itself (ledger/modules/...) vs some input of the check that this checkout lacks
        return "missing" if "ledger/modules/" in r else "unchecked"
    if r.startswith(("certificate missing/invalid", "certificate unavailable", "manifest invalid", "invalid ")) or "retail" in r:
        return "attention"
    return "stale" if _STALE_RE.search(r) else "attention"


_UNIVERSAL_HEADERS = ("include/common.h", "include/game.h", "include/globals.h", "include/include_asm.h")


def _short_headers(headers):
    """Header column: names relative to include/, without the four headers every module pulls in."""
    keep = [h[len("include/"):] if h.startswith("include/") else h for h in headers if h not in _UNIVERSAL_HEADERS]
    return ", ".join(f"`{h}`" for h in keep) or "-"


def _state_table(groups, unit="modules"):
    """Summary table: one line per state with module and row counts."""
    out = ["| state | modules | rows | meaning |", "|---|---:|---:|---|"]
    for k, (word, meaning) in CERT_STATES.items():
        g = groups.get(k, [])
        if not g and k != "current":
            continue   # a state nobody is in is noise; "current" always shows (0 current is the news)
        out.append(f"| {word} | {len(g)} | {sum(x[1] for x in g):,} | {meaning} |")
    return out


def _details(summary, header, lines):
    """A collapsed GitHub block (blank lines around the table keep the markdown rendering)."""
    return ["", f"<details><summary>{summary}</summary>", "", *header, *lines, "", "</details>"]


def coverage_summary(root):
    """Whole-image code coverage from the ledger alone (tools/coverage.py: no binary reads); None when unavailable.
    slus is not in that report (it has its own row accounting), so these figures are main + town + dungeon + ovmovie."""
    try:
        import importlib.util   # by path: a site-packages `coverage` must never shadow tools/coverage.py
        spec = importlib.util.spec_from_file_location("azure_coverage", Path(root) / "tools" / "coverage.py")
        _cov = importlib.util.module_from_spec(spec); spec.loader.exec_module(_cov)
        rep = _cov.coverage(root)["containers"]
        num_c = num_all = den = 0
        for v in rep.values():
            w = v["whole_image"]
            den += w["code_bytes_classified_or_estimated"]
            num_c += w["c_rows"]; num_all += w["c_rows"] + w["proven_instances"]
        return {"containers": sorted(rep), "c_pct": 100 * num_c / den, "copy_pct": 100 * num_all / den, "code_bytes": den} if den else None
    except Exception:
        return None


def not_yet_c(root):
    """Per-container split of the code that is not (yet) C, from the ledger alone, with the same interval arithmetic and priorities as
    tools/coverage.py (loaded by path; its helpers do the set work) extended by the undecompiled split segments inside overlay windows:
    {container: dict(in_c, copies, split, recorded, heuristic)} in bytes.  Every byte belongs to at most one class."""
    import importlib.util
    root = Path(root)
    spec = importlib.util.spec_from_file_location("azure_coverage", root / "tools" / "coverage.py")
    cv = importlib.util.module_from_spec(spec); spec.loader.exec_module(cv)
    merge, subtract, inter, size, ext = cv.merge, cv.subtract, cv.intersection, cv.size, cv.extent
    led = root / "ledger"
    rows_, inst, regs = cv.records(led / "rows.jsonl"), cv.records(led / "instances.jsonl"), cv.records(led / "coverage_regions.jsonl")
    conts = {r["container"]: r for r in cv.records(led / "containers.jsonl")}
    latest = {}
    for r in regs: latest[(r["container"], r["foff"], r["size"], r["category"])] = r
    regs = [r for r in latest.values() if r.get("active", True)]
    li = {}
    for r in inst: li[(r["container"], r["foff"], r["size"])] = r
    blocked = {(r["container"], r["foff"], r["size"]) for r in regs if r["category"] == "instance_excluded"}
    proven = [r for r in li.values() if r.get("result") == "proven" and (r["container"], r["foff"], r["size"]) not in blocked]
    # overlay windows: config/overlays yaml file_start/file_end pairs (the container a yaml belongs to is named by its target path)
    file2c = {str(r.get("file", "")).upper(): c for c, r in conts.items()}
    ywin = collections.defaultdict(list)
    for yp in sorted((root / "config/overlays").glob("*.overlay.yaml")):
        t = yp.read_text(errors="replace")
        m = re.search(r"(?:container_path|target_path):\s*(\S+)", t)
        c = file2c.get(Path(m.group(1)).name.upper()) if m else None
        fs = re.findall(r"file_start:\s*(0x[0-9a-fA-F]+|\d+)", t); fe = re.findall(r"file_end:\s*(0x[0-9a-fA-F]+|\d+)", t)
        if c and fs and len(fs) == len(fe):
            ywin[c] += [[int(a, 0), int(b, 0)] for a, b in zip(fs, fe)]
    res = {}
    for c in sorted(conts):
        if c == "slus":
            continue
        cats = collections.defaultdict(list)
        for r in regs:
            if r["container"] == c: cats[r["category"]].append(ext(r))
        win = merge(cats["window"] + ywin.get(c, []))
        C = merge([ext(r) for r in rows_ if r["container"] == c and r.get("foff") is not None and (r.get("func") or "").startswith("func_")])
        drow = [ext(r) for r in rows_ if r["container"] == c and r.get("foff") is not None and not (r.get("func") or "").startswith("func_")]
        data = merge(cats["data_excluded"] + drow)
        cop = subtract([ext(r) for r in proven if r["container"] == c], C + data)
        ss, dseg = [], []
        for key in [c] + (["dungeon_engine"] if c == "dungeon" else []):
            for sp in cv.records(led / "splits" / (key + ".jsonl")):
                if sp.get("foff") is None: continue
                e = ext(sp)
                if sp.get("data_segment") or sp.get("result") == "data": dseg.append(e); continue
                if sp.get("result") == "MERGE_FAIL": continue
                if sp.get("result") in ("CFAIL", "M2C_FAIL") and sp["size"] > 8192: continue   # a whole-window view, not a function
                ss.append(e)
        data_all = merge(data + dseg)
        raw = inter(subtract(ss, C + data_all + cop), win)
        occ = merge(C + cop + raw)
        got_ = {}
        for k in ("unported", "sdk_asm", "estimated_code"):
            got_[k] = subtract(cats[k], occ + data_all); occ = merge(occ + got_[k])
        res[c] = dict(in_c=size(C), copies=size(cop), split=size(raw), sdk=size(got_["sdk_asm"]), unported=size(got_["unported"]), heuristic=size(got_["estimated_code"]))
    return res


BINARY_NAMES = collections.OrderedDict([("slus", "SLUS_006.14 executable"), ("main", "MAIN.BIN"), ("town", "TOWN overlays"),
                                        ("dungeon", "DUNGEON overlays"), ("ovmovie", "OVMOVIE overlay")])


def container_legend(containers):
    return ", ".join("`%s` = %s" % (c, BINARY_NAMES.get(c, c)) for c in containers)


def slus_text(root):
    """SLUS executable text by linked-section ownership (not row sizes, which are stale pre-partition sizes): the linker script's
    `._800` text range, with the objects listed in it classed by where they come from.  None when there is no SLUS build here.
    in_c = text - SDK library asm (build/asm/psyq, PsyQ objects identified against the SDK signatures) - other asm
    (build/asm/*.o hand code) - retail data blobs inside the range (build/assets)."""
    import shutil, subprocess
    b = Path(root) / "build_slus" / "build"
    ld = next((b / n for n in ("slus_006.14_ordered.ld", "slus_006.14.ld") if (b / n).exists()), None)
    elf = b / "slus_006.14.elf"
    readelf, nm = shutil.which("mipsel-linux-gnu-readelf"), shutil.which("mipsel-linux-gnu-nm")
    if not (ld and elf.exists() and readelf and nm):
        return None
    syms = {}
    for line in subprocess.run([nm, str(elf)], capture_output=True, text=True).stdout.splitlines():
        t = line.split()
        if len(t) == 3 and t[2] in ("_800_TEXT_START", "_800_TEXT_END"):
            syms[t[2]] = int(t[0], 16)
    text = syms["_800_TEXT_END"] - syms["_800_TEXT_START"]
    lines = ld.read_text().splitlines()
    a = next(i for i, l in enumerate(lines) if "_800_TEXT_START = ." in l); z = next(i for i, l in enumerate(lines) if "_800_TEXT_END = ." in l)
    def section_bytes(path, prefix):
        out = subprocess.run([readelf, "-SW", str(Path(root) / "build_slus" / path)], capture_output=True, text=True).stdout
        return sum(int(m.group(2), 16) for m in re.finditer(r"\]\s+(\.\S+)\s+PROGBITS\s+\S+\s+\S+\s+([0-9a-f]+)", out) if m.group(1).startswith(prefix))
    sdk = other = blobs = 0
    for l in lines[a:z]:
        for obj, sec in re.findall(r"(build/\S+?\.o)\((\.\w+)\)", l):
            if obj.startswith("build/asm/psyq/"): sdk += section_bytes(obj, sec)
            elif obj.startswith("build/asm/"): other += section_bytes(obj, sec)
            elif obj.startswith("build/assets/"): blobs += section_bytes(obj, sec)
    return dict(text=text, sdk=sdk, other=other + blobs, in_c=text - sdk - other - blobs)


def not_yet_c_section(root):
    root = Path(root)
    if not (root / "tools" / "coverage.py").exists():
        return ""   # a bare tree without the coverage tool: like the glance row, the section is simply absent
    res = not_yet_c(root)
    head = ["container", "code bytes", "in C", "C %", "byte-identical copies of C", "undecompiled split segments",
            "SDK library asm", "other hand asm / unported", "heuristic only", "not yet C (excl. library)"]
    out = ["## Not yet C\n",
           "Code bytes per binary: " + container_legend(list(BINARY_NAMES)) + ". Columns **in C** and **SDK library asm** are done: "
           "C is compiled and matched, and PsyQ SDK library code is reported as library, not a decompile target (decision 55). "
           "The columns **byte-identical copies of C**, **undecompiled split segments**, **other hand asm / unported** and **heuristic only** "
           "are not yet C; **not yet C** is their sum.\n",
           "| " + " | ".join(head) + " |", "|" + "---|" + "---:|" * (len(head) - 1)]
    tot = collections.Counter()
    def line(name, v):
        code = v["in_c"] + v["copies"] + v["split"] + v["sdk"] + v["unported"] + v["heuristic"]
        rest = v["copies"] + v["split"] + v["unported"] + v["heuristic"]
        tot.update(v)
        return (f"| {name} | {code:,} | {v['in_c']:,} | {100 * v['in_c'] / code:.1f}% | {v['copies']:,} | {v['split']:,} | {v['sdk']:,} | {v['unported']:,} | {v['heuristic']:,} | {rest:,} |"
                if code else f"| {name} | 0 | 0 | - | 0 | 0 | 0 | 0 | 0 | 0 |")
    st = slus_text(root)
    if st:
        out.append(line("`slus` (SLUS_006.14)", dict(in_c=st["in_c"], copies=0, split=0, sdk=st["sdk"], unported=st["other"], heuristic=0)))
    for c in sorted(res, key=lambda c: list(BINARY_NAMES).index(c) if c in BINARY_NAMES else 99):
        out.append(line(f"`{c}` ({BINARY_NAMES.get(c, c)})", res[c]))
    code = sum(tot[k] for k in tot)
    if code:
        rest = tot["copies"] + tot["split"] + tot["unported"] + tot["heuristic"]
        out.append(f"| **total** | {code:,} | {tot['in_c']:,} | {100 * tot['in_c'] / code:.1f}% | {tot['copies']:,} | {tot['split']:,} | {tot['sdk']:,} | {tot['unported']:,} | {tot['heuristic']:,} | {rest:,} |")
    sdk_objs = sum(1 for _ in read_jsonl(LEDGER / "sdk_objects.jsonl")) if (LEDGER / "sdk_objects.jsonl").exists() else 0
    out += ["",
            "- **in C**: code whose C is compiled and compared byte for byte with retail.",
            "- **byte-identical copies of C**: a span proven identical to a C function elsewhere in the images; it becomes a link-list placement of that function's source, not new C.",
            "- **undecompiled split segments**: code the split tables carve out inside an overlay window that has no C row yet.",
            "- **SDK library asm**: PsyQ / Sony library code kept as assembler of the retail bytes (library code, decision 55); "
            f"in `slus` the PsyQ objects linked into the text, in the overlays the regions recorded as `sdk_asm` ({sdk_objs} whole Sony SDK objects are also listed in `ledger/sdk_objects.jsonl`).",
            "- **other hand asm / unported**: hand-written assembler of the original program (`slus`: `main.s` and retail data blobs inside the text range) or regions recorded as deliberately unported.",
            "- **heuristic only**: spans that look like functions (`jr ra` shape) with no row, split or proven copy; an estimate.",
            ("- **`slus`** is measured from the linked image: text range, SDK objects and hand asm by linker-script ownership, the rest is C (row sizes are stale pre-partition sizes and are not used)."
             if st else "- **`slus`** needs a SLUS build (`build_slus/`) to be measured by linked-section ownership; it is absent from this table when there is none."),
            ""]
    return "\n".join(out)


# SLUS regions (r82_fable_slus): game image 0x80033AA8-0x8005CA70 = one 2.7.2-cdk build, sound TU 0x8005CA90-0x8005FA34 = stock 2.7.2
def _slus_want(r):
    """Region build of a SLUS row: its w_<addr> id address, else the majority region of its function definitions."""
    m = re.search(r"w_([0-9A-F]{8})", r["id"])
    addrs = [int(m.group(1), 16)] if m else [int(x, 16) for x in re.findall(r"func_([0-9A-F]{8})", " ".join(r.get("defs") or []))]
    votes = collections.Counter("2.7.2-cdk" if 0x80033AA8 <= a < 0x8005CA70 else "2.7.2" if 0x8005CA90 <= a <= 0x8005FA34 else None
                                for a in addrs)
    votes.pop(None, None)
    return votes.most_common(1)[0][0] if votes else None


def _no_g(cfg):
    """Overlays and ovmovie are -G0 everywhere (no overlay function touches $gp): the -G axis is not a compiler fact there."""
    return " ".join(x for x in cfg.replace("-G0", " ").split())


def _recipe_tracker(rs, curc):
    """Rows whose registered recipe is likely NOT their real build (round 84 build structure, r84_fable_build): every
    2.8.x / egcs / 2.95.2 cell is fitted, and a row off its module's census recipe is a crutch candidate."""
    cen = {(c["container"], c["module"]): c.get("best_recipe") for c in read_jsonl(LEDGER / "module_recipe_census.jsonl")}
    # r86_opus_census: recipes the module's pin-free rows cannot separate from best_recipe (stock 2.6.3 / 2.7.2 flavour or the
    # -G axis below the >=3-row bar) - a row registered at one of them is not "likely incorrect"
    tie = {(c["container"], c["module"]): set(c.get("tie_with") or ()) for c in read_jsonl(LEDGER / "module_recipe_census.jsonl")}
    mod = {r["id"]: r.get("module") for r in read_jsonl(LEDGER / "modules.jsonl")}
    # Sony SDK library objects identified by whole-object byte match (owner 2026-10-07): not the game build, so the
    # module recipe says nothing about their compiler (ledger/sdk_objects.jsonl)
    sdk = {r["id"] for r in read_jsonl(LEDGER / "sdk_objects.jsonl")} if (LEDGER / "sdk_objects.jsonl").exists() else set()
    # per-row compiler evidence that overrides the module census (r98: e.g. a reproduced version-specific reorg rule):
    # exempt only while the row stays at the recorded cfg (ledger/recipe_evidence.jsonl)
    rev_all = {r["id"]: r for r in read_jsonl(LEDGER / "recipe_evidence.jsonl")} if (LEDGER / "recipe_evidence.jsonl").exists() else {}
    # only evidence that decides the row exempts it; an unconfirmed attribution stays listed with what would confirm it
    rev = {i: r for i, r in rev_all.items() if r.get("confidence") in ("supported", "confirmed")}
    unconf = {i: r for i, r in rev_all.items() if i not in rev}
    # retail split-address fingerprint (tools/fidelity/split_fingerprint.py): positive evidence that the row's CELL is cdk
    # (the flags/-G stay candidates); a fingerprinted ovmovie head row at a cdk cell is not "likely incorrect"
    fp = {r["id"] for r in read_jsonl(LEDGER / "split_fingerprint_rows.jsonl") if r.get("kinds")} \
        if (LEDGER / "split_fingerprint_rows.jsonl").exists() else set()
    # ovmovie has no module census: the yardstick is the container's majority recipe on the -G-normalised cfg
    ovm = collections.Counter(_no_g(r["cfg"]) for r in rs if r["id"].split("/")[0] == "ovmovie")
    ovm_best = ovm.most_common(1)[0][0] if ovm else None
    members = collections.defaultdict(list)
    tied = []
    cats = collections.OrderedDict((k, collections.Counter()) for k in (
        "late cell (2.8.x / egcs / 2.95.2: fitted)", "cdk cell + crutch flags, module is plain",
        "stock cell inside a cdk module", "other mismatch with the module recipe (-G, stock flavour, -O1)"))
    worst = []
    for r in rs:
        c = r["id"].split("/")[0]
        if r["id"] in sdk or rev.get(r["id"], {}).get("cfg") == r["cfg"] or r.get("row_kind") == "data":
            continue
        cell = r["cfg"].split()[0]
        if c == "slus":
            best = _slus_want(r)            # no code (gte_port_state) -> None -> not judged
        elif c == "ovmovie":
            best = ovm_best
            if best and _no_g(r["cfg"]) == best:
                continue
            if cell.startswith("2.7.2-cdk") and r["id"] in fp and not [x for x in r["cfg"].split()[1:] if x.startswith(("-f", "-O", "-m"))]:
                continue                    # fingerprint-evidenced cdk head of the movie overlay
        else:
            best = cen.get((c, mod.get(r["id"])))
        if c in ("dungeon", "town", "main", "ovmovie") and best and best.split()[0] == "2.7.2-cdk":
            # overlays are -G0 everywhere (r84_fable_build: no overlay function touches $gp); a census that picked cdk -G8
            # only saw texts neutral on the -G axis, so the yardstick is the -G0 cell (r86: 132 rows moved to it)
            best = " ".join(["2.7.2-cdk-G0"] + best.split()[1:])
        late = cell.startswith(("2.8", "2.9"))
        if not late and (not best or r["cfg"] == best):
            continue
        if not late and r["cfg"] in tie.get((c, mod.get(r["id"])), ()):
            tied.append((r["id"], r["cfg"], best))   # the module's pin-free texts cannot separate the two recipes
            continue
        flags = [x for x in r["cfg"].replace("+", " ").split()[1:] if x.startswith(("-f", "-O", "-m"))]
        if late:
            k = "late cell (2.8.x / egcs / 2.95.2: fitted)"
        elif cell.startswith("2.7.2-cdk") and flags and best and best.startswith("2.7.2-cdk") and not best.split()[1:]:
            k = "cdk cell + crutch flags, module is plain"
        elif not cell.startswith("2.7.2-cdk") and best and best.startswith("2.7.2-cdk"):
            k = "stock cell inside a cdk module"
        else:
            k = "other mismatch with the module recipe (-G, stock flavour, -O1)"
        n = (curc.get(r["id"]) or {}).get("pin_total", 0)
        cats[k]["rows"] += 1; cats[k]["pinned"] += bool(n); cats[k]["pins"] += n; cats[k][c] += 1
        members[k].append("%s %s (yardstick %s)" % (r["id"], r["cfg"], best or "?"))
        if n:
            worst.append((n, r["id"], r["cfg"], best or "?"))
    tot = sum(v["rows"] for v in cats.values()); tp = sum(v["pins"] for v in cats.values())
    out = ["\n## Likely incorrect compiler (registered recipe vs the real build)\n",
           "The game is one `2.7.2-cdk -G0 -O2` build plus a town -O1 debug family and stock Sony/devkit/minigame objects "
           "(r84_fable_build). A row is listed when its recipe differs from the one its module's pin-free rows use. Module recipe = "
           "ledger/module_recipe_census.jsonl `best_recipe`; per row see src/<container>/INDEX.md.\n",
           (f"**{tot} rows** differ from their module's recipe ({tp} pins among them)." if tot else "**Compilers are aligned: 0 rows differ from their module's recipe.**")
           + f" {len(rev)} rows sit at a registered recipe backed by per-row compiler evidence; {len(unconf)} attributions are unconfirmed; "
           f"{len(sdk)} are Sony SDK library objects (not the game build); {len(tied)} rows sit at a recipe the module census cannot separate from the best one.\n"]
    body = ["| class | rows | slus / ovmovie / dungeon / town / main | pinned rows | pins |", "|---|---:|---|---:|---:|"]
    for k, v in cats.items():
        body.append(f"| {k} | {v['rows']} | {v['slus']} / {v['ovmovie']} / {v['dungeon']} / {v['town']} / {v['main']} | {v['pinned']} | {v['pins']} |")
    body.append(f"| **total** | **{tot}** | | **{sum(v['pinned'] for v in cats.values())}** | **{tp}** |")
    for k, v in members.items():
        if v:
            body.append(f"\n- {k}: " + "; ".join(v[:40]) + (f"; ... +{len(v) - 40}" if len(v) > 40 else ""))
    if worst:
        body.append("\nMost-pinned rows off their build recipe: " + "; ".join(
            f"{i} {n} pins ({cfg} -> {best})" for n, i, cfg, best in sorted(worst, reverse=True)[:12]) + ".")
    if tot:
        out += body
        body = []
    out.extend(_details("class table" if not tot else "other lists", [], body) if body else [])
    lists = []
    if tied:
        lists += _details(f"rows whose recipe the module census cannot separate from best_recipe (tie_with): {len(tied)}", [],
                          [", ".join("%s %s (best %s)" % t for t in tied) + "."])
    if rev:
        lists += _details(f"rows at a registered recipe backed by per-row compiler evidence (ledger/recipe_evidence.jsonl): {len(rev)}", [],
                          [", ".join("%s %s (%s)" % (i, x["cfg"], x["confidence"]) for i, x in sorted(rev.items())) + "."])
    if unconf:
        lists += _details(f"unconfirmed compiler attributions (ledger/recipe_evidence.jsonl `to_confirm` names the measurement): {len(unconf)}", [],
                          [", ".join("%s %s" % (i, x["cfg"]) for i, x in sorted(unconf.items())) + "."])
    if sdk:
        lists += _details(f"Sony SDK library objects (ledger/sdk_objects.jsonl, whole-object byte match): {len(sdk)}", [], [", ".join(sorted(sdk)) + "."])
    out += lists
    out.append("")
    return "\n".join(out)


def at_a_glance(denom, containers, slus_groups, ov_groups, cov, pins_now, pins_now_rows, pins_pin, levels_pct):
    """Top-of-page summary for a visitor.  Everything is computed; the proof-state paragraph follows the certificate counts."""
    def counts(g):
        return {k: len(g.get(k, [])) for k in CERT_STATES}
    sc, oc = counts(slus_groups), counts(ov_groups)
    total = {k: sc[k] + oc[k] for k in CERT_STATES}
    n_cert = sum(total.values())
    out = ["## At a glance\n",
           "| | |", "|---|---|",
           f"| **Matched** | {denom['rows']:,} functions and data rows, {denom['bytes']:,} bytes, in {len(containers)} containers "
           f"({container_legend(containers)}) |",
           f"| **Byte-identical to retail** | {denom['exact']:,} of {denom['rows']:,} rows ({100*denom['exact']/denom['rows']:.1f}%), "
           f"{denom['exact_bytes']:,} bytes; {denom['unverified']:,} unverified |"]
    if cov:
        out.append(f"| **Code that is C** | {cov['c_pct']:.1f}% as C; {cov['copy_pct']:.1f}% counting byte-identical copies of C functions proven elsewhere "
                   f"(of {cov['code_bytes']:,} bytes of classified or estimated code in {', '.join('`%s`' % c for c in cov['containers'])}; "
                   f"`slus` is accounted by its own rows; breakdown under Not yet C) |")
    out.append(f"| **Assembler scaffolding left** | {pins_now:,} pin sites in {pins_now_rows:,} rows (from {pins_pin:,} at the first pass) |")
    if levels_pct:
        out.append("| **Readability** | " + ", ".join(f"L{l} {levels_pct[l]:.1f}%" for l in (3, 4, 5)) + " of bytes (levels below) |")
    if n_cert:
        out.append(f"| **Module certificates** | {total['current']} of {n_cert} current"
                   + "".join(f", {total[k]} {CERT_STATES[k][0].split(':')[0]}" for k in ("stale", "missing", "unchecked", "attention") if total[k]) + " |")
    out.append("")
    if n_cert and total["current"] < n_cert:
        l45 = (f"; L4 and L5, which need the module certificate, read {levels_pct[4]:.1f}% and {levels_pct[5]:.1f}%" if levels_pct else "")
        out.append(f"**Current proof state.** {n_cert - total['current']} of {n_cert} module certificates are not current{l45}. "
                   "A certificate goes stale when any input it covers changes, so this is a gap in the recorded module proof, not a mismatch; "
                   "one consolidation gate renews them after change batches (decision 53).\n")
    return "\n".join(out)


def placed_shapes(f, curc, by):
    """Link-list placement rows (`source_row`, docs/LINK_LISTS.md) whose home TU satisfies the shape predicate `f`:
    a placement links the home's text at another address, so its bytes carry the home's shape, but the file is
    counted once (the home's entry in `curc`; cur_facts returns None for a placement)."""
    return [r for r in by.values() if r.get("source_row") and r["container"] not in PARKED_CONTAINERS
            and curc.get(r["source_row"]) and f(curc[r["source_row"]])]

SECTIONS = ("head", "glance", "notyet", "progress", "levels", "shape", "modules", "compiler", "trades", "trade_notes", "evidence", "proof")
PROOF_TEXT = ("(1) Per row: the row's C is compiled with the period compiler and assembler and compared byte for byte with the retail bytes. "
              "(2) Window gate: the container's overlay windows (and the whole `SLUS` image) are rebuilt from the sources and compared with retail. "
              "(3) Module certificates: a certificate records that a module's complete translation unit and every affected window rebuild to retail with the "
              "genuine assembler; it is bound to a fingerprint of the module's sources, recipe, headers and tools, so any change to those makes it stale.\n")
READ_NEXT = ("\n**Read next.** [README](README.md) (project overview) - [docs/README.md](docs/README.md) (documentation index) - [docs/PLAN.md](docs/PLAN.md) "
             "(levels L0-L5) - [docs/FIDELITY.md](docs/FIDELITY.md) (what scaffolding means) - [docs/SLUS_MODULES.md](docs/SLUS_MODULES.md) (executable modules) - "
             "[CONTRIBUTING.md](CONTRIBUTING.md).\n")

def main():
    cache = RowCache(ROOT, "status")
    rs = rows(); by = {r["id"]: r for r in rs}
    base = {b["id"]: b for b in read_jsonl(LEDGER / "baseline.jsonl")}
    cen = {c["id"]: c for c in current_row_records(read_jsonl(LEDGER / "census.jsonl"), by)}
    pin = json.load(open(LEDGER / "pin.json"))
    # The page is assembled from named sections at the end (order = SECTIONS); `out` is rebound to the section being written.
    sec = collections.OrderedDict((k, []) for k in SECTIONS)
    out = sec["head"]
    out.append(f"# azure-dreams-decomp status\n\n**Azure Dreams (PlayStation, NTSC-U `SLUS-006.14`) rebuilt as readable C that compiles to the retail game's exact bytes.** "
               f"This page is generated from the ledger by `tools/status.py`; every figure is computed, none is typed in.\n\n"
               f"Generated {time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())}. Baseline: first-pass text frozen {str(pin['extracted_at'])[:10]}.\n")
    out = sec["progress"]
    out.append("## Progress by container\n\n| container | rows | bytes | verified byte-identical | verified bytes | unverified |\n|---|---:|---:|---:|---:|---:|")
    T = collections.Counter(); nonstock = 0
    for c in ("slus", "main", "town", "dungeon", "ovmovie", "ALL"):
        sel = [r for r in rs if (c == "ALL" and r["container"] not in PARKED_CONTAINERS) or r["container"] == c]
        st = [r for r in sel if r["stock"]]
        ex = [r for r in st if base.get(r["id"], {}).get("exact") is True or (r["kind"] == "slus" and base.get(r["id"], {}).get("status") == "ok")]
        nb = [r for r in st if r["id"] not in base]
        if c == "ALL": nonstock = len(sel) - len(st)
        out.append(f"| {c} | {len(sel):,} | {sum(r['size'] for r in sel):,} | {len(ex):,} | {sum(r['size'] for r in ex):,} | {len(nb):,} |")
        if c == "ALL":
            denom = dict(rows=len(sel), bytes=sum(r['size'] for r in sel), exact=len(ex), exact_bytes=sum(r['size'] for r in ex), unverified=len(nb))
    out.append(placement_unproven_status(rs))
    bad = [r for r in rs if r["stock"] and r["id"] in base and base[r["id"]].get("exact") is False]
    parked = (", ".join(sorted(PARKED_CONTAINERS)) + " parked by the owner (listed, excluded from ALL).") if PARKED_CONTAINERS else "No container is parked (ovmovie unparked by the owner 2026-10-14)."
    sec["proof"].append(f"{parked} Ordinary SLUS rows use pinned-TU object verification; grouped module candidates use the full SLUS image gate, including sibling functions and owned data. Historical raw baselines stay per row. Overlay rows use retail-slice comparison through the per-row scorer, with the window gate as the fallback of record. Non-stock rows (bridge cells, per-row assembler dials, platform asm) would be excluded; there are {nonstock} at the pin.\n")
    out.append(f"\nBaseline NOT exact: {len(bad)} rows" + (": " + ", ".join(r["id"] for r in bad[:20]) if bad else "") + "\n")
    out = sec["modules"]
    from slus_module_evidence import module_status
    with cache.phase("slus_placements"):
        module_records = module_status()
    slus_groups = {}
    slus_partition = []
    if module_records:
        for entry in module_records:
            module = entry["module"]
            item = (module["name"], len(module["members"]), module["headers"])
            if module.get("partition_only"):
                slus_partition.append(item)
            elif entry["valid"]:
                slus_groups.setdefault("current", []).append(item)
            elif not (LEDGER / "modules" / (module["name"] + ".json")).exists():
                slus_groups.setdefault("missing", []).append(item)
            else:
                slus_groups.setdefault(cert_state(entry["reason"]), []).append(item)
        n_slus = sum(len(g) for g in slus_groups.values())
        out.append(f"## SLUS modules\n\n{len(module_records)} modules: {n_slus} need a placement certificate, {len(slus_partition)} are partition owners "
                   f"(they grant no whole-row placement, so there is nothing to certify). State of the {n_slus}:\n")
        out.extend(_state_table(slus_groups))
        for k, (word, _) in CERT_STATES.items():
            g = slus_groups.get(k, [])
            if g:
                out.extend(_details(f"{word} - {len(g)} modules, {sum(x[1] for x in g):,} rows", ["| module | logical rows | shared headers (under include/) |", "|---|---:|---|"],
                                    [f"| {n} | {r} | {_short_headers(h)} |" for n, r, h in g]))
        if slus_partition:
            out.extend(_details(f"partition owners: {len(slus_partition)} modules", ["| module | logical rows | shared headers (under include/) |", "|---|---:|---|"],
                                [f"| {n} | {r} | {_short_headers(h)} |" for n, r, h in slus_partition]))
        out.append("\nNot certified yet means no placement certificate has been issued; ownership and retail-byte proofs are separate. Partition owners do not grant whole-row placement. "
                   "Shared headers lists exclude the four every module includes (`common.h`, `game.h`, `globals.h`, `include_asm.h`).\n")
        out.append("Module placement preserves logical row IDs. The existing L4/L5 pin, tail-jump and fidelity requirements still apply; changed shared inputs invalidate placement evidence.\n")
    from accounting_modules import overlay_statuses as overlay_module_status
    with cache.phase("overlay_placements"):
        overlay_records = overlay_module_status(ROOT)
    ov_groups = {}
    for entry in overlay_records:
        ov_groups.setdefault(cert_state(entry["reason"] if not entry["valid"] else None), []).append(
            (entry["module"]["key"], len(entry["module"]["members"])))
    if overlay_records:
        out.append(f"## Overlay modules\n\n{len(overlay_records)} modules ({sum(len(entry['module']['members']) for entry in overlay_records):,} rows). "
                   f"Each is one translation unit placed in a container overlay; its certificate is the whole-TU and window proof:\n")
        out.extend(_state_table(ov_groups))
        for k, (word, _) in CERT_STATES.items():
            g = ov_groups.get(k, [])
            if g:
                out.extend(_details(f"{word} - {len(g)} modules, {sum(x[1] for x in g):,} rows", ["| module | rows |", "|---|---:|"],
                                    [f"| {n} | {r} |" for n, r in g]))
        out.append("\nPlacement alone does not override any lower-level or source-residue guard.\n")
    out = sec["shape"]
    shape_full = ["| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |", "|---|---:|---:|---:|---:|---:|---:|"]
    shape_now = ["| defect still in the clean tree | files | bytes | % of bytes |", "|---|---:|---:|---:|"]
    tot = sum(r["size"] for r in rs)
    import re as _re
    from pathlib import Path as _P
    PIN_RE = _re.compile(r"\bASM_([A-Z0-9_]+)\(")
    # one-trip blocks tracked as statement-macro bodies (owner 2026-10-06: decisions item 19 for pinned rows,
    # r97 decision 16 for the pin-free load-bearing ones) - listed in the ledgers, not counted as scaffolding
    _onetrip_tracked = set()
    for _lf in ("ledger/onetrip_barrier_rows.jsonl", "ledger/onetrip_loadbearing.jsonl"):
        if (ROOT / _lf).exists():
            _onetrip_tracked |= {json.loads(l)["id"] for l in open(ROOT / _lf) if l.strip()}
    with cache.phase("dependencies"):
        facts = FactInputs(ROOT, _levels)
    def cur_facts(r):
        if r.get("source_row"): return None   # link-list placement: its home's TU is counted once (placed_shapes adds the bytes)
        cp = layout_row_path(r, ROOT)
        p = cp if cp.exists() else ROOT / "raw" / r["container"] / _P(r["c_path"]).name
        if not p.exists(): return None
        t = p.read_text(errors="replace")
        def compute():
            return {"boiler": "This header contains macros emitted by m2c" in t or "typedef float f32;" in t,
                "m2c_field": len(_re.findall(r"(?<![A-Za-z0-9_])(?:M2C_)?FIELD\(", "\n".join(l for l in t.splitlines() if not l.lstrip().startswith("#")))),
                # through the pin machinery, not the raw text: PIN_RE also matches a pin note in a
                # comment and a local wrapper #define, so a row the campaign had freed kept
                # being counted and this column drifted from pin_watch and the sweep
                "pin_total": len(sites_of(t)), "pins_by": collections.Counter(s[1][4:] for s in sites_of(t)), "hidden": hidden_asm(t),
                "gotos": len(_re.findall(r"\bgoto\s+[A-Za-z_]", t)),
                "computed_goto": len(_re.findall(r"\bgoto\s*\*", t)), "inline_asm": len(_re.findall(r"__asm__|\basm\s*\(", strip_composite_asm(t))),   # minus the owner-kept composite spelling (r95 decisions item 8), counted on its own line below
                "composite_asm": len(composite_asm_spans(t)),
                "m2c_locals": len(set(_re.findall(r"\b(temp_[a-z0-9_]+|arg[0-9]|sp[0-9A-F]{2,}|var_[a-z0-9_]+|phi_[a-z0-9_]+)\b",
                                                 _re.sub(r"/\*.*?\*/|//[^\n]*", " ", t, flags=_re.S)))),   # code only (r78: struct notes like `/* arg0 in func_X */` inflated this 2,687 -> 785 rows)
                "n_local_structs": len(set(_re.findall(r"\b((?:S_|Struct|Func)[0-9A-F]{7,8}[A-Za-z0-9_]*)\b", t))),
                # LIVE, from the current text with the same functions levels.py uses (not `cen`, the census of the PINNED
                # raw text, which never moved with src/): "audit" = the L5 `fidelity_site` predicate (sites that still show a
                # defect), "audit_any" = every live audit site, unnarrowed.
                "audit": collections.Counter(x.split("|")[0] for x in _levels.live_fidelity_sites(r, t)),
                "audit_any": collections.Counter(x.split("|")[0] for x in _levels.live_audit_sites(r, t)),
                # r95: real noreturn tail calls only, not composite data aliases; 2026-10-14: minus byte-verified real calls
                "tail_idiom": sum((r["id"], tgt) not in _call_verified for tgt in _levels.real_tail_call_targets(t)),
                "dowhile0": 0 if r["id"] in _onetrip_tracked else len(_re.findall(r"\bdo\s*\{[^{}]*\}\s*while\s*\(\s*0\s*\)", t, _re.S)),
                "fakedep": _fakedep(t),
                "markers": sum(1 for _s in sites_of(t) if _s[1] in (
                    "ASM_TAILSLOT_PIN", "ASM_TAILSLOT_PIN_TIED", "ASM_PAGEBASE_PIN", "ASM_JALDELAY_PIN",
                    "ASM_LIVE_SIBCALL_PIN", "ASM_SHAPE_D_SIBCALL_PIN", "ASM_BRANCH_LABEL_SPLIT"))}
        with cache.phase("dependencies"):
            inputs = [r, text_key(t), facts.for_row(r), r["id"] in _onetrip_tracked,
                      sorted(tgt for rid, tgt in _call_verified if rid == r["id"])]
        return cache.get(r["id"], inputs, compute)
    _call_verified = _levels.call_verified_index()   # owner ruling 2026-10-14 (levels.py)
    curc = {r["id"]: cur_facts(r) for r in rs}
    cache.save()
    defs = [("m2c boilerplate block", lambda c: c["boiler"]), ("M2C_FIELD raw offsets", lambda c: c["m2c_field"] > 0), ("m2c local names", lambda c: c["m2c_locals"] > 0),
            ("ASM_ pins", lambda c: c["pin_total"] > 0), ("goto", lambda c: c["gotos"] > 0), ("computed-goto jump table", lambda c: c["computed_goto"] > 0),
            ("inline asm outside macros (clean: minus the composite-row carve debt, counted on its own line below)", lambda c: c["inline_asm"] > 0), ("fidelity blocking site, LABEL_AS_CALL/PASSTHRU_NO_ARGS (pin: baseline audit of the frozen text; clean: live, L5 predicate)", lambda c: any(k in ("LABEL_AS_CALL", "PASSTHRU_NO_ARGS") for k in c["audit"])),
            ("any fidelity site (pin: any baseline audit class; clean: live L5 `fidelity_site` predicate, = levels.py)", lambda c: bool(c["audit"])),
            ("any live audit site, unnarrowed (clean column only; pin column repeats the row above)", lambda c: bool(c.get("audit_any", c["audit"]))),
            ("noreturn tail-call spelling (scaffolding, docs/FIDELITY.md)", lambda c: c.get("tail_idiom", 0) > 0), ("maspsx marker pins (scaffolding)", lambda c: c.get("markers", 0) > 0),
            ("do{}while(0) scheduling barrier (scaffolding, pure C)", lambda c: c.get("dowhile0", 0) > 0),
            ("fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C)", lambda c: c.get("fakedep", 0) > 0),
            ("local address-named struct", lambda c: c["n_local_structs"] > 0),
            ("clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names)", lambda c: not c["boiler"] and c["m2c_field"] == 0 and c["pin_total"] == 0 and c["gotos"] == 0 and c["m2c_locals"] == 0)]
    for name, f in defs:
        sel = [by[i] for i, c in cen.items() if not c.get("missing") and f(dict(c, audit=c.get("audit_pin", c.get("audit", {}))))]   # pin column: the audit as it was at the pin
        b = sum(r["size"] for r in sel)
        # parked containers excluded like "Pin sites now" and the L4 line (r91_luna_offby1: ovmovie/func_80041044 made it 151 vs 150)
        sel2 = [by[i] for i, c in curc.items() if c and i.split("/")[0] not in PARKED_CONTAINERS and f(c)]
        b2 = sum(r["size"] for r in sel2 + placed_shapes(f, curc, by))   # files = TUs; bytes also cover the placements of a TU
        shape_full.append(f"| {name} | {len(sel)} | {b:,} | {100*b/tot:.1f}% | {len(sel2)} | {b2:,} | {100*b2/tot:.1f}% |")
        if sel2 or b2:
            shape_now.append(f"| {name.split(' (')[0]} | {len(sel2):,} | {b2:,} | {100*b2/tot:.1f}% |")
    pins = collections.Counter(); 
    for c in cen.values():
        for k, v in c.get("pins", {}).items(): pins[k] += v
    # `cen` is the census of the frozen text at the pin; the live count is the current tree's.
    # This line used to print only the former under the bare label "Pin sites" (25,788 against
    # 12,041 live on 2026-09-11), which read as the size of the remaining debt.
    # parked containers are listed, not counted (the ALL row above excludes them too)
    live ={i: c for i, c in curc.items() if c and i.split("/")[0] not in PARKED_CONTAINERS}
    pins = collections.Counter()
    for i, c in cen.items():
        if i.split("/")[0] not in PARKED_CONTAINERS:
            pins.update(c.get("pins", {}))
    now = collections.Counter()
    for c in live.values():
        now.update(c["pins_by"])
    out.append("## Code shape: what is left to clean in the C\n\nDefects still present in the current tree (files = source files, bytes = image bytes of the functions in them; "
               "the last row is the positive one). The comparison with the frozen first-pass text is collapsed below.\n")
    out.extend(shape_now)
    out.extend(_details("pinned first-pass text vs current tree, every defect", shape_full[:2], shape_full[2:]))
    out.append(f"\nPin sites now: {sum(now.values()):,} in {sum(1 for c in live.values() if c['pin_total']):,} rows; "
               + (", ".join(f"{k} {v:,}" for k, v in now.most_common(8)) or "none left")
               + f".  At the pin: {sum(pins.values()):,}; " + ", ".join(f"{k} {v:,}" for k, v in pins.most_common(8)) + ".\n")
    notes = sec["trade_notes"]; trade_tab = []   # (kind, count, ledger file): the compact table; `notes` keeps the full descriptions (lines some tools parse)
    out = notes
    hid = collections.Counter()
    for c in live.values(): hid.update(c["hidden"])
    _odd = [json.loads(l) for l in open(ROOT / "ledger/oddities.jsonl")] if (ROOT / "ledger/oddities.jsonl").exists() else []
    _ot = [json.loads(l) for l in open(ROOT / "ledger/onetrip_barrier_rows.jsonl")] if (ROOT / "ledger/onetrip_barrier_rows.jsonl").exists() else []
    _otl = [json.loads(l) for l in open(ROOT / "ledger/onetrip_loadbearing.jsonl") if l.strip()] if (ROOT / "ledger/onetrip_loadbearing.jsonl").exists() else []
    trade_tab += [("oddities (zero-byte fences retail needs)", f"{len(_odd)}", "ledger/oddities.jsonl"),
                  ("one-trip barrier rows", f"{len(_ot)}", "ledger/onetrip_barrier_rows.jsonl"),
                  ("load-bearing one-trip rows", f"{len(_otl)}", "ledger/onetrip_loadbearing.jsonl")]
    out.append(f"Tracked, not pins (owner 2026-10-06): oddities {len(_odd)} (ledger/oddities.jsonl - zero-byte fences retail needs, curiosities, "
               f"not removal targets: {', '.join(o['id'] for o in _odd) or '-'}); one-trip barrier rows {len(_ot)} (ledger/onetrip_barrier_rows.jsonl); "
               f"load-bearing one-trip rows {len(_otl)} (ledger/onetrip_loadbearing.jsonl, statement-macro bodies, not counted in the do{{}}while(0) row above).")
    _comp = [i for i, c in live.items() if c["composite_asm"]]
    trade_tab.append(("carve debt: composite rows", f"{sum(live[i]['composite_asm'] for i in _comp):,} statements in {len(_comp):,} rows", "tools/pin_census.py composite_asm_spans"))
    out.append(f"Carve debt - composite rows (r95 decisions item 8 kept the spelling for bytes; r99: it is an artifact of one-row-per-function "
               f"carving, owned by module placement): the `asm(\"func_X\")` data prefix (another function's jump table / overlay data that retail "
               f"places before this row's code) and its `.globl/.type/.size func_X` stamp (`pin_census.composite_asm_spans`), "
               f"{sum(live[i]['composite_asm'] for i in _comp):,} statements in {len(_comp):,} rows - counted here, not in the inline-asm row "
               f"above; still L5 `inline_asm` residue in levels.py until the module TU owns the data.")
    trade_tab.append(("hidden scaffolding (not pins)", f"{sum(hid.values()):,} sites ({hid['symbol-alias']:,} symbol aliases)", "pin_census.hidden_asm"))
    out.append(f"Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements {hid['raw-pin']:,}, "
               f"calls of local asm wrappers {hid['wrapper-call']:,}, hand-written asm in function bodies {hid['asm-code']:,} "
               f"(C that is missing); symbol aliases {hid['symbol-alias']:,} (a second typed name for one symbol: a missing type); "
               f"file-scope asm directives {hid['file-asm']:,}; file-scope global register variables {hid['reg-global']:,} "
               f"(`register T g asm(\"$R\")`).\n")
    nfl = collections.Counter(min(2, len([x for x in r["cfg"].replace("+", " ").split()[1:] if x.startswith(("-f", "-O", "-m"))]))
                          for r in rs if r["id"].split("/")[0] not in PARKED_CONTAINERS)
    trade_tab.append(("per-row optimization flags", f"{nfl[1]:,} rows with one, {nfl[2]:,} with two or more", "ledger/rows.jsonl"))
    out.append(f"Per-row optimization flags (weak evidence about the real build; each switch is undone from the "
               f"`t30_cellpins` journal's `cell_from`): {nfl[1]:,} rows carry one flag, {nfl[2]:,} carry two or more.\n")

    try:
        sec["compiler"].append(_recipe_tracker(rs, curc))
    except Exception as e:
        sec["compiler"].append(f"\n(recipe tracker unavailable: {e})")
    trades = list(read_jsonl(LEDGER / "recipe_trades.jsonl")) if (LEDGER / "recipe_trades.jsonl").exists() else []
    site_for_pin = sum(1 for t in trades if t.get("kind") == "site_for_pin")
    trade_tab.append(("site-for-pin trades", f"{site_for_pin:,}", "ledger/recipe_trades.jsonl"))
    out.append(f"Site-for-pin trades (`ledger/recipe_trades.jsonl` records shaped "
               f'`{{"kind":"site_for_pin","id":row,"site":"LABEL_AS_CALL|ITC|PASSTHRU","pin":macro,'
               f'"residue_without_pin":str,"at":iso,"note":str}}` -- one pin, or two when one is not enough '
               f'(owner ruling 2026-09-22 afternoon, "accept 2 pins") -- charter rule 3, "a pin moved elsewhere is not '
               f'a removal"; the trade is tracked, and L4 is where pins stop counting toward removal regardless): '
               f"{site_for_pin:,}.\n")
    dead_init = sum(1 for t in trades if t.get("kind") == "dead_init")
    trade_tab.append(("dead-initializer trades", f"{dead_init:,}", "ledger/recipe_trades.jsonl"))
    out.append(f"Dead-initializer trades (`ledger/recipe_trades.jsonl` records shaped "
               f'`{{"kind":"dead_init","id":row,"site":pins,"init":decl,"lane":lane,"at":iso,"note":str}}` -- a '
               f"never-read `= 0` at a declaration makes the variable multi-set; ordinary C by the owner ruling "
               f"2026-09-23, tracked as a spelling trade, informational, the pin count is unchanged; appended by "
               f"tools/apply_candidates.py at landing): {dead_init:,}.\n")

    unions_all = list(read_jsonl(LEDGER / "union_trades.jsonl")) if (LEDGER / "union_trades.jsonl").exists() else []
    unions = [u for u in unions_all if not u.get("resolved")]
    if unions_all:
        def _union_line(kind, label):
            sites = [u for u in unions if u.get("kind") == kind]
            per_row = collections.Counter(u["id"] for u in sites)
            live = sum(1 for r in per_row if not by.get(r, {}).get("source_row") and (layout_row_path(r, ROOT)).exists() and "union" in (layout_row_path(r, ROOT)).read_text(errors="replace"))
            top = ", ".join(f"{r.split('/')[-1]} {n}" for r, n in per_row.most_common(4))
            return f"{label}: {len(sites):,} sites in {len(per_row):,} rows ({live:,} rows still carry a union; most: {top})"
        trade_tab.append(("union trades (tracked, plausibility unproven)", f"{len(unions):,} open of {len(unions_all):,} sites", "ledger/union_trades.jsonl"))
        out.append("Union trades (`ledger/union_trades.jsonl`, owner 2026-10-13: kept as nicer-than-a-pin but TRACKED - their "
                   "plausibility as original 1997 code is unproven; census work/native_lane/_r118/union_census): "
                   + _union_line("union_idiom", "zero-init one-member idiom (accepted trade)") + "; "
                   + _union_line("union_host_merge", "host-merge levers (int/pointer share one union variable; owner ruling pending)")
                   + f". Resolved by re-spells (original-C shapes, byte-exact): {len(unions_all) - len(unions):,} of {len(unions_all):,} recorded sites."
                   + " Refused union levers (float launders, dead-value keepers) are recorded in the hard basket.\n")

    dead_branch = sorted({t["id"] for t in trades if t.get("kind") == "dead_branch"})
    if dead_branch:
        trade_tab.append(("dead-branch trades (decision 45)", f"{len(dead_branch):,} rows", "ledger/recipe_trades.jsonl"))
        out.append(f"Dead-branch trades (decision 45, owner 2026-10-13; `ledger/recipe_trades.jsonl` kind dead_branch - a one-arm "
                   f"`if (value) {{ local = 0; }}` over a retail-evidenced value whose arm sets a never-read local, reconstructing a "
                   f"set-but-unused leftover that jump2 deletes while delete_computation keeps the load): {len(dead_branch):,} rows "
                   f"({', '.join(r.split('/')[-1] for r in dead_branch)}).\n")

    dead_arm = sorted({t["id"] for t in trades if t.get("kind") == "dead_arm"})
    if dead_arm:
        trade_tab.append(("dead-arm trades (decision 46)", f"{len(dead_arm):,} rows", "ledger/recipe_trades.jsonl"))
        out.append(f"Dead-arm trades (decision 46, owner 2026-10-13; `ledger/recipe_trades.jsonl` kind dead_arm - a never-taken "
                   f"arm over a never-reassigned local that combine folds after flow counted it, so sched/global/reload still see "
                   f"it and jump2 deletes it; the arm body is a RECONSTRUCTION, only its shape is byte-evidenced): {len(dead_arm):,} rows "
                   f"({', '.join(r.split('/')[-1] for r in dead_arm)}).\n")

    from census import declared_void_callees, void_exact_targets, live_sites, audit_sites
    import census as _census_mod

    def _void_tiers():
        """Tier per symbol in config/void_callees.txt.  The file carries no per-line tier marker
        (checked): tier is read instead from its `# ---- tier A ...` / `# ---- tier B ...`
        section-header comments, the convention docs/L0_BLOCKED_PLAN_20260922.md section 6
        introduced it under."""
        tiers = {}; tier = None
        p = ROOT / "config" / "void_callees.txt"
        if p.exists():
            for line in p.read_text(errors="replace").splitlines():
                s = line.strip()
                if s.startswith("#"):
                    low = s.lower()
                    if "tier a" in low: tier = "A"
                    elif "tier b" in low: tier = "B"
                    continue
                tok = line.split("#", 1)[0].split()
                if tok and _re.fullmatch(r"func_[0-9A-F]{8}", tok[0]):
                    tiers[tok[0]] = tier or "A"
        return tiers

    tiers = _void_tiers()
    tier_a = sum(1 for t in tiers.values() if t == "A")
    tier_b = sum(1 for t in tiers.values() if t == "B")
    tier_drift = set(tiers) ^ declared_void_callees()   # cross-check against the reused census function
    tierB_syms = {s for s, t in tiers.items() if t == "B"}
    tb_rows = []
    if tierB_syms:
        full_void = void_exact_targets()          # census.declared_void_callees() unioned in, both tiers
        reduced_void = full_void - tierB_syms
        for r in rs:
            if r["container"] in PARKED_CONTAINERS or r.get("source_row"): continue   # a placement shares its home's TU (counted once)
            keys = [f"{r['container']}/{f}" for f in (r.get("defs") or [r["func"]])]
            pt_sites = []
            for k in keys:
                pt_sites += [s for s in audit_sites().get(k, []) if s.startswith("PASSTHRU_NO_ARGS|")]
            if not pt_sites: continue
            cpv = layout_row_path(r, ROOT)
            pv = cpv if cpv.exists() else ROOT / "raw" / r["container"] / _P(r["c_path"]).name
            if not pv.exists(): continue
            textv = pv.read_text(errors="replace")
            _census_mod._VOID_EXACT_TARGETS = full_void
            live_with = live_sites(textv, pt_sites)
            _census_mod._VOID_EXACT_TARGETS = reduced_void
            live_without = live_sites(textv, pt_sites)
            if not live_with and live_without:    # exempt with tier B, blocked again without it
                tb_rows.append(r)
        _census_mod._VOID_EXACT_TARGETS = full_void   # restore: every other call in this run sees both tiers
    tb_bytes = sum(r["size"] for r in tb_rows)
    trade_tab.append(("void callees (tier A in-tree / tier B explicit)", f"{tier_a} + {tier_b} symbols; {len(tb_rows)} rows rest on tier B", "config/void_callees.txt"))
    out.append(f"Void callees (`config/void_callees.txt`, tiers read from its section-header comments -- no "
               f"per-line marker exists): tier A {tier_a}, tier B {tier_b} symbols" +
               (f"; WARNING {len(tier_drift)} symbol(s) differ from `census.declared_void_callees()` -- header "
                f"parse drifted from the file" if tier_drift else " (matches `census.declared_void_callees()`)") +
               f". Rows whose PASSTHRU_NO_ARGS exemption rests on a tier-B symbol alone (blocked again if tier B "
               f"were dropped, tier-A/in-tree exemptions do not cover them): {len(tb_rows)} rows, {tb_bytes:,} B.\n")

    lv = LEDGER / "levels.jsonl"
    out = sec["levels"]
    out.append("## Readability levels (bytes at or above each level)\n")
    if lv.exists():
        level_rows = current_row_records(read_jsonl(lv), by)
        L = collections.Counter()
        for x in level_rows:
            for l in range(0, x["level"] + 1): L[l] += by[x["id"]]["size"]
        out.append("| level | bytes | % |\n|---|---:|---:|")
        for l in range(6): out.append(f"| L{l} | {L[l]:,} | {100*L[l]/tot:.1f}% |")
        out.append("\nL0 byte-exact, L1 no fidelity blockers, L2 typed field access, L3 readable body landed in `src/`, L4 zero pins and placed in a "
                   "module whose certificate is current, L5 nothing left (no fidelity site, goto table, inline asm or `NON_MATCHING`). Full definitions: docs/PLAN.md.")
        recs = [x for x in level_rows if x.get("records")]
        rb = sum(by[x["id"]]["size"] for x in recs)
        out.append(f"\nOn shared record headers (T7, `include/records/`): {len(recs)} rows, {rb:,} bytes ({100*rb/tot:.1f}%); "
                   f"records used: {len({r for x in recs for r in x['records']})}.")
        resid_n = collections.Counter(); resid_b = collections.Counter()
        for x in level_rows:
            if x["id"].split("/")[0] in PARKED_CONTAINERS: continue   # as "Pin sites now": the pins count must equal its row count
            for k in x.get("l4_residue", []):
                resid_n[k] += 1; resid_b[k] += by[x["id"]]["size"]
        out.append(f"\nL4 residue (rows below L4, by blocker; a row can carry more than one; parked containers excluded): "
                   f"pins {resid_n['pins']:,} rows ({resid_b['pins']:,} B), "
                   f"tail_jump {resid_n['tail_jump']:,} rows ({resid_b['tail_jump']:,} B), "
                   f"not_in_module {resid_n['not_in_module']:,} rows ({resid_b['not_in_module']:,} B).")
    else:
        exb = sum(r["size"] for r in rs if r["stock"] and (base.get(r["id"], {}).get("exact") is True or (r["kind"] == "slus" and base.get(r["id"], {}).get("status") == "ok")))
        out.append(f"L0 (verified byte-exact at the pin): {exb:,} bytes ({100*exb/tot:.1f}%). No transforms applied yet; every row is at L0.\n")
    out = sec["evidence"]
    try:
        from evidence import census as _ev_census
        ev = _ev_census().splitlines()
        i0 = next((i for i, l in enumerate(ev) if l.startswith("|")), None)
        if i0 is None:
            out.extend(_details("Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)", [], ev))
        else:
            out.extend(_details("Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)", ev[i0:i0 + 2], ev[i0 + 2:]))
        out.append("\nEvery lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.")
    except Exception as e:
        out.append(f"\n(evidence census unavailable: {type(e).__name__})")
    try:
        lvp = {l: 100 * L[l] / tot for l in range(6)} if lv.exists() else None
        sec["glance"].append(at_a_glance(denom, sorted({r["container"] for r in rs if r["container"] not in PARKED_CONTAINERS}, key=("slus", "main", "town", "dungeon", "ovmovie").index),
                                          slus_groups, ov_groups, coverage_summary(ROOT), sum(now.values()), sum(1 for c in live.values() if c["pin_total"]),
                                          sum(pins.values()), lvp))
    except Exception as e:
        sec["glance"].append(f"## At a glance\n\n(summary unavailable: {type(e).__name__})\n")
    try:
        sec["notyet"].append(not_yet_c_section(ROOT))
    except Exception as e:
        sec["notyet"].append(f"## Not yet C\n\n(summary unavailable: {type(e).__name__})\n")
    sec["trades"].extend(_details(f"Tracked spellings and trades: {len(trade_tab)} kinds (none is an assembler pin)", ["| kind | count | where recorded |", "|---|---|---|"],
                                  [f"| {k} | {n} | `{w}` |" for k, n, w in trade_tab]))
    sec["trades"].insert(0, "## Tracked spellings and trades\n\nChoices the tree keeps on purpose and tracks; none is an assembler pin. The compact table and the full descriptions are collapsed.\n")
    sec["trades"].extend(_details("full descriptions", [], sec.pop("trade_notes")))
    sec["proof"].insert(0, "## How a match is proven\n")
    sec["proof"].insert(1, PROOF_TEXT)
    sec["proof"][2:] = _details("How rows are verified", [], sec["proof"][2:])
    sec["proof"].append(READ_NEXT)
    out = [x for part in sec.values() for x in part + [""]]
    (ROOT / "STATUS.md").write_text("\n".join(out) + "\n")
    print("\n".join(out))
    try:   # src/<container>/INDEX.md mirrors the ledger (stale since import until 2026-10-01)
        import gen_src_index
        gen_src_index.main()
    except Exception as e:
        print(f"(src INDEX.md not regenerated: {e})")

if __name__ == "__main__":
    main()
