#!/usr/bin/env python3
"""Naming and module evidence for every row -> ledger/evidence/ (docs/EVIDENCE.md is the index).

Sources, all in-tree once imported:
  docs/evidence/konami_assertion_sites.csv   Konami/Sony assert()/mark()/"%s = %d" sites left on the disc:
                                             real source file + line, and real identifier text (ost_w, cdhd_cnt, ...)
  ledger/evidence/adrando_map.json           the De-Randomizer's address map as facts (name, disc offset, RAM, layouts)
  ledger/evidence/knowledge/<func>.json      prior per-function notes carried over (doc, globals, calls)
  baserom/slus_006.14                        resident pointer tables (event-script VM handler table and friends)
  config/names.tsv                           applied function renames with their evidence

Commands:
  import --adrando-constants F --knowledge-dir D   one-time import (paths on the command line; nothing standing)
  build                                            (re)derive ledger/evidence/{assertions.jsonl,dev_identifiers.json,
                                                   vm_tables.json,rows.jsonl} from the in-tree sources
  show <row-id>                                    print the evidence block a lane receives for one row
  census                                           coverage table (markdown) for STATUS.md
  symbols                                          write docs/SYMBOLS.md, the human-readable catalogue
"""
import argparse, csv, json, re, struct, sys
from collections import defaultdict, Counter
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, read_jsonl, write_jsonl

EV = LEDGER / "evidence"
DOCS = ROOT / "docs" / "evidence"
CSV = DOCS / "konami_assertion_sites.csv"
CONT = {"TOWN.BIN": "town", "MAIN.BIN": "main", "DUNGEON.BIN": "dungeon", "OVMOVIE.BIN": "ovmovie"}
SLUS_LO, SLUS_HI = 0x8002D000, 0x8008B000

# Real identifiers printed by the shipped debug macros (docs/evidence/konami_assertion_sites.md §3.3, §4.1, §6, §7).
# The meaning column is what the catalogue could establish; "unnamed object" means the owning .c file is not known.
IDENTIFIERS = {
    "((u_long)p - (u_long)ost_w)/ sizeof(OSETDT)":   ("main.c",     "OSETDT = object-set table record type; ost_w = the object-set table (array of OSETDT); p indexes it"),
    "((u_long)pp - (u_long)osel_w)/ sizeof(OSETDT*)": ("main.c",     "osel_w = object-select array (OSETDT* pointers parallel to ost_w); pp indexes it"),
    "cdhd_cnt":            ("main.c",     "CD-header counter (global)"),
    "ov_work.kind":        ("sn_main.c",  "ov_work = overlay work struct (devkit scene tool), .kind = overlay kind"),
    "p->kind":             ("sn_main.c",  "kind field of the object pointed to by p (devkit scene tool)"),
    "kind":                ("flgtst.c?",  "devkit blob, probably flgtst.c (inferred)"),
    "mode":                ("flgtst.c?",  "devkit blob, probably flgtst.c (inferred)"),
    "sno":                 ("flgtst.c?",  "scene/sequence number, devkit blob, probably flgtst.c (inferred)"),
    "head":                ("(unnamed object before lshop.o)", "list head; same function also prints ptr[n].vx / ptr[n].vy -> a vertex array walker"),
    "ptr[n].vx":           ("(unnamed object before lshop.o)", "vertex array element x (PSY-Q SVECTOR/DVECTOR .vx)"),
    "ptr[n].vy":           ("(unnamed object before lshop.o)", "vertex array element y"),
    "s0[0]": ("(unnamed object between main.o and player.o)", "first element of string/array s0"),
    "s1[0]": ("(unnamed object between main.o and player.o)", "first element of string/array s1"),
    "s[0]":  ("(unnamed object between main.o and player.o)", "first element of string/array s"),
    "(int)gsw->check_sum": ("(MAIN.BIN devkit module)", "gsw = game-save work struct, .check_sum = save checksum"),
    "card_first_flg":      ("c_server.c", "Sony libcard: first-access flag"),
    "cnt":                 ("c_server.c", "Sony libcard: a counter"),
}
SOURCE_FILES = {
    "main.c":   "Konami town-scene main (linked into every one of the 54 TOWN event-script modules; two revisions: lines 40/55 in 47 modules, 39/54 in 7)",
    "lshop.c":  "Konami shop code (small file; assertions at lines 65, 113, 118, 128 in three consecutive functions; linked before main.o)",
    "player.c": "Konami player code (assert at line 64; linked after main.o)",
    "tobjs.c":  "Konami devkit scene tool: town objects (TOWN.BIN devkit blob, not shipped game code)",
    "sn_main.c": "Konami devkit scene tool main (mark: trace macro, devkit blob)",
    "flgtst.c": "Konami devkit flag test (mark: trace macro, devkit blob)",
    "c_server.c": "Sony libcard card server (MAIN.BIN; shipped copy at 0x80020000 and a devkit copy at 0x80400000)",
    "card_mes.c": "Konami memory-card UI: messages (MAIN.BIN devkit module)",
    "card_opt.c": "Konami memory-card UI: options (MAIN.BIN devkit module)",
    "card_win.c": "Konami memory-card UI: windows (MAIN.BIN devkit module)",
    "cardbk.c":  "Konami memory-card UI: background (MAIN.BIN devkit module)",
    "cardinfo.c": "Konami memory-card UI: info (MAIN.BIN devkit module)",
    "cardslot.c": "Konami memory-card UI: slots (MAIN.BIN devkit module)",
    "cardsme.c": "Konami memory-card UI (MAIN.BIN devkit module)",
    "memory.c":  "Konami memory-card module (MAIN.BIN devkit module; a code-only copy in TOWN.BIN)",
}
DEV_STRINGS = [  # §7.1 of the catalogue: other developer strings, with container file offsets
    {"string": "\\vx035\\data\\town\\sb43s000.bin, \\vx035\\data\\town\\sb06.bin", "container": "town", "foff": ["0x65281C", "0x65283C"], "note": "developer volume \\vx035; town map data files"},
    {"string": "\\vx035\\data\\sn\\SENGEI00.BIN .. SENGEI10.BIN (11)", "container": "town", "foff": ["0x7F877C-0x7F8894"], "note": "scene data files (sn = scene), devkit blob path table"},
    {"string": "\\vx035\\data\\town\\st.bin (6)", "container": "town", "foff": ["0x8CD128", "0x8CE128", "0x8CF124", "0x8D0124", "0x8D1124", "0x8D21E8"], "note": ""},
    {"string": "\\vx035\\data\\sn\\mv05.bin", "container": "town", "foff": ["0x8D20FC"], "note": ""},
    {"string": "GAME OVER (4)", "container": "town", "foff": ["0x78BA94", "0x796030", "0x796070", "0x7960B4"], "note": ""},
    {"string": "BASLUS-00614", "container": "main", "foff": ["0x264F20"], "note": "save file name, shipped image, vram 0x80027F20"},
    {"string": "BISLPS-00001", "container": "main", "foff": ["0x271AA8"], "note": "leftover JP save name, devkit image, vram 0x80408AA8"},
    {"string": "CHAN %x, CARD STATUS0/1 %x, illegal data", "container": "main", "foff": ["0x269090", "0x2690BC", "0x2690D0", "0x269138"], "note": "devkit image card diagnostics"},
    {"string": "bu10: / bu00:", "container": "main", "foff": ["0x25D074", "0x25D07C", "0x2690E4", "0x2690EC"], "note": "libcard device names"},
    {"string": "$Id: intr.c,v 1.76 / bios.c,v 1.86 / sys.c,v 1.129", "container": "slus", "foff": ["0x6AC8", "0x6D78", "0x6EFC"], "note": "PSY-Q library RCS ids"},
]
# Resident pointer tables (docs/evidence: exe_census §2.2). (vram, file offset in slus_006.14, entries, role)
VM_TABLES = [
    ("0x8006AA90", 0x3E290, 89, "event-script VM handler table: entry i = handler for opcode i; four slots share the 8-byte 'unimplemented opcode' stub; the 89th word is the default/terminator (state-transition dispatcher)"),
    ("0x8006AC9C", 0x3E49C, 19, "resident function-pointer table (role not yet named)"),
    ("0x8006AD74", 0x3E574, 12, "resident function-pointer table (role not yet named)"),
    ("0x8006B01C", 0x3E81C, 33, "resident function-pointer table (role not yet named)"),
    ("0x8007AED8", 0x4E6D8, 40, "resident function-pointer table (role not yet named)"),
    ("0x8008077C", 0x53F7C, 16, "resident function-pointer table (role not yet named)"),
]

# ---- the script symbol dump (TOWN.BIN devkit blob): 36-byte records, u32 value + char name[32] ----
SYM_NAME = re.compile(rb"^[A-Za-z_][A-Za-z0-9_]*$")
FAMILIES = {  # prefix: (what the numbers are, how the repo uses them)
    "FNO_": ("script function numbers: the town event-script VM calls C functions by number through a dispatch table (entry = number - 100); the text after FNO_ is the developer's name of that C function", "function names (ledger/evidence/names_proposed.tsv), per-row evidence"),
    "F_": ("event flag numbers (index into the save-game event-flag array); F_act_<npc> are the actor flags, F_<scene>_* scene flags", "flag constants (include/script_symbols.h) wherever a flag test/set call takes a literal"),
    "Ftt_": ("event flags, talk-table variant (same number space)", "flag constants"),
    "Ft_": ("event flags, talk variant", "flag constants"), "Fr_": ("event flags, reserve variant", "flag constants"),
    "Fc_": ("event flags, count/clear variant", "flag constants"), "Fp_": ("event flags, pool/person variant", "flag constants"),
    "Fost_": ("event flag, object-set variant", "flag constants"), "Fo_": ("event flag", "flag constants"), "Frg_": ("event flag", "flag constants"),
    "GOODS_": ("shop goods save flags (GOODS_SAVE_FLG_NN), in the flag number space", "flag constants"),
    "mamonogoya_": ("monster-hut (mamono-goya) flags and status slots; 0x8000-based numbers are a second flag bank", "flag constants"),
    "SSTP_": ("scene step ids: the per-scene state-machine steps the scripts wait on (SSTP_ANGEL_APPEAR ...)", "step constants and scene summaries"),
    "IMG_": ("portrait image ids per character (IMG_B<name>_<pose>; 0..12 within each character's set)", "image constants"),
    "S_": ("script system-call numbers: the VM's built-in operations (S_open_shop, S_flgtst, S_rand_sn, S_printf/S_sprintf/S_getchar/S_exit ...)", "opcode/builtin names for the VM handlers"),
    "V_": ("script variable slots (V_sys, V_gamew2, V_pobj, V_pad03..)", "variable-slot constants"),
    "sn_": ("scene numbers and scene switches (sn_win_sw0.., sn_open_*)", "scene constants"),
    "PSN_": ("person (NPC) demo-motion commands PSN_DM_* (home position, talk, walk a way, jump, display on/off, delete)", "NPC command constants"),
    "ANM_": ("animation ids paired with the PSN_DM commands", "animation constants"), "ANMWAY_": ("facing directions (down/left/up/right)", "direction constants"),
    "mam_": ("mama's first-talk ids", "constants"), "fg_": ("opening-demo end flags", "flag constants"), "SB01_": ("scene sb01 steps", "step constants"),
    "func_": ("town-map function numbers (func_town_map_reset/del/set)", "constants"), "P_": ("person ids (cheriru scenes)", "constants"),
    "Arg_": ("script argument slots (mode, pno, sno)", "constants"), "snf_": ("script booleans", "constants"), "TB_": ("table ids", "constants"),
    "Mode_": ("person modes", "constants"), "NUM_": ("counts (NUM_SN_VAR_WORK)", "constants"), "DFLT_": ("defaults", "constants"),
    "SHOW970906_": ("build tag: the 1997-09-06 show version", "provenance"),
}
def family_of(name):
    m = re.match(r"(_?[A-Za-z0-9]+_)", name); f = m.group(1) if m else ""
    return f if f in FAMILIES else (f.lstrip("_") if f.lstrip("_") in FAMILIES else f or "(other)")

def parse_symbol_tables(b: bytes):
    """Runs of >= 3 consecutive 36-byte records (u32 value, NUL-padded 32-byte identifier)."""
    tables, cur, i, n = [], [], 0, len(b)
    while i + 36 <= n:
        v = struct.unpack_from("<I", b, i)[0]; nm = b[i + 4:i + 36]; z = nm.find(b"\0")
        if z > 0 and SYM_NAME.match(nm[:z]) and not any(nm[z:]):
            cur.append({"file_offset": f"0x{i:X}", "value": v, "name": nm[:z].decode()}); i += 36
        else:
            if len(cur) >= 3: tables.append(cur)
            cur = []; i += 4
    if len(cur) >= 3: tables.append(cur)
    return tables

def detect_fno_table(b: bytes, rs, fno_names):
    """The dispatch table the script VM indexes with (number - 100): the run of pointer words whose
    named-number entries land on known function starts most often. Returns the entry list."""
    town = [r for r in rs if r["container"] == "town" and r.get("foff") is not None]
    by_foff = {r["foff"]: r for r in town}
    anch = [(r["foff"], int(r["true_name"][5:], 16) - r["foff"]) for r in town if r.get("true_name")]
    idx = _addr_index(rs); names = _names()
    n = len(b) // 4; W = struct.unpack_from(f"<{n}I", b, 0)
    runs, run, start = [], 0, 0
    for i, w in enumerate(W):
        if 0x8002D000 <= w < 0x80200000 and w % 4 == 0:
            if run == 0: start = i
            run += 1
        else:
            if run >= 112: runs.append((start * 4, run))
            run = 0
    best = None
    for foff, nn in runs:
        a = min(anch, key=lambda t: abs(t[0] - foff)); delta = a[1]
        ws = W[foff // 4: foff // 4 + nn]
        hits = sum(1 for i, w in enumerate(ws) if (i + 100) in fno_names and ((w - delta) in by_foff or _lookup(idx, "slus", w)))
        if best is None or hits > best[0]: best = (hits, foff, nn, delta, ws)
    if not best: return None
    hits, foff, nn, delta, ws = best
    stub = Counter(ws).most_common(1)[0][0] if Counter(ws).most_common(1)[0][1] > 4 else None
    ents = []
    for i, w in enumerate(ws):
        r = by_foff.get(w - delta); res = _lookup(idx, "slus", w)
        ents.append({"number": i + 100, "symbol": fno_names.get(i + 100), "dev_name": fno_names[i + 100][4:] if (i + 100) in fno_names else None,
                     "target": f"0x{w:08X}", "row": r["id"] if r else (res[0] if res and res[2] == 0 else None),
                     "row_func": r["func"] if r else (names.get(res[1], (res[1],))[0] if res and res[2] == 0 else None),
                     "stub": w == stub})
    return {"file_offset": f"0x{foff:X}", "vram": f"0x{foff + delta:08X}", "entries": nn, "index": "number - 100",
            "named_numbers_on_function_starts": f"{hits}/{sum(1 for k in fno_names if 100 <= k < 100 + nn)}",
            "stub_target": f"0x{stub:08X}" if stub else None, "table": ents}

def import_town_symbols(town_bin):
    b = Path(town_bin).read_bytes(); tabs = parse_symbol_tables(b)
    recs = [dict(r, family=family_of(r["name"])) for t in tabs for r in t]
    fam = Counter(r["family"] for r in recs)
    (EV / "script_symbols.json").write_text(json.dumps({
        "source": "TOWN.BIN devkit blob: the scene tool's symbol dump, 36-byte records (u32 value + 32-byte name); identical on the Japanese disc (one name fewer)",
        "tables": [{"file_offset": t[0]["file_offset"], "records": len(t)} for t in tabs],
        "families": {k: {"count": v, "what": FAMILIES.get(k, ("", ""))[0], "use": FAMILIES.get(k, ("", ""))[1]} for k, v in fam.most_common()},
        "records": recs}, indent=1) + "\n")
    with (DOCS / "script_symbols.tsv").open("w") as f:
        f.write("name\tvalue\tfamily\tfile_offset\n")
        for r in recs: f.write(f"{r['name']}\t{r['value']}\t{r['family']}\t{r['file_offset']}\n")
    fno = {r["value"]: r["name"] for r in recs if r["name"].startswith("FNO_")}
    ft = detect_fno_table(b, rows(), fno)
    if ft: (EV / "fno_table.json").write_text(json.dumps(ft, indent=1) + "\n")
    # a header of the constants, for the L4 lanes (not included by anything until a lane proves a literal is one of these)
    H = ["/* Generated by tools/evidence.py from the script symbol dump Konami left in TOWN.BIN (docs/SYMBOLS.md).",
         " * Values are the developer's own numbers: event flags (F_*), goods flags, scene steps (SSTP_*), script",
         " * system calls (S_*), function numbers (FNO_*), person commands (PSN_DM_*) ... Include it only where a", " * literal has been proven to be one of these. */", "#ifndef SCRIPT_SYMBOLS_H", "#define SCRIPT_SYMBOLS_H", ""]
    seen = set()
    for r in recs:
        if r["name"] in seen: continue
        seen.add(r["name"]); H.append(f"#define {r['name']} {r['value']}")
    H += ["", "#endif", ""]
    (ROOT / "include" / "script_symbols.h").write_text("\n".join(H))
    print(f"script symbols: {len(recs)} records in {len(tabs)} tables; families {fam.most_common(8)}")
    if ft: print(f"FNO dispatch table: {ft['file_offset']} (vram {ft['vram']}), {ft['entries']} entries, named numbers on function starts {ft['named_numbers_on_function_starts']}, stub {ft['stub_target']}")

def _names():
    out = {}
    p = ROOT / "config" / "names.tsv"
    if p.exists():
        for l in p.read_text().splitlines():
            if l.startswith("#") or not l.strip(): continue
            f = l.split("\t")
            if len(f) >= 4: out[f[1]] = (f[2], f[3])
    return out

def _addr_index(rs):
    """(container, start, end, row_id, symbol) for every function the tree knows an address for."""
    sizes = json.loads((ROOT / "config" / "func_sizes.json").read_text()) if (ROOT / "config" / "func_sizes.json").exists() else {}
    idx = []
    for r in rs:
        if r["container"] == "slus":
            for d in (r.get("defs") or ([r["func"]] if r.get("func") else [])):
                a = int(d[5:], 16); idx.append(("slus", a, a + sizes.get(d, 4), r["id"], d))
        elif r.get("true_name") and r["true_name"].startswith("func_"):
            a = int(r["true_name"][5:], 16); idx.append((r["container"], a, a + r["size"], r["id"], r["func"]))
    idx.sort(key=lambda t: (t[0], t[1]))
    return idx

def _lookup(idx, cont, addr):
    for c, a, b, rid, sym in idx:
        if c == cont and a <= addr < b: return rid, sym, addr - a
    return None

def _iso_files():
    """{path: (lba, size)} of every file on the disc image (raw 2352-byte sectors), path like 'TOWN/TOWN.BIN'."""
    imgs = sorted((ROOT / "bin").glob("*.bin"), key=lambda p: p.stat().st_size, reverse=True) if (ROOT / "bin").exists() else []
    if not imgs: return {}
    with open(imgs[0], "rb") as f:
        def sector(n):
            f.seek(n * 2352 + 0x18); return f.read(2048)
        pvd = sector(16)
        if pvd[1:6] != b"CD001": return {}
        out = {}
        def walk(lba, size, prefix):
            data = b"".join(sector(lba + i) for i in range((size + 2047) // 2048)); i = 0
            while i < len(data):
                n = data[i]
                if n == 0:
                    i = (i // 2048 + 1) * 2048; continue
                rec = data[i:i + n]; flags = rec[25]; nl = rec[32]; raw = rec[33:33 + nl]
                i += n
                if raw in (b"\x00", b"\x01"): continue
                name = raw.decode("latin1").split(";")[0]; l = struct.unpack_from("<I", rec, 2)[0]; s = struct.unpack_from("<I", rec, 10)[0]
                if flags & 2: walk(l, s, prefix + name + "/")
                else: out[prefix + name] = (l, s)
        root = pvd[156:190]; walk(struct.unpack_from("<I", root, 2)[0], struct.unpack_from("<I", root, 10)[0], "")
        return out

def _disc_to_file(files, off):
    """raw disc-image offset -> (file name, file offset) or None."""
    sec, rem = divmod(off, 2352); rem -= 0x18
    if rem < 0 or rem >= 2048: return None
    for name, (lba, size) in files.items():
        if lba <= sec < lba + (size + 2047) // 2048:
            return name, (sec - lba) * 2048 + rem
    return None

def cmd_import(a):
    EV.mkdir(parents=True, exist_ok=True)
    if a.adrando_constants:
        t = Path(a.adrando_constants).read_text()
        def block(name):
            m = re.search(r"const %s = \{(.*?)\n  \}" % re.escape(name), t, re.S); return m.group(1) if m else ""
        def kv(body, hexval=True):
            out = []
            for l in body.splitlines():
                m = re.match(r"\s*([A-Za-z0-9_]+):\s*(0x[0-9a-fA-F]+|\d+)\s*,?\s*(?://\s*(.*))?$", l)
                if m: out.append((m.group(1), int(m.group(2), 0), (m.group(3) or "").strip()))
            return out
        rom = []
        for name, off, note in kv(block("romAddresses")):
            m = re.match(r"RAM (0x[0-9a-fA-F]+)\s*(.*)", note); ram = int(m.group(1), 16) if m else None
            rom.append({"name": name, "disc_offset": f"0x{off:X}", "ram": f"0x{ram:08X}" if ram else None, "note": (m.group(2) if m else note).strip()})
        adr = {"source": "Azure Dreams De-Randomizer (ProGrammar-R, MPL-2.0): facts about the retail binary only, no code",
               "offset_scheme": "disc_offset = raw disc-image byte offset (2352-byte sectors); ram = load address where the map states it",
               "romAddresses": rom,
               "rowLength": {k: v for k, v, _ in kv(block("rowLength"))},
               "monsterStats_layout": {k: v for k, v, _ in kv(block("monsterStats"))},
               "item_TYPE": {k: v for k, v, _ in kv(block("TYPE"))},
               "TRAP_TYPES": {k: v for k, v, _ in kv(block("TRAP_TYPES"))},
               "spells": {k: v for k, v, _ in kv(block("spells"))},
               "lcgConstants": {"modulus": "0x1fffFFFFffff", "multiplier": "0x5DEECE66D", "increment": 11}}
        (EV / "adrando_map.json").write_text(json.dumps(adr, indent=1) + "\n")
        print(f"adrando_map.json: {len(rom)} romAddresses, layouts {list(adr['rowLength'])}")
    if a.town_bin:
        import_town_symbols(a.town_bin)
    if a.knowledge_dir:
        kd = EV / "knowledge"; kd.mkdir(exist_ok=True); n = 0
        for p in sorted(Path(a.knowledge_dir).glob("func_*.json")):
            d = json.loads(p.read_text())
            keep = {k: d[k] for k in ("func", "doc", "globals", "calls") if k in d}
            if not any(k in keep for k in ("doc", "globals", "calls")): continue
            s = json.dumps(keep, indent=1) + "\n"
            if ("/" + "home/") in s: continue   # keep private paths out of the tree
            (kd / p.name).write_text(s); n += 1
        print(f"knowledge: {n} files with doc/globals/calls")

def build():
    EV.mkdir(parents=True, exist_ok=True)
    rs = rows(); by_id = {r["id"]: r for r in rs}
    by_foff = {(r["container"], r["foff"]): r for r in rs if r.get("foff") is not None}
    by_true = defaultdict(list)
    for r in rs:
        if r.get("true_name"): by_true[(r["container"], r["true_name"])].append(r)
    names = _names(); idx = _addr_index(rs)
    per = defaultdict(lambda: {"assert_sites": [], "identifiers": [], "knowledge": [], "adrando": [], "data": [], "vm": [], "name": [], "script_function": []})
    # 1. assertion sites -> rows (by container+foff for the representative copy, by true_name for retired duplicates)
    asserts, unowned = [], []
    if CSV.exists():
        for s in csv.DictReader(CSV.open()):
            cont = CONT[s["container"]]; foff = int(s["containing_func_foff"], 16)
            site = {"source_file": s["source_file"] or None, "line": int(s["line"]) if s["line"] else None, "kind": s["kind"],
                    "expression": s["expression_or_null"] or None, "distinct_id": s["distinct_id"], "site_vram": s["site_vram"],
                    "copy_foff": s["containing_func_foff"], "copy_func": s["containing_function"], "attribution": s["attribution"]}
            r = by_foff.get((cont, foff))
            targets = [r] if r else by_true.get((cont, s["true_name"]), []) if s["true_name"] else []
            if not targets and s["true_name"]:   # a retired copy whose representative lives in another container
                targets = [x for k, v in by_true.items() if k[1] == s["true_name"] for x in v]
            if not targets:
                unowned.append(dict(site, container=cont, true_name=s["true_name"] or None, func_status=s["func_status"], size=int(s["containing_func_size"] or 0)))
                continue
            for r in targets:
                site2 = dict(site, own_copy=(r is by_foff.get((cont, foff))))
                per[r["id"]]["assert_sites"].append(site2)
        for rid, e in per.items():
            r = by_id[rid]
            sites = e["assert_sites"]
            if not sites: continue
            d = {}
            for s in sites:
                k = (s["source_file"], s["line"], s["kind"], s["expression"])
                d.setdefault(k, {"source_file": k[0], "line": k[1], "kind": k[2], "expression": k[3], "copies": 0, "distinct_id": s["distinct_id"]})["copies"] += 1
            files = sorted({s["source_file"] for s in sites if s["source_file"]})
            exprs = sorted({s["expression"] for s in sites if s["expression"]})
            asserts.append({"id": rid, "container": r["container"], "func": r["func"], "true_name": r.get("true_name"), "size": r["size"],
                            "source_files": files, "lines": sorted({(s["source_file"], s["line"]) for s in sites if s["line"]}),
                            "expressions": exprs, "sites": sorted(d.values(), key=lambda x: (x["source_file"] or "", x["line"] or 0, x["expression"] or "")),
                            "copies": len(sites)})
            for x in exprs:
                meta = IDENTIFIERS.get(x)
                per[rid]["identifiers"].append({"text": x, "file": meta[0] if meta else None, "meaning": meta[1] if meta else None})
    asserts.sort(key=lambda x: (x["container"], x["func"]))
    write_jsonl(EV / "assertions.jsonl", asserts)
    (EV / "assertions_unowned.json").write_text(json.dumps(unowned, indent=1) + "\n")
    (EV / "dev_identifiers.json").write_text(json.dumps({
        "note": "Real identifier text printed by Konami's shipped debug macros; each entry lists the rows whose function prints it (docs/evidence/konami_assertion_sites.md).",
        "identifiers": [{"text": k, "file": v[0], "meaning": v[1], "rows": sorted(rid for rid, e in per.items() if any(i["text"] == k for i in e["identifiers"]))} for k, v in IDENTIFIERS.items()],
        "source_files": SOURCE_FILES, "developer_strings": DEV_STRINGS}, indent=1) + "\n")
    # 2. adrando map -> rows by address
    adr_p = EV / "adrando_map.json"; adr_hits = 0
    if adr_p.exists():
        adr = json.loads(adr_p.read_text()); files = _iso_files()
        fmap = {"SLUS_006.14": "slus", "MAIN/MAIN.BIN": "main", "TOWN/TOWN.BIN": "town", "DUNGEON/DUNGEON.BIN": "dungeon", "OVMOVIE.BIN": "ovmovie"}
        for e in adr["romAddresses"]:
            loc = _disc_to_file(files, int(e["disc_offset"], 16)) if files else None
            e["file"] = loc[0] if loc else None; e["file_offset"] = f"0x{loc[1]:X}" if loc else None
            e["row"] = None
            if e["ram"]:
                ram = int(e["ram"], 16)
                conts = ["slus"] if SLUS_LO <= ram < SLUS_HI else ([fmap[loc[0]]] if loc and loc[0] in fmap else ["main", "town", "dungeon"])
                for c in conts:
                    hit = _lookup(idx, c, ram)
                    if hit:
                        e["row"], e["symbol"], e["offset_in_function"] = hit[0], hit[1], hit[2]
                        per[hit[0]]["adrando"].append({"name": e["name"], "ram": e["ram"], "offset_in_function": hit[2], "note": e["note"]}); adr_hits += 1
                        break
        data = [e for e in adr["romAddresses"] if e["ram"] and not e["row"]]
        from common import current_text
        want = {f"D_{int(e['ram'], 16):08X}": e for e in data}
        pat = re.compile(r"\b(D_[0-9A-F]{8})\b")
        for r in rs:
            try: txt = current_text(r)
            except Exception: continue
            for sym in set(pat.findall(txt)):
                e = want.get(sym)
                if e:
                    lay = adr["rowLength"].get({"initialStatsTable": "initialStats", "trapTable": "trap", "statGrowthTable": "statGrowth"}.get(e["name"], ""))
                    per[r["id"]]["data"].append({"symbol": sym, "name": e["name"], "ram": e["ram"], "record_bytes": lay,
                                                 "layout": adr["monsterStats_layout"] if e["name"] == "initialStatsTable" else None, "note": e["note"]})
                    e.setdefault("rows", []).append(r["id"])
        adr_p.write_text(json.dumps(adr, indent=1) + "\n")
    # 3. resident pointer tables
    slus = ROOT / "baserom" / "slus_006.14"; tables = []
    if slus.exists():
        b = slus.read_bytes()
        for vram, foff, n, role in VM_TABLES:
            ws = struct.unpack_from("<%dI" % n, b, foff); ents = []
            for i, w in enumerate(ws):
                hit = _lookup(idx, "slus", w); sym = f"func_{w:08X}"
                ents.append({"index": i, "target": f"0x{w:08X}", "row": hit[0] if hit else None, "symbol": (names.get(sym, (sym,))[0]) if hit and hit[2] == 0 else (hit[1] if hit else None)})
                if hit and hit[2] == 0: per[hit[0]]["vm"].append({"table": vram, "index": i, "role": role.split(":")[0]})
            tables.append({"vram": vram, "file_offset": f"0x{foff:X}", "entries": n, "role": role, "targets": ents})
    (EV / "vm_tables.json").write_text(json.dumps(tables, indent=1) + "\n")
    # 4. knowledge notes (by nominal func name, or by the renamed symbol through names.tsv)
    kd = EV / "knowledge"; k_hits = 0
    if kd.exists():
        sym_to_rows = defaultdict(list)
        for c, a, bnd, rid, sym in idx: sym_to_rows[sym].append(rid)
        for r in rs:
            if r.get("func"): sym_to_rows[r["func"]].append(r["id"])
        for p in kd.glob("func_*.json"):
            d = json.loads(p.read_text()); f = p.stem
            if str(d.get("doc", "")).strip().lower() in ("", "n/a", "none", "tbd") and not d.get("globals") and not d.get("calls"): continue
            note = {"func": f, **{k: d[k] for k in ("doc", "globals", "calls") if k in d}}
            if str(note.get("doc", "")).strip().lower() in ("", "n/a", "none", "tbd"): note.pop("doc", None)
            for rid in dict.fromkeys(sym_to_rows.get(f, [])):
                per[rid]["knowledge"].append(note); k_hits += 1
    # 4b. script function numbers -> the functions the town dispatch table names
    ftp = EV / "fno_table.json"
    if ftp.exists():
        ft = json.loads(ftp.read_text()); prop = []
        for e in ft["table"]:
            if not e["row"]: continue
            if e["stub"]:
                per[e["row"]]["script_function"].append({"number": e["number"], "dev_name": None, "stub": True, "table": ft["vram"]})
                continue
            per[e["row"]]["script_function"].append({"number": e["number"], "dev_name": e["dev_name"], "symbol": e["symbol"], "stub": False, "table": ft["vram"]})
            if e["dev_name"] and not e["dev_name"].startswith("nouse") and e["row_func"] and e["row_func"].startswith("func_"):
                new = e["dev_name"]; note = ""
                if new.startswith("func_"): new = "scr_" + new; note = " (developer name starts with func_, which the alias mechanism reserves; prefixed scr_)"
                prop.append(f"0x{int(e['row_func'][5:], 16):08X}\t{e['row_func']}\t{new}\tscript function number {e['number']}: dispatch table {ft['vram']} entry {e['number'] - 100} = this function; developer symbol {e['symbol']} (TOWN.BIN symbol dump){note}")
        (EV / "names_proposed.tsv").write_text("# Proposed function renames from the script symbol dump (docs/SYMBOLS.md §5). Same columns as config/names.tsv;\n# apply at L4 with the gate (tools/build/ccproc.py alias mechanism). Not applied yet.\n" + "\n".join(prop) + "\n")
    # 5. applied names
    for r in rs:
        syms = (r.get("defs") or []) + ([r["func"]] if r.get("func") else [])
        for s in syms:
            if s in names: per[r["id"]]["name"].append({"symbol": s, "new_name": names[s][0], "evidence": names[s][1]})
    out = []
    for rid, e in per.items():
        if not (e["assert_sites"] or e["identifiers"] or e["knowledge"] or e["adrando"] or e["data"] or e["vm"] or e["name"] or e["script_function"]): continue
        e["knowledge"].sort(key=lambda n: n["func"]); e["name"].sort(key=lambda n: n["symbol"])
        r = by_id[rid]
        out.append({"id": rid, "container": r["container"], "size": r["size"], "func": r["func"], "true_name": r.get("true_name"),
                    "assert_sites": [s for s in e["assert_sites"] if s.get("own_copy")] or e["assert_sites"][:1],
                    "assert_copies": len(e["assert_sites"]), "identifiers": e["identifiers"], "knowledge": e["knowledge"],
                    "adrando": e["adrando"], "data": e["data"], "vm": e["vm"], "name": e["name"], "script_function": e["script_function"]})
    out.sort(key=lambda x: (x["container"], x["func"] or x["id"]))
    write_jsonl(EV / "rows.jsonl", out)
    print(f"assertions: {len(asserts)} rows carry {sum(a['copies'] for a in asserts)} site copies; {len(unowned)} copies in functions the tree does not own")
    print(f"adrando: {adr_hits} code entries resolved to a function, {sum(len(e['data']) for e in per.values())} data-table references attached to rows; vm tables: {len(tables)}; knowledge: {k_hits} row notes; names: {sum(1 for e in per.values() if e['name'])} rows")
    print(f"script functions: {sum(1 for e in per.values() if any(not s['stub'] for s in e['script_function']))} rows named by the dispatch table")
    print(f"rows with any evidence: {len(out)}")
    return out

_ROWS = None
def for_row(rid):
    global _ROWS
    if _ROWS is None:
        _ROWS = {e["id"]: e for e in read_jsonl(EV / "rows.jsonl")} if (EV / "rows.jsonl").exists() else {}
    return _ROWS.get(rid)

def prompt_block(rid):
    """The evidence paragraph a lane receives for one row ('' when the tree has none)."""
    e = for_row(rid)
    if not e: return ""
    L = ["--- EVIDENCE for this row (facts from the retail disc and earlier analysis; see docs/EVIDENCE.md) ---"]
    for s in e["assert_sites"]:
        if s["kind"] in ("assert", "mark") and s["source_file"]:
            L.append(f"- this function contains Konami's `{s['source_file']}` line {s['line']} ({s['kind']} macro; the file name is the developer's real source file). "
                     f"Keep the assert shape and the line constant exactly; it proves where this function lives.")
        elif s["expression"]:
            meta = IDENTIFIERS.get(s["expression"])
            L.append(f"- this function prints the developer's expression `{s['expression']}`" + (f" -> {meta[1]}" if meta else "") + "; the identifiers in it are the real names: use them for the matching locals/globals.")
    if e["assert_copies"] > len(e["assert_sites"]):
        L.append(f"- (the same site appears {e['assert_copies']} times across the overlay modules; this row is the representative)")
    for a in e["adrando"]:
        L.append(f"- randomizer map: `{a['name']}` is at {a['ram']}" + (f" (+0x{a['offset_in_function']:X} into this function)" if a["offset_in_function"] else " = this function") + (f"; {a['note']}" if a["note"] else ""))
    for v in e["vm"]:
        L.append(f"- resident pointer table {v['table']}: this function is entry {v['index']} ({v['role']})")
    sf = [s for s in e.get("script_function", []) if not s.get("stub")]
    if sf:
        L.append("- script function: the town event-script VM reaches this function by number " + ", ".join(str(s["number"]) for s in sf) + f" through the dispatch table at {sf[0]['table']}; the developer's name for it is `" + "` / `".join(s["dev_name"] for s in sf if s["dev_name"]) + "` (symbol " + ", ".join(s["symbol"] for s in sf if s.get("symbol")) + "). Use that name in the summary comment; the symbol rename itself happens through config/names.tsv.")
    st = [s for s in e.get("script_function", []) if s.get("stub")]
    if st:
        L.append(f"- script function stub: {len(st)} script function numbers dispatch here in this overlay (the real implementation lives in another scene overlay or the number is unused)")
    for d in e.get("data", []):
        lay = f"; record {d['record_bytes']} bytes" if d.get("record_bytes") else ""
        fields = ("; fields (byte offsets): " + ", ".join(f"{k}@{v}" for k, v in d["layout"].items())) if d.get("layout") else ""
        L.append(f"- randomizer map: `{d['symbol']}` is `{d['name']}`{lay}{fields}" + (f"; {d['note']}" if d.get("note") else ""))
    for n in e["name"]:
        L.append(f"- applied name: {n['symbol']} = {n['new_name']} ({n['evidence'][:160]})")
    notes = e["knowledge"]
    for k in notes[:10]:
        if k.get("doc"): L.append(f"- prior note on {k['func']} (medium confidence, verify against the code): {k['doc'][:700]}")
        for g in (k.get("globals") or [])[:6]:
            if isinstance(g, dict) and g.get("name"): L.append(f"- global {g['name']} ({k['func']}): {str(g.get('decl') or g.get('doc') or '')[:220]}")
        for c in (k.get("calls") or [])[:4]:
            L.append(f"- callee ({k['func']}): {str(c)[:220]}")
    if len(notes) > 10: L.append(f"- (+{len(notes) - 10} more prior notes: ledger/evidence/knowledge/)")
    L.append("Use these as candidates for local names, the summary comment and struct-member reading. Keep func_/D_ symbols unchanged: function renames are applied through config/names.tsv, member names through include/records/.")
    return "\n".join(L) + "\n\n"

def census(md=True):
    rs = rows(); by_id = {r["id"]: r for r in rs}
    ev = read_jsonl(EV / "rows.jsonl") if (EV / "rows.jsonl").exists() else []
    kinds = [("assert_sites", "assert file:line / expression"), ("identifiers", "developer identifiers"), ("adrando", "randomizer map (code)"), ("data", "randomizer map (data tables)"), ("vm", "resident pointer tables"), ("script_function", "script function names"), ("knowledge", "prior notes"), ("name", "applied names")]
    tab = defaultdict(lambda: Counter())
    for e in ev:
        for k, _ in kinds:
            if e.get(k): tab[e["container"]][k] += 1; tab[e["container"]][k + "_b"] += e["size"]
        tab[e["container"]]["any"] += 1; tab[e["container"]]["any_b"] += e["size"]
    if not md: return tab
    out = ["| container | " + " | ".join(l for _, l in kinds) + " | any (rows / bytes) |", "|---|" + "---:|" * (len(kinds) + 1)]
    for c in ("slus", "main", "town", "dungeon"):
        t = tab[c]; out.append(f"| {c} | " + " | ".join(str(t[k]) for k, _ in kinds) + f" | {t['any']} / {t['any_b']:,} |")
    return "\n".join(out)

def symbols_md():
    """docs/SYMBOLS.md: the human-readable catalogue of every real name the tree has recovered and how it is used."""
    adr = json.loads((EV / "adrando_map.json").read_text()) if (EV / "adrando_map.json").exists() else {"romAddresses": []}
    vm = json.loads((EV / "vm_tables.json").read_text()) if (EV / "vm_tables.json").exists() else []
    asr = list(read_jsonl(EV / "assertions.jsonl")) if (EV / "assertions.jsonl").exists() else []
    dev = json.loads((EV / "dev_identifiers.json").read_text()) if (EV / "dev_identifiers.json").exists() else {"identifiers": []}
    names = _names()
    O = []
    O.append("# The names the disc gives us (and how the repo uses them)\n")
    O.append("*Generated by `python3 tools/evidence.py symbols` from `ledger/evidence/`; the index of sources and per-level rules is `docs/EVIDENCE.md`. Regenerate after `tools/evidence.py build`.*\n")
    O.append("""Konami shipped Azure Dreams with debug code still in it. That leaves four kinds of real names on the
disc, none of which a decompiler could invent: the **source file names and line numbers** of the
assertions, the **identifier text** of the debug prints, the **script symbol dump** (thousands of named
constants and the script function numbers, §5), the **developer's file paths and ids**, and the **table
addresses** that the community's randomizer mapped and named. This page lists all of
them in plain language and says what each one will become in the C. The rule throughout: a name
the developers wrote is used verbatim; a name the randomizer chose is used for the data symbol it
maps; everything else stays `func_XXXXXXXX` / `unk_XX` until evidence arrives.
""")
    # 1. source files
    O.append("## 1. Source files Konami and Sony named for us\n")
    O.append("Every PSY-Q `assert()` prints `__FILE__` and `__LINE__`. The strings are still there, and each call site is inside a function whose C body therefore contains that line of that file. These are the module names the L4 step uses for `src/<container>/<file>`.\n")
    O.append("| file | what it is | rows in this tree (function, true address, size) | lines proven |")
    O.append("|---|---|---|---|")
    byf = defaultdict(list)
    for a in asr:
        for f in (a["source_files"] or ["(no file attribution)"]): byf[f].append(a)
    order = ["main.c", "lshop.c", "player.c", "c_server.c", "card_mes.c", "card_opt.c", "card_win.c", "cardbk.c", "cardinfo.c", "cardslot.c", "cardsme.c", "memory.c", "tobjs.c", "sn_main.c", "flgtst.c", "(no file attribution)"]
    for f in order:
        rs_ = byf.get(f, [])
        if not rs_ and f != "(no file attribution)": continue
        cells = "; ".join(f"`{a['id']}` ({a['true_name'] or 'no true name'}, {a['size']} B)" for a in rs_)
        lines = sorted({l for a in rs_ for (sf, l) in a["lines"] if sf == f})
        O.append(f"| `{f}` | {SOURCE_FILES.get(f, 'functions that print an identifier whose owning file is not proven (§2)')} | {cells or '—'} | {', '.join(str(l) for l in lines) or '—'} |")
    O.append("")
    O.append("""How they are used:

- **Module names.** A row that proves `main.c:40` goes into `src/town/main.c`; `lshop.c`, `player.c`,
  `c_server.c` and the card files likewise. The link order inside a TOWN scene module is proven as
  *unnamed vertex walker → lshop.o → main.o → player.o* (`docs/EVIDENCE.md` §2), so the rows between
  two proven objects are placed by that order, and the assertion lines order the functions inside a file.
- **The assertion stays in the C.** The retail bytes contain the `printf` with the `__LINE__` constant,
  so the rewritten function keeps `assert(...)`-shaped code at that line; a mismatch there means the
  function was placed at the wrong source line. The debug-print helpers (`%s = %d`) are kept the same way.
- **Devkit files are not game code.** `tobjs.c`, `sn_main.c`, `flgtst.c` (a scene-authoring tool linked
  into a TOWN.BIN blob) and the `card_*.c` / `memory.c` copies in MAIN.BIN are debug builds that shipped by
  accident. They get their real file names and stay clearly separated from the shipped modules.
""")
    # 2. identifiers
    O.append("## 2. Identifiers the developers wrote\n")
    O.append("The `%s = %d` / `%s = %x` debug macro prints the *expression text*, so these are Konami's own variable, type and member names. They are used verbatim for the matching C symbols.\n")
    O.append("| expression on the disc | owning file | meaning | C names to use | rows |")
    O.append("|---|---|---|---|---|")
    use = {
        "((u_long)p - (u_long)ost_w)/ sizeof(OSETDT)": "`OSETDT` (typedef of the object-set record), `ost_w[]` (the table), `p` (an `OSETDT *` cursor)",
        "((u_long)pp - (u_long)osel_w)/ sizeof(OSETDT*)": "`osel_w[]` (array of `OSETDT *`), `pp` (an `OSETDT **` cursor)",
        "cdhd_cnt": "`cdhd_cnt` (global counter)",
        "ov_work.kind": "`ov_work` (global overlay-work struct) with member `kind`",
        "p->kind": "member `kind` on the pointed-to record",
        "kind": "`kind`", "mode": "`mode`", "sno": "`sno` (scene number)",
        "head": "`head`", "ptr[n].vx": "`ptr` (vertex array, PSY-Q `SVECTOR`/`DVECTOR`-style `.vx`/`.vy`), `n` (index)", "ptr[n].vy": "as above",
        "s0[0]": "`s0`", "s1[0]": "`s1`", "s[0]": "`s`",
        "(int)gsw->check_sum": "`gsw` (game-save work pointer) with member `check_sum`",
        "card_first_flg": "`card_first_flg` (libcard global)", "cnt": "`cnt`",
    }
    for i in dev["identifiers"]:
        O.append(f"| `{i['text']}` | `{i['file']}` | {i['meaning']} | {use.get(i['text'], '')} | {', '.join('`%s`' % r for r in i['rows']) or '(no row owns it yet)'} |")
    O.append("")
    O.append("""Notes:

- The `main.c` triple (`OSETDT` / `ost_w` / `osel_w` / `cdhd_cnt`) appears **54 times in TOWN.BIN**: once per
  event-script module, because every script module links its own copy of the town-scene `main.o`. It is not
  script data; it is the scene runtime each script carries. `ost_w` is an "object-set table" of `OSETDT`
  records with `osel_w` a parallel array of pointers into it, and `cdhd_cnt` counts CD headers (the loader
  side of the same file).
- `gsw->check_sum` names the save-game work struct and its checksum member; the memory-card UI rows that
  read the checksum use the same names.
- `head`, `ptr[n].vx`, `ptr[n].vy` belong to an object linked *before* `lshop.o` whose file name is not on the
  disc; `s0[0]` / `s1[0]` / `s[0]` to one between `main.o` and `player.o`. The identifiers are still used
  verbatim; the module gets a descriptive provisional file name until a better fact appears.
""")
    # 3. developer strings
    O.append("## 3. Other developer strings\n")
    O.append("| string | container | file offsets | note |")
    O.append("|---|---|---|---|")
    for d in dev.get("developer_strings", []):
        O.append(f"| `{d['string']}` | {d['container']} | {', '.join(d['foff'])} | {d['note']} |")
    O.append("\nThe `\\vx035\\data\\sn\\SENGEI*.BIN` and `\\vx035\\data\\town\\*.bin` paths are the developer's data layout (`sn` = scene files, `town` = town map data); they name the data files the loaders open and are used in comments and in the names of the loader routines.\n")
    # 4. randomizer
    O.append("## 4. The randomizer's address map\n")
    O.append("The Azure Dreams De-Randomizer (ProGrammar-R, MPL-2.0) documents where the game's tables and a number of code sites live, with names and record layouts. Verified against this disc (`docs/evidence/adrando-findings.md`). Only the facts are used, never its code.\n")
    O.append("### 4.1 Data tables and strings (become `D_` symbol names and record headers)\n")
    O.append("| randomizer name | RAM | container / file offset | record | rows that reference it | becomes |")
    O.append("|---|---|---|---|---|---|")
    lay = {"initialStatsTable": "initialStats", "trapTable": "trap", "statGrowthTable": "statGrowth"}
    for e in adr["romAddresses"]:
        if e["ram"] and not e.get("row"):
            rec = adr["rowLength"].get(lay.get(e["name"], ""), "")
            sym = f"D_{int(e['ram'], 16):08X}"
            O.append(f"| `{e['name']}` | `{e['ram']}` | {e.get('file') or '?'} @ {e.get('file_offset') or '?'} | {str(rec) + ' B/record' if rec else ''} | {', '.join('`%s`' % r for r in e.get('rows', [])) or '—'} | `{sym}` → `{e['name']}`{' (typed `' + e['name'].replace('Table', '') + 'Record`)' if rec else ''} |")
    O.append("")
    O.append("Record layouts the map gives (byte offsets):\n")
    O.append("- `initialStatsTable` (24 B): " + ", ".join(f"`{k}`@{v}" for k, v in adr.get("monsterStats_layout", {}).items()))
    O.append("- `trapTable`: 12 B per trap; `statGrowthTable`: 8 B per record")
    O.append("- item categories (`TYPE`): " + ", ".join(f"`{k}`={v}" for k, v in adr.get("item_TYPE", {}).items()))
    O.append("- trap types: " + ", ".join(f"`{k}`={v}" for k, v in adr.get("TRAP_TYPES", {}).items()))
    O.append("- spell ids known: " + ", ".join(f"`{k}`=0x{v:X}" for k, v in adr.get("spells", {}).items()) + f"; RNG is a 48-bit LCG (multiplier `{adr.get('lcgConstants', {}).get('multiplier')}`, increment {adr.get('lcgConstants', {}).get('increment')})\n")
    O.append("### 4.2 Code sites (say what the surrounding function does)\n")
    O.append("Each entry is a byte the randomizer patches; its name describes the behaviour at that point, which is evidence for the function's summary and, together with the call sites, for its name.\n")
    O.append("| randomizer name | RAM | row (function) | offset into the function |")
    O.append("|---|---|---|---|")
    seen = set()
    for e in adr["romAddresses"]:
        if e.get("row"):
            k = (e["name"].rstrip("12"), e["row"])
            if k in seen: continue
            seen.add(k)
            O.append(f"| `{e['name']}` | `{e['ram']}` | `{e['row']}` ({names.get(e['symbol'], (e['symbol'],))[0]}) | +0x{e['offset_in_function']:X} |")
    O.append("")
    rest = [e for e in adr["romAddresses"] if not e["ram"]]
    if rest:
        O.append("Entries without a load address (data blobs inside overlay files, located by disc offset only): " + ", ".join(f"`{e['name']}`" + (f" ({e['file']} @ {e['file_offset']})" if e.get("file") else "") for e in rest) + ".\n")
    # 5. the script symbol dump
    ss_p = EV / "script_symbols.json"; ft_p = EV / "fno_table.json"
    if ss_p.exists():
        ss = json.loads(ss_p.read_text()); recs = ss["records"]
        O.append("## 5. The script symbol dump Konami left in TOWN.BIN\n")
        O.append(f"""Inside the devkit blob in TOWN.BIN (two tables, file offsets {', '.join(t['file_offset'] for t in ss['tables'])}) sits the scene tool's
symbol dump: **{len(recs):,} records** of a 32-bit value and a 32-byte name. These are the constants the event scripts
were compiled against, with the developers' own names: event flags, function numbers, scene steps, script system
calls, image and person ids. The Japanese disc carries the same dump (one name fewer), so the US disc is the complete
source. The full list is `docs/evidence/script_symbols.tsv`; `include/script_symbols.h` defines every one of them for
the day a lane proves that a literal in the C is one of these numbers.
""")
        O.append("| family | count | what the numbers are | how the repo uses them |")
        O.append("|---|---:|---|---|")
        for k, v in ss["families"].items():
            O.append(f"| `{k}` | {v['count']} | {v['what'] or '—'} | {v['use'] or '—'} |")
        O.append("")
        if ft_p.exists():
            ft = json.loads(ft_p.read_text())
            named = [e for e in ft["table"] if e["dev_name"] and not e["stub"] and e["row"]]
            stubs = [e for e in ft["table"] if e["stub"] and e["dev_name"]]
            unnamed = [e for e in ft["table"] if not e["dev_name"] and e["row"]]
            O.append("### 5.1 Script function numbers: the dispatch table, resolved\n")
            O.append(f"""The `FNO_` numbers are how a town script calls C code: the VM takes the number, subtracts 100 and indexes the
function-pointer table at `{ft['vram']}` (TOWN.BIN file {ft['file_offset']}, {ft['entries']} entries, in the town main
overlay). {ft['named_numbers_on_function_starts']} of the named numbers land exactly on a known function start, so **the text
after `FNO_` is the developer's own name for that C function**. {len(named)} of them resolve to a function this tree owns
(the resident ones through the SLUS rows); they are listed in `ledger/evidence/names_proposed.tsv` in `config/names.tsv`
format, to be applied at L4 through the alias mechanism (byte-exact by construction). Names that begin with `func_`
(`FNO_func_sn_ball` ...) collide with the address-derived namespace the tools reserve and are proposed with a `scr_` prefix.
{len(stubs)} numbers ({stubs[0]['number']}–{stubs[-1]['number']}) point at one stub (`{ft['stub_target']}`) in this overlay: their
implementations live in the scene overlays or script modules and are still to be located. Numbers {unnamed[0]['number']}–{unnamed[-1]['number']}
have functions but no name in the dump (the dump predates them); `FNO_func_sn_casino` = 3 is the one number below 100.
""")
            O.append("| number | developer name | function (row) | note |")
            O.append("|---|---|---|---|")
            for e in ft["table"]:
                if not e["dev_name"] and not e["row"]: continue
                note = "stub in this overlay" if e["stub"] else ("" if e["row"] else f"target {e['target']} is not a function start the tree knows")
                O.append(f"| {e['number']} | `{e['dev_name'] or '—'}` | `{e['row'] or '—'}`{(' (' + e['row_func'] + ')') if e['row_func'] and e['row'] and e['row_func'] != e['row'].split('/')[-1] else ''} | {note} |")
            O.append("")
        # small families in full
        by = defaultdict(list)
        for r in recs: by[r["family"]].append((r["value"], r["name"]))
        O.append("### 5.2 The small families in full\n")
        for fam_, title in (("S_", "Script system calls (`S_`)"), ("V_", "Script variable slots (`V_`)"), ("sn_", "Scene numbers and switches (`sn_`)"), ("PSN_", "Person demo-motion commands (`PSN_DM_*`)"), ("ANM_", "Animations (`ANM_`)"), ("ANMWAY_", "Directions"), ("IMG_", "Portrait image ids (`IMG_`)"), ("SSTP_", "Scene steps (`SSTP_`)"), ("mam_", "`mam_`"), ("fg_", "`fg_`")):
            items = sorted(set(by.get(fam_, [])))
            if not items: continue
            O.append(f"- **{title}** ({len(items)}): " + ", ".join(f"`{n}`={v}" for v, n in items))
        O.append("")
        O.append("""The `S_` numbers 0–32 line up one-for-one with the 33-entry resident pointer table at `0x8006B01C` (a table of small
trampolines at the start of the SLUS text, listed in `ledger/evidence/vm_tables.json`): `S_open_sell_dougu` = 0 ...
`S_set_no_change_seq` = 32. That is a hypothesis from the counts and order, not yet a proof; reading the VM's system-call
handler settles it, and would name those 33 trampolines and the overlay functions behind them. `S_printf` /
`S_sprintf` / `S_getchar` / `S_exit` (34, 90–92) are the developer-console calls the port found unimplemented in retail.
""")
        O.append("### 5.3 The flags (`F_` and its variants, `GOODS_`, `mamonogoya_`)\n")
        F = sorted(set(by["F_"]))
        O.append(f"""{len(F):,} event-flag numbers plus the `Ftt_` / `Ft_` / `Fr_` / `Fc_` / `Fp_` variants and the `GOODS_SAVE_FLG_NN` goods flags,
all in one number space (up to 0x{max(v for v, _ in F):X}); `mamonogoya_setfgNN` / `mamonogoya_stat_NN` use a second, 0x8000-based bank.
The names read as scene + event: `F_sakaba_close` (bar closed), `F_guy_sword_pickup`, `F_ultima_egg_pickup`,
`F_act_<npc>` (actor flags for every town character: player, mascot, gy, rees, wedy, gosh, selfy, paty, far, mia, niko,
vivian, cheril, ...). They become the argument names of the flag test/set calls once a lane proves which resident
routine is the flag accessor (`flgtst.c` is its devkit test harness); until then they live in the header and the TSV.
Examples: """ + ", ".join(f"`{n}`={v}" for v, n in F[:10]) + " ...\n")
    # 6. pointer tables
    O.append("## 6. Resident pointer tables (opcode numbering)\n")
    if vm:
        t0 = vm[0]
        O.append(f"The event-script VM's handler table at `{t0['vram']}` has {t0['entries']} entries: entry *i* is the handler for script opcode *i*. {t0['role'].split(':', 1)[1].strip()}. Handlers therefore get names of the form `ScriptOp<NN>_<verb>` once the verb is read from the body; the numbering itself is a fact.\n")
        O.append("| opcode | handler | row |")
        O.append("|---|---|---|")
        stub = Counter(x["target"] for x in t0["targets"]).most_common(1)[0][0]
        for x in t0["targets"]:
            O.append(f"| {x['index']} | `{x['symbol'] or x['target']}`{' (unimplemented-opcode stub)' if x['target'] == stub else ''} | `{x['row'] or '?'}` |")
        O.append("")
        O.append("Five more resident function-pointer tables are resolved to rows but not yet named: " + ", ".join(f"`{x['vram']}` ({x['entries']} entries)" for x in vm[1:]) + ". Their roles come from reading the dispatcher that indexes them.\n")
    # 6. names + notes
    O.append("## 7. Names already applied, and the prior notes\n")
    O.append(f"`config/names.tsv` holds {len(names)} function renames applied through the alias mechanism (byte-exact by construction), each with an evidence line:\n")
    O.append("| symbol | name | evidence |")
    O.append("|---|---|---|")
    for s, (n, ev) in sorted(names.items()):
        O.append(f"| `{s}` | `{n}` | {ev[:140]} |")
    kn = len(list((EV / "knowledge").glob("func_*.json"))) if (EV / "knowledge").exists() else 0
    O.append(f"\n{kn} prior per-function notes (`ledger/evidence/knowledge/`) carry a one-paragraph description, typed globals and callee summaries written during the matching campaign. They are medium-confidence: the lane sees them as candidates and checks them against the code.\n")
    # 7. how used
    O.append("""## 8. How the repo uses all of this

1. **Every lane prompt carries the row's evidence block** (`tools/agent_task.py`; `tools/evidence.py show <row>`
   prints it). The L2/L3 lane names locals and writes the summary from it, keeps assertion lines exact, and
   leaves `func_` / `D_` / `unk_` symbols alone. The journal marks `evidence: true` on those rows.
2. **L4 names** are applied in one place each: functions through `config/names.tsv` (alias, byte-exact;
   `ledger/evidence/names_proposed.tsv` holds the script-function names ready to apply),
   data symbols through the symbol files, struct members through `include/records/Rec_*.h`. Trust order:
   developer text (verbatim) → randomizer table names (verbatim for the data symbol) → pointer-table
   numbering → prior notes (verified) → call-site roles. No name without an evidence line.
3. **L4 modules** are cut on the assertion source map where it exists (`main.c`, `lshop.c`, `player.c`,
   `c_server.c`, `card_*.c`, `memory.c`) and on call-graph clusters and address ranges elsewhere;
   `ledger/levels.jsonl` records each row's evidence kinds so the gate can check a row with a proven file
   is in that file's module.
4. **Devkit leftovers** (`tobjs.c`, `sn_main.c`, `flgtst.c`, the card UI and libcard copies) are named from
   the same evidence but kept apart from the shipped game code.
5. `STATUS.md` reports how many rows carry each kind of evidence; `docs/EVIDENCE.md` is the index.
""")
    return "\n".join(O) + "\n"

def main():
    ap = argparse.ArgumentParser(); sub = ap.add_subparsers(dest="cmd", required=True)
    i = sub.add_parser("import"); i.add_argument("--adrando-constants"); i.add_argument("--knowledge-dir"); i.add_argument("--town-bin", help="TOWN.BIN container: parse the script symbol dump + FNO dispatch table")
    sub.add_parser("build"); s = sub.add_parser("show"); s.add_argument("row"); sub.add_parser("census"); sub.add_parser("symbols")
    a = ap.parse_args()
    if a.cmd == "import": cmd_import(a)
    elif a.cmd == "build": build()
    elif a.cmd == "show": print(prompt_block(a.row) or f"(no evidence for {a.row})")
    elif a.cmd == "census": print(census())
    elif a.cmd == "symbols":
        (ROOT / "docs" / "SYMBOLS.md").write_text(symbols_md()); print("docs/SYMBOLS.md written")

if __name__ == "__main__":
    main()
