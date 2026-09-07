#!/usr/bin/env python3
"""T7 step 1: shared record headers from the struct census.

    python3 tools/gen_records.py [--min-rows 10] [--only KEY,KEY]

For every provenance class of the census (ledger/struct_census_structs.json, written by
tools/struct_census.py) with at least --min-rows member functions and a global or parameter
root, emit include/records/<Name>.h with the merged layout:

  one type at an offset            ->  T unk_XX;
  several types, same width        ->  union { s16 s; u16 u; } unk_XX;        (every view a row uses)
  overlapping spans                ->  union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;
  gaps                             ->  u8 pad_XX[0xN];

Nothing is guessed: a view exists in the header because some function reads the offset with
that type, and each member function keeps its own view (the transform rewrites `->unk_XX` to
`->unk_XX.s` etc.), so the bytes cannot move.  Rows whose local struct carries an in-row union
or an unknown-width type are left out of the votes and listed as `unmapped` (they keep their
local struct).  The mapping every member function needs is written to ledger/records.json:
record -> header, sha256, class, and per local struct (row|name) the path of each member.  View
names derive from the type alone (as_s16, as_pv, at02_u16), so regenerating a header after more
rows joined a class adds views but never renames one.
"""
from __future__ import annotations
import argparse, collections, hashlib, json, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER
sys.path.insert(0, str(ROOT / "tools/xform"))
from t4_fields import width, member_decl

OUT = ROOT / "include/records"


def class_name(key: str, members=None, structs=None) -> str | None:
    kind, *rest = key.split(":")
    if kind == "global":
        # union-find picks the class root by merge order; name the record after the global most
        # member structs are rooted at (stable across census re-runs)
        if members and structs:
            import collections as _c
            bases = _c.Counter(structs[n]["base"].lstrip("&") for n in members if re.fullmatch(r"&?D_[0-9A-F]{8}", structs[n]["base"]))
            if bases:
                return "Rec_" + bases.most_common(1)[0][0]
        return "Rec_" + rest[0]
    if kind == "param":
        _cont, fn, param = rest
        if not fn.startswith("func_"):
            return None            # BODY_NAME placeholders: the function is named by a macro
        return f"Rec_{fn}_{param}"
    return None


def norm(ty: str) -> str:
    return re.sub(r"\s+", " ", ty).strip()


_TAG = {"s8": "s8", "u8": "u8", "s16": "s16", "u16": "u16", "s32": "s32", "u32": "u32", "f32": "f32", "s64": "s64",
        "u64": "u64", "f64": "f64", "M2C_UNK": "m", "M2C_UNK8": "m8", "M2C_UNK16": "m16", "M2C_UNK32": "m32",
        "M2C_UNK64": "m64", "char": "c", "short": "sh", "int": "i"}

def type_tag(ty: str) -> str:
    """A view name derived from the type alone and injective over types: 's16' -> as_s16,
    'volatile u8' -> as_vu8, 'void *' -> as_pv, 'M2C_UNK *' -> as_pm, 's32 **' -> as_pps32, a function
    pointer or any other shape -> as_x<6 hex of the type text>.  Stable across regenerations."""
    ty = norm(ty); vol = "v" if "volatile" in ty else ""
    base = re.sub(r"\b(volatile|const)\b", "", ty).strip(); base = re.sub(r"\s+", " ", base)
    stars = 0
    while base.endswith("*"):
        stars += 1; base = base[:-1].strip()
    if "(" in base or base not in _TAG and base != "void":
        return "as_" + vol + "p" * stars + "x" + hashlib.sha256(ty.encode()).hexdigest()[:6]
    return "as_" + vol + "p" * stars + ("v" if base == "void" else _TAG[base])


def build(key, members, structs):
    """members: [sname]. Returns (header_text, paths {sname: {off_hex: path}}, unmapped [sname], info)."""
    votes = collections.defaultdict(collections.Counter)     # off -> {type: n}
    usable = []; unmapped = []
    for n in members:
        lay = structs[n]["layout"]
        bad = None
        parsed = {}
        for oh, ty in lay.items():
            ty = norm(ty)
            if ty.startswith("union:"):
                bad = "in-row union"; break
            if width(ty) is None:
                bad = f"unknown width: {ty}"; break
            parsed[int(oh, 16)] = ty
        if bad or not parsed:
            unmapped.append(n); continue
        usable.append((n, parsed))
        for off, ty in parsed.items():
            votes[off][ty] += 1
    if not usable:
        return None, {}, unmapped, {}
    # clusters of overlapping members (T4's rule, across functions)
    clusters = []
    for off in sorted(votes):
        w = max(width(t) for t in votes[off])
        if clusters and off < clusters[-1][1]:
            lo, hi, mem = clusters[-1]; mem[off] = votes[off]; clusters[-1] = (lo, max(hi, off + w), mem)
        else:
            clusters.append((off, off + w, {off: votes[off]}))
    lines = []; pos = 0; path = {}      # (off, type) -> access path
    for lo, hi, mem in clusters:
        if lo > pos:
            lines.append(f"    u8 pad_{pos:02X}[0x{lo - pos:X}];")
        if len(mem) == 1:
            off = next(iter(mem)); types = sorted(mem[off], key=type_tag)
            if len(types) == 1:
                lines.append("    " + member_decl(types[0], f"unk_{off:02X}"))
                path[(off, types[0])] = f"unk_{off:02X}"
            else:
                lines.append("    union { " + " ".join(member_decl(t, type_tag(t)) for t in types) + f" }} unk_{off:02X};   /* read as {', '.join(f'{t} by {mem[off][t]}' for t in types)} */")
                for t in types:
                    path[(off, t)] = f"unk_{off:02X}.{type_tag(t)}"
        else:
            views = []
            for off in sorted(mem):
                for t in sorted(mem[off], key=type_tag):
                    inner = (f"u8 pad[0x{off - lo:X}]; " if off > lo else "") + member_decl(t, "v")
                    tag = f"at{off - lo:02X}_{type_tag(t)[3:]}"
                    views.append(f"struct {{ {inner} }} {tag};")
                    path[(off, t)] = f"unk_{lo:02X}.{tag}.v"
            lines.append("    union { " + " ".join(views) + f" }} unk_{lo:02X};   /* overlapping accesses */")
        pos = hi
    name = class_name(key, members, structs)
    conts = collections.Counter(structs[n]["container"] for n, _ in usable)
    rows = len({structs[n]["row"] for n, _ in usable})
    globals_ = collections.Counter(structs[n]["base"].lstrip("&") for n, _ in usable if re.fullmatch(r"&?D_[0-9A-F]{8}", structs[n]["base"]))
    params_ = collections.Counter(f"{structs[n]['fn']}:{structs[n]['base']}" for n, _ in usable if not re.fullmatch(r"&?D_[0-9A-F]{8}", structs[n]["base"]))
    roots = (f" * Rooted at: " + ", ".join(f"{g} ({k})" for g, k in globals_.most_common(12)) + (f", +{len(globals_) - 12} more globals" if len(globals_) > 12 else "") + "\n" if globals_ else "") + \
            (f" * Reached as a parameter in: " + ", ".join(f"{g} ({k})" for g, k in params_.most_common(6)) + (f", +{len(params_) - 6} more" if len(params_) > 6 else "") + "\n" if params_ else "")
    hdr = (f"/* {name}: record class from the struct census (tools/gen_records.py).\n"
           f" * Provenance: {key}; {rows} functions ({', '.join(f'{c} {k}' for c, k in conts.most_common())}); span 0x{pos:X}.\n" + roots +
           f" * Every view here is one some function reads the offset with; member names are offsets\n"
           f" * until evidence names them.  Regenerate, never hand-edit: the census is the source. */\n"
           f"#ifndef {name.upper()}_H\n#define {name.upper()}_H\n\n#include \"common.h\"\n"
           + ("#include \"m2c_compat.h\"   /* M2C_UNK* views: rows that never needed the compat header still compile */\n" if any("M2C_" in l for l in lines) else "") + "\n"
           f"typedef struct {name} {{\n" + "\n".join(lines) + f"\n}} {name};\n\n#endif\n")
    paths = {n: {f"0x{off:X}": path[(off, ty)] for off, ty in parsed.items()} for n, parsed in usable}
    info = {"rows": rows, "structs": len(usable), "span": pos, "containers": dict(conts),
            "unions": sum(1 for l in lines if "union {" in l), "members": sum(1 for l in lines if "pad_" not in l)}
    return hdr, paths, unmapped, info


def compile_check(name):
    """gcc 2.7.2 -S of a stub that includes the header alone: duplicate members, unknown types."""
    import subprocess, tempfile
    cc = ROOT / "toolchain/compilers/gcc-2.7.2"
    with tempfile.TemporaryDirectory() as td:
        stub = Path(td) / "stub.c"; stub.write_text(f'#include "records/{name}.h"\nint stub_var;\n')
        r = subprocess.run([str(cc / "gcc"), f"-B{cc}/", "-S", "-O2", "-I", str(ROOT / "include"), "-w", str(stub), "-o", str(Path(td) / "stub.s")],
                           capture_output=True, text=True)
    return "" if r.returncode == 0 else (r.stderr or r.stdout).strip().replace(str(ROOT), "<repo>")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--min-rows", type=int, default=10); ap.add_argument("--only")
    a = ap.parse_args()
    structs = json.load(open(LEDGER / "struct_census_structs.json"))
    classes = collections.defaultdict(list)
    for n, s in structs.items():
        if s.get("class") and not n.endswith("_pre"):
            classes[s["class"]].append(n)
    OUT.mkdir(parents=True, exist_ok=True)
    records = {}; bad_headers = []
    for key, members in sorted(classes.items(), key=lambda kv: -len(kv[1])):
        if key.startswith("local:"): continue
        name = class_name(key, members, structs)
        if not name: continue
        rows = len({structs[n]["row"] for n in members})
        if rows < a.min_rows: continue
        if a.only and key not in a.only.split(",") and name not in a.only.split(","): continue
        hdr, paths, unmapped, info = build(key, members, structs)
        if hdr is None:
            print(f"{key}: no usable member struct"); continue
        p = OUT / f"{name}.h"
        if not p.exists() or p.read_text() != hdr:
            p.write_text(hdr)
        sha = hashlib.sha256(hdr.encode()).hexdigest()
        err = compile_check(name)
        if err:
            print(f"  HEADER DOES NOT COMPILE: {err[:200]}"); bad_headers.append(name)
        records[name] = {"class": key, "header": f"records/{name}.h", "sha256": sha, "needs_compat": '"m2c_compat.h"' in hdr,
                         "compiles": not err, "paths": paths, "unmapped": unmapped, **info}
        print(f"{name:28} rows {info['rows']:4} structs {info['structs']:4} span 0x{info['span']:X} members {info['members']} unions {info['unions']} unmapped {len(unmapped)}")
    json.dump(records, open(LEDGER / "records.json", "w"), indent=0)
    print(f"{len(records)} record headers in include/records/; mapping in ledger/records.json" + (f"; NOT COMPILING: {bad_headers}" if bad_headers else "; every header compiles standalone (gcc 2.7.2)"))
    sys.exit(1 if bad_headers else 0)


if __name__ == "__main__":
    main()
