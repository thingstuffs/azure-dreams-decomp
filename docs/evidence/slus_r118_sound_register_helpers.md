# Sound register helpers: coherent read/write interface

Reviewer: pending. This is an inferred partial integration in the known stock
GCC 2.7.2 sound TU, not a recovered filename or original three-function boundary.
The earlier bounded two-function integration remains historical evidence.

The owner includes storeU16TableEntry / func_8005D550, func_8005D63C and
func_8005D678 in retail order. Setter/readback share the actual halfword register
base pointer D_80079958 and scalar shift cell D_80079980. The setter preserves
its existing volatile halfword stores through SoundRegister16; readback keeps
ordinary loads. The DMA helper retains the existing volatile s32 pointee of
D_80079968. No pointer object gains volatility, allocated data or adjacent extent.
No padded extern wrappers are introduced. The selected setter first passes an
exact frozen-raw control and complete object trial; full owner production proof
must independently pass before delivery.

func_8005D598 remains excluded work: its per-row --expand-div alignment target
is not TU-boundary evidence. The seven code collector sound functions remain
in the landed sound_tu_code owner. This package preserves that entire logical
pipeline and all current compiler/assembler recipes; it claims no neighboring
function or data. Required proof is the unchanged complete retail-image gate,
pinned recipe and complete member/full physical-owner genuine ASPSX 2.79 checks,
with zero masked retail relocations. Real certification and review are pending.
