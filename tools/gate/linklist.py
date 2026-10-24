"""Link lists: one TU, many placements (v0, decision 59), whole-image byte maps (v1, decision 60b).

v1 keeps the code entry shape and adds metadata intervals. validate_image + coverage require exact tiling,
conserved census labels and non-cyclic load-image references. Only code entries enter the placement indices;
all existing build and rebinding callers consequently ignore metadata. See docs/LINK_LISTS.md.

config/link/<container>/<image>.json describes ONE load image (a bank / floor slot / scene image):

    {"schema": "azure-clean.linklist.v0", "image": "dungeon/bank_fad000", "container": "dungeon",
     "foff": "0xFAD000", "size": "0x6000", "vma": "0x8016A800", "layout": "bank_fa7000_family",
     "evidence": "...", "symbols": {},
     "entries": [{"row": "dungeon/func_80F90664", "tu": "src/dungeon/func_80F8A664.c",
                  "home": "dungeon/func_80F8A664", "foff": "0xFB0664", "vma": "0x8016DE64", "size": 56,
                  "bindings": {}}]}

An entry places the TU of its `home` row at `vma` inside this image. The TU's object spells every symbol by its
HOME address name (func_/D_<addr in the home image>; tools/ccproc.py turns names.tsv aliases back into those), so
a placement is resolved by ADDRESS, never by a readable name (`binding` lists the rules). A rename in
config/names.tsv or in the TU therefore cannot change what a placement links to. The home row is itself an entry
of its own image's link list and compiles without rebinding.

The window gate (overlay_local_gate.compile_c_segments) compiles the TU for the placement's segment, rewrites the
object's symbols with objcopy (`rebind_object`), and the unchanged mini-link + window compare proves the bytes at
that address. tools/lanes/proof_receipts.window_inputs binds the TU (through source_layout's `source_row`
redirection) and the link-list files that decide the placement's symbols (`window_files`).

With no config/link/ directory every function here is inert: no placement, no rebinding, no extra inputs.
"""
from __future__ import annotations
import hashlib, json, re, subprocess
from functools import lru_cache
from pathlib import Path

SCHEMA = "azure-clean.linklist.v0"
MAP_SCHEMA = "azure-clean.linklist.v1"
CENSUS_LABELS = ("proven_code", "library_code", "strongly_code", "proven_data",
                 "noncode_typing_pending", "padding_leftover", "unknown")
ADDR = re.compile(r"^(func|D)_([0-9A-F]{8})$")
OBJCOPY = "mipsel-linux-gnu-objcopy"
NM = "mipsel-linux-gnu-nm"
ENTRY_KEYS = {"row", "tu", "home", "foff", "vma", "size"}
ENTRY_OPTIONAL = {"bindings", "evidence", "body_offset"}
IMAGE_KEYS = {"schema", "image", "container", "foff", "size", "vma", "entries"}
IMAGE_OPTIONAL = {"layout", "evidence", "symbols", "load_evidence"}


def is_code(entry):
    """Only the unchanged v0 TU shape participates in compilation and rebinding."""
    return "kind" not in entry


def census_label(entry):
    if is_code(entry):
        return "proven_code"
    kind = entry["kind"]
    if kind in ("asset", "code_region"):
        return entry["census_label"]
    if kind == "data":
        return "noncode_typing_pending" if entry["type"] == "typing pending" else "proven_data"
    return {"padding": "padding_leftover", "leftover": "padding_leftover", "unresolved": "unknown"}[kind]


def _totals(value):
    if not isinstance(value, dict) or set(value) - set(CENSUS_LABELS):
        raise ValueError("invalid census totals")
    out = {k: value.get(k, 0) for k in CENSUS_LABELS}
    if any(type(v) is not int or v < 0 for v in out.values()):
        raise ValueError("census totals must be nonnegative integer byte counts")
    return out


def _metadata(raw):
    common = {"kind", "foff", "size", "evidence"}
    extra = {"data": {"type"}, "padding": set(), "leftover": {"reason"}, "unresolved": set(),
             "asset": {"format", "sha256", "extractor", "census_label"}, "code_region": {"census_label"},
             "image": {"ref"}}
    kind = raw.get("kind")
    optional = {"vma"} | ({"sha256", "extractor", "symbols"} if kind in ("data", "padding") else set())
    if kind not in extra or not common | extra[kind] <= set(raw) or set(raw) - common - extra[kind] - optional:
        raise ValueError("link list metadata entry keys: " + str(kind))
    for k in (common | extra[kind]) - {"foff", "size"}:
        if not isinstance(raw[k], str) or not raw[k].strip():
            raise ValueError("metadata field must be nonempty text: " + k)
    emitted = kind in ("data", "padding") and bool(set(raw) & {"sha256", "extractor", "symbols"})
    if emitted:
        if not {"sha256", "extractor", "symbols"} <= set(raw):
            raise ValueError("emitted data/padding needs sha256, extractor and symbols")
        if num(raw['size']) != 4 or num(raw['foff']) % 4:
            raise ValueError("emitted data/padding must be one aligned word")
        symbols = raw["symbols"]
        if (not isinstance(symbols, dict) or not symbols
                or any(not isinstance(k, str) or not ADDR.fullmatch(k)
                       or num(v) != int(k.split('_')[1], 16) for k, v in symbols.items())
                or len({num(v) for v in symbols.values()}) != 1):
            raise ValueError("emitted symbols must bind canonical address identities")
    elif kind != "asset" and set(raw) & {"sha256", "extractor", "symbols"}:
        raise ValueError("extraction fields require asset or emitted data/padding")
    if kind == "asset" or emitted:
        if not isinstance(raw["sha256"], str) or not re.fullmatch(r"[0-9a-f]{64}", raw["sha256"]):
            raise ValueError("invalid asset sha256")
        if raw["extractor"] != "container-slice-v1":
            raise ValueError("unknown asset extractor: " + raw["extractor"])
        if kind == "asset" and raw["census_label"] not in ("proven_data", "noncode_typing_pending"):
            raise ValueError("asset must retain a non-code census label")
    if kind == "code_region" and raw["census_label"] not in CENSUS_LABELS[:3]:
        raise ValueError("code_region must retain a code census label")


def validate_image(doc, path="<image>"):
    """Validate one document without requiring its references/homes to be loaded yet."""
    whole = doc.get("schema") == MAP_SCHEMA
    if doc.get("schema") not in (SCHEMA, MAP_SCHEMA):
        raise ValueError("unknown link list schema: " + str(path))
    required = IMAGE_KEYS | ({"census"} if whole else set())
    optional = IMAGE_OPTIONAL | ({"provenance"} if whole else set())
    if not required <= set(doc) or set(doc) - required - optional:
        raise ValueError("link list image keys: " + str(path))
    if whole and (not isinstance(doc["image"], str) or not re.fullmatch(r"[a-z][a-z0-9_]*/[A-Za-z0-9_]+", doc["image"])):
        raise ValueError("invalid byte map image id")
    if whole and "provenance" in doc:
        provenance = doc["provenance"]
        if not isinstance(provenance, dict) or set(provenance) != {"labels_sha256", "coverage_sha256", "source"}:
            raise ValueError("byte map provenance keys")
        if any(not isinstance(provenance[k], str) or not re.fullmatch(r"[0-9a-f]{64}", provenance[k])
               for k in ("labels_sha256", "coverage_sha256")) or not isinstance(provenance["source"], str) or not provenance["source"].strip():
            raise ValueError("invalid byte map provenance")
    if "load_evidence" in doc:
        proof = doc["load_evidence"]
        if (not isinstance(proof, dict) or set(proof) != {"path", "record_sha256"}
                or proof["path"] != "ledger/instance_load_regions.jsonl"
                or not isinstance(proof["record_sha256"], str)
                or not re.fullmatch(r"[0-9a-f]{64}", proof["record_sha256"])):
            raise ValueError("invalid image load_evidence")
    img = dict(doc, foff=num(doc["foff"]), size=num(doc["size"]),
               vma=None if whole and doc["vma"] is None else num(doc["vma"]), path=str(path),
               symbols=_addr_map(doc.get("symbols"), "image symbols"))
    if img["foff"] < 0 or img["size"] <= 0:
        raise ValueError("empty image or negative image offset: " + str(path))
    if not isinstance(doc["entries"], list):
        raise ValueError("entries must be a list")
    last, entries = img["foff"], []
    for raw in doc["entries"]:
        code = is_code(raw)
        if code:
            if not ENTRY_KEYS <= set(raw) or set(raw) - ENTRY_KEYS - ENTRY_OPTIONAL:
                raise ValueError("link list entry keys: %s in %s" % (raw.get("row"), path))
        elif not whole:
            raise ValueError("metadata requires linklist.v1")
        else:
            _metadata(raw)
        e = dict(raw, foff=num(raw["foff"]), size=num(raw["size"]), image=img["image"], container=img["container"])
        name = raw.get("row", raw.get("kind"))
        if e["size"] <= 0 or not img["foff"] <= e["foff"] < e["foff"] + e["size"] <= img["foff"] + img["size"]:
            raise ValueError("entry outside its image: " + str(name))
        if raw.get('kind') in ('data', 'padding') and raw.get('extractor') and img['vma'] is not None:
            expected = img['vma'] + e['foff'] - img['foff']
            if any(num(v) != expected for v in raw['symbols'].values()):
                raise ValueError('emitted symbol disagrees with image load address')
        if code or "vma" in raw:
            e["vma"] = num(raw["vma"])
            if img["vma"] is None or e["vma"] - img["vma"] != e["foff"] - img["foff"]:
                raise ValueError("entry vma is not image vma + offset: " + str(name))
        if e["foff"] < last:
            raise ValueError("entries out of order or overlapping in %s at %s" % (img["image"], name))
        if whole and e["foff"] != last:
            raise ValueError("byte map gap in %s at 0x%X" % (img["image"], last))
        last = e["foff"] + e["size"]
        if code:
            e["bindings"] = _addr_map(raw.get("bindings"), "entry bindings")
            if "body_offset" in raw:
                # A home whose registered extent begins with a data prefix it keeps owning (a module member
                # with body_offset): its copies place only the function body that follows the prefix.
                bo = raw["body_offset"]
                if (type(bo) is not int or bo <= 0 or bo % 4 or bo >= e["size"]
                        or raw["row"] != raw["home"]):
                    raise ValueError("body_offset must be a positive word offset inside a home entry: " + str(name))
        entries.append(e)
    if whole:
        if last != img["foff"] + img["size"]:
            raise ValueError("byte map trailing gap in " + img["image"])
        img["census"] = _totals(doc["census"])
    img["entries"] = entries
    return img


def coverage(images):
    """Prove exact per-image tiling (in validate_image), reference extents and census conservation.

    File-only container images may reference load images; references carry no duplicate TU and no invented VMA.
    The recursive walk counts each referenced byte once and rejects cycles, stale totals and v0 children.
    """
    done, active = {}, set()
    def visit(img):
        key = img["image"]
        if key in active:
            raise ValueError("byte map image reference cycle: " + key)
        if key in done:
            return done[key]
        if img["schema"] != MAP_SCHEMA:
            raise ValueError("byte map reference needs a whole-image v1 child: " + key)
        active.add(key)
        totals = dict.fromkeys(CENSUS_LABELS, 0)
        for e in img["entries"]:
            if e.get("kind") == "image":
                child = images.get(e["ref"])
                if child is None or (child["container"], child["foff"], child["size"]) != (img["container"], e["foff"], e["size"]):
                    raise ValueError("byte map image reference extent/container differs: " + e["ref"])
                for k, v in visit(child).items():
                    totals[k] += v
            else:
                totals[census_label(e)] += e["size"]
        active.remove(key)
        if totals != img["census"] or sum(totals.values()) != img["size"]:
            raise ValueError("byte map census totals differ: " + key)
        done[key] = totals
        return totals
    for img in images.values():
        if img["schema"] == MAP_SCHEMA:
            visit(img)
    return done


def num(v):
    if isinstance(v, bool):
        raise ValueError("not an address: " + repr(v))
    return int(v) if isinstance(v, int) else int(str(v), 0)


def family(container):
    return "dungeon" if container == "dungeon_engine" else container


def link_dir(root):
    return Path(root) / "config" / "link"


def files(root):
    d = link_dir(root)
    if not d.is_dir():
        return []
    return sorted(p for x in d.iterdir() if x.is_dir() for p in x.glob("*.json"))


def _stamp(paths):
    out = []
    for p in paths:
        s = p.stat()
        out.append((str(p), s.st_ino, s.st_mtime_ns, s.st_ctime_ns, s.st_size))
    return tuple(out)


def _addr_map(value, what):
    if value is None:
        return {}
    if not isinstance(value, dict):
        raise ValueError(what + " must be an object")
    return {num(k): num(v) for k, v in value.items()}


@lru_cache(maxsize=8)
def _load(stamp):
    images, by_place, by_row = {}, {}, {}
    for path, *_ in stamp:
        doc = json.loads(Path(path).read_text())
        if doc["container"] != Path(path).parent.name or not doc["image"].startswith(doc["container"] + "/"):
            raise ValueError("link list lives outside its container directory: " + path)
        img = validate_image(doc, path)
        if img["image"] in images:
            raise ValueError("duplicate image " + img["image"])
        images[img["image"]] = img
        for e in img["entries"]:
            if not is_code(e):
                continue
            if family(e["row"].split("/", 1)[0]) != doc["container"]:
                raise ValueError("entry row belongs to another container: " + e["row"])
            key = (doc["container"], e["foff"])
            if key in by_place or e["row"] in by_row:
                raise ValueError("placement listed twice: " + e["row"])
            by_place[key] = e
            by_row[e["row"]] = e
    coverage(images)
    for e in by_row.values():
        if e["home"] not in by_row:
            raise ValueError("home row is not placed in any link list: " + e["home"])
        h = by_row[e["home"]]
        if h["home"] != h["row"] or h["tu"] != e["tu"]:
            raise ValueError("home entry must be its own home and share the TU: " + e["row"])
        if e is not h and (h["size"] - h.get("body_offset", 0)) != e["size"]:
            raise ValueError("placement size differs from its home: " + e["row"])
        if e is h and e["bindings"]:
            raise ValueError("a home entry takes no bindings: " + e["row"])
    # rule 3 table: image -> home vma -> [(home image, vma of that TU's placement in this image)]
    local = {}
    for e in by_row.values():
        h = by_row[e["home"]]
        if e is not h:
            local.setdefault(e["image"], {}).setdefault(h["vma"] + h.get("body_offset", 0), []).append((h["image"], e["vma"]))
    return images, by_place, by_row, local


def load(root):
    """(images, {(container, foff): entry}, {row id: entry}, rule-3 table) over EVERY link list (a placement's
    home may live in another container's lists); four empty maps without config/link/."""
    return _load(_stamp(files(root)))


def placement(root, container, foff, row=None):
    """The link-list entry placing a TU at (container, foff), or None for an own-file row. `row` (the segment's
    registered row id) must be the entry's row: a list naming another row at this span is refused."""
    e = load(root)[1].get((family(container), foff))
    if e is not None and row is not None and e["row"] != row:
        raise ValueError("link list entry at %s 0x%X names %s, the segment is %s" % (container, foff, e["row"], row))
    return e


def is_placement(root, row_id):
    e = load(root)[2].get(row_id)
    return e is not None and e["home"] != row_id


def evidence_foff(root, entry):
    """The file offset whose frozen bank evidence (maspsx noreturn census) a placement compiles with: its HOME's.
    The TU's assembly spells home addresses, so the census must too; the home's census is the one that proved
    the home bytes, and the same text saw the same declarations in every bank it was linked into."""
    home = load(root)[2][entry["home"]]
    if home["container"] != entry["container"]:
        raise ValueError("cross-container placement: use evidence_scope: " + entry["row"])
    return home["foff"]


def evidence_scope(root, entry):
    """(family, file offset) of the frozen evidence a placement compiles with: its HOME's (decision 75 (A): the
    home may live in another container; the home's family evidence then applies, exactly as its own window
    compiles it)."""
    home = load(root)[2][entry["home"]]
    return family(home["container"]), home["foff"]


def evidence_offsets(root, container, offsets):
    """Home offsets of the same-container placements among (container, offsets): the extra evidence a window
    binds.  Cross-container homes are bound by cross_evidence (a separate key, so same-container digests stay)."""
    by_place = load(root)[1]
    out = set()
    for off in offsets:
        e = by_place.get((family(container), off))
        if e is not None and e["home"] != e["row"]:
            fam, foff = evidence_scope(root, e)
            if fam == family(container):
                out.add(foff)
    return out


def cross_evidence(root, container, offsets):
    """{home family: {home offsets}} for the cross-container placements among (container, offsets)."""
    by_place = load(root)[1]
    out = {}
    for off in offsets:
        e = by_place.get((family(container), off))
        if e is not None and e["home"] != e["row"]:
            fam, foff = evidence_scope(root, e)
            if fam != family(container):
                out.setdefault(fam, set()).add(foff)
    return out


def _inside(img, address):
    return img["vma"] <= address < img["vma"] + img["size"]


def binding(root, entry, address, *, home_image=None):
    """Linker semantics for one placement, by address (first rule that applies):
    1. the TU's own entry point -> this placement's vma
    2. entry.bindings (per-placement override, evidence-backed)
    3. a symbol whose home row is ALSO placed in this image -> that placement (local definition wins); a symbol
       inside the TU's home image means that image's row, any other address must be unambiguous
    4. both images carry the same `layout` tag (same-layout copies, e.g. the banks of one bank family) and the
       symbol lies in the home image -> shifted by the image delta
    5. image.symbols (per-image map, e.g. the image's own data objects)
    6. unchanged (resident: SLUS / the engine build this image links against)"""
    return _binding(load(root), entry, address, home_image)


def _binding(tables, entry, address, home_image=None):
    """Same address rules over one validator's already observed link census."""
    images, _, by_row, local = tables
    home = by_row[entry["home"]]
    if entry["row"] == home["row"]:
        return address
    if address == home["vma"] + home.get("body_offset", 0):
        return entry["vma"]
    if address in entry["bindings"]:
        return entry["bindings"][address]
    img, himg = images[entry["image"]], images[home_image or home["image"]]
    hits = local.get(entry["image"], {}).get(address, [])
    if _inside(himg, address):
        hits = [h for h in hits if h[0] == himg["image"]]
    if len(hits) > 1:
        raise ValueError("link list %s: address 0x%08X is the home of %d TUs placed here; bind it explicitly in %s"
                         % (img["image"], address, len(hits), entry["row"]))
    if hits:
        return hits[0][1]
    if img.get("layout") and img.get("layout") == himg.get("layout") and _inside(himg, address):
        return address + (img["vma"] - himg["vma"])
    return img["symbols"].get(address, address)


def rebind_object(root, entry, obj, log=None):
    """Rewrite the TU object's home-address symbols to this placement's addresses (in place)."""
    by_row = load(root)[2]
    if entry["row"] == by_row[entry["home"]]["row"]:
        return {}
    out = subprocess.run([NM, str(obj)], capture_output=True, text=True, check=True).stdout
    names = {l.split()[-1] for l in out.splitlines() if l.split()}
    renames = {}
    for n in sorted(names):
        m = ADDR.match(n)
        if not m:
            continue
        new = "%s_%08X" % (m.group(1), binding(root, entry, int(m.group(2), 16)))
        if new != n:
            renames[n] = new
    if log is not None:
        Path(log).write_text("".join("%s -> %s\n" % kv for kv in sorted(renames.items())))
    if not renames:
        return {}
    # Several home REFERENCES may bind to one destination address (the destination keeps one table where
    # the home kept two, opus_place1): those undefined symbols merge into one name, applied in successive
    # objcopy passes (objcopy refuses two redefinitions onto one target in a single call). The link
    # resolves every reference by address, so the merge is exact. A definition never merges.
    undefined = {l.split()[-1] for l in out.splitlines() if len(l.split()) == 2 and l.split()[0] == "U"}
    groups = {}
    for o, n in renames.items():
        groups.setdefault(n, []).append(o)
    clash = set(renames.values()) & (names - set(renames))
    if (any(len(v) > 1 and not set(v) <= undefined for v in groups.values())
            or not clash <= undefined or any(not set(groups[n]) <= undefined for n in clash)):
        raise SystemExit("link list %s: rebinding of %s collides with an existing symbol" % (entry["image"], entry["row"]))
    pending, passes = dict(renames), []
    while pending:
        batch = {}
        for o, n in list(pending.items()):
            if n not in batch.values():
                batch[o] = n
                del pending[o]
        passes.append(batch)
    for batch in passes:
        args = [OBJCOPY]
        for o, n in batch.items():
            args += ["--redefine-sym", o + "=" + n, "--rename-section", ".text." + o + "=.text." + n,
                     "--rename-section", ".rel.text." + o + "=.rel.text." + n]
        subprocess.run(args + [str(obj)], check=True, capture_output=True, text=True)
    return renames


def window_files(root, row_ids):
    """Link-list files that decide the bytes of these rows (bound into window inputs): for every placement among
    them its own image (rules 1-3, 5), its home's image (rule 4) and the home image of every other placement in
    its image (rule 3). Home rows and own-file rows bind nothing, so with no placements this is [] and a
    link-list edit re-keys only the windows holding affected placements."""
    images, _, by_row, _ = load(root)
    members = {}
    for e in by_row.values():
        members.setdefault(e["image"], []).append(e)
    out = set()
    for rid in row_ids:
        e = by_row.get(rid)
        if e is None or e["home"] == rid:
            continue
        out.add(images[e["image"]]["path"])
        for x in [e, *members[e["image"]]]:
            if x["home"] != x["row"]:
                out.add(images[by_row[x["home"]]["image"]]["path"])
    # These records authorize no-region bases. Their bytes are proof inputs too.
    for img in images.values():
        if img["path"] in out and img.get("load_evidence"):
            out.add(str(Path(root) / img["load_evidence"]["path"]))
    base = Path(root).absolute()
    return sorted(str(Path(p).absolute().relative_to(base)) for p in out)


# Load-region record kinds that establish a link base (ledger/instance_load_regions.jsonl). A record
# with any other method (a heuristic or a future free-form kind) cannot authorize a no-region base.
LOAD_METHODS = ("validated ", "internal link-evidence")


def placement_vma(root, container, foff, size, row, proven_delta=None, *, allow_legacy=False):
    """A fileless placement's load address, checked against a proven region or load record.

    Solved regions still require rowbase promotion. A no-region image must bind an exact
    current instance-load-region record; free-form evidence text cannot authorize a base.
    """
    e = placement(root, container, foff, row)
    if e is None or e["home"] == row:
        return None
    if e["size"] != size:
        raise ValueError("placement extent differs from split: " + row)
    img = load(root)[0][e["image"]]
    # Existing placements keep their original proven-rowbase/window behavior.
    # Only an explicitly evidenced image opts into the new no-region link path.
    if allow_legacy and not img.get("load_evidence"):
        return None
    if proven_delta is not None:
        if e["vma"] != foff + proven_delta:
            raise ValueError("placement vma disagrees with proven rowbase: " + row)
        return e["vma"]
    root = Path(root)
    from gate_read_cache import read_records
    region_path = root / "config/overlays" / (family(container) + ".rowbase.jsonl")
    for region in read_records(region_path) if region_path.exists() else ():
        if num(region["foff_start"]) <= foff < num(region["foff_end"]):
            raise ValueError("placement requires proven rowbase promotion: " + row)
    img = load(root)[0][e["image"]]
    proof = img.get("load_evidence")
    if proof is None:
        raise ValueError("placement image has no checked load evidence: " + row)
    hits = [r for r in read_records(root / proof["path"])
            if hashlib.sha256(json.dumps(r, sort_keys=True, separators=(",", ":")).encode()).hexdigest()
            == proof["record_sha256"]]
    if len(hits) != 1:
        raise ValueError("placement load evidence is missing or stale: " + row)
    r = hits[0]
    if (r.get("schema") != "azure-clean.instance-load-region.v1"
            or r["container"] != family(container)
            or not isinstance(r.get("method"), str) or not r["method"].startswith(LOAD_METHODS) or not r.get("evidence")
            or not num(r["foff"]) <= img["foff"] < img["foff"] + img["size"] <= num(r["foff"]) + num(r["size"])
            or num(r["base"]) - num(r["foff"]) != num(r["delta"])
            or img["vma"] - img["foff"] != num(r["delta"])):
        raise ValueError("placement image disagrees with load evidence: " + row)
    return e["vma"]


def split_vma(rec):
    """The address a split record's object is linked at (its true base when it has one)."""
    if isinstance(rec.get("true_vram"), int):
        return rec["true_vram"]
    if rec.get("true_name") and ADDR.match(rec["true_name"]):
        return int(rec["true_name"][-8:], 16)
    return rec.get("vram")


def check(root, splits, registry, tu_of):
    """Consistency of the link lists with the row database (tools/row_db.py check). Returns a list of problems.
    splits: {container: [split records]} (dungeon_engine mirror excluded); registry: {row id: rows.jsonl record};
    tu_of(row id) -> the resolved source path of an own-file row, relative to the root."""
    try:
        images, _, by_row, _ = load(root)
    except (OSError, ValueError, KeyError, TypeError) as exc:
        return ["link lists: " + str(exc)]
    if not by_row:
        return []
    bad = []
    if (Path(root)/'config/overlays/module_placements.json').exists():
        try:
            import overlay_module_placements as MP
            MP.load(root)
            G=MP.authority()
            if G.read_json(Path(root)/'ledger/splits/overlay_modules.build.json')!=G.graph(root):
                bad.append('module placement physical graph stale')
        except (OSError,ValueError,KeyError,TypeError) as exc:
            bad.append('module placements: '+str(exc))
    index = {}
    for cont, recs in splits.items():
        for r in recs:
            if r.get("func_vram") and not r.get("rerun"):
                index.setdefault(cont + "/" + r["func_vram"], []).append(r)
    module_rows = set()
    module_body = {}
    mpath = Path(root) / "config/overlays/modules.json"
    if mpath.exists():
        for m in json.loads(mpath.read_text()).get("modules", []):
            module_rows.update(a["id"] for k in ("members", "data_members") for a in m.get(k, []))
            module_body.update((a["id"], a.get("body_offset", 0)) for a in m.get("members", []))
    for rid, e in sorted(by_row.items()):
        where = "link list %s: %s" % (e["image"], rid)
        recs = index.get(rid, [])
        if len(recs) != 1:
            bad.append("%s has %d split records" % (where, len(recs))); continue
        s = recs[0]
        if s.get("result") != "MATCH" or s.get("source_kind", "c") != "c":
            bad.append(where + " is not a MATCH C row")
        if s.get("foff") != e["foff"] or int(s.get("size") or 0) != e["size"]:
            bad.append(where + " extent differs from its split record")
        if split_vma(s) != e["vma"]:
            bad.append("%s vma 0x%X, split record links at 0x%X" % (where, e["vma"], split_vma(s) or 0))
        if rid in module_rows and e["home"] != rid:
            # A home may be a module member: its member file is compiled standalone at the placement and the
            # window gate proves it (or fails closed). A placement row inside a module is a module placement.
            bad.append(where + " is both a home module member and a copy (duplicate physical ownership)")
        if "body_offset" in e and (module_body.get(rid) != e["body_offset"]
                                   or s.get("native_prefix_bytes") != e["body_offset"]):
            # The prefix stays with its module owner: the module member, the split record and this entry
            # must agree on it before any body-only copy is accepted.
            bad.append(where + " body_offset disagrees with its module member or split prefix")
        reg = registry.get(rid)
        if reg is None:
            bad.append(where + " is not registered"); continue
        if e["home"] == rid:
            if reg.get("source_row"):
                bad.append(where + " is a home but carries source_row")
            elif tu_of(rid) != e["tu"]:
                bad.append("%s tu %s, the home row's source is %s" % (where, e["tu"], tu_of(rid)))
        elif reg.get("source_row") != e["home"]:
            bad.append("%s source_row %s, link list home %s (rerun tools/registry.py)" % (where, reg.get("source_row"), e["home"]))
    for rid, reg in registry.items():
        if reg.get("source_row") and rid not in by_row:
            bad.append("registry: %s carries source_row but no link list places it" % rid)
    return bad
