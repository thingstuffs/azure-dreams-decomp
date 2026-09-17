Working paths in this snapshot refer to `work/native_lane/r41_copy88/`.

# Recipe acceptance review: `town/func_8080E838`

## Decision

Do not weaken `tools/pin_cells_land.py` or the existing
`apply_candidates.py --cells` rule. That rule is for a simple cell correction
of substantially the same pinned source: it requires both the pin-free candidate and the current
pinned text to be exact at the destination cell. Here the source has been
reconstructed as ordinary C at the same time as the build recipe changes. The
old pinned source failing at 2.7.2 is therefore expected evidence of a
source/recipe interaction, not a reason to reject an otherwise reviewed whole-C
reconstruction.

For this one row, use an explicit audited endpoint transition through
`common.set_row_cfgs`: exact current source at the recorded recipe to exact
zero-pin source at the proposed stock recipe. This keeps the narrower cell-fix
rule intact. A new generic tool option is justified only if this pattern recurs;
it must be a separately named reconstruction mode, never a `--force` bypass.

## Evidence in hand

- Current source SHA-256 is
  `a261d783e75d340a921329340d331c02fdf1f8a05f8556bad649a1a48eba3eb5`,
  with 19 live pins. `base_2.95.2-G0_-mno-split-addresses_verify.json`
  records it exact at the existing stock recipe.
- `natural_v2.c` SHA-256 is
  `4e9dfcd15b22ed8f48d574865c7bd5ca6b20e85fa36fd28c1bf646a4fce542dd`.
  It has zero pin sites and is independently exact, 87/87 words, at stock
  `2.7.2-G0`; both the normal verifier receipt and
  `independent_verify.json` record zero substitutions and zero indels.
- `pin_census.landing_refusal` returns `None` for the candidate against the
  current source. This proves the existing unscored-arm and portability-lint
  checks pass; it is not a semantic proof.
- The 88-byte aggregate expansion, retail register partition, and indexed
  global-load macro support the 2.7-era compiler family. They do not identify a
  historical release. The row recipe may be changed to the reproducible stock
  recipe while the historical lineage remains explicitly qualified.

The exact bytes do not by themselves prove the recovered object types, the
88-byte and 24-byte copy extents, non-overlap, callback/data declarations,
callee prototypes, or caller-visible behavior. They also do not turn the 2.7
family fingerprint into release provenance.

## Required landing record and gates

1. Bind the transition to the two hashes above. Retain the old-source/old-recipe
   exact receipt and the new-source/new-recipe exact receipts. Record the two
   cross-combinations as controls when available, but do not require either to
   be exact; they diagnose why this is not a simple cell correction.
2. Complete an independent semantic and caller review covering the aggregate
   layouts and extents, source/destination non-overlap, all external object and
   function declarations, the null path, and the unchanged ABI. Record any port
   debt separately. Require zero pins and a fresh `landing_refusal == None` on
   the hash-bound candidate.
3. Apply the source and recipe as one reviewed transition. Use
   `common.set_row_cfgs([("town/func_8080E838", "2.7.2-G0", note)])`, with a
   note such as: `whole-C reconstruction: old source exact at recorded recipe;
   zero-pin candidate exact at 2.7.2-G0; 2.7-family compatible, historical
   release unresolved`. Then write the hash-bound candidate and immediately
   reverify the live row at its exported recipe.
4. Journal `in_sha`, `out_sha`, `cfg_from`, `cfg_to`, both endpoint receipts,
   the semantic/caller review artifact, and the qualified lineage statement.
   Run `tools/row_db.py check` and the complete affected
   `town_deep_t8b_78e59c` window gate. The transition is resolved only after
   both pass. If the live-row verify or gate fails, restore both the old source
   and old recipe and verify that restored endpoint.

This is a narrow whole-C reconstruction policy: byte identity at both valid
endpoints, ordinary-source review, stock-recipe qualification, and full
publication closure. It does not authorize arbitrary recipe search or weaken
the existing cell-switch rule.

## Final source identity

Independent semantic review corrected the resource table/image to s32 and the
handler to a typed function pointer. The landing source additionally uses the
canonical `func_80529594` name and retains the existing allocator void-pointer
return declaration. `final.c` SHA-256: `b43f43d88ed13ca9df37ba3714c7a4673254bff1ab803504ce18b92361bdb6be`. It independently verifies 87/87 exact; the endpoint rule above applies to this reviewed final hash.


## Second reviewed endpoint and publication

The same explicit endpoint method was independently applied to
`town/func_8081DD70`, after its own semantic/caller review. Baseline SHA-256
`9c369347519663478a166ae5b520c615934ead681ddc8f1beff0dd8c88a25e21`
is exact at `2.95.2-G0 -fno-expensive-optimizations`; selected source SHA-256
`00e5f850c3d20827125c648ccaf1ddf225c7e5a990f668701235fdf927dea3b3`
is exact at stock `2.7.2-cdk-G0`, with zero pins. Its actual callback takes three
void pointers. The reviewed candidate retains pointer helper contracts and
rejects an alternative adding pointer-to-s32 casts. This is a second reviewed
whole reconstruction; no generic bypass option was added.

Both final sources passed independent and live-row verification, their complete
affected windows, SLUS and the row database check. The final applied hashes,
recipes and gate receipts are in
[pin_research_round41_20260917.json](pin_research_round41_20260917.json).
The original pending journal events are followed by publication-gated events.
