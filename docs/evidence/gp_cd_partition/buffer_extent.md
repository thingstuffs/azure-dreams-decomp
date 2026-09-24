# `D_80081450` CD result-buffer extent

The locally available retail SDK assembly proves an **eight-byte writable
result view**, `0x80081450..0x80081457` (end exclusive `0x80081458`), for the
non-null CD result pointers used by `func_8003E758` and `func_8003F368`.
This is a minimum extent required by reachable successful SDK paths, not a
claim about the historical allocation or translation unit. The `54240` asset
bytes at offsets `0xA10..0xA17` are eight zero bytes and equal the retail image.

| Caller | Pointer passed to SDK | Relevant sites |
|---|---|---|
| `src/slus/w_8003E758.c` | `CDBUF = &D_80081438[0x18]`, resolving to `0x80081450` | macro at 82; `CdControl` at 148, 216, 232, 251, 434, 448; `CdSync` at 374, 411, 442 |
| `src/slus/w_8003F368.c` | `(u8 *)&D_80081451 - 1`, also `0x80081450` | `CdControl(0x10, ...)` at 56; `CdSync(1, ...)` at 68 |

`CdSync` in `build_slus/asm/psyq/libcd/S_012.s:12–21` passes its second
argument unchanged to `CD_sync`. In the retail `CD_sync` implementation
(`BIOS_1.s`, `0x80061958..0x80061BD8`), that pointer is saved in `$s6` at
`0x80061968`. For completion values 2 or 5, the branch at
`0x80061B50..0x80061B64` reaches a non-null check at `0x80061B78`; the
`0x80061B84..0x80061B98` loop copies eight bytes from `D_80086DC8` to
`$s6[0..7]` with `sb` at `0x80061B90`. The loop starts at 7 and terminates
after decrementing through -1. Both callers pass mode 1; 3F368 waits for
completion 2, while 3E758 checks completion 5 in one path.

`CdControl` in `S_016.s` retains its third argument in `$s2` at
`0x80060E10` and passes it as `CD_cw`'s third argument on its command path
(`0x80060ED4..0x80060EDC`; the parameter-probe path also passes it at
`0x80060EB0..0x80060EB8`). `CD_cw` in `BIOS_1.s` saves that result pointer
in `$s5` at `0x80061EBC`. Its successful result branch checks non-null at
`0x80062254` and copies eight bytes from `D_80086DC8` with `sb` at
`0x80062270` in the `0x8006225C..0x80062278` loop. The callers' command
values differ, but the copy is controlled by the result pointer and outcome,
not by a four-byte declaration at 81450. Failure or non-result paths can
write fewer bytes; the evidence establishes the **possible write span**.

`func_8003F368` itself saves, clears, and restores a four-byte union at
81450 (`w_8003F368.c:45–46,86`) and reads its first three bytes through
`D_80081450.b.mm`, `D_80081451.val`, and `D_80081452.val` at 90–92.
The byte tests at 101 and 103 likewise address 81451 and 81452. In
`func_8003E758`, direct scalar reads of 81450 occur at 435 and 455. These
caller-side accesses alone establish four bytes; the SDK's eight-byte copy
extends the required view through 81457.

The larger source declarations are **address-generation aliases**. In 3E758,
`D_80081438[0x20]` has a mathematical span `81438..81457`; its last eight
bytes are CDBUF, but the earlier part overlaps already owned 81440 and 81448
words. In 3F368, `S_80081451` is a one-byte value plus 15-byte pad, declared
for both `D_80081451` and `D_80081452`; their literal 16-byte spans would
overlap each other and the already owned 81460 word. Current code uses only
their `.val` bytes and address arithmetic, so neither 16-byte declaration
proves allocation. The generated symbol map confirms the alias addresses
81438, 81450, 81451 and 81452
(`build_slus/config/generated/slus_006.14.undefined_syms.txt:599–604`).

The bounded next ownership shape is therefore an eight-byte result view at
81450, with any source declaration reconciled against the scalar and alias
uses. The actual object/allocation boundary remains unproved; no production
source, asset, manifest or build was changed in this audit.

## Addendum: F368's first stack result and retail loop bytes

`w_8003F368.c:39,48` declares `sync_result[4]` and passes it to the first
`CdSync`. The retail `func_8003F368` prologue at `0x8003F368` reserves 48
bytes (`addiu $sp,$sp,-48`); the call at `0x8003F388` passes `$sp+24` in
`$a1` at `0x8003F38C`. The SDK's possible eight-byte copy therefore reaches
frame offsets 24–31. The function's saved `$s0/$s1/$s2/$ra` slots begin at
offsets 32, 36, 40 and 44, respectively. The later `cd_loc` bytes are at
offsets 16–18, and the retail function has no other access to offsets 28–31.
Thus the eight-byte SDK write stays within the retail frame and does not
overwrite an adjacent live slot. It still writes past the four-byte
`sync_result` **C declaration**; the machine-stack observation does not make
that C access in bounds or prove the compiler allocated an eight-byte object.
E758's `sync_status[8]` declaration at `w_8003E758.c:95` already covers the
SDK copy width.

The copy loops were checked against `baserom/slus_006.14` at the VMA-to-file
offsets recorded in the assembly comments. The comment bytes, taken in their
printed raw-byte order, equal the retail slices exactly:

| Retail slice, end exclusive | File offset | Bytes | SHA-256 |
|---|---:|---:|---|
| `CD_sync` `80061B84–80061B9C` | `0x35384` | 24 | `d86c6206f9a62beb28436d5f07f0f2f41e3173fd862af40ac588fe4127ff6920` |
| `CD_cw` `8006225C–8006227C` | `0x35A5C` | 32 | `d273f8f88a35c45a5590a5423e59f43ffa114ce11dd8b28b7f844f5be5a03f8a` |

The F368 prologue and first call slice `8003F368–8003F39C` is 52 retail
bytes at file offset `0x12B68`, SHA-256
`a061d5394d177a0bfd11dc1a6166ffb1fe11a612d172234b8cb3875d88fb85d6`.
These are static retail bytes; they establish the call address and possible
write extent, not that every runtime call takes a copying branch.
