# B17 assembly notes

Baseline: B16 `c52cce14159949aea623240931a54b25efd8cdb1`.
The supplied scratch tree omitted Git metadata and `link/`. A private synthetic
Git baseline records its supplied source files. The exact B16 link tree was
restored with a read-only Git archive: all 1,332 files / 7,877,303 bytes were
verified against their Git blob IDs. All writes and ref changes stay private.
`b16_map_baseline.json` records every original file identity.

## Ordered patches

1. `0001-gate-release.patch`: reviewed release, including LL34 tools and all
   Opus fixes. Applies cleanly on the supplied B16 source files.
2. `0002-ll34-content.patch`: LL3c/LL4 content; tools excluded because patch 1
   already contains them. Shared link lists union by row and retain both sets of
   fields; no home or split-field disagreements. Append-only baseline, instance
   and raw-retirement ledgers union their lines. Split/layout records merge by
   immutable row identity. The LL3c documentation section follows B16's newer
   census sections. Four B16-edited town copies are deleted as requested and
   verified to resolve to present home sources. Registry, levels, indices and
   module graph regenerate; relocation-text allowlist only shrinks.
3. `0003-tu1.patch`: eleven proven TUs; manifest entries and membership assignments
   merge by identity, retaining B16/release entries. MAIN scoped fingerprints use
   the co-resident main/SLUS noreturn and sibcall evidence files.
4. `0004-tu4.patch`: 21 new TUs and one duplicate represented by TU1.
   `main_card_save_menu_request` has the same members/recipe as the earlier
   `main_card_save_request`; retain TU1's physical owner and omit duplicate glue
   and three alternate evidence files. The 33 input items represent 32 distinct
   new TUs. TU4 adds one previously unassigned membership row. Its alternate
   negative-record branch conflicts with Opus: preserve the release's shared
   eligibility helper and explicit false eligibility/unavailable measurements;
   adapt the incoming negative tests to those semantics. MAIN support merges once.
5. `0005-required-fixes.patch`: five p04 destination reviews become pending in
   descriptors and matching nested v2 review records. Final levels/indices/graph
   regenerate. Census snapshot anchors to B16 and binds consolidated input bytes.
   One stale SLUS bounded-read attestation is omitted, never re-signed: 68 current
   reads and all three replayed prefixes remain. The first map rollout exposed a
   missing compact-header mapping for `load_evidence`; optional key `b` now retains
   the complete object, with an end-to-end round-trip/malformed-hash regression.
6. `0006-ll6-byte-maps.patch`: exact old/new diff against the Git-verified B16 map
   tree; regenerates the whole catalogue for snapshot drift and changed link lists.
   All seven original non-generated link notes remain unchanged. The six patches
   replay successfully in a private index initialized from B16 source files plus
   its authenticated original link tree.

## Validation

Row database, source layout, frozen noreturn, relink lint, fresh census replay
with exact --check, complete physical-root byte maps, and census unit tests pass.
The initial byte-map CLI call omitted explicit physical roots; its overlap error
is superseded by the documented --physical-roots/--complete-containers check.
That complete check covers 1,635 images and all 50,952,192 physical container bytes.
The generated JSON/TSV set has 1,643 files / 8,907,316 bytes and no cached detectors.
After patch 6, all 1,211 witness hashes and all generated map bytes were revalidated
unchanged against the fresh replay; see final_receipt_revalidation.json.

The full isolated per-module suite runs 3,900 unit cases. Its 35 FAIL / 28 ERROR
parent cases match the supplied reference counts, modules and causes. Eleven
scratch temporary-directory errors/failures disappear in 61 passing rechecks
using root tmp outside native_lane. Four original historical source paths were
restored using 20 authentic Git objects, with no source refs changed; the separate
non-unit test_t10_epilogue then matches the reference empty module (0 tests, rc 5).
No failure remains outside the reference modules and causes.

All 32 new TU home fingerprints pass read-only final-metadata preflight, including
all five MAIN modules. These are diagnostic fingerprints, not byte proofs or
issued certificates. All eleven compact-map unit tests pass.

Exactly one scoped gate invocation uses six workers and a fresh private journal.
Its union contains LL34's 1,917 windows and the 24 TU windows (four additional):
1,921 of 3,197 active production windows. --all forces fresh builds inside this
explicit scope; no full gate runs. gate.log, gate_journal.jsonl and gate_summary.json
record its final result. watch_gate.py keeps REPORT.md current and finalizes all
portable deliveries once the existing invocation exits.

All five p04 destination review tuples remain valid and pending. No certificate
or L4/L5 grant is issued. LL34's research holds remain as recorded in its delivered
hold_summary.tsv; this assembly makes no new claim of resolving them.

Direct actual-B16 verification also passes: a private index reads the immutable
B16 Git object tree, applies all six patches with --cached --check, then verifies
all 3,995 touched paths equal the private assembly. The resulting full B16-plus-
patches tree is 248e7af330c7e577cbb0058e91b71a3f4c4c3ceb. No source worktree
or refs are changed. See actual_b16_patch_chain.json and its log.

## Generated paths

Regenerated tracked paths are `ledger/rows.jsonl`, `ledger/levels.jsonl`,
`ledger/splits/overlay_modules.build.json`, and the `src/<container>/INDEX.md`
files for dungeon, main, ovmovie, slus and town. The private build view exports
updated split-result JSON from the authoritative split ledgers. The relocation
allowlist `config/lint/relink_text.allow` is regenerated by shrinking only.
`config/census/snapshot.json` is refreshed; the complete generated JSON/TSV map
set under `link/` is regenerated, preserving non-generated B16 notes.
