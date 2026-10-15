# Common sound registers and reverb control: bounded input review

Reviewer: pending. The existing jtbl_8005EDA0 key and original switch-table
ownership are preserved. The input now includes func_8005D88C followed by
func_8005EDA0, in retail order, at their unchanged stock-2.7.2 recipe with
empty compiler/assembler flags. Both use the SPU control halfword at offset
0x1AA in the existing SpuRegs layout. One controls reverb bit 0x80 and mirrors
the active flag; the other applies master/CD/external attributes and control
bits. This supports a bounded partial cluster within the r82 sound interval,
not a recovered historical filename or a separate original TU boundary.

The controller reuses SpuRegs instead of its redundant control-only record
and padded pointer wrapper. Its two observed state words are scalar s32.
D_80079500 is a u32 value view passed to the actual u32 range predicate
func_8005D9DC. Supporting producer evidence is in w_8005CA90 (stores the
channel value there) and w_8005DA88 (stores the indexed numeric mode value
and passes it to the register writer). No allocation/pointer ownership or
adjacent extent is inferred from that scalar view. The pointer/control
accesses remain ordinary nonvolatile operations, matching the existing
common owner. No qualifier or extra access is added.

The controller candidate passed an exact frozen-raw object control and
whole-object identity. Its masks, comparisons, calls and stores are preserved.
Delivery additionally requires the full image, complete physical-owner/member
direct genuine ASPSX 2.79 checks, zero masked retail relocations and the unchanged
data-owner prover for the original tables. No new data, logical row, collector
part, rowbase, recipe exception, gate tool, window value or noreturn census is
changed. The orchestrator reviews and performs real --write after final inputs.

Rebase receipt at 97f105e7f: this input uses the committed code/code2 parent recipes (both 2.7.2-cdk) and preserves the seven-function stock-2.7.2 sound_tu_code partition. Any earlier production proof is historical; this delivery requires fresh unchanged full-image, member/physical-owner genuine and relevant production-window checks at this HEAD. No old collector recipe, asm alias, compiler flag, pin-census implementation or parked-container setting is restored. Reviewer remains pending.
