"""Read-only planner for generic single-window twin candidates.

The family runner in :mod:`twins` obtains a donor extent from the preceding
0x6000 bank.  That is sound for the repeated monster-bank families, but it is
not a valid assumption for a generic window.  This planner uses the census's
function entry hit as the anchor, then proves the complete body, a current
proven rowbase link context, and its import contracts without changing
staging/root.

The planner deliberately emits candidates, not admissions.  Source C is kept
under evidence/single_plans/<family>/candidates and can be reviewed or fed to
an integration runner later.  ``run(f, W)`` is provided as a safe integration
hook and is equivalent to ``plan(f, W)``.
"""

import argparse
import collections
import functools
import hashlib
import json
import re
import sys
from pathlib import Path

MAIN_SCRIPTS = Path(__file__).resolve().parent
sys.path.insert(0, str(MAIN_SCRIPTS))

from twins import L as TWIN_L, R as TWIN_R, World, load_families, proof, references  # noqa: E402
from contracts import bind  # noqa: E402

# Match twins.py's worker-lane routing. A parallel worker can set TWINS_LANE
# to its private lane; twins.L already resolves that lane for evidence output,
# while implementation imports remain anchored to this main scripts directory.
HERE = TWIN_L


TARGET_FAMILIES = (
    "dungeon_1830080",
    "town_52000",
    "town_5dc000",
    "dungeon_197ad48",
    "dungeon_18d08ec",
    "dungeon_d07540",
    "ovmovie_0",
    "dungeon_187c98c",
)


def sha256(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def as_int(value):
    if isinstance(value, int):
        return value
    return int(str(value), 0)


def row_true_start(row):
    name = row.get("true_name")
    if isinstance(name, str) and name.startswith("func_"):
        return int(name[5:], 16)
    return None


def row_definitions(world, row):
    return world.byrow.get(row["id"], [])


def source_contract(world, donor_container, address, donor):
    """Return a body-backed source contract, or None.

    Existing matched definitions are preferred.  A target inside the donor
    body is allowed only when that donor row has one complete definition.  No
    guessed prototype or dynamic/runtime contract is created here.
    """

    if address in world.sdk.symbols:return world.sdk.get(address)
    definitions = world.defs.get(address)
    if definitions:
        preferred = sorted(
            definitions,
            key=lambda definition: (
                not definition["row"].startswith(donor_container + "/"),
                definition["row"],
            ),
        )[0]
        return dict(
            preferred,
            binding="matched-definition-at-encoded-source-target",
        )

    base = row_true_start(donor)
    if base is None or not base <= address < base + donor["size"]:
        return None
    definitions = row_definitions(world, donor)
    if len(definitions) != 1:
        return None
    return dict(definitions[0], binding="local-complete-retail-twin")


def overlap(a_start, a_size, b_start, b_size):
    return a_start < b_start + b_size and b_start < a_start + a_size


def existing_extents(world, container):
    """Yield registered complete extents used to reject placement collisions."""

    for row in world.rows:
        if row.get("container") != container:
            continue
        if row.get("foff") is None or not row.get("size"):
            continue
        yield int(row["foff"]), int(row["size"]), row["id"]

    for split in world.splits.get(container, []):
        if split.get("foff") is None or not split.get("size"):
            continue
        yield int(split["foff"]), int(split["size"]), split.get("id", "split")


@functools.lru_cache(maxsize=None)
def rowbase_regions(container):
    """Read established rowbase regions for one binary container.

    The worker's current ``twins.R`` configuration is the source of truth for
    extents and deltas. Solved regions remain candidates until the normal
    rowbase promotion hook proves their compile placement; synthetic-only or
    missing bases cannot provide a link context.
    """

    path = TWIN_R / "config" / "overlays" / (container + ".rowbase.jsonl")
    regions = []
    if not path.is_file():
        return tuple()
    for line in path.read_text().splitlines():
        if not line or line.startswith("#"):
            continue
        try:
            record = json.loads(line)
            start = as_int(record["foff_start"])
            end = as_int(record["foff_end"])
            delta = as_int(record["delta"])
        except (KeyError, TypeError, ValueError, json.JSONDecodeError):
            continue
        if end <= start or record.get("base_confidence") not in ("solved", "proven"):
            continue
        region = record.get("region")
        if not region:
            continue
        regions.append(
            {
                "region": str(region),
                "foff_start": start,
                "foff_end": end,
                "delta": delta,
                "base_confidence": record["base_confidence"],
            }
        )
    return tuple(regions)


def covering_rowbase(container, target, size, window_start, window_end, window_vram):
    """Resolve exactly one established rowbase context for a complete candidate."""

    hits = [
        region
        for region in rowbase_regions(container)
        if region["foff_start"] <= target
        and target + size <= region["foff_end"]
    ]
    if not hits:
        return None, "entry_no_covering_rowbase_region", []
    if len(hits) > 1:
        deltas = {region["delta"] for region in hits}
        reason = (
            "entry_conflicting_rowbase_regions"
            if len(deltas) > 1
            else "entry_ambiguous_rowbase_regions"
        )
        return None, reason, hits
    region = hits[0]
    if region["delta"] == window_vram - window_start:
        context = {
            "start": window_start,
            "end": window_end,
            "vram": window_vram,
            "basis": "window-correlated-rowbase",
            "region": region["region"],
            "delta": region["delta"],
        }
    else:
        context = {
            "start": region["foff_start"],
            "end": region["foff_end"],
            "vram": region["foff_start"] + region["delta"],
            "basis": "existing-rowbase-region",
            "region": region["region"],
            "delta": region["delta"],
        }
    return context, None, hits


def census_spans(family):
    return family["banks"][0]["spans"]


def hold(span, reason, **details):
    out = {
        "foff": hex(as_int(span["foff"])),
        "size": int(span["bytes"]),
        "reason": reason,
    }
    out.update(details)
    return out


def plan(family, world, evidence_dir="single_plans", occupied=None):
    """Produce one read-only generic-window plan and evidence directory."""

    if len(family.get("banks", [])) != 1:
        raise ValueError("single_plan accepts one bank only")
    bank = family["banks"][0]
    container = bank["container"]
    start = int(bank["start"])
    end = int(bank["end"])
    vram = int(bank["vram"])
    out_dir = HERE / "evidence" / evidence_dir / family["id"]
    source_dir = out_dir / "candidates"
    source_dir.mkdir(parents=True, exist_ok=True)
    # A later live-ledger pass can turn an earlier candidate into an overlap
    # hold.  Remove only this planner's generated C files so stale evidence
    # cannot be mistaken for a current row.
    for old_source in source_dir.glob("func_*.c"):
        old_source.unlink()

    holds = []
    candidates = []
    placed = []
    if occupied is None:
        occupied = list(existing_extents(world, container))
    else:
        occupied = list(occupied)

    for span in census_spans(family):
        span_start = as_int(span["foff"])
        span_size = int(span["bytes"])
        span_end = span_start + span_size
        if int(span.get("hit_count", 0)) <= 0:
            holds.append(hold(span, "census_no_whole_body_twin"))
            continue

        if not span.get("best_hit_foff") or not span.get("best_matched_row"):
            holds.append(hold(span, "census_hit_has_no_entry_anchor"))
            continue
        target = as_int(span["best_hit_foff"])
        if target % 4:
            holds.append(hold(span, "entry_not_word_aligned", target=hex(target)))
            continue
        if target < start or target >= end:
            holds.append(hold(span, "entry_outside_window", target=hex(target)))
            continue

        anchored = [
            (donor, proof)
            for donor, proof in world.twins_at(container, target)
            if donor["id"] == span["best_matched_row"]
        ]
        if not anchored:
            holds.append(
                hold(
                    span,
                    "census_anchor_not_complete_twin",
                    target=hex(target),
                    census_template=span["best_matched_row"],
                )
            )
            continue

        donor, masked_discovery_proof = anchored[0]
        size = int(donor["size"])
        if size % 4 or size <= 0:
            holds.append(hold(span, "donor_extent_not_complete_words", template=donor["id"]))
            continue
        if target + size > span_end:
            holds.append(
                hold(
                    span,
                    "entry_extent_exceeds_census_span",
                    target=hex(target),
                    template=donor["id"],
                    template_size=size,
                )
            )
            continue
        if target + size > end:
            holds.append(
                hold(
                    span,
                    "entry_extent_exceeds_window",
                    target=hex(target),
                    template=donor["id"],
                    template_size=size,
                )
            )
            continue

        link_context, rowbase_reason, rowbase_hits = covering_rowbase(
            container,
            target,
            size,
            start,
            end,
            vram,
        )
        if link_context is None:
            details = {
                "target": hex(target),
                "template": donor["id"],
                "template_size": size,
                "rowbase_candidates": [
                    {
                        "region": item["region"],
                        "foff_start": hex(item["foff_start"]),
                        "foff_end": hex(item["foff_end"]),
                        "delta": hex(item["delta"]),
                    }
                    for item in rowbase_hits
                ],
            }
            holds.append(hold(span, rowbase_reason, **details))
            continue

        collision = next(
            (
                item
                for item in occupied
                if overlap(target, size, item[0], item[1])
            ),
            None,
        )
        if collision is not None:
            holds.append(
                hold(
                    span,
                    "entry_extent_overlaps_registered_body",
                    target=hex(target),
                    template=donor["id"],
                    registered_extent={
                        "foff": hex(collision[0]),
                        "size": collision[1],
                        "id": collision[2],
                    },
                )
            )
            continue

        prior = next(
            (item for item in placed if overlap(target, size, item["foff"], item["size"])),
            None,
        )
        if prior is not None:
            holds.append(
                hold(
                    span,
                    "entry_extent_overlaps_another_candidate",
                    target=hex(target),
                    prior_candidate=prior["id"],
                )
            )
            continue

        target_vram = target + link_context["delta"]
        try:
            source, relocation_proof, address_map = world.generate(
                donor, container, target, size, target_vram
            )
        except ValueError as error:
            holds.append(
                hold(
                    span,
                    "source_generation_rejected",
                    target=hex(target),
                    template=donor["id"],
                    detail=str(error),
                )
            )
            continue

        # The World method already proves every body difference is a j/jal or
        # a reaching HI16/LO16 relocation.  Repeat the full unmasked proof here
        # so the evidence does not depend on census masking.
        exact_proof = proof(
            world.words(donor["container"], donor["foff"], size),
            world.words(container, target, size),
        )
        if exact_proof is None:
            holds.append(
                hold(
                    span,
                    "unmasked_relocation_proof_failed",
                    target=hex(target),
                    template=donor["id"],
                )
            )
            continue

        # target_contract_proof uses the same proven rowbase link context as
        # source generation.  A window-wide context is used only when its
        # delta agrees with the covering region; otherwise the region bounds
        # are the conservative callee address space.
        donor_container = donor["container"]
        source_words = world.words(donor_container, donor["foff"], size)
        target_words = world.words(container, target, size)
        source_refs = references(source_words)[0]
        target_refs = references(target_words)[0]
        source_vram = row_true_start(donor)
        calls = []
        unresolved = []
        for word, source_ref in sorted(source_refs.items()):
            internal_jump = (
                source_ref["kind"] == "j"
                and source_vram is not None
                and source_vram <= source_ref["address"] < source_vram + size
            )
            if source_ref["kind"] != "jal" and not (
                source_ref["kind"] == "j" and not internal_jump
            ):
                continue
            target_ref = target_refs.get(word)
            target_address = target_ref["address"] if target_ref else None
            contract = source_contract(
                world, donor_container, source_ref["address"], donor
            )
            target_proof = None
            if contract is not None and target_address is not None:
                target_proof = world.target_contract_proof(
                    container,
                    target_address,
                    link_context["start"],
                    link_context["vram"],
                    link_context["end"] - link_context["start"],
                    contract,
                    source_ref["address"],
                )
            call = {
                "word": word,
                "call_foff": hex(target + word * 4),
                "kind": source_ref["kind"],
                "source_callee": hex(source_ref["address"]),
                "encoded_callee": (
                    hex(target_address) if target_address is not None else None
                ),
                "contract": contract,
                "target_body_proof": target_proof,
            }
            calls.append(call)
            if contract is None:
                unresolved.append(
                    dict(reason="unresolved source callee contract", call=call)
                )
            elif target_address is None:
                unresolved.append(
                    dict(reason="target direct-call inventory differs", call=call)
                )
            elif target_proof is None:
                unresolved.append(
                    dict(reason="target callee body is not a complete twin", call=call)
                )
        if unresolved:
            holds.append(
                hold(
                    span,
                    "matched_callee_contracts_unresolved",
                    target=hex(target),
                    template=donor["id"],
                    unresolved=unresolved,
                    direct_call_count=len(calls),
                )
            )
            continue

        try:
            source = bind(source, calls)
        except ValueError as error:
            holds.append(
                hold(
                    span,
                    "matched_callee_contract_binding_failed",
                    target=hex(target),
                    template=donor["id"],
                    detail=str(error),
                )
            )
            continue

        func = "func_%08X" % target_vram
        source_path = source_dir / (func + ".c")
        source_path.write_text(source)
        candidate = {
            "id": container + "/" + func,
            "family": family["id"],
            "window": bank["window"],
            "container": container,
            "foff": target,
            "size": size,
            "func": func,
            "vram": target_vram,
            "template": donor["id"],
            "template_foff": donor["foff"],
            "template_true_name": donor.get("true_name"),
            "source": str(source_path.relative_to(HERE)),
            "source_sha256": sha256(source_path),
            "entry_validation": {
                "census_span": {
                    "foff": hex(span_start),
                    "size": span_size,
                },
                "anchored_best_hit": hex(target),
                "complete_extent": True,
                "inside_window": True,
                "inside_census_span": True,
                "rowbase": {
                    "region": link_context["region"],
                    "foff_start": link_context["start"]
                    if link_context["basis"] == "existing-rowbase-region"
                    else rowbase_hits[0]["foff_start"],
                    "foff_end": link_context["end"]
                    if link_context["basis"] == "existing-rowbase-region"
                    else rowbase_hits[0]["foff_end"],
                    "delta": link_context["delta"],
                },
                "placement_collision": False,
            },
            "link_context": link_context,
            "relocation_proof": exact_proof,
            "relocation_count": len(exact_proof),
            "paired_addresses": {
                hex(old): hex(new)
                for old, new in address_map.items()
                if old != new
            },
            "contracts": calls,
            "direct_call_count": len(calls),
            "discovery_proof": masked_discovery_proof,
            "admission": "CANDIDATE_REQUIRES_NORMAL_SOURCE_RAW_WINDOW_GATES",
        }
        candidates.append(candidate)
        placed.append(candidate)

    reasons = collections.Counter(item["reason"] for item in holds)
    result = {
        "schema": "azure-clean.single-window-plan.v1",
        "family": family["id"],
        "kind": family.get("kind", "single-window"),
        "window": bank["window"],
        "container": container,
        "start": start,
        "end": end,
        "vram": vram,
        "census": {
            "path": "refs/prev/twin_census.tsv",
            "span_count": len(census_spans(family)),
            "lead_bytes": int(bank["lead_bytes"]),
        },
        "candidates": candidates,
        "holds": holds,
        "summary": {
            "candidate_count": len(candidates),
            "candidate_bytes": sum(item["size"] for item in candidates),
            "hold_count": len(holds),
            "hold_reasons": dict(sorted(reasons.items())),
            "status": "CANDIDATES" if candidates else "HOLD",
        },
        "read_only": True,
        "staging_mutated": False,
    }
    (out_dir / "plan.json").write_text(json.dumps(result, indent=1) + "\n")

    with (out_dir / "recommendations.tsv").open("w") as stream:
        stream.write("status\tfoff\tsize\tid\ttemplate\treason\n")
        for item in candidates:
            stream.write(
                "CANDIDATE\t0x%X\t%d\t%s\t%s\t%s\n"
                % (item["foff"], item["size"], item["id"], item["template"], "")
            )
        for item in holds:
            stream.write(
                "HOLD\t%s\t%s\t\t%s\t%s\n"
                % (
                    item["foff"],
                    item["size"],
                    item.get("template", ""),
                    item["reason"],
                )
            )

    return result


def runner_plan(family, world, evidence_dir="single_plans", occupied=None):
    """Adapt a read-only plan to the row shape consumed by ``twins.run``.

    Generic windows have no preceding-bank donor.  Their row name stays on a
    stable synthetic sweep base (``foff + 0x7FFE0000``), while ``true_name``
    carries the proven rowbase target/link address used by the generated C.
    The source remains in this lane's evidence directory until the normal
    runner has independently scored and gated it.
    """

    result = plan(
        family,
        world,
        evidence_dir=evidence_dir,
        occupied=occupied,
    )
    rows = []
    bank = family["banks"][0]
    container = bank["container"]
    for candidate in result["candidates"]:
        template = world.byid[candidate["template"]]
        foff = int(candidate["foff"])
        size = int(candidate["size"])
        synthetic_vram = foff + 0x7FFE0000
        synthetic_func = "func_%08X" % synthetic_vram
        target_vram = int(candidate["vram"])
        template_c_path = template.get("c_path", "")
        c_path = f"overlays/{container}/first_pass_matched/{synthetic_func}.c"
        row = {
            "id": f"{container}/{synthetic_func}",
            "container": container,
            "func": synthetic_func,
            "foff": foff,
            "size": size,
            "vram": synthetic_vram,
            "true_name": "func_%08X" % target_vram,
            "true_vram": target_vram,
            "delta": target_vram - foff,
            "cfg": template.get("cfg"),
            "cell": template.get("cell"),
            "flags": template.get("flags"),
            "kind": template.get("kind", "overlay"),
            "c_path": c_path,
            "src": candidate["source"],
            "window": candidate["window"],
            "template": candidate["template"],
            "template_foff": candidate["template_foff"],
            "template_true_name": candidate.get("template_true_name"),
            "template_c_path": template_c_path,
            "candidate_func": candidate["func"],
            "candidate_id": candidate["id"],
            "source_sha256": candidate["source_sha256"],
            "target_vram": target_vram,
            "relocation_proof": candidate["relocation_proof"],
            "paired_addresses": candidate["paired_addresses"],
            "contracts": candidate["contracts"],
            "direct_call_count": candidate["direct_call_count"],
            "entry_validation": candidate["entry_validation"],
            "link_context": candidate["link_context"],
            "admission": candidate["admission"],
        }
        rows.append(row)

    holds = []
    for item in result["holds"]:
        converted = dict(item)
        converted["window"] = result["window"]
        # Keep the hex form used by twins.plan evidence while retaining an
        # integer for callers that need arithmetic or interval checks.
        converted["foff_int"] = as_int(item["foff"])
        holds.append(converted)

    runner_result = {
        "schema": "azure-clean.single-window-runner-plan.v1",
        "family": result["family"],
        "source_family": family.get("source_family", family["id"]),
        "window": result["window"],
        "start": result["start"],
        "end": result["end"],
        "vram": result["vram"],
        "rows": rows,
        "holds": holds,
        "status": "CANDIDATES" if rows else "HOLD",
        "read_only": True,
    }
    runner_path = HERE / "evidence" / evidence_dir / family["id"] / "runner_plan.json"
    runner_path.write_text(json.dumps(runner_result, indent=1) + "\n")
    return rows, holds


def run(family, world):
    """Safe integration route: plan only; never edits staging/root."""

    return plan(family, world)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("families", nargs="*", choices=TARGET_FAMILIES)
    parser.add_argument("--all", action="store_true", help="plan all eight priority families")
    args = parser.parse_args(argv)
    wanted = list(TARGET_FAMILIES if args.all or not args.families else args.families)
    families = {family["id"]: family for family in load_families()}
    world = World()
    results = [run(families[name], world) for name in wanted]
    summary = HERE / "evidence" / "single_plans" / "summary.tsv"
    with summary.open("w") as stream:
        stream.write("family\tstatus\tcandidates\tbytes\tholds\n")
        for result in results:
            info = result["summary"]
            stream.write(
                "%s\t%s\t%d\t%d\t%d\n"
                % (
                    result["family"],
                    info["status"],
                    info["candidate_count"],
                    info["candidate_bytes"],
                    info["hold_count"],
                )
            )
            print(
                "%s %s candidates=%d bytes=%d holds=%d"
                % (
                    result["family"],
                    info["status"],
                    info["candidate_count"],
                    info["candidate_bytes"],
                    info["hold_count"],
                )
            )


if __name__ == "__main__":
    main()
