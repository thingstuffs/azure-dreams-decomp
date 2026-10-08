# Spiral-effect spawner at file 0x1972E54

Review: pending. Reviewer: pending.

The full 476-byte function occupies file [0x1972E54,0x1973030),
RAM [0x80024654,0x80024830). The existing following function
func_80024830 calls RAM 0x80024654 twice; the spawner installs the preceding
func_8002434C as callback and jumps internally to 0x800247FC. These relocations
plus a complete byte-exact C recompile independently support the row base.
The interval is disjoint from every existing region. It asserts no bank load
extent or physical TU boundary.

The C recovers the 40-byte frame, five callee-saved values, allocation and
sprite setup, mirrored angle, origin/target positioning, terrain-height cap,
and lifetime fields. The third ABI argument is unused. Typed s16 array
indexing by ((u32)angle >> 9) & 7 emits the retail shift/address/mask order;
the former byte-pointer expression emitted the mask too early. No register
pins, inline assembly, literal instructions or invented volatile accesses.

Compiler: gcc-2.7.2-cdk -O2 -G0; ASPSX 2.79 conventions. This working
lineage matches adjacent rows; the byte fingerprint alone is family-neutral.
Retail SHA-256: 6a7e30512d42bdf6ba9177e6fe813d9a626e76bb4f948b59bde898d1b84c1db9.
The bounded production window is dungeon_native_1972e54_recovered;
r103_astra_hold/PROOF.md contains the gate_all and independent assembler receipts.

Weak assignment to index 192 records the callback relationship, not strong
membership. No native-module promotion, baseline, L2 promotion, reviewer
acceptance or module certificate is fabricated. The whole five-function
cohort and trailing bank data remain separate review work.
