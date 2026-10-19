# B17 consolidation assembly

Baseline: supplied B16 scratch files, `c52cce14159949aea623240931a54b25efd8cdb1`.
All source changes and artifacts remain in this private root. No external refs
were moved. All six patches apply to the actual B16 Git tree; all 3,995 touched
paths equal the private assembly. The resulting actual-baseline tree is
`248e7af330c7e577cbb0058e91b71a3f4c4c3ceb`.

## Per-item status

| Item | Status |
|---|---|
| 1. Reviewed gate-tool release | Complete; patch 0001 |
| 2. LL34 content | Complete; patch 0002: 1,662 LL3c placements, 523 hand-copy conversions plus 30 legacy relinks, 1,106 source/raw retirements |
| 3a. TU1 | Complete; eleven distinct proven TUs, patch 0003 |
| 3b. TU4 | Complete; 21 new TUs and one duplicate consolidated with TU1, patch 0004 |
| 4a. Five p04 destination reviews | Complete; pending in descriptors and matching v2 records, patch 0005 |
| 4b. Census snapshot and LL6 maps | Complete; exact B16 map replacement patch 0006; fresh exact regeneration passes |
| Required deterministic checks | PASS: row database, source layout, noreturn, relink lint, census regeneration, complete byte maps, census unit suite |
| Full unit suite | 3,900 unit tests; reference 35 FAIL / 28 ERROR parent cases only; no failures outside reference modules/causes |
| Single scoped gate | PASS: 1921/1,921 windows; {"MATCH": 1921}; six workers; exit 0 |

TU4's `main_card_save_menu_request` exactly duplicates TU1's
`main_card_save_request` member tuples and recipe. The earlier TU1 module remains
the sole physical owner. The 33 input TU items therefore represent 32 distinct
new TUs. The gate union is LL34's 1,917 windows plus four additional TU windows,
out of 3,197 active production windows. No full gate was run.

The four B16-edited town copies were retired and verified to resolve to existing
homes. Link lists retain both lanes' entries and fields. Append-only ledgers
retain both histories; membership assignments merge by row identity. Generated
registry, levels, source indices and module graph were regenerated.

Patch 0005 also fixes lossless compact serialization of the new `load_evidence`
image field; all eleven compact-map tests pass. The census refresh omits one
stale SLUS read attestation without re-signing it: 68 current bounded reads and
three replayed prefixes remain. The fresh replay uses no detector cache.

## Deliveries

- `patches/0001-gate-release.patch` through `0006-ll6-byte-maps.patch`, in order.
- `patch_manifest.json` and `patch_chain.log`: SHA-256 identities and successful
  isolated-index replay of all patches against the supplied baseline files.
- `actual_b16_patch_chain.json` and its log: direct verification against the
  actual B16 Git object tree, with matching final contents on all touched paths.
- `regenerated_link/`: 1,643 metadata files, 8,907,316 bytes; complete replacement
  generated map set, with per-file hashes in `regenerated_link_manifest.json`.
  `MAP_INSTALL.md` preserves the receiver's original non-generated link notes.
- `checks.log`, `check_results.json`, `suite_comparison.json`, per-module suite
  logs, `gate.log`, `gate_journal.jsonl`, `gate_summary.json`, scope and census receipts.
- `plan_notes.md`, `MAP_INSTALL.md`, `input_manifest.json`, `large_receipts.json`,
  and `delivery_files.txt`. Large raw detector spans remain ignored; only their
  sizes and SHA-256 identities are delivered.

Complete byte-map validation covers 1,635 images and all 50,952,192 container
bytes under the five explicit physical roots. Fresh `regenerate.py --check`
compares the exact generated file set and all bytes successfully. Catalogue
map-set SHA-256: `1d890faa28dd18814db4a13a9e3083d3885c812add4230a3a227a0994ec25fab`.

## Holds by reason

1. **Placement issuance:** the five p04 reviews are deliberately pending as
   requested. Independent review is still required before issuance. No placement
   certificate or L4/L5 grant was issued by this assembly.
2. **Pre-existing unit-suite debt:** the reference's 63 failing parent cases
   remain. No new failures were found outside its modules and causes. The empty
   `test_t10_epilogue` module now matches the reference exactly (0 tests, rc 5),
   after restoring its four historical source paths from authentic Git objects.

The initial missing-map packaging hold is resolved: read-only archive recovery
restored all 1,332 B16 link files, 7,877,303 bytes, and verified each against its
Git blob ID. `b16_map_baseline.json` binds that exact baseline. Patch 0006 is a
real old/new diff against those files; existing non-generated notes are retained.
Historical test recovery copied 20 authentic Git objects into the private object
database, without changing source refs. No unverified historical reconstruction
or re-signed source attestation was used.

LL34's existing research holds are preserved, without new claims of resolution,
in `docs/evidence/r121w_ll34/hold_summary.tsv`.

## HOW TO CONTINUE

Apply patches 0001–0006 in order on an exact B16 private checkout. Follow
`MAP_INSTALL.md` for the two map verification commands. Review `gate_summary.json` and its closing
audit in `gate.log`. The orchestrator performs the full consolidation gate and
landing. Complete independent p04 destination reviews before any issuance.
