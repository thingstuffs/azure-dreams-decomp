# Real split small-data storage for 48660

`func_80048660` now owns its three initialized coordinate halfwords and its
private uninitialized generation halfword in C. The body, recipe and existing
unrelated source scaffolding are unchanged. The complete SLUS image is retail
exact, and genuine ASPSX 2.79 matches all 53 function words with zero masked
relocations. This removes one GP dependency: 35 to 34 remaining, and 202 to 201
total dependency records. It does not certify module placement or L4.

| Symbol | Definition | Input section | Retail address |
|---|---|---|---|
| `D_80080B10` | `u16`, initialized to zero | `.sdata` + 0 | `0x80080B10` |
| `D_80080B12` | `u16`, initialized to zero | `.sdata` + 2 | `0x80080B12` |
| `D_80080B14` | `u16`, initialized to zero | `.sdata` + 4 | `0x80080B14` |
| `D_80081530` | `static u16`, uninitialized | `.sbss` + 0 | `0x80081530` |

The private storage has no other canonical SLUS source users. Explicit internal
linkage expresses its current sole ownership; it does not claim historical
visibility. GCC emits `.lcomm`, and both genuine ASPSX and stock maspsx allocate
the two-byte storage. The earlier tentative-global experiment exposed maspsx's
local lowering of small `.comm` symbols; the accepted C declares that scope
explicitly. No assembler change, artificial dependency, padding global or
section attribute is used. The old unrelated padded state declaration remains
visible source debt, and no whole-function cleanup claim is made.

The [ownership receipt](gp_split_storage_receipt.json) proves exact section
contents/lengths, symbol section/offset/binding, non-absolute linked addresses,
full-image equality and genuine-ASPSX equality. `.sbss` is NOBITS: its section
size represents zero storage, while its actual linked bytes are checked against
retail. The six `.sdata` bytes and two `.sbss` bytes replace their separate raw
asset intervals. All 884 logical rows and 875 physical C inputs are preserved.

The production manifest accepts `.sdata` and zero-only `.sbss`, with one ordered,
contiguous interval per input section. Distinct sections from the same object
may occupy separate intervals; cross-section and cross-module overlap remains
an error. Ownership proof uses ELF section identity, size and contents, rejects
COMMON/absolute stand-ins and ambiguous owned names, and verifies the complete
linked image. Receipt schema 2 stores proofs by section. Historical schema-1
receipts still describe the earlier measurements.

```sh
flock build_ovl/work/land.lock \
  python3 tools/fidelity/prove_slus_ownership.py gp_split_storage \
    --output work/native_lane/gp_split_integration/recheck.json
```

The original runtime directory pilot is recertified against the updated helper,
verifier and pinned recipe. The private source experiments and their visibility
comparison remain documented in [gp_next_ownership.md](gp_next_ownership.md).

All 87 focused tests pass (54 SLUS tests and 33 configuration, genuine-comparison
and recipe-landing tests), including real GNU assembler/linker fixtures
for separated initialized and NOBITS storage and negative ownership cases.
The refreshed [module build receipt](slus_module_build_receipt.json) preserves
all 16 active units while accepting unchanged/restored candidates, rejecting
changed code and sibling regressions, and refusing incompatible or partial
module recipe changes. The runtime pilot still matches genuine ASPSX over all
104 words with zero masks.
