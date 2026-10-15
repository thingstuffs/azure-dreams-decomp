# Adjacent sound transfer frontends

Reviewer: pending. Membership is an inferred bounded integration inside the
stock GCC 2.7.2 sound interval recorded by docs/HANDOVER.md. These two consecutive
retail functions span 0x8005D460..0x8005D550: w_8005D460 starts/restarts transfer,
and w_8005D4E8 uploads a buffer. Both call the actual variadic command dispatcher
func_8005D1D0, read the halfword D_80079970, and shift by the scalar D_80079980.
The first also reads the scalar busy flag D_80079974 and can call the FIFO writer.
Their common recipe has empty compiler and assembler flags. This is a partial
sound integration; no historical filename or exact original two-function TU
boundary is claimed. Adjacent storeU16TableEntry and all collector functions
remain excluded. Per-row recipe exceptions are not boundary evidence.

The old declaration wrappers explicitly padded these actual scalar cells to
force addressing. This interface declares only the observed u16 address cell
and s32 busy/shift cells; it allocates no data and asserts no adjacent extent.
The dispatcher prototype is its actual variadic definition in w_8005D1D0.c.
The FIFO writer's actual definition in w_8005CE98.c returns void and accepts a
u16 pointer and unsigned byte count. The frontend keeps its established scalar
address ABI, explicitly casting that address/count at this call. Signed shifts,
return values, branches, and operation order otherwise stay unchanged.

Each candidate requires its own exact frozen-raw object control before the
scalar-view trial. Both complete objects must match at their unchanged stock
recipe. Those diagnostics do not grant placement. The final shared-header
physical owner must pass the unchanged complete-image production build,
pinned recipe, and certify_slus_module.py dry-run, including complete direct
genuine ASPSX 2.79/member/physical-owner comparison with zero masked retail
relocations. No gate, fingerprint, logical split, rowbase, noreturn or compiler
exception is changed. Real reviewed --write remains the orchestrator's action.

Rebase receipt at 97f105e7f: this input uses the committed code/code2 parent recipes (both 2.7.2-cdk) and preserves the seven-function stock-2.7.2 sound_tu_code partition. Any earlier production proof is historical; this delivery requires fresh unchanged full-image, member/physical-owner genuine and relevant production-window checks at this HEAD. No old collector recipe, asm alias, compiler flag, pin-census implementation or parked-container setting is restored. Reviewer remains pending.
