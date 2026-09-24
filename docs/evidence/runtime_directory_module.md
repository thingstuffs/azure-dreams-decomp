# Runtime key-directory module review

This is an inferred grouping of three resident runtime functions, not a recovered
original filename or proof of an original translation-unit boundary. The name
`runtime_directory` describes a table that maps keys to indices; it does not claim
filesystem behavior. Function symbols retain their address names.

## Membership and interface

| function | observed role | shared state/interface |
|---|---|---|
| `func_8003C634` | searches signed keys at an eight-byte stride; returns index or -1 | reads `D_80080A6C` and the table beginning at `D_8006B200` |
| `func_8003C758` | calls the lookup, or bypasses it under the existing mode/guard conditions; on failure uses the last index | calls `func_8003C634` and external setter `func_8003C6F8`, reads the same count |
| `func_8003C920` | copies the default table prefix or installs the alternate first pair, then sets count to four or one | writes the same table and count |

The selected functions lie at 0x8003C634, 0x8003C758 and 0x8003C920. All currently
use the same stock `2.7.2-cdk` recipe with empty compiler and assembler flags.
Shared state, a direct call, a coherent interface and the nearby addresses support
this partial module under PLAN.md's call-graph/address-range fallback. Intervening
functions and other users are not silently claimed as members. The inspected
assertion/row evidence index has no exact assertion naming these three functions
or a conflicting original module; that index is partial, so absence is not proof
that no historical evidence exists. The old C758 registry entry counts two extern
prototypes as definitions; module validation instead checks actual function bodies. In particular,
`func_8003C6F8` remains an external function and its outstanding assembler/data
dependency is not cleared by this pilot.

The shared header `include/slus/runtime_directory.h` declares the prototypes,
globals and `GpTablePrefix` once. The prefix is exactly eight `u32` words: the
observed 32-byte copy and word assignments establish this extent. It deliberately
does not name unproved semantic fields or claim a larger object layout. The lookup
reads the corresponding signed word view at an eight-byte stride. External byte
arrays remain incomplete rather than guessing their bounds. The fixed guard byte
at 0x800DCF4D retains its existing explicit `s8` access; its ownership and semantic
name remain unknown. The existing volatile local copy in `func_8003C920` is retained;
this integration adds no volatile qualifier, pin, inline assembly or fake dependency.

## Data ownership and proof

The ordinary definition `s32 D_80080A6C = 4;` replaces exactly the four retail bytes
`04 00 00 00` at file offset 0x5426C (asset 54240 offset 0x2C). The generated link
places its `.sdata` at 0x80080A6C and removes the former absolute symbol assignment.
The untouched prefix and suffix remain raw assets. This proves present C ownership;
it does not establish the historical compiler's original object boundaries.

Canonical per-row source fragments remain editable and keep their original IDs.
The ordinary C aggregator includes them in retail order and is compiled once.
The header supplies shared types and declarations to all three users. The row
registry still represents all 884 logical SLUS rows while this grouping removes
two physical compilation edges.

`tools/fidelity/probe_slus_module_build.py` reproduces the complete isolated
configured build, genuine-ASPSX comparison, data placement and candidate checks.
The durable result is [slus_module_build_receipt.json](slus_module_build_receipt.json):
the full 524,288-byte image equals retail, all three function addresses and sizes
are preserved, and genuine ASPSX 2.79 matches 104 words with no masked relocations.
An edit which leaves its own function exact but changes a sibling is rejected by
the full-image candidate gate. These are the required checks again at activation.

The live certificate under `ledger/modules/` records the reviewed source/header/
manifest fingerprint, this review's hash, verifier inputs, the pinned recipe and
each member's fresh genuine/retail proof. Placement is invalidated when those inputs
change. L4/L5 still require the existing ladder criteria; grouping alone supplies
no exemption for pins, tail jumps, fidelity sites or toolchain dependence.
