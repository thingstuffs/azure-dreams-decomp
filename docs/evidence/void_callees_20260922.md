# `config/void_callees.txt`: the retail-byte evidence, symbol by symbol (2026-09-22)

The owner's 2026-09-22 ruling (docs/L0_BLOCKED_PLAN_20260922.md sec 5, docs/FIDELITY.md's
`PASSTHRU_NO_ARGS` bullet) exempts a zero-argument call whose callee is defined `(void)` in the
tree and whose row verifies byte-exact.  `tools/census.py::void_exact_targets()` implements that
by scanning `src/{main,town,dungeon,slus}/*.c` for `func_X(void) {` definitions.

This file covers the next question: the PASSTHRU-undefined class, where the callee has **no C
definition anywhere in the tree**, so `void_exact_targets()` can never see it and the row stays at
L0 for ever.  For each symbol below the callee's own **retail instructions** were read out of the
shipped container and checked: does it read `a0`-`a3` before writing them?

## How a callee's bytes were located

A row's retail slice is `<container>.BIN[foff : foff+size]` and it links at
`foff + rowbase.delta_for(family, foff)` (`tools/gate/rowbase.py`, `config/overlays/*.rowbase.jsonl`).
A `jal` encodes an absolute address, so a callee named `func_T` in the caller's C is the byte at
`foff_callee = T - delta`, disassembled with `mipsel-linux-gnu-objdump -D -b binary -m mips:3000 -EL`.
Two devkit modules carry no rowbase record (`town/func_8087FEF0`, `town/func_808B94E0`); their delta
was recovered by fingerprint - the unique TOWN.BIN offset at which **all five** of the module's own
`jal` targets land on a function start (prologue word, or preceded by `jr ra`).  Both searches
returned exactly one candidate.

## The test

The function's reachable extent is computed by a linear sweep from the entry that follows every
conditional-branch target, stops at `j`/`jr` (delay slot included) and re-extends only from a branch
target - so the body is the whole function, not just the first block.  Inside that extent every
occurrence of `a0`-`a3` is classified write-or-read in address order.  **Verdict `reads nothing` =
the first occurrence of each of `a0`-`a3` is a write (or the register never appears).**  The
extents below end exactly at the function's own `jr ra`, which is the cross-check that the located
address really is a function start.

## Tier A - the callee's own bytes were read (24 symbols)

| symbol | container | foff | extent | first instructions | a0-a3 first use | verdict |
|---|---|---|---|---|---|---|
| `func_800176B4` | town | 0x438EB4 | 0x800176B4-0x800176EC (15 w) | `addiu sp,sp,-24; sw ra,16(sp); lui v0,0x8001` | a0=write, a1=write | reads nothing |
| `func_800178D0` | town | 0x6590D0 | 0x800178D0-0x80017920 (21 w) | `addiu sp,sp,-24; sw ra,16(sp); lui a0,0x8002` | a0=write | reads nothing |
| `func_80017918` | town | 0x6AB918 | 0x80017918-0x80017934 (8 w) | `lui v0,0x8001; lw v0,24576(v0); nop` | never appears | reads nothing |
| `func_8001796C` | town | 0x3F696C | 0x8001796C-0x80017A04 (39 w) | `lui v1,0x8001; lbu v0,25960(v1); addiu sp,sp,-32` | a0=write | reads nothing |
| `func_800187AC` | town | 0x3F17AC | 0x800187AC-0x800187E4 (15 w) | `addiu sp,sp,-24; sw ra,16(sp); lui v0,0x8001` | a0=write, a1=write | reads nothing |
| `func_80018C58` | town | 0x3F1C58 | 0x80018C58-0x80018CCC (30 w) | `move a1,zero; lui v0,0x8001; lw v0,24576(v0)` | a0=write, a1=write, a2=write, a3=write | reads nothing |
| `func_800191E8` | town | 0x5551E8 | 0x800191E8-0x80019214 (12 w) | `lui v0,0x8001; lw v0,24576(v0); nop` | never appears | reads nothing |
| `func_8001A7AC` | town | 0x6917AC | 0x8001A7AC-0x8001A7E4 (15 w) | `addiu sp,sp,-24; sw ra,16(sp); lui v0,0x8001` | a0=write, a1=write | reads nothing |
| `func_8001A7F8` | town | 0x3F37F8 | 0x8001A7F8-0x8001A814 (8 w) | `lui v0,0x8001; lw v0,24576(v0); nop` | never appears | reads nothing |
| `func_8001A934` | town | 0x691934 | 0x8001A934-0x8001A950 (8 w) | `lui v0,0x8001; lw v0,24576(v0); nop` | never appears | reads nothing |
| `func_8001E82C` | town | 0x3ED82C | 0x8001E82C-0x8001E848 (8 w) | `lui v0,0x8001; lw v0,24576(v0); nop` | never appears | reads nothing |
| `func_8016E264` | dungeon | 0x1346A64 | 0x8016E264-0x8016E2FC (39 w) | `addiu sp,sp,-32; sw s2,24(sp); lui s2,0x8017` | a0=write, a1=write, a2=write | reads nothing |
| `func_8070042C` | town | 0x83942C | 0x8070042C-0x80700484 (23 w) | `addiu sp,sp,-32; sw s1,20(sp); move s1,zero` | a0=write | reads nothing |
| `func_80700488` | town | 0x839488 | 0x80700488-0x807004DC (22 w) | `addiu sp,sp,-24; sw s0,16(sp); li s0,4` | a0=write | reads nothing |
| `func_80700B4C` | town | 0x80134C | 0x80700B4C-0x80700BC8 (32 w) | `addiu sp,sp,-32; sw s1,20(sp); move s1,zero` | a0=write | reads nothing |
| `func_80700B7C` | town | 0x83337C | 0x80700B7C-0x80700C64 (59 w) | `addiu sp,sp,-64; sw ra,56(sp); sw s3,52(sp)` | a0=write, a1=write | reads nothing |
| `func_80700BCC` | town | 0x8013CC | 0x80700BCC-0x80700C20 (22 w) | `addiu sp,sp,-24; sw s0,16(sp); li s0,0x4` | a0=write | reads nothing |
| `func_80700D84` | town | 0x7F4D84 | 0x80700D84-0x80700E14 (37 w) | `lui v0,0x8070; lw v0,6532(v0); addiu sp,sp,-32` | a0=write, a1=write, a2=write | reads nothing |
| `func_80700E3C` | town | 0x7FFE3C | 0x80700E3C-0x80700E94 (23 w) | `addiu sp,sp,-32; sw s1,20(sp); move s1,zero` | a0=write | reads nothing |
| `func_80700E98` | town | 0x7FFE98 | 0x80700E98-0x80700EEC (22 w) | `addiu sp,sp,-24; sw s0,16(sp); li s0,0x4` | a0=write | reads nothing |
| `func_80700EB4` | town | 0x8016B4 | 0x80700EB4-0x80700ED4 (9 w) | `lui v0,0x8070; addiu v0,v0,1784; lw v1,0(v0)` | a0=write | reads nothing |
| `func_80701060` | town | 0x7F5060 | 0x80701060-0x80701120 (49 w) | `addiu sp,sp,-40; sw ra,32(sp); lui a1,0x8070` | a0=write, a1=write, a2=write, a3=write | reads nothing |
| `func_8070114C` | town | 0x7F514C | 0x8070114C-0x80701200 (46 w) | `li a2,0x1; li t1,0x1; lui t0,0x8070` | a0=write, a1=write, a2=write, a3=write | reads nothing |
| `func_8070168C` | town | 0x7F568C | 0x8070168C-0x80701774 (59 w) | `addiu sp,sp,-64; sw ra,56(sp); sw s3,52(sp)` | a0=write, a1=write | reads nothing |

### Per-symbol notes (where the address came from, and who calls it)

- **`func_800176B4`** @ 0x800176B4 - located via sweep_437C44; TOWN/DUNGEON foff 0x438EB4. Callers in the L0 set: town/func_804B7E18.
- **`func_800178D0`** @ 0x800178D0 - located via sweep_657A24; TOWN/DUNGEON foff 0x6590D0. Callers in the L0 set: town/func_806D7FDC.
- **`func_80017918`** @ 0x80017918 - located via sweep_6AA100; TOWN/DUNGEON foff 0x6AB918. Callers in the L0 set: town/func_8072A100.
- **`func_8001796C`** @ 0x8001796C - located via sweep_3F6460; TOWN/DUNGEON foff 0x3F696C. Callers in the L0 set: town/func_80476A08.
- **`func_800187AC`** @ 0x800187AC - located via sweep_3EF28C; TOWN/DUNGEON foff 0x3F17AC. Callers in the L0 set: town/func_8046FCF4.
- **`func_80018C58`** @ 0x80018C58 - located via module delta 0x7fc27000 (sweep_3EF28C); TOWN/DUNGEON foff 0x3F1C58. Callers in the L0 set: town/func_80471F74.
- **`func_800191E8`** @ 0x800191E8 - located via sweep_55228C; TOWN/DUNGEON foff 0x5551E8. Callers in the L0 set: town/func_805D3370.
- **`func_8001A7AC`** @ 0x8001A7AC - located via sweep_68DCE4; TOWN/DUNGEON foff 0x6917AC. Callers in the L0 set: town/func_8070E604, town/func_8070E728, town/func_8070E81C.
- **`func_8001A7F8`** @ 0x8001A7F8 - located via module delta 0x7fc27000 (sweep_3EF28C); TOWN/DUNGEON foff 0x3F37F8. Callers in the L0 set: town/func_8046F28C, town/func_8046FEE8.
- **`func_8001A934`** @ 0x8001A934 - located via sweep_68DCE4; TOWN/DUNGEON foff 0x691934. Callers in the L0 set: town/func_8070DE48.
- **`func_8001E82C`** @ 0x8001E82C - located via sweep_3EA000; TOWN/DUNGEON foff 0x3ED82C. Callers in the L0 set: town/func_80468418, town/func_8046B884.
- **`func_8016E264`** @ 0x8016E264 - located via dungeon module delta 0x7ee27800; TOWN/DUNGEON foff 0x1346A64. Callers in the L0 set: dungeon/func_813265B8, dungeon/func_8132661C.
- **`func_8070042C`** @ 0x8070042C - located via module delta 0x7fec7000 (fingerprint, 5/5); TOWN/DUNGEON foff 0x83942C. Callers in the L0 set: town/func_808B94E0.
- **`func_80700488`** @ 0x80700488 - located via module delta 0x7fec7000 (fingerprint, 5/5); TOWN/DUNGEON foff 0x839488. Callers in the L0 set: town/func_808B94E0.  Same bytes are the registered row **town/func_808B9488** (exact=True), whose C defines it under the synthetic name.
- **`func_80700B4C`** @ 0x80700B4C - located via row_80134c_80700b4c = town/func_8088134C; TOWN/DUNGEON foff 0x80134C. Callers in the L0 set: town/func_8088124C, town/func_80881424.  Same bytes are the registered row **town/func_8088134C** (exact=True), whose C defines it under the synthetic name.
- **`func_80700B7C`** @ 0x80700B7C - located via module delta 0x7fecd800 (row_8332ac_80700aac); TOWN/DUNGEON foff 0x83337C. Callers in the L0 set: town/func_808B32AC.
- **`func_80700BCC`** @ 0x80700BCC - located via module delta 0x7feff800 = town/func_808813CC; TOWN/DUNGEON foff 0x8013CC. Callers in the L0 set: town/func_80881424.  Same bytes are the registered row **town/func_808813CC** (exact=True), whose C defines it under the synthetic name.
- **`func_80700D84`** @ 0x80700D84 - located via row_7f4e18_80700e18 module = town/func_80874D84; TOWN/DUNGEON foff 0x7F4D84. Callers in the L0 set: town/func_80874E18.  Same bytes are the registered row **town/func_80874D84** (exact=True), whose C defines it under the synthetic name.
- **`func_80700E3C`** @ 0x80700E3C - located via module delta 0x7ff01000 (fingerprint, 5/5); TOWN/DUNGEON foff 0x7FFE3C. Callers in the L0 set: town/func_8087FDA4, town/func_8087FEF0.
- **`func_80700E98`** @ 0x80700E98 - located via module delta 0x7ff01000 (fingerprint, 5/5); TOWN/DUNGEON foff 0x7FFE98. Callers in the L0 set: town/func_8087FEF0.  Same bytes are the registered row **town/func_8087FE98** (exact=True), whose C defines it under the synthetic name.
- **`func_80700EB4`** @ 0x80700EB4 - located via module delta 0x7feff800 = town/func_808816B4; TOWN/DUNGEON foff 0x8016B4. Callers in the L0 set: town/func_808816D8.  Same bytes are the registered row **town/func_808816B4** (exact=True), whose C defines it under the synthetic name.
- **`func_80701060`** @ 0x80701060 - located via module delta 0x7ff0c000 = town/func_80875060; TOWN/DUNGEON foff 0x7F5060. Callers in the L0 set: town/func_80875124, town/func_80875204.  Same bytes are the registered row **town/func_80875060** (exact=True), whose C defines it under the synthetic name.
- **`func_8070114C`** @ 0x8070114C - located via module delta 0x7ff0c000 = town/func_8087514C; TOWN/DUNGEON foff 0x7F514C. Callers in the L0 set: town/func_80875204.  Same bytes are the registered row **town/func_8087514C** (exact=True), whose C defines it under the synthetic name.
- **`func_8070168C`** @ 0x8070168C - located via row_7f55ac_807015ac module; TOWN/DUNGEON foff 0x7F568C. Callers in the L0 set: town/func_808755AC.

## Tier B - call-site bytes only, the callee's own image is not on the disc (1 symbol)

`func_80071494` is called 37 times (32 audited sites, 11 callers) by the TOWN devkit module whose
rows link at `0x8052xxxx` (`config/overlays/town.rowbase.jsonl`, `town100_*` / `row_78*` records).
That module's external calls - `0x80034A1C`, `0x800373DC`, `0x8003BC18`, ... `0x8006F49C`,
`0x80071424`, `0x80071494` - do **not** resolve in `baserom/slus_006.14` (whose text is
`0x8002D000`-`0x80081800`, PS-X EXE header `t_addr/t_size`): `0x800373DC` and `0x8003BC18` land
mid-instruction-stream and `0x80071494` lands in the Shift-JIS font/rodata table at
`slus foff 0x44C94`.  A fingerprint search over TOWN.BIN, DUNGEON.BIN, MAIN.BIN, OVMOVIE.BIN and
the SLUS image for an offset at which 15 of that module's external targets are simultaneously
function starts scores at best 4/15 (noise).  **The devkit main executable these blobs were linked
against did not ship**, so `func_80071494` has no bytes anywhere on this disc.  What the retail
does say, from the caller side:

- **No call site sets an argument register.**  At all 37 `jal 0x80071494` in the module the delay
  slot is either `nop` or an unrelated store (`sw v0,12(s0)`, `ae220008 sw v0,8(s1)`,
  `a602002a sh v0,42(s0)`), and no `li/move/lui/lw` into `a0`-`a3` precedes the call in its block.
- **The result is consumed and masked**: `andi v0,v0,0x7f`, `andi v0,v0,0xff`,
  `andi a1,v0,0xf`, `andi a1,v0,0x3` immediately after the call - the shape of `s32 rand(void)`,
  the same shape as the already-ruled hub `func_800A6D30` (190 sites, `s32 func_800A6D30(void)`).
- **`need` is constant `a3` at all 32 audited sites across 11 different callers**
  (`ledger/cache/audit.json`).  A callee-derived `need` on a function reading only `a3` and not
  `a0`-`a2` is impossible; this is the caller-side liveness label sec 5 already identified.

That is weaker than tier A (no callee bytes), and it is listed separately so the line can be
deleted on its own if the owner wants only tier A.

## Considered and NOT listed

- **`func_800C8408`** (1 site, `dungeon/func_800C335C`): located at dungeon foff 0xE2CA8 and its
  **first instruction is `lw v0,20(a0)`** - it reads `a0`.  Genuine PASSTHRU class; the row keeps
  the site and takes the t8/t8b move instead.
- **`func_80019988`** (1 site, `town/func_8070E604`): already `params:void *record, s32 entry_index`
  in the tree - genuine class, untouched.
- **`func_8007CA38` / `func_8007CA48`** (`main/func_80019EF8`, the MAIN.BIN `c_server.c` copy):
  same problem as tier B - the callee addresses `0x8007xxxx` are outside MAIN.BIN's own extent under
  its module delta (`0x7FDC3000`, file 0x275800 long) and are not the SLUS bytes at those addresses.
  `func_8007CA48` is already declared `extern void func_8007CA48(void);` in two TUs, but
  `func_8007CA38` is declared **`(void)` in `src/main/func_80019EF8.c` and
  `(s32, s32, s32, s32)` in `src/main/func_80019A10.c`** - the tree contradicts itself, so the
  arity is not established and neither symbol is listed.  `main/func_80019EF8` (488 B) stays at L0.

## Tier A, segment-resolved (added after the coordinator hand-off, 2026-09-22)

A TOWN overlay symbol is **not unique**: each event module links its own copy of the scene runtime,
so the same `func_XXXXXXXX` can be different code in two modules.  Measured here:
`func_80019988` is a 21-word `(void)` wrapper at town foff 0x690988 (first instruction
`lui a0,0x8002` - a write; no `a0`-`a3` read anywhere in its extent) in the `sweep_68DCE4` module,
and a 21-word function at town foff 0x2AF188 - row `town/func_8032F188`, defined
`(void *record, s32 entry_index)` and exact - whose third instruction is `lh a0,24(s0)` after
`move s0,a0`, i.e. it really **does** read `a0` and `a1`.  Resolving a PASSTHRU target by name
across the whole tree therefore reaches the wrong body; the callee must be read in the *caller's own
segment* (`caller foff + rowbase delta`).

For the three symbols added below, every audited caller of the name lies in a single segment
(`ledger/cache/audit.json`), so a name-keyed entry cannot leak into another module:

| symbol | callers (foff range) | callee foff | extent | a0-a3 first use | verdict |
|---|---|---|---|---|---|
| `func_80019988` | town 0x68E0DC-0x68F2FC (5 rows) | 0x690988 | 0x80019988-0x800199D8 (21 w) | a0=write, a1-a3 never appear | reads nothing |
| `func_8070090C` | town 0x832F58-0x833074 (3 rows) | 0x83310C | 0x8070090C-0x807009F4 (59 w) | a0=write, a1=write | reads nothing |
| `func_80701404` | town 0x7F5238-0x7F5364 (3 rows) | 0x7F5404 | 0x80701404-0x807014EC (59 w) | a0=write, a1=write | reads nothing; the same bytes are row `town/func_80875404`, `void func_80875404(void)`, exact |

**A new PASSTHRU site on one of these names in another segment invalidates the entry** and that
segment's copy must be read before the site is exempted.  That is also why the generic remedy the
coordinator proposed - aliasing every `(void)`-exact row's `true_name` into
`void_exact_targets()` - was **not** taken: `town/func_8032F188` shows the alias would exempt a
callee that genuinely reads `a0`/`a1` wherever the name is reused.

## Branch-path check on the five tier-A bodies with a conditional branch before their first `aN` write

`func_8016E264` (taken path 0x8016E2E4-0x8016E2FC: epilogue loads only), `func_8001796C`
(0x800179DC-0x80017A04: one global `lbu` then the epilogue), `func_80700D84`, `func_80700B7C` and
`func_8070168C` (no conditional branch at all before their first `aN` write) were disassembled on
the branch-taken path by hand; none reads `a0`-`a3`.

## Tier B, second entry: `func_8007CA38` / `func_8007CA48` (2026-09-22, evening)

The "Considered and NOT listed" note above left `main/func_80019EF8` (488 B) at L0 on two grounds:
the callee bytes could not be located, and the tree contradicted itself on `func_8007CA38`'s arity
(`(void)` in `src/main/func_80019EF8.c`, `(s32, s32, s32, s32)` in `src/main/func_80019A10.c`).
Both are settled here.

### Why the callee is not on the disc

* Under the caller's own module delta `0x7FDC3000` (`main/func_80019EF8` links at true base
  `0x8002CEF8` = foff `0x269EF8`), `0x8007CA38` maps to **foff `0x2B9A38`**, past the end of
  `MAIN_MAIN.BIN` (`0x275800`).  No other delta in `config/overlays/main.rowbase.jsonl` helps:
  the 63 `0x80197000` regions give a negative offset, and the four `0x80066F60` regions give foff
  `0x15AD8`, which lies far outside those regions' own extent (`0x21A0C`-`0x23F00`) and so is not
  base-resolvable code for that module.  Neither caller row (foff `0x269A10`, `0x269EF8`) is inside
  any rowbase region at all.
* The **SLUS bytes at that address are not this code**.  `baserom/slus_006.14` is a PS-X EXE with
  `t_addr = 0x8002D000`, `t_size = 0x54800`, so `0x8007CA38` does fall inside the resident segment
  (file offset `0x50238`) - but that part of the segment is `.rodata`, not text:
  `0x8007BEF0` is the middle of the string table `"Error: Can't push matrix,stack(max 20) is
  full!"`, and `0x8007CA38` disassembles as a table of ascending half-word pairs
  (`07d20df2 07cd0df5 07c80df8 ...`).  The MAIN overlay links its own `c_server`/libapi copy whose
  text sits above `MAIN_MAIN.BIN`'s end; that devkit image never shipped, exactly like
  `func_80071494`.  Tier A is therefore not available for either symbol.

### Call-site evidence (`mipsel-linux-gnu-objdump -D -b binary -m mips:3000 -EL` over MAIN_MAIN.BIN)

`jal 0x8007ca38` = word `0C01F28E`: **7 sites**, none of which writes `a0`-`a3` for the call.

| site foff | addr | the call, with its delay slot | `a0`-`a3` set for it? |
|---|---|---|---|
| 0x269A18 | 0x8002CA18 | `addiu sp,sp,-24; sw ra,20(sp); jal 0x8007ca38; sw s0,16(sp)` | no - function prologue |
| 0x269F00 | 0x8002CF00 | `addiu sp,sp,-24; sw ra,16(sp); jal 0x8007ca38; nop` | no - and the caller is `void func_80019EF8(void)`, so `a0`-`a3` hold entry garbage |
| 0x2716F4 | 0x800346F4 | `jal 0x8007cb08; move a0,zero` then `jal 0x8007ca38; nop` | no - the `move a0,zero` is the *previous* call's argument |
| 0x271738 | 0x80034738 | `addiu sp,sp,-24; sw ra,16(sp); jal 0x8007ca38; nop` | no |
| 0x2717D0 | 0x800347D0 | `lui at,0x8041; sw ra,-28116(at); jal 0x8007ca38; nop` | no |
| 0x2718A8 | 0x800348A8 | `lui at,0x8041; sw ra,-28100(at); jal 0x8007ca38; nop` | no |
| 0x271960 | 0x80034960 | `lui at,0x8041; sw ra,-28100(at); jal 0x8007ca38; nop` | no |

`jal 0x8007ca48` = word `0C01F292`: **5 sites** (0x269C58, 0x26A0C8, 0x271714, 0x271750, 0x271814),
none setting `a0`-`a3` either; the `li a0,1` that precedes two of them is the argument of the
immediately preceding `jal 0x8007bef0` (the assert/abort helper).

**Verdict.** A zero-argument callee.  Site 0x269F00 is decisive on its own: it sits in a `(void)`
function whose whole prologue is `addiu sp; sw ra; jal; nop`, so a callee that read `a0`-`a3` there
would be reading whatever the previous call left behind.  The `(s32, s32, s32, s32)` spelling in
`src/main/func_80019A10.c` was m2c's usual entry-liveness artefact - that TU forwards its own
`arg0`-`arg3` as the *first* statement, which compiles to no code at all, so the retail bytes are
identical either way and cannot support the four parameters.

**Applied 2026-09-22.** `src/main/func_80019A10.c` now declares `extern void func_8007CA38(void);`
and calls `func_8007CA38();` (`tools/promote.py --source agents:claude-opus-l0`: exact, class
`match`, total 0) - the two TUs agree and the standing "never give a zero-argument call arguments"
rule is satisfied.  `func_80019A10`'s own `(s32, s32, s32, s32)` signature is left alone: its four
parameters are now unused, and **no `jal` to it exists anywhere in `MAIN_MAIN.BIN`** (nor to
`func_80019EF8`), so nothing on the disc can settle its arity.

Both symbols are listed **tier B**, not tier A: the task asked for tier A, but tier A means the
callee's own instructions were read, and they are not on the disc.  The marking mirrors
`func_80071494` and the line can be deleted on its own.

## Tier B, third entry: `func_80020298` (2026-09-22, town, single site)

`town/func_800C4D18` (`true_name` `func_800C2478`, `config/decomp_audit_baseline.json`) carries one
`PASSTHRU_NO_ARGS|func_80020298|0` site.  `src/town/func_800C4D18.c` defines `void func_800C2478(void)`
whose entire body is two zero-argument calls:

```c
void func_800C2478(void) {
    func_800C2444();
    func_80020298();
}
```

**Single-site confirmation (re-run for this entry).** `jal 0x80020298` encodes as opcode 3 over
`target >> 2`, word `0x0C0080A6` (`(3<<26) | ((0x80020298>>2) & 0x03FFFFFF)`), little-endian bytes
`a6 80 00 0c`.  A byte-string scan of `build_ovl/work/s3_splat/extract/TOWN_TOWN.BIN` (16,889,856 B)
for that 4-byte pattern returns **exactly one hit, at foff `0x44D28`** - matching the evidence handed
off.  Disassembling the surrounding words (`mipsel-linux-gnu-objdump -D -b binary -m mips:3000 -EL`
window, and by hand for the boundary) gives the whole function:

```
00044d18 <.data+0x44d18>:
   44d18:  27bdffe8   addiu sp,sp,-24
   44d1c:  afbf0010   sw    ra,16(sp)
   44d20:  0c030911   jal   0xc2444
   44d24:  00000000   nop
   44d28:  0c0080a6   jal   0x20298
   44d2c:  00000000   nop
   44d30:  8fbf0010   lw    ra,16(sp)
   44d34:  27bd0018   addiu sp,sp,24
   44d38:  03e00008   jr    ra
   44d3c:  00000000   nop
```

This is byte-for-byte `func_800C2478`'s two-call body: a `nop` delay slot on the `jal 0x80020298`,
and no `li`/`move`/`lui`/`lw` into `a0`-`a3` anywhere in the function before it (the only other
instructions are the frame save/restore and the first `jal`, whose own delay slot is also `nop`).

**Off-disc check.** The caller's module lives in the `xfer_town_B000` rowbase region (`config/overlays/town.rowbase.jsonl`,
`delta 0x8007D760`, proven).  Under that delta the callee address resolves to TOWN.BIN foff
`0x80020298 - 0x8007D760` - negative, i.e. below the start of TOWN.BIN entirely; the devkit module
this caller links against did not ship, same shape as `func_80071494` and `func_8007CA38`/`func_8007CA48`
above.  The only two rowbase regions whose delta puts `0x80020298` **inside their own foff extent**
are:

- **town `sweep_796260`** (`delta 0x7F88A000`, foff `[0x796260, 0x79cdc8)`, proven): `0x80020298 -
  0x7F88A000 = 0x796298`, 0x38 bytes into the region - a mid-function offset, not the region's own
  entry point, i.e. a case block inside someone else's function, not a `func_80020298` prologue.
- **main `xfer_main_25CA6C`** (`delta 0x7FDC3000`, foff `[0x25CA6C, 0x2650F8)`, proven): `0x80020298 -
  0x7FDC3000 = 0x25D298`, inside the region's extent but inside the compressed/packed span of that
  transfer, not disassemblable code.

Both checks corroborate the hand-off's claim without contradicting it: nowhere on the disc is
`0x80020298` a function start, so tier A (reading the callee's own bytes) is not available and this
is tier B evidence from the call site only - the single site above sets no argument register and has
a `nop` delay slot, exactly the tier-B test already applied to `func_80071494` and `func_8007CA38`/
`func_8007CA48`.

**Owner-visible note.** The owner accepted tier B on 2026-09-22 (see the two entries above). This
entry has by far the thinnest corpus of any tier-B symbol so far - **one** call site, against 37, 7
and 5 for the others - so it is marked owner-visible in `config/void_callees.txt` rather than folded
in silently; delete its line there to keep tier A (and the thicker tier-B corpora) only.

## Three artefact-param closures (2026-09-22): tree fixed, `config/void_callees.txt` untouched

Unlike the tiers above, these four callees each already had a `(void)` C **definition** somewhere in
the tree; the PASSTHRU class was m2c's own entry-liveness artefact (a caller-side TU spelling `arg0`-`arg3`
parameters that compile to no code, per the `func_8007CA38`/`func_80019A10` note earlier in this
file), so `census.py::void_exact_targets()` picks each of them up automatically once the arity is
made to agree everywhere - no new line in `config/void_callees.txt` is needed or was added.

- **`func_8009EF04`** (dungeon, foff `0xB97A4`) and **`func_8009EF78`** (dungeon, foff `0xB9818`):
  both bodies' first occurrence of each of `a0`-`a3` is a write, and both forward to
  `func_8009EEAC`. `src/dungeon/func_800997A4.c` now defines `void func_8009EF04(void)` and
  `src/dungeon/func_80099818.c` now defines `void func_8009EF78(void)`; both call
  `func_8009EEAC();` with no arguments as their first statement. The caller,
  `src/dungeon/func_80098378.c`, declares and calls both `extern void func_8009EF04(void);` /
  `extern void func_8009EF78(void);` with empty parens.
- **`func_800A0E44`** (dungeon, foff `0xBB6E4`, 10-word body, no `a0`-`a3` at all): calls
  `func_800A6D30` (the already-ruled `s32 func_800A6D30(void)` hub, 190 sites elsewhere in this
  file). `src/dungeon/func_8009B6E4.c` defines `void func_800A0E44(void) { D_80083466[0] =
  func_800A6D30() & 0xF; }`; the caller `src/dungeon/func_80285A70.c` declares and calls it
  `extern void func_800A0E44(void);` / `func_800A0E44();`.
- **`func_8001A3E8`** (town, foff `0x3E93E8`, 11-word body, no `a0`-`a3`): forwards to
  `func_8001A414`. `src/town/func_804693E8.c` defines `void func_8001A3E8(void) {
  D_8001E950->unk_02 = 0xFF; func_8001A414(); }`, zero-argument both for the call it makes and for
  how it is itself called.

**Tree inconsistency noted, not fixed here.** `src/town/func_8046AC98.c` still declares
`u8 func_8001A3E8(void);` and reads its result (`D_8001E950[4] = func_8001A3E8();`) - a *return-type*
mismatch against the `void` definition above, not an arity one, and out of scope for this pass (see
task 3's C-tree fixes below, which are arity-only and explicitly leave this file's return type
alone).
