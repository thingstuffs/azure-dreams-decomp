# CD-state cleanup: eight-byte buffer repair and ownership evidence

The resumed goal found and repaired a real C bounds error in
`func_8003F368`: `CdSync` can write eight result bytes, while its local
`sync_result` array declared four. The array now declares eight bytes. This
changes neither the compiled object nor any of the 113 retail instruction
words at the existing plain 2.7.2 recipe. The isolated full executable gate
passes, all 868 other active objects are unchanged, and the production gate
is recorded in the [activation receipt](gp_cd_partition/activation.json).
The existing pin and GP dependency remain.

The [buffer audit](gp_cd_partition/buffer_extent.md) follows the actual retail
`CdSync -> CD_sync` and `CdControl -> CD_cw` copies. Each can write eight bytes.
F368 passes sp+24 in its 48-byte frame; the last copied byte is sp+31 and the
saved registers begin at sp+32. Widening the C array therefore corrects the
source contract without moving live machine storage. The same audit establishes
an eight-byte writable global view at `80081450..80081458`, beyond the earlier
four-byte caller-only observation. It does not infer a historical allocation.

## Fresh compiler and assembler baseline

The [seven-row baseline](gp_cd_partition/baseline.md) compiles each unchanged
whole source at its registered recipe. All stock outputs match the complete
retail function extents with zero masks. Every private generic result equals
genuine ASPSX 2.79 `-q`, including raw emitted-function coverage, but they are
longer than retail: 24/134/730/32/122/11/26 words for
E34C/E4FC/E758/F2A4/F368/F5AC/F624 respectively, against
20/132/698/31/113/10/25 retail words. All seven have externally declared GP
state. The complete [baseline receipt](gp_cd_partition/baseline_receipt.json)
predates the buffer correction; the [buffer direct receipt](gp_cd_partition/buffer_probe_receipt.json)
proves that correction leaves all three assembler results unchanged.

The [state inventory](gp_cd_partition/state_inventory.md) identifies eight
direct CD function consumers, including F240 in the `code2` remainder, across
five registered recipes. The separate message-mode 81550 component is not
part of this CD group. No CD data owner is activated by this checkpoint.

## E758's current problem is data representation

The [complete retail map](gp_cd_partition/e758_site_map.md) and
[unchanged byte classifier](gp_cd_partition/lineage.json) show mixed macro and
compiler-split stores, split addresses, return copies and 32 GP references.
Reading the current raw compiler output resolves the old store-dialect concern:
it already emits bare D2/D3 stores and compiler-split driver-field stores in
one function at CDK `-G32 -fno-expensive-optimizations`. A new store-rewriting
assembler pass is not needed to obtain that combination here.

A [bounded local-storage oracle](gp_cd_partition/e758_owned_oracle_receipt.json)
changes only the eight GP extern declarations into zero-initialized tentative
definitions, and gives 81450 the demonstrated eight-byte array view. It retains
the current body, recipe, aliases and two existing pins. Stock, the private
generic assembler and genuine ASPSX now reproduce **all 698 retail words with
zero masks**. Their full function token streams also agree. This is a reachable
data-ownership effect, not evidence for a missing compiler.

**The oracle is not linkable production ownership proof.** Its `.comm` objects
are packed into one `.sbss`; instruction comparison resolves each common symbol
at its named retail address. Actual retail cells are scattered. The current
[module carver](gp_cd_partition/data_section_options.md) supports only one
contiguous `.sdata` span and one contiguous `.sbss` span per module. It cannot
place this packed `.sbss` at the scattered addresses. Full link, real allocation
bounds, shared declarations, compatible group recipes, and collector coverage
still need proof. The oracle earns no dependency removal or placement level.

The [old wall measurements](gp_cd_partition/prior_analysis.md) remain scoped
to their G8 v3/v4 candidates. Their suggested split-store bridge is superseded
as a diagnosis of the present E758 source. The classifier itself still reports
mixed evidence and does not identify a unique historical compiler or TU.

## Named sections: measured capability, not the needed fix

The [three-spelling storage probe](gp_cd_partition/section_probe/REPORT.md)
confirms that CDK and genuine ASPSX accept two independently named four-byte
data sections. The actual named-section directives survive the complete input
path. However, genuine and private generic assembly then use absolute addressing
for all six tested references. Ordinary initialized small data and tentative
commons retain GP loads/stores. Direct C section attributes therefore lose the
required genuine GP code in this measured case; they are not the CD ownership
solution. No production assembler change was made.

## Linked data-piece prototype

The resumed [layout experiment](gp_cd_partition/object_split/REPORT.md) now
proves a linkable private representation: eight explicitly initialized globals
are split into named sections after assembly. All 698 words still match genuine
ASPSX and retail with zero masks. Stock and generic full-image arms are both
retail-exact, including 23 selected data bytes and every surrounding byte. The
transformer changes no instruction or relocation record. This closes the layout
experiment above; shared declarations, production tooling and owner activation
remain unfinished. The earlier tentative-common oracle remains only an oracle.

## Tracked next work

1. Integrate the now-proved explicit data-piece layout into module tooling,
   genuine comparison and ownership certificates together. The
   [linked prototype](gp_cd_partition/object_split/REPORT.md) uses explicit
   initialized globals and partitions assembled data without changing instruction
   bytes or relocation entries. Both full executable arms match retail; all 868
   outside objects are unchanged. Production schema and activation remain pending.
   Preserve raw gap bytes and reject ambiguous data targets.
2. Reconcile the CD shared declarations using the eight-byte result buffer,
   real B0/B4 pair, byte state and AD fields. Measure complete consumers, including
   F240, under evidenced recipes. A grouping is acceptable only with complete
   function coverage, exact data bytes, genuine comparison and full-image proof.
3. Route any C-owned mismatches from that measured declaration contract through
   `az-c-rebuild`, using the retained site map. Existing pins can remain during
   this work. Do not start another compiler sweep from the historical score table.

Production remains 23 ownership units, 869 physical / 884 logical rows,
189 dependencies and 21 GP rows. The prepared 18-function generic integration
fixture is still separate; the buffer fix changes none of its outside object
bytes. Production assembler semantics and pass retirement are unchanged.

The prior 81554 activation reproducer gained old-recipe precondition guards
in its ignored script. Its cached-registry refresh was replayed on the saved
preactivation rows and reproduced the current registry exactly; the recorded
script hash is refreshed here. This is a reproducer correction, not another
81554 activation.
