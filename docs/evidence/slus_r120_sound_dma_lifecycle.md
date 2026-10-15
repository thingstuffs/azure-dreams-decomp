# Sound hardware initialization, FIFO and DMA lifecycle

Reviewer: pending. This bounded inferred integration lies in the documented
stock GCC 2.7.2 sound interval. The initializer directly calls FIFO/delay; FIFO,
start and completion call delay; the dispatcher shares their transfer registers
and actual DMA channel cells. No original filename or six-function TU boundary
is asserted. Intervening functions and the complete landed code owner remain
separate; per-row alignment flags are never boundary evidence.

The hardware view consists of the initializer's observed 24 voice register slots,
observed common/transfer fields through0x1B6, and real register-offset holes.
No storage is allocated. Existing per-field qualifiers and access widths remain:
FIFO status reads are ordinary, initializer status reads use the same volatile
halfword view as its former field. FIFO transfer-address accesses are ordinary;
DMA start/dispatcher accesses use their existing volatile-halfword view. DMA
start's volatile D79960 pointer-object qualifier remains in the shared header;
dispatcher uses its original ordinary pointer-object view at its access. Pointee
qualifiers are independent and unchanged. Callback D79990 remains the actual
volatile function-pointer object; initializer's zero clear retains that qualifier.
D79994 retains its existing volatile word clear. The actual ten-halfword clear
loop and eight-halfword startup sample retain their observed extents.

The actual transfer-address and status halfwords each have ordinary and volatile
union-component views, both exactly two bytes at their observed register offset.
This preserves GCC's structured-memory classification for the original volatile
member accesses without adding allocation or access qualifiers. The dispatcher
then matches all164retail words; pointer casting alone had lost MEM_IN_STRUCT_P.
The initializer also keeps an actual component access for status. Its existing
BIOS printf call (A0/3F, retail libc/C63 stub) uses the integer return interface,
with the value ignored. This restores stock sched.c's function-wide return-register
set-count conditions while preserving the FIFO's real void interface. It matches
all165retail words. Both results independently pass fresh whole-image and direct
genuine ASPSX2.79 checks with zero retail masks before this coherent integration.

Dispatcher's full multi-block transfer_arg lifetime, varargs macros, branchless
block count and existing nonvolatile store cast are preserved. Delay is unchanged.
Raw controls/trials are retained separately and cannot grant placement. The fresh
complete image, pinned recipe, direct genuine ASPSX 2.79 and zero masked retail
comparisons must pass for every full member and this entire physical owner.
Real review/certificate writes and any L4/L5 promotion remain pending.
