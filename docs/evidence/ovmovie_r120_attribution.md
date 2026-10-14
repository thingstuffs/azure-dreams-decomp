# OVMOVIE r120 follow-up: six recovered rows

Base: 97f105e7fd8bbfdeab9b87ad675d5345c744b939. Review pending. The combined package supplies the native LIBPRESS entry; the game entry remains held.

The three game gaps are readable C at the one game recipe, 2.7.2-cdk-G0:
file 0x4A8 / 488 B (80176CA8), 0x72C / 400 B (80176F2C), and 0x99C / 1340 B
(8017719C). Every complete body matches retail under GNU/maspsx and genuine ASPSX
2.79, with zero masked words. Re-reading at the true base removed the old candidates'
invented calls: their alleged callees were internal branch destinations.

The largest body uses an inline boolean helper that emits no separate function.
Its cleanup retains `display.viewport.w *= 3 / 2`: integer division truncates to one;
cdk retains the width load while deleting the redundant store. This explicitly
reconstructs retail word 310 and is flagged for source review. There are no asm,
register pins, goto statements, fabricated rows, or added volatile stack accesses.

DecDCTout (0x10C0 / 32 B), MDEC_reset (0x11A0 / 252 B), and MDEC_out_sync
(0x1458 / 152 B) are now proposed as real rows at 2.7.2-G0. Their independently
compiled full bodies also match both assembler legs and retail, zero masks.
The reset's volatile accesses are the actual decoder/DMA hardware accesses.

The guarded installer appends two absent split records, updates four previously
NOMATCH records without changing extents, consolidates the narrow load proofs into the independently proven resident region,
and appends six exact baselines and readable-body promotions. The prior
row_1044_80177844 proof is preserved in the guarded consolidation proposal. All six use the existing production
config/overlays/ovmovie.overlay.yaml. Its unchanged gate_all --all window matches
131072 bytes in fresh scratch. Registry reports zero rows lacking a gate window;
noreturn_syms files are unchanged. The replay has 28 OVMOVIE rows / 5516 B, all L3,
zero pins, zero tail jumps. A second dry-run has no mutations.

The complete eleven-function game TU matches all 3628 text bytes in natural retail
order under both assemblers. The library's seventeen-function owned TU matches 1888
text bytes, 169 string bytes, and 332 writable-data bytes (2389 semantic bytes).
The original SDK object establishes strong library membership, including its seven
private helpers, tables, identification pair and hardware-pointer variables. G0 is
chosen per TU: cdk default-G discriminates the game head; owned stock-G8 changes
seven library bodies and has 34 gp relocations. The original identification pair's
bit-field interpretation is not claimed.

The ordinary stock-G0 native model now proves and physically projects every library
allocation: [0,0xA9), [0xED8,0x1638), and [0x1A3C,0x1B88). Strict literal/symbol/section
inventory and GNU tail-padding checks cover three string and four data padding bytes;
all semantic bytes match genuine and retail without masks/raw payload substitution.
A real scratch certification succeeds. All 37 live modules were really certified
under this exact tool version after 172 fresh affected production windows passed.
The explicit clean dungeon-engine timing is 201.871 seconds, byte-exact.

The final combined package supplies one pending native entry, ovmovie_libpress.
After scratch test review/certification and levels regeneration, its seventeen rows
reach L5; no actual live review or certificate is installed by the package. GAME
remains a complete text candidate. Its six scalar and seven pointer-record candidates
at [0x19D0,0x1A3C) still lack original object ownership, caller/ABI and full relocated
allocation evidence. The preceding 36 bytes are proven VLC assembly spill workspace,
excluded from GAME. The resident load map itself is already proven and supplied.

The prior 800413C0 repair remains included: its fake 80177C48 call was its own
epilogue at +0x88. Structured C at 80177BC0 removes that call and the fitted maspsx
rewrite. Append-only dependence evidence retires the stale annotations on that row
and 80040360. Names remain proposals only. common.py already unparks OVMOVIE at
this base; this package makes no additional unpark change.

Reproduction: work/native_lane/r120_ovm/PROOF.md. Row receipts:
docs/evidence/ovmovie_r120_recovered.json. Complete game proof and library ownership
artifacts remain in the lane. The authoritative installer is the single combined
work/native_lane/r120_ovm/delivery/final/apply.py; no predecessor package is required.
