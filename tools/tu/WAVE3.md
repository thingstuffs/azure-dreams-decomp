# Shared members and uniform recipes

`tu_cohort.py` reads an ordered `member_rows` list from byte inference. It resolves
shared sites to their existing definitions and inventories every registered use.
It groups uses by image **and displacement**, so two complete copies in one image
stay distinct. A partial third copy cannot borrow siblings from the first two.
The JSON details give each missing home, exact file slot and current occupant.
Large details are split into bounded pages; the manifest lists every page.

```
python3 tools/tu/tu_cohort.py --groups groups.tsv --out cohorts.tsv --details details
python3 tools/tu/tu_cohort.py --spec shared.json --spec-out home.json --out facts.json
```

Normalization succeeds only if every cohort has all siblings, every byte has a
proven rowbase and the existing canonical homes form the same ordered file. It
preserves the evidence sites in `placement_sites` and substitutes the actual home
rows in `members`. A missing sibling needs its normal binding and byte proof, or
new grouping evidence that cuts the inferred file. Scattered canonical homes
need an explicit reviewed rehome transaction. The tool creates no definitions,
rowbase, admission, storage ownership or destination review.

Pass the normalized spec through `tu_merge.py draft`, `prove`, then `install`.
Plan and review **every** destination using `tu_placements.py`; pending descriptors
do not supply reviewed production authority. Its planner can represent several
complete cohorts in one image, with distinct descriptor keys based on the first
member's file offset. An incomplete extra cohort remains an explicit refusal.

A spec can select one uniform `recipe` even when members used registered
`--preserve-return-delay` or `--expand-div` treatments. The frozen originals are
assembled with their treatments; the merged object uses the gate's ordinary
recipe. Text, relocation streams and all emitted sections must match. This does
not assume that a treatment is harmless: a division cohort still differs and
fails. Successful reattribution updates both the split/registry recipes and the
authoritative assembler-treatment table, preserving the former proof/history.

For unrelated source-private typedefs sharing a name, a reviewed spec can use:

```
"member_type_names": {
  "town/func_8032FBFC": {"TownCallback": "TownStateCallback"}
}
```

Only locally declared typedef identifiers may change. Comments, literals,
functions and globals remain intact. The reference compile still uses the
unmodified frozen original. Whole-object equality decides whether the rename
and merged declaration context preserve the code.

`load_rowbase.py` reports conflicting proven rowbase regions alongside an L3
row-attribution failure. Repairing one row name does not authorize erasing a
different proven load map; the 64d000 case retains both evidence chains.
