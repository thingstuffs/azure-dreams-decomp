# Existing ELF data-split interfaces and validation assumptions

Read-only audit of the current tools and the exact E758 oracle object. No compiler, assembler, linker, or test was run for this note; `readelf` was used on the named existing object only.

## Existing readers, writers, and placement helpers

- `tools/fidelity/objread.py:47-134` is an ELF32 little-endian MIPS reader. It returns allocated PROGBITS/NOBITS sections, a symbol map, relocations, and unknown-relocation diagnostics. It has no ELF serialization or section-editing API. Its returned section bytes do not retain ELF section-header flags, alignment, type, or original file placement, and its relocation records do not retain the original symbol-table index or raw `r_info`.
- `tools/build/slus_modules.py:239-355` is the existing reusable placement path, not an object splitter. It carves untouched bytes from the original asset into raw chunks (optionally invokes `mipsel-linux-gnu-ld -r --format=binary` to make `.data` chunk objects), then rewrites the ordered linker script to put a module object's complete `.sdata` or `.sbss` input section between those chunks. The section selectors are whole input sections, not ranges of symbols within a section. It changes only the linker-script text and raw chunks; it does not rewrite a module ELF object.
- `tools/fidelity/probe_gp_module.py:60-131` shows a private one-datum pilot: it removes one known four-byte interval from `assets/54240.bin`, makes prefix/suffix binary objects, and inserts the aggregator's `.sdata` section at that slot. This is a linked placement demonstration, not a generic object section splitter.
- The bounded `tools/` search found no in-tree ELF section writer/repacker. Existing `objcopy` calls extract sections to raw binary or convert a linked image to binary; no `--update-section`, `--add-section`, or symbol-aware split/rewrite helper was found.

## Current typed-data proof surface

The module data manifest supplies `symbol`, `asset`, `offset`, `size`, `vram`, exact `bytes`, and `section`; the allowed sections are only `.sdata` and `.sbss`, with all-zero bytes required for `.sbss` (`tools/build/slus_modules.py:128-154,220-236`). It contains no C type, signedness, declared alignment, ELF binding, or per-symbol section-fragment identifier. Type interpretation therefore remains source/evidence review plus a declared byte extent.

`tools/fidelity/prove_slus_ownership.py:180-210` checks that each module object's complete section bytes equal the concatenation of the manifest bytes, that each named symbol is in the declared section at the prefix-sum offset and is either reported `global` or `local`, and that linked symbols have the declared VMA and the image has the declared asset bytes. It intentionally allows local storage, including static `.sbss`. `objread.read_elf()` retains ELF `st_size` as the fourth symbol tuple value, but `prove_data()` does not compare it to manifest `size`, nor does the reader preserve STT_OBJECT versus STT_NOTYPE for non-function symbols. It validates extents from manifest sizes and section bytes instead. Before that keyed symbol map can collapse duplicate definitions, `prove_slus_ownership.symbols()` rejects duplicate names using `nm` (`:167-177,238-248`).

For NOBITS, `read_elf()` turns the recorded `.sbss` section size into zero bytes (`objread.py:55-66`); the ownership proof compares that exact section length/payload and rejects nonzero `.sbss` manifest bytes. `tools/tests/test_slus_ownership_data.py:41-106,114-128` covers exact `.sdata`/`.sbss` payload sizes, a local NOBITS symbol, wrong offsets/sections and linked addresses, image-byte drift, nonzero `.sbss`, and a real assembled NOBITS sample. The test fixtures include a symbol size of 2, but do not assert that ELF `st_size` equals 2.

`tools/slus_module_evidence.py` is a freshness/certificate checker. Its physical descriptor covers module source, recipe, and function contributors; the certificate checks the reviewed evidence hash, recipe/image identity, and per-row function proof. It does not parse data sections or independently validate data symbol extents. The separate `prove_slus_ownership.py` receipt contains the section/data proof.

## Relocation information exposed to a checker

`objread.read_elf()` reads SHT_REL records and maps MIPS relocation numbers 2/4/5/6/7 to `32`, `26`, `HI16`, `LO16`, and `GPREL16` (`objread.py:28,87-134`). The returned relocation records include the target section containing the relocation, byte offset, relocation kind, normalized target, and decoded addend. A section-symbol or locally bound defined-symbol relocation is represented as a section-base target; for a local defined symbol, the symbol's section-relative value is folded into the addend. Global defined and undefined targets remain symbol targets. REL addends are read from instruction/data words; HI16 pairs with the later LO16 for the same symbol.

Downstream `aspsx_diff.View` canonicalizes those section/symbol targets and identifies GP extern uses (`tools/fidelity/aspsx_diff.py:192-196,229-267,312-320`). The data ownership proof itself does not enumerate or validate relocations. These interfaces preserve enough normalized information to compare relocation semantics, but they do not expose a ready-to-edit ELF representation.

## E758 object samples: tentative-local versus initialized

The first, tentative-local sample was `work/native_lane/gp_cd_partition/e758_owned_oracle/generic.o` (SHA-256 `c33cbf9859e843d53febe9ab0a321ed0e759f7bf8065da6a3749768ab1d751bc`). It has `.text.func_8003E758` size `0xae8`, zero-sized `.sdata`, and `.sbss` NOBITS size `0x20`, alignment 8. Its eight relevant labels are local NOTYPE/zero-size labels in `.sbss`, at offsets `D_800814D0=0`, `D_800814CC=4`, `D_800814D4=1`, `D_80081450=8`, `D_80080AD0=16`, `D_80080AD2=18`, `D_80080AD4=20`, and `D_80080AD8=24`. Its 32 `R_MIPS_GPREL16` relocations name `.sbss` as the section-symbol target; the reader represents them as `("sec", ".sbss")`. This is the initial tentative-local experiment, not the current initialized layout.

The current initialized sample is `work/native_lane/gp_cd_partition/object_split/initialized/{a.s,a.o,generic.o}`. The current `a.s` explicitly defines eight `.globl` labels with initialized bytes in `.sdata`; both current objects report `.sdata` PROGBITS size `0x1c` (28 bytes), alignment 4, `.sbss` size zero, and those eight labels as GLOBAL NOTYPE with `st_size == 0`. The symbols have these offsets and selected extents:

| Symbol | `.sdata` offset | selected bytes |
| --- | ---: | ---: |
| `D_800814D0` | 0 | 1 |
| `D_800814D4` | 1 | 1 |
| `D_800814CC` | 4 | 4 |
| `D_80081450` | 8 | 8 |
| `D_80080AD0` | 16 | 1 |
| `D_80080AD2` | 18 | 2 |
| `D_80080AD4` | 20 | 2 |
| `D_80080AD8` | 24 | 4 |

The selected extents total 23 bytes of the original 28-byte section. The five unselected bytes are the actual gaps at offsets `[2,4)`, `[17,18)`, and `[22,24)`; the samples do not promote those gaps to symbol extents. `initialized_receipt.json` records the same piece sizes and old ELF symbol size zero for each moved label.

Both current `a.o` and `generic.o` contain 32 `R_MIPS_GPREL16` relocations from `.rel.text.func_8003E758`. In these initialized objects, the relocation targets are the named GLOBAL symbols (`D_800814D0`, `D_800814CC`, `D_800814D4`, `D_80080AD8`, `D_80080AD0`, `D_80080AD2`, `D_80081450`, `D_80080AD4`); `objread.read_elf()` decodes addend zero for all 32. They are not section-base targets in this sample. The direct initialized receipt also records 698-word stock/generic/genuine equality, but that function result does not establish retail data-object extents.

Object identities checked: `initialized/a.o` SHA-256 `3c19c64f5580b2bdc80172a7b400a571e27fd25f662ba5f7c48d1d6d071f4607`; `initialized/generic.o` SHA-256 `1b56426a94ce9f03e576fdf647edd9edfe2725199ebf4b6221519307dda57c63`; `initialized/a.s` SHA-256 `55d2d6c3da8315440e44a9621358fde4e3e9a0fa367f5dbecf3ad4a19e372108`.

## Bounded implications

The reusable current mechanism is raw-asset interval carving plus linker-script section placement. The named reader and ownership proof can inspect section payloads, local/global binding class, offsets, linked addresses, image bytes, and normalized GP relocations, but they do not provide a general ELF rewrite path or validate per-symbol ELF `st_size`. Both the tentative-local and initialized E758 samples have zero-sized data labels; their bindings and GP relocation targets differ, so evidence must cite which sample it describes. These are object-local compiler/oracle layouts and do not establish retail object extents. This audit does not claim a particular splitting architecture.
