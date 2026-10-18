#!/usr/bin/env python3
"""Generate/check whole-image link lists from an evidenced, disjoint census export.

See docs/LINK_LISTS.md. No inference of data types or leftover status happens here.
Retail is read only to verify hashes, never serialized into a map or receipt.
"""
from __future__ import annotations

import argparse
from collections import defaultdict
import hashlib
import json
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent / "gate"))
import linklist as L
import byte_map_format as F

INPUT_SCHEMA = "azure-clean.census-map.v1"
IMAGE_ID = re.compile(r"[a-z][a-z0-9_]*/[A-Za-z0-9_]+\Z")
RETAIL = {"main": "work/disc/containers/MAIN_MAIN.BIN", "town": "work/disc/containers/TOWN_TOWN.BIN",
          "dungeon": "work/disc/containers/DUNGEON_DUNGEON.BIN", "ovmovie": "work/disc/containers/OVMOVIE.BIN",
          "slus": "baserom/slus_006.14"}


def sha256(path):
    h = hashlib.sha256()
    with Path(path).open("rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()


def read_jsonl(path):
    with Path(path).open() as f:
        for n, line in enumerate(f, 1):
            if line.strip():
                try:
                    yield json.loads(line)
                except ValueError as exc:
                    raise ValueError(f"{path}:{n}: invalid JSON") from exc


def image_path(root, image, catalogue=None):
    if not IMAGE_ID.fullmatch(image):
        raise ValueError("unsafe image id: " + image)
    return Path(root) / (catalogue or "config/link") / (image + ".json")


def load_maps(root, catalogue=None):
    """Read either the production placement catalogue or an explicit byte-map catalogue.

    A separate catalogue can extend coverage without re-keying compilation receipts for
    unchanged placement inputs. Both use the identical production validator and indices.
    """
    if catalogue is None:
        return L.load(root)
    directory = Path(root) / catalogue
    documents = F.load_documents(directory, root)
    # v1 JSON remains readable for migration and small caller-supplied fixtures.
    documents.extend((json.loads(p.read_text()), str(p))
                     for p in sorted(directory.glob('*/*.json')))
    return index_documents(documents)


def index_documents(documents):
    """Use production geometry/census validation and unchanged placement rules."""
    images, by_place, by_row = {}, {}, {}
    for doc, path in documents:
        img = L.validate_image(doc, path)
        if img['image'] in images:
            raise ValueError('duplicate image '+img['image'])
        images[img['image']] = img
        for e in img['entries']:
            if not L.is_code(e):
                continue
            if L.family(e['row'].split('/', 1)[0]) != img['container']:
                raise ValueError('entry row belongs to another container: '+e['row'])
            key = (img['container'], e['foff'])
            if key in by_place or e['row'] in by_row:
                raise ValueError('placement listed twice: '+e['row'])
            by_place[key] = e
            by_row[e['row']] = e
    L.coverage(images)
    local = {}
    for e in by_row.values():
        if e['home'] not in by_row:
            raise ValueError('home row is not placed: '+e['home'])
        h = by_row[e['home']]
        if h['home'] != h['row'] or h['tu'] != e['tu'] or h['size'] != e['size']:
            raise ValueError('home TU/size differs: '+e['row'])
        if e is h and e['bindings']:
            raise ValueError('a home entry takes no bindings: '+e['row'])
        if e is not h:
            local.setdefault(e['image'], {}).setdefault(h['vma'], []).append((h['image'], e['vma']))
    return images, by_place, by_row, local


def totals(spans):
    out = dict.fromkeys(L.CENSUS_LABELS, 0)
    for s in spans:
        out[s["label"]] += s["size"]
    return out


def read_labels(path):
    headers, spans = {}, defaultdict(list)
    for r in read_jsonl(path):
        image = r.get("image", "")
        if not IMAGE_ID.fullmatch(image):
            raise ValueError("unsafe/missing census image id: " + image)
        if "schema" in r:
            allowed = {"schema", "image", "container", "foff", "size", "vma", "census", "evidence", "children"}
            if r["schema"] != INPUT_SCHEMA or image in headers or set(r) - allowed:
                raise ValueError("invalid/duplicate census header: " + image)
            if not {"container", "foff", "size", "vma", "census", "evidence"} <= r.keys():
                raise ValueError("incomplete census header: " + image)
            if image.split("/")[0] != r["container"] or r["container"] not in RETAIL:
                raise ValueError("census header container differs: " + image)
            headers[image] = dict(r, foff=L.num(r["foff"]), size=L.num(r["size"]), census=L._totals(r["census"]))
        else:
            allowed = {"image", "foff", "size", "label", "evidence", "kind", "type", "format", "sha256", "extractor", "reason"}
            if set(r) - allowed or not {"foff", "size", "label", "evidence"} <= r.keys():
                raise ValueError("invalid census span keys: " + image)
            if r["label"] not in L.CENSUS_LABELS or not isinstance(r["evidence"], str) or not r["evidence"].strip():
                raise ValueError("invalid census label/evidence: " + image)
            spans[image].append(dict(r, foff=L.num(r["foff"]), size=L.num(r["size"])))
    if not headers or set(spans) != set(headers):
        raise ValueError("census headers and span images differ")
    for image, h in headers.items():
        last = h["foff"]
        if last < 0 or h["size"] <= 0:
            raise ValueError("invalid census image extent: " + image)
        for s in spans[image]:
            if s["foff"] != last or s["size"] <= 0:
                raise ValueError("census spans have gap/overlap/order error: " + image)
            last += s["size"]
        if last != h["foff"] + h["size"] or totals(spans[image]) != h["census"]:
            raise ValueError("census extent/totals differ: " + image)
    return headers, spans


def clipped(spans, start, end):
    for s in spans:
        a, b = max(start, s["foff"]), min(end, s["foff"] + s["size"])
        if a < b:
            yield dict(s, foff=a, size=b-a)


def metadata(span, retail=None):
    label = span["label"]
    kind = span.get("kind")
    if kind is None:
        kind = ("code_region" if label in L.CENSUS_LABELS[:3] else
                "data" if label in L.CENSUS_LABELS[3:5] else
                "padding" if label == "padding_leftover" else "unresolved")
    if label == "padding_leftover" and "kind" not in span:
        raise ValueError("padding_leftover needs explicit kind padding or leftover")
    out = {"kind": kind, "foff": hex(span["foff"]), "size": span["size"], "evidence": span["evidence"]}
    if kind == "data":
        if label == "noncode_typing_pending":
            out["type"] = "typing pending"
        else:
            out["type"] = span.get("type")
            if not out["type"] or out["type"] == "typing pending":
                raise ValueError("proven_data needs its evidenced type (or an asset format)")
    if kind in ("asset", "code_region"):
        out["census_label"] = label
    if kind == "leftover":
        out["reason"] = span.get("reason")
    if kind == "asset":
        out.update(format=span.get("format"), sha256=span.get("sha256"), extractor=span.get("extractor"))
        if retail is not None:
            retail.seek(span["foff"])
            blob = retail.read(span["size"])
            if len(blob) != span["size"] or hashlib.sha256(blob).hexdigest() != out["sha256"]:
                raise ValueError("asset slice sha256 differs at " + out["foff"])
    L._metadata(out)
    if L.census_label(out) != label:
        raise ValueError("kind contradicts census label: " + kind)
    return out


def flatten(images, image):
    """Yield leaf intervals, never double-counting a container's referenced load image."""
    for e in images[image]["entries"]:
        if e.get("kind") == "image":
            yield from flatten(images, e["ref"])
        else:
            yield {"foff": e["foff"], "size": e["size"], "label": L.census_label(e)}


def compare_labels(actual, expected, image):
    """Compare labels at every boundary, allowing equivalent adjacent span coalescing."""
    actual, expected = list(actual), list(expected)
    if not actual or not expected:
        raise ValueError("empty label comparison: " + image)
    i = j = 0
    pos = actual[0]["foff"]
    while i < len(actual) and j < len(expected):
        a, e = actual[i], expected[j]
        if not (a["foff"] <= pos < a["foff"]+a["size"] and e["foff"] <= pos < e["foff"]+e["size"]) or a["label"] != e["label"]:
            raise ValueError("map/census label differs in %s at 0x%X" % (image, pos))
        pos = min(a["foff"]+a["size"], e["foff"]+e["size"])
        i += pos == a["foff"]+a["size"]
        j += pos == e["foff"]+e["size"]
    if i != len(actual) or j != len(expected):
        raise ValueError("map/census extent differs: " + image)


def coverage_summary(path, headers):
    """Coverage categories overlap and are witnesses, never an alternative census denominator."""
    regions = list(read_jsonl(path))
    out = {}
    for key, h in headers.items():
        cats = defaultdict(list)
        for r in regions:
            if r["container"] != h["container"]:
                continue
            a = max(h["foff"], L.num(r["foff"]))
            b = min(h["foff"]+h["size"], L.num(r["foff"])+L.num(r["size"]))
            if a < b:
                cats[r["category"]].append((a, b))
        counts = {}
        for cat, ivs in cats.items():
            n, last = 0, -1
            for a, b in sorted(ivs):
                n += max(0, b-max(a, last))
                last = max(last, b)
            counts[cat] = n
        out[key] = counts
    return out


def generate(root, labels_path, coverage_path, verify_retail=False):
    headers, spans = read_labels(labels_path)
    originals = {}
    # Read raw documents so every pre-existing code entry remains byte-for-byte equivalent as JSON.
    for image in headers:
        p = image_path(root, image)
        if p.exists():
            originals[image] = json.loads(p.read_text())
    docs = {}
    for image, h in headers.items():
        original = originals.get(image)
        doc = ({k: h[k] for k in ("image", "container", "foff", "size", "vma", "evidence")}
               if original is None else dict(original))
        vma = lambda v: None if v is None else L.num(v)
        if (doc["container"], L.num(doc["foff"]), L.num(doc["size"]), vma(doc["vma"])) != (h["container"], h["foff"], h["size"], vma(h["vma"])):
            raise ValueError("census header changes existing image geometry: " + image)
        protected = [e for e in (original or {}).get("entries", []) if L.is_code(e)]
        for child in h.get("children", []):
            ch = headers.get(child)
            if ch is None:
                raise ValueError("child needs a census header in the same export: " + child)
            protected.append({"kind": "image", "ref": child, "foff": hex(ch["foff"]), "size": ch["size"],
                              "evidence": "whole-image census export; referenced load image"})
        protected.sort(key=lambda e: L.num(e["foff"]))
        entries, last = [], h["foff"]
        f = (Path(root)/RETAIL[h["container"]]).open("rb") if verify_retail else None
        try:
            for e in protected:
                start, size = L.num(e["foff"]), L.num(e["size"])
                if start < last or start+size > h["foff"]+h["size"]:
                    raise ValueError("protected code/child extents overlap or escape image: " + image)
                entries.extend(metadata(s, f) for s in clipped(spans[image], last, start))
                own = list(clipped(spans[image], start, start+size))
                if L.is_code(e) and any(s["label"] != "proven_code" for s in own):
                    raise ValueError("census contradicts existing code TU (stale census?): " + e["row"])
                # A physical asset cannot be split: its hash covers exactly its original extent.
                for s in spans[image]:
                    if s.get("kind") == "asset" and s["foff"] < start+size and start < s["foff"]+s["size"]:
                        if L.is_code(e) or s["foff"] < start or s["foff"]+s["size"] > start+size:
                            raise ValueError("asset overlaps protected code/child boundary: " + image)
                entries.append(dict(e))
                last = start+size
            entries.extend(metadata(s, f) for s in clipped(spans[image], last, h["foff"]+h["size"]))
        finally:
            if f is not None:
                f.close()
        doc.update(schema=L.MAP_SCHEMA, entries=entries, census=h["census"],
                   provenance={"labels_sha256": sha256(labels_path), "coverage_sha256": sha256(coverage_path),
                               "source": h["evidence"]})
        docs[image] = doc
    images = {k: L.validate_image(d) for k, d in docs.items()}
    L.coverage(images)
    for image in images:
        compare_labels(flatten(images, image), spans[image], image)
    # Check home references and duplicate placements against all other lists before writing anything.
    loaded = L.load(root)[0]
    combined = dict(loaded, **images)
    seen = {}
    for img in combined.values():
        for e in img["entries"]:
            if L.is_code(e):
                if e["row"] in seen or (img["container"], e["foff"]) in seen:
                    raise ValueError("duplicate generated placement: " + e["row"])
                seen[e["row"]] = e
                seen[(img["container"], e["foff"])] = e
    for e in list(seen.values()):
        if e["home"] not in seen:
            raise ValueError("generated placement has no home: " + e["home"])
    return docs, coverage_summary(coverage_path, headers)


def describe(images, keys, physical_roots=None):
    children = {e["ref"] for k in keys for e in images[k]["entries"] if e.get("kind") == "image"}
    roots = sorted(set(keys)-children) if physical_roots is None else sorted(physical_roots)
    if not roots or len(roots) != len(set(roots)) or set(roots) - set(keys):
        raise ValueError("physical roots must be unique selected v1 images")
    by_cont = defaultdict(list)
    out = {}
    for key in sorted(keys):
        img = images[key]
        out[key] = {"bytes": img["size"], "entries": len(img["entries"]), "census": img["census"]}
        if key in roots:
            by_cont[img["container"]].append((img["foff"], img["foff"]+img["size"]))
    for cont, ivs in by_cont.items():
        last = -1
        for a, b in sorted(ivs):
            if a < last:
                raise ValueError("selected root images overlap in " + cont)
            last = b
    if physical_roots is not None:
        # Historical placement views overlap. An explicit physical partition is the
        # denominator; every selected view must reproduce its labels at every boundary.
        physical = defaultdict(list)
        for k in roots:
            physical[images[k]["container"]].extend(flatten(images, k))
        for cont in physical:
            physical[cont].sort(key=lambda s: s["foff"])
        for k in keys:
            h = images[k]
            expected = list(clipped(physical[h["container"]], h["foff"], h["foff"]+h["size"]))
            if not expected or expected[0]["foff"] != h["foff"] or sum(s["size"] for s in expected) != h["size"]:
                raise ValueError("image outside physical roots: " + k)
            compare_labels(flatten(images, k), expected, k)
    return {"images": out, "roots": roots, "root_bytes": sum(images[k]["size"] for k in roots)}


def check(root, labels_path=None, keys=None, complete=False, catalogue=None, physical_roots=None):
    images = load_maps(root, catalogue)[0]  # Production validation for both catalogues.
    keys = keys or [k for k, v in images.items() if v["schema"] == L.MAP_SCHEMA]
    if not keys:
        raise ValueError("no whole-image maps selected")
    if any(k not in images or images[k]["schema"] != L.MAP_SCHEMA for k in keys):
        raise ValueError("selected image is missing or is still v0")
    if labels_path:
        headers, spans = read_labels(labels_path)
        for k in keys:
            if k not in headers or images[k].get("provenance", {}).get("labels_sha256") != sha256(labels_path):
                raise ValueError("census export provenance differs: " + k)
            compare_labels(flatten(images, k), spans[k], k)
    result = describe(images, keys, physical_roots)
    if complete:
        expected = {r["container"]: r["bytes"] for r in read_jsonl(Path(root)/"ledger/containers.jsonl")}
        expected["slus"] = 524288
        for cont in RETAIL:
            ivs = sorted((images[k]["foff"], images[k]["size"]) for k in result["roots"] if images[k]["container"] == cont)
            last = 0
            for start, size in ivs:
                if start != last:
                    raise ValueError("container map gap: " + cont)
                last += size
            if last != expected[cont]:
                raise ValueError("container map incomplete: " + cont)
    return result


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    sub = ap.add_subparsers(dest="command", required=True)
    p = sub.add_parser("generate")
    p.add_argument("--labels", type=Path, required=True)
    p.add_argument("--coverage-regions", type=Path)
    p.add_argument("--write", action="store_true", help="write the compact catalogue after all validation passes")
    p.add_argument("--verify-retail", action="store_true")
    p.add_argument("--catalogue", type=Path, default=Path("link"))
    p = sub.add_parser("check")
    p.add_argument("--labels", type=Path)
    p.add_argument("--image", action="append")
    p.add_argument("--complete-containers", action="store_true")
    p.add_argument("--catalogue", type=Path, help="explicit byte-map directory; default config/link")
    p.add_argument("--physical-roots", type=Path, help="JSON array of nonoverlapping physical root image IDs; all selected views must agree")
    a = ap.parse_args()
    try:
        if a.command == "generate":
            cp = a.coverage_regions or a.root/"ledger/coverage_regions.jsonl"
            docs, regions = generate(a.root, a.labels, cp, a.verify_retail)
            images = {k: L.validate_image(d) for k, d in docs.items()}
            result = describe(images, list(images))
            result["coverage_region_bytes_by_category"] = regions
            result["link_file_bytes"] = {k: sum(len(blob) for blob in F.encode(d)) for k, d in docs.items()}
            if a.write:
                for k, d in docs.items():
                    F.write(a.root/a.catalogue/k.split('/')[0], d)
                load_maps(a.root, a.catalogue)
        else:
            roots = json.loads(a.physical_roots.read_text()) if a.physical_roots else None
            if roots is not None and not isinstance(roots, list):
                raise ValueError("physical roots must be a JSON array")
            result = check(a.root, a.labels, a.image, a.complete_containers, a.catalogue, roots)
        print(json.dumps(result, sort_keys=True, indent=2))
    except (OSError, ValueError, KeyError, TypeError) as exc:
        ap.exit(1, "byte map: " + str(exc) + "\n")


if __name__ == "__main__":
    main()
