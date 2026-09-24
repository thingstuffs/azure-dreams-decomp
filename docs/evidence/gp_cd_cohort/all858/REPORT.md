# All-active-SLUS guarded-generic inventory

The frozen `gp_ready26_cd/stage` was cloned before any output was removed.
Its passing receipt, graph, generic CLI and package, 858 active object bytes,
and current production inputs were pinned and rechecked after the trial.
Only cloned C objects were invalidated. Ninja rebuilt all 858 active physical
SLUS C TUs with the guarded generic assembler at four jobs; none failed or
went missing. The prior 13 private generic rules remained in the graph.

Only two rebuilt objects changed canonical function/data/relocation semantics:

| Object | Function | Words before → after | Relocation change |
| --- | --- | ---: | --- |
| `build/src/code.o` | `func_8003F5D4` | 3 → 4 | `D_800814C8`: GPREL16 → HI16/LO16 |
| `build/src/code.o` | `func_8003F5E0` | 3 → 4 | `D_800814C8`: GPREL16 → HI16/LO16 |
| `build/src/code2.o` | `func_80048DA0` | 11 → 13 | `D_80080B1B` and `D_80080B1C`: GPREL16 → HI16/LO16 |

No function set or allocated data payload changed. The other 856 objects
have equal canonical function tokens, data payloads, and relocations. Among
them, 266 raw ELF hashes changed without a measured instruction, data, or
canonical relocation change; they are recorded separately rather than
counted as semantic differences. The new CD owner's eleven data-piece
sidecars verified successfully.

The fresh generated link and objcopy completed, then the SHA-1 gate failed.
The trial image is 524,304 bytes, 16 bytes longer than the 524,288-byte
retail image. The first direct byte difference is at file offset `0x74F0`.
That length increase equals the four new instruction words across the three
changed functions, and shifts later linked content; the large raw byte-diff
count is not an independent function mismatch count. No mask, filter, source
repair, or production edit was applied in this lane.

The [receipt](receipt.json) holds all 858 object comparisons, exact changed
function names and token-alignment diagnostics, relocation transitions,
before/after pins, and the failed gate result. `all_objects_build.log`,
`full_image_gate.log`, `image_diff_summary.json`, and the cloned `stage/`
retain the raw evidence. Unequal-length alignment in the receipt uses
`SequenceMatcher` over canonical `aspsx_diff` tokens and is labeled
descriptive; it is not presented as the gate's canonical distance score.
