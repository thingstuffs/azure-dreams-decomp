# Complete overlay module placements

This is a maintainer reference for complete translation-unit (TU) placement
proofs. See [link lists](LINK_LISTS.md) for the basic model and
[source locations](SOURCE_LAYOUT.md) for editable paths.

`config/overlays/module_placements.json` is an intended placement index. Its
schema is `azure-clean.module-placements.v1`; every descriptor has exactly:

- `key`: unique snake_case placement key, distinct from every physical module key.
- `module`: a physical module key in `config/overlays/modules.json`.
- `image`, `home_image`: explicit destination image and whole-TU home namespace
  from `config/link/<container>/*.json`. A heuristic single-row home record does
  not silently choose a namespace for a multi-function module.
- `recipe`: the module's exact uniform `cfg` and `row_asflags`.
- `members`: every home member, in natural order, as `{home, row}`. Destination
  rows retain their identities and their registry `source_row`.
- `imports`: the complete home-symbol inventory with destination values. Every
  projected member's address resolution must agree in the explicit home image.
  Keep ELF symbol names; two imports may alias one destination address.
- `review`, `review_inputs`: membership/types/ownership review and its inputs.
  `pending` allows computational rehearsal; it never allows production issuance.

The placement backend accepts complete contiguous native TUs in one container
and one recipe, including typed pointer/switch rodata heads, composite body offsets
and separately registered prefix rows. It also accepts the existing
`separated-literal-allocations-v1` home model when an explicit `allocations` field
projects EVERY home allocation by the same file/VMA displacement. Allocation
section/slot/type/extent/order must remain exact; every destination allocation
needs complete proven load coverage. It rejects BSS, switch-allocation models
and cross-container copies. It also rejects incomplete,
reordered or duplicate projections, changed recipes, partial/raw window rows,
ambiguous bindings, unproven load-map bytes and stale generated split exports.
Home module support for native data/allocation models is unchanged.

Every imported data view needs an explicit extent and evidenced mapping. In
addition to existing asset proofs, placement evidence can define a `link_image`
map: `image`, `link_list`, `asset`, `file_start`, `file_end`, `delta`, and `basis`.
The evidence `views[symbol]` must equal the import declaration, and the map must
match a current image exactly. That map must contain the complete code image,
share its container and load delta, and contain the whole imported storage view.
A tiny heuristic code image does not establish a surrounding storage map.
These checks prove the declared mapping and its extent bounds. Membership,
types and storage ownership still require a completed destination review; a
shifted address or a passing code comparison supplies no such review.

## Proof boundaries

`tools/gate/overlay_module_placements.py` validates descriptors, builds and reads
shards. `source_layout.physical_owner` exposes TU ownership separately from the
logical member's source path.

One home source/recipe/census artifact is built under a per-content lock in
`work/module_artifacts/`. Every reuse verifies its exact current fingerprint,
whole-object inventory, native trim proof, genuine object and home retail bytes.
Home and destination window projections share that artifact. Candidates remain
on the existing full-TU substitution path; fileless placements cannot stage edits.

A destination link uses the entire object in natural section order. The genuine
comparison preserves original external relocation symbols and paired full
HI16/LO16 addends until destination resolution. Both real object streams must
resolve to the complete destination retail footprint with zero unresolved words,
masks or raw substitutions. The reader independently replays both object legs.
Separated literals retain natural native sections, slot identities and only the
home backend's existing checked GNU end-padding trim. Window projections retain
all owned allocations while leaving unowned gaps outside their ownership claim.

Before ordinary row compilation, member slices enter all intersecting windows.
`modules.json` records module, placement, image, artifact, fingerprint and row
projection. The window manifest records module, placement and artifact per
projected segment. The complete normal window linker/retail check still runs;
module and placement inputs are rechecked afterwards.

Production review additionally needs exactly one bound
`azure-clean.module-placement-review.v2` record whose `placement_descriptor`
equals the entire current descriptor and whose `review` equals its named review.
Changing a descriptor alone or reusing a review for another tuple cannot authorize
issuance. Scratch proof production still performs all computational checks.

A production shard is `ledger/modules/placement_<key>.json`, with schema
`azure-clean.module-placement-proof.v1` and kind `overlay_module_link_placement`.
It binds its whole home artifact, exact member/image tuple, import/storage/map
inputs and every active affected destination window. Its proof directory is
unique per issuance so failed renewals cannot replace an earlier shard's files.
A missing, stale, reordered or failed shard grants no rows. Adding a valid pending
descriptor does not itself invalidate an unchanged home's independent proof.

`overlay_module_evidence` and `accounting_modules` supply only current shard
rows to the existing level ladder. All shared TU bodies/headers/glue enter each
projected row's source context. Each copy retains its own gate/base/split-audit
requirements and all existing L3/pins/tail/residue and L5 fidelity requirements.
A placement proof alone grants neither L4 eligibility nor L5.

Native packages resolve physical ownership, reject edits staged under a fileless
row, bind placement maps/evidence/readers, and fan out to home and destination
windows. Recorded production shards are renewal obligations in `certify_batch`.
An invalid recorded shard selects its owner for renewal, and the home producer
renews its invalid issued shards from fresh canonical destination receipts.
Unissued pending descriptors are not automatic issuance obligations. A removed
issued descriptor requires explicit retirement of its certificate.

Portable kind `overlay-module-placement` carries the original canonical shard,
complete artifact and every window. Its producer/reader rediscover all inputs.
The lander inventories/preserves placement proofs and can adopt their exact
windows. Scratch certificates cannot be exported as production shard authority.

## Producing or renewing a proof

**Requires the user-owned disc, provisioned toolchain and pinned genuine Psy-Q
assembler** described in [TOOLCHAIN_PSYQ.md](TOOLCHAIN_PSYQ.md). This is a
reviewed maintainer operation: a descriptor, completed destination review and
fresh canonical gate receipts must exist before production issuance.

Regenerate the physical graph/build view after descriptor edits. Gate the union
of home and destination windows, retain the fresh immutable receipts and their
transaction identity, then certify the selected complete module placement.
The public producers document their accepted arguments:

```sh
python3 tools/gate/overlay_module_gate.py --help
python3 tools/fidelity/certify_overlay_module.py --help
```

Those help commands need no disc. A pending review may be measured with the
certificate producer's `--scratch-output`; its scratch kind grants no production
authority. Exporting a receipt never replaces review, input freshness or the
complete affected window checks. Refresh the generated level/status views only
after the proof is current. Module placement alone grants neither L4 nor L5;
see [the level definitions](PLAN.md).
