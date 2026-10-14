# sound_tu_code: the slus/code functions inside the stock sound TU

`slus/code` is a partition parent whose remainder used stock 2.7.2. The remainder
spans two retail compilation regions. Most of it is the 2.7.2-cdk -G8 game image
from 0x80033AA8 to 0x8005CA70. The other region is the stock-2.7.2 sound TU from
0x8005CA90 to 0x8005FA34 (r82_fable_slus; land_recipe_move `--slus-region-b`).
This partition puts the seven sound-TU functions into their own stock owner.
After that, the image remainder can use the game image's compiler.

## Owner

The owner is `sound_tu_code`, a partition-only module with source
`src/sound_tu_code_owned.c` and the stock recipe `2.7.2`. It has no data and no
whole members. Its single incoming part, from `slus/code`, holds these functions:

- func_8005D6D8
- func_8005D704
- func_8005D798
- func_8005DA68
- func_8005E4A0
- func_8005E78C
- func_8005EC0C

The owner source repeats the declarations these bodies use. They are copied from
`src/slus/code.c` without changes, including the padded `D_80079958_t`. The
canonical `src/slus/code.c` still holds every definition, so the logical row
keeps its 149 remainder definitions plus its existing parts.

Text placement does not depend on which object holds a function. configure.py
links every `.text.func_*` section through one `SORT_BY_NAME` glob, so any
owner keeps the retail layout.

**Why not join an existing stock sound module.** The only stock modules inside
the sound TU are `jtbl_8005EDA0` and `jtbl_8005F134`. Both are jump-table
(.rodata) owners, and each wraps a single row. `prove_slus_ownership.prove_rodata`
takes its function set from `members` only, and the `jtbl_<row>` convention ties
each wrapper to one row (docs/SLUS_PARTITIONS.md, jump-table owners). An incoming
part would make that module a connected physical owner, which needs direct
genuine proof of the complete TU. The jump-table proofs would also change.
Every other sound-TU row is an ordinary single-function TU, not a module.

## Measurements

These were run in a scratch root at b5521a548:

- **Part added, remainder still stock:** the full SLUS SHA-1 gate gives MATCH
  (861 TUs) with the re-pinned recipe. `code.o` emits 142 functions and
  `sound_tu_code_owned.o` emits the 7.
- **Remainder at cdk** (`slus_recipe.py --tu code --to 2.7.2-cdk --apply`):
  - The text has 5 small-extern declaration fixes from r118_sonnet_unknowns.
  - The control build at stock with the new text gives MATCH.
  - The cdk gate gives MATCH: SHA-1 e6bfbb95…, retail SHA-256 ae19d8d4….
- **Sound owner at cdk** (trial, restored): NO MATCH.
  - func_8005D6D8 and func_8005D704 load the pointer high half into `v0`
    instead of `a0`.
  - func_8005DA68 tests the 0x1AA flag with `lbu`/`srl 7` instead of
    `lhu`/`andi 0x80`/`sltu`. This makes the function 8 bytes shorter.
  - Stock 2.7.2 reproduces retail for all three.

`prove_slus_ownership.py sound_tu_code` refuses with "module has no owned data".
This is a recipe partition, not a data-ownership unit. `certify_slus_module.py`
refuses partition-only owners by design.
