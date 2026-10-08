# Recovered callback at file 0x1870FDC

Review: pending. Reviewer: pending. No placement certificate is requested by this row delivery.

The registered entry row writes the address 0x800247DC into the spawned object's
callback field at +0x10. At the predecessor's proven load delta 0x7E7B3800 that
address is file 0x1870FDC. Retail starts with `addiu sp,sp,-32` (0x27BDFFE0),
saves the three incoming arguments, and terminates with `jr ra` and its delay
slot at 0x80024970/0x80024974. Every local branch/jump stays within the function.
The recovered interval is [0x1870FDC,0x1871178), 412 bytes; the following bytes
are outside this code claim. The base is independently bound by the existing
callback reference and the recovered function's internal absolute jumps.

The C updates a particle's owner flags, delay, motion and lifetime, then fades
its primitive or requests deletion. Its parameters follow the callback's
three observed argument registers: effect payload, motion, primitive. Its
registration call uses the real SLUS contract (`s32`, node pointer, integer
registration ID); the function address used as that ID is explicitly cast.
The declarations were checked against w_8004491C.c, w_80045340.c and code.c.
The global object flags retain the shared runtime declaration.

One CDK-G0 TU containing the original entry function and this callback emits
the native four-byte entry and 2,008 + 412 code bytes. Both maspsx/GNU as and
genuine ASPSX 2.79 resolve to the complete 2,424 retail bytes, SHA-256
994956783b71164ed240309edac35f0c9b837235928c7c57607afb4b168140bd.
No byte mask, owned retail substitution, forced per-function placement, inline
instruction, fabricated symbol size, or entry alias is used in that experiment.

The separate registration package corrects the parent callback/return declarations
while retaining its legacy prefix, and adds the recovered row, its disjoint
proven rowbase interval, a weak assignment
to the parent's ledger group and an expanded validation window. That window
rebuilds all 2,424 bytes with two C segments and zero raw segments. The original 2,012-byte parent window also passes. The parent keeps its composite
representation in this independent row delivery, but no longer declares the
callback as a byte array.
The native two-function proposal is retained separately and removes that debt
only after complete-module membership, type, ownership and L3 screening.

This establishes the callback's bank-local source owner and a concrete proposed
two-function reconstruction. It does not recover an historical source filename,
upgrade the existing weak membership, allocate resident storage, or issue a
certificate. The existing module gate also requires one proven map containing
the whole cohort; the two adjacent proven rowbase records do not meet that
manifest condition. Resolve that explicitly before offering the module.

Proofs and commands: r101_astra_gate/PROOF.md, evidence/callback_recovery.log,
evidence/callback_window.log, scratch/held/work/recovered/1870800/ and
scratch/callback/work/s3_splat/dungeon_native_1870800_recovered/.
