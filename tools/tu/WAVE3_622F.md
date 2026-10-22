# Recreating the wave-3 merges on 622ffe756

The two groups retain their ordered registered home rows and inferred-weak
grouping labels. A prior patch application reported a duplicate physical source
path for G01118. Recreate the groups with `tu_merge.py`, rather than copying a
layout mapping independently of its inline provenance.

G01118 contains `town/func_80091840`, `town/func_80091880` and
`town/func_800918BC`, in that order. Its recipe is `2.7.2-cdk-G0`. Draft from
the current sources, prove against all three frozen original objects with
their registered assembler treatments, and install the source, header,
`ledger/layout.jsonl` and `ledger/layout_inline.jsonl` together. Preserve the
current function comments and declarations. Every member must have its own
byte-bound inline record; sharing a path without that record remains an error.

G01209 contains `town/func_8046C188` and `town/func_8046C280`. Its uniform
recipe is `2.7.2-cdk-G0 -O1`. The explicit integer `history_base` local and
recorded operand order remain necessary for whole-object identity. Gather the
five existing entries into the evidenced enclosing views only after a fresh
global binding-preservation plan. Then re-prove all six complete cohorts,
including the five native destinations. Pending computational placement
descriptors keep their existing review policy.

The portable delivery provides `reapply_622f.py`, `merge_map_622f.tsv` and
`tool_map_622f.tsv`. Run the replay's `--check` preflight before writing.
Edited tool symbols refuse for reviewed integration. Source compatibility
still requires fresh complete-object, retail and genuine ASPSX proofs.

Run `tools/source_layout.py --root . check` and `tools/row_db.py check` in
the recreated tree, then the configured build, one final `make check`, and
the TU unit suite. `test_tu_layout.py` covers valid merged provenance, the
reported missing-provenance collision, and refusal of changed source bytes.
