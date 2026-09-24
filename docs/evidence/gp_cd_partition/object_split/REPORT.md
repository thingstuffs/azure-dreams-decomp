# E758: linked proof of scattered initialized data

The private prototype links all eight E758 data definitions at their real retail
addresses while preserving every instruction byte and relocation record in the
assembled object. Both stock and private generic assembler arms reproduce the
complete 524,288-byte executable, SHA-1
`e6bfbb95ff6676899e077481221d73ddd4d3bf52`. This resolves the previously untested
layout mechanism. It does not activate a CD owner or remove a dependency.

## What changed in the candidate

The [source patch](candidate.patch) changes eight extern declarations into
explicit zero initializers in ordinary small data. The demonstrated eight-byte
81450 buffer is an array; its two scalar reads use element zero. The existing
body, aliases, recipe (CDK `-G32 -fno-expensive-optimizations`) and two pins
remain. No compiler or assembler exception is added.

Explicit initialization matters: the old tentative-common oracle yielded local
`.sbss` labels and section-base relocations. The new objects contain eight
GLOBAL symbols in 28 bytes of ordinary `.sdata`; all 32 relevant GP relocations
refer to those names with zero addends. The selected payload is 23 bytes. Five
zero compiler alignment bytes are not claimed as retail storage.

The private splitter moves each declared span to a separate `.sdata.<symbol>`
section. It preserves section indices for all existing sections, every symbol
index, all instruction bytes, and all 268 relocation entries. Only the selected
symbols' section/value fields change. It rejects unselected defined labels,
local/section-base targets, relocations originating in moved data, overlapping
spans, nonzero discarded bytes and unsupported ELF forms. This restricted
contract does not support arbitrary C data or infer sizes from zero ELF sizes.

## Evidence

- [Fresh three-assembler proof](initialized_receipt.json): whole emitted-function
  sets are exactly `func_8003E758`; stock, private generic and genuine ASPSX 2.79
  `-q` have identical 698-word streams. The explicit piece layout resolves all
  698 retail words with zero masks, including both split ELF objects.
- [Splitter checks](selfcheck_receipt.json): both actual initialized objects
  preserve all nondata payloads and relocation records; twelve unsafe cases are
  refused.
- [Independent GNU-linker tests](independent_link_receipt.json): nonzero data is
  preserved, contiguous placement preserves linked code/pointers/payload, and
  reversed sparse placement correctly resolves GP loads, HI/LO address formation
  and a 32-bit pointer. Six semantic refusal cases pass.
- [Full-image receipt](full_link_receipt.json): both arms match retail, eight
  named definitions have the expected non-ABS addresses, all 23 payload bytes
  agree, and all 868 other active C objects match production. The production
  source/configuration/image snapshot is unchanged.
- [Layout inventory](layout_inventory.md): exactly three old raw selectors are
  replaced by eight named sections and nine raw remainders totaling 195 bytes.
  All 179,625 asset bytes outside the selected spans remain at their original
  offsets (concatenated SHA-256
  `a969af86b62590b8d251feced3a174f2bc9cd4fdfcb818198554c3d03c15b941`).

The genuine LNK is never edited or linked by GNU ld. A private read-only view
maps its eight bounded, named initializer spans through the same explicit piece
plan. This preserves the complete raw comparison and gives zero-mask instruction
resolution. Actual allocation is separately proved by the linked ELF arms.
This distinction must survive any production fidelity integration.

GNU nm labels the final symbols `T` because the executable combines code and
data in the `_800` output section. The input definitions are GLOBAL small-data
symbols; the decisive checks are their non-ABS binding, exact addresses, input
section payloads and full image, not nm's output-section letter.

The [tooling audit](audit.md) records current reader, carver and certificate
interfaces and distinguishes the earlier local-label oracle from this input.

## Next implementation boundary

1. Add an explicit, opt-in data-piece plan to module tooling. Keep existing
   contiguous owners unchanged. The plan must declare source section, symbol,
   proved extent/alignment and destination section; reject overlapping retail
   ranges and duplicate ownership. Do not use an address list in the assembler.
2. Integrate the generic ELF partition step after assembly and before linking.
   Preserve the original object and a hashed transformation receipt. Wire it
   through generated Ninja, candidate compilation/restoration and physical-row
   enumeration so direct linking cannot bypass coverage checks. The prototype's
   hand-edited linker script is not the production interface.
3. Extend asset carving, genuine comparison and ownership certificates together.
   Fingerprints must bind the piece plan, transformer and pre/post objects.
   Genuine data projection must use a validated plan and fail on ambiguous or
   uncovered targets; never silently mask a split data reference.
4. Reconcile shared CD declarations and measure all affected consumers, including
   F240 in the `code2` remainder. F368 still has a four-byte global union view;
   widening its already-fixed local result buffer did not repair that shared
   declaration. Do not infer a common recipe or claim historical TU membership
   from this single-function proof.
5. Require existing module/configure/coverage/certificate gates, meaningful
   candidate-rejection/restoration tests, fresh genuine and retail checks, and
   a complete SLUS image before any activation. The remaining generic assembler
   transition and pass retirement retain their existing final owner sign-off.

Production remains 23 owners, 869 physical / 884 logical rows, 189 dependencies
and 21 GP rows. The prepared 18-function integration fixture remains separate.
The full goal stays active; this is a validated architectural experiment.

[Reproduction paths and hashes](reproducer.json) identify the retained private
scripts and artifacts. Run the initialized probe, splitter selfcheck, independent
link tests and full-link harness in that order with the fidelity Python environment.
