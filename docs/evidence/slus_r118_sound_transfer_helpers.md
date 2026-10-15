# Adjacent sound transfer helpers: membership and scalar declaration review

Reviewer: pending. This is an inferred bounded cluster within the established
stock-2.7.2 sound TU (docs/HANDOVER.md, r82, 0x8005CA90..0x8005FA34).
No original filename or original three-function TU boundary is asserted.
The three retail functions are consecutive: func_8005EC40 occupies 96 bytes,
func_8005ECA0 occupies 88 bytes, and func_8005ECF8 occupies 168 bytes. Their
text covers 0x8005EC40..0x8005EDA0, in this order. The physical aggregator
includes exactly those three whole logical rows, with their identical stock
2.7.2 recipe and empty compiler/assembler flags.

func_8005EC40 caps the requested value at 0x7EFF0, invokes func_8005D460 and
clears D_8007998C when D_80079990 is zero. func_8005ECA0 validates the address
range, invokes func_8005D598 to convert it, stores a halfword at D_80079970
and returns the widened halfword shifted by D_80079980. func_8005ECF8 checks
D_800794F4/D_8007998C, tests or waits for the event at D_800794EC, and latches
the completion value in D_8007998C. The shared state and consecutive text,
within the proven sound interval, support this partial integration candidate.
The neighboring common-attribute jump-table owner at func_8005EDA0 is excluded.
The streaming function func_8005E7E0 and every collector contribution are also
excluded; their aliasing or declaration reconciliation is separate work.

The header exposes only the accessed four-byte scalar state values and the
halfword latch at D_80079970. It replaces padded wrappers, array-of-three
addressing workarounds and the array-to-halfword cast with the corresponding
scalar lvalues. It does not define any global, claim an adjacent byte, change
an access width or add volatility. The current ordinary accesses are preserved.
The two callees' one-line prototypes agree with their canonical definitions;
their arguments remain 32-bit values. All bounds, shifts, return values, event
polling, control flow and storage ownership are preserved.

Every candidate passed an unchanged-recipe frozen-raw object control and exact
whole-object identity before staging. A private diagnostic cache preserves the
certificate-input cache. Object equality alone does not grant placement.
The final one-input physical TU must pass a fresh complete retail-image build
and the unchanged certify_slus_module.py dry-run, including complete direct
genuine ASPSX 2.79/member/physical-owner comparisons and zero masked retail
relocations. Review identity and real --write remain orchestrator actions.

No logical split record, compiler/assembler recipe exception, data carve,
collector part, rowbase, window bound, gate tool or noreturn census is changed.
The header allocates no storage. Other source-quality debt remains work.
This partial cluster does not assert that excluded functions belong to a
different historical TU.

Rebase receipt at 97f105e7f: this input uses the committed code/code2 parent recipes (both 2.7.2-cdk) and preserves the seven-function stock-2.7.2 sound_tu_code partition. Any earlier production proof is historical; this delivery requires fresh unchanged full-image, member/physical-owner genuine and relevant production-window checks at this HEAD. No old collector recipe, asm alias, compiler flag, pin-census implementation or parked-container setting is restored. Reviewer remains pending.
