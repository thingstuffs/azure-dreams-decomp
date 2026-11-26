#!/usr/bin/env python3
"""Audit and repair the eight scheduled-prologue assertion boundaries.

This is an explicit retail-backed correction, not a containment fallback. The
original one-off assertion scanner is not present in tools/. Its documented
stack-allocation refinement skipped a flag load scheduled before the prologue.
Every repair must pass the instruction, string, extent and direct-call checks.
Run without --apply to audit; --check additionally requires corrected CSV data.
"""
import argparse
import csv
import hashlib
import io
import json
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "docs/evidence/tobjs_assertion_boundaries.json"
CSV = ROOT / "docs/evidence/konami_assertion_sites.csv"


def word(data, offset):
    return struct.unpack_from("<I", data, offset)[0]


def returns(word):
    return word >> 26 == 0 and (word >> 21) & 31 == 31 and word & 0x1fffff == 8


def scheduled_flag_prefix(data, entry):
    """Require a live flag definition and the branch that controls the assertion.

    Only stack stores and argument copies may intervene.
    """
    hi, load, stack = (word(data, entry + i * 4) for i in range(3))
    if hi >> 16 != 0x3C02 or load >> 16 != 0x8C42:
        raise ValueError("entry lacks the expected flag address and load")
    if stack >> 16 != 0x27BD or not (stack & 0x8000):
        raise ValueError("stack allocation is not at entry+8")
    for i in range(3, 12):
        w = word(data, entry + i * 4)
        if w >> 16 == 0x1040:
            flag = ((hi & 0xFFFF) << 16) + struct.unpack("<h", struct.pack("<H", load & 0xFFFF))[0]
            return {"flag_object_address": f"0x{flag & 0xFFFFFFFF:08X}",
                    "branch_offset": i * 4, "stack_bytes": 0x10000 - (stack & 0xFFFF)}
        stack_store = w >> 26 == 43 and (w >> 21) & 31 == 29
        arg_copy = (w & 0xFC00003F) == 0x21 and (w >> 16) & 31 == 0 and (w >> 11) & 31 in (16, 17)
        if not (stack_store or arg_copy):
            raise ValueError(f"flag value not proven live through instruction +0x{i * 4:X}")
    raise ValueError("no assertion-controlling branch found")


def direct_xrefs(data, first, delta, entry, stack):
    targets = {((entry + delta) & 0x0FFFFFFF): "entry",
               ((stack + delta) & 0x0FFFFFFF): "stack"}
    result = []
    for i, (w,) in enumerate(struct.iter_unpack("<I", data)):
        target = (w & 0x03FFFFFF) << 2
        if w >> 26 in (2, 3) and target in targets:
            result.append({"foff": f"0x{first + i * 4:X}",
                           "transfer": "jump" if w >> 26 == 2 else "call",
                           "target": targets[target]})
    return result


def audit(site, spec, stream, registered):
    entry = int(spec["entry_foff"], 0); old = entry + 8
    size = spec["size"]; end = entry + size
    delta = int(site["derived_base"], 0)
    at = int(site["containing_func_foff"], 0)
    if at not in (entry, old) or at + int(site["containing_func_size"]) != end:
        raise ValueError("catalogue extent is neither the historical nor corrected extent")
    if (site["container"] != "TOWN.BIN" or site["source_file"] != spec["source_name_ref"]
            or site["kind"] != "assert" or int(site["line"]) != spec["line"]):
        raise ValueError("assertion identity differs from the audited manifest")
    stream.seek(entry - 8); data = stream.read(size + 8)
    if len(data) != size + 8 or not returns(word(data, 0)) or word(data, 4) >> 26 != 43:
        raise ValueError("preceding helper does not end at the corrected entry")
    flag = scheduled_flag_prefix(data, 8)
    if not returns(word(data, len(data) - 8)):
        raise ValueError("function lacks its terminal return")
    call = int(site["site_foff"], 0)
    if not entry < call < end - 4:
        raise ValueError("assertion call lies outside its routine")
    transfer = word(data, call - entry + 8)
    line_setup = word(data, call - entry + 12)
    if (transfer >> 26 != 0 or transfer & 63 != 9 or (transfer >> 11) & 31 != 31
            or line_setup >> 26 not in (9, 13) or (line_setup >> 21) & 31 != 0
            or (line_setup >> 16) & 31 != 6 or line_setup & 0xffff != spec["line"]):
        raise ValueError("assertion call / line constant differs")
    pool = int(site["chunk_pool_foff"], 0)
    stream.seek(pool); strings = stream.read(64)
    if len(strings) != 64 or hashlib.sha256(strings).hexdigest() != spec["pool_sha256"]:
        raise ValueError("assertion format and source-name pool differ from the disc witness")
    first, last = (int(spec[k], 0) for k in ("scan_start", "scan_end"))
    stream.seek(first); scan = stream.read(last - first)
    if len(scan) != last - first:
        raise ValueError("direct-reference scan is truncated")
    refs = direct_xrefs(scan, first, delta, entry, old)
    if not any(r["target"] == "entry" for r in refs) or any(r["target"] == "stack" for r in refs):
        raise ValueError("direct calls do not corroborate the corrected entry exclusively")
    row = registered.get(entry)
    if row and row["size"] != size:
        raise ValueError("registered row has a different extent")
    if hashlib.sha256(data).hexdigest() != spec["range_sha256"]:
        raise ValueError("assertion routine differs from the disc witness")
    nominal = f"func_{entry + 0x80080000:08X}"
    corrected = dict(site, containing_function=nominal, containing_func_foff=f"0x{entry:X}",
                     containing_func_vram=f"0x{(entry + delta) & 0xFFFFFFFF:08X}",
                     containing_func_size=str(size), func_status="MATCH" if row else "not-in-sweep")
    note = "The entry includes the flag read before frame setup. The return boundary and incoming calls corroborate it."
    if note not in corrected["notes"]:
        corrected["notes"] = (corrected["notes"] + "; " if corrected["notes"] else "") + note
    receipt = {**spec, **flag, "old_entry_foff": f"0x{old:X}", "row": row["id"] if row else None,
               "object_vram": corrected["containing_func_vram"],
               "registered_true_name": row.get("true_name") if row else None,
               "direct_xrefs": refs, "already_corrected": corrected == site}
    return corrected, receipt


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--report", type=Path)
    args = ap.parse_args()
    manifest = json.loads(MANIFEST.read_text())
    with CSV.open(newline="") as f:
        reader = csv.DictReader(f); fields = reader.fieldnames; sites = list(reader)
    registered = {r["foff"]: r for r in map(json.loads, (ROOT / "ledger/rows.jsonl").read_text().splitlines())
                  if r["container"] == "town" and r.get("foff") is not None}
    by_site = {s["site_foff"]: s for s in sites if s["container"] == "TOWN.BIN"}
    receipts = []; replacements = {}
    with (ROOT / "work/disc/containers/TOWN_TOWN.BIN").open("rb") as stream:
        for spec in manifest["sites"]:
            site = by_site[spec["site_foff"]]
            corrected, receipt = audit(site, spec, stream, registered)
            replacements[spec["site_foff"]] = corrected; receipts.append(receipt)
    changes = sum(not r["already_corrected"] for r in receipts)
    if args.apply and changes:
        output = io.StringIO(newline="")
        writer = csv.DictWriter(output, fields, lineterminator="\n"); writer.writeheader()
        writer.writerows(replacements.get(s["site_foff"], s) if s["container"] == "TOWN.BIN" else s for s in sites)
        CSV.write_bytes(output.getvalue().encode())
    report = {"schema": "azure-clean.assertion-boundary-audit.v1", "sites": receipts,
              "corrections_needed": changes, "applied": bool(args.apply and changes)}
    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(json.dumps(report, indent=2) + "\n")
    print(f"{len(receipts)} retail-backed boundaries; {changes} corrections {'applied' if args.apply else 'needed'}")
    if args.check and changes and not args.apply:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
