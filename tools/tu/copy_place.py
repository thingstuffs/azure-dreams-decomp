#!/usr/bin/env python3
"""Relinked copies -> link-list placements (decision 73 (e), docs/LINK_LISTS.md).

A relinked copy is a row whose own source file re-spells another row's (its home's) C at a
different address/image: `/* Relink of matched <home>` (relink_lint allowlist), `/* Relinked copy
of <home>` (r121_nodonor and later lanes; not seen by relink_lint) or a split record whose
`clone_template` names a home while the row still owns a file.  A placement compiles the HOME's
text (its member projection when the home was inlined) and rebinds the object BY ADDRESS, so the
copy's file, its layout record and its relink text disappear.

    python3 tools/tu/copy_place.py census --out OUT.tsv            # every copy + blocker class
    python3 tools/tu/copy_place.py derive ROW [ROW...] --work W     # compile home + copy, pair relocations
    python3 tools/tu/copy_place.py apply PLAN.json [--check]        # name-keyed, idempotent
    python3 tools/tu/copy_place.py windows PLAN.json                # copy + home windows to gate

`derive` compiles the home's placement unit exactly as the window gate does (member projection, home
frozen noreturn evidence, home as-flags) and the copy's current file, requires equal .text bytes
outside relocation fields and equal relocation (offset, type) streams, and maps every home symbol to
the copy symbol at the same relocation.  The mapping is then compared with linklist.binding() under
the planned entry; only disagreements become explicit `bindings`.  A home symbol that needs two
different copy symbols, or a copy symbol reached from two home symbols when the rules cannot already
produce it, is refused (alias / collision).  The retail byte compare of the window gate stays the
arbiter: derive proves nothing by itself.
"""
from __future__ import annotations

import argparse, hashlib, json, os, re, subprocess, sys, tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/gate"))

import linklist as L  # noqa: E402
import source_layout as SL  # noqa: E402

RELINK_HEAD = re.compile(r"^/\* Relink of matched ([a-z_]+/func_[0-9A-F]{8})", re.M)
RELINKED_HEAD = re.compile(r"Relinked copy of ([a-z_]+/func_[0-9A-F]{8})")
NODONOR = re.compile(r"r121_nodonor relink of ([a-z_]+/func_[0-9A-F]{8})")
DEFINE = re.compile(r"^#define\s+(\w+)\s+((?:func|D)_[0-9A-Fa-f]{8})\b", re.M)
OBJDUMP = "mipsel-linux-gnu-objdump"
READELF = "mipsel-linux-gnu-readelf"


def jl(path):
    p = Path(path)
    return [json.loads(l) for l in p.read_text().splitlines() if l.strip()] if p.exists() else []


def registry(root=ROOT):
    return {r["id"]: r for r in jl(Path(root) / "ledger/rows.jsonl")}


def modules(root=ROOT):
    out = {}
    p = Path(root) / "config/overlays/modules.json"
    if p.exists():
        for m in json.loads(p.read_text()).get("modules", []):
            for k in ("members", "data_members"):
                for a in m.get(k, []):
                    out[a["id"]] = m["key"]
    return out


def splits(root=ROOT):
    out = {}
    for cont in ("main", "town", "dungeon", "ovmovie"):
        for r in jl(Path(root) / f"ledger/splits/{cont}.jsonl"):
            if r.get("func_vram") and not r.get("rerun"):
                out[cont + "/" + r["func_vram"]] = r
    return out


def images_at(images, container, foff):
    return sorted((i for i in images.values()
                   if i["container"] == L.family(container) and i["foff"] <= foff < i["foff"] + i["size"]
                   and i["vma"] is not None),
                  key=lambda i: (i["schema"] != L.SCHEMA, i["size"], i["image"]))


def ultimate_home(rid, homes, seen=None, reg=None):
    """Follow copy chains (and, with reg, link-list placements: a home that is itself a placement compiles its
    own home's TU) to the one own-file home."""
    seen = seen or set()
    while rid not in seen:
        seen.add(rid)
        if rid in homes:
            rid = homes[rid]
        elif reg is not None and reg.get(rid, {}).get("source_row"):
            rid = reg[rid]["source_row"]
        else:
            break
    return rid


def copy_rows(root=ROOT):
    """{copy row id: dict(home=..., marker=..., file=...)} over every source marker + split clone_template."""
    root = Path(root)
    reg = registry(root)
    images, by_place, by_row, _ = L.load(root)
    paths = {}
    for rid, r in reg.items():
        if r.get("source_row") or r.get("kind") == "slus" or r["container"] == "slus":
            continue
        try:
            paths.setdefault(SL.row_relative(r, root), []).append(rid)
        except Exception:
            continue
    out = {}
    for rel, rids in paths.items():
        p = root / rel
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        heads = RELINK_HEAD.findall(text)
        marker, home = None, None
        if heads:
            marker, home = "relink_of_matched", heads[0]
        else:
            m = RELINKED_HEAD.search(text) or NODONOR.search(text)
            if m:
                marker, home = "relinked_copy", m.group(1)
        if not marker:
            continue
        for rid in rids:
            if len(rids) > 1:
                # several rows in one physical TU: only rows whose own member text carries the marker
                continue
            out[rid] = dict(home=home, marker=marker, file=rel, chain=heads[1:] if heads else [],
                            defines=len(DEFINE.findall(text)))
    sp = splits(root)
    for rid, s in sp.items():
        t = s.get("clone_template")
        if not t or rid in out or rid in by_row and by_row[rid]["home"] != rid:
            continue
        r = reg.get(rid)
        if r is None or r.get("source_row"):
            continue
        try:
            rel = SL.row_relative(r, root)
        except Exception:
            continue
        if not (root / rel).exists() or t == rid:
            continue
        out[rid] = dict(home=t, marker="split_clone_template:" + str(s.get("clone_binding_mode")), file=rel,
                        chain=[], defines=0)
    return out


def classify(root=ROOT):
    root = Path(root)
    reg = registry(root)
    mods = modules(root)
    images, by_place, by_row, _ = L.load(root)
    inline = {r["member_id"]: r for r in jl(root / "ledger/layout_inline.jsonl")}
    copies = copy_rows(root)
    homes = {k: v["home"] for k, v in copies.items()}
    rows = []
    for rid, c in sorted(copies.items()):
        r = reg[rid]
        home = ultimate_home(c["home"], homes, reg=reg)
        h = reg.get(home)
        hrel = None
        try:
            hrel = SL.row_relative(h, root) if h else None
        except Exception:
            pass
        txt = (root / c["file"]).read_text(errors="replace")
        imgs = images_at(images, r["container"], r["foff"])
        v0 = [i for i in imgs if i["schema"] == L.SCHEMA]
        himgs = images_at(images, h["container"], h["foff"]) if h else []
        hentry = by_row.get(home)
        sibs = {}
        for i in v0:
            sibs[i["image"]] = sum(1 for e in i["entries"] if L.is_code(e) and hrel and e["tu"] == hrel and e["row"] != e["home"])
        blockers = []
        if h is None:
            blockers.append("home_not_registered")
        elif h["container"] != r["container"] and L.family(h["container"]) != L.family(r["container"]):
            pass  # decision 75 (A): placements may cross containers (recorded in the cross column)
        if h is not None and h.get("source_row"):
            blockers.append("home_is_placement")
        if h is not None and h["size"] != r["size"]:
            blockers.append("size_differs_from_home")
        if home in copies:
            blockers.append("home_is_copy")
        if rid in mods:
            blockers.append("copy_is_module_member")
        if not v0:
            blockers.append("no_link_image_at_copy")
        if h is not None and not hentry and not [i for i in himgs if i["schema"] == L.SCHEMA]:
            blockers.append("no_link_image_at_home")
        if h is not None and hrel and h["container"] == r["container"] and inline.get(home) is None:
            # own-file home: the TU must define only the home (else the placement object carries siblings)
            n_defs = sum(1 for k, v in reg.items() if not v.get("source_row") and v.get("container") == h["container"]
                         and _rel(v, root) == hrel)
            if n_defs > 1:
                blockers.append("home_tu_multi_row_without_inline_record")
        rows.append(dict(
            copy_row=rid, copy_file=c["file"], marker=c["marker"], copy_true=r.get("true_name"),
            copy_foff=hex(r["foff"]), size=r["size"], cfg=r.get("cfg"), copy_window=r.get("gate_config"),
            home_row=home, home_declared=c["home"], home_true=h and h.get("true_name"), home_tu=hrel,
            home_module=mods.get(home, ""), home_inline=bool(inline.get(home)),
            home_ll_image=hentry["image"] if hentry else "", home_window=h and h.get("gate_config"),
            copy_images=",".join(i["image"] + ("@" + str(i.get("layout")) if i.get("layout") else "") for i in v0),
            home_images=",".join(i["image"] + ("@" + str(i.get("layout")) if i.get("layout") else "") for i in himgs if i["schema"] == L.SCHEMA),
            siblings_placed=",".join("%s:%d" % kv for kv in sibs.items() if kv[1]),
            defines=c["defines"], chain=",".join(c["chain"]),
            reads_player=int("D_800814A8" in txt), entityrec=txt.count("EntityRec"), unk_58=txt.count("unk_58"),
            blockers=",".join(blockers) or "none"))
    return rows


_REL_CACHE = {}


def _rel(v, root):
    k = v["id"]
    if k not in _REL_CACHE:
        try:
            _REL_CACHE[k] = SL.row_relative(v, root)
        except Exception:
            _REL_CACHE[k] = None
    return _REL_CACHE[k]


def write_tsv(rows, out):
    if not rows:
        Path(out).write_text("")
        return
    cols = list(rows[0])
    with open(out, "w") as f:
        f.write("\t".join(cols) + "\n")
        for r in rows:
            f.write("\t".join(str(r[c]) for c in cols) + "\n")


# ---------------------------------------------------------------------------------------------- derive

_HELPER = r"""
import json, sys
sys.path.insert(0, 'tools')
import overlay_local_gate as G, overlay_evidence as E
from overlay_as_flags import default_as_flags
src, cfg, func, cont, foff, ev, afunc, acont, afoff = sys.argv[1:10]
foff, afoff = int(foff), int(afoff)
v, f = G.config_to_flags(cfg)
env = E.evidence_env_with_candidate(cont, open(src, errors='replace').read(), ev, foff=foff)
print(json.dumps(dict(ver=v, flags=f, asflags=default_as_flags(afunc, acont, foff=afoff), env=env)))
"""


def _compile(src: Path, out_o: Path, cfg: str, row_func: str, container: str, foff: int, ev_dir: Path,
             as_row=None):
    """Compile one TU the way overlay_local_gate.compile_c_segments does (run inside the build_ovl view,
    whose tools/ are the gate's): evidence = (container, foff) of the TU's own home; as-flags from as_row
    (func, container, foff) - a placement's own logical row - or the same identity."""
    b = ROOT / "build_ovl"
    ev_dir.mkdir(parents=True, exist_ok=True)
    afunc, acont, afoff = as_row or (row_func, container, foff)
    spec = json.loads(subprocess.run([sys.executable, "-c", _HELPER, str(src), cfg, row_func, L.family(container),
                                      str(foff), str(ev_dir), afunc, L.family(acont), str(afoff)],
                                     cwd=b, check=True, capture_output=True, text=True).stdout)
    env = dict(os.environ)
    env.update(spec["env"])
    subprocess.run([str(b / "tools/cc.sh"), str(src), str(out_o), spec["ver"], spec["flags"], spec["asflags"]],
                   env=env, check=True, capture_output=True, text=True, cwd=b)


def _sections(obj: Path):
    """{section name: (bytes, [(offset, type, symbol)])} for the allocated payload sections of one object
    (.text*, .rodata*, .data*, .sdata*); .pdr/.mdebug/.reginfo are debug/ABI records and do not link."""
    out = subprocess.run([READELF, "-SW", str(obj)], capture_output=True, text=True, check=True).stdout
    data = obj.read_bytes()
    secs = {}
    for line in out.splitlines():
        m = re.match(r"\s*\[\s*(\d+)\]\s+(\S+)\s+(\S+)\s+[0-9a-f]+\s+([0-9a-f]+)\s+([0-9a-f]+)", line)
        if m and re.match(r"\.(text|rodata|data|sdata|bss|sbss|rdata)", m.group(2)) and m.group(3) in ("PROGBITS", "NOBITS"):
            off, size = int(m.group(4), 16), int(m.group(5), 16)
            if size:
                secs[m.group(2)] = [data[off:off + size] if m.group(3) == "PROGBITS" else b"\0" * size, [], m.group(3)]
    rel = subprocess.run([READELF, "-rW", str(obj)], capture_output=True, text=True, check=True).stdout
    cur = None
    for line in rel.splitlines():
        m = re.match(r"Relocation section '\.rel(\S+)'", line)
        if m:
            cur = m.group(1)
            continue
        m = re.match(r"\s*([0-9a-f]{8})\s+[0-9a-f]+\s+(R_MIPS_\w+)\s+[0-9a-f]+\s+(\S+)", line)
        if m and cur in secs:
            secs[cur][1].append((int(m.group(1), 16), m.group(2), m.group(3)))
    for v in secs.values():
        v[1].sort()
    return secs


def _mask(text: bytes, relocs):
    b = bytearray(text)
    for off, typ, _ in relocs:
        if typ in ("R_MIPS_HI16", "R_MIPS_LO16", "R_MIPS_GPREL16"):
            b[off:off + 2] = b"\0\0"
        elif typ == "R_MIPS_26":
            w = int.from_bytes(b[off:off + 4], "little") & 0xFC000000
            b[off:off + 4] = w.to_bytes(4, "little")
        elif typ == "R_MIPS_32":
            b[off:off + 4] = b"\0\0\0\0"
    return bytes(b)


def pair_objects(ho, co, size):
    """({home symbol: destination address}, None, sections) when the two objects are one object modulo
    relocation targets, else (None, reason, None)."""
    hs_, cs_ = _sections(ho), _sections(co)
    def norm(name):  # .text.func_<home true> / .text.func_<copy true> are the one function section
        return ".text.<fn>" if name.startswith(".text.") else name
    hn = {norm(k): (k, v) for k, v in hs_.items()}
    cn = {norm(k): (k, v) for k, v in cs_.items()}
    if set(hn) != set(cn):
        return None, ("section sets differ: home %s copy %s" % (sorted(hs_), sorted(cs_))), None
    text = [k for k in hn if k.startswith(".text")]
    if sum(len(hn[k][1][0]) for k in text) != size:
        return None, ("home text size differs from the row extent"), None
    secs = {k: len(v[1][0]) for k, v in hn.items()}
    pairs = []
    for k in sorted(hn):
        (hname, (hb, hr, _)), (cname, (cb, cr, _)) = hn[k], cn[k]
        if len(hb) != len(cb):
            return None, ("section %s size home %d copy %d" % (k, len(hb), len(cb))), None
        if [(o, t) for o, t, _ in hr] != [(o, t) for o, t, _ in cr]:
            return None, ("relocation streams differ in " + k), None
        if _mask(hb, hr) != _mask(cb, cr):
            return None, ("%s differs outside relocation fields" % k), None
        ha, ca = _full_addends(hb, hr), _full_addends(cb, cr)
        for (o, t, hsym), (_, _, csym), x, y in zip(hr, cr, ha, ca):
            if hsym.startswith(".text.") and csym.startswith(".text.") and norm(hsym) == norm(csym):
                if x != y:
                    return None, ("own-section relocation addend differs at %s+0x%X" % (k, o)), None
                continue  # section symbol of the function's own section: renamed with it
            m1, m2 = L.ADDR.match(hsym), L.ADDR.match(csym)
            if not m1 or not m2:
                if hsym != csym or x != y:
                    return None, ("non-address relocation %s+0x%X -> %s+0x%X in %s" % (hsym, x, csym, y, k)), None
                continue  # a local section symbol (.rodata, .data): moves with the object
            # the linker resolves sym + addend: the home symbol must land where the copy's reference lands
            need = (int(m2.group(2), 16) + y - x) & 0xFFFFFFFF
            pairs.append((hsym, need, t))
    want = {}
    for hs, need, t in pairs:
        want.setdefault(hs, set()).add(need)
    multi = {k: sorted(map(hex, v)) for k, v in want.items() if len(v) > 1}
    if multi:
        return None, ("home symbol needs two destination addresses: %s" % multi), None
    want = {k: next(iter(v)) for k, v in want.items()}
    return want, None, secs


def bindings_for(tables, entry, want):
    """Explicit bindings an entry needs on top of linklist's rules, and the reference aliases it merges."""
    bindings = {}
    for hs, b in sorted(want.items()):
        a = int(L.ADDR.match(hs).group(2), 16)
        try:
            got = L._binding(tables, entry, a, None)
        except ValueError:
            got = None
        if got != b:
            bindings[a] = b
    tgt = {}
    for hs, b in want.items():
        tgt.setdefault("%s_%08X" % (L.ADDR.match(hs).group(1), b), []).append(hs)
    return bindings, {k: v for k, v in tgt.items() if len(v) > 1}


def derive(rid, work: Path, root=ROOT):
    """Plan record for one copy row (see module doc)."""
    root = Path(root)
    reg = registry(root)
    copies = copy_rows(root)
    c = copies.get(rid)
    if c is None:
        return dict(copy_row=rid, ok=False, reason="not a copy row")
    homes = {k: v["home"] for k, v in copies.items()}
    home = ultimate_home(c["home"], homes, reg=reg)
    r, h = reg[rid], reg[home]
    images, by_place, by_row, local = L.load(root)
    v0 = [i for i in images_at(images, r["container"], r["foff"]) if i["schema"] == L.SCHEMA]
    hrel = SL.row_relative(h, root)
    w = work.absolute() / rid.replace("/", "_")
    w.mkdir(parents=True, exist_ok=True)
    # home placement unit, exactly as overlay_local_gate.compile_c_segments builds it
    unit = SL.member_projection(home, root)
    hsrc = w / (home.split("/", 1)[1] + ".c")
    hsrc.write_bytes(unit if unit is not None else (root / hrel).read_bytes())
    ho, co = w / "home.o", w / "copy.o"
    # exactly as the window gate compiles the placement: HOME evidence (family, foff), the placement row's as-flags
    # the window gate compiles a placement at ITS OWN row's recipe (seg.match.config), so derive does too
    _compile(hsrc, ho, r["cfg"], home.split("/", 1)[1], h["container"], h["foff"], w / "ev_home",
             as_row=(rid.split("/", 1)[1], r["container"], r["foff"]))
    csrc = root / c["file"]
    _compile(csrc, co, r["cfg"], rid.split("/", 1)[1], r["container"], r["foff"], w / "ev_copy")
    rec = dict(copy_row=rid, home_row=home, home_tu=hrel, copy_file=c["file"], marker=c["marker"], copy_foff=hex(r["foff"]),
               size=r["size"], home_obj_sha=hashlib.sha256(ho.read_bytes()).hexdigest(),
               copy_obj_sha=hashlib.sha256(co.read_bytes()).hexdigest())
    if h["cfg"] != r["cfg"]:
        rec["recipe_note"] = "home row recipe %s, placement recipe %s (the placement compiles at its own)" % (h["cfg"], r["cfg"])
    want, err, secs = pair_objects(ho, co, r["size"])
    if err:
        return dict(rec, ok=False, reason=err)
    rec["sections"] = secs
    if len(v0) == 0:
        return dict(rec, ok=False, reason="no v0 link image at the copy")
    plans = []
    for img in v0:
        entry = dict(row=rid, tu=hrel, home=home, foff=r["foff"], vma=img["vma"] + r["foff"] - img["foff"],
                     size=r["size"], bindings={}, image=img["image"], container=img["container"])
        if entry["vma"] != _true_vma(r):
            plans.append(dict(image=img["image"], ok=False, reason="image vma %s != split true name %s" % (hex(entry["vma"]), r.get("true_name"))))
            continue
        hentry = by_row.get(home)
        tables = (images, by_place, dict(by_row), local)
        if hentry is None:
            himg = [i for i in images_at(images, h["container"], h["foff"]) if i["schema"] == L.SCHEMA]
            # the image where the same TU's other home entries are listed (a TU has one home image)
            himg.sort(key=lambda i: -sum(1 for e in i["entries"] if L.is_code(e) and e["home"] == e["row"] and e["tu"] == hrel))
            if not himg:
                plans.append(dict(image=img["image"], ok=False, reason="no link image for the home"))
                continue
            hentry = dict(row=home, tu=hrel, home=home, foff=h["foff"], vma=himg[0]["vma"] + h["foff"] - himg[0]["foff"],
                          size=h["size"], bindings={}, image=himg[0]["image"], container=himg[0]["container"])
            if hentry["vma"] != _true_vma(h):
                plans.append(dict(image=img["image"], ok=False, reason="home image vma disagrees with home true name"))
                continue
            tables[2][home] = hentry
        tables[2][rid] = entry
        bindings, coll = bindings_for(tables, entry, want)
        bad = []
        plans.append(dict(image=img["image"], ok=not bad, reason="; ".join(bad), aliases=coll,
                          vma=hex(entry["vma"]), new_home_entry=(None if by_row.get(home) else
                                                                  dict(image=hentry["image"], vma=hex(hentry["vma"]))),
                          bindings={"0x%08X" % k: "0x%08X" % v for k, v in sorted(bindings.items())}))
    good = [p for p in plans if p["ok"]]
    if rid in by_row:  # the copy already has a (home) entry: it stays in that image
        good = [p for p in good if p["image"] == by_row[rid]["image"]]
    rec["plans"] = plans
    if not good:
        return dict(rec, ok=False, reason="no image admits the placement: " + " | ".join(p["reason"] for p in plans))
    # prefer the image whose rules need the fewest explicit bindings, then the narrowest (images_at order)
    best = min(good, key=lambda p: len(p["bindings"]))
    # A copy that is already the link-list HOME of other placements: those placements follow it onto the
    # ultimate home.  Each dependent's current object (the copy's object rebound by its entry) is paired
    # with the ultimate home's object exactly like a copy.
    deps = [e for e in by_row.values() if e["home"] == rid and e["row"] != rid]
    dep_recs = []
    if deps:
        tables = (images, by_place, dict(by_row), local)
        new_entry = dict(row=rid, tu=hrel, home=home, foff=r["foff"], vma=int(best["vma"], 16), size=r["size"],
                         bindings={int(k, 16): int(v, 16) for k, v in best["bindings"].items()},
                         image=best["image"], container=r["container"] if r["container"] != "dungeon_engine" else "dungeon")
        tables[2][rid] = new_entry
        if home not in tables[2]:
            ne = best["new_home_entry"]
            tables[2][home] = dict(row=home, tu=hrel, home=home, foff=h["foff"], vma=int(ne["vma"], 16), size=h["size"],
                                   bindings={}, image=ne["image"], container=new_entry["container"])
        for e in sorted(deps, key=lambda e: e["row"]):
            do = w / (e["row"].split("/", 1)[1] + ".rebound.o")
            do.write_bytes(co.read_bytes())
            L.rebind_object(root, e, do)
            dwant, derr, _ = pair_objects(ho, do, e["size"])
            if derr:
                return dict(rec, ok=False, reason="dependent placement %s: %s" % (e["row"], derr))
            ne = dict(e, home=home, tu=hrel, bindings={})
            tables[2][e["row"]] = ne
            b, al = bindings_for(tables, ne, dwant)
            dep_recs.append(dict(row=e["row"], image=e["image"], old_home=rid, old_bindings={"0x%08X" % k: "0x%08X" % v for k, v in e["bindings"].items()},
                                 bindings={"0x%08X" % k: "0x%08X" % v for k, v in sorted(b.items())}, aliases=al,
                                 rebound_obj_sha=hashlib.sha256(do.read_bytes()).hexdigest()))
    return dict(rec, ok=True, reason="", image=best["image"], vma=best["vma"], bindings=best["bindings"],
                aliases=best["aliases"], symbol_map={k: "0x%08X" % v for k, v in want.items()},
                new_home_entry=best["new_home_entry"], dependents=dep_recs)


def _sext16(v):
    return v - 0x10000 if v & 0x8000 else v


def _full_addends(text, relocs):
    """The addend the linker applies at each relocation (REL: in the instruction), with HI16/LO16 pairs
    combined as the MIPS ABI does: AHL = (hi << 16) + sext(lo) over the pair of the same symbol."""
    word = lambda o: int.from_bytes(text[o:o + 4], "little")
    out = []
    for i, (off, typ, sym) in enumerate(relocs):
        w = word(off)
        if typ == "R_MIPS_HI16":
            lo = next((word(o2) & 0xFFFF for o2, t2, s2 in relocs[i + 1:] if t2 == "R_MIPS_LO16" and s2 == sym), 0)
            a = ((w & 0xFFFF) << 16) + _sext16(lo)
        elif typ == "R_MIPS_LO16":
            hi = next((word(o2) & 0xFFFF for o2, t2, s2 in reversed(relocs[:i]) if t2 == "R_MIPS_HI16" and s2 == sym), 0)
            a = (hi << 16) + _sext16(w & 0xFFFF)
        elif typ == "R_MIPS_26":
            a = (w & 0x03FFFFFF) << 2
        elif typ == "R_MIPS_GPREL16":
            a = _sext16(w & 0xFFFF)
        else:
            a = w
        out.append(a & 0xFFFFFFFF)
    return out


def _true_vma(r):
    t = r.get("true_name") or ""
    m = L.ADDR.match(t)
    return int(m.group(2), 16) if m else None


def _addends(text, relocs):
    out = []
    for off, typ, _ in relocs:
        w = int.from_bytes(text[off:off + 4], "little")
        if typ in ("R_MIPS_HI16", "R_MIPS_LO16", "R_MIPS_GPREL16"):
            a = w & 0xFFFF
        elif typ == "R_MIPS_26":
            a = w & 0x03FFFFFF
        else:
            a = w
        out.append((off, typ, a))
    return out


# ---------------------------------------------------------------------------------------------- apply

def _image_path(root, image):
    cont, name = image.split("/", 1)
    return Path(root) / "config/link" / cont / (name + ".json")


def _fmt_hex(v):
    return "0x%X" % v


def apply_plan(plan, root=ROOT, check=False):
    """Name-keyed and idempotent: for every record (copy row, home row, image) ensure
    (1) the home owns a home entry, (2) the copy's placement entry with the planned bindings,
    (3) the copy file is gone, (4) its layout record is gone, (5) the raw retirement is recorded.
    Returns a list of (row, step, state) where state is done / already / would / refused:<why>."""
    root = Path(root)
    log = []
    reg = registry(root)
    layout = jl(root / "ledger/layout.jsonl")
    lay_ids = {r["id"] for r in layout}
    changed_layout = False
    retire = jl(root / "ledger/raw_retired.jsonl")
    retired = {r.get("id") for r in retire if str(r.get("path", "")).startswith("src/")}
    new_retire = []
    for rec in plan:
        if not rec.get("ok"):
            continue
        rid, home = rec["copy_row"], rec["home_row"]
        r = reg.get(rid)
        if r is None:
            log.append((rid, "registry", "refused:copy row not registered")); continue
        if reg.get(home) is None:
            log.append((rid, "registry", "refused:home not registered")); continue
        hrel = SL.row_relative(reg[home], root) if not reg[home].get("source_row") else None
        if hrel is None:
            log.append((rid, "home", "refused:home is itself a placement")); continue
        images, by_place, by_row, _ = L.load(root)
        # (1) home entry
        if home not in by_row:
            ne = rec.get("new_home_entry")
            if not ne:
                log.append((rid, "home_entry", "refused:no planned home entry")); continue
            if check:
                log.append((rid, "home_entry", "would"))
            else:
                _insert_entry(root, ne["image"], dict(row=home, tu=hrel, home=home, foff=_fmt_hex(reg[home]["foff"]),
                                                      vma=ne["vma"], size=reg[home]["size"]))
                log.append((rid, "home_entry", "done"))
        else:
            he = by_row[home]
            if he["tu"] != hrel:
                if check:
                    log.append((rid, "home_tu", "would"))
                else:
                    _retarget_tu(root, home, hrel)
                    log.append((rid, "home_tu", "done"))
            else:
                log.append((rid, "home_entry", "already"))
        # (1b) placements homed on this copy follow it onto the ultimate home (before the copy stops being a home)
        for d in rec.get("dependents") or []:
            images, by_place, by_row, _ = L.load(root)
            de = by_row.get(d["row"])
            if de is None:
                log.append((d["row"], "rehome", "refused:dependent not placed")); continue
            if de["home"] == home:
                log.append((d["row"], "rehome", "already")); continue
            if de["home"] != d["old_home"]:
                log.append((d["row"], "rehome", "refused:dependent home is %s" % de["home"])); continue
            dw = dict(row=d["row"], tu=hrel, home=home, foff=_fmt_hex(de["foff"]), vma=_fmt_hex(de["vma"]), size=de["size"],
                      bindings=d["bindings"], evidence="opus_place1: re-homed from relinked copy %s onto %s; "
                      "tools/tu/copy_place.py derive (dependent object == home object modulo relocation targets)" % (rid, home))
            if not dw["bindings"]:
                dw.pop("bindings")
            if check:
                log.append((d["row"], "rehome", "would"))
            else:
                _update_entry(root, d["row"], dw)
                log.append((d["row"], "rehome", "done"))
        # (2) copy placement entry
        images, by_place, by_row, _ = L.load(root) if not check else (images, by_place, by_row, None)
        e = by_row.get(rid)
        want = dict(row=rid, tu=hrel, home=home, foff=_fmt_hex(r["foff"]), vma=rec["vma"], size=r["size"],
                    bindings=rec.get("bindings") or {})
        if not want["bindings"]:
            want.pop("bindings")
        want["evidence"] = rec.get("evidence") or ("opus_place1: relinked copy -> placement; home object == copy "
                                                   "object outside relocation fields, relocation map derived by "
                                                   "tools/tu/copy_place.py derive; window gate MATCH")
        if e is None:
            if check:
                log.append((rid, "placement", "would"))
            else:
                _insert_entry(root, rec["image"], want)
                log.append((rid, "placement", "done"))
        elif e["home"] == rid and e["row"] == rid:
            # the copy was itself a link-list home: its entry becomes the placement (same image/extent)
            if e["image"] != rec["image"]:
                log.append((rid, "placement", "refused:home entry lives in %s, plan says %s" % (e["image"], rec["image"]))); continue
            if check:
                log.append((rid, "placement", "would-convert-home"))
            else:
                _update_entry(root, rid, want)
                log.append((rid, "placement", "converted-home"))
        elif e["home"] != home:
            log.append((rid, "placement", "refused:placed with another home " + e["home"])); continue
        else:
            log.append((rid, "placement", "already"))
        # (3) copy file: the recorded path, or the row's live path when another change moved it; never a file
        # that also holds another row (a shared TU / the home)
        cf = _live_copy_file(root, rec, reg, hrel)
        if cf is not None and cf.exists():
            if check:
                log.append((rid, "copy_file", "would"))
            else:
                sha = hashlib.sha256(cf.read_bytes()).hexdigest()
                cf.unlink()
                log.append((rid, "copy_file", "done"))
                if rid not in retired:
                    new_retire.append(dict(id=rid, path=rec["copy_file"], sha256=sha, home=home,
                                           batch="LL4-opus_place1"))
        else:
            log.append((rid, "copy_file", "already"))
        # (4) layout record
        if rid in lay_ids:
            if check:
                log.append((rid, "layout", "would"))
            else:
                layout = [x for x in layout if x["id"] != rid]
                lay_ids.discard(rid)
                changed_layout = True
                log.append((rid, "layout", "done"))
        else:
            log.append((rid, "layout", "already"))
    if not check:
        if changed_layout:
            (root / "ledger/layout.jsonl").write_text("".join(json.dumps(x, separators=(",", ":")) + "\n" for x in layout))
        if new_retire:
            with open(root / "ledger/raw_retired.jsonl", "a") as f:
                for x in new_retire:
                    f.write(json.dumps(x, separators=(",", ":")) + "\n")
    return log


_OWNERS = {}


def _owners(root, reg):
    key = (str(root), id(reg))
    if key not in _OWNERS:
        inv = {}
        for rid, r in reg.items():
            if r.get("source_row") or r.get("container") == "slus":
                continue
            try:
                inv.setdefault(SL.row_relative(r, root), set()).add(rid)
            except Exception:
                pass
        _OWNERS.clear()
        _OWNERS[key] = inv
    return _OWNERS[key]


def _live_copy_file(root, rec, reg, hrel):
    cands = [rec["copy_file"]]
    try:
        live = SL.row_relative(reg[rec["copy_row"]], root)
        if live not in cands:
            cands.append(live)
    except Exception:
        pass
    for rel in cands:
        p = root / rel
        if not p.exists() or rel == hrel:
            continue
        # only own-file rows own a file (placements resolve to their home's file)
        others = _owners(root, reg).get(rel, set()) - {rec["copy_row"]}
        if others:
            continue
        text = p.read_text(errors="replace")
        if not (RELINK_HEAD.search(text) or RELINKED_HEAD.search(text) or NODONOR.search(text)
                or rec.get("marker", "").startswith("split_clone_template") or rec.get("allow_unmarked")):
            continue
        return p
    return None


def _load_doc(path):
    return json.loads(Path(path).read_text())


def _dump_doc(path, doc):
    Path(path).write_text(json.dumps(doc, indent=2) + "\n")


def _insert_entry(root, image, entry):
    p = _image_path(root, image)
    doc = _load_doc(p)
    if doc["schema"] != L.SCHEMA:
        raise SystemExit("refusing to insert a code entry into a whole-image byte map: " + image)
    f = L.num(entry["foff"])
    ents = doc["entries"]
    if any(L.num(x["foff"]) == f for x in ents):
        raise SystemExit("entry already present at %s in %s" % (hex(f), image))
    pos = next((k for k, x in enumerate(ents) if L.num(x["foff"]) > f), len(ents))
    ents.insert(pos, entry)
    _dump_doc(p, doc)


def _update_entry(root, row, entry):
    for p in L.files(root):
        doc = _load_doc(p)
        for k, e in enumerate(doc["entries"]):
            if L.is_code(e) and e["row"] == row:
                doc["entries"][k] = entry
                _dump_doc(p, doc)
                return
    raise SystemExit("no link-list entry for " + row)


def _retarget_tu(root, home, tu):
    for p in L.files(root):
        doc = _load_doc(p)
        hit = False
        for e in doc["entries"]:
            if L.is_code(e) and e["home"] == home and e["tu"] != tu:
                e["tu"] = tu
                hit = True
        if hit:
            _dump_doc(p, doc)


def revert(rows, base, root=ROOT):
    """Undo apply for these copy rows (and the dependents re-homed with them) back to git revision `base`:
    link-list entries, copy files, layout records, relink allowlist lines, retirement records."""
    root = Path(root)
    def show(rel):
        r = subprocess.run(["git", "show", "%s:%s" % (base, rel)], cwd=root, capture_output=True)
        return r.stdout if r.returncode == 0 else None
    rows = set(rows)
    # dependents: entries whose base home was one of the rows
    base_entries = {}
    for p in L.files(root):
        rel = p.relative_to(root).as_posix()
        b = show(rel)
        if b is None:
            continue
        for e in json.loads(b)["entries"]:
            if L.is_code(e):
                base_entries[e["row"]] = (rel, e)
    deps = {r for r, (_, e) in base_entries.items() if e["home"] in rows and r not in rows}
    targets = rows | deps
    log = []
    for p in L.files(root):
        doc = _load_doc(p)
        changed = False
        for k in range(len(doc["entries"]) - 1, -1, -1):
            e = doc["entries"][k]
            if L.is_code(e) and e["row"] in targets:
                if e["row"] in base_entries:
                    doc["entries"][k] = base_entries[e["row"]][1]
                else:
                    del doc["entries"][k]
                changed = True
                log.append((e["row"], "linklist", "restored"))
        if changed:
            _dump_doc(p, doc)
    reg = registry(root)
    lay_base = [json.loads(l) for l in (show("ledger/layout.jsonl") or b"").decode().splitlines() if l.strip()]
    lay_base = {x["id"]: x for x in lay_base}
    layout = jl(root / "ledger/layout.jsonl")
    have = {x["id"] for x in layout}
    retired = jl(root / "ledger/raw_retired.jsonl")
    for r in sorted(rows):
        rec = [x for x in retired if x.get("id") == r and x.get("batch") == "LL4-opus_place1"]
        for x in rec:
            data = show(x["path"])
            if data is not None:
                (root / x["path"]).parent.mkdir(parents=True, exist_ok=True)
                (root / x["path"]).write_bytes(data)
                log.append((r, "copy_file", "restored " + x["path"]))
        if r in lay_base and r not in have:
            layout.append(lay_base[r])
            log.append((r, "layout", "restored"))
    order = {x: i for i, x in enumerate(lay_base)}
    layout.sort(key=lambda x: order.get(x["id"], 1 << 30))
    (root / "ledger/layout.jsonl").write_text("".join(json.dumps(x, separators=(",", ":")) + "\n" for x in layout))
    keep = [x for x in retired if not (x.get("id") in rows and x.get("batch") == "LL4-opus_place1")]
    (root / "ledger/raw_retired.jsonl").write_text("".join(json.dumps(x, separators=(",", ":")) + "\n" for x in keep))
    # relink allowlist lines of restored files
    allow_base = (show("config/lint/relink_text.allow") or b"").decode().splitlines()
    cur = (root / "config/lint/relink_text.allow").read_text().splitlines()
    restored = {x["path"] for x in retired if x.get("id") in rows}
    add = [l for l in allow_base if l.split("\t")[0] in restored and l not in cur]
    if add:
        head = [l for l in cur if l.startswith("#")]
        body = sorted(set(l for l in cur if not l.startswith("#")) | set(add))
        (root / "config/lint/relink_text.allow").write_text("\n".join(head + body) + "\n")
    # home entries this tool created that no placement uses any more
    images, _, by_row, _ = L.load(root)
    return log


def affected_windows(plan, root=ROOT):
    """Every window whose bytes the plan can change: windows covering each copy row, its home row and every
    code entry of each touched link image (rule 3 re-resolves the whole image once a new local definition
    appears there)."""
    from common import covering_windows, window_map
    root = Path(root)
    reg = registry(root)
    images, _, by_row, _ = L.load(root)
    wm = window_map()
    spans, touched = set(), set()
    for rec in plan:
        if not rec.get("ok"):
            continue
        for rid in (rec["copy_row"], rec["home_row"]):
            r = reg[rid]
            spans.add((L.family(r["container"]), r["foff"], r["size"]))
        touched.add(rec["image"])
        touched.update(d["image"] for d in rec.get("dependents") or [])
        if rec.get("new_home_entry"):
            touched.add(rec["new_home_entry"]["image"])
    for img in touched:
        for e in images[img]["entries"]:
            if L.is_code(e):
                spans.add((images[img]["container"], e["foff"], e["size"]))
    out = set()
    for cont, foff, size in spans:
        for w in covering_windows(cont, foff, size, wm):
            out.add("config/overlays/" + w[0])
    return sorted(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    a = sub.add_parser("census"); a.add_argument("--out", required=True)
    a = sub.add_parser("derive"); a.add_argument("rows", nargs="+"); a.add_argument("--work", required=True)
    a.add_argument("--out", required=True)
    a = sub.add_parser("apply"); a.add_argument("plan"); a.add_argument("--check", action="store_true")
    a = sub.add_parser("windows"); a.add_argument("plan")
    a = sub.add_parser("revert"); a.add_argument("rows", nargs="+"); a.add_argument("--base", required=True)
    args = ap.parse_args()
    if args.cmd == "census":
        rows = classify()
        write_tsv(rows, args.out)
        from collections import Counter
        print(len(rows), "copy rows;", dict(Counter(r["blockers"] for r in rows)))
    elif args.cmd == "derive":
        out = []
        for rid in args.rows:
            try:
                rec = derive(rid, Path(args.work))
            except subprocess.CalledProcessError as exc:
                rec = dict(copy_row=rid, ok=False, reason="compile failed: " + (exc.stderr or "")[-400:])
            except Exception as exc:  # noqa: BLE001 - recorded per row
                rec = dict(copy_row=rid, ok=False, reason="%s: %s" % (type(exc).__name__, exc))
            out.append(rec)
            print(rid, "OK" if rec.get("ok") else "HOLD", rec.get("image", ""), len(rec.get("bindings") or {}),
                  rec.get("reason", "")[:300], flush=True)
        Path(args.out).write_text(json.dumps(out, indent=1, default=list) + "\n")
    elif args.cmd == "apply":
        plan = json.loads(Path(args.plan).read_text())
        for x in apply_plan(plan, check=args.check):
            print("\t".join(x))
    elif args.cmd == "revert":
        for x in revert(args.rows, args.base):
            print("\t".join(x))
    elif args.cmd == "windows":
        for w in affected_windows(json.loads(Path(args.plan).read_text())):
            print(w)


if __name__ == "__main__":
    main()
