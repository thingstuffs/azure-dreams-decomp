#!/usr/bin/env python3
"""Cross-function struct census (Layer 3 groundwork).

For every per-function struct T4 produced (`typedef struct S_<addr>_<n> {...}  /* <base> in <fn> */`),
record its layout and the provenance of its base:
  - a global `D_XXXXXXXX` (or `&D_...`) used directly as the base
  - a parameter: every caller's argument expression at that position (a global, a caller
    parameter, a member of a caller struct, ...) — chains are followed one hop
Then group layouts by provenance key and report agreement / conflict per group.
Output: ledger/struct_census.json and a Markdown summary on stdout.
"""
import json, re, collections, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, UP, LEDGER, rows

TYPEDEF = re.compile(r"typedef struct (S_[0-9A-F]+_[0-9a-z_]+)(?:_pre)? \{\n(.*?)\n\} \1(?:_pre)?;\s*/\* (.*?) \*/", re.S)
MEMBER = re.compile(r"^\s+(?:union \{ (.*?) \} unk_([0-9A-F]+)|(.+?)\s+(?:\(\*)?unk_([0-9A-F]+)(?:\))?(?:\([^)]*\))?;)", re.M)
DEF_HEAD = re.compile(r"^[ \t]*[A-Za-z_][A-Za-z0-9_ \*]*?\b\**(func_[0-9A-F]{8}|[A-Za-z_][A-Za-z0-9_]*)\s*\(([^;{]*)\)\s*\{", re.M)
CALL = re.compile(r"\b(func_[0-9A-F]{8})\s*\(")

def current_text(r):
    p = ROOT / "src" / r["container"] / Path(r["c_path"]).name
    return (p if p.exists() else UP / r["c_path"]).read_text(errors="replace")

def split_args(s):
    out, depth, cur = [], 0, ""
    for c in s:
        if c in "([": depth += 1
        elif c in ")]": depth -= 1
        if c == "," and depth == 0: out.append(cur.strip()); cur = ""
        else: cur += c
    if cur.strip(): out.append(cur.strip())
    return out

def layout_of(body):
    lay = {}
    for m in MEMBER.finditer(body):
        if m.group(2):
            lay[int(m.group(2), 16)] = "union:" + re.sub(r"\s+", " ", m.group(1))[:60]
        elif m.group(4) and not m.group(3).strip().startswith("u8 pad"):
            lay[int(m.group(4), 16)] = m.group(3).strip()
    return lay

def main():
    rs = rows(); by = {r["id"]: r for r in rs}
    structs = {}          # sname -> {row, fn, base, layout, container}
    params = {}           # (container, fn) -> [param names]; ptype (container, fn, idx) -> sname
    calls = collections.defaultdict(list)   # callee -> [(caller_row, args)]
    texts = {}
    for r in rs:
        if not r["exists"]: continue
        t = current_text(r); texts[r["id"]] = t
        for m in TYPEDEF.finditer(t):
            note = m.group(3); mm = re.match(r"(.+?) in (\S+)", note)
            if not mm: continue
            structs[m.group(1) + ("_pre" if "_pre" in m.group(0)[:60] else "")] = {"row": r["id"], "container": r["container"], "fn": mm.group(2), "base": mm.group(1), "layout": layout_of(m.group(2))}
        for d in DEF_HEAD.finditer(t):
            ps = [p.strip() for p in split_args(d.group(2))]
            names = [re.sub(r".*?\b([A-Za-z_][A-Za-z0-9_]*)\s*$", r"\1", p) for p in ps]
            types = [re.sub(r"\s*\b[A-Za-z_][A-Za-z0-9_]*\s*$", "", p).strip() for p in ps]
            params[(r["container"], d.group(1))] = list(zip(names, types))
        # call sites with argument text (single-line calls only)
        for line in t.splitlines():
            if line.lstrip().startswith("#"):
                continue
            for c in CALL.finditer(line):
                before = line[:c.start()]
                # a declaration or definition head: a type-ish word (possibly pointer stars) right before the name
                if re.search(r"(^|[;{}]\s*)(extern\s+|static\s+)?[A-Za-z_][A-Za-z0-9_]*(\s*\*+)?\s*\**\s*$", before) and not re.search(r"\b(return|goto|if|while|for|switch|else|case)\s*$", before):
                    continue
                rest = line[c.end():]; depth = 1; arg = ""
                for ch in rest:
                    if ch == "(": depth += 1
                    elif ch == ")":
                        depth -= 1
                        if depth == 0: break
                    arg += ch
                if depth == 0:
                    calls[c.group(1)].append((r["id"], split_args(arg)))
    # transitive provenance: union-find over (container, fn, param) nodes linked by call edges
    parent = {}
    def find(x):
        parent.setdefault(x, x)
        while parent[x] != x:
            parent[x] = parent[parent[x]]; x = parent[x]
        return x
    edges = collections.Counter()
    def union(a, b):
        edges[(a, b)] += 1
    node_structs = collections.defaultdict(list)     # node -> [sname] (structs whose base is that node)
    for sname, st in structs.items():
        base = st["base"]
        if re.fullmatch(r"&?D_[0-9A-F]{8}", base):
            node_structs["global:" + base.lstrip("&")].append(sname)
        else:
            ps = params.get((st["container"], st["fn"]))
            if ps and base in [n for n, _ in ps]:
                node_structs[f"param:{st['container']}:{st['fn']}:{base}"].append(sname)
    WIDTH = {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "s32": 4, "f32": 4, "M2C_UNK": 4}
    def wkind(ty):
        t = re.sub(r"\b(volatile|const)\b", "", ty).strip()
        if t.startswith("union:"): return "union"
        if t.endswith("*") or "(*" in t: return "ptr"
        return str(WIDTH.get(t, "?"))
    class_layout = {}
    def layout_of_class(root):
        if root in class_layout: return class_layout[root]
        lay = {}
        for n in members_of[root]:
            for off, ty in structs[n]["layout"].items():
                lay.setdefault(off, set()).add(wkind(ty))
        class_layout[root] = lay; return lay
    def compatible(la, lb):
        shared = set(la) & set(lb)
        if not shared: return True
        bad = sum(1 for o in shared if not (la[o] & lb[o]) and "union" not in la[o] | lb[o])
        return bad == 0 or bad / len(shared) <= 0.1
    members_of = collections.defaultdict(set)
    def do_merge():
        for n in list(node_structs): find(n)
        for n in parent: members_of[n] = set(node_structs.get(n, []))
        for (a, b), w in sorted(edges.items(), key=lambda kv: -kv[1]):
            ra, rb = find(a), find(b)
            if ra == rb: continue
            if compatible(layout_of_class(ra), layout_of_class(rb)):
                if rb.startswith("global:") or (not ra.startswith("global:") and rb < ra): ra, rb = rb, ra
                parent[rb] = ra; members_of[ra] |= members_of[rb]; class_layout.pop(ra, None); class_layout.pop(rb, None)
    fn_container = {}
    for r in rs:
        if r["exists"]:
            for d in DEF_HEAD.finditer(texts.get(r["id"], "")):
                fn_container[d.group(1)] = r["container"]
    for callee, sites in calls.items():
        cps = params.get((fn_container.get(callee, ""), callee))
        if not cps: continue
        for caller_row, args in sites:
            caller_fns = [d.group(1) for d in DEF_HEAD.finditer(texts[caller_row])]
            for idx, a in enumerate(args[:len(cps)]):
                callee_node = f"param:{fn_container.get(callee)}:{callee}:{cps[idx][0]}"
                if re.fullmatch(r"&?D_[0-9A-F]{8}", a):
                    union(callee_node, "global:" + a.lstrip("&"))
                elif re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", a):
                    for cf in caller_fns:
                        if a in [n for n, _ in params.get((by[caller_row]["container"], cf), [])]:
                            union(callee_node, f"param:{by[caller_row]['container']}:{cf}:{a}")
    do_merge()
    # provenance of each struct's base
    prov = collections.defaultdict(list)     # key -> [sname]
    for sname, s in structs.items():
        base = s["base"]
        if re.fullmatch(r"&?D_[0-9A-F]{8}", base):
            prov[find("global:" + base.lstrip("&"))].append(sname); continue
        ps = params.get((s["container"], s["fn"]))
        if ps and base in [n for n, _ in ps]:
            prov[find(f"param:{s['container']}:{s['fn']}:{base}")].append(sname)
        else:
            prov["local:" + s["row"] + ":" + base[:40]].append(sname)
    # agreement inside each provenance group
    groups = []
    for k, names in prov.items():
        if len(names) < 2: continue
        merged = collections.defaultdict(collections.Counter)
        for n in names:
            for off, ty in structs[n]["layout"].items():
                merged[off][re.sub(r"\b(volatile|const)\b", "", ty).strip()] += 1
        hard = sum(1 for off, c in merged.items() if len({wkind(t) for t in c}) > 1)
        soft = sum(1 for off, c in merged.items() if len(c) > 1) - hard
        layout = {f"0x{off:X}": dict(c.most_common(3)) for off, c in sorted(merged.items())}
        groups.append({"key": k, "structs": len(names), "rows": len({structs[n]["row"] for n in names}), "members": len(merged), "hard_conflicts": hard, "soft_conflicts": soft, "span": max(merged) + 4 if merged else 0, "names": names[:50], "layout": layout})
    groups.sort(key=lambda g: -g["structs"])
    json.dump({"structs": len(structs), "groups": groups, "provenance_keys": len(prov)}, open(LEDGER / "struct_census.json", "w"), indent=0)
    kinds = collections.Counter(k.split(":")[0] for k in prov)
    print(f"structs {len(structs)} from {len({s['row'] for s in structs.values()})} rows; provenance keys {len(prov)} ({dict(kinds)}); groups with >=2 structs: {len(groups)}")
    print("\n| provenance | structs | rows | members | hard conflicts | soft (sign/qualifier) | span |\n|---|---:|---:|---:|---:|---:|---:|")
    for g in groups[:25]:
        print(f"| {g['key'][:60]} | {g['structs']} | {g['rows']} | {g['members']} | {g['hard_conflicts']} | {g['soft_conflicts']} | 0x{g['span']:X} |")
    for g in groups[:4]:
        print(f"\n{g['key']}: " + "  ".join(f"{o}:{'/'.join(f'{t}×{n}' for t, n in c.items())}" for o, c in list(g["layout"].items())[:16]))

if __name__ == "__main__":
    main()
