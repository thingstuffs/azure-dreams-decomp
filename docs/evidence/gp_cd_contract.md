# Shared CD small-global declarations

Seven whole CD rows now include `include/slus/cd_state.h` for eleven selected
small globals. The change reconciles their declaration widths and signedness;
it does not join the functions into an owner or change their compiler recipes.
The baseline is commit `193c2e1c`.

## Contract and source changes

`SlusCdResult` provides `u8 bytes[8]` and `u32 first_word` views of
`D_80081450`. The [SDK copy evidence](gp_cd_partition/buffer_extent.md) proves
that CdSync and CdControl may write eight bytes at this address. It does not
prove an original allocation boundary. E758 reads `bytes[0]`. F368 now saves,
clears and restores `first_word` explicitly: the retail code copies four bytes,
so enlarging its saved local to eight bytes would change the program. The
existing eight-byte stack result buffer remains unchanged.

The header also declares AD0/D0/D4 as unsigned bytes, AD2/AD4 as unsigned
halfwords, AD8 as signed read status, ADC as an event-data pointer, CC as an
unsigned address word, and B0/B4 as signed pair words. E34C only stores zero
to its changed declarations; E4FC already treats ADC as a pointer. These
choices follow the other consumers without changing the accessed widths.
E758's F240 prototype now returns `u8`, matching the actual definition in
`code2` and F368's declaration. The collector retains its existing compatible
D0 declaration; its source and all emitted functions are unchanged.

## Proof

All seven sources were freshly compiled at their registered recipes in stock,
private generic and genuine ASPSX 2.79 `-q` arms. Every candidate's complete
function token stream equals its respective baseline. The stock arm resolves
all **1,029 words to retail without masks**. Generic and genuine still have
the preexisting external-GP discrepancy; equality to their prior outputs is
not a retail-exact claim for those arms.

| Row | Stock/retail words | Generic and genuine words | Existing recipe |
|---|---:|---:|---|
| E34C | 20 | 24 | CDK default |
| E4FC / Control_CD | 132 | 134 | CDK default |
| E758 | 698 | 730 | CDK `-G32 -fno-expensive-optimizations` |
| F2A4 | 31 | 32 | 2.6.3 `-fno-schedule-insns` |
| F368 | 113 | 122 | 2.7.2 default |
| F5AC | 10 | 11 | CDK default |
| F624 | 25 | 26 | 2.7.2 default |

The per-row receipts in [gp_cd_contract/](gp_cd_contract/) record source/header
hashes, full function sets, resolved retail bytes and all three comparisons.
The [scalar probe](gp_cd_contract/scalar_probe.md) independently checked E34C
and E4FC before the shared-header integration.

The [private full-image gate](gp_cd_contract/gate_receipt.json) compiled all
seven candidates together, including the new header, and reproduced the entire
retail image. All **869 physical objects** stayed byte-identical, including the
collector containing F240. The candidate gate restored its original sources,
objects and image afterward. The [production receipt](gp_cd_contract/production_receipt.json)
records the repeated production gate and unchanged recipe and objects. Adding the
header invalidated the global verifier fingerprint, so all 23 ownership proofs
and both placement certificates were refreshed. The accepted t272 model remains
explicitly labelled in the [ownership receipt](gp_cd_contract/ownership_receipt.json).
The module manifest and dependency ledger are unchanged.

## Unresolved views and next source work

This header deliberately does not declare the older overlapping address views
as owned storage. They remain visible source work:

- E758's `D_80081438[0x20]` reaches the result buffer but crosses already owned
  neighboring objects; it is not a 32-byte allocation claim.
- F368's `D_80081451` and `D_80081452` still use one-byte fields plus 15-byte
  padding. Their negative/positive byte offsets are address-generation views,
  not independent 16-byte objects.
- D1/D2/D3 and their aliased arrays overlap each other, D4 and the D8 buffer.
  Their existing padded extents are not ownership evidence.
- F2A4's `D_800814AC[12]` view overlaps B0/B4. Its bound does not establish
  another allocation.
- The driver and queue structs at D83958/D83968 still have separate source
  definitions, including E758's size-forcing driver padding. Their real accessed
  fields and compiler address forms must be reconciled before joining consumers.

The next source route is `az-c-rebuild`: start with F368's result aliases using
its [complete site map](gp_cd_contract/f368_site_map.md),
[retail listing](gp_cd_contract/f368_retail.dis) and
[lineage signatures](gp_cd_contract/f368_lineage.json),
then E758's existing [site map](gp_cd_partition/e758_site_map.md). Preserve the
observed GP versus absolute access forms without adding fake storage, pins or
assembler exceptions. Measure every changed consumer at its attributed recipe;
the five recipes are still a separate barrier to one ordinary owner TU.
The existing private E758 data-piece proof remains a layout experiment until
these source contracts and the complete consumer group are proved.

Production remains **23 owners, 869 physical / 884 logical rows, 189 dependencies
and 21 GP rows**. No dependency, placement level, historical module boundary or
generic-assembler transition is claimed by this repair.

The private reproducer is `work/native_lane/gp_cd_contract/probe.py`, followed by
`gate.py`. The paired probe uses the pre-change sources at `193c2e1c`; after
landing, the original sources are retained under its `prelanding/` directory.
Receipts bind the exact before/after source and header hashes. Repeating the
current source as both arms would only be a control, not a reproduction of the
historical declaration comparison.

## Next probes recorded after the shared-header gate

These are private source experiments, not part of the production repair above.
F368's padded D81451/52 structs can be replaced with incomplete byte-array views
while retaining the complete 113-word stock/retail instruction stream. Its
[probe](gp_cd_contract/next_probes/receipt.json) still shows the known generic/
genuine external-GP discrepancy; a new full-image gate is required before landing.

For E758, a control using the shared result union and eight explicit data
initializers reproduces all 698 retail words through stock, generic and genuine
arms after the validated data-piece projection. The raw diagnostic view has
unresolved small-data section bases; only the [projected results](gp_cd_contract/next_probes/projected_receipt.json)
provide an unmasked retail comparison for these objects.

Changing D1/D2/D3 array views to scalar byte views changes ten generic/genuine
mismatch regions even though the 698-word extent stays fixed. It changes the
compiler's access ordering and address reuse, so it is not a byte-exact repair.
Keeping the array access idiom while reducing D1/D2 and the D3 aliases to one
byte, and the primary D3 view to the two actually accessed bytes, does reproduce
all **698 words unmasked with both generic and genuine ASPSX**. The
[bounded-view receipt](gp_cd_contract/next_probes/bounded_receipt.json) and
[candidate](gp_cd_contract/next_probes/e758_owned_bounded_views.c) preserve this
result. These are access spans, not independent allocation claims for overlapping
views, and the existing distinct assembler aliases remain.

The stock assembler emits only 667 words for that candidate because its erroneous
external-size GP rule now affects these small byte views. Therefore this candidate
must travel with the pending generic-assembler correction and its full-image
consumer gates; it must not be installed under current stock semantics. Next is
that configured link proof and the remaining result/driver/queue views. The
matched private candidate is a concrete source-repair route, not a compiler wall.
