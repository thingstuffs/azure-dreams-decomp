# script_opcode_handlers: initialized .data owner

The event-script interpreter `interpret_script_opcodes_until_action_changes`
(`slus/konami_runtime_w_80038AB8`) dispatches through `script_opcode_handlers`,
an 89-word table of handler addresses at VMA 0x8006AA90, one slot per
`enum ScriptOpcode` value (`include/engine/script.h`). Until this change the
table was raw bytes inside the resident-data asset `assets/3E018.bin` and the C
saw only an `extern`.

## Ownership

| owner | member | symbol | asset offset | VMA | size |
|---|---|---|---|---|---|
| script_opcode_handlers | src/slus/konami_runtime_w_80038AB8.c | D_8006AA90 (`script_opcode_handlers`) | 0x278 | 0x8006AA90 | 356 |

The table is defined in the interpreter's source with designated initializers
indexed by the opcode enum (a GNU C extension GCC 2.7.2 accepts). The wrapper
`src/slus/konami_runtime_w_80038AB8_owned.c` includes the member, as the jump-table
owners do. The grouping is an inferred build organization, not a recovered retail
TU boundary.

GCC emits the table as `.data` with `.align 2`; the relocations are 89
`R_MIPS_32` words against the handler symbols (six slots name `script_nop`).
The existing asset carve (`plan_asset_carves`) splits `3E018.o` around
the span and places this object's `.data` there. `slus_modules.py` now accepts
`.data` records. GNU as pads the section from 356 to 368 bytes. `slus_rodata_trim.py`
now cuts an owned `.data` back to its manifest span with the same fail-closed
checks as `.rodata`: the cut must be zero, shorter than the alignment, and hold no
relocation or symbol. The neighbouring resident data before and after the span
remains in asset chunks.

The slot type is `ScriptOpcodeHandler` (`void (*)()`). The handlers take different
views of the script context. Four handlers return values that the dispatcher
ignores: `script_set_flag`, `script_jump_if_flag_set`, `script_divide` and
`script_call_variable`. Their initializers are cast to the slot type.

## Validation

`tools/lanes/prove_scope.sh` built the SLUS image with retail SHA-1
`e6bfbb95ff6676899e077481221d73ddd4d3bf52`. The interpreter's `.text` is unchanged.
This is data placement only. It grants no L4/L5 certificate, and
`prove_slus_ownership.py` has no `.data` branch yet.
