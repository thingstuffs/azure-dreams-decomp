# r121_hardholds: two dungeon rows (patch B6)

Two formerly held dungeon rows are exact C at the unchanged `2.7.2-cdk-G0` recipe, 208 bytes.
They supersede the `r121_remnants` hold records (NOMATCH splits and `unported` coverage records).

| Row | File offset / bytes | True function | Window |
|---|---:|---|---|
| dungeon/func_800B7914 | 0xD7914 / 176 | func_800BD074 | `dungeon_engine.overlay.yaml` |
| dungeon/func_813266E8 | 0x13466E8 / 32 | func_8016DEE8 | `dungeon_deep_1346004_truebase_8016d804.overlay.yaml` |

## func_800B7914 (save-image object view)

A page pointer or an inferred two-word state object is not justified; the bounded object
declaration generated 180 bytes against 176 retail. Independent retail witnesses establish a
real serialized save image at 0x80010000, exactly 0x6000 bytes (read/write wrappers pass the whole
buffer in 0xC0 units; the checksum covers [0x208,0x6000); the resident reset routine clears
+0x208C/+0x2090). `SaveImage { prefix[0x208C]; pending; active; suffix[0x3F6C]; }` therefore
represents the imported storage object, and the local pointer lives in s0 across the call, giving
all 176 bytes with no pin, asm, volatile, fake dependency or recipe change. Witness hashes:
`r121_hardholds/save_image_storage.json`; method note: `tools/learnings/r121_save_image_owner.md`.
This grants no arbitrary page abstraction for other globals.

## func_813266E8 (signed-bound RNG wrapper)

The callee `func_8016ADB8` is the complete local signed-bound RNG routine at file 0x13435B8 in an
independently proven bank; it takes the bound in a0 and returns the sample in v0, so the wrapper
forwards the argument and the result (this resolves the ABI hold that withdrew the no-argument wrapper).

## Proofs kept

`r121_hardholds/proofs/<row>/`: `generated.bin` and `retail.bin` (byte-identical), `generated.dis`,
`proof.json` (sizes and hashes; `exact: true`). `r121_hardholds/first_passes/`: independent m2c first
passes. `r121_hardholds/<row>.lab.log`: lab logs. raw/ keeps the live m2c first pass for both rows.
Window verification is recorded in the patch REPORT and re-proved by the consolidation gate.

The r121_hardholds town rows and 21 callback rows are not part of this evidence: they are already live
through r121_nodonor (town 0x5FF770 corrected rowbase) and r121_rem_opus.
