# Byte-bound references and missing sibling slots

Legacy numeric group IDs are local to one inference run. `tu_reference.py`
reads only the unavailable-member clause of a hold, preserves anchor order and
multiplicity, and reports every compatible fresh tuple. Later diagnostic text
is never treated as part of a member identity. A unique fresh candidate still
does not recover the complete historical member list.

```
python3 tools/tu/tu_reference.py --references holds.tsv --groups groups.tsv \
  --out references.tsv --evidence EVIDENCE --snapshots snapshots
```

Each snapshot contains the full ordered site list, canonical homes, exact file
extents, per-site byte hashes, load delta and inference evidence. Its full
content digest excludes the numeric group ID. A separate ordered-tuple digest
identifies site membership; it does not assert byte identity. Neither digest
promotes an inferred grouping into decisive evidence.

`tu_slots.py` checks what is actually at each missing cohort slot. First compile
the necessary home member projections with their registered placement recipes
and evidence, as `copy_place.py` does. Supply a TSV with `home` and root-relative
`object` columns. The extraction requires one complete text extent and agreement
with the home's retail instructions outside the object's relocation fields.

```
python3 tools/tu/tu_slots.py extract --objects objects.tsv --out shapes.json
python3 tools/tu/tu_slots.py check --groups groups.tsv --shapes shapes.json \
  --out slots.tsv --details slot_details
```

The exported shapes contain relocation metadata and hashes, with no object or
retail payload. Checking the metadata requires the user's retail containers.
It rejects stale home bytes/geometry, malformed or unsupported masks and reads
past container bounds. Slots beyond a catalogue view remain `outside_view`,
even if the following physical bytes have the same shape; known enclosing
same-delta views are listed separately. Other registered rows at the expected
physical slot are retained even when they belong to another view.

`text_conflict` means the supplied home object's text cannot occupy that slot
by relocation alone. A destination compiled under another recipe/context needs
its own complete-object and byte proof. `masked_text_equal` only passes a
necessary instruction screen: it proves neither the destination relocation
targets nor table allocations, row ownership, admission or original membership.
The checker never changes cohort completeness, cuts groups or installs copies.
Repeated homes still need the literal evidence required by decision 72(g) before
becoming independent static definitions.

Details use the bounded, lossless page format from `tu_cohort.py`. Keep the full
manifest and every referenced page together. Run the TU tests after changing
these tools, then the configured build, row database and source-layout checks.

## Measured follow-ups

G01209's fresh inferred-weak tuple G01086 resolves to
`town/func_8046C188` and `town/func_8046C280`. Its eight missing sibling slots
are registered same-home rows split between overlapping views. Gathering those
views would still need binding preservation, including the effect of moving a
canonical home namespace on placements outside the touched views.

The unedited complete C shape fails identity at all four supported uniform
recipes. At cdk `-O1` it emits the expected 652 bytes and 31 relocations. The
first 248-byte function initially has two aligned register-field substitutions
at offsets `0xb8` and `0xbc`, with no insertions/deletions. Retail computes an
integer history base through a short-lived register, then forms the loop's
pointer. An integer local reduces the distance to one substitution; preserving
the retail operand order makes the complete 652-byte object and every relocation
exact. No cast is added overall. The lineage fingerprint remains family-neutral;
the registered original cdk `-O2` function is exact independently. No compiler or
version-wall claim is made.

`view_merge.preserve` now accounts for canonical-home moves outside the touched
views. Moving an entry changes local lookup at its home's address; moving an
own-home entry also changes the home-image rules for all of its copies. The
planner checks those critical addresses for every placement and the complete
address-symbol inventory of moved entries and changed-home copies. It records
old resolutions explicitly wherever they would change, including remote views.
Moves must fit an enclosing legacy view at the same load delta. Any unresolved
binding or compile refusal prevents application. The scoped tests include both
remote-reference effects of moving a canonical home.

G01198's fresh item-count tuple G01075 is exact at cdk `-O1`: 104 text bytes,
three relocations and no other emitted allocation. Its placement closure still
requires reconciling the independently homed 20-minus-count wrappers at
`town/func_80481244` and `town/func_80472120`, preserving their dependent
placements and every old resolution. Equal instruction shapes alone cannot
perform that transaction or complete destination review.
